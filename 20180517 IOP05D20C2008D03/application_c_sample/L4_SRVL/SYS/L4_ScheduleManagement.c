/******************************************************************************
*
* ChuangQu NewEnergy .
* (c) Copyright 2014 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     
*
* @brief    
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2014/12/20      JiaoYu    	   	N/A          Original
************************************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/
//#include "Sys_Cfg.h"

#include "L4_ScheduleManagement.h"
/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/
static void NullFunction_Task21_L4_Per(void);
static void NullFunction_Task22_L4_Per(void);

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
static uint8 timer200us = 0;
static uint8 Cnt100us   = 0;
static uint8 TaskIndex  = 0;

static PFCN_VOID_VOID L4_S_TaskFunction[13] = 
{
	&NullFunction_Task21_L4_Per,&NullFunction_Task21_L4_Per,
	&NullFunction_Task21_L4_Per,&NullFunction_Task21_L4_Per,
	&NullFunction_Task21_L4_Per,&NullFunction_Task21_L4_Per,
	&NullFunction_Task21_L4_Per,&NullFunction_Task21_L4_Per,
	&NullFunction_Task21_L4_Per,&NullFunction_Task21_L4_Per,		
};
static PFCN_VOID_VOID L4_S_DcDcTaskFunction = &NullFunction_Task22_L4_Per;

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/
volatile uint32 FunMaxTimer_u32p06 = 0;
volatile uint32 FunMinTimer_u32p06 = 0xFFFFFFFF;
volatile uint32 FunRunTimer_u32p06 = 0;
volatile uint32 diff = 0;


volatile uint16 FunMaxTimer_u16p06 = 0;
volatile uint16 FunMinTimer_u16p06 = 0xFFFF;
volatile uint16 FunRunTimer_u16p06 = 0;

#define d_L4SCHEDULEMANAGEMENT_START_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
/*Task Array list*/
TaskType_Str L4_S_Task_G_Str[d_MaxTaskNumber_u16];


#define d_L4SCHEDULEMANAGEMENT_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4SCHEDULEMANAGEMENT_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************
*
*   Function:     NullFunction_Task2_l4_Per
*
*   Description:  This function is Task for Null operation ,used to bypass
*                 Normal control function
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void NullFunction_Task21_L4_Per(void)
{

}
/*****************************************************************************
*
*   Function:     NullFunction_Task2_l4_Per
*
*   Description:  This function is Task for Null operation ,used to bypass
*                 Normal control function
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void NullFunction_Task22_L4_Per(void)
{

}

/*****************************************************************************
*
*   Function:     ScheduleManagement_L4_Init
*
*   Description:  This function is use to Initial the Task Schedule
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void ScheduleManagement_L4_ColdInit(void)
{
    timer200us = 0;
    TaskIndex  = 0;

	L4_S_TaskFunction[0] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[1] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[2] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[3] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[4] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[5] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[6] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[7] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[8] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[9] = &NullFunction_Task21_L4_Per;
	
	L4_S_DcDcTaskFunction = &NullFunction_Task22_L4_Per;
}
/*****************************************************************************
*
*   Function:     ScheduleManagement_L4_Init
*
*   Description:  This function is use to Initial the Task Schedule
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void ScheduleManagement_L4_WarmInit(void)
{
	L4_S_TaskFunction[0] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[1] = &CAN_Comm_WTask_L4_Per;
	L4_S_TaskFunction[2] = &CCP_WTask_L4_Per;
	L4_S_TaskFunction[3] = &app_stateflow_task_L5_Per;//add by ych
	L4_S_TaskFunction[4] = &SignalSampling_WTask_L4_Per;
	L4_S_TaskFunction[5] = &sys_diag_task_L5_Per;
	L4_S_TaskFunction[6] = &DTCManage_WTask_L4_Per;
	L4_S_TaskFunction[7] = &UDS_ON_CAN_WTask_L4_Per;
	L4_S_TaskFunction[8] = &FaultManage_WTask_L4_Per;
	L4_S_TaskFunction[9] = &RunStateMonitor_WTask_L4_Per;
	
	L4_S_DcDcTaskFunction = &DcDc_Task_L4_Per;
}
/*****************************************************************************
*
*   Function:     ScheduleManagement_L4_Init
*
*   Description:  This function is use to Initial the Task Schedule
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void ScheduleManagement_L4_RunInit(void)
{
	L4_S_TaskFunction[0] = &PowerAssistCtrl1_RTask_L4_Per;
	L4_S_TaskFunction[1] = &CAN_Comm_RTask_L4_Per;
	L4_S_TaskFunction[2] = &CCP_RTask_L4_Per;
	L4_S_TaskFunction[3] = &PowerAssistCtrl2_RTask_L4_Per;
	L4_S_TaskFunction[4] = &FaultManage_RTask_L4_Per;
	L4_S_TaskFunction[5] = &PowerAssistCtrl1_RTask_L4_Per;
	L4_S_TaskFunction[6] = &DTCManage_RTask_L4_Per;
	L4_S_TaskFunction[7] = &UDS_ON_CAN_RTask_L4_Per;
	L4_S_TaskFunction[8] = &SignalSampling_RTask_L4_Per;
	L4_S_TaskFunction[9] = &RunStateMonitor_RTask_L4_Per;

	L4_S_DcDcTaskFunction = &MotorCtrl_RTask_L4_Per;
}
/*****************************************************************************
*
*   Function:     ScheduleManagement_L4_Init
*
*   Description:  This function is use to Initial the Task Schedule
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void ScheduleManagement_L4_StopInit(void)
{
	L4_S_TaskFunction[0] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[1] = &CAN_Comm_STask_L4_Per;
	L4_S_TaskFunction[2] = &CCP_STask_L4_Per;
	L4_S_TaskFunction[3] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[4] = &SignalSampling_STask_L4_Per;
	L4_S_TaskFunction[5] = &NullFunction_Task21_L4_Per;
	L4_S_TaskFunction[6] = &DTCManage_STask_L4_Per;
	L4_S_TaskFunction[7] = &UDS_ON_CAN_STask_L4_Per;
	L4_S_TaskFunction[8] = &FaultManage_STask_L4_Per;
	L4_S_TaskFunction[9] = &RunStateMonitor_STask_L4_Per;
	
	L4_S_DcDcTaskFunction = &MotorCtrl_STask_L4_Per;
}
/*****************************************************************************
*
*   Function:     ScheduleManagement_L4_Per
*
*   Description:  This function is use to Manage the Task Schedule
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 50us
*
*****************************************************************************/
void ScheduleManagement_L4_Per(void)
{
	for(;;)
	{
	   if(timer200us != 0)
	   {
	   	  timer200us = 0;
	   	  
	   	  /* task index */
	   	  if(TaskIndex >= 10)
	   	  {
	   	  	TaskIndex = 0;
	   	  }
	   	  
	   	  /* background task */
	   	  L4_S_TaskFunction[TaskIndex]();
	   	  
	   	  TaskIndex++;
	   }
	   else
	   {
	   	
	   }
	}
}
/*****************************************************************************
*
*   Function:     ScheduleManagement_L4_Per
*
*   Description:  This function is use to Manage the Task Schedule
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 50us
*
*****************************************************************************/
void pFUN_mEDMA_IRQ11_CH0_Hook(void)
{
	 L4_S_DcDcTaskFunction();
	
	 if((++Cnt100us) >= 10)
	 {
	    Cnt100us = 0;

	    //A5_OUT = ~A5_OUT;
	    
	    timer200us++;
	 }
	 else
	 {
	 }

}
#define d_L4SCHEDULEMANAGEMENT_STOP_SEC_CODE
#include "MemMap.h"

/*End of L4_ScheduleManagement.c file*/