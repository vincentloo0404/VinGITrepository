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
#include "L4_RunTask.h"
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
#define d_L4RUNTASK_START_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/

#define d_L4RUNTASK_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4RUNTASK_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************
*
*   Function:     Monitor_Service_Task_L4_Per
*
*   Description:  This function is the task for Monitor Service loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 400us
*
*****************************************************************************/
void Monitor_Service_RTask_L4_Per(void)
{

}
/*****************************************************************************
*
*   Function:     PowerSteeringCtrl_Task_L4_Per
*
*   Description:  This function is the task for Power Steering Control Loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void PowerAssistCtrl1_RTask_L4_Per(void)
{
}
/*****************************************************************************
*
*   Function:     PowerSteeringCtrl_Task_L4_Per
*
*   Description:  This function is the task for Power Steering Control Loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void PowerAssistCtrl2_RTask_L4_Per(void)
{

}
/*****************************************************************************
*
*   Function:     MotorCtrl_Task_L4_Per
*
*   Description:  This function is the task for Motor Control Loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 200us
*
*****************************************************************************/
void MotorCtrl_RTask_L4_Per(void)
{
   AdcSigSample_L3_Per();
  
   /* adc sample */
   AdcSigSample_L3_Per1();
   
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
void DTCManage_RTask_L4_Per(void)
{
    /*DTC control loop*/
    DTC_L4_POLLING_2ms();
}
/*****************************************************************************
*
*   Function:     SignalSampling_Task_L4_Per
*
*   Description:  This function is the task for signal sampling Loop
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void SignalSampling_RTask_L4_Per(void)
{
   /* SBC */
   SBC_L3_Per();

   /* motor speed signal abstract */
   MotorSpeedSignalAbstract_L3_Per();

   /* motor phase voltage abstract*/
   Phase_Volt_Abstarct_L3_Per1();

   /*Abstract Ignition state*/
   IgnitionSignalAbstarct_L3_Per();

   /*Abstract Ignition state*/
   VoltSignalAbstract_L3_Per();

   /* sensor voltage */
   SensorVoltageAbstract_L3_Per();

   /* HandWheel Torque abstract */
   //HwTorqueAbstarct_L3_Per();
   
   /* handwheel position abstract */
   HwAngleAbstarct_L3_Per();

   /* ignition diagnostic */
   FS_L3_IgnitionVoltDiagPer();

   /*predriver state*/
   PreDriverSignalAbstract_L3_Per();
   
   /* temperature */
   TemperatureAbstarct_L3_Per();
   
   /*Diagnose Battery Power*/
   FS_L3_BatVoltDiagPer();	
   	
   /*Diagnose Sensor Power*/
   FS_L3_SensorVoltDiagPer();  

   /*Diagnose the Temperature input signal*/
   FS_L3_TemperatureDiagPer();
   
   /* predriver diagnostic */
   FS_L3_PreDriverDiagPer();

   /* torque sensor diag */
   HwTorqueDiag_L3_Per();

    /*Phase Voltage Diagnostic*/
   FS_L3_MotorVoltDiagPer();
}
/*****************************************************************************
*
*   Function:     RunStateMonitor_Task_L4_Per
*
*   Description:  This function is the task for Running State Monitor
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void RunStateMonitor_RTask_L4_Per(void)
{
	/*Task Monitor*/
	//TaskMonitor_L4_Per(13);
	/*ECU state management*/
    ECUStateManagement_L4_Per();
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
void FaultManage_RTask_L4_Per(void)
{
//	FS_L3_EcuDiagPer();	
    /* FailSafe control loop */
    FM_L4_Per();
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
void CAN_Comm_RTask_L4_Per(void)
{
	if((L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OFF)
	&& (L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OVER2))
    {
		/*CAN Communication Loop*/
        CAN_L3_Per();
		/*abstract vehicle speed signal*/
		VehicleSpeedSignalAbstarct_L3_Per();
		/*abstract engine status signal*/
		EngineSignalAbstarct_L3_Per();
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
void UDS_ON_CAN_RTask_L4_Per(void)
{
   /* motor phase voltage abstract*/
   Phase_Volt_Abstarct_L3_Per();    
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
void CCP_RTask_L4_Per(void)
{
	if((L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OFF)
	&& (L3_S_BatState_Uls_G_Enu != e_BAT_STATE_OVER2))
    {
		/*CAN CCP Loop*/
		CCP_Per();
    }
}
#define d_L4RUNTASK_STOP_SEC_CODE
#include "MemMap.h"

/*End of L4_ScheduleManagement.c file*/