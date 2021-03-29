/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm_Lcfg.c  
*
* @brief  Application Timer-Paramater define and DID configurable.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/25    CODER1     N/A           Original
*     
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/  
#include "Dcm.h"
#include "Dcm_Cfg.h"
#include "Dcm_Types.h"

/*****************************************************************************************                           
 *   config tables                
 *****************************************************************************************/
/*----------------------------------------------------------------------------------------
    &&~ S3Server Timer
-----------------------------------------------------------------------------------------*/  
ROM_CONST uint32 gDcmDspNonDefaultSessionS3Server = 5000;/* Unit:ms */

/*----------------------------------------------------------------------------------------
    &&~ Session Typs Parameter Config
-----------------------------------------------------------------------------------------*/ 
ROM_CONST DcmDspSessionRow gDcmDspSessionRow[KIND_OF_SESSION] = 
{
  { DCM_NO_BOOT, DCM_DEFAULT_SESSION|DCM_EXTENDED_DIAGNOSTIC_SESSION, 50, 5000 },/* Do not change DCM_DEFAULT_SESSION|DCM_EXTENDED_DIAGNOSTIC_SESSION into 4! */

  { DCM_NO_BOOT, 2, 50, 5000 },        /* 2 means being supported only in extended session  */

  { DCM_NO_BOOT, 2, 50, 5000 }         /* 2 means being supported only in extended session  */
};

/*----------------------------------------------------------------------------------------
    &&~ Parameter for 27 service Config
-----------------------------------------------------------------------------------------*/ 
#if(DCM_SERVICE_27_ENABLED==STD_ON)

ROM_CONST DcmDspSecurityRow gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL]= 
{
  { 10000, 10000, SECURITY_SEED_SIZE, DCM_SEC_LEV_L1, 3, SECURITY_SEED_SIZE },/* For DID write and memory read/write */
};

#endif

/*----------------------------------------------------------------------------------------
    &&~ DID Parameter for 22 service Config
-----------------------------------------------------------------------------------------*/ 
#if(DCM_SERVICE_22_ENABLED==STD_ON)

ROM_CONST uint16 DcmDspMaxDidToRead= 1;/* the max DID number in a single request of 22hex service.*/

ROM_CONST Dcm_22_ServiceInfoType gDcmDsdSubService_22[NUMBER_OF_READ_DID]= 
{
  { 0xF187, 1, DID_F187_LEN, App_ReadF187, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0xF18A, 1, DID_F18A_LEN, App_ReadF18A, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0xF18B, 1, DID_F18B_LEN, App_ReadF18B, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0xF18C, 1, DID_F18C_LEN, App_ReadF18C, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0xF190, 1, DID_F190_LEN, App_ReadF190, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0xF193, 1, DID_F193_LEN, App_ReadF193, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0xF195, 1, DID_F195_LEN, App_ReadF195, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x0100, 1, DID_0100_LEN, App_Read0100, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },
    
  { 0xF010, 1, DID_F010_LEN, App_ReadF010, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE }  
  #if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
	,
  { 0xF197, 1, DID_F197_LEN, App_ReadF197, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C00, 1, DID_1C00_LEN, App_Read1C00, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C01, 1, DID_1C01_LEN, App_Read1C01, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C02, 1, DID_1C02_LEN, App_Read1C02, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C03, 1, DID_1C03_LEN, App_Read1C03, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C04, 1, DID_1C04_LEN, App_Read1C04, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },
    
  { 0x1C05, 1, DID_1C05_LEN, App_Read1C05, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE }  
  #endif  
    
};

#endif



/*----------------------------------------------------------------------------------------
    &&~ DID Parameter for 2E service Config
-----------------------------------------------------------------------------------------*/ 

/**[only NOTE]
the following context actually in Dcm_Cfg.h, 
<NUMBER_OF_WRITE_DID   9     20130314,add F187,debug.>
finally the number is only indicate those DIDs(be written) can be supported in default session
[only NOTE]**/

#if(DCM_SERVICE_2E_ENABLED==STD_ON)

/*the following config is only for debug. so not set securityaccess limit.*/
ROM_CONST Dcm_2E_ServiceInfoType gDcmDsdSubService_2E[NUMBER_OF_WRITE_DID] = 
{
  { 0xF187, 1, DID_F187_LEN, App_WriteF187, DCM_SEC_LEV_L1, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED }, 
          
  { 0xF18A, 1, DID_F18A_LEN, App_WriteF18A, DCM_SEC_LEV_LOCK, EXTENDED_SEESION_HANDLE, 
    PHYSICAL_REQ_SUPPORTED },  
    
  { 0xF18B, 1, DID_F18B_LEN, App_WriteF18B, DCM_SEC_LEV_LOCK, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },  
    
  { 0xF18C, 1, DID_F18C_LEN, App_WriteF18C, DCM_SEC_LEV_LOCK, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },
    
  { 0xF190, 1, DID_F190_LEN, App_WriteF190, DCM_SEC_LEV_L1,EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },  
    
  { 0xF193, 1, DID_F193_LEN, App_WriteF193, DCM_SEC_LEV_LOCK, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },
    
  { 0xF195, 1, DID_F195_LEN, App_WriteF195, DCM_SEC_LEV_LOCK, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },

  { 0x0100, 1, DID_0100_LEN, App_Write0100, DCM_SEC_LEV_L1, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },
    
  { 0xF010, 1, DID_F010_LEN, App_WriteF010, DCM_SEC_LEV_L1, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED }
    #if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
	,
  { 0xF197, 1, DID_F197_LEN, App_WriteF197, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C00, 1, DID_1C00_LEN, App_Write1C00, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C01, 1, DID_1C01_LEN, App_Write1C01, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C02, 1, DID_1C02_LEN, App_Write1C02, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C03, 1, DID_1C03_LEN, App_Write1C03, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },

  { 0x1C04, 1, DID_1C04_LEN, App_Write1C04, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE },
    
  { 0x1C05, 1, DID_1C05_LEN, App_Write1C05, DCM_SEC_LEV_LOCK,
    DEFAULT_AND_EXTENDED_SEESION_HANDLE }  
  #endif
};

#endif


/*----------------------------------------------------------------------------------------
    &&~ DID Parameter for 31 service Config
-----------------------------------------------------------------------------------------*/ 


#if(DCM_SERVICE_31_ENABLED==STD_ON)

/*the following config is only for debug. so not set securityaccess limit.*/
ROM_CONST DcmDspRoutine DcmDspRoutineIdentifierTable_31[NUMBER_OF_RID] = 
{0
/*
  { 0xF187, 1, DID_F187_LEN, App_WriteF187, DCM_SEC_LEV_L2, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },
    */ 
};

#endif


/*----------------------------------------------------------------------------------------
    &&~ DID Parameter for 2F service Config
-----------------------------------------------------------------------------------------*/ 


#if(DCM_SERVICE_2F_ENABLED==STD_ON)

/*the following config is only for debug. so not set securityaccess limit.*/
ROM_CONST Dcm_2F_ServiceInfoType gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID] = 
{
	{
		0x4C00,DCM_SEC_LEV_L1,EXTENDED_SEESION_HANDLE,PHYSICAL_REQ_SUPPORTED,{1,0,0},
		#if(DCM_DSP_DATA_USE_PORT==UseFnc)
			App_2F_4C00_ReturnControlToEcuFnc,
			App_2F_4C00_ResetToDefaultFnc,
			App_2F_4C00_FreezeCurrentStateFnc,
			App_2F_4C00_ShortTermAdjustmentFnc,
		#endif
		DCM_NULL
	}
/*
  { 0xF187, 1, DID_F187_LEN, App_WriteF187, DCM_SEC_LEV_L2, EXTENDED_SEESION_HANDLE,
    PHYSICAL_REQ_SUPPORTED },
    */ 
};

#endif

/******************************************************* End  ******************************************************/
