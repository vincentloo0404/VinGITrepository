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
#include "L3_ECAL.h"

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

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3ECAL_START_SEC_VAR
#include "MemMap.h"

/*System timer counter for Task management*/

#define d_L3ECAL_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3ECAL_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************
*
*   Function:     ECU_L3_Init
*
*   Description:  This function is use to Initial the ECU system
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void ECU_L3_Init(void)
{
     /* eeprom data */
     EmEep_L3_Init();

	 /* adc signal sample init */
	 AdcSigSample_L3_Init();
	 SensorVoltageAbstract_L3_Init();
	 VoltSignalAbstract_L3_Init();

     /* calibration init */
     ccpInit();/* ccp stack init */	       

     /* init ignition key fun */
	 IgnitionSignalAbstarct_L3_Init();
     
    
     /* can com init */
     CAN_L3_Init();
     
     //SAFEPORT_CAN_L3_Init();
    

     /* temperature init */
     TemperatureAbstarct_L3_Init();
     
     /*FailSafe Initial*/
     FS_L3_EcalFailSafeInit();
     
     /*SBC UJA1076 Initial*/
     SBC_L3_Init();

     L3_CP_Init();
}
/*****************************************************************************
*
*   Function:     ECU_L3_Stop
*
*   Description:  This function is use to Stop the ECU system
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void ECU_L3_Stop(void)
{
    /*****************************************
      Predriver control pin 
    ******************************************/
	Predriver_L3_Ctrl_Off();
	Predriver_L3_INH_Off();
	
    RlyMosPower_L3_Ctrl_Off();
    PreCharge_L3_Ctrl_Off();
    
    /* discharge */
    DisCharge_L3_Ctrl_On();
}
#define d_L3ECAL_STOP_SEC_CODE
#include "MemMap.h"

#define d_L3ECAL_START_SEC_FAST_CODE
#include "MemMap.h"

#define d_L3ECAL_STOP_SEC_FAST_CODE
#include "MemMap.h"

/*End of L3_ECAL.c file*/
