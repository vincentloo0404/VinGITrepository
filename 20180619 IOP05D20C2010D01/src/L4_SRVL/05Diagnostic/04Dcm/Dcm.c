/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm.c  
*
* @brief  UDS service realize.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/25    CODER1     N/A           Original
*     1.1      2018/06/26    YCH        N/A           Original 
*     1.0      2013/03/25    CODER1     N/A           Original
*     1.1      2018/06/26    YCH        N/A           Original    
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/     
#include "Dcm.h"
#include "PduR_Dcm.h"
#include "CanTp_Cfg.h"

/************************************************************************************
* Global variables(Scope:global)
*************************************************************************************/
      
Dcm_MsgItemType  gUDS_Physical_DiagBuffer[UDS_PHYS_BUFFER_SIZE];    /*256*/
Dcm_MsgItemType  gUDS_Functional_DiagBuffer[UDS_FUNC_BUFFER_SIZE];  /*8*/
DcmDslBufferSize gDcmDslAvailableBufferSize[2];
Dcm_MsgItemType  gNegativeResponseBuffer[NEG_RESP_BUFFER_SIZE];     /*u8, NegativeResponseBuffer buffersize is 3: 7F+service ID+NegCode*/
uint16           gResponseLength; 
uint32           gDTCSwitch;



Dcm_SesCtrlType    gSesCtrlType;/*session type*/
Dcm_ProtocolType   gActiveProtocol;
Dcm_MsgContextType gMsgContextType;/*struct for request data or response data*/
Dcm_NegativeResponseCodeType gNegativeResponseCode; /*NegativeResponseCode*/


uint8         gDiagState;
uint32        gP2ServerTimer;/*maybe concern with bit-transition operation,also need to check if other 32bit varibles have bit-transition operation.*/
uint32        gS3ServerTimer;/*maybe concern with bit-transition operation*/ 
uint8         gP2ServerTimerStartFlag;
uint8         gS3ServerTimerStartFlag;

uint8   gCurrentSecurityAccessRequestLevel;/*27 service security level*/
uint32  gSecurityDelayTimeOnBootFlag;      /*flag for 27 sevice active delaytime after power on*/ 

#if(DCM_SERVICE_27_ENABLED == STD_ON)
uint32  gSecurityAcessDelayTimeOnBoot[KIND_OF_SECURITY_LEVEL];/*access 27service delay time after power on.*/
uint8   gSecurityAcessAttempNumber[KIND_OF_SECURITY_LEVEL];   /*attempt times can be tried when failed accessing.*/
uint8   gSecurityAcessAttempNumberExceeded[KIND_OF_SECURITY_LEVEL];
uint32  gSecurityAcessDelayTime[KIND_OF_SECURITY_LEVEL];      /*delaytime from [after failed trying 'gSecurityAcessAttempNumber' times accessing(exceed the limit times)] to [re accessing] 27service*/
uint8   gSecurityAcessSequence[KIND_OF_SECURITY_LEVEL];

Dcm_SecLevelType   gSecLevelType[KIND_OF_SECURITY_LEVEL]; 
#endif

/************************************************************************************
* Local variables(Scope:local)
*************************************************************************************/

STATIC uint32 gMaxNumberOfRCRRP;                                                                                     
STATIC uint8  gSubServicePosition;
STATIC Std_ReturnType  gSessionSwtPostiveRespNotDoneFlg;/*used to indicate if the response for session mode switch request has been sent successfully.*/

#if(DCM_SERVICE_22_ENABLED == STD_ON)
STATIC DidlistType DidList[1];    /*size is related to DcmDspMaxDidToRead, here it can be only one, because DcmDspMaxDidToRead = 1;*/
STATIC uint16 DidCounter; /*be used in cycle to complete the processing of more than one DIDs in one time request.*/ 
#endif 

#if(DCM_SERVICE_2E_ENABLED == STD_ON) 
STATIC uint8  gNumberOfWriteDID;
#endif


#if(DCM_SERVICE_2F_ENABLED == STD_ON) 
STATIC uint8  gNumberOf2FDID;
#endif

STATIC uint8 gDcm_RepeatTransmmitFlag;
STATIC Dcm_NegativeResponseCodeType gAppReturnValutMapToNRC[4] = 
{
    DCM_E_POSITIVERESPONSE,    /*Application callback function's return value equals 0(NRC=0x00)*/
    DCM_E_GENERALREJECT,       /*Application callback function's return value equals 1(NRC=0x10)*/
    DCM_E_CONDITIONSNOTCORRECT,/*Application callback function's return value equals 2(NRC=0x22)*/
    DCM_E_REQUESTOUTOFRANGE    /*Application callback function's return value equals 3(NRC=0x31)*/
};


/************************************************************************************
* Internal Function Prototype
*************************************************************************************/   
/*-----------------------------------------------------------------------------
    &&~ function pointer
 -----------------------------------------------------------------------------*/
STATIC void  (*gFunctionHandler)(void);
STATIC uint8 (*gSubFunctionHandler)(Dcm_MsgContextType* pMsgContext);
STATIC void  (*gVoidSubFunctionHandler)(Dcm_MsgContextType* pMsgContext);
STATIC void  (*gSubFunctionPostHandler)(Std_ReturnType Result);

/*-----------------------------------------------------------------------------
    &&~ function declaration
 -----------------------------------------------------------------------------*/
STATIC FUNC(uint8,DCM_CODE) FindUdsSid
(
    uint8 RequestSid
);
STATIC FUNC(void,DCM_CODE)  DsdInternal_UdsSidDispatcher
(
    void
);
STATIC FUNC(void,DCM_CODE)  DsdInternal_DidDispatcher
(
    void
);
#if(DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN==STD_ON)
extern FUNC(void,DCM_CODE)  DslInternal_RCRResponsePending
(
    uint8 ForceRCR_RP
);
#else
STATIC FUNC(void,DCM_CODE)  DslInternal_RCRResponsePending
(
    uint8 ForceRCR_RP
);
#endif
                                                               
STATIC FUNC(void,DCM_CODE)  DsdInternal_10_11_28_85
(
    void
);

#if(DCM_SERVICE_27_ENABLED==STD_ON)
STATIC FUNC(void,DCM_CODE)  DsdInternal_AccessAttemptNumberDec
(
    void
);
#endif

#if(DCM_INTERNALTEST_SERVCIE_SUPPORTED == STD_ON)

STATIC FUNC(void,DCM_CODE)  Dcm_InternalTestServiceFnc
(
	void
);

#endif

       


/******************************************************************************
* Name         :  Dcm_Init 
* Called by    :  Application 
* Preconditions:  None
* Parameters   :  -ConfigPtr: Pointer pointing to the configure parameter of Dcm
* Return code  :  None
* Description  :  Initial Dcm module's global variable
*                
******************************************************************************/
FUNC(void,DCM_CODE) Dcm_Init
(
    P2VAR(Dcm_ConfigType,AUTOMATIC,DCM_APPL_DATA) ConfigPtr
)
{
    uint8  i;
    uint16 j;
    uint16 k;
    uint16 l;

    dDiag_vDcmAppInit();
    Set_ActiveProtocol(ConfigPtr->protocolType);
    gNegativeResponseCode = DCM_E_POSITIVERESPONSE;
    Set_SesCtrl(DCM_DEFAULT_SESSION);
    Clr_S3_Server_Timer();
    gS3ServerTimerStartFlag = 0;
    
    Clr_P2_Server_Timer();
    gP2ServerTimerStartFlag = 0;
    
    Reset_DiagState();
    Reset_PduId();
    gSecurityDelayTimeOnBootFlag = 1;/*flag showing if 27 service need to delay a specified time after poweron.*/
    
    #if(DCM_SERVICE_27_ENABLED == STD_ON)
    for(i = 0 ; i < KIND_OF_SECURITY_LEVEL ; i++)  /*each level type there is the time parameters.*/
    {
        /*set initial value about 27 service active delay time after power on. The value is 10000,see Dcm_Lcfg.c;*/
        gSecurityAcessDelayTimeOnBoot[i] = gDcmDspSecurityRow[i].DcmDspSecurityDelayTimeOnBoot/DCM_TASK_TIME;
        /*set initial value about 27 service repeat request times after failed to access.The value is 3,see Dcm_Lcfg.c;*/
        gSecurityAcessAttempNumber[i] = gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay;
        /*set initial value about 27 service delay time between two times request when ECU lock because of failed to key-checking.
        the value is 10000/5 or 10000/10.*/
        gSecurityAcessDelayTime[i] = gDcmDspSecurityRow[i].DcmDspSecurityDelayTime/DCM_TASK_TIME;
        /* value==1 indicate ECU has tried the most permitted times.*/
        gSecurityAcessAttempNumberExceeded[i] = 0;
        /*shows current access state. 0 means initial and start to accessing and 1 means have gotten seeds.*/
        gSecurityAcessSequence[i] = 0;
        /* DCM_SEC_LEV_LOCK means 27 service default is no used*/
        gSecLevelType[i] = DCM_SEC_LEV_LOCK;
    }
    #endif
    
    /*-* Init the Dcm variables *-*/
    for(j=0;j<UDS_PHYS_BUFFER_SIZE;j++)
    {
	    gUDS_Physical_DiagBuffer[j] = 0;       	
    }
    
    for(k=0;k<UDS_FUNC_BUFFER_SIZE;k++)
    {
    	gUDS_Functional_DiagBuffer[k] = 0;
    }
    
    gDcmDslAvailableBufferSize[0] = UDS_PHYS_BUFFER_SIZE;
    gDcmDslAvailableBufferSize[1] = UDS_FUNC_BUFFER_SIZE;
    
    for(l=0;l<NEG_RESP_BUFFER_SIZE;l++)
    {
    	gNegativeResponseBuffer[l] = 0;    	
    }
    
    DidList[0].Did = 0;
    DidList[0].DidPosition = 0;    

    gResponseLength = 0; 
    gDTCSwitch = 0x01;

    gCurrentSecurityAccessRequestLevel = DCM_SEC_LEV_L1;
    
    gMaxNumberOfRCRRP = DCM_NUM_MAX_RESPPEND;
    gSubServicePosition = 0;
    gSessionSwtPostiveRespNotDoneFlg = 1;
    DidCounter = 0;
    gDcm_RepeatTransmmitFlag = 0;
    #if(DCM_SERVICE_2E_ENABLED==STD_ON)
    gNumberOfWriteDID = NUMBER_OF_WRITE_DID;
    #endif
    
    #if(DCM_SERVICE_2F_ENABLED==STD_ON)
    gNumberOf2FDID = NUMBER_OF_CONTROL_DID;
    #endif
    
    
}

/******************************************************************************
* Name         :  Dcm_GetSecurityLevel 
* Called by    :  DspInternal_Uds_SecurityAccess 
* Preconditions:  None
* Parameters   :  SecLevel
* Return code  :  the level of security
* Description  :  Get the current security level.
*                
******************************************************************************/
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetSecurityLevel
(
    P2VAR(Dcm_SecLevelType,AUTOMATIC,DCM_APPL_DATA) SecLevel
)
{   
    Std_ReturnType result;
    result = (Std_ReturnType)(*SecLevel + 1) / 2;
    return result;
}
/******************************************************************************
* Name         :  Dcm_GetSesCtrlType 
* Called by    :   
* Preconditions:  None
* Parameters   :  SesCtrlType
* Return code  :  session control type
* Description  :  Get the current session control type.
*                
******************************************************************************/
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetSesCtrlType
(
    P2VAR(Dcm_SesCtrlType,AUTOMATIC,DCM_APPL_DATA) SesCtrlType
)
{
     return (*SesCtrlType);
}
/******************************************************************************
* Name         :  Dcm_GetActiveProtocol 
* Called by    :  Application	 
* Preconditions:  None
* Parameters   :  ActiveProtocol
* Return code  :  the current active protocol
* Description  :  Get current active protocol
*                
******************************************************************************/
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocol
(
    P2VAR(Dcm_ProtocolType,AUTOMATIC,DCM_APPL_DATA) ActiveProtocol
)
{
    return *ActiveProtocol;
}
/******************************************************************************
* Name         :  Dcm_ResetToDefaultSession 
* Called by    :  App callback---App_Hardreset / DslInternal_Timer_CallbackTask
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Force the current session return to default session;
*                
******************************************************************************/
FUNC(void,DCM_CODE) Dcm_ResetToDefaultSession
(
    void
)
{
    App_DefaultSessionPost(E_OK);  
}
/******************************************************************************
* Name         :  Dcm_MainFunction 
* Called by    :  Application 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Main function of Dcm module
*                
******************************************************************************/
FUNC(void,DCM_CODE) Dcm_MainFunction
(
    void
)
{                        

    PduInfoType temp;
    Std_ReturnType result;
            
    u32FreRunCntrForRand++;/*used for 27 service,generate rand data*/
        
    DsdInternal_UdsSidDispatcher();
    if(gDcm_RepeatTransmmitFlag == 1)
    {
        if(gP2ServerTimer > 0)
        {
            temp.SduDataPtr = gMsgContextType.resData;
            temp.SduLength = (uint16)gMsgContextType.resDataLen;
            gResponseLength = (uint16)gMsgContextType.resDataLen;
            result = PduR_DcmTransmit(gMsgContextType.dcmRxPduId,&temp);
            if(result == E_OK)    /* FF has been correctly transmitted */
            {
                gDcm_RepeatTransmmitFlag = 0;
                gP2ServerTimerStartFlag = 0;  /* Stop P2 Timrer */
                Clr_P2_Server_Timer();
                Clr_DiagState(DIAG_UDS_PROCESSING);
            }
            else
            {
                gDcm_RepeatTransmmitFlag = 1;
            }
        }
        else
        {
            gDcm_RepeatTransmmitFlag = 0;
        }
    }
}

/*****************************************************************************************************
* Name         :  DslInternal_Timer_CallbackTask 
* Called by    :  None 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Exceute period=1ms,Preocssing Uds's S3, P2 and P2* Timer.called
                  in 1ms timer interrupt routine
*                
*****************************************************************************************************/
FUNC(void,DCM_CODE) DslInternal_Timer_CallbackTask
(
    void
)
{
    /* for 0x27, delay time after sevral times failed accessing */
    if(gSecurityAcessAttempNumber[gCurrentSecurityAccessRequestLevel-1] == 0) /* means ECU access-failed(not pass security) has exceeded limit times. */ 
    {
        if(gSecurityAcessDelayTime[gCurrentSecurityAccessRequestLevel-1] != 0)/* means ECU has got the dalaytime and being in waitting.*/
        {
            gSecurityAcessDelayTime[gCurrentSecurityAccessRequestLevel-1]--;
        }
        else/*means delay time has elapsed, so*/ 
        {
            /*re-assign the times value which canbe tried to access.*/
            gSecurityAcessAttempNumber[gCurrentSecurityAccessRequestLevel-1] = gDcmDspSecurityRow[gCurrentSecurityAccessRequestLevel-1].DcmDspSecurityNumAttDelay;
            /*re-assign the delay time.*/
            gSecurityAcessDelayTime[gCurrentSecurityAccessRequestLevel-1] = gDcmDspSecurityRow[gCurrentSecurityAccessRequestLevel-1].DcmDspSecurityDelayTime/DCM_TASK_TIME;
            gSecurityAcessSequence[gCurrentSecurityAccessRequestLevel-1] = 0; /*means still have not  got the seeds.*/
        }
    }
    /* for 0x27, delay time on boot */ 
    if(gSecurityDelayTimeOnBootFlag == 1)
    {
        if(gSecurityAcessDelayTimeOnBoot[gCurrentSecurityAccessRequestLevel-1] != 0)
        {
            gSecurityAcessDelayTimeOnBoot[gCurrentSecurityAccessRequestLevel-1]--;/*wait until delay time is expired.*/
        }
        else
        {
            gSecurityDelayTimeOnBootFlag = 0;
            /*reset the initial config value.*/
            gSecurityAcessDelayTimeOnBoot[gCurrentSecurityAccessRequestLevel-1] = gDcmDspSecurityRow[gCurrentSecurityAccessRequestLevel-1].DcmDspSecurityDelayTimeOnBoot/DCM_TASK_TIME;  
        }
    }
    /* S3 Timer */
    if(gS3ServerTimerStartFlag == 1)
    {
        if(gS3ServerTimer != 0)
        {
            Dec_S3_Server_Timer();/*S3 timer dece*/
            if(gS3ServerTimer == 0)
            {
                 Dcm_ResetToDefaultSession();
                 #if(DCM_SERVICE_27_ENABLED == STD_ON) 
                 Set_SecLevel(DCM_SEC_LEV_LOCK); /*means securityacess related service will be locked*/
                 #endif
            }
        }
    }
    /* P2 and P2* timer  */
    if(gP2ServerTimerStartFlag == 1)
    {
        if(gMaxNumberOfRCRRP != 0) 
        {
            Dec_P2_Server_Timer();
            /* If P2 timeout,send first 0x78 negative response and change P2 to P2Ext */
            DslInternal_RCRResponsePending(0);
            /* If P2Ext timeout,send following 0x78 negative response */
            if((gP2ServerTimer > (uint32)(gDcmDspSessionRow[gSesCtrlType-1].DcmDspSessionP2ServerMax/DCM_TASK_TIME))&&\
               (gP2ServerTimer < (((uint32)(gDcmDspSessionRow[gSesCtrlType-1].DcmDspSessionP2StarServerMax/DCM_TASK_TIME))>>1)))
            {
                DslInternal_RCRResponsePending(1);
            }
        }
        else
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_GENERALREJECT);
            DsdInternal_ProcessingDone(&gMsgContextType);
            Set_DiagState(DIAG_UDS_RCRP_DONE);
        }
    }
}

/*****************************************************************************************************
* Name         :  DspInternal_Uds_DiagnosticSessionControl 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x10
*                
******************************************************************************************************/
#if(DCM_SERVICE_10_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_DiagnosticSessionControl
(
    void
)
{
    /*Dcm_Delay(1000); used for testing 0x78 NR, if not limited maximum of 0x78 NR, CANoe will get 3 0x78 NRs */
    /* Check message format */    
    if(gMsgContextType.reqDataLen!=2)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        if(GetSuppressPosResponseBit()==0)/* If positive response is supressed, dont' need make it */
        {
            gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
            gMsgContextType.resData[1]=gMsgContextType.reqData[1];
            gMsgContextType.resData[2]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax>>8);
            gMsgContextType.resData[3]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax); 
            gMsgContextType.resData[4]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2StarServerMax>>8);
            gMsgContextType.resData[5]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2StarServerMax);
            gMsgContextType.resDataLen=6;
        }   
        else
        {
        	;
        }     
        
        gSubFunctionHandler=(EcucSubFunctionNameDef)gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;/*get the sub-function callback handle(Default\Extend\Programm)*/
        (*gSubFunctionHandler)(&gMsgContextType);/*assign parameter and execute the sub-function */       
      
        gSubFunctionPostHandler=gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunctionPost;/*get the sub-post-function callback handle(DefaultPost\ExtendPost\ProgrammPost)*/
        (*gSubFunctionPostHandler)(gSessionSwtPostiveRespNotDoneFlg);/*assign parameter and execute the sub-post-function*/       
        
    }
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_EcuReset 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x11
*                
******************************************************************************************************/
#if(DCM_SERVICE_11_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_EcuReset
(
    void
) 
{
    /* Dcm_Delay(2000);used for testing 0x78 NR, if not limited maximum of 0x78 NR, CANoe will get 6 0x78 NRs */
    /* Check message format */
    if(gMsgContextType.reqDataLen!=2)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        DsdInternal_10_11_28_85();
    }
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_ClearDiagnosticInformation 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x14
*                
******************************************************************************************************/
#if(DCM_SERVICE_14_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_ClearDiagnosticInformation
(
    void
)
{
    uint8 result;
    /* Check message format */
    if(gMsgContextType.reqDataLen!=4)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        result=App_ClearDiagnosticInformation(&gMsgContextType); 
        if(result!=0)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,gAppReturnValutMapToNRC[result]);
        }
        else
        {
            DsdInternal_ProcessingDone(&gMsgContextType); 
        }
    }
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_ReadDTCInformation 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x19 
*                
******************************************************************************************************/
#if(DCM_SERVICE_19_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_ReadDTCInformation
(
    void
)
{
    uint8 result;
    switch(gMsgContextType.reqData[1])
    {
        case 0x01:
        case 0x02:
        case 0x05:
        case 0x0f:
        case 0x11:
        case 0x12:
        case 0x13:
        if(gMsgContextType.reqDataLen!=3)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        	
        }
        break;   
        case 0x04:
        case 0x06:
        case 0x10:
        if(gMsgContextType.reqDataLen!=6)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        break;
        case 0x07:
        case 0x08:
        if(gMsgContextType.reqDataLen!=4)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        	
        }
        break;
        case 0x09:
        if(gMsgContextType.reqDataLen!=5)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        	
        }
        break;
        default:/*e.g. gMsgContextType.reqData[1]==0x0A or 03*/
        if(gMsgContextType.reqDataLen!=2)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        	
        }
        break;
    }
    if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)/*positive response*/
    {
        gSubFunctionHandler=(EcucSubFunctionNameDef)gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction; 
        result=(*gSubFunctionHandler)(&gMsgContextType); 
        if(result!=0)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,gAppReturnValutMapToNRC[result]);
        }
        else
        {
            DsdInternal_ProcessingDone(&gMsgContextType); 
        }
    }   
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_ReadDataByIdentifier 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x22
*                
******************************************************************************************************/
#if(DCM_SERVICE_22_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_ReadDataByIdentifier
(
    void
)
{
    gMsgContextType.reqDataLen-=1;  /* the correct request length should be even number and bigger than 0 */
    /* Check message format */
    if(((gMsgContextType.reqDataLen&0x01)!=0)||(gMsgContextType.reqDataLen>(DcmDspMaxDidToRead<<1)))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        DsdInternal_DidDispatcher();
        DsdInternal_ProcessingDone(&gMsgContextType);
    }
}
#endif

/*****************************************************************************************************
* Name         :  DspInternal_Uds_SecurityAccess 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None 
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x27
*                
******************************************************************************************************/
#if(DCM_SERVICE_27_ENABLED==STD_ON)
/* there is only one kind of security access level at a time */
FUNC(void,DCM_CODE) DspInternal_Uds_SecurityAccess
(
    void
)
{
    uint8 i;
    uint8 level;
    uint8 result;
    level=Dcm_GetSecurityLevel(gMsgContextType.reqData+1);
    /* Check whether the delay time on-boot has elapsed */
    if(gSecurityDelayTimeOnBootFlag!=0)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
    }
    /* If attempt number is over the limit, check whether the delay time has elapsed */
    else if(gSecurityAcessAttempNumber[gCurrentSecurityAccessRequestLevel-1]==0)
    {
        if(gSecurityAcessAttempNumberExceeded[gCurrentSecurityAccessRequestLevel-1]==1)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_EXCEEDNUMBEROFATTEMPTS);
            gSecurityAcessAttempNumberExceeded[gCurrentSecurityAccessRequestLevel-1]=0;
        }
        else
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUIREDTIMEDELAYNOTEXPIRED);
        }
    }
    /********** Get Seed **********/
    else if((gMsgContextType.reqData[1]&1)!=0) 
    {
        /* Check message format */
        if (gMsgContextType.reqDataLen!=2)  /* if enable DcmDspSecurityADRSize, check standard should not be 2 */
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            DsdInternal_AccessAttemptNumberDec();
        }
        /* Check the requested security leve has already been cracked, if so, send zero seeds */
        else if (gSecLevelType[level-1]==level)  /*means currently diagrequest has passed the security access.*/
        {                                        /* e.g.:2E service, when first write need getseed,then when second write will execute this part which send 0;*/
            gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
            gMsgContextType.resData[1]=gMsgContextType.reqData[1];
            for (i=0;i<gDcmDspSecurityRow[level-1].DcmDspSecuritySeedSize;i++)
            {
                gMsgContextType.resData[2+i]=0x00;
            }
            gCurrentSecurityAccessRequestLevel=level;/* Record latest request's level */
            gSecurityAcessSequence[gCurrentSecurityAccessRequestLevel-1]=HAVE_GOTTON_SEED;/* Means the client has get the seeds already */
            gMsgContextType.resDataLen=gDcmDspSecurityRow[level-1].DcmDspSecuritySeedSize+2;    
            
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
        else /*If not, call related appliction callback function to get the seeds */
        {
            gSubFunctionHandler=(EcucSubFunctionNameDef)gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;
            (*gSubFunctionHandler)(&gMsgContextType);            
            gSecurityAcessSequence[gCurrentSecurityAccessRequestLevel-1]=HAVE_GOTTON_SEED;/* Means the client has get the seeds already */
            gMsgContextType.resDataLen=gDcmDspSecurityRow[level-1].DcmDspSecuritySeedSize+2; 
            gCurrentSecurityAccessRequestLevel=level;
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
    }
    /************ Send Key **************/
    else
    {
        /* Check whether the client has already gotten the seeds */
        if((gSecurityAcessSequence[gCurrentSecurityAccessRequestLevel-1]&HAVE_GOTTON_SEED)!=HAVE_GOTTON_SEED)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTSEQUENCEERROR);
            DsdInternal_AccessAttemptNumberDec();
        }
        else
        {   /* Check whether the send-key request's level is equal to latest get-seed request */
            if(gCurrentSecurityAccessRequestLevel!=level)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTSEQUENCEERROR); /*wrong send-key level compared with get-seed*/
                DsdInternal_AccessAttemptNumberDec(); /*If not,decrease allowed attmept number */
            }
            /* Check message format */
            else if (gMsgContextType.reqDataLen!=(gDcmDspSecurityRow[level-1].DcmDspSecurityKeySize+2))
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                DsdInternal_AccessAttemptNumberDec();/*If not,decrease allowed attmept number */
            }
            else
            {
                /* Call related application callback funtion to compare the key */
                gSubFunctionHandler=(EcucSubFunctionNameDef)gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;                
                result=(*gSubFunctionHandler)(&gMsgContextType);
               
                if (result!=0)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INVALIDKEY);
                    DsdInternal_AccessAttemptNumberDec();/*If not,decrease allowed attmept number */
                }
                else/* If the key is valid,unlock realated security level and reset related variable */
                {
                    gSecurityAcessSequence[gCurrentSecurityAccessRequestLevel-1]=0;
                    gSecurityAcessAttempNumber[gCurrentSecurityAccessRequestLevel-1]=gDcmDspSecurityRow[gCurrentSecurityAccessRequestLevel-1].DcmDspSecurityNumAttDelay;
                    gSecurityAcessDelayTime[gCurrentSecurityAccessRequestLevel-1]=gDcmDspSecurityRow[gCurrentSecurityAccessRequestLevel-1].DcmDspSecurityDelayTime/DCM_TASK_TIME;
                    Set_SecLevel(level);
                    gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
                    gMsgContextType.resData[1]=gMsgContextType.reqData[1];
                    gMsgContextType.resDataLen=2;
                    DsdInternal_ProcessingDone(&gMsgContextType);
                }
            }
        }
    }
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_CommunicationControl 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x28
*                
******************************************************************************************************/
#if(DCM_SERVICE_28_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_CommunicationControl
(
    void
)
{
    /* Check message format */
    if(gMsgContextType.reqDataLen!=3)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    /* Check communication type */
    else if(((gMsgContextType.reqData[2]&BOTH_NORMAL_AND_NM_MSG)==0)||(gMsgContextType.reqData[2]>3))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        DsdInternal_10_11_28_85();
    }
}
#endif

/*****************************************************************************************************
* Name         :  DspInternal_Uds_WriteDataByIdentifier 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x2E
*                
******************************************************************************************************/
#if(DCM_SERVICE_2E_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_WriteDataByIdentifier
(
    void
)
{
    uint8  i;
    uint8  error=1;
    uint16 tempdid;
    uint8* tempresdata;
    uint8  didposition=0;
    uint8  securitylevel;
    uint8  result;
    tempresdata=gMsgContextType.resData;
    tempdid=Make16Bit(gMsgContextType.reqData[1],gMsgContextType.reqData[2]);
    for(i=0;i<gNumberOfWriteDID;i++)
    {
        if(tempdid==gDcmDsdSubService_2E[i].DcmDspDidIdentifier)
        {
            error=0;
            didposition=i;
            i=gNumberOfWriteDID;
        }
        else
        {
        	
        }
    }
    error==1;//强制不支持2e,等eeprom编写完成后在去除。20180623
    /* Check whether the requested DID is defined in gDcmDsdSubService_2E */
    if(error==1)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    /* Check if the requested DID supported */
    else if(gDcmDsdSubService_2E[didposition].DcmDspDidUsed!=1)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    /* Check message format */
    else if(gMsgContextType.reqDataLen!=(3+gDcmDsdSubService_2E[didposition].DcmDspDataSize))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        /* Check whether the security condition is met */
        securitylevel=gDcmDsdSubService_2E[didposition].DcmDspDidWriteSecurityLevelRef;
        if(securitylevel!=0)
        {
            #if(DCM_SERVICE_27_ENABLED==STD_ON)
            if(gDcmDspSecurityRow[securitylevel-1].DcmDspSecurityLevel!=gSecLevelType[securitylevel-1])
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
            }
            else
            #endif
            {
                /* No error happened,give positive response */
                gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
                gMsgContextType.resData+=1;     
                gSubFunctionHandler=gDcmDsdSubService_2E[didposition].DcmDspDataWriteFnc;
                result=(*gSubFunctionHandler)(&gMsgContextType);
                if(result!=0)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,gAppReturnValutMapToNRC[result]);
                }
                else
                {
                    gMsgContextType.resDataLen=3;
                    gMsgContextType.resData=tempresdata;
                    DsdInternal_ProcessingDone(&gMsgContextType);
                }
            }
        }
        else
        {
            /* No error happened,give positive response */
            gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
            gMsgContextType.resData+=1;     
            gSubFunctionHandler=gDcmDsdSubService_2E[didposition].DcmDspDataWriteFnc;
            result=(*gSubFunctionHandler)(&gMsgContextType);
            if(result!=0)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,gAppReturnValutMapToNRC[result]);
            }
            else
            {
                gMsgContextType.resDataLen=3;
                gMsgContextType.resData=tempresdata;
                DsdInternal_ProcessingDone(&gMsgContextType);
            }
        }
    }
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_InputOutputControlByIdentifier 
* Called by    :   
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x2F
*                
******************************************************************************************************/
#if(DCM_SERVICE_2F_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_InputOutputControlByIdentifier
(
    void
)
{
    uint8  i;
    uint8  error=1;
    uint16 tempdid;
    uint8* tempresdata;
    uint8  didposition=0;
    uint8  securitylevel;
    uint8  result,inputOutputControlParameter,tempLength;
    tempresdata=gMsgContextType.resData;
    tempdid=Make16Bit(gMsgContextType.reqData[1],gMsgContextType.reqData[2]);
    inputOutputControlParameter = gMsgContextType.reqData[3];
    for(i=0;i<gNumberOf2FDID;i++)
    {
        if(tempdid==gDcmDsdSubService_2F[i].DcmDspDidIdentifier)
        {
            error=0;
            didposition=i;
            i=gNumberOf2FDID;
        }
        else
        {
        	
        }
    }
    tempLength = 3+gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlOptionRecordSize+gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlEnableMaskRecordSize+gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlStatusRecordSize+1;
    /* Check whether the requested DID is defined in gDcmDsdSubService_2F */
    if(error==1)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    /* Check message format */
    else if(inputOutputControlParameter== 0 &&gMsgContextType.reqDataLen!=(tempLength-1))//00控制权给ECU
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else if(gMsgContextType.reqDataLen!=(tempLength))
    {
    	DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        /* Check whether the security condition is met */
        securitylevel=gDcmDsdSubService_2F[didposition].DcmDspDidControlSecurityLevelRef;
        if(securitylevel!=0)
        {
            #if(DCM_SERVICE_27_ENABLED==STD_ON)
            if(gDcmDspSecurityRow[securitylevel-1].DcmDspSecurityLevel!=gSecLevelType[securitylevel-1])
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
            }
            else
            #endif
            {
                /* No error happened,give positive response */
                gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
                gMsgContextType.resData+=1;
                if(inputOutputControlParameter == 0)
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataReturnControlToEcuFnc;
                }
                else if(inputOutputControlParameter == 1)
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataResetToDefaultFnc;
                }
                else if(inputOutputControlParameter == 2)
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataFreezeCurrentStateFnc;
                }
                else
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataShortTermAdjustmentFnc;
                }
                
                result=(*gSubFunctionHandler)(&gMsgContextType);
                if(result!=0)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,gAppReturnValutMapToNRC[result]);
                }
                else
                {
                    //gMsgContextType.resDataLen=4;
                    //gMsgContextType.resData=tempresdata;
                    
                    //gMsgContextType.resData+=(gDcmDsdSubService_22[DidList[i].DidPosition].DcmDspDataSize+2);
                    gMsgContextType.resData=tempresdata;
                    gMsgContextType.resDataLen=tempLength;
                    
                    DsdInternal_ProcessingDone(&gMsgContextType);
                }
            }
        }
        else
        {
            /* No error happened,give positive response */
                gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
                gMsgContextType.resData+=1;
                if(inputOutputControlParameter == 0)
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataReturnControlToEcuFnc;
                }
                else if(inputOutputControlParameter == 1)
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataResetToDefaultFnc;
                }
                else if(inputOutputControlParameter == 2)
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataFreezeCurrentStateFnc;
                }
                else
                {
                	gSubFunctionHandler=gDcmDsdSubService_2F[didposition].DcmDspDataShortTermAdjustmentFnc;
                }
                
                result=(*gSubFunctionHandler)(&gMsgContextType);
                if(result!=0)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,gAppReturnValutMapToNRC[result]);
                }
                else
                {
                    //gMsgContextType.resDataLen=4;
                    //gMsgContextType.resData=tempresdata;
                    
                    gMsgContextType.resData=tempresdata;
                    gMsgContextType.resDataLen=tempLength;
                    
                    
                    DsdInternal_ProcessingDone(&gMsgContextType);
                }
        }
    }
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_RoutineControl 
* Called by    :   
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x31
*                
******************************************************************************************************/
#if(DCM_SERVICE_31_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_RoutineControl
(
    void
)
{
    uint8 result;
    switch(gMsgContextType.reqData[1])
    {
        case START_ROUTINE:
        case STOP_ROUTINE:
        case REQUEST_ROUTINE_RESULT:
        if(gMsgContextType.reqDataLen!=4)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        	
        }
        break;   
        default:
        	DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
        break;
    }
    if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)/*positive response*/
    {
        gSubFunctionHandler=(EcucSubFunctionNameDef)gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction; 
        result=(*gSubFunctionHandler)(&gMsgContextType); 
        if(result!=0)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,gAppReturnValutMapToNRC[result]);
        }
        else
        {
            DsdInternal_ProcessingDone(&gMsgContextType); 
        }
    }   
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_TesterPresent 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x3E
*                
******************************************************************************************************/
#if(DCM_SERVICE_3E_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_TesterPresent
(
    void
)
{
    /* Check message format */
    if(gMsgContextType.reqDataLen!=2)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        if(gMsgContextType.msgAddInfo.suppressPosResponse==0)/* If positive response is supressed, dont' need make it */
        {
            gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
            gMsgContextType.resData[1]=gMsgContextType.reqData[1];
            gMsgContextType.resDataLen=2;
        }
        else
        {
        	
        }
        DsdInternal_ProcessingDone(&gMsgContextType); 
    }
}
#endif
/*****************************************************************************************************
* Name         :  DspInternal_Uds_ControlDTCSetting 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds servie 0x85
*                
*****************************************************************************************************/
#if(DCM_SERVICE_85_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DspInternal_Uds_ControlDTCSetting
(
    void
)
{
    /* Check message format */
    if(gMsgContextType.reqDataLen!=2)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        DsdInternal_10_11_28_85();  
    }
}
#endif

/*****************************************************************************************************
* Name         :  DsdInternal_SetNegResponse 
* Called by    :  Any Uds service function 
* Preconditions:  None
* Parameters   :  -pMsgContext:Pointer pointed to the buffer having NR
* Return code  :  None
* Description  :  Set negative response
*                
******************************************************************************************************/
FUNC(void,DCM_CODE) DsdInternal_SetNegResponse
(
    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext,
    uint8 ErrorCode
)
{
    SetNegativeResponseCode(ErrorCode);
    gNegativeResponseBuffer[0]=0x7F;
    gNegativeResponseBuffer[1]=pMsgContext->reqData[SID_POSITION];
    gNegativeResponseBuffer[2]=gNegativeResponseCode;
    pMsgContext->resData=gNegativeResponseBuffer; /* Make global pointer point to gNegativeResponseBuffer */
    pMsgContext->resDataLen=3;
}
/******************************************************************************************************
* Name         :  DsdInternal_ProcessingDone 
* Called by    :  Any Uds service function 
* Preconditions:  None
* Parameters   :  -pMsgContext: Pointer pointed to the buffer having response 
* Return code  :  None 
* Description  :  Preocessing the response result of each Uds service.Transmitt 
*                 negative or positive respose(if not suppressed)
******************************************************************************************************/
FUNC(void,DCM_CODE) DsdInternal_ProcessingDone
(
    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext
)
{
    PduInfoType temp;
    Std_ReturnType result;
    if((gDiagState&DIAG_UDS_RCRP_DONE)!=DIAG_UDS_RCRP_DONE)
    {
        /* Suppress positive response or fobidden 0x11 and 0x12 NRC under the condition of functionally-addressing */
        if(((GetSuppressPosResponseBit()==1)&&(gNegativeResponseCode==DCM_E_POSITIVERESPONSE))||(gMsgContextType.resDataLen==0))
        {
            /* Start S3 Timer */
            if(gSesCtrlType!=DCM_DEFAULT_SESSION)
            {
                gS3ServerTimerStartFlag=1;
                Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
            }
            else
            {
            	
            }
            gP2ServerTimerStartFlag=0;
            Clr_P2_Server_Timer();
            ClrSuppressPosResponseBit();
            ClrNegativeResponseCode();
            Clr_ActiveProtocol();
            Reset_DiagState();
            Reset_PduId();
        }
        else
        {
            if(gNegativeResponseCode != DCM_E_CONDITIONSNOTCORRECT)   /* add this condition,make sure the DCM_E_CONDITIONSNOTCORRECT has higher priority*/
            {
                /* Check whether the response length is over the related buffer's buffersize */
                if(gMsgContextType.resDataLen>UDS_PHYS_BUFFER_SIZE) /* Response is always put in physical buffer */
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                }
                else
                {
                	
                }            
            }
            else
            {
            	
            }
            
            /* Positive response or negative response */
            temp.SduDataPtr=pMsgContext->resData;
            temp.SduLength=(uint16)pMsgContext->resDataLen;
            gResponseLength=(uint16)pMsgContext->resDataLen;
            result=PduR_DcmTransmit(pMsgContext->dcmRxPduId,&temp);
            if(result==E_OK)  /* FF has been correctly transmitted */
            {
                gDcm_RepeatTransmmitFlag=0;
                gP2ServerTimerStartFlag=0; /* Stop P2 Timer */
                Clr_P2_Server_Timer();
                Clr_DiagState(DIAG_UDS_PROCESSING);
                
                /* set the value and used in sessioncontrol function, to be confirmed */
                if(0x7F != *pMsgContext->resData) 
                {
                   gSessionSwtPostiveRespNotDoneFlg = 0;/*means positive response has been sent success. */              
                }
                else
                {
                	
                }

            }
            else
            {
                gDcm_RepeatTransmmitFlag=1;
            }
            ClrNegativeResponseCode();
        }
        Reset_Max_Number_Of_RCRRP();
    }
    else
    {
        Clr_ActiveProtocol();
        Reset_PduId();
        Clr_DiagState(DIAG_UDS_RCRP_DONE);
    }
}


/****************************************************************************************************
* Name         :  FindSid 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  -RequestSid:service Id in requested message.
* Return code  :  The service Id's positon in gCurrentSidMap
* Description  :  Find the Sid's postion in gCurrentSidMap, get the number but not the service ID self. 
*                
*****************************************************************************************************/

FUNC(uint8,DCM_CODE) FindUdsSid
(
    uint8 RequestSid
)
{
    uint8 result = 0xFF;
    uint8 offset=0;
    if(((RequestSid&0x40)==0)&&(RequestSid<=0x85))/*10-3E,83-87. 00~0F for OBD, other reserved*/
    {
        if((RequestSid&0x80)!=0)
        {
          offset=0x40;
        }
        else
        {
        	
        }
        result=gCurrentSidMap[RequestSid-offset];/* 0x85-0x40=0x45=69, Get 09 by searching table，just indicate 0x85.*/
    }
    else
    {
    	
    }
    return result;
}


/******************************************************************************************************
* Name         :  DsdInternal_UdsSidDispatcher 
* Called by    :  Dcm_MainFunction 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Uds service dispatcher.
*                 
******************************************************************************************************/
FUNC(void,DCM_CODE) DsdInternal_UdsSidDispatcher
(
    void
)
{
    uint8 i = 0;
    uint8 sid=0;
    DcmDsdServiceTable service;
    uint8 sessiontype = 0;
    uint8 error=1;
    gSubServicePosition=0;
    if((gDiagState&DIAG_UDS_INDICATION)==DIAG_UDS_INDICATION)
    {
        Clr_DiagState(DIAG_UDS_INDICATION);
        Set_DiagState(DIAG_UDS_PROCESSING);
        sid=FindUdsSid(gMsgContextType.reqData[0]);/* sid is not the service IDbut the sequence number in table gSidMap_1 */
        /*
        if(sid == 0x08)
        {
        	sid = 0x08;
        }
        */
        service=gCurrentDcmDsdServiceTable[sid];/* by sid, get the service context in table gServiceTable_1 which is DcmDsdServiceTable type.*/
        if( (sid<gCurentDcmDsdServiceTableSize) && ((service.IsSupportedFunctionReq-gMsgContextType.msgAddInfo.reqType)>=0) )
        { 
          /*IsSupportedFunctionReq means the service supportted address mode,value canbe 0-physical;1-functional;2-both.
          gMsgContextType.msgAddInfo.reqType is the current request address mode.so value range only 0 or 1;
          so result < 0 occurs when support mode is only physical and actually request mode is functional.*/
            if(gMsgContextType.reqDataLen<2)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            }
            else
            {
                /* Check session type */
                sessiontype=service.ServiceTable.DcmDsdSidTabSessionLevelRef;
                if((gDcmDspSessionRow[sessiontype].DcmDspSessionLevel&gSesCtrlType)==0)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION);
                }
                else
                {
                    /* If the requested service has sub-function */
                    if((service.ServiceTable.DcmDsdSidTabSubfuncAvail==1))
                    {
                        /* Set suprresPostResponseBit if needed */
                        gMsgContextType.msgAddInfo.suppressPosResponse=(gMsgContextType.reqData[1]&SET_SUPPRESS_POS_RESONPOSE_BIT_MASK)>>7;
                        gMsgContextType.reqData[1]&= ~ SET_SUPPRESS_POS_RESONPOSE_BIT_MASK; /* set the highest bit as 0;*/
                        /* Check if the sub-function is defined in the gDcmDsdSubService */
                        /* and following part can located the subfunction postition in table gDcmDsdSubService*/
                        for(i=service.FirstSubService;i<(service.LastSubService+1);i++)
                        {
                            if((gMsgContextType.reqData[1]==gDcmDsdSubService[i].DcmDsdSubServiceId))
                            {
                                error=0;
                                gSubServicePosition=i;
                                i=service.LastSubService+1; 
                            }
                            else
                            {
                            	
                            }
                        }
                        if(error==1)
                        {
                            
                            if(gMsgContextType.msgAddInfo.reqType==0)  /* Under the situation of functionally-addressing,not send 0x12 NR */
                            {
                                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
                            }
                            else 
                            {
                                gMsgContextType.resDataLen=0;
                                DsdInternal_ProcessingDone(&gMsgContextType);
                            }
                        }
                        else
                        {
                            /* Check if the sub-function supported */
                            if(gDcmDsdSubService[gSubServicePosition].DcmDsdSubServiceIdSupported!=SUB_FUNCTION_SUPPORTED)
                            {
                                /*Physical Addressing*/
                                if(gMsgContextType.msgAddInfo.reqType==0)/* Under the situation of functionally-addressing,not send 0x12 NR */ 
                                {
                                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
                                }
                                else
                                {
                                    gMsgContextType.resDataLen=0;
                                    DsdInternal_ProcessingDone(&gMsgContextType);
                                }
                            }
                            else
                            {
                                /* Call corresponding service function */
                                gFunctionHandler=service.ServiceTable.DcmDsdSidTabFnc;
                                (*gFunctionHandler)(); 
                            }
                        }
                    }
                    else
                    {
                        /* Call corresponding service function ,if not has subservice*/
                        gFunctionHandler=service.ServiceTable.DcmDsdSidTabFnc;
                        (*gFunctionHandler)();
                    }
                }
            }
        }
        
      #if(DCM_INTERNALTEST_SERVCIE_SUPPORTED==STD_ON)
        else if(gMsgContextType.reqData[0] == 0xE0 )
        {       
        	Dcm_InternalTestServiceFnc();
        }
      #endif
        
        else
        {
            if(gMsgContextType.msgAddInfo.reqType==0) /*this can confirm request sid exceed the supportted service number.*/
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SERVICENOTSUPPORTED); /*service not supportted.*/
            }
            else /*request addressing mode is functional mode,so response data length is 0;*/
            {
                gMsgContextType.resDataLen=0;  /*functional addressing mode, no response data,only serviceID and sub-function ID*/
                DsdInternal_ProcessingDone(&gMsgContextType);
            }
        }

    }
    if(gNegativeResponseCode!=0)
    {
        DsdInternal_ProcessingDone(&gMsgContextType);
    }
    else
    {
    	
    }
}
/******************************************************************************************************
* Name         :  DidDispatcher 
* Called by    :  DspInternal_Uds_ReadDataByIdentifier 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Implementation of Uds service 0x22
*                
******************************************************************************************************/
#if(DCM_SERVICE_22_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DsdInternal_DidDispatcher
(
    void
)
{
    uint16 tempdid;
    uint8* tempreqdata;
    uint8* tempresdata;
    uint16 i;
    uint16 j;
    uint8  securitylevel;
    uint8 error=0;
    
    tempreqdata=gMsgContextType.reqData;
    tempresdata=gMsgContextType.resData;
    DidCounter=0;
    /* Check whether the request DIDs are supported and record total number of DID */
    for(i=0;i<gMsgContextType.reqDataLen;i+=2)
    {
        tempdid=Make16Bit(gMsgContextType.reqData[1],gMsgContextType.reqData[2]); /* e.g. 22==reqData[0]; F1==reqData[1];87==reqData[2]*/
        for(j=0;j<NUMBER_OF_READ_DID;j++)
        {
            if(tempdid==gDcmDsdSubService_22[j].DcmDspDidIdentifier)
            {
                /* check whether the request DID meet the security access condition only check if you config rightly.  */
                securitylevel=gDcmDsdSubService_22[j].DcmDspDidReadSecurityLevelRef;
                if(securitylevel!=0)
                {
                    #if(DCM_SERVICE_27_ENABLED==STD_ON)
                    if(gDcmDspSecurityRow[securitylevel-1].DcmDspSecurityLevel!=gSecLevelType[securitylevel-1])
                    {
                        gMsgContextType.reqData=tempreqdata;/* in case the situation that allow servral Did in one request and
                                                               the first Did is supported and don't need security access, the
                                                               second Did is also supported but need security access 
                                                               the following line
                                                               " gMsgContextType.reqData+=2;" will be executed */
                                                               
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                        i=(uint16)gMsgContextType.reqDataLen;
                        j=NUMBER_OF_READ_DID;
                        error=1; 
                    }
                    else
                    {
                    	
                    }
                    #endif
                }
                else
                {
                    DidList[DidCounter].Did=tempdid;
                    DidList[DidCounter].DidPosition=j;
                    DidCounter++;/*when meets more than one DIDs at one single request,DidCounter will be added more than 1. */
                    gMsgContextType.reqData+=2;
                    j=NUMBER_OF_READ_DID; 
                }
            }
            else
            {
                if(j==(NUMBER_OF_READ_DID-1))
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                    i=(uint16)gMsgContextType.reqDataLen;
                    error=1;
                }
                else
                {
                	
                }
            }
        }
    }
   
    if(error==0)
    {
        if(DidCounter!=0)
        { 
            gMsgContextType.reqData=tempreqdata;
            /* check if the  number of requested DID is bigger than DcmDspMaxDidToRead */
            if(DidCounter>DcmDspMaxDidToRead)    
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
            }
            else
            {
                /* Call realated did processing function */
                gMsgContextType.resData[0]=0x62; /* Record response Sid */
                (gMsgContextType.resData)+=1;
                gMsgContextType.resDataLen=1;    
                for(i=0;i<DidCounter;i++)  /*DidCounter>1 only When meets more than one DIDs at one single request.*/ 
                {
                    gVoidSubFunctionHandler=gDcmDsdSubService_22[DidList[i].DidPosition].DcmDspDataReadFnc;
                    (*gVoidSubFunctionHandler)(&gMsgContextType);
                    /* If it is not implemented in app_dcm.c, it should be added here */
                    /* put following content here but not in App_Dcm.c callback*/
                    gMsgContextType.resData+=(gDcmDsdSubService_22[DidList[i].DidPosition].DcmDspDataSize+2);
                    gMsgContextType.resDataLen+=(gDcmDsdSubService_22[DidList[i].DidPosition].DcmDspDataSize+2);
                   
                }
                gMsgContextType.resData=tempresdata;/* re-refer to the first response adress which the content is 62.*/
            }
        }
        else
        {
        	
        }
    }
}
#endif
/********************************************************************************************************
* Name         :  DslInternal_RCRResponsePending 
* Called by    :  DslInternal_Timer_CallbackTask 
* Preconditions:  None
* Parameters   :  ForceRCR_RP,used to indicate if 0x78 code be used
* Return code  :  None
* Description  :  When p2 timeout or ForceRCR_RP == 1, DCM will force to send a NegCode 0x78.
*********************************************************************************************************/
FUNC(void,DCM_CODE) DslInternal_RCRResponsePending
(
    uint8 ForceRCR_RP
)
{
    PduInfoType temp;
    if((gP2ServerTimer<(uint32)(10/DCM_TASK_TIME))||(ForceRCR_RP==1))  
    {
        Set_DiagState(DIAG_UDS_RCRP);/*show P2 or P2* timeout occurs.*/
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING);
        /*put it into PDU buffer.*/
        temp.SduDataPtr=gMsgContextType.resData;
        temp.SduLength=(uint16)gMsgContextType.resDataLen;

        (void)PduR_DcmTransmit(gMsgContextType.dcmRxPduId,&temp);/* Transmite 0x78 negative response(NR) */
        /* Make the global pointer re-point to the buffer before tranmitting 0x78 NR */
        gMsgContextType.resData=gUDS_Physical_DiagBuffer;/* Response is always put in physical buffer since it is always physical.
                                                            And only request has two kinds(functional and physical) */
        Dec_Max_Number_Of_RCRRP(); /* Decrease the allowed maximum number of 0x78 NR */
    }
    else
    {
    	
    }
}

/**********************************************************************************************************
* Name         :  DsdInternal_10_11_28_85 
* Called by    :  Uds service(0x10,0x11,0x28 and 0x85) function 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None 
* Description  :  If no error happened, give positive response if needed, and
*                 call related application callback function
***********************************************************************************************************/
FUNC(void,DCM_CODE) DsdInternal_10_11_28_85
(
    void
)
{
    if(gMsgContextType.msgAddInfo.suppressPosResponse==0)/* If positive response is supressed, dont' need make it */
    {
        gMsgContextType.resData[0]=gMsgContextType.reqData[0]+SIDOFFSET;
        gMsgContextType.resData[1]=gMsgContextType.reqData[1];
        gMsgContextType.resDataLen=2;
    }
    else
    {
    	
    }

    gSubFunctionHandler=(EcucSubFunctionNameDef)gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;/*gSubServicePosition has been located in DsdInternal_UdsSidDispatcher()*/
    (*gSubFunctionHandler)(&gMsgContextType);       
        

}
/******************************************************************************************************
* Name         :  DsdInternal_AccessAttemptNumberDec 
* Called by    :  DspInternal_Uds_SecurityAccess 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  Decrease allowed security access attempt number
*                
******************************************************************************************************/
#if(DCM_SERVICE_27_ENABLED==STD_ON)
FUNC(void,DCM_CODE) DsdInternal_AccessAttemptNumberDec
(
    void
)
{
    if(gSecurityAcessAttempNumber[gCurrentSecurityAccessRequestLevel-1]!=0) /*means ECU can continute to trying another access.*/
    {
        gSecurityAcessAttempNumber[gCurrentSecurityAccessRequestLevel-1]--;
        if(gSecurityAcessAttempNumber[gCurrentSecurityAccessRequestLevel-1]==0)/*means ECU has tried enouth.*/
        {
            gSecurityAcessAttempNumberExceeded[gCurrentSecurityAccessRequestLevel-1]=1;/*set ECU disable trying access flag.*/
        }
        else
        {
        	
        }
    }   
    else
    {
    	
    }
}
#endif

/******************************************************************************************************
* Name         :  Dcm_InternalTestServiceFnc 
* Called by    :  DsdInternal_UdsSidDispatcher 
* Preconditions:  None
* Parameters   :  None
* Return code  :  None
* Description  :  only for internal test
*                
******************************************************************************************************/
#if(DCM_INTERNALTEST_SERVCIE_SUPPORTED==STD_ON)
FUNC(void,DCM_CODE)  Dcm_InternalTestServiceFnc
(
	void
)
{    

    App_InternalTestServcie(gMsgContextType.reqData[1]);
    
    switch ( gMsgContextType.reqData[1] )
    {
        
    	case 0x01:
    	{
    	    
    	    break;	
    	}
    	case 0x02:
    	{
    		break;
    	}
    	case 0x03:
    	{
    	
    	    break;	
    	}
    	case 0x04:
    	{
    	
    		break;
    	}
    	case 0x05:
    	{
    	
    	    break;	
    	}
    	case 0x06:
    	{
    	
    		break;
    	}
    	case 0x07:
    	{
    	
    	    break;	
    	}
    	case 0x08:
    	{
    	
    		break;
    	}
    	case 0x09:
    	{
    	
    	    break;	
    	}
    	case 0x10:
    	{
    	
    		break;
    	}
    	case 0x11:
    	{
    	
    	    break;	
    	}
    	case 0x12:
    	{
    	
    		break;
    	}
    	case 0x13:
    	{
    	
    	    break;	
    	}
    	case 0x14:
    	{
    	
    		break;
    	}
    	case 0x15:
    	{
    	
    	    break;	
    	}
    	case 0x16:
    	{
    	
    		break;
    	}  
    	case 0x17:
    	{
    	
    	    break;	
    	}
    	case 0x18:
    	{
    	
    		break;
    	}
    	case 0x19:
    	{
    	
    	    break;	
    	}
    	case 0x20:
    	{
    	
    		break;
    	}
    	case 0x21:
    	{
    	
    	    break;	
    	}
    	case 0x22:
    	{
    	
    		break;
    	}
    	case 0x23:
    	{
    	
    	    break;	
    	}
    	case 0x24:
    	{
    	
    		break;
    	}    
    	case 0x25:
    	{
    	
    		break;
    	}      		
    	  	
    	default:
    	break;
    }
    
}
#endif


/*******************************************************  Dcm.c End  ******************************************************/













