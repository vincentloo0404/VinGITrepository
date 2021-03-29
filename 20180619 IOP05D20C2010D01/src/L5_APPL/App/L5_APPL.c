/*****************************************************************************
*   Copyright 2010 - 2011 Shanghai Aerospace Automobile Electromechanical 
*   Co., Ltd., all rights reserved.
*
*   Filename:    L5_APPL.c
*
*   Description: This file is the C source file for the interface between
*                Application Layer with other Layer
*
*
*   Revision History:
*
*   Date            Author          Description
*   ----------      ----------      -----------------------------------------
*   2017-1-31      	  YCH		     Initial created
*
*****************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L5_APPL.h"
#include "my_all.h"
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

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L5APPL_START_SEC_CODE
#include "MemMap.h"
#include "dDiagScheduEntryExt.h"
#include "my_all.h"

 uint16 UDS_TimeOutCnt; 
 uint8 UDS_TimeOutFlag; 
/*****************************************************************************
*
*   Function:     APPL_L5_Init
*
*   Description:  This function is use to Initial the ECU Abstraction Layer
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void APPL_L5_Init(void)
{
    /*Power Steering Control Initial*/
    //PowerSteeringCtrl_L5_Init();

    /*Motor Control Initial*/
    //MotorCtrl_L5_Init();

    /*Failsafe control Initial*/
   // FS_L5_ApplFailSafeInit();
   /*
   Diag_PreInit_Dtc_Entry();
   Diag_Init_Dtc_Entry();
   Diag_Init_CanTp_Entry();
   Diag_Init_Dcm_Entry();
   Diag_Init_EEPROMforDtc_Entry();
   Diag_Init_Dec_Entry();
   dDiag_vInitDecisionTask_Entry();
   */
   hCanBus_vBusDiagModuleInit();
   Diag_PreInit_Dtc_Entry();
   /*-------------- Diagnostic --------------*/
	    
	    /*EEPROM manage block init*/
		Diag_Init_EEPROMforDtc_Entry();	
		
		/*transport layer init*/	    
		Diag_Init_CanTp_Entry();
       	
		/*UDS service init*/
		Diag_Init_Dcm_Entry();
		
        /*DTC strategy init*/
		Diag_Init_Dtc_Entry(); 
      		
		/*Diag Decision init*/
		Diag_Init_Dec_Entry();
		UDS_TimeOutCnt = 0;
		UDS_TimeOutFlag = FALSE;
		/* angle calibration init,MUST after get dtc value from EEPROM */
		//hAngCal_vInit();		
	    /*-------------- Diagnostic --------------*/
   Schedule_Diag_InitDec_Task_Entry();
   OBC_initialize();
   FSM_init();
   
}


void APPL_1ms_task(void)
{
		
		/* timer tick */
       // mComm_vTimeTick();   
       //hCanBus_vBusStateMonitor(); //BUSOFF recovery mechanism 2, the code is not verified
	  /*-------------- Diagnostic --------------*/
       Schedule_Diag_ComStack_Task_Entry();
       Schedule_Diag_DtcStrgy_Task_Entry();
       Schedule_Diag_RuntimeDec_Task_Entry();       
       /*-------------- Diagnostic --------------*/
	/*
	static uint8 delay1msCnt = 0;
	//TEST1 = ~TEST1;
	dDiag_vRuntimeDecisionTask_Entry();
	dDiag_vCommStackTask_Entry();
	if(delay1msCnt >= 1)
	{
		dDiag_vDtcStrategyTask_Entry();
	}
	else
	{
		delay1msCnt = 1;
	}
	//TEST1 = LOW;
	*/
	
	if(UDS_TimeOutCnt>10000)//10S
	{
		UDS_TimeOutFlag = TRUE;
		//UDS_TimeOutCnt = 0;
	}
	else
	{
		UDS_TimeOutFlag = FALSE;
		UDS_TimeOutCnt ++;
	}
}

void APPL_100us_task(void)
{
	//TEST1 = HIGH;
	//Driver13V_diag_handle();
	//TEST1 = LOW;
	
	AdcSigSample_L3_Per1();
	Driver13V_diag_handle();
}
void APPL_softwareRest(void)
{
	 uint16 testCnt = 0;
	 powerDown();
	 while(testCnt++ < 10000)
	{
		asm 
		{
		  nop	
		  nop
		  nop
		  nop
		}
	}
	EcuSoftRst();
}

#define d_L5APPL_STOP_SEC_CODE
#include "MemMap.h"
/*End of L5_APPL.c file*/
