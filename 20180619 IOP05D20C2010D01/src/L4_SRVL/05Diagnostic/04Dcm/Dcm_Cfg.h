/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm_Cfg.h  
*
* @brief  config head file for DCM module.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26     CODER1       N/A           Original
*     
*******************************************************************************/
#ifndef _DCM_CFG_H_
#define _DCM_CFG_H_


/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/ 
#include "Dcm.h"
#include "PduR_Dcm.h"
#include "CanTp.h"         

/*****************************************************************************************                           
 *   Macros and Tyedef                
 *****************************************************************************************/
/*----------------------------------------------------------------------------------------
    &&~ The following macros are non-configurable
-----------------------------------------------------------------------------------------*/  
#define UseBlockId                     0x01u
#define UseDataClientServer            0x02u
#define UseDataSenderReceiver          0x03u
#define UseEcuSignal                   0x04u
#define UseFnc                         0x05u
#define DCM_NULL                       ((void*)0)       
#define SUB_FUNCTION_NOT_SUPPORTED     0x00u
#define SUB_FUNCTION_SUPPORTED         0x01u

/* IsSupportedFunctionReq=0 means only Physical Address and 1 represent both Phy and Fun */
#define PHYSICAL_REQ_SUPPORTED                0x00u
#define PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED 0x01u
#define FUNCTIONAL_REQ_SUPPORTED              0x02u



/*----------------------------------------------------------------------------------------
    &&~  For 0x27 
-----------------------------------------------------------------------------------------*/ 
#define REQUEST_SEED_L1                0x01u
#define SEND_KEY_L1                    0x02u
#define REQUEST_SEED_L2                0x03u
#define SEND_KEY_L2                    0x04u
#define REQUEST_SEED_L3                0x05u
#define SEND_KEY_L3                    0x06u


/*----------------------------------------------------------------------------------------
    &&~  For 0x28 
-----------------------------------------------------------------------------------------*/ 
#define ENABLE_RX_AND_TX               0x00u
#define ENBALE_RX_AND_DISABLE_TX       0x01u
#define DISABLE_RX_AND_ENBALE_TX       0x02u
#define DISABLE_RX_AND_TX              0x03u
#define NORMAL_MSG                     0x01u
#define NM_MSG                         0x02u
#define BOTH_NORMAL_AND_NM_MSG         0x03u


/*----------------------------------------------------------------------------------------
    &&~  For 0x2F 
-----------------------------------------------------------------------------------------*/ 
#define RETURN_CONTROL_TO_ECU          0x00u
#define RESET_TO_DEFAULT               0x01u
#define FREEZE_CURRENT_STATE           0x02u
#define SHORT_TERM_ADJUSTMENT          0x03u


/*----------------------------------------------------------------------------------------
    &&~  For 0x31
-----------------------------------------------------------------------------------------*/ 
#define START_ROUTINE                  0x01u
#define STOP_ROUTINE                   0x02u
#define REQUEST_ROUTINE_RESULT         0x03u


/*----------------------------------------------------------------------------------------
    &&~ For 0x3E 
-----------------------------------------------------------------------------------------*/ 
#define ZERO_SUB_FUNCTION              0x00u


/*----------------------------------------------------------------------------------------
    &&~  For 0x85 
-----------------------------------------------------------------------------------------*/ 
#define DTC_RECORD_ON                  0x01u
#define DTC_RECORD_OFF                 0x02u


/*----------------------------------------------------------------------------------------
    &&~  For 0xB0 
-----------------------------------------------------------------------------------------*/ 
#define ECHO_REQUEST                   0x01u
#define DCM_VENDOR_ID                  (uint16)(0xFFFFu)         /* Supplier ID */
#define DCM_MODULE_ID                  (uint16)(0x0023u)         /* Dcm Moudle ID */

/* CanTp Component release Version  */
#define DCM_SW_MAJOR_VERSION           (uint8)(0x01u)
#define DCM_SW_MINOR_VERSION           (uint8)(0x01u)
#define DCM_SW_PATCH_VERSION           (uint8)(0x00u)

/* Autosar release version */
#define DCM_AR_MAJOR_VERSION           (uint8)(0x01u)
#define DCM_AR_MINOR_VERSION           (uint8)(0x00u)
#define DCM_AR_PATCH_VERSION           (uint8)(0x00u)

/******************************************************************************************           
                The following macros are configurable                     
\******************************************************************************************/
#define DCM_DSP_DATA_USE_PORT          UseFnc
#define DCM_DEV_ERROR_DETECT           STD_OFF
#define DCM_OEM_INDICATION             STD_OFF
#define DCM_SUPPLIER_INDICATION        STD_OFF
#define DCM_RESPONSE_ALL_REQ           STD_ON
#define DCM_VERSION_INFO_API           STD_OFF

/* Related to Dcm calling cycle */
#define DCM_TASK_TIME                  5

/* Related to 0x78 negative response */
#define DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN STD_ON
                                                  
#define DCM_NUM_MAX_RESPPEND           0xFFFFFFFFu

/* Related to customized service */
#define DCM_COSTOMIZED_SERVCIE_SUPPORTED   STD_ON

/* Related to Internal Test service */
#define DCM_INTERNALTEST_SERVCIE_SUPPORTED STD_ON


/*----------------------------------------------------------------------------------------
    &&~   Related to Obd service 
-----------------------------------------------------------------------------------------*/ 
#define ISO_15031_5                    STD_OFF
#define DCM_NUM_OF_OBD_SERVICE         10u
#define DCM_SERVICE_01_ENABLED         STD_OFF
#define DCM_SERVICE_02_ENABLED         STD_OFF
#define DCM_SERVICE_03_ENABLED         STD_OFF
#define DCM_SERVICE_04_ENABLED         STD_OFF
#define DCM_SERVICE_06_ENABLED         STD_OFF
#define DCM_SERVICE_07_ENABLED         STD_OFF
#define DCM_SERVICE_08_ENABLED         STD_OFF
#define DCM_SERVICE_09_ENABLED         STD_OFF
#define DCM_SERVICE_0A_ENABLED         STD_OFF




/*---------------------------------------------------
    &&~   10 
----------------------------------------------------*/
#define DCM_SERVICE_10_ENABLED         STD_ON
#if(DCM_SERVICE_10_ENABLED==STD_ON)
#define DCM_SERVICE_10_DefaultSession  STD_ON
#define DCM_SERVICE_10_ProgramSession  STD_OFF
#define DCM_SERVICE_10_ExtendedSession STD_ON
#define KIND_OF_SESSION                3u
#define NUM_OF_10_SUB_FUNCTION         2//3u modify by ych
#define DEFAULT_AND_EXTENDED_SEESION_HANDLE 0u                   /* Related to handle in gDcmDspSessionRow */
#define EXTENDED_SEESION_HANDLE        1u                        /* Related to handle in gDcmDspSessionRow */
#define RESPONSE_WITH_P2TIMER          STD_ON
#else
#define NUM_OF_10_SUB_FUNCTION         0u
#endif

/*---------------------------------------------------
    &&~   11 
----------------------------------------------------*/
#define DCM_SERVICE_11_ENABLED         STD_ON
#if(DCM_SERVICE_11_ENABLED==STD_ON)
#define DCM_SERVICE_11_HardReset       STD_ON
#define DCM_SERVICE_11_KeyOffOnReset   STD_OFF
#define DCM_SERVICE_11_SoftReset       STD_ON
#define DCM_SERVICE_11_EnableRapidPowerShutDown STD_OFF
#define DCM_SERVICE_11_DisableRapidPowerShutDown STD_OFF
#define NUM_OF_11_SUB_FUNCTION         2u
#else
#define NUM_OF_11_SUB_FUNCTION         0u
#endif

/*---------------------------------------------------
    &&~   14 
----------------------------------------------------*/
#define DCM_SERVICE_14_ENABLED         STD_ON
#define EmissionsRelatedSystems    		(0x000000)
#define PowertrainGroup  	  			(0x100000)

#define DTCGroup 							PowertrainGroup
#define ALLGroup     						(0xFFFFFF)

#define DTCGroupCheck     					(DTCGroup<<8)
#define ALLGroupCheck     					(ALLGroup<<8)

#define Sevice14ClearAllFaultAndRecov     //Clears the current DTC and resumes system failure to continue operation./


/*---------------------------------------------------
    &&~   19 
----------------------------------------------------*/
#define DCM_SERVICE_19_ENABLED         STD_ON
#if(DCM_SERVICE_19_ENABLED==STD_ON)
#define reportNumberOfDTCByStatusMask  STD_ON                    /* 0x01 */
#define reportDTCByStatusMask          STD_ON                    /* 0x02 */
#define reportDTCSnapshotIdentification STD_ON                  /* 0x03 */
#define reportDTCSnapshotRecordByDTCNumber STD_ON               /* 0x04 */
#define reportDTCSnapshotRecordByRecordNumber STD_OFF            /* 0x05 */
#define reportDTCExtendedDataRecordByDTCNumber STD_ON           /* 0x06 */
#define reportNumberOfDTCBySeverityMaskRecord STD_OFF            /* 0x07 */
#define reportDTCBySeverityMaskRecord  STD_OFF                   /* 0x08 */
#define reportSeverityInformationOfDTC STD_OFF                   /* 0x09 */
#define reportSupportedDTC             STD_ON                    /* 0x0a */
#define reportFirstTestFailedDTC       STD_OFF                   /* 0x0b */
#define reportFirstConfirmedDTC        STD_OFF                   /* 0x0c */
#define reportMostRecentTestFailedDTC  STD_OFF                   /* 0x0d */
#define reportMostRecentConfirmedDTC   STD_OFF                   /* 0x0e */
#define reportMirrorMemoryDTCByStatusMask STD_OFF                /* 0x0f */
#define reportMirrorMemoryDTCExtendedDataRecordByDTCNumber STD_OFF/* 0x10 */
#define reportNumberOfMirrorMemoryDTCByStatusMask STD_OFF        /* 0x11 */
#define reportNumberOfEmissionsRelatedOBDDTCByStatusMask STD_OFF /* 0x12 */
#define reportEmissionsRelatedOBDDTCByStatusMask STD_OFF         /* 0x13 */
#define SAE_J2012_DA_DTCFormat_00 		0
#define ISO_14229_1_DTCFormat 			1
#define SAE_J1939_73_DTCFormat 			2
#define ISO_11992_4_DTCFormat 			3
#define SAE_J2012_DA_DTCFormat_04  		4
#define DTCFormatIdentifier           	ISO_14229_1_DTCFormat
#define NUM_OF_19_SUB_FUNCTION         	6u
#else
#define NUM_OF_19_SUB_FUNCTION         0u
#endif

/*---------------------------------------------------
    &&~   22 
----------------------------------------------------*/
#define DCM_SERVICE_22_ENABLED         STD_ON
#define DCM_SERVICE_22_COMBINED_DID    STD_OFF
#define OBC_DCM_SERVICE_22_ENABLED    STD_ON
#if(DCM_SERVICE_22_ENABLED==STD_ON)
	#if(OBC_DCM_SERVICE_22_ENABLED==STD_OFF)
		#define NUMBER_OF_READ_DID             9
	#else
		#define NUMBER_OF_READ_DID             (9+7)
	#endif
#endif


/*---------------------------------------------------
    &&~   23 
----------------------------------------------------*/
#define DCM_SERVICE_23_ENABLED         STD_OFF
#if(DCM_SERVICE_23_ENABLED==STD_ON)
#define NUMBER_OF_READ_ADDRESS_SEG     3
#endif


/*---------------------------------------------------
    &&~   24 
----------------------------------------------------*/
#define DCM_SERVICE_24_ENABLED         STD_OFF
#if(DCM_SERVICE_24_ENABLED==STD_ON)
#define NUMBER_OF_READ_DID_24          1
#endif


/*---------------------------------------------------
    &&~   27 
----------------------------------------------------*/
#define DCM_SERVICE_27_ENABLED         STD_ON
#if(DCM_SERVICE_27_ENABLED==STD_ON)
#define DCM_SERVICE_27_GetSeed_L1      STD_ON
#define DCM_SERVICE_27_CompareKey_L1   STD_ON
#define DCM_SERVICE_27_GetSeed_L2      STD_OFF
#define DCM_SERVICE_27_CompareKey_L2   STD_OFF
#define DCM_SERVICE_27_GetSeed_L3      STD_OFF
#define DCM_SERVICE_27_CompareKey_L3   STD_OFF
#define KIND_OF_SECURITY_LEVEL         1u/* we only use one kind(One Level)*/
#define NUM_OF_27_SUB_FUNCTION         2u
#define DISABLE_SECURITY_ACCESS_ATTEMPT_NUMBER_RESET
#else
#define NUM_OF_27_SUB_FUNCTION         0u
#endif


/*---------------------------------------------------
    &&~   28 
----------------------------------------------------*/
#define DCM_SERVICE_28_ENABLED         STD_ON
#if(DCM_SERVICE_28_ENABLED==STD_ON)
#define DCM_SERVICE_28_EnableRxAndTx   STD_ON
#define DCM_SERVICE_28_EnableRxAndDisableTx STD_OFF
#define DCM_SERVICE_28_DisableRxAndEnableTx STD_OFF
#define DCM_SERVICE_28_DisableRxAndTx  STD_ON
#define NUM_OF_28_SUB_FUNCTION         2u
#else
#define NUM_OF_28_SUB_FUNCTION         0u
#endif


/*---------------------------------------------------
    &&~   2A 
----------------------------------------------------*/
#define DCM_SERVICE_2A_ENABLED         STD_OFF
#if(DCM_SERVICE_2A_ENABLED==STD_ON)
#define SEND_AT_SLOW_RATE              10000                     /*Unit: ms*/
#define SEND_AT_MEDIUM_RATE            1000                      /*Unit: ms*/
#define SEND_AT_FAST_RATE              100                       /*Unit: ms*/
#define NUMBER_OF_PERIODIC_DID         5
#define DCM_PERIODIC_TRANS_TYPE1_ENABLED STD_ON
#define DCM_PERIODIC_TRANS_TYPE2_ENABLED STD_OFF
#endif


/*---------------------------------------------------
    &&~   2C 
----------------------------------------------------*/
#define DCM_SERVICE_2C_ENABLED         STD_OFF
#if(DCM_SERVICE_2C_ENABLED==STD_ON)
#define DCM_SERVICE_2C_defineByIdentifier STD_OFF
#define DCM_SERVICE_2C_defineByMemoryAddress STD_OFF
#define DCM_SERVICE_2C_clearDynamicallyDefinedDataIdentifier STD_OFF
#define NUM_OF_2C_SUB_FUNCTION         3u
#define NUMBER_OF_DYN_DID              4
#else
#define NUM_OF_2C_SUB_FUNCTION         0u
#endif


/*---------------------------------------------------
    &&~   2E 
----------------------------------------------------*/
#define DCM_SERVICE_2E_ENABLED         STD_ON
#if(DCM_SERVICE_2E_ENABLED==STD_ON)
/*#define NUMBER_OF_WRITE_DID          2*/
//#define NUMBER_OF_WRITE_DID            9     /*20130314,add F187,debug*/
	#if(OBC_DCM_SERVICE_22_ENABLED==STD_OFF)
		#define NUMBER_OF_WRITE_DID             9
	#else
		#define NUMBER_OF_WRITE_DID             (9+7)
	#endif
#else
	#define NUMBER_OF_WRITE_DID 0
#endif


/*---------------------------------------------------
    &&~   2F 
----------------------------------------------------*/
#define DCM_SERVICE_2F_ENABLED         STD_ON
#if(DCM_SERVICE_2F_ENABLED==STD_ON)
#define NUMBER_OF_CONTROL_DID          1u
#endif


/*---------------------------------------------------
    &&~   31 
----------------------------------------------------*/
#define DCM_SERVICE_31_ENABLED         STD_ON
#if(DCM_SERVICE_31_ENABLED==STD_ON)
#define DCM_SERVICE_31_startRoutine    STD_ON  //启动（0x01）、停止（0x02）、查询结果（0x03）
#define DCM_SERVICE_31_stopRoutine     STD_OFF
#define DCM_SERVICE_31_requestRoutineResults STD_OFF
#define NUMBER_OF_RID                  1u//24
#define NUM_OF_31_SUB_FUNCTION         (DCM_SERVICE_31_startRoutine+DCM_SERVICE_31_stopRoutine+DCM_SERVICE_31_requestRoutineResults)

#define CHECKCONDITION 					(0x0203)//check the programming condition
#else
#define NUM_OF_31_SUB_FUNCTION         0u
#endif


/*---------------------------------------------------
    &&~   3D 
----------------------------------------------------*/
#define DCM_SERVICE_3D_ENABLED         STD_OFF
#if(DCM_SERVICE_3D_ENABLED==STD_ON)
#define NUMBER_OF_WRITE_ADDRESS_SEG    3
#endif


/*---------------------------------------------------
    &&~   3E 
----------------------------------------------------*/
#define DCM_SERVICE_3E_ENABLED         STD_ON
#if(DCM_SERVICE_3E_ENABLED==STD_ON)
#define NUM_OF_3E_SUB_FUNCTION         1u
#else
#define NUM_OF_3E_SUB_FUNCTION         0u
#endif


/*---------------------------------------------------
    &&~   85 
----------------------------------------------------*/
#define DCM_SERVICE_85_ENABLED         STD_ON
#if(DCM_SERVICE_85_ENABLED==STD_ON)
#define DCM_SERVICE_85_DTCRecordOn     STD_ON
#define DCM_SERVICE_85_DTCRecordOff    STD_ON
#define NUM_OF_85_SUB_FUNCTION         2u
#else
#define NUM_OF_85_SUB_FUNCTION         0u
#endif


/*---------------------------------------------------
    &&~   86 
----------------------------------------------------*/
#define DCM_SERVICE_86_ENABLED         STD_OFF
#if(DCM_SERVICE_86_ENABLED==STD_ON)
#define DCM_ROE_TRANS_TYPE1_ENABLED    STD_ON
#define DCM_ROE_TRANS_TYPE2_ENABLED    STD_OFF
#define DCM_SERVICE_86_stopResponseOnEvent STD_OFF
#define DCM_SERVICE_86_onDTCStatusChange STD_OFF
#define DCM_SERVICE_86_onTimerInterrupt STD_OFF
#define DCM_SERVICE_86_onChangeOfDataIdentifier STD_OFF
#define DCM_SERVICE_86_reportActivatedEvents STD_OFF
#define DCM_SERVICE_86_startResponseOnEvent STD_OFF
#define DCM_SERVICE_86_clearResponseOnEvent STD_OFF
#define DCM_SERVICE_86_onComparisonOfValues STD_OFF
#define NUM_OF_86_SUB_FUNCTION         8u
#else
#define NUM_OF_86_SUB_FUNCTION         0u
#endif


/* Related to diagnostic buffer */
#define DCM_PAGEDBUFFER_ENABLED        STD_OFF
#if(ISO_15031_5==STD_ON)
#define OBD_PHYS_BUFFER_SIZE           1u
#define OBD_FUNC_BUFFER_SIZE           1u
#endif

#define UDS_FUNC_BUFFER_SIZE           8u
#define UDS_PHYS_BUFFER_SIZE           256u
#define NEG_RESP_BUFFER_SIZE           3u
#if(DCM_SERVICE_2A_ENABLED==STD_ON)
#define PERODIC_RESP_BUFFER_SIZE       8
#endif

#if(DCM_SERVICE_86_ENABLED==STD_ON)
#define EVENT_RESP_BUFFER_SIZE         8
#endif

/* Additional applicaiton callback */
#define DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL STD_ON


/*----------------------------------------------------------------------------------------
    &&~   Related to Uds service 
-----------------------------------------------------------------------------------------*/
//#define STD_ON_OFF_TO_NUM(x)    (x)
#define DCM_NUM_OF_SERVICE             ((uint8)(DCM_SERVICE_10_ENABLED)+ (uint8)(DCM_SERVICE_11_ENABLED) +(uint8)(DCM_SERVICE_14_ENABLED) +(uint8)(DCM_SERVICE_19_ENABLED)+(uint8)DCM_SERVICE_22_ENABLED  +(uint8)DCM_SERVICE_23_ENABLED+	(uint8)DCM_SERVICE_24_ENABLED+(uint8)DCM_SERVICE_27_ENABLED+(uint8)DCM_SERVICE_28_ENABLED+(uint8)DCM_SERVICE_2A_ENABLED+(uint8)DCM_SERVICE_2C_ENABLED+(uint8)DCM_SERVICE_2E_ENABLED+(uint8)DCM_SERVICE_2F_ENABLED+(uint8)DCM_SERVICE_31_ENABLED+(uint8)DCM_SERVICE_3D_ENABLED+	(uint8)DCM_SERVICE_3E_ENABLED+(uint8)DCM_SERVICE_85_ENABLED+(uint8)DCM_SERVICE_86_ENABLED+1)/* 12 services */
#define DCM_NUM_OF_SUB_SERVICE         (NUM_OF_10_SUB_FUNCTION+NUM_OF_11_SUB_FUNCTION+ NUM_OF_19_SUB_FUNCTION+NUM_OF_27_SUB_FUNCTION+ NUM_OF_28_SUB_FUNCTION+NUM_OF_2C_SUB_FUNCTION+ NUM_OF_31_SUB_FUNCTION+NUM_OF_3E_SUB_FUNCTION+ NUM_OF_85_SUB_FUNCTION+NUM_OF_86_SUB_FUNCTION+1u)
#define UDS_SERVICE_WITHOUT_SUB_FUNCTION 0u
#define UDS_SERVICE_WITH_SUB_FUNCTION  1u

typedef uint32 DcmDslBufferSize;
typedef void (*EcucFunctionNameDef)(void);
typedef uint8 (*EcucSubFunctionNameDef)(Dcm_MsgContextType*);
typedef void (*VoidEcucSubFunctionNameDef)(Dcm_MsgContextType*);
typedef void (*EcucPostSubFunctionNameDef)(Std_ReturnType Result);


/******************************************************************************************************           
 *                               Data types definition                     
\******************************************************************************************************/

/*---------------------------------------------------
    &&~   For Obd service table 
----------------------------------------------------*/
typedef struct 
{
	EcucFunctionNameDef DcmDsdSidTabFnc;
	uint8 DcmDsdSidTabServiceId;
} DcmDsdObdService;                    /* self-defined */


/*---------------------------------------------------
    &&~   For Uds service table 
----------------------------------------------------*/
typedef struct 
{
	EcucFunctionNameDef DcmDsdSidTabFnc; /*current service main function which call the callback function,do the abnormal-processing,
	                                   set positive or negtive code and give the response.*/
	/*uint8 DcmDsdSidTabServiceId; */   /*reserved*/
	uint8 DcmDsdSidTabSubfuncAvail;   /*indicate if the current service has the sub-function*/
	uint8 DcmDsdSidTabSecurityLevelRef;/*the security level which current service need supported,maybe do not need security access or maybe need levelone.*/
	uint8 DcmDsdSidTabSessionLevelRef;/*the session type which current service supported, default or extended or both.*/
} DcmDsdService;

typedef struct 
{
	uint8 DcmDsdSidTabId;
	DcmDsdService ServiceTable;
	uint8 FirstSubService;               /* self-defined */
	uint8 LastSubService;                /* self-defined */
	uint8 IsSupportedFunctionReq;
} DcmDsdServiceTable;


/*---------------------------------------------------
    &&~   For Uds sub-service table 
----------------------------------------------------*/
typedef struct 
{
	EcucSubFunctionNameDef DcmDsdSubFunction;/* self-defined,service-sub function */      

	EcucPostSubFunctionNameDef DcmDsdSubFunctionPost;/* self-defined, sub post function */
	uint8 DcmDsdSubServiceId;              /* sub-service ID */
	uint8 DcmDsdSubServiceIdSupported;     /* self-defined, sub-service ID of current service */
	uint8 DcmDsdSubServiceSecurityLevelRef;/* indicate if the sub-function support the security access */
	uint8 DcmDsdSubServiceSessionLevelRef; /* indicate if all the session types which the sub-function supportted */
	uint8 AddressingMode;                  /* self-defined,indicate the addressing mode which the sub_function supportted */  
} DcmDsdSubService;

/* For security access */
typedef struct 
{
	/* uint32 DcmDspSecurityADRSize;*/
	uint32 DcmDspSecurityDelayTime;
	uint32 DcmDspSecurityDelayTimeOnBoot;
	uint32 DcmDspSecurityKeySize;
	uint8 DcmDspSecurityLevel;
	uint8 DcmDspSecurityNumAttDelay;
	uint32 DcmDspSecuritySeedSize;
} DcmDspSecurityRow;

typedef enum 
{
	KEY_IS_NOT_VALID=0x00u,
	KEY_IS_VALID=0x01u
} DcmDspSecurityAccessKey;


/*---------------------------------------------------
    &&~    For session control 
----------------------------------------------------*/

typedef enum 
{
	DCM_NO_BOOT,
	DCM_OEM_BOOT,
	DCM_SYS_BOOT
} DcmDspSessionForBoot;

typedef struct 
{
	DcmDspSessionForBoot DcmDspSession;
	uint8 DcmDspSessionLevel;
	uint32 DcmDspSessionP2ServerMax;
	uint32 DcmDspSessionP2StarServerMax;
} DcmDspSessionRow;


/*---------------------------------------------------
    &&~   22 
----------------------------------------------------*/
typedef struct 
{
	uint32 DcmDspDidIdentifier;
	boolean DcmDspDidUsed;
	uint16 DcmDspDataSize;

	#if(DCM_DSP_DATA_USE_PORT==UseFnc)

	VoidEcucSubFunctionNameDef DcmDspDataReadFnc;

	#endif

	#if(DCM_DSP_DATA_USE_PORT==UseEcuSignal)

	VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
	VoidEcucSubFunctionNameDef DcmDspDataReadEcuSignal;

	#endif

	uint8 DcmDspDidReadSecurityLevelRef;
	uint8 DcmDspDidReadSessionRef;
} Dcm_22_ServiceInfoType;


/*---------------------------------------------------
    &&~   23 
----------------------------------------------------*/
typedef struct 
{
	uint32 DcmDspReadMemoryRangeHigh;
	uint32 DcmDspReadMemoryRangeLow;
	uint8 DcmDspReadMemoryRangeSecurityLevelRef;
	uint8 DcmDspReadMemoryRangeSessionRef;
	uint8 AddressingMode;
} DcmDspReadMemoryRangeInfo;


/*---------------------------------------------------
    &&~   24 
----------------------------------------------------*/
typedef struct 
{
	uint32 DcmDspDidIdentifier;
	boolean DcmDspDidUsed;
	uint16 DcmDspDataSize;

	#if(DCM_DSP_DATA_USE_PORT==UseFnc)

	VoidEcucSubFunctionNameDef DcmDspDataGetScalingInfoFnc;

	#endif

	#if(DCM_DSP_DATA_USE_PORT==UseEcuSignal)

	VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
	VoidEcucSubFunctionNameDef DcmDspDataReadEcuSignal;

	#endif

	uint8 DcmDspDidReadSecurityLevelRef;
	uint8 DcmDspDidReadSessionRef;
	uint8 AddressingMode;
} Dcm_24_ServiceInfoType;


/*---------------------------------------------------
    &&~   2A 
----------------------------------------------------*/
typedef struct 
{
	uint8 DcmDspDidIdentifier;
	boolean DcmDspDidUsed;
	uint16 DcmDspDataSize;

	#if(DCM_DSP_DATA_USE_PORT==UseFnc)

	VoidEcucSubFunctionNameDef DcmDspDataReadFnc;

	#endif

	uint8 DcmDspDidReadSecurityLevelRef;
	uint8 DcmDspDidReadSessionRef;
	uint8 AddressingMode;
} Dcm_2A_ServiceInfoType;


/*---------------------------------------------------
    &&~   2C 
----------------------------------------------------*/
typedef struct 
{
	uint32 DcmDspDidIdentifier;
	uint16 DcmDspDataSize;
	uint8 DcmDspDidReadSecurityLevelRef; /* security level must be the same as in 0x22 */
	uint8 DcmDspDidReadSessionRef;       /* session type must be the same as in 0x22 */
	uint8 AddressingMode;
} Dcm_2C_ServiceInfoType;


/*---------------------------------------------------
    &&~   2E 
----------------------------------------------------*/
typedef struct 
{
	uint32 DcmDspDidIdentifier;
	boolean DcmDspDidUsed;
	uint16 DcmDspDataSize;

	#if(DCM_DSP_DATA_USE_PORT==UseFnc)

	EcucSubFunctionNameDef DcmDspDataWriteFnc;

	#endif

	#if(DCM_DSP_DATA_USE_PORT==UseEcuSignal)

	EcucSubFunctionNameDef DcmDspDataEcuSignal;

	#endif

	uint8 DcmDspDidWriteSecurityLevelRef;
	uint8 DcmDspDidWriteSessionRef;
	uint8 AddressingMode;
} Dcm_2E_ServiceInfoType;


/*---------------------------------------------------
    &&~   2F 
----------------------------------------------------*/
typedef struct 
{
	uint32 DcmDspDidControlOptionRecordSize;/* This define the size of controlOptionRecord without the InputOutputControlParameter */
	uint32 DcmDspDidControlEnableMaskRecordSize;/* This is only useful when use InputOutputControlParameter */
	uint32 DcmDspDidControlStatusRecordSize;
} DcmDspDidControlRecordSizes;

typedef struct 
{
	uint32 DcmDspDidIdentifier;
	uint8 DcmDspDidControlSecurityLevelRef;
	uint8 DcmDspDidControlSessionRef;
	uint8 AddressingMode;
	DcmDspDidControlRecordSizes RecordSizes;

	#if(DCM_DSP_DATA_USE_PORT==UseFnc)

	EcucSubFunctionNameDef DcmDspDataReturnControlToEcuFnc;
	EcucSubFunctionNameDef DcmDspDataResetToDefaultFnc;
	EcucSubFunctionNameDef DcmDspDataFreezeCurrentStateFnc;
	EcucSubFunctionNameDef DcmDspDataShortTermAdjustmentFnc;

	#endif

	EcucFunctionNameDef OtherFnc; /* self-defined */
} Dcm_2F_ServiceInfoType;


/*---------------------------------------------------
    &&~   31 
----------------------------------------------------*/
typedef struct 
{
	uint8 DcmDspRoutineSecurityLevelRef;
	uint8 DcmDspRoutineSessionRef;
	uint8 AddressingMode;
} DcmDspRoutineAuthorization;

typedef struct 
{
	uint32 DcmDspRoutineSignalLength;

	/* uint32 DcmDspRoutineSignalPos; */
	/* Reserved */
} DcmDspRoutineSignal;

typedef struct 
{
	DcmDspRoutineAuthorization RoutineAuthorization;
	DcmDspRoutineSignal DcmDspRoutineRequestResOut;
	DcmDspRoutineSignal DcmDspRoutineStopIn;
	DcmDspRoutineSignal DcmDspRoutineStopOut;
	DcmDspRoutineSignal DcmDspStartRoutineIn;
	DcmDspRoutineSignal DcmDspStartRoutineOut;
} DcmDspRoutineInfo;

typedef struct 
{
	uint16 DcmDspRoutineIdentifier;
	boolean DcmDspRoutineUsed;
	boolean DcmDspRoutineUsePort;
	boolean DcmDspRoutineFixedLength;
	VoidEcucSubFunctionNameDef DcmDspStartRoutineFnc;
	VoidEcucSubFunctionNameDef DcmDspStopRoutineFnc;
	VoidEcucSubFunctionNameDef DcmDspRequestResultsRoutineFnc;
	DcmDspRoutineInfo DcmDspRoutineInfoRef;
} DcmDspRoutine;


/*---------------------------------------------------
    &&~   3D 
----------------------------------------------------*/
typedef struct 
{
	uint32 DcmDspWriteMemoryRangeHigh;
	uint32 DcmDspWriteMemoryRangeLow;
	uint8  DcmDspWriteMemoryRangeSecurityLevelRef;
	uint8  DcmDspWriteMemoryRangeSessionRef;
	uint8  AddressingMode;
} DcmDspWriteMemoryRangeInfo;


/*---------------------------------------------------
    &&~   86 
----------------------------------------------------*/
typedef struct 
{
	void(*DcmDspDidRoeActivateFnc)();
	uint32 DcmDspDidRoeEventId;
	boolean DcmDspRoeInitOnDSC;
	uint32 DcmDspRoeInterMessageTime;
	uint16 DcmDspRoeMaxEventLength;
	uint8 DcmDspRoeMaxNumberOfRetry;
	uint16 DcmDspRoeMaxQueueLength;
	boolean DcmDspRoeQueueEnabled;
} DcmDspRoe;




/**************************************************************************************************
 * extern declaration
 **************************************************************************************************/
extern ROM_CONST uint8* const gCurrentSidMap;
extern ROM_CONST DcmDsdServiceTable* const gCurrentDcmDsdServiceTable;

#if(ISO_15031_5==STD_ON)

extern ROM_CONST DcmDsdObdService gDcmDsdObdServiceTable[DCM_NUM_OF_OBD_SERVICE];

#endif

extern ROM_CONST uint32 gCurentDcmDsdServiceTableSize;

/* For 0x10,0x11,0x19,0x27,0x28,0x2C,0x31,0x3E,0x85 0x86 */
extern ROM_CONST DcmDsdSubService gDcmDsdSubService[DCM_NUM_OF_SUB_SERVICE];
extern ROM_CONST uint32 gDcmDspNonDefaultSessionS3Server;
extern ROM_CONST DcmDspSessionRow gDcmDspSessionRow[KIND_OF_SESSION];

#if(DCM_SERVICE_27_ENABLED==STD_ON)

extern ROM_CONST DcmDspSecurityRow gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL];

#endif

#if(DCM_SERVICE_22_ENABLED==STD_ON)

extern ROM_CONST Dcm_22_ServiceInfoType gDcmDsdSubService_22[NUMBER_OF_READ_DID];/* For 0x22 and 0x2C */
extern ROM_CONST uint16 DcmDspMaxDidToRead;

#endif

#if((DCM_SERVICE_23_ENABLED==STD_ON)|| (DCM_SERVICE_2C_ENABLED==STD_ON)||(DCM_SERVICE_3D_ENABLED==STD_ON))

extern ROM_CONST uint8 gMemoryAddressFormat;
extern ROM_CONST uint8 gMemorySizeFormat;

#endif

#if(DCM_SERVICE_23_ENABLED==STD_ON)

extern ROM_CONST DcmDspReadMemoryRangeInfo gDcmDspReadMemoryRangeInfo_23
  [NUMBER_OF_READ_ADDRESS_SEG];

#endif

#if(DCM_SERVICE_24_ENABLED==STD_ON)

extern ROM_CONST Dcm_24_ServiceInfoType gDcmDsdSubService_24[NUMBER_OF_READ_DID_24];/* For 0x24 */

#endif

#if(DCM_SERVICE_2A_ENABLED==STD_ON)

extern ROM_CONST Dcm_2A_ServiceInfoType gDcmDsdSubService_2A[NUMBER_OF_PERIODIC_DID];/* For 0x2A */

#endif

#if(DCM_SERVICE_2C_ENABLED==STD_ON)

extern ROM_CONST Dcm_2C_ServiceInfoType gDcmDsdSubService_2C[NUMBER_OF_DYN_DID];/* For 0x2C */

#endif

#if(DCM_SERVICE_2E_ENABLED==STD_ON)

extern ROM_CONST Dcm_2E_ServiceInfoType gDcmDsdSubService_2E[NUMBER_OF_WRITE_DID];/* For 0x2E */

#endif

#if(DCM_SERVICE_2F_ENABLED==STD_ON)

extern ROM_CONST Dcm_2F_ServiceInfoType gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID];/* For 0x2F */

#endif

#if(DCM_SERVICE_31_ENABLED==STD_ON)

extern ROM_CONST DcmDspRoutine DcmDspRoutineIdentifierTable_31[NUMBER_OF_RID];/* For 0x31 */

#endif

#if(DCM_SERVICE_3D_ENABLED==STD_ON)

extern ROM_CONST DcmDspWriteMemoryRangeInfo gDcmDspWriteMemoryRangeInfo_3D[NUMBER_OF_WRITE_ADDRESS_SEG];

#endif
#endif


/******************************************************* End  ******************************************************/
