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
#ifndef L4_RUNTASK
#define L4_RUNTASK  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "m_ETimer_Drv.h"

#include "L4_ScheduleManagement_Cfg.h"
#include "L3_ECAL.h"
//#include "L3_MotorPositionSignal.h"
//#include "L3_MotorSpeedSignal.h"
#include "L3_IgnitionSignal.h"
#include "L3_TemperatureSignal.h"
#include "L3_SensorVoltageSignal.h"
#include "L3_EmEep.h"
#include "L3_ECUPowerSignal.h"

#include "L3_CAN.h"

//#include "L5_MotorCtrl.h"
//#include "L5_Assist.h"

/* diagnostic */
#include "L3_BattVolt_Diag.h"
#include "L3_SensorVolt_Diag.h"
#include "L3_Temperature_Diag.h"
#include "L4_ECUStateManagement.h"
#include "L4_FaultManager.h"
#include "L4_DTC.h"

#if 0

#include "L4_MonitorSrv.h"

#endif

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void Monitor_Service_RTask_L4_Per(void);
extern void PowerAssistCtrl1_RTask_L4_Per(void);
extern void PowerAssistCtrl2_RTask_L4_Per(void);
extern void MotorCtrl_RTask_L4_Per(void);
extern void EepromManagement_RTask_L4_Per(void);
extern void DTCManage_RTask_L4_Per(void);
extern void SignalSampling_RTask_L4_Per(void);
extern void RunStateMonitor_RTask_L4_Per(void);
extern void FaultManage_RTask_L4_Per(void);
extern void CAN_Comm_RTask_L4_Per(void);
extern void UDS_ON_CAN_RTask_L4_Per(void);
extern void CCP_RTask_L4_Per(void);

#endif
/*End of L4_ScheduleManagement.h file*/
