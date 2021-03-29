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
#include "L4_StopTask.h"
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
#define d_L4STOPTASK_START_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/

#define d_L4STOPTASK_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4STOPTASK_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************
*
*   Function:     FailSafeCtrl_Task_L4_Per
*
*   Description:  This function is the task for failsafe control loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 200us
*
*****************************************************************************/
void MotorCtrl_STask_L4_Per(void)
{
    AdcSigSample_L3_Per();
    //AdcSigSample_L3_Per1();
}
/*****************************************************************************
*
*   Function:     FailSafeCtrl_Task_L4_Per
*
*   Description:  This function is the task for failsafe control loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 200us
*
*****************************************************************************/
void DTCManage_STask_L4_Per(void)
{
    /*DTC control loop*/
    DTC_L4_POLLING_2ms();
}
/*****************************************************************************
*
*   Function:     FailSafeCtrl_Task_L4_Per
*
*   Description:  This function is the task for failsafe control loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 200us
*
*****************************************************************************/
void SignalSampling_STask_L4_Per(void)
{
   /* SBC */
   SBC_L3_Per();   

   /*Abstract Ignition state*/
   IgnitionSignalAbstarct_L3_Per();

   /* temperature */
   TemperatureAbstarct_L3_Per();

   /*Diagnose Battery Power*/
   FS_L3_BatVoltDiagPer();		

   /*Diagnose the Temperature input signal*/
   FS_L3_TemperatureDiagPer();
   
   /* ignition diagnostic */
   FS_L3_IgnitionVoltDiagPer();
}
/*****************************************************************************
*
*   Function:     FailSafeCtrl_Task_L4_Per
*
*   Description:  This function is the task for failsafe control loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 200us
*
*****************************************************************************/
void RunStateMonitor_STask_L4_Per(void)
{
	/*ECU system shut down*/
	ECUShutDown_L4_Ctrl();
}
/*****************************************************************************
*
*   Function:     FailSafeCtrl_Task_L4_Per
*
*   Description:  This function is the task for failsafe control loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 200us
*
*****************************************************************************/
void FaultManage_STask_L4_Per(void)
{
	/* FailSafe control loop */
	FM_L4_ShutDown();
}
/*****************************************************************************
*
*   Function:     CAN_Comm_Task_L4_Per
*
*   Description:  This function is the task for CAN Communication Loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void CAN_Comm_STask_L4_Per(void)
{
	if((L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OFF)
	&& (L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OVER2))
    {
		/*CAN Communication Loop*/
        CAN_L3_Per();
    }   
}
/*****************************************************************************
*
*   Function:     UDS_ON_CAN_Task_L4_Per
*
*   Description:  This function is the task for UDS ON CAN Loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void UDS_ON_CAN_STask_L4_Per(void)
{
   
}

/*****************************************************************************
*
*   Function:     CCP_Task_L4_Per
*
*   Description:  This function is the task for CCP Loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void CCP_STask_L4_Per(void)
{
	if((L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OFF)
	&& (L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OVER2)
	)
	{
		/*CAN CCP Loop*/
		CCP_Per();
	}
    /*Task Monitor*/
    //TaskMonitor_L4_Per(7);
}
#define d_L4STOPTASK_STOP_SEC_CODE
#include "MemMap.h"

/*End of L4_StopTask.c file*/
