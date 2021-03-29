/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @Filename:  dDiagScheduEntryExt.h     
*
* @brief      This file Mask the entry of DiagnosticTask that be scheduled in App layer.             
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2013/8/30     CODER1       N/A            Original
*     
************************************************************************************************/

#ifndef D_DIAG_SCAHEDU_ENTRY_EXT_H
#define D_DIAG_SCAHEDU_ENTRY_EXT_H

/*********************************************************************************************
 *********************************************************************************************
 Include files
 *********************************************************************************************
 *********************************************************************************************/
#include   	"dDiagScheduEntry.h"

/***********************************************************************************
 ***********************************************************************************
 Macros Function
 ***********************************************************************************
 ***********************************************************************************/
 
 /* Description : CommStack task entry, called by the App layer;
 ***********************************************************************************/
#define  Schedule_Diag_ComStack_Task_Entry()       dDiag_vCommStackTask_Entry()

 /* Description : Dtc task entry, called by the App layer;
 ***********************************************************************************/
#define  Schedule_Diag_DtcStrgy_Task_Entry()       dDiag_vDtcStrategyTask_Entry()

 /* Description : (Init_Process)Fault Decision task entry, called by the App layer;
 ***********************************************************************************/
#define  Schedule_Diag_InitDec_Task_Entry()        dDiag_vInitDecisionTask_Entry()

 /* Description : (Runtime_Process)Fault Decision entry, called by the App layer;
 ***********************************************************************************/
#define  Schedule_Diag_RuntimeDec_Task_Entry()     dDiag_vRuntimeDecisionTask_Entry()

 /* Description : Dtc infomation save entry, called by shutdown state;
 ***********************************************************************************/
#define  Schedule_Diag_Save_DtcInfo_Entry()        Dtc_Save()

 /* Description : Dtc Pre-Init entry, called by the App layer;
 ***********************************************************************************/
#define  Diag_PreInit_Dtc_Entry()                  Dtc_PreInit()

 /* Description : Dtc Init entry, called by the App layer;
 ***********************************************************************************/
#define  Diag_Init_Dtc_Entry()                     Dtc_Init()

 /* Description : transport layer Init entry, called by the App layer;
 ***********************************************************************************/
#define  Diag_Init_CanTp_Entry()                   CanTp_Init(&CanTp_Cfg)

 /* Description : UDS service Init entry, called by the App layer;
 ***********************************************************************************/
#define  Diag_Init_Dcm_Entry()                     Dcm_Init(NULL_PTR)

 /* Description : EEPROM manage block Init entry, called by the App layer;
 ***********************************************************************************/
#define  Diag_Init_EEPROMforDtc_Entry()            mEEPROM_Init()

 /* Description : Fault Decision Init entry, called by the App layer;
 ***********************************************************************************/
#define  Diag_Init_Dec_Entry()                     dDiagDec_vInit()

    
			
#endif
/******************************************* end **********************************************/