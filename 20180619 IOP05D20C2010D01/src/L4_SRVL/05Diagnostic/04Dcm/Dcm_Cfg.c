/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm_Cfg.c  
*
* @brief  Service config,includes its subfunction...
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
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/ 

#include "Dcm.h"


/************************************************************************************
*              Supported UDS services config table (ROM)
*************************************************************************************/

static ROM_CONST uint8 gSidMap_1[72]=
{
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*7*/
    
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*15*/  /*First two lines for OBD */
 /* 0x10 0x11           0x14                */
    0x00,0x01,0xFF,0xFF,0x02,0xFF,0xFF,0xFF,/*23*/
 /*      0x19                               */
    0xFF,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*31*/
 /*           0x22                     0x27 */
    0xFF,0xFF,0x04,0xFF,0xFF,0xFF,0xFF,0x05,/*39*/
 /* 0x28                          0x2E 0x2F     */
    0x06,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x08,/*47*/
 /*      0x31                                  */
    0xFF,0x09,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*55*/
 /*                               0x3E      */
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0A,0xFF,/*63*/
 /*                          0x85           */
    0xFF,0xFF,0xFF,0xFF,0xFF,0x0B,0xFF,0xFF /*71*/    
};


/************************************************************************************
*               Supported UDS services Attributes config table (ROM)
*************************************************************************************/
static ROM_CONST DcmDsdServiceTable gServiceTable_1[DCM_NUM_OF_SERVICE]=
{
    #if(DCM_SERVICE_10_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_DiagnosticSessionControl,        UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE}, 0u,                      (NUM_OF_10_SUB_FUNCTION-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x10 */
    #endif
    
    #if(DCM_SERVICE_11_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_EcuReset,                        UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE}, NUM_OF_10_SUB_FUNCTION,  (NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                            NUM_OF_11_SUB_FUNCTION-1u),PHYSICAL_REQ_SUPPORTED},/* 0x11 */
    #endif
    
    #if(DCM_SERVICE_14_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ClearDiagnosticInformation,      UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x14 */
    #endif
    
    #if(DCM_SERVICE_19_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ReadDTCInformation,              UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE}, (NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                   NUM_OF_11_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                            NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                            NUM_OF_19_SUB_FUNCTION-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x19 */
    #endif
   
    #if(DCM_SERVICE_22_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ReadDataByIdentifier,            UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_REQ_SUPPORTED},/* 0x22 */
    #endif
    
    #if(DCM_SERVICE_23_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ReadMemoryByAddress,             UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x23 */
    #endif
    #if(DCM_SERVICE_24_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ReadScalingDataByIdentifier,     UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x24 */
    #endif
    
    #if(DCM_SERVICE_27_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_SecurityAccess,                  UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_19_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_27_SUB_FUNCTION-1u),PHYSICAL_REQ_SUPPORTED},/* 0x27 */
    #endif
    
    #if(DCM_SERVICE_28_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_CommunicationControl,            UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE},            (NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_27_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_28_SUB_FUNCTION-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x28 */
    #endif
    
    #if(DCM_SERVICE_2A_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ReadDataByPeriodicIdentifier,    UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x2A */
    #endif
    
    #if(DCM_SERVICE_2C_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_DynamicallyDefinedDataIdentifier,UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_28_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_2C_SUB_FUNCTION-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x2C */
    #endif
    
    #if(DCM_SERVICE_2E_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_WriteDataByIdentifier,           UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_L1,EXTENDED_SEESION_HANDLE/*DEFAULT_AND_EXTENDED_SEESION_HANDLE*/},            (DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_REQ_SUPPORTED},/* 0x2E */
    #endif
    
    #if(DCM_SERVICE_2F_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_InputOutputControlByIdentifier,  UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE},            (DCM_NUM_OF_SUB_SERVICE-1),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_REQ_SUPPORTED},               /* 0x2F */
    #endif
    
    #if(DCM_SERVICE_31_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_RoutineControl,                  UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,DCM_SEC_LEV_LOCK},            (NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_2C_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_2C_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_31_SUB_FUNCTION-1u),PHYSICAL_REQ_SUPPORTED},               /* 0x31 */
    #endif
    
    #if(DCM_SERVICE_3D_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_WriteMemoryByAddress,            UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE},            (DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x3D */
    #endif
    
    #if(DCM_SERVICE_3E_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_TesterPresent,                   UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_2C_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_31_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_2C_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_31_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_3E_SUB_FUNCTION-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x3E */
    #endif
    
    #if(DCM_SERVICE_85_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ControlDTCSetting,               UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE},            (NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_2C_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_31_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_3E_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_2C_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_31_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_3E_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_85_SUB_FUNCTION-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x85 */
    #endif
    
    #if(DCM_SERVICE_86_ENABLED==STD_ON)
    { 1,{DspInternal_Uds_ResponseOnEvent,                 UDS_SERVICE_WITH_SUB_FUNCTION,   DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE},            (NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_2C_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_31_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_3E_SUB_FUNCTION+\
                                                                                                                                                  NUM_OF_85_SUB_FUNCTION),(NUM_OF_10_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_11_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_19_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_27_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_28_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_2C_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_31_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_3E_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_85_SUB_FUNCTION+\
                                                                                                                                                                           NUM_OF_86_SUB_FUNCTION-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},/* 0x86 */
    #endif
    
    { 1,{DCM_NULL,                                        UDS_SERVICE_WITHOUT_SUB_FUNCTION,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE},(DCM_NUM_OF_SUB_SERVICE-1u),(DCM_NUM_OF_SUB_SERVICE-1u),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED} /* 0xFF */
}; 


/********************************************************************************************************************
*               Global Variables definition (ROM)
*********************************************************************************************************************/
ROM_CONST uint8* const gCurrentSidMap = gSidMap_1;
ROM_CONST DcmDsdServiceTable* const gCurrentDcmDsdServiceTable=gServiceTable_1;
ROM_CONST uint32 gCurentDcmDsdServiceTableSize=DCM_NUM_OF_SERVICE;


/********************************************************************************************************************
*               Supported Subfunction of UDS services Attributes config table (ROM)
*********************************************************************************************************************/
ROM_CONST DcmDsdSubService gDcmDsdSubService[DCM_NUM_OF_SUB_SERVICE]=
{                                                           
  #if(DCM_SERVICE_10_ENABLED==STD_ON)
  #if(DCM_SERVICE_10_DefaultSession==STD_ON)
  {(EcucSubFunctionNameDef)App_DefaultSession,             App_DefaultSessionPost,           DCM_DEFAULT_SESSION,                   SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 00,0x10 01 */
  #endif
  
  #if(DCM_SERVICE_10_ProgramSession==STD_ON)
  {(EcucSubFunctionNameDef)App_ProgramSession,             App_ProgramSessionPost,           DCM_PROGRAMMING_SESSION,               SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 01,0x10 02 */
  #endif
  
  #if(DCM_SERVICE_10_ExtendedSession==STD_ON)
  {(EcucSubFunctionNameDef)App_ExtendedSession,            App_ExtendedSessionPost,          DCM_EXTENDED_DIAGNOSTIC_SESSION,       SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 02,0x10 03 */
  #endif
  #endif
  
  #if(DCM_SERVICE_11_ENABLED==STD_ON)
  #if(DCM_SERVICE_11_HardReset==STD_ON)
  {(EcucSubFunctionNameDef)App_HardReset,                  App_HardResetPost,                DCM_HARD_RESET,                        SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_REQ_SUPPORTED}, /* 03,0x11 01 */
  #endif
  
  #if(DCM_SERVICE_11_KeyOffOnReset==STD_ON)
  {App_KeyOffOnReset,                                      App_KeyOffOnResetPost,            DCM_KEY_ON_OFF_RESET,                  SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 04,0x11 02 */
  #endif
  
  #if(DCM_SERVICE_11_SoftReset==STD_ON)
  {(EcucSubFunctionNameDef)App_SoftReset,                  App_SoftResetPost,                DCM_SOFT_RESET,                        SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 05,0x11 03 */
  #endif
  
  #if(DCM_SERVICE_11_EnableRapidPowerShutDown==STD_ON)
  {App_EnableRapidPowerShutDown,                           App_EnableRapidPowerShutDownPost, DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET, SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 06,0x11 04 */
  #endif
  
  #if(DCM_SERVICE_11_DisableRapidPowerShutDown==STD_ON)
  {App_DisableRapidPowerShutDown,                          App_DisableRapidPowerShutDownPost,DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET,SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 07,0x11 05 */
  #endif
  #endif
  
  #if(DCM_SERVICE_19_ENABLED==STD_ON)                                                                                                                
  #if(reportNumberOfDTCByStatusMask==STD_ON)
  {App_ReportNumberOfDTCByStatusMask,                     DCM_NULL,                         0x01,                                  SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 08,0x19 01 */
  #endif
  
  #if(reportDTCByStatusMask==STD_ON)
  {App_ReportDTCByStatusMask,                             DCM_NULL,                         0x02,                                  SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 09,0x19 02 */
  #endif
  
  #if(reportDTCSnapshotIdentification==STD_ON)
  {App_ReportDTCSnapshotIdentification,                   DCM_NULL,                         0x03,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 10,0x19 03 */
  #endif
  
  #if(reportDTCSnapshotRecordByDTCNumber==STD_ON)
  {App_ReportDTCSnapshotRecordByDTCNumber,                DCM_NULL,                         0x04,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 11,0x19 04 */
  #endif
  
  #if(reportDTCSnapshotRecordByRecordNumber==STD_ON)
  {App_ReportDTCSnapshotRecordByRecordNumber,             DCM_NULL,                         0x05,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 12,0x19 05 */
  #endif
  
  #if(reportDTCExtendedDataRecordByDTCNumber==STD_ON)
  {App_ReportDTCExtendedDataRecordByDTCNumber,            DCM_NULL,                         0x06,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 13,0x19 06 */
  #endif
  
  #if(reportNumberOfDTCBySeverityMaskRecord==STD_ON)
  {App_ReportNumberOfDTCBySeverityMaskRecord,             DCM_NULL,                         0x07,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 14,0x19 07 */
  #endif
  
  #if(reportDTCBySeverityMaskRecord==STD_ON)
  {App_ReportDTCBySeverityMaskRecord,                     DCM_NULL,                         0x08,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 15,0x19 08 */
  #endif
  
  #if(reportSeverityInformationOfDTC==STD_ON)
  {App_ReportSeverityInformationOfDTC,                    DCM_NULL,                         0x09,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 16,0x19 09 */
  #endif
  
  #if(reportSupportedDTC==STD_ON)
  {App_ReportSupportedDTC,        DCM_NULL,                         0x0A,                                  SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 17,0x19 0A */
  #endif
  
  #if(reportFirstTestFailedDTC==STD_ON)
  {App_ReportFirstTestFailedDTC,                          DCM_NULL,                         0x0B,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 18,0x19 0B */
  #endif
  
  #if(reportFirstConfirmedDTC==STD_ON)
  {App_ReportFirstConfirmedDTC,                           DCM_NULL,                         0x0C,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 19,0x19 0C */
  #endif
  
  #if(reportMostRecentTestFailedDTC==STD_ON)
  {App_ReportMostRecentTestFailedDTC,                     DCM_NULL,                         0x0D,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 20,0x19 0D */
  #endif
  
  #if(reportMostRecentConfirmedDTC==STD_ON)
  {App_ReportMostRecentConfirmedDTC,                      DCM_NULL,                         0x0E,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 21,0x19 0E */
  #endif
  
  #if(reportMirrorMemoryDTCByStatusMask==STD_ON)
  {App_ReportMirrorMemoryDTCByStatusMask,                 DCM_NULL,                         0x0F,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 22,0x19 0F */
  #endif
  
  #if(reportMirrorMemoryDTCExtendedDataRecordByDTCNumber==STD_ON)
  {App_ReportMirrorMemoryDTCExtendedDataRecordByDTCNumber,DCM_NULL,                         0x10,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 23,0x19 10 */
  #endif
  
  #if(reportNumberOfMirrorMemoryDTCByStatusMask==STD_ON)
  {App_ReportNumberOfMirrorMemoryDTCByStatusMask,         DCM_NULL,                         0x11,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 24,0x19 11 */
  #endif
  
  #if(reportNumberOfEmissionsRelatedOBDDTCByStatusMask==STD_ON)
  {App_ReportNumberOfEmissionsRelatedOBDDTCByStatusMask,  DCM_NULL,                         0x12,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 25,0x19 12 */
  #endif
  
  #if(reportEmissionsRelatedOBDDTCByStatusMask==STD_ON)
  {App_ReportEmissionsRelatedOBDDTCByStatusMask,          DCM_NULL,                         0x13,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 26,0x19 13 */
  #endif
  #endif
  
  #if(DCM_SERVICE_27_ENABLED==STD_ON)                                                                                                                                                                             
  
  #if(DCM_SERVICE_27_GetSeed_L1==STD_ON)
  {(EcucSubFunctionNameDef)App_GetSeed_L1,                DCM_NULL,                         REQUEST_SEED_L1,                       SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_REQ_SUPPORTED}, /* 27,0x27 01 */
  #endif
  
  #if(DCM_SERVICE_27_CompareKey_L1==STD_ON)
  {(EcucSubFunctionNameDef)App_CompareKey_L1,             DCM_NULL,                         SEND_KEY_L1,                           SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_REQ_SUPPORTED}, /* 28,0x27 02 */
  #endif
  
  #if(DCM_SERVICE_27_GetSeed_L2==STD_ON)
  {App_GetSeed_L2,                                        DCM_NULL,                         REQUEST_SEED_L2,                       SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_REQ_SUPPORTED}, /* 29,0x27 03 */
  #endif
  
  #if(DCM_SERVICE_27_CompareKey_L2==STD_ON)
  {App_CompareKey_L2,                                     DCM_NULL,                         SEND_KEY_L2,                           SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_REQ_SUPPORTED}, /* 30,0x27 04 */ 
  #endif
  
  #if(DCM_SERVICE_27_GetSeed_L3==STD_ON)
  {App_GetSeed_L3,                                        DCM_NULL,                         REQUEST_SEED_L3,                       SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 31,0x27 05 */
  #endif
  
  #if(DCM_SERVICE_27_CompareKey_L3==STD_ON)
  {App_CompareKey_L3,                                     DCM_NULL,                         SEND_KEY_L3,                           SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 32,0x27 06 */
  #endif
  #endif
  
  #if(DCM_SERVICE_28_ENABLED==STD_ON)
  #if(DCM_SERVICE_28_EnableRxAndTx==STD_ON)
  {(EcucSubFunctionNameDef)App_EnableRxAndTx,             DCM_NULL,                         ENABLE_RX_AND_TX,                      SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 33,0x28 00 */ 
  #endif
  
  #if(DCM_SERVICE_28_EnableRxAndDisableTx==STD_ON)
  {App_EnableRxAndDisableTx,                              DCM_NULL,                         ENBALE_RX_AND_DISABLE_TX,              SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 34,0x28 01 */
  #endif
  
  #if(DCM_SERVICE_28_DisableRxAndEnableTx==STD_ON)
  {App_DisableRxAndEnableTx,                              DCM_NULL,                         DISABLE_RX_AND_ENBALE_TX,              SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 35,0x28 02 */
  #endif
  
  #if(DCM_SERVICE_28_DisableRxAndTx==STD_ON)
  {(EcucSubFunctionNameDef)App_DisableRxAndTx,            DCM_NULL,                         DISABLE_RX_AND_TX,                     SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 36,0x28 03 */
  #endif
  #endif
  
  #if(DCM_SERVICE_2C_ENABLED==STD_ON)
  #if(DCM_SERVICE_2C_defineByIdentifier==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x01u,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 37,0x2C 01 */
  #endif
  
  #if(DCM_SERVICE_2C_defineByMemoryAddress==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x02u,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 38,0x2C 02 */
  #endif
  
  #if(DCM_SERVICE_2C_clearDynamicallyDefinedDataIdentifier==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x03u,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 39,0x2C 03 */
  #endif
  #endif
  
  #if(DCM_SERVICE_31_ENABLED==STD_ON)
  #if(DCM_SERVICE_31_startRoutine==STD_ON)
  {(EcucSubFunctionNameDef)App_31_startRoutine,           DCM_NULL,                         START_ROUTINE,                         SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,               PHYSICAL_REQ_SUPPORTED},                 /* 40,0x31 01 */
  #endif
  
  #if(DCM_SERVICE_31_stopRoutine==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         STOP_ROUTINE,                          SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_L2,EXTENDED_SEESION_HANDLE,               PHYSICAL_REQ_SUPPORTED},                 /* 41,0x31 02 */ 
  #endif
  
  #if(DCM_SERVICE_31_requestRoutineResults==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         REQUEST_ROUTINE_RESULT,                SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_L2,EXTENDED_SEESION_HANDLE,               PHYSICAL_REQ_SUPPORTED},                 /* 42,0x31 03 */ 
  #endif
  #endif
  
  #if(DCM_SERVICE_3E_ENABLED==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         ZERO_SUB_FUNCTION,                     SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},  /* 43,0x3E 00 */
  #endif
  
  #if(DCM_SERVICE_85_ENABLED==STD_ON)
  #if(DCM_SERVICE_85_DTCRecordOn==STD_ON)
  {(EcucSubFunctionNameDef)App_DTCRecordOn,               DCM_NULL,                         DTC_RECORD_ON,                         SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},  /* 44,0x85 01 */
  #endif
  
  #if(DCM_SERVICE_85_DTCRecordOff==STD_ON)
  {(EcucSubFunctionNameDef)App_DTCRecordOff,              DCM_NULL,                         DTC_RECORD_OFF,                        SUB_FUNCTION_SUPPORTED,    DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},  /* 45,0x85 02 */
  #endif
  #endif
  
  #if(DCM_SERVICE_86_ENABLED==STD_ON)
  #if(DCM_SERVICE_86_stopResponseOnEvent==STD_ON) 
  {DCM_NULL,                                              DCM_NULL,                         0x00,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 46,0x86 00 */
  #endif
  
  #if(DCM_SERVICE_86_onDTCStatusChange==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x01,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 47,0x86 01 */
  #endif
  
  #if(DCM_SERVICE_86_onTimerInterrupt==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x02,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 48,0x86 02 */
  #endif
  
  #if(DCM_SERVICE_86_onChangeOfDataIdentifier==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x03,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 49,0x86 03 */
  #endif
  
  #if(DCM_SERVICE_86_reportActivatedEvents==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x04,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 50,0x86 04 */
  #endif
  
  #if(DCM_SERVICE_86_startResponseOnEvent==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x05,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 51,0x86 05 */
  #endif
  
  #if(DCM_SERVICE_86_clearResponseOnEvent==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x06,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 52,0x86 06 */
  #endif
  
  #if(DCM_SERVICE_86_onComparisonOfValues==STD_ON)
  {DCM_NULL,                                              DCM_NULL,                         0x07,                                  SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,EXTENDED_SEESION_HANDLE,            PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}, /* 53,0x86 07 */
  #endif
  #endif
  
  {DCM_NULL,                                              DCM_NULL,                         0,                                     SUB_FUNCTION_SUPPORTED,DCM_SEC_LEV_LOCK,DEFAULT_AND_EXTENDED_SEESION_HANDLE,PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED}  /* 54,0xFF */
};


/*******************************************************  End  ******************************************************/
