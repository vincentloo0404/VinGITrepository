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
*     1.0        2014/12/20      ----    	   	N/A          Original
************************************************************************************************/
#ifndef L4_SCHEDULEMANAGEMENT_CFG_H
#define L4_SCHEDULEMANAGEMENT_CFG_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/
/*Define the Max Tasks Number*/
#define d_MaxTaskNumber_u16				   11U
/*Max system timer count value*/
#define d_SystemTimerMaxCnt_u16             8U

/*define the Initial counter for each Task*/
#define d_RunStateMonitor_InitCt_u16   26   /*Task 1*/
#define d_PowerAssistCtrl_InitCt_u16   37   /*Task 2*/
#define d_PowerAssistCtrl2_InitCt_u16  2   /*Task 3*/
#define d_MotorCtrl_InitCt_u16         4   /*Task 4*/
#define d_SignalSampling_InitCt_u16    31   /*Task 5*/
#define d_FaultManagement_InitCt_u16   21   /*Task 6*/
#define d_DTCManagement_InitCt_u16     20   /*Task 7*/
#define d_CAN_Comm_InitCt_u16          16   /*Task 8*/
#define d_UDS_ON_CAN_InitCt_u16        15   /*Task 9*/
#define d_CCP_InitCt_u16               11   /*Task 10*/
#define d_MonitorSrv_InitCt_u16        6   /*Task 11*/

/*define the Period for each Task*/
#define d_RunStateMonitor_Period_u16     40U  /*Task 1*/
#define d_PowerAssistCtrl_Period_u16     40U  /*Task 2*/
#define d_PowerAssistCtrl2_Period_u16    40U  /*Task 3*/
#define d_MotorCtrl_Period_u16            5U  /*Task 4*/
#define d_SignalSampling_Period_u16      40U  /*Task 5*/
#define d_FaultManagement_Period_u16     40U  /*Task 6*/
#define d_DTCManagement_Period_u16       40U  /*Task 7*/
#define d_CAN_Comm_Period_u16            40U  /*Task 8*/
#define d_UDS_ON_CAN_Period_u16          40U  /*Task 9*/
#define d_CCP_Period_u16                 40U  /*Task 10*/
#define d_MonitorSrv_Period_u16          40U  /*Task 11*/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/

#endif  
/*End of L4_ScheduleManagement_Cfg.h file */
