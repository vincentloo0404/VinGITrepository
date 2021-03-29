/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @Filename:  dDiagScheduEntry.h     
*
* @brief      This file defines the entry of DiagnosticTask.             
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2013/8/30     CODER1       N/A            Original
*     
************************************************************************************************/

#ifndef D_DIAG_SCAHEDU_ENTRY_H
#define D_DIAG_SCAHEDU_ENTRY_H


#ifdef 	D_DIAG_SCAHEDU_ENTRY_C
#define D_DIAG_SCAHEDU_ENTRY_EXT
#else
#define D_DIAG_SCAHEDU_ENTRY_EXT 	extern
#endif


/*********************************************************************************************
 *********************************************************************************************
 Include files
 *********************************************************************************************
 *********************************************************************************************/
#include   	"dDiagFaultEvent.h"
#include 	"dDiagDec.h"
#include    "DtcStatusManage.h"
#include    "App_Dcm.h"
#include    "Dcm.h"
#include    "CanTp.h"

/*******************************************************************************
 *******************************************************************************
 External Function
 *******************************************************************************
 *******************************************************************************/
D_DIAG_SCAHEDU_ENTRY_EXT void dDiag_vCommStackTask_Entry(void);
D_DIAG_SCAHEDU_ENTRY_EXT void dDiag_vDtcStrategyTask_Entry(void);
D_DIAG_SCAHEDU_ENTRY_EXT void dDiag_vInitDecisionTask_Entry(void);
D_DIAG_SCAHEDU_ENTRY_EXT void dDiag_vRuntimeDecisionTask_Entry(void);

/*******************************************************************************
 *******************************************************************************
   Config Marcos for DiagTask Schedule
 *******************************************************************************
 *******************************************************************************/
 
#define DIAG_COMSTACK_SCAHEDULE   (DCM_TASK_TIME)        /*5ms*/
#define DIAG_DTCUPDATE_SCAHEDULE  (DTC_TASK_TIME)        /*5ms*/
#define DIAG_DECISION_SCAHEDULE   (1u * TIMER_BASE)      /*1ms*/
#define DELAY_DETECT_MSG_ERR      250u                    /*ms*/



#if((DIAG_COMSTACK_SCAHEDULE != DCM_TASK_TIME) || (DIAG_COMSTACK_SCAHEDULE != CANTP_MAIN_FUNCTION_PERIOD))
#error "DIAG_COMSTACK_SCAHEDULE and DCM_TASK_TIME and CANTP_MAIN_FUNCTION_PERIOD must be equal !"
#endif

#if(DIAG_DTCUPDATE_SCAHEDULE != DTC_TASK_TIME)
#error "DIAG_DTCUPDATE_SCAHEDULE and DTC_TASK_TIME must be equal !"
#endif


#endif

/******************************************* end ***********************************************/