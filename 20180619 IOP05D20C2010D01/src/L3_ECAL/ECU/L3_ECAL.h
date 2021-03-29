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
#ifndef L3_ECAL_H
#define L3_ECAL_H  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "L3_ECUPowerSignal.h"
#include "L3_IgnitionSignal.h"
#include "L3_VoltSignal.h"


//#include "L3_MotorPositionSignal.h"
//#include "L3_MotorSpeedSignal.h"
#include "L3_TemperatureSignal.h"

#include "L3_EmEep.h"

#include "L3_EcalFailSafe.h"

#include "L3_SbcDrv.h"




/*

#include "L2_MCAL.h"

#include "L3_ECAL_Cfg.h"
#include "L3_ECU_Diagnosis.h"

#include "L3_VehicleSpeedSignal.h"
#include "L3_EngineSignal.h"
#include "L3_BatteryVoltageSignal.h"
#include "L3_MosfetVoltageSignal.h"
#include "L3_SensorVoltageSignal.h"
#include "L3_TemperatureSignal.h"
#include "L3_HandWheelPositionSignal.h"
#include "L3_HandWheelTorqueSignal.h"
#include "TorqueAndAngle.h"

#include "L3_CAN.h"
#include "L3_Monitor.h"
#include "L3_Ext_EEPROM.h"

*/
/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
/*Enum for register lock mode*/
typedef enum
{
    HardwareRst,
    SoftwareRst,
    ProgSessionRst
}ECU_SystemResetType_enu;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void ECU_L3_Init(void);
extern void SystemBaseTimers_L3_Ctrl(uint8 Ctrl);
extern void ECU_System_L3_Reset(ECU_SystemResetType_enu RST_Mode);
extern void ECU_L3_Stop(void);

#endif 
 /* End of L3_ECAL.h file */
