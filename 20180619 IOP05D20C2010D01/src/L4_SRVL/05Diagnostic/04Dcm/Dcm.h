/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm.h  
*
* @brief  Head file for DCM module.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/25    CODER1     N/A           Original
*     1.1      2018/06/26    YCH        N/A           Original 
*     
*******************************************************************************/


#ifndef _DCM_H_
#define _DCM_H_

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/       
#include "UDS_ComStack_Types.h"
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"
#include "App_Dcm.h"
/**************************************************************************************************
* Macros and Tyedef
***************************************************************************************************/
/*-----------------------------------------------------------------------------
    &&~ Genernal
 -----------------------------------------------------------------------------*/
     
#define SID_POSITION   							0
#define SIDOFFSET                               0x40/* offset value of positiveID,sid+0x40*/
#define SET_SUPPRESS_POS_RESONPOSE_BIT_MASK     (uint8)0x80 
#define HAVE_GOTTON_SEED                        0x01
#define HAVE_STARTED_ROUNTINE 					0x01

/*-----------------------------------------------------------------------------
    &&~ PduIdType
 -----------------------------------------------------------------------------*/
#define UDS_PHYSICAL_ON_CAN_Rx    0u
#define UDS_FUNCTIONAL_ON_CAN_Rx  1u 
#define UDS_ON_CAN_Tx             0u
#if(ISO_15031_5==STD_ON)
#define OBD_PHYSICAL_ON_CAN_Rx    2u
#define OBD_FUNCTIONAL_ON_CAN_Rx  3u /* Related with position of gDcmDslAvailableBufferSize's member */
#define OBD_ON_CAN_Tx             1u
#endif  

/*-----------------------------------------------------------------------------
    &&~ Diagnostic State Machine
 -----------------------------------------------------------------------------*/
#define DIAG_IDLE                 (uint8)0x00u/*default */
#define DIAG_UDS_INDICATION       (uint8)0x01u/*showing receive uds request*/
#define DIAG_UDS_PROCESSING       (uint8)0x02u/*when dcm module detect the indication bit has been setted,it will change the diagstate to Processing..*/
#define DIAG_UDS_RCRP             (uint8)0x04u/*received correctly_response pending*/
#define DIAG_UDS_RCRP_DONE        (uint8)0x08u/*when send 0x78 exceed limittimes,then PduRouter set the state into this state.*/
#define DIAG_OBD_INDICATION       (uint8)0x10u
#define DIAG_OBD_PROCESSING       (uint8)0x20u


/*-----------------------------------------------------------------------------
    &&~ For 0x22
 -----------------------------------------------------------------------------*/
typedef struct
{
  uint16  Did;
  uint16  DidPosition; 
}DidlistType;


/*-----------------------------------------------------------------------------
    &&~ For 0x2A
 -----------------------------------------------------------------------------*/
#if(DCM_SERVICE_2A_ENABLED==STD_ON)
typedef struct
{
    uint8   Did;
    uint16  DidPosition; 
}PeriodicDidlistType;
#endif 


/*-----------------------------------------------------------------------------
    &&~ For 0x2C
 -----------------------------------------------------------------------------*/
#if(DCM_SERVICE_2C_ENABLED==STD_ON)
typedef struct
{
    uint8 ByDidOrAddress; /* 0x00: byDid, 0x01:ByAddress */
    uint8 DidOrAddressCounter;
}DynamicalDidDefinedSequence;
typedef struct
{
    uint16   SourceDid;
    uint16   SourceDidPosition;
    uint16   PositionInSourceDataRecord;
    uint16   MemorySize;
}DefinedByDid;
typedef struct
{
    uint32   MemoryAddress;
    uint8    AddressSegment;
    uint32   MemorySize;
  
}DefinedByAddress;
typedef struct
{
    uint16                      DynamicalDid;
    uint8                       DynamicalDidPosion;/* Posicon in gDcmDsdSubService_2C*/ 
    uint8                       DefinedTime;
    DynamicalDidDefinedSequence Sequence[16];
    DefinedByDid                ByDid[16];/* size should be configurable  */
    uint8                       SourceDidCounter;       
    DefinedByAddress            ByAddress[16];/* size should be configurable   */
    uint8                       AddessCounter;
    uint32                      TotalDataSize;
}DynamicalDidRelatedInfo;

#endif 



/**************************************************************************************************
* Global variables(Scope:global)
***************************************************************************************************/
extern Dcm_MsgItemType              gUDS_Physical_DiagBuffer[UDS_PHYS_BUFFER_SIZE]; 
extern Dcm_MsgItemType              gUDS_Functional_DiagBuffer[UDS_FUNC_BUFFER_SIZE]; 
#if(ISO_15031_5==STD_ON)
extern Dcm_MsgItemType              gOBD_Physical_DiagBuffer[OBD_PHYS_BUFFER_SIZE];
extern Dcm_MsgItemType              gOBD_Functional_DiagBuffer[OBD_FUNC_BUFFER_SIZE];
extern DcmDslBufferSize             gDcmDslAvailableBufferSize[4];   
#else
extern DcmDslBufferSize             gDcmDslAvailableBufferSize[2];
#endif

extern Dcm_MsgItemType              gNegativeResponseBuffer[NEG_RESP_BUFFER_SIZE];
extern uint16                       gResponseLength;   

#if(DCM_SERVICE_27_ENABLED==STD_ON)
extern Dcm_SecLevelType             gSecLevelType[KIND_OF_SECURITY_LEVEL];
#endif

extern Dcm_SesCtrlType              gSesCtrlType;
extern Dcm_ProtocolType             gActiveProtocol;
extern Dcm_MsgContextType           gMsgContextType;
extern Dcm_NegativeResponseCodeType gNegativeResponseCode;
extern uint8                        gDiagState;
extern uint32                       gP2ServerTimer;
extern uint32                       gS3ServerTimer;
extern uint8                        gP2ServerTimerStartFlag;
extern uint8                        gS3ServerTimerStartFlag;
extern uint8                        gCurrentSecurityAccessRequestLevel;
extern uint32                       gSecurityDelayTimeOnBootFlag; 

#if(DCM_SERVICE_27_ENABLED==STD_ON)
extern uint32                       gSecurityAcessDelayTimeOnBoot[KIND_OF_SECURITY_LEVEL];
extern uint8                        gSecurityAcessAttempNumber[KIND_OF_SECURITY_LEVEL];   
extern uint8                        gSecurityAcessAttempNumberExceeded[KIND_OF_SECURITY_LEVEL];
extern uint32                       gSecurityAcessDelayTime[KIND_OF_SECURITY_LEVEL];      
extern uint8                        gSecurityAcessSequence[KIND_OF_SECURITY_LEVEL];
#endif

extern uint32                       gDTCSwitch;



/**************************************************************************************************
* Global Function Prototype
***************************************************************************************************/

/*-----------------------------------------------------------------------------
    &&~ Marco Functions
 -----------------------------------------------------------------------------*/
#define Set_SecLevel(x)                (gSecLevelType[gCurrentSecurityAccessRequestLevel-1]=(x))
#define Set_SesCtrl(x)                 (gSesCtrlType=(x))
#define Set_ActiveProtocol(x)          (gActiveProtocol=(x))
#define Clr_ActiveProtocol()           (gActiveProtocol=(0))
#define Set_PduId(x)                   (gMsgContextType.dcmRxPduId=(x))
#define Reset_PduId()                  (gMsgContextType.dcmRxPduId=0xFF)
#define Set_P2_Server_Timer(x)         (gP2ServerTimer=(uint32)((x)/DCM_TASK_TIME))
#define Dec_P2_Server_Timer()          (gP2ServerTimer--)
#define Clr_P2_Server_Timer()          (gP2ServerTimer=0)
#define Set_S3_Server_Timer(x)         (gS3ServerTimer=(uint32)((x)/DCM_TASK_TIME))
#define Dec_S3_Server_Timer()          (gS3ServerTimer--)
#define Clr_S3_Server_Timer()          (gS3ServerTimer=0)
#define Set_DiagState(x)               (gDiagState|=(x))
#define Clr_DiagState(x)               (gDiagState&=(~(x)))
#define Reset_DiagState()              (gDiagState=DIAG_IDLE)
#define GetSuppressPosResponseBit()    (gMsgContextType.msgAddInfo.suppressPosResponse)
#define ClrSuppressPosResponseBit()    (gMsgContextType.msgAddInfo.suppressPosResponse=0)
#define SetNegativeResponseCode(x)     (gNegativeResponseCode=(x))
#define ClrNegativeResponseCode()      (gNegativeResponseCode=0)
#define Dec_Max_Number_Of_RCRRP()      (gMaxNumberOfRCRRP--)
#define Reset_Max_Number_Of_RCRRP()    (gMaxNumberOfRCRRP=DCM_NUM_MAX_RESPPEND)
#define Make16Bit(HiByte,LoByte)       ((uint16)((((uint16)(HiByte))<<8)|((uint16)(LoByte))))
#define Make24Bit(HiByte,MiByte,LoByte) ((uint32)((((uint32)(HiByte))<<16)|((uint32)(MiByte)<<8)|((uint32)(LoByte))))

/*-----------------------------------------------------------------------------
    &&~ Global Functions
 -----------------------------------------------------------------------------*/
extern FUNC(void,DCM_CODE) Dcm_Init
(
    P2VAR(Dcm_ConfigType,AUTOMATIC,DCM_APPL_DATA) ConfigPtr
);

   
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetSecurityLevel
(
    P2VAR(Dcm_SecLevelType,AUTOMATIC,DCM_APPL_DATA) SecLevel
);

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetSesCtrlType
(
    P2VAR(Dcm_SesCtrlType,AUTOMATIC,DCM_APPL_DATA) SesCtrlType
);

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocol
(
    P2VAR(Dcm_ProtocolType,AUTOMATIC,DCM_APPL_DATA) ActiveProtocol
);

extern FUNC(void,DCM_CODE) Dcm_ResetToDefaultSession
(
    void
);

extern FUNC(void,DCM_CODE) Dcm_MainFunction
(
    void
);

extern FUNC(void,DCM_CODE) DslInternal_Timer_CallbackTask
(
    void
);


#if(DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN==STD_ON)
extern void  DslInternal_RCRResponsePending
(
    uint8 ForceRCR_RP
);
#else
STATIC void  DslInternal_RCRResponsePending
(
    uint8 ForceRCR_RP
);
#endif

extern void DsdInternal_ProcessingDone
(
    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext
);
extern void DsdInternal_ProcessingDoneNoResponse
(
    void
);

#if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
extern void DsdInternal_DidProcessingDone
(
    void
);
#endif
extern void DsdInternal_SetNegResponse
(
    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext,
    uint8 ErrorCode
);      
 
/*-----------------------------------------------------------------------------
    &&~ OBD diagnostic service 
 -----------------------------------------------------------------------------*/
#if(ISO_15031_5==STD_ON)
#if(DCM_SERVICE_01_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestCurrentPowertrainDiagnosticData
(
    void
);
#endif
        
#if(DCM_SERVICE_02_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestPowertrainFreezeFrameData
(
    void
);
#endif

#if(DCM_SERVICE_03_ENABLED==STD_ON)               
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestEmissionRelatedDiagnosticTroubleCodes
(
    void
);
#endif

#if(DCM_SERVICE_04_ENABLED==STD_ON)   
extern FUNC(void,DCM_CODE) DspInternal_Obd_ClearResetEmissionRelatedDiagnosticInformation
(
    void
);
#endif

#if(DCM_SERVICE_06_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestOnboardMonitoringTestResultsForSpecificMonitoredSystems
(
    void
);
#endif

#if(DCM_SERVICE_07_ENABLED==STD_ON) 
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestEmissionRelatedDiagnosticTroubleCodesDetectedDuringCurrentOrLastCompletedDrivingCycle
(
    void
);
#endif

#if(DCM_SERVICE_08_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestControlOfOnboardSystemTestOrComponent
(
    void
);
#endif

#if(DCM_SERVICE_09_ENABLED==STD_ON)   
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestVehicleInformation
(
    void
);
#endif

#if(DCM_SERVICE_0A_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Obd_RequestEmissionRelatedDiagnosticTroubleCodeswithPermanentStatus
(
    void
);
#endif
 
#endif     


/*-----------------------------------------------------------------------------
    &&~ UDS diagnostic service
 -----------------------------------------------------------------------------*/         
#if(DCM_SERVICE_10_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_DiagnosticSessionControl
(
    void
);
#endif

#if(DCM_SERVICE_11_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_EcuReset
(
    void
);
#endif

#if(DCM_SERVICE_14_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_ClearDiagnosticInformation
(
    void
);
#endif

#if(DCM_SERVICE_19_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_ReadDTCInformation
(
    void
);
#endif

#if(DCM_SERVICE_22_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_ReadDataByIdentifier
(
    void
);
#endif



#if(DCM_SERVICE_27_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_SecurityAccess  /*used in Dcm_Cfg.c.*/
(
    void
);

/*reserved*/
extern void  DsdInternal_SecurityAccessKeyCompared
(
    uint8 level, DcmDspSecurityAccessKey keyIsValid
);


#endif 

#if(DCM_SERVICE_28_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_CommunicationControl
(
    void
);
#endif

#if(DCM_SERVICE_2A_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_ReadDataByPeriodicIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_2C_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_DynamicallyDefinedDataIdentifier
(
    void
);
#endif  

#if(DCM_SERVICE_2E_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_WriteDataByIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_2F_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_InputOutputControlByIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_31_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_RoutineControl
(
    void
);

extern void  DsdInternal_RoutineStarted
(
    void
);
#endif

#if(DCM_SERVICE_3D_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_WriteMemoryByAddress
(
    void
);
#endif   

#if(DCM_SERVICE_3E_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_TesterPresent
(
    void
);
#endif

#if(DCM_SERVICE_85_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_ControlDTCSetting
(
    void
);
#endif

#if(DCM_SERVICE_86_ENABLED==STD_ON)
extern FUNC(void,DCM_CODE) DspInternal_Uds_ResponseOnEvent
(
    void
);
#endif     

#endif


/*******************************************************  Dcm.h End  ******************************************************/
