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
******************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2014/12/20      JiaoYu    	   	N/A          Original
******************************************************************************/

/* include files */

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L4_ECUStateManagement.h"

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
#define d_L4ECUSTATEMANAGEMENT_START_SEC_VAR
#include "MemMap.h"

static uint8 L4_S_NVMState_G_u08 = STD_OFF;
static uint16 L3_SleepWaitTime_Ct_u16 = 0;

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/

/*Enum for ECU state*/
ECU_State_enu L4_S_ECUState_Now_G_Enu;
ECU_State_enu L4_S_ECUState_Pre_G_Enu;

#define d_L4ECUSTATEMANAGEMENT_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4ECUSTATEMANAGEMENT_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     ECUStartUp_L4_Ctrl
*
*   Description:  This function is used for ECU Startup Control
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void ECUStartUp_L4_Ctrl(void)
{
	int testCnt = 0;
	unsigned char delayCnt = 4;
	/* disable global interrupt */
    IRQ_DISABLE();

    /*Initial the MCU*/
    MCU_L2_Init();
    /*Initial the ECU*/
    ECU_L3_Init();
    /*Initial the Service Layer*/
    SRVL_L4_Init();
    /*Initial the Application Layer*/
    APPL_L5_Init();
    /*Initial the ECU running state*/
    ECUStateManagement_L4_ColdInit();
    
    PORT_L2_MCU_FATInit();
    
    mPWM_Sub_All_Start();
    //mPWM_offset_Advance((0),0);
    //mPWM_Sub_OVP_OCP_PWM_Start();
	/*//100ms
		while(testCnt++ < 714300)
		  {
		  	asm 
		  	{
		  	  nop	
		  	  nop
		  	  nop
		  	  nop
		  	}
		  }
		  */
	while(testCnt++ < 714300)
	{
		asm 
		{
		  nop	
		  nop
		  nop
		  nop
		}
	}
	//100ms
	/*
	while(delayCnt-->1)
	{
	  while(testCnt++ < 714300)
	  {
	  	asm 
	  	{
	  	  nop	
	  	  nop
	  	  nop
	  	  nop
	  	}
	  }
	  testCnt = 0;
	  SBC_L3_Per();
	}
	*/
	PORT_L2_Init(); 
	mINTC_SetCurrPriority_Irq(PRIOR_0);
    IRQ_ENABLE();    
}
/*****************************************************************************
*
*   Function:     ECUShutDown_L4_Ctrl
*
*   Description:  This function is used for ECU Stop Control
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
extern void main(void);

void ECUShutDown_L4_Ctrl(void)
{
    if(L3_S_IgnitionState_G_u08 == STD_OFF)
    {
       // EmEep_L3_PowerDown();

        /* kick sbc watchdog */
        //hSBC_vFeedWatchdog();                       

         /* shutdown mcu and system power supply */
         if((SBC_WI_INT_FLG_SET != SBC_L3_CheckWakeupIntEvent()) || (L3_SleepWaitTime_Ct_u16 > 20))
         {
             SBC_L3_CfgSleepMode();
             
            #if 0 
	        asm
	        {
	        	mr		 r3, r14
	        	mr		 r4, r15
	        	mr		 r5, r16
	        	bl		main
	        }
	        #endif

         }
         else
         {
         	L3_SleepWaitTime_Ct_u16++;
         }
         
    }
    else
    {
    }
}
/*****************************************************************************
*
*   Function:     ECUStateManagement_L4_Per
*
*   Description:  This function is used for period ECU state management
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void ECUStateManagement_L4_ColdInit(void)
{
    L3_SleepWaitTime_Ct_u16 = 0;

	/*Schedule ColdInit*/
	ScheduleManagement_L4_ColdInit();

	if((L4_S_SysFaultState_Uls_G_Enu == System_F1_Fault)\
	|| (L4_S_SysFaultState_Uls_G_Enu == System_F2_Fault))
	{
		L4_S_ECUState_Now_G_Enu = ShutDown_State;
		/*Schedule StopInit*/
		ScheduleManagement_L4_StopInit();
	}
	else
	{
		L4_S_ECUState_Now_G_Enu = WarmInit_State;
		/*Schedule WarmInit*/
		ScheduleManagement_L4_WarmInit();
	}
	L4_S_ECUState_Pre_G_Enu = CodeInit_State;
}
/*****************************************************************************
*
*   Function:     ECUStateManagement_L4_Per
*
*   Description:  This function is used for period ECU state management
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void ECUStateManagement_L4_WarmInit(void)
{
}
/*****************************************************************************
*
*   Function:     ECUStateManagement_L4_Per
*
*   Description:  This function is used for period ECU state management
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:        Period 2ms
*
*****************************************************************************/
void ECUStateManagement_L4_Per(void)
{
}
#define d_L4ECUSTATEMANAGEMENT_STOP_SEC_CODE
#include "MemMap.h"
/*End of L4_ECUStateManagement.c file*/