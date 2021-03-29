/******************************************************************************
*
* ChuangQu NewEnergy .
* (c) Copyright 2014 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     L4_WarmTask.c
*
* @brief    warm task
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2016/11/12      ----    	   	N/A          Original
*	  1.0        2017/02/20      YCH    	   	N/A          Original
************************************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/
//#include "Sys_Cfg.h"

#include "L4_WarmTask.h"
#include "m_PWM_Drv_InitVal.h"
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
#define d_L4WARMTASK_START_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/

#define d_L4WARMTASK_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4WARMTASK_START_SEC_CODE
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
*   Notes:        Period 2000us
*
*****************************************************************************/
void Monitor_Service_WTask_L4_Per(void)
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


//volatile uint16 k_PhaseAdvance_Ct_u16Test = 420;
volatile uint16 k_PhaseAdvance_Ct_u16 = 300;
//volatile uint16 k_PhaseAdvance_Ct_u16 = 420;
volatile sint16 k_PianCiComp_Ct_s16 = 0;

uint16 k_MaxPhaseAdvance_Ct_u16 = 555;//600*0.925;



volatile uint16 k_Dcdc_Vref_Ct_u16 = DCDC_VOLT_AD_CONVERT(DCDC_LOOP_VOLT_SET);
volatile uint16 k_Dcdc_Iref_Ct_u16 = DCDC_CURRENT_AD_CONVERT(DCDC_LOOP_CURRENT_SET);

//volatile uint16 k_Dcdc_SetpInitIref_Ct_u16 = DCDC_CURRENT_AD_CONVERT(1);
//volatile uint16 k_Dcdc_SetpIref_Ct_u16 = DCDC_CURRENT_AD_CONVERT(1);//1A开始启动


volatile uint16 k_Dcdc_SetpInitIref_Ct_u16 = DCDC_CURRENT_AD_CONVERT(DCDC_CURRENT_INIT_UP_SET);
volatile uint16 k_Dcdc_SetpIref_Ct_u16 = DCDC_CURRENT_AD_CONVERT(DCDC_CURRENT_INIT_UP_SET);//1A开始启动


volatile uint16 k_Dcdc_startOnVref_Ct_u16 = PFC_VOLT_AD_CONVERT(PFC_START_DCDC_SET);//启动电压AD值 390*1.69984
volatile uint16 k_Dcdc_stopOnVref_Ct_u16 = PFC_VOLT_AD_CONVERT(PFC_OFF_DCDC_SET);//启动电压AD值 350*1.69984

/*
//volatile uint16 k_Dcdc_Vref_Ct_u16 = (uint16)(380*1024/500);
//volatile uint16 k_Dcdc_Vref_Ct_u16 = (uint16)((uint32)380*1024*9.175/5000);
volatile uint16 k_Dcdc_Vref_Ct_u16 = (uint16)((uint32)270*1024*9.975/5000);//270*1024*9.175/5000;80*1024*9.175/5000
//volatile uint16 k_Dcdc_Vref_Ct_u16 = (uint16)((uint32)330*1024*10.65/5000);//270*1024*9.175/5000;80*1024*9.175/5000
//volatile uint16 k_Dcdc_Iref_Ct_u16 = (uint16)((8 + 2.5)*71.68);
volatile uint16 k_Dcdc_Iref_Ct_u16 = (uint16)((8 + 2.5)*71.68);//(3 + 2.5)*71.68，(6 + 2.5)*71.68


//volatile uint16 k_Dcdc_Vref_Ct_u16 = (uint16)(360*1024/500);
//volatile uint16 k_Dcdc_Iref_Ct_u16 = (uint16)((11 + 2.5)*71.68);
//volatile uint16 k_Dcdc_SetpInitIref_Ct_u16 = (uint16)((1 + 2.5)*71.68);
//volatile uint16 k_Dcdc_SetpIref_Ct_u16 = (uint16)((1 + 2.5)*71.68);//1A开始启动

volatile uint16 k_Dcdc_SetpInitIref_Ct_u16 = (uint16)((11 + 2.5)*71.68);
volatile uint16 k_Dcdc_SetpIref_Ct_u16 = (uint16)((11 + 2.5)*71.68);//1A开始启动



//volatile uint16 k_Dcdc_startOnVref_Ct_u16 = (uint16)(380*1024/500);//启动电压
//volatile uint16 k_Dcdc_startOnVref_Ct_u16 = 760;//启动电压AD值 380v

//volatile uint16 k_Dcdc_startOnVref_Ct_u16 = 786;//启动电压AD值 390v
//volatile uint16 k_Dcdc_stopOnVref_Ct_u16 = 705;//启动电压AD值 350v


volatile uint16 k_Dcdc_startOnVref_Ct_u16 = 663;//启动电压AD值 390*1.69984
volatile uint16 k_Dcdc_stopOnVref_Ct_u16 = 595;//启动电压AD值 350*1.69984

*/
volatile uint8 startOver = 0;
volatile uint8 waitStart = 0;

volatile uint8 k_PwmSelect_u08 = DCDC_CONTRL_LOOP;//0 开环,1 双环 4、 0%

volatile uint8 k_DcDcTaskPer_u08 = 50;

volatile uint8 L3_DcDcTaskCt_u08 = 0;

volatile uint8 k_O_S_RlyCT = 0;
volatile uint8 k_O_S_RlyCT_lastFlag = 0;
volatile uint16 k_deadTime = SUB_0_DEADTIMR_INIT;
volatile uint16 k_deadTime_lastFlag = SUB_0_DEADTIMR_INIT;
volatile uint8 k_pianCiCnt_u08 = 4;    
volatile uint32 DcDc_Task_frist_run = 0; 

volatile uint8 K_I_GLB_EN = 0;  
volatile uint8 K_OVER_CUR_TRIG = 0; 

volatile uint8 clearACVoltMax = 0;
volatile uint8 clearAC_CurrentMax = 0;

volatile int16_T parameter_CurKi_Uls_s16p15 = CURRENT_I;    
volatile int16_T parameter_CurKp_Uls_s16p12 = CURRENT_P; 


uint8 time1msDelay = 50;
uint8 time1msCnt = 0;

uint32 time20msDelay = 1000;
uint32 time20msCnt = 0;

uint32 time1msDelay1 = 50;
uint32 time1msCnt1 = 0;


uint32 time100msDelay = 5000;
uint32 time100msCnt = 0;

uint32 currentUpCnt = 0;
//uint32 current1sUpCntMax = 50000;//1s
uint32 currentTimeUpCntMax = 1500;//30ms
//k_Dcdc_SetpIref_Ct_u16 += 251;//1A ad值
//k_Dcdc_SetpIref_Ct_u16 += 215;//0.5A ad值
//k_Dcdc_SetpIref_Ct_u16 += 197;//0.25A ad值
//k_Dcdc_SetpIref_Ct_u16 += 10;//0.25A ad值
//k_Dcdc_SetpIref_Ct_u16 += 100;//0.25A ad值
uint8 currentUpAdValue = 1;

volatile uint8 L3_HW_DCDC_OCP_u08 = FALSE;
volatile uint8 L3_HW_DCDC_OVP_u08 = FALSE;

volatile uint8 L3_last_LOOP_state_u08 = FALSE;
volatile uint16 L3_last_OBC_Y_Ct_u16  = 0xffff;
volatile uint16 L3_loopChangeSetCt_u16  = 0xffff;
volatile uint8 L3_Keeplast_LOOP_state_u08 = FALSE;
volatile uint16 L3_ChangeloopCnt_Ct_u16  = 0xffff;
volatile uint8 L3_ChangeloopMaxCnt_Ct_u16  = 10;
volatile sint16 L3_loopChangeErrorCt_u16  = 0xffff;
void DcDc_Task_L4_Per(void)
{
//20us
	 /* SBC */
	//mPWM_Sub_AB_PWM_Stop();
	//mPWM_Sub_CD_PWM_Stop();
	//mPWM_Sub_All_Stop();
	//TEST1 = HIGH;
	L3_HW_DCDC_OCP_u08 = I_DCDC_OCP;
	L3_HW_DCDC_OVP_u08 = I_DCDC_OVP;
   AdcSigSample_L3_Per();
   
   //return;
   
   //TEST1 = ~TEST1; 
   //OBC_Y.Ct = 5;
   //OBC_Y.Ct1 = 3;
  //SAFEPORT_CAN_L5_TxMsg();
   //if(1)
   /*
   	if(stSysFSMCtrl.ucLastState != STATE_STANDBY)
	{
		TEST1 = ~TEST1;
	}
   */
   
   if(stSysFSMCtrl.ucCurrentState  == STATE_OPETRATION)
   {
   		/*
   		if(opetrationDelayOver != TRUE)
   		{
   			return;
   		}*/
   		
   		//O_MCU_FAT = HIGH;	
  		//O_GLB_RSET = HIGH;
		//OBC_initialize();
	//	(void)mPWM_offset_Advance((0),0);
		//return;
		//Driver13V_diag_handle();

		#ifndef PFC_DIAG_ENABLE
			if(1)
		#else
			if(startOver || (L3_I_AD_PFC_slow_Ct_u16 >= k_Dcdc_startOnVref_Ct_u16) )
		//if(L3_I_AD_PFC_slow_Ct_u16 >= k_Dcdc_startOnVref_Ct_u16)
		#endif
		{
		   
		   if(startOver == 0)
		   {
		   	 //O_MCU_FAT = HIGH;
		   	 //O_GLB_RSET = HIGH;
		   //	mPWM_Sub_ABCD_PWM_Start();
		   	/*
		   	if(time100msCnt<time100msDelay)
		   	{
		   		time100msCnt++;
		   		return;	
		   	}
		   	
		   	A7_OUT = HIGH;
		   	C4_OUT = HIGH;
		   	C5_OUT = HIGH;
		   	D8_OUT = HIGH;
		   	C7_OUT = HIGH;
		   	D9_OUT = LOW;
		   	A8_OUT = HIGH;
		   	A12_OUT = LOW;
		   	
		   	if(time1msCnt<time1msDelay)
		   	{
		   		time1msCnt++;
		   		return;	
		   	}
		   	// O_OVP_RSET 
		    A7_OUT = LOW;
		//	PCR_CFG(A7,PCR_PIN_OUT_WPE);
		        
		    // O_OCP_RSET 
			C4_OUT = LOW;
			//PCR_CFG(C4,PCR_PIN_OUT_WPE);

			//O_PFC_OVP_RSET
			C5_OUT = LOW;
		//	PCR_CFG(C5,PCR_PIN_OUT_WPE);
			
			//O_GLB_RSET
			D8_OUT = LOW;
		//	PCR_CFG(D8,PCR_PIN_OUT_WPE);

		    // O_PFC_OCP_RSET 
		    C7_OUT = LOW;
		//	PCR_CFG(C7,PCR_PIN_OUT_WPE);
		*/ 	
		   	startOver = 1;
		   	time100msCnt = 0;
		   	currentUpCnt = 0;
		   	k_Dcdc_SetpIref_Ct_u16 = k_Dcdc_SetpInitIref_Ct_u16;
		   	//mPWM_Sub_3_A_Updata_Duty(SUB_3_VAL3_DCDC_RUN);
		   }
		   
		   //	if(time100msCnt <= time100msDelay)
		   //	{
		   //		time100msCnt++;
		   		
		   //	}
		   //	else
		   	{
		   			//A8_OUT = ~A8_OUT ;
		   	   //A8_OUT  = LOW;
		   	  
		   	   if(k_Dcdc_Iref_Ct_u16 > k_Dcdc_SetpIref_Ct_u16)
			   	{
			   	 
			   	 	if(currentUpCnt >= currentTimeUpCntMax)
			   	 	{
			   	 		currentUpCnt = 0;
			   	 		//if(L3_Dcdc_Iout_Ct_u16 >= k_Dcdc_SetpIref_Ct_u16)
				   	 	//{
			   	 			//if(k_Dcdc_SetpIref_Ct_u16 <= k_Dcdc_Iref_Ct_u16)
					   	 	//{
					   	 	
					   	k_Dcdc_SetpIref_Ct_u16 += currentUpAdValue;
					   	 	//}
				   	 	//}
			   	 	}
			   	 	else
			   	 	{
			   	 		currentUpCnt++;
			   	 	}
			   	 	
			   	 	OBC_U.VoErr = (sint16)k_Dcdc_Vref_Ct_u16 - (sint16)L3_Dcdc_Vout_Ct_u16;
			   		OBC_U.IoErr = (sint16)k_Dcdc_SetpIref_Ct_u16 - (sint16)L3_Dcdc_Iout_Ct_u16;
			   	 }
			   	 else
			   	 {
			   	 	
			   	 	OBC_U.VoErr = (sint16)k_Dcdc_Vref_Ct_u16 - (sint16)L3_Dcdc_Vout_Ct_u16;
			   		OBC_U.IoErr = (sint16)k_Dcdc_Iref_Ct_u16 - (sint16)L3_Dcdc_Iout_Ct_u16;
			   	 }
		   	 	//mPWM_Sub_3_B_Updata_Duty((uint16)((uint32)(OBC_U.VoErr)*DUTY_FULL/1024));
		   	 
		   	 
		   	 	//OBC_U.VoErr = (sint16)k_Dcdc_Vref_Ct_u16 - (sint16)L3_Dcdc_Vout_Ct_u16;
		   		//OBC_U.IoErr = (sint16)k_Dcdc_Iref_Ct_u16 - (sint16)L3_Dcdc_Iout_Ct_u16;
			   OBC_DcDc();
			   //A8_OUT = OBC_Y.VLOOPbIT;
			   //2aê?1yá÷?ì2a
			   //K_I_GLB_EN = I_GLB_EN;
			   //K_OVER_CUR_TRIG = OVER_CUR_TRIG;
			   //I_AD_PFC_SLOW//????μ??1
			   /*
			   if(OBC_Y.VLOOPbIT)
			   {
			   		if(	OBC_Y.Ct > k_PhaseAdvance_Ct_u16Test)
			   		{
			   			OBC_Y.Ct = k_PhaseAdvance_Ct_u16Test;
			   		}
			   }*/
			   
			   //mPWM_Sub_3_B_Updata_Duty((uint16)((uint32)(L3_Dcdc_Vout_Ct_u16)*DUTY_FULL/1024));
			   //mPWM_Sub_3_B_Updata_Duty((uint16)((uint32)(voltCurrentdiffCt)*DUTY_FULL/600));
			   /*
			   if(OBC_Y.VLOOPbIT)
			   {
			   		TEST1 = LOW;
			   }
			   else
			   {
			   		TEST1 = HIGH;
			   }
			   */
			   /*
			   if(L3_last_OBC_Y_Ct_u16 !=0xffff && L3_last_LOOP_state_u08 != OBC_Y.VLOOPbIT)
			   {
			   		//OBC_Y.Ct = L3_last_OBC_Y_Ct_u16;
			   		TEST1 = ~TEST1;
			   		
			   	
			   }*/
			   
			   //VloopCt
			   //CurrentLoopCt
			   /*
			   if(L3_last_OBC_Y_Ct_u16 !=0xffff && L3_last_LOOP_state_u08 != OBC_Y.VLOOPbIT)
			   {
			   		//OBC_Y.Ct = L3_last_OBC_Y_Ct_u16;
			   		TEST1 = ~TEST1;
			   		//L3_Keeplast_LOOP_state_u08 = TRUE;
			   		L3_ChangeloopCnt_Ct_u16 = 0;
			   		
			   		if(OBC_Y.VLOOPbIT == TRUE)
			   		{
			   			L3_loopChangeErrorCt_u16 = (sint16)(L3_last_OBC_Y_Ct_u16-(sint16)OBC_Y.VloopCt);
			   		}
			   		else
			   		{
			   			L3_loopChangeErrorCt_u16 = (sint16)(L3_last_OBC_Y_Ct_u16-(sint16)OBC_Y.CurrentLoopCt);
			   		}
			   		
			   }
			   //if(L3_Keeplast_LOOP_state_u08 == TRUE && L3_ChangeloopCnt_Ct_u16<10)
			   if(L3_ChangeloopCnt_Ct_u16<L3_ChangeloopMaxCnt_Ct_u16)
			   {
			   
			   		L3_loopChangeSetCt_u16 = L3_last_OBC_Y_Ct_u16+L3_loopChangeErrorCt_u16/L3_ChangeloopMaxCnt_Ct_u16;
			   		
			   		OBC_Y.Ct = L3_loopChangeSetCt_u16;
			   		
			   		L3_ChangeloopCnt_Ct_u16++;
			   }
			   */
			   	
			   
			   if(OBC_Y.Ct >= k_MaxPhaseAdvance_Ct_u16)
			   {
			   	OBC_Y.Ct = k_MaxPhaseAdvance_Ct_u16;
			   }
			   
			   
			   L3_last_LOOP_state_u08 = OBC_Y.VLOOPbIT;
			   L3_last_OBC_Y_Ct_u16 = OBC_Y.Ct;

			   
			   

			   //if(L3_DcDcTaskCt_u08 >= k_DcDcTaskPer_u08)
			   L3_DcDcTaskCt_u08++;
			   if(L3_DcDcTaskCt_u08 >= k_DcDcTaskPer_u08)
			   {
			       L3_DcDcTaskCt_u08 = 0;
			       if(DcDc_Task_frist_run <10000)
				   {
				   		DcDc_Task_frist_run++;
				   }
			   

			   	   //AdcSigSample_L3_Per1();
			   
			   	  if(DcDc_Task_frist_run == 10000)
			   	  {
			   	  		
			   	  		//A8_OUT = ~A8_OUT ;

			   	  	 	OBC_U.PfcCurErr = (sint16)L3_PriCurHigh_Ct_u16 - (sint16)L3_PriCurLow_Ct_u16;
			   			
				   	   /* end of Outputs for SubSystem: '<Root>/DcDc' */

				   	   /* Outputs for atomic SubSystem: '<Root>/PianCi' */
				   	   //OBC_PianCi();
				   	   if(OBC_U.PfcCurErr <= -27)//27 == 1.2A
				   	   {
				   	   		OBC_Y.Ct1++;
				   	   }
				   	   else if(OBC_U.PfcCurErr >= 27)
				   	   {
				   	   		
				   	   		OBC_Y.Ct1--;
				   	   }
				   	   
				   	   if(	OBC_Y.Ct1 <=-5 )
				   	   {
				   	   	OBC_Y.Ct1 = -5;
				   	   }
				   	   else if(	OBC_Y.Ct1 >= 5)
				   	   {
				   	   	
				   	   	OBC_Y.Ct1 = 5;
				   	   }
			   	  }
			   }

				
				
					
			if(k_PwmSelect_u08 == 1)
			   {
			       
			       (void)mPWM_offset_Advance((OBC_Y.Ct),OBC_Y.Ct1);
			   	   //(DUTY_FULL * PWM_SUB_3_A_DUTY_PERCENT_RUN/PWM__DUTY_PERCENT_FULL)
			   	   //mPWM_Sub_3_B_Updata_Duty((uint16)((uint32)(voltCurrentdiffCt >> 15)*DUTY_FULL/600));
			   	  
			   }
			   else if(k_PwmSelect_u08 == 0)
			   {
 					/* less than 600 Ct */
			       (void)mPWM_offset_Advance((k_PhaseAdvance_Ct_u16),k_PianCiComp_Ct_s16);
			   }
			   /*
			   else if(k_PwmSelect_u08 == 2){
			   		
			   		mPWM_Sub_0_AB_Advance_pianci((OBC_Y.Ct),OBC_Y.Ct1,k_pianCiCnt_u08);
			   }*/
			   else
			   {
			   	   (void)mPWM_offset_Advance((0),0);
			   }   	
				//if(DcDc_Task_frist_run == 1)
				//{
				//	DcDc_Task_frist_run = 0;
					//mPWM_Sub_0_AB_Advance_pianci((OBC_Y.Ct),OBC_Y.Ct1,k_pianCiCnt_u08);
			//	}
			/*
				if(k_deadTime != k_deadTime_lastFlag)
				{

					if(k_deadTime>=12 || k_deadTime<=42)
					{
						//100ns <= x <= 300ns
						k_deadTime_lastFlag = k_deadTime;
						//DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53 
						// Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period  
					
						#ifdef AB_before_CD
							#ifdef	PWM_SUB_1_DEADTIME_EN
							PWM_DISMAP(1) = DISMAP_VALUE;								// ReSet PWMA & PWMB Fault Disable Mask //
							PWM_DTCNT0(1) = k_deadTime_lastFlag;					// PWMA Dead Time//
							PWM_DTCNT1(1) = k_deadTime_lastFlag;					// PWMB Dead Time ///
							#else
							PWM_DISMAP(1) = DISMAP_VALUE;								// ReSet PWMA & PWMB Fault Disable Mask //
							PWM_DTCNT0(1) = 0x0000;								// PWMA Dead Time /
							PWM_DTCNT1(1) = 0x0000;								// PWMB Dead Time /
							#endif
						#else	
							#ifdef	PWM_SUB_0_DEADTIME_EN
							PWM_DISMAP(0) = DISMAP_VALUE;								// ReSet PWMA & PWMB Fault Disable Mask //
							PWM_DTCNT0(0) = k_deadTime_lastFlag;				// PWMA Dead Time //
							PWM_DTCNT1(0) = k_deadTime_lastFlag;					// PWMB Dead Time //
							#else
							PWM_DISMAP(0) = DISMAP_VALUE;							//ReSet PWMA & PWMB Fault Disable Mask //
							PWM_DTCNT0(0) = 0x0000;							// PWMA Dead Time //
							PWM_DTCNT1(0) = 0x0000;							// PWMB Dead Time //
							#endif
						#endif
						
					}
					
				}*/
		   	}
		}
		else
		{	
			if(L3_I_AD_PFC_slow_Ct_u16 <= k_Dcdc_stopOnVref_Ct_u16)
			{
				startOver = 0;
				//O_MCU_FAT = LOW;
				stopAllPwm();
				OBC_initialize();
				(void)mPWM_offset_Advance((0),0);
			}
		
		   	//O_GLB_RSET = LOW;
		/*	if(waitStart == 0)
			{
				mPWM_Sub_All_Stop();
				waitStart = 1;
			}*/
		}

   }
   /*
   else if(stSysFSMCtrl.ucCurrentState  == STATE_PRECHARGE2)
   {
   	
  		//Driver13V_diag_handle();
  		if(L3_Dcdc_Vout_Ct_u16 >= L3_Dcdc_Vout_Precharge2High)
  		{
  			//O_DCDC_DRV_EN = LOW;
  			//O_MCU_FAT = LOW;
  			stopAllPwm();
  		}
  		else
  		{
  			if(L3_Dcdc_Vout_Ct_u16 <= L3_Dcdc_Vout_Precharge2Low)
  			{
  				//TEST1 = ~TEST1;
  				//O_DCDC_DRV_EN = HIGH;	
	  			//O_MCU_FAT = HIGH;	
	  			//O_GLB_RSET = HIGH;
	  			startAllPwm();
	  		//	(void)mPWM_offset_Advance((6),0);
	  			(void)mPWM_offset_Advance((18),0);

	  			
	  			
  			}
  		
  		}
  	
  		//O_MCU_FAT = LOW;
   }
   */
   /*
   else if(stSysFSMCtrl.ucCurrentState  == STATE_AFTER_RUN)
   {
		if(mVARCntrTag.afterRunACRelayDelayCntr >= mVARTimerTag.afterRunACRelayDelayTime)
		{
			if(AC_Volt_fast_limtLow_Ct_u16<=L5_AC_Volt_fast_maxBuffCPS && L5_AC_Volt_fast_maxBuffCPS <= AC_Volt_fast_maxHigh_Ct_u16)
			{
				//O_MCU_FAT = HIGH;	
	  			//O_GLB_RSET = HIGH;
	  			startAllPwm();
	  			(void)mPWM_offset_Advance((120),0);//10%
			}
			
		}
   }*/
   else
   {
   		(void)mPWM_offset_Advance((0),0);
   		//(void)mPWM_offset_Advance((60),0);//5%
   }
   
   
  
	/*

   if(k_O_S_RlyCT != k_O_S_RlyCT_lastFlag)
	{
		

		k_O_S_RlyCT_lastFlag = k_O_S_RlyCT;
		A12_OUT = k_O_S_RlyCT;
	}
	*/
	
	/*
   if(parameter_CurKi_Uls_s16p15 != k_CurKi_Uls_s16p15)
	{
		
		k_CurKi_Uls_s16p15 = parameter_CurKi_Uls_s16p15;
	
	}
	
	
   if(parameter_CurKp_Uls_s16p12 != k_CurKp_Uls_s16p12)
	{
		

		k_CurKp_Uls_s16p12 = parameter_CurKp_Uls_s16p12;
	}
	*/
	//TEST1 = LOW;
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
*   Notes:        Period 2000us
*
*****************************************************************************/
void DTCManage_WTask_L4_Per(void)
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
*   Notes:        Period 2000us
*
*****************************************************************************/
void SignalSampling_WTask_L4_Per(void)
{
	//AdcSigSample_L3_Per1();
	 /* caculate CP */
   L2_eTimer_Per1();

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
*   Notes:        Period 2000us
*
*****************************************************************************/
void RunStateMonitor_WTask_L4_Per(void)
{
	/*ECU state management*/
	ECUStateManagement_L4_WarmInit();
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
void FaultManage_WTask_L4_Per(void)
{
   /* FailSafe control loop */
   FM_L4_WarmInit();
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
void CAN_Comm_WTask_L4_Per(void)
{
		//TEST2 = HIGH;
		SBC_L3_Per();
		//AdcSigSample_L3_Per1();
       /*CAN Communication Loop*/
       CAN_L3_Per();
       //TEST2 = LOW;
    
       //SAFEPORT_CAN_L3_Per();
   
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
void UDS_ON_CAN_WTask_L4_Per(void)
{
   
}


/*****************************************************************************
*
*   Function:     app_stateflow_task_L5_Per
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
void app_stateflow_task_L5_Per(void)
{
   	//TEST2 = HIGH;
   app_stateflow_task();
   //	TEST2 = LOW;
}


/*****************************************************************************
*
*   Function:     app_stateflow_task_L5_Per
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
void sys_diag_task_L5_Per(void)
{
   
   sys_diag_task();
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
void CCP_WTask_L4_Per(void)
{
		/*CAN CCP Loop*/
		CCP_Per();
}
#define d_L4WARMTASK_STOP_SEC_CODE
#include "MemMap.h"

/*End of L4_WarmTask.c file*/
