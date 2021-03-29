/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   App_Dcm.c  
*
* @brief  Application Interface for Diagnostic Communication Management
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/20    CODER1     N/A           Original
*     
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "App_Dcm.h"
#include "L3_GPIO.h"
#include "obc_app.h"
//#include "hFbl_Serv.h"

/*****************************************************************************************                           
 *  Global Varibales Definition              
 *****************************************************************************************/
uint8  u8EnCanRxAndTx;
uint8  u8MsgType;
uint32 u32FreRunCntrForRand;/*A rand data*/

/*****************************************************************************************                           
 *  Internal Varibales Definition              
 *****************************************************************************************/
static uint8  gIgnStatus;
static uint8  gOperationPermit;

#if(DCM_SERVICE_27_ENABLED==STD_ON)

static  uint8 seedForSend[4];

#endif

/*- initiallize the EEPEOM-scope of DID: according to customer,the initial values are 0xFF or 0 or others -*/

#if 1
/*reserved*/
//static uint8 DID_F187[DID_F187_LEN] = { 0u };
const uint8 DID_F187[DID_F187_LEN] = { 0u,0u,83u,53u,48u,69u,86u,67u,45u,50u,49u,48u,55u,48u,49u,48u};//S50EVC-2107010
//static uint8 DID_F18A[DID_F18A_LEN] = { 0u};//31Q069
static uint8 DID_F18A[DID_F18A_LEN] = { 0u,0,0,0,51,49,81,48,54,57 };//31Q069

static uint8 DID_F18B[DID_F18B_LEN] = { 0u };

static uint8 DID_F18C[DID_F18C_LEN] = { 0u };

static uint8 DID_F190[DID_F190_LEN] = { 0u };
//static uint8 DID_F193[DID_F193_LEN] = { 0u };//S50EVC_01_V01.01
//static uint8 DID_F195[DID_F195_LEN] = { 0u };//S50EVC_01_P01.01
static uint8 DID_F193[DID_F193_LEN] = { 0u,0u,83u,53u,48u,69u,86u,67u,95u,48u,49u,95u,86u,48u,49u,46u,48u,49u };//S50EVC_01_V01.01
static uint8 DID_F195[DID_F195_LEN] = { 0u,0u,0u,0u,83u,53u,48u,69u,86u,67u,95u,48u,49u,95u,80u,48u,49u,46u,48u,49u };//S50EVC_01_P01.01

static uint8 DID_0100[DID_0100_LEN] = { 0u };

static uint8 DID_F010[DID_F010_LEN] = { 0u };
#if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
//static uint8 DID_F197[DID_F197_LEN] = { 0u};//OBC
static uint8 DID_F197[DID_F197_LEN] = { 0u,0u,0u,0u,0u,0u,0u,79u,66u,67u };//OBC
static uint8 DID_1C00[DID_1C00_LEN] = { 0u };
static uint8 DID_1C01[DID_1C01_LEN] = { 0u };
static uint8 DID_1C02[DID_1C02_LEN] = { 0u };
static uint8 DID_1C03[DID_1C03_LEN] = { 0u };
static uint8 DID_1C04[DID_1C04_LEN] = { 0u };
static uint8 DID_1C05[DID_1C05_LEN] = { 0u };

#endif
#endif


#if 0
/* e.g: 0x0107 is related to both IAC and EGR */ /* used  For 0x2F */

static uint8 IAC[7]= { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 }; 

static uint8 EGR[7]= { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6 }; 

#endif


/*****************************************************************************************                           
 *                               Function Implementation              
 *****************************************************************************************/
 
/******************************************************************************
 * Name         : dDiag_vDcmAppInit()
 * Called by    : Dcm_Init
 * Preconditions: N/A
 * Parameters   :  
 * Return code  : void
 * Description  : init the global variables used in Dcm_App module
 *
 ******************************************************************************/

void dDiag_vDcmAppInit(void)
{   
	
	gIgnStatus = IGN_ON;
	gOperationPermit = DISABLE_OPERATION;
	u8EnCanRxAndTx = 0u;
    u8MsgType = 0x3u;
    #if(DCM_SERVICE_27_ENABLED==STD_ON)
    seedForSend[0] = 0;
    seedForSend[1] = 0;
    seedForSend[2] = 0;
    seedForSend[3] = 0;    
    #endif
    
    
}

/******************************************************************************
 * Name         : SetIgnStatus
 * Called by    : Dcm
 * Preconditions: N/A
 * Parameters   : uint8 aIgnStatus
 * Return code  : void
 * Description  : set the Ign status.
 *
 ******************************************************************************/

void SetIgnStatus(uint8 aIgnStatus)
{   
    gIgnStatus = aIgnStatus;
}

/******************************************************************************
 * Name         : SetDiagCondition
 * Called by    : Dcm
 * Preconditions: N/A
 * Parameters   : uint8 u8DiagCondition
 * Return code  : void
 * Description  : provide limit operation condition to some external diag-request
 *                such as 11\28\2E service..etc.
 *
 ******************************************************************************/

void SetDiagCondition(uint8 u8DiagCondition)
{
	gOperationPermit = u8DiagCondition;
}



#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL==STD_ON)

/******************************************************************************
 * Name         :App_DiagnosticAtive
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :void
 * Return code  : 0 - Positive response
 *                1 - Condition not correct
 * Description  :Post processing after transition into default session.
 *
 ******************************************************************************/

Std_ReturnType App_DiagnosticActive(void)
{
    uint8 result;
    if (gIgnStatus == 0x01u) 
    {
        result = E_OK;
    } 
    else 
    {
        result = E_NOT_OK;
    }

    return (result);
}

#endif



#if(DCM_COSTOMIZED_SERVCIE_SUPPORTED==STD_ON)

/******************************************************************************
 * Name         :App_CustomizedServcie
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :N/A
 * Return code  :N/A
 * Description  :Customized service need application to do its work.
 *
 ******************************************************************************/
void App_CustomizedServcie(Dcm_MsgContextType* pMsgContext)
{
	(Dcm_MsgContextType*)pMsgContext;
	/*reserved,self-defined function*/
}

#endif


#if(DCM_INTERNALTEST_SERVCIE_SUPPORTED==STD_ON)

/******************************************************************************
 * Name         :App_InternalTestServcie
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :subpara
 * Return code  :N/A
 * Description  :Internal Service for Test and debug.
 *
 ******************************************************************************/
void App_InternalTestServcie(uint8 subpara)
{    
    /*reserved,self-defined function*/
    (uint8)subpara; 

}

#endif


#if(DCM_SERVICE_10_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_DefaultSession
 * Called by    :  session control function
 * Preconditions:  None
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  callback of default session control function
 ******************************************************************************/
 
void App_DefaultSession(Dcm_MsgContextType* pMsgContext)
{  
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
 * Name         :  App_ProgramSession
 * Called by    :  session control function
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  callback of program session control function
 ******************************************************************************/
 
void  App_ProgramSession(Dcm_MsgContextType* pMsgContext)
{    
    DsdInternal_ProcessingDone(pMsgContext);
}
                


 /******************************************************************************
 * Name         :  App_ExtendedSession
 * Called by    :  session control function
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  callback of extend session control function
 ******************************************************************************/
void App_ExtendedSession(Dcm_MsgContextType* pMsgContext)
{
	if (gOperationPermit == DISABLE_OPERATION) 
	{
		DsdInternal_SetNegResponse(pMsgContext,DCM_E_CONDITIONSNOTCORRECT);
	} 
	else 
	{
	}

	DsdInternal_ProcessingDone(pMsgContext);

}

/******************************************************************************
 * Name         :App_DefaultSessionPost
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :Std_ReturnType Result
 * Return code  :N/A
 * Description  :Jump to default session once positive response is transmitted.
 *               Otherwise, do not change session type.
 ******************************************************************************/

void App_DefaultSessionPost(Std_ReturnType Result)
{
    uint8 i=0;
    if(Result==E_OK)
    {
        Set_SesCtrl(DCM_DEFAULT_SESSION);
      
        for(i=0;i<KIND_OF_SECURITY_LEVEL;i++)
        {
            gSecLevelType[i]=DCM_SEC_LEV_LOCK;  /*re enterinto lock satate, no security access request,because 27 is not supported in default session.*/
        }
        
        u8EnCanRxAndTx = 0; /*enable RX and TX; If in extendedsession the communcation 
                              has been disabled and when switchinto defaultsession,the communcation will be auto-enabled. */ 
        u8MsgType = 0x03;   /*default enable app msg and Network msg*/
                             
        gDTCSwitch=1;       /*And also the 0x85 service, Auto open the DTC management.*/
        
        /*gCallCycle=0;If 0x2A is STD_ON,the calling-periodic which 0x2A service configed will be disabled here,beacuse 2A not support defaultsession. */
    }
    else
    {

    }
 
}

/******************************************************************************
 * Name         :App_ProgramSessionPost
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :Dcm_MsgContextType* pMsgContext
 * Return code  :N/A
 * Description  :Reset once positive response is transmitted.
 *               Otherwise, do not reset.
 ******************************************************************************/

void App_ProgramSessionPost(Std_ReturnType Result)
{
    (void)Result;
    #if(DCM_SERVICE_27_ENABLED==STD_ON)
    gSecLevelType[0]=0;
    #endif

}

/******************************************************************************
 * Name         :App_ExtendedSessionPost
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :Dcm_MsgContextType* pMsgContext
 * Return code  :N/A
 * Description  :Jump to extended session once positive response is transmitted.
 *               Otherwise, do not change session type.
 ******************************************************************************/

void App_ExtendedSessionPost(Std_ReturnType Result)
{
  uint8 i= 0;
  if (Result==E_OK) 
  {
    Set_SesCtrl(DCM_EXTENDED_DIAGNOSTIC_SESSION);
    for (i=0;i<KIND_OF_SECURITY_LEVEL;i++) 
    {
       gSecLevelType[i]= DCM_SEC_LEV_LOCK;
    }
  } 
  else 
  {
  }
  

}

#endif


#if(DCM_SERVICE_11_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_HardReset
 * Called by    :  DsdInternal_10_11_28_85
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  excute the reset operation
 ******************************************************************************/
void App_HardReset(Dcm_MsgContextType* pMsgContext)
{
  uint16 i = 0xFFFU;
	
  if (gOperationPermit == DISABLE_OPERATION) 
  {
     DsdInternal_SetNegResponse(pMsgContext,DCM_E_CONDITIONSNOTCORRECT);
     DsdInternal_ProcessingDone(pMsgContext);
  } 
  else 
  { 
     DsdInternal_ProcessingDone(pMsgContext);
     pMsgContext->resDataLen= 2;

     if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)
     {
	     Dcm_ResetToDefaultSession();         

	 #if(DCM_SERVICE_27_ENABLED==STD_ON)

	     Set_SecLevel(DCM_SEC_LEV_LOCK);
	     gSecurityDelayTimeOnBootFlag= 1;

	 #endif
	 

		 //hFbl_HardReset_Service(); //ych remove for not hardReset enable ,use software reset replease hardReset
		 APPL_softwareRest(); 	     	

     }
     else
     {
     	
     }

  }
  
}


#endif
/******************************************************************************
 * Name         :App_HardResetPost
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :Std_ReturnType Result
 * Return code  :N/A
 * Description  :Hard reset once positive response is transmitted. Otherwise, do
 *               not reset.
 ******************************************************************************/
void App_HardResetPost(Std_ReturnType Result)
{
   (Std_ReturnType)Result;
}


#if(DCM_SERVICE_11_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_SoftReset
 * Called by    :  DsdInternal_10_11_28_85
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  excute the reset operation
 ******************************************************************************/
void App_SoftReset(Dcm_MsgContextType* pMsgContext)
{
  uint16 i = 0xFFFU;
	
  if (gOperationPermit == DISABLE_OPERATION) 
  {
     DsdInternal_SetNegResponse(pMsgContext,DCM_E_CONDITIONSNOTCORRECT);
     DsdInternal_ProcessingDone(pMsgContext);
  } 
  else 
  { 
     DsdInternal_ProcessingDone(pMsgContext);
     pMsgContext->resDataLen= 2;

     if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)
     {
	     Dcm_ResetToDefaultSession();         

	 #if(DCM_SERVICE_27_ENABLED==STD_ON)

	     Set_SecLevel(DCM_SEC_LEV_LOCK);
	     gSecurityDelayTimeOnBootFlag= 1;

	 #endif
	 

		 APPL_softwareRest();  	     	

     }
     else
     {
     	
     }

  }
  
}


#endif
/******************************************************************************
 * Name         :App_SoftResetPost
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :Std_ReturnType Result
 * Return code  :N/A
 * Description  :Hard reset once positive response is transmitted. Otherwise, do
 *               not reset.
 ******************************************************************************/
void App_SoftResetPost(Std_ReturnType Result)
{
   (Std_ReturnType)Result;
}





#if(DCM_SERVICE_14_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_ClearDiagnosticInformation
 * Called by    :  DspInternal_Uds_ClearDiagnosticInformation
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  : callback of 14 service,used to clear the DTC info in ECU;
 ******************************************************************************/

uint32 gClrGroupOfDTC = 0xFFFFFFFF;
uint8  App_ClearDiagnosticInformation(Dcm_MsgContextType* pMsgContext)
{
    uint8  result = 0;
    uint32 DtcGroupRequest;

    DtcGroupRequest=Make24Bit(pMsgContext->reqData[1],pMsgContext->reqData[2],pMsgContext->reqData[3]);
    
    //if((DtcGroupRequest == 0xD00000)||(DtcGroupRequest == 0xFFFFFF)) /* 20130326 0xD00000 means OEM defined,so it can be changed according to OEM */
    if((DtcGroupRequest == DTCGroup)||(DtcGroupRequest == ALLGroup))
    {
        gClrGroupOfDTC = DtcGroupRequest<<8;
        
        Dtc_Status_14Service_Hook(gClrGroupOfDTC);  
        
        pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40;
        pMsgContext->resDataLen=1;       

        result = DCM_NUM_POSITIVERESPONSE;
        
    }
    else
    {
        result = DCM_NUM_REQUESTOUTOFRANGE;
    }
    
    return result;
}

#endif

#if(DCM_SERVICE_19_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_ReportNumberOfDTCByStatusMask
 * Called by    :  
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  : report the count of DTCs by StatusMask.
 ******************************************************************************/
uint8 App_ReportNumberOfDTCByStatusMask(Dcm_MsgContextType* pMsgContext)
{
  uint8 i;
  uint8 result= 0u;
  uint16 DtcNumCounter= 0u;
  uint8 ConcernedDtcBits = 0u;
    
  ConcernedDtcBits = pMsgContext->reqData[2];
  
  if ((ConcernedDtcBits & DTCStatusAvailabilityMask)!=0) 
  {
      for (i=0;i<DTC_NUMBER_SIZE;i++) 
      {
          if ((DTC_STATUS_BYTE(i) & ConcernedDtcBits & DTCStatusAvailabilityMask) != 0) 
          {
              DtcNumCounter++;
          } 
          else 
          {    
          }
      }

      pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40u;
      pMsgContext->resData[1]=pMsgContext->reqData[1];
      
      pMsgContext->resData[2]= DTCStatusAvailabilityMask;
      //pMsgContext->resData[3]= 0x00u;
      pMsgContext->resData[3]= DTCFormatIdentifier;
      
      pMsgContext->resData[4]= (uint8)(DtcNumCounter>>8u);
      pMsgContext->resData[5]= (uint8)(DtcNumCounter&0xFF);
      pMsgContext->resDataLen= 6u;
      
      result = DCM_NUM_POSITIVERESPONSE;
  } 
  else 
  {
      result = DCM_NUM_REQUESTOUTOFRANGE;
  }
  
  return result;

}

/******************************************************************************
 * Name         :App_ReportDTCByStatusMask
 * Called by    :pMsgContext
 * Preconditions:none
 * Parameters   :pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :report all DTC codes by status Mask
 ******************************************************************************/

uint8 App_ReportDTCByStatusMask(Dcm_MsgContextType* pMsgContext)
{
  uint8 i;
  uint8 j;
  uint8 result = 0; 
  uint16 DtcNumCounter= 0;
  uint8 ConcernedDtcBits = 0;
  ConcernedDtcBits = pMsgContext->reqData[2];
  
  if (0 != (ConcernedDtcBits & DTCStatusAvailabilityMask)) 
  {
      for (i=0,j=0;i<DTC_NUMBER_SIZE;i++) 
      {
          if (0 != (DTC_STATUS_BYTE(i) & ConcernedDtcBits & DTCStatusAvailabilityMask)) 
          {
              pMsgContext->resData[3+j*4] = (uint8)(DTC_InitValue[i]>>24);
              pMsgContext->resData[4+j*4] = (uint8)(DTC_InitValue[i]>>16);
              pMsgContext->resData[5+j*4] = (uint8)(DTC_InitValue[i]>>8);
              pMsgContext->resData[6+j*4] = (uint8)DTC_STATUS_BYTE(i);
              j++;
              DtcNumCounter++;
          } 
          else 
          {
          }
      }

      pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40u;
      pMsgContext->resData[1]=pMsgContext->reqData[1];
      pMsgContext->resData[2]= DTCStatusAvailabilityMask;
      pMsgContext->resDataLen= 3 + DtcNumCounter*4;
      
      result = DCM_NUM_POSITIVERESPONSE;
      
  } 
  else 
  {
      result = DCM_NUM_REQUESTOUTOFRANGE;
  }

  return result;
}      

/******************************************************************************
 * Name         :  App_ReportSupportedDTC
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  
 * Description  :  report all the supported DTC codes.
 ******************************************************************************/
uint8 App_ReportSupportedDTC(Dcm_MsgContextType* pMsgContext)
{
  uint8 result = 0;
  uint32 i;
  
  pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40;
  pMsgContext->resData[1]=pMsgContext->reqData[1];
  pMsgContext->resData[2]= DTCStatusAvailabilityMask;
  
  for (i=0;i<DTC_NUMBER_SIZE;i++) 
  {
      pMsgContext->resData[3+i*4] = (uint8)(DTC_InitValue[i]>>24);
      pMsgContext->resData[4+i*4] = (uint8)(DTC_InitValue[i]>>16);
      pMsgContext->resData[5+i*4] = (uint8)(DTC_InitValue[i]>>8);
      pMsgContext->resData[6+i*4] = DTC_STATUS_BYTE(i);
  }

  pMsgContext->resDataLen= 3 + DTC_NUMBER_SIZE*4;

  
  return result;
} 


/******************************************************************************
 * Name         :App_ReportDTCSnapshotIdentification
 * Called by    :
 * Preconditions:
 * Parameters   :
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :report the snapsotidentification of one 
 ******************************************************************************/
uint8 App_ReportDTCSnapshotIdentification(Dcm_MsgContextType* pMsgContext)/* 03 */ 
{
    uint8  result = 0u;
	uint8  FFDNumber;
	uint8  DataLen = 0u;
	uint16 i;
	uint16 j;     
	
	pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40;  
	pMsgContext->resData[1]=pMsgContext->reqData[1];        

	for (i=0,j=0;i<DTC_NUMBER_SIZE;i++) 
	{
		 if(DTC_NO_SNAPSHOT != gDtc_Attribute_Table[i].WithFreezeFrameFlag)
		 {
		    pMsgContext->resData[2+j*4] = (uint8)(DTC_InitValue[i]>>24);
		    pMsgContext->resData[3+j*4] = (uint8)(DTC_InitValue[i]>>16);
		    pMsgContext->resData[4+j*4] = (uint8)(DTC_InitValue[i]>>8);  
		          	
			FFDNumber = gDtc_Attribute_Table[i].FreezeFrameNumber;	        
		    pMsgContext->resData[5+j*4] = FFDNumber;
		    
		  	j++;
		  	
		  	DataLen++;
		  	
		 }
		 else
		 {
		 	;
		 }
	}
	
	pMsgContext->resDataLen= 2u + DataLen*4u; 
	
	return result;
}

/******************************************************************************
 * Name         :App_ReportDTCSnapshotRecordByDTCNumber
 * Called by    :
 * Preconditions:
 * Parameters   :
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :report dtc snopshot context by Dtcnumber
 ******************************************************************************/
uint8 App_ReportDTCSnapshotRecordByDTCNumber(Dcm_MsgContextType* pMsgContext)/* 04 */ 
{
	uint16 i;
	uint16 j;  
	uint8  result = 0;
	
  	uint8  FFDNumber;
	uint32 DtcCodeThreeBytes = 0x00000000u;
	
	uint8  DtcCodeNotSup = 1u;
	uint8  RecordNumberNotSup = 0u;
	
	uint16 didcode;
    uint8  didsize;
    uint8  didIndex;
    uint8  dataoffset = 0u;
	
	pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40u;  
	pMsgContext->resData[1]=pMsgContext->reqData[1];        
	pMsgContext->resData[2]=pMsgContext->reqData[2];
	pMsgContext->resData[3]=pMsgContext->reqData[3];
	pMsgContext->resData[4]=pMsgContext->reqData[4];

    DtcCodeThreeBytes |= ((uint32)pMsgContext->reqData[2]<<24u); 
    DtcCodeThreeBytes |= ((uint32)pMsgContext->reqData[3]<<16u);
    DtcCodeThreeBytes |= ((uint32)pMsgContext->reqData[4]<<8u);
    
	for (i=0u;i<DTC_NUMBER_SIZE;i++) 
	{
	     if((DtcCodeThreeBytes & 0xFFFFFF00u) == (DTC_InitValue[i] & 0xFFFFFF00u))
	     {
	         DtcCodeNotSup = 0u;
	         
			 if(DTC_NO_SNAPSHOT != gDtc_Attribute_Table[i].WithFreezeFrameFlag)
			 {	 	          	
				FFDNumber = gDtc_Attribute_Table[i].FreezeFrameNumber;/*one DTC only support one record number*/
				
				if((0xFFu == pMsgContext->reqData[5])||(FFDNumber == pMsgContext->reqData[5]))
				{					   
				    pMsgContext->resData[5] = DTC_STATUS_BYTE(i);
					pMsgContext->resData[6]=FFDNumber;
					
				    if(0u != DTC_EXT_NUM_FAILED_CYCLE_DATA(i))/*judge if there is freezeframe*/
				    {						
						pMsgContext->resData[7]=Dtc_FFRecCfgTable[FFDNumber-1u].NumOfDid;
						
					    for(j=0u; j< Dtc_FFRecCfgTable[FFDNumber-1u].NumOfDid;j++)
						{
						    didIndex = Dtc_FFRecCfgTable[FFDNumber-1u].DidRefTable[j];
							didcode = Dtc_DidCfgTable[didIndex].Did;
							didsize = Dtc_DidCfgTable[didIndex].DataSize;
							
							pMsgContext->resData[j*2u + (8+dataoffset)]=(uint8)(didcode>>8u);
							pMsgContext->resData[j*2u + (9+dataoffset)]=(uint8)(didcode&0xFFu);
							
  							Dtc_DataCopy(&(pMsgContext->resData[j*2u + (10+dataoffset)]),&DTC_SNAPSHOT_DATA_BYTE(i)[dataoffset],didsize);
        
							dataoffset += didsize;	
						}
						
						pMsgContext->resDataLen= (10u + 2*Dtc_FFRecCfgTable[FFDNumber-1u].NumOfDid) + dataoffset;  				    	
				    }
				    else/*give positive response but no freezeframe data*/
				    {
				    	pMsgContext->resDataLen= 7u;
				    }
					
				}
				else
				{
					RecordNumberNotSup = 1u;
				}
				
			 }
			 else
			 {
			 	DtcCodeNotSup = 1u; 
			 }	     	
	     }
	     else
	     {
	     	;
	     }
	     
	}
	
	if((RecordNumberNotSup == 1u) || (DtcCodeNotSup == 1u))
	{
        result = DCM_NUM_REQUESTOUTOFRANGE;
	}
	else
	{
		result = DCM_NUM_POSITIVERESPONSE;
	}
	
    return result;
}


/*reserved*/
uint8 App_ReportDTCSnapshotRecordByRecordNumber(Dcm_MsgContextType* pMsgContext)/* 05 */ 
{
    (void)pMsgContext;

    return 0;
}

/******************************************************************************
 * Name         :App_ReportDTCExtendedDataRecordByDTCNumber
 * Called by    :
 * Preconditions:none
 * Parameters   :pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :report the DTC extend data.
 ******************************************************************************/
uint8 App_ReportDTCExtendedDataRecordByDTCNumber(Dcm_MsgContextType* pMsgContext)/* 06 */ 
{
    uint8 i = 0;
    uint8 result = 0;
  
 	uint32 DtcCodeThreeBytes = 0x00000000u;
	
	uint8  DtcCodeNotSup = 1u;
	uint8  RecordNumberNotSup = 0u; 
  
  	pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40u;  
	pMsgContext->resData[1]=pMsgContext->reqData[1];  
	      
	pMsgContext->resData[2]=pMsgContext->reqData[2];
	pMsgContext->resData[3]=pMsgContext->reqData[3];
	pMsgContext->resData[4]=pMsgContext->reqData[4];

    DtcCodeThreeBytes |= ((uint32)pMsgContext->reqData[2]<<24u); 
    DtcCodeThreeBytes |= ((uint32)pMsgContext->reqData[3]<<16u);
    DtcCodeThreeBytes |= ((uint32)pMsgContext->reqData[4]<<8u);
    
	for (i=0u;i<DTC_NUMBER_SIZE;i++) 
	{
	     if((DtcCodeThreeBytes & 0xFFFFFF00u) == (DTC_InitValue[i] & 0xFFFFFF00u))
	     {
	         DtcCodeNotSup = 0u;
	         
			 if((0xFFu == pMsgContext->reqData[5])||(0x1u == pMsgContext->reqData[5]))/*only support 01 number or FF number*/
		 	 {					   
			     pMsgContext->resData[5] = DTC_STATUS_BYTE(i);
			 	 pMsgContext->resData[6]=0x1u;
				
				 Dtc_DataCopy(&(pMsgContext->resData[7]),DTC_EXT_DATA_BYTE(i),DTC_EXD_DATA_TYPE_SIZE);

			     pMsgContext->resDataLen= (7u + DTC_EXD_DATA_TYPE_SIZE);  				    	
			 }
			 else/*give positive response but no freezeframe data*/
			 {
			     RecordNumberNotSup = 1u;
			 }
	     }
	     else
	     {
	     	;
	     }
	}
  
  	if((RecordNumberNotSup == 1u) || (DtcCodeNotSup == 1u))
	{
        result = DCM_NUM_REQUESTOUTOFRANGE;
	}
	else
	{
		result = DCM_NUM_POSITIVERESPONSE;
	}
	
    return result;
}

#endif


#if(DCM_SERVICE_22_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_ReadF187
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF187(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x87;
	for (i=0;i<DID_F187_LEN;i++) 
	{    
		pMsgContext->resData[2+i]= DID_F187[i]; 
	}
}

/******************************************************************************
 * Name         :  App_ReadF18A
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF18A(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x8A;
	for (i=0;i<DID_F18A_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F18A[i];
	}
}

/******************************************************************************
 * Name         :  App_ReadF18B
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF18B(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x8B;
	for (i=0;i<DID_F18B_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F18B[i];
	}

}

/******************************************************************************
 * Name         :  App_ReadF18C
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF18C(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x8C;
	for (i=0;i<DID_F18C_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F18C[i];
	}

}

/******************************************************************************
 * Name         :  App_ReadF190
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF190(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x90;
	for (i=0;i<DID_F190_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F190[i];
	}

}

/******************************************************************************
 * Name         :  App_ReadF193
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF193(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x93;
	for (i=0;i<DID_F193_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F193[i];
	}

}

/******************************************************************************
 * Name         :  App_ReadF195
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF195(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x95;

	for (i=0;i<DID_F195_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F195[i];
	}

}

/******************************************************************************
 * Name         :  App_Read0100
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_Read0100(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0x01;
	pMsgContext->resData[1]= 0x00;

	for (i=0;i<DID_0100_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_0100[i];
	}

}

/******************************************************************************
 * Name         :  App_ReadF010
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF010(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF0;
	pMsgContext->resData[1]= 0x10;

	for (i=0;i<DID_F010_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F010[i];
	}

}



/******************************************************************************
 * Name         :  App_ReadF197
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_ReadF197(Dcm_MsgContextType* pMsgContext)
{
	uint8 i;
	pMsgContext->resData[0]= 0xF1;
	pMsgContext->resData[1]= 0x97;

	for (i=0;i<DID_F197_LEN;i++) 
	{
		pMsgContext->resData[2+i]= DID_F197[i];
	}

}





/******************************************************************************
 * Name         :  App_Read1C00
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_Read1C00(Dcm_MsgContextType* pMsgContext)
{
	uint8 i,tempI;
	pMsgContext->resData[0]= 0x1C;
	pMsgContext->resData[1]= 0x00;

	for (i=0;i<DID_1C00_LEN;i++) 
	{
		//pMsgContext->resData[2+i]= DID_1C00[i];
		//pMsgContext->resData[2+i]= (uint8)(OBC_OUTVoltage>>(8*i));
		tempI = (DID_1C00_LEN-1-i);
		pMsgContext->resData[2+tempI]= (uint8)(OBC_OUTVoltage>>(8*i));
		
	}

}


/******************************************************************************
 * Name         :  App_Read1C01
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_Read1C01(Dcm_MsgContextType* pMsgContext)
{
	uint8 i,tempI;
	pMsgContext->resData[0]= 0x1C;
	pMsgContext->resData[1]= 0x01;

	for (i=0;i<DID_1C01_LEN;i++) 
	{
		//pMsgContext->resData[2+i]= DID_1C01[i];
		//pMsgContext->resData[2+i]= (uint8)(OBC_OUTCurrent>>(8*i));
		tempI = (DID_1C01_LEN-1-i);
		pMsgContext->resData[2+tempI]= (uint8)(OBC_OUTCurrent>>(8*i));
	}

}


/******************************************************************************
 * Name         :  App_Read1C02
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_Read1C02(Dcm_MsgContextType* pMsgContext)
{
	uint8 i,tempI;
	pMsgContext->resData[0]= 0x1C;
	pMsgContext->resData[1]= 0x02;

	for (i=0;i<DID_1C02_LEN;i++) 
	{
		//pMsgContext->resData[2+i]= DID_1C02[i];
		//pMsgContext->resData[2+i]= (uint8)(OBC_INPUTVoltage>>(8*i));
		tempI = (DID_1C02_LEN-1-i);
		pMsgContext->resData[2+tempI]= (uint8)(OBC_INPUTVoltage>>(8*i));
	}

}


/******************************************************************************
 * Name         :  App_Read1C03
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_Read1C03(Dcm_MsgContextType* pMsgContext)
{
	uint8 i,tempI;
	pMsgContext->resData[0]= 0x1C;
	pMsgContext->resData[1]= 0x04;

	for (i=0;i<DID_1C03_LEN;i++) 
	{
	//	pMsgContext->resData[2+i]= DID_1C03[i];
		//pMsgContext->resData[2+i]= (uint8)(OBC_INPUTCurrent>>(8*i));
		tempI = (DID_1C03_LEN-1-i);
		pMsgContext->resData[2+tempI]= (uint8)(OBC_INPUTCurrent>>(8*i));
	}

}



/******************************************************************************
 * Name         :  App_Read1C04
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_Read1C04(Dcm_MsgContextType* pMsgContext)
{
	uint8 i,tempI;
	pMsgContext->resData[0]= 0x1C;
	pMsgContext->resData[1]= 0x04;

	for (i=0;i<DID_1C04_LEN;i++) 
	{
	//	pMsgContext->resData[2+i]= DID_1C04[i];
		//pMsgContext->resData[2+i]= (uint8)(OBC_CPDUTY>>(8*i));
		tempI = (DID_1C04_LEN-1-i);
		pMsgContext->resData[2+tempI]= (uint8)(OBC_CPDUTY>>(8*i));
	}

}



/******************************************************************************
 * Name         :  App_Read1C05
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  read DTD content from ECU
 *
 ******************************************************************************/
void App_Read1C05(Dcm_MsgContextType* pMsgContext)
{
	uint8 i,tempI;
	pMsgContext->resData[0]= 0x1C;
	pMsgContext->resData[1]= 0x05;

	for (i=0;i<DID_1C05_LEN;i++) 
	{
		//pMsgContext->resData[2+i]= DID_1C05[i];
		//pMsgContext->resData[2+i]= (uint8)(OBC_OBCTemp>>(8*i));
		tempI = (DID_1C05_LEN-1-i);
		pMsgContext->resData[2+tempI]= (uint8)(OBC_OBCTemp>>(8*i));
	}

}
#endif



#if(DCM_SERVICE_27_ENABLED==STD_ON)

#define random(x)   (rand()%x)

/******************************************************************************
 * Name         :  seedToKey
 * Called by    :
 * Preconditions:  none
 * Parameters   :  seed: input, rand data
                   key:  output,generate from seed;
 * Return code  :  none
 * Description  :  Generate the key by seed;
 *
 ******************************************************************************/
 
static void seedToKey(uint8 *seed, uint8 *key)
{
	uint8 i,j;
	uint8 lKey;
	uint8 seedToKeyMask[SECURITY_SEED_SIZE] = { SECURITY_MASK_CODE_FIRST, SECURITY_MASK_CODE_SECOND }; 
	for (i = 0u; i < SECURITY_SEED_SIZE; i++) 
	{
		lKey = 0u;
		for (j = 0u;j < SECURITY_SEED_SIZE;j++) 
		{
			lKey += seedToKeyMask[i] ^ seed[j];
		}

		key[i] = seed[i] ^ lKey;
	}
}

static unsigned long  seedToKeyForS50(unsigned int num_rounds , unsigned long seed)
{
	unsigned long  seedTemp1 = seed,seedTemp2=~seed, i;
	unsigned long  sum=0,delta=0x0ab16003;
	unsigned long  k[4],key;
	k[0] = 0x4c495551;
	k[1] = 0x49534545;
	k[2] = 0x444b4559;
	k[3] = 0x414c474f;
	for(i=0;i<num_rounds;i++)
	{
		seedTemp1 += (((seedTemp2<<4)^(seedTemp2>>5))+seedTemp2)^(sum+k[sum&3]);
		sum+= delta;
		seedTemp2+=(((seedTemp1<<4)^(seedTemp1>>5))+seedTemp1)^(sum+k[(sum>>11)&3]);
	}
	key=seedTemp1;
	return key;
	
}
/******************************************************************************
 * Name         :  App_GetSeed_L1
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  get the rand seed;
 *
 ******************************************************************************/

void App_GetSeed_L1(Dcm_MsgContextType* pMsgContext)
{
	uint8 i = 0;

	srand(u32FreRunCntrForRand);
	pMsgContext->resData[0] = pMsgContext->reqData[0]+0x40;
	pMsgContext->resData[1] = pMsgContext->reqData[1];

	for (i=0;i<SECURITY_SEED_SIZE;i++) 
	{
		seedForSend[i] = (uint8)random(256);
		pMsgContext->resData[2+i] = seedForSend[i];
	}

	pMsgContext->resDataLen= gDcmDspSecurityRow[0].DcmDspSecuritySeedSize+2;
  
}
/******************************************************************************
 * Name         :  App_CompareKey_L1
 * Called by    :  
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  result which indicate if 27 service access successful
                   0: success; 1:fail;
 * Description  :  compare if the ECU key and the Tester Key are equal.
 *
 ******************************************************************************/
uint8 App_CompareKey_L1(Dcm_MsgContextType* pMsgContext)
{
    uint8 result = 0;

    uint8 calAccessKey[2] = { 0 };
	unsigned long calAccessKeyS50,seed,TersterKey;
	/* 
    seedToKey(seedForSend,calAccessKey);
    if ((calAccessKey[0] == pMsgContext->reqData[2]) && (calAccessKey[1] == pMsgContext->reqData[3]))
    {
       result = 0;
    } 
    else 
    {
       result = 1;
    }
    */
    //seed = seedForSend[0]<<24+seedForSend[1]<<16+seedForSend[2]<<8+seedForSend[3];
    seed = ((((uint32)seedForSend[3])& 0x000000ff) 
                      + (((uint32)(seedForSend[2]) << 8) & 0x0000ff00)
                      + (((uint32)(seedForSend[1]) << 16) & 0x00ff0000)
                      + (((uint32)(seedForSend[0]) << 24) & 0xff000000));  
    TersterKey = ((((uint32)pMsgContext->reqData[5])& 0x000000ff) 
                      + (((uint32)(pMsgContext->reqData[4]) << 8) & 0x0000ff00)
                      + (((uint32)(pMsgContext->reqData[3]) << 16) & 0x00ff0000)
                      + (((uint32)(pMsgContext->reqData[2]) << 24) & 0xff000000));  
    calAccessKeyS50 = seedToKeyForS50(2,seed);
    if(calAccessKeyS50 == TersterKey)
    {
    	result = 0;
    }
    else
    {
    	result = 1;
    }
    return result;
}

#endif



#if(DCM_SERVICE_28_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_EnableRxAndTx
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  callback of 28 service,used to enable the can comm
 *
 ******************************************************************************/

void App_EnableRxAndTx(Dcm_MsgContextType* pMsgContext)
{  
	DsdInternal_ProcessingDone(pMsgContext);  
	if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)
	{
	  /* following global variables will be used in application */
	  
		u8EnCanRxAndTx = pMsgContext->reqData[1]; /* =0,means enable RX and TX */
	    u8MsgType = pMsgContext->reqData[2];/* =1,means Normal comm;=2,means Networkmanagement; =3,means Normal and Networkmanagement. */    	
	}
	else
	{    

	}
}

/******************************************************************************
 * Name         :  App_DisableRxAndTx
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  callback of 28 service,used to stop can comm
 *
 ******************************************************************************/
void App_DisableRxAndTx(Dcm_MsgContextType* pMsgContext)
{  
	DsdInternal_ProcessingDone(pMsgContext);  
	if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)
	{    
	    u8EnCanRxAndTx =  pMsgContext->reqData[1];  /* =3,means disable RX and TX */
	    u8MsgType = pMsgContext->reqData[2];  /* =1,means Normal comm;=2,means Networkmanagement; =3,means Normal and Networkmanagement. */

	}
	else
	{

	}
}

#endif

#if(DCM_SERVICE_2E_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_WriteF187
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/
uint8 App_WriteF187(Dcm_MsgContextType* pMsgContext)
{
    uint8 result= DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;    
    } 
    else
    {
        pMsgContext->resData[0]= 0xF1;
        pMsgContext->resData[1]= 0x87;
        
       /* if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F187_ADDR,DID_F187_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT;
        }*/
    }
    
    return result;
}
/******************************************************************************
 * Name         :  App_WriteF18A
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_WriteF18A(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;    
    } 
    else
    {
        pMsgContext->resData[0]= 0xF1;
        pMsgContext->resData[1]= 0x8a;
        
       /* if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F18A_ADDR,DID_F18A_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT;
        }*/
    }
    
    return result;
    
}

/******************************************************************************
 * Name         :  App_WriteF18B
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_WriteF18B(Dcm_MsgContextType* pMsgContext)
{
    uint8 result= DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;    
    } 
    else
    {
        pMsgContext->resData[0]= 0xF1;
        pMsgContext->resData[1]= 0x8b;
        
       /* if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F18B_ADDR,DID_F18B_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT;
        }*/
    }
    
    return result;
}
/******************************************************************************
 * Name         :  App_WriteF18C
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/
uint8 App_WriteF18C(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;    
    } 
    else
    {
        pMsgContext->resData[0]= 0xF1;
        pMsgContext->resData[1]= 0x8c;
        
     /*   if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F18C_ADDR,DID_F18C_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT;
        }*/
    }
    
    return result;
}
/******************************************************************************
 * Name         :  App_WriteF190
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/
uint8 App_WriteF190(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;    
    } 
    else
    {
        pMsgContext->resData[0]= 0xF1;
        pMsgContext->resData[1]= 0x90;
        
      /*  if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F190_ADDR,DID_F190_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT;
        }*/
    }

    return result;
}
/******************************************************************************
 * Name         :  App_WriteF193
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_WriteF193(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;    
    } 
    else 
    {
        pMsgContext->resData[0]= 0xF1;
        pMsgContext->resData[1]= 0x93;
        
      /*  if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F193_ADDR,DID_F193_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT;
        }*/
    }

    return result;
}
/******************************************************************************
 * Name         :  App_WriteF195
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

/*result=0 menas success,=1 means write error and give a NRC=GeneralReject, =2 means conditionnotsupport.*/
uint8 App_WriteF195(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
   
    
    if(gOperationPermit == DISABLE_OPERATION) 
    {
      result = DCM_NUM_CONDITIONSNOTCORRECT;/* 0x22  */ 
    } 
    else
    {
      pMsgContext->resData[0]= 0xF1;
      pMsgContext->resData[1]= 0x95;
      
      /*
      if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F195_ADDR,DID_F195_LEN)) 
      {
         result = DCM_NUM_GENERALREJECT;
      }
      */
    }
    
    return result;
}

/******************************************************************************
 * Name         :  App_Write0100
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_Write0100(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else 
    {
        pMsgContext->resData[0]= 0x01;
        pMsgContext->resData[1]= 0x00;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_0100_ADDR,DID_0100_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}

/******************************************************************************
 * Name         :  App_WriteF010
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_WriteF010(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0xF0;
        pMsgContext->resData[1]= 0x10;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F010_ADDR,DID_F010_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}


/******************************************************************************
 * Name         :  App_WriteF197
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_WriteF197(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0xF1;
        pMsgContext->resData[1]= 0x97;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_F197_ADDR,DID_F197_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}



/******************************************************************************
 * Name         :  App_Write1C00
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_Write1C00(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0x1C;
        pMsgContext->resData[1]= 0x00;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C00_ADDR,DID_1C00_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}



/******************************************************************************
 * Name         :  App_Write1C01
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_Write1C01(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0x1C;
        pMsgContext->resData[1]= 0x01;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C01_ADDR,DID_1C01_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}


/******************************************************************************
 * Name         :  App_Write1C02
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_Write1C02(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0x1C;
        pMsgContext->resData[1]= 0x02;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C02_ADDR,DID_1C02_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}

/******************************************************************************
 * Name         :  App_Write1C03
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_Write1C03(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0x1C;
        pMsgContext->resData[1]= 0x03;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C03_ADDR,DID_1C03_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}

/******************************************************************************
 * Name         :  App_Write1C04
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_Write1C04(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0x1C;
        pMsgContext->resData[1]= 0x04;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C04_ADDR,DID_1C04_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}

/******************************************************************************
 * Name         :  App_Write1C05
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  write DID into E2
 ******************************************************************************/

uint8 App_Write1C05(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0x1C;
        pMsgContext->resData[1]= 0x05;
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C05_ADDR,DID_1C05_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}
#endif


#if(DCM_SERVICE_2F_ENABLED==STD_ON)
/******************************************************************************
 * Name         :  App_2F_4C00_ReturnControlToEcuFnc
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  
 ******************************************************************************/

uint8 App_2F_4C00_ReturnControlToEcuFnc(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        pMsgContext->resData[0]= 0x4C;
        pMsgContext->resData[1]= 0x00;
        pMsgContext->resData[2]= pMsgContext->reqData[3];
        pMsgContext->resData[3]= getGPIO(S2_CTR);
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C05_ADDR,DID_1C05_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}

/******************************************************************************
 * Name         :  App_2F_4C00_ResetToDefaultFnc
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  
 ******************************************************************************/
uint8 App_2F_4C00_ResetToDefaultFnc(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
    	//setGPIO(&S2_CTR,&HW_S2_CTR,LOW);
    	S2_CTR = LOW;
    	HW_S2_CTR = S2_CTR;
        pMsgContext->resData[0]= 0x4C;
        pMsgContext->resData[1]= 0x00;
        pMsgContext->resData[2]= pMsgContext->reqData[3];
        pMsgContext->resData[3]= getGPIO(S2_CTR);
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C05_ADDR,DID_1C05_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}

/******************************************************************************
 * Name         :  App_2F_4C00_FreezeCurrentStateFnc
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  
 ******************************************************************************/
uint8 App_2F_4C00_FreezeCurrentStateFnc(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    } 
    else
    {
        //setGPIO(&S2_CTR,(uint8*)&HW_S2_CTR,getGPIO(S2_CTR));
        //S2_CTR = getGPIO(S2_CTR);
    	//HW_S2_CTR = S2_CTR;
        pMsgContext->resData[0]= 0x4C;
        pMsgContext->resData[1]= 0x00;
        pMsgContext->resData[2]= pMsgContext->reqData[3];
        pMsgContext->resData[3]= getGPIO(S2_CTR);
        
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C05_ADDR,DID_1C05_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}

/******************************************************************************
 * Name         :  App_2F_4C00_ShortTermAdjustmentFnc
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :1(NRC=0x10)  : GeneralReject
 *               2(NRC=0x22)  : Condition not correct
 *               3(NRC=0x31)  : Request OutofRange
 * Description  :  
 ******************************************************************************/
uint8 App_2F_4C00_ShortTermAdjustmentFnc(Dcm_MsgContextType* pMsgContext)
{
    uint8 result=DCM_NUM_POSITIVERESPONSE;
    uint8 controlState = 0;
    controlState = pMsgContext->reqData[4];
    if (gOperationPermit == DISABLE_OPERATION) 
    {
        result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    }
    else if(controlState != LOW && controlState != HIGH)
    {
    	result = DCM_NUM_CONDITIONSNOTCORRECT;/*NRC=0x22*/    
    }
    else
    {
    	//setGPIO(&S2_CTR,(uint8*)&HW_S2_CTR,controlState);
    	S2_CTR = controlState;
    	HW_S2_CTR = S2_CTR;
        pMsgContext->resData[0]= 0x4C;
        pMsgContext->resData[1]= 0x00;
        pMsgContext->resData[2]= pMsgContext->reqData[3];
        pMsgContext->resData[3]= getGPIO(S2_CTR);
        /*
        if(0 != EEpromWriteData(&pMsgContext->resData[2],DID_1C05_ADDR,DID_1C05_LEN)) 
        {
           result = DCM_NUM_GENERALREJECT; 
        }
        */
    }

    return result;
}
#endif

#if(DCM_SERVICE_85_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_DTCRecordOn
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  control DTC record open
 ******************************************************************************/
void App_DTCRecordOn(Dcm_MsgContextType* pMsgContext)
{
    (void)pMsgContext;
    DsdInternal_ProcessingDone(pMsgContext);
    
    if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)
    {
       gDTCSwitch= 1;    	
    }
    else
    {
    	
    }
}
/******************************************************************************
 * Name         :  App_DTCRecordOff
 * Called by    :
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  control DTC record stop
 ******************************************************************************/
void App_DTCRecordOff(Dcm_MsgContextType* pMsgContext)
{
    (void)pMsgContext;
    DsdInternal_ProcessingDone(pMsgContext);
    
    if(gNegativeResponseCode==DCM_E_POSITIVERESPONSE)
    {
       gDTCSwitch= 0;    	
    }
    else
    {
    	
    }

}


#endif

/******************************************************************************
 * Name         :App_EchoRequest
 * Called by    :Dcm
 * Preconditions:N/A
 * Parameters   :Dcm_MsgContextType* pMsgContext
 * Return code  :N/A
 * Description  :Internal test callback.
 *
 ******************************************************************************/
void App_EchoRequest(Dcm_MsgContextType* pMsgContext)
{
   pMsgContext->resDataLen = pMsgContext->reqDataLen;
}




#if(DCM_SERVICE_31_ENABLED==STD_ON)

/******************************************************************************
 * Name         :  App_31_startRoutine
 * Called by    :  
 * Preconditions:  none
 * Parameters   :  pMsgContext
 * Return code  :  none
 * Description  :  excute the reset operation
 ******************************************************************************/

uint8  App_31_startRoutine(Dcm_MsgContextType* pMsgContext)
{
    uint8  result = 0;
    uint16 RoutineDIDRequest;

    RoutineDIDRequest=Make16Bit(pMsgContext->reqData[2],pMsgContext->reqData[3]);
    
    if((RoutineDIDRequest == CHECKCONDITION))
    {
        
        pMsgContext->resData[0]=pMsgContext->reqData[0]+0x40;
        pMsgContext->resData[1]=pMsgContext->reqData[1];
        pMsgContext->resData[2]=pMsgContext->reqData[2];
        pMsgContext->resData[3]=pMsgContext->reqData[3];
        pMsgContext->resDataLen=4;       

        result = DCM_NUM_POSITIVERESPONSE;
        
    }
    else
    {
        result = DCM_NUM_REQUESTOUTOFRANGE;
    }
    
    return result;
}


#endif

/******************************************************* End  ******************************************************/

