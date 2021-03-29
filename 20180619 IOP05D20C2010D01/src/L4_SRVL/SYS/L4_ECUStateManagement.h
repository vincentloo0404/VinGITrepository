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
#ifndef L4_ECUSTATEMANAGEMENT_H
#define L4_ECUSTATEMANAGEMENT_H  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "L2_MCAL.h"

#include "L3_ECAL.h"

#include "L4_SRVL.h"
#include "L4_ScheduleManagement.h"

#include "L4_FaultManager.h"
/*
#include "L5_APPL.h"
#include "L5_PowerSteeringCtrl.h"
*/

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
/*Enum for ECU state*/
typedef enum
{
	PowerOff_State = 0,
	CodeInit_State,
	WarmInit_State,
    Run_State,
    SoftDisable_State,
    HardDisable_State,
	CtrlDisable_State,
	ShutDown_State,
    SystemTest_State
}ECU_State_enu;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern ECU_State_enu L4_S_ECUState_Now_G_Enu;
extern ECU_State_enu L4_S_ECUState_Pre_G_Enu;

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void ECUStateManagement_L4_ColdInit(void);
extern void ECUStateManagement_L4_WarmInit(void);
extern void ECUStateManagement_L4_Per(void);
extern void ECUStartUp_L4_Ctrl(void);
extern void ECUShutDown_L4_Ctrl(void);

#endif
/*End of L4_ECUStateManagement.h file*/
