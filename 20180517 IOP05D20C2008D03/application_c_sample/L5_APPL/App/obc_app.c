/*
 * obc_app.c
 *
 *  Created on: 2017年2月14日
 *      Author: YCH
 */
#include "obc_app.h"

SysFSMCtrlTag stSysFSMCtrl = {0};
CtrlParaTag ctrlParaTag;
void (*pFSMAct[STATE_TOTAL_CNT])(void);  // 系统状态机执行函数接口

OBCPOWERTAG OBCPOWERTag = {0};
OBCTAG OBCTag = {0};
BMSTAG BMSTag = {0};
StateCntrTag stateCntrTag = { 0};
const StateTimerTag stateTimerTag = {0};
uint8_t wakeupSignal = WAKEUP_INT;

/*
//uint16_t ACVolt_pfcVolt_err_Ct_u16 = 16;//10*(1.531475187) ~ 16  ???????10V问题
uint16_t ACVolt_pfcVolt_err_u16 = 70;//70v
uint16_t preC1ToPfcRunACVolt_Ct_u16 = 237;//105*(1.531475187)
uint16_t pfcRunToPreC2PfcVolt_Ct_u16 = 765;//380*(2.01542149)
*/

//uint16_t ACVolt_pfcVolt_err_Ct_u16 = 16;//10*(1.531475187) ~ 16  ???????10V问题
//uint16_t ACVolt_pfcVolt_err_u16 = 70;//70v
uint16_t ACVolt_pfcVolt_err_u16 = 20;//20v
//uint16_t preC1ToPfcRunACVolt_Ct_u16 = 237;//105*(1.531475187)
uint16_t preC1ToPfcRunACVolt_Ct_u16 = AC_VOLT_AD_CONVERT(100);//(2.5+(0.005* 105 ))*1024/5  105V
uint16_t pfcRunToPreC2PfcVolt_Ct_u16 = PFC_VOLT_AD_CONVERT(380);//380*(1.69984)

uint16_t pfcPreFailureVolt_Ct_u16 = PFC_VOLT_AD_CONVERT(380);//380*(1.69984)


volatile uint16 L5_AC_Volt_fast_max_buff;
volatile uint16 L5_AC_Volt_fast_maxBuffCPS;

volatile uint16 L5_AC_current_max_buff;


//uint16_t preC2TodcOpetrationDCVolt_Ct_u16 = 765;//380*(2.01542149)
uint16_t preC2TodcOpetrationDCVolt_Ct_u16 = PFC_VOLT_AD_CONVERT(380);//380*(1.69984) //PFC PRE over

StateCntrTag mStateCntrTag = {0};


#define AC_Volt_zeroP   (20)
#define AC_Volt_zeroN   (0)

uint16 L3_AD0_AC_Volt_fast_zeroP_Ct_u16 =  AC_VOLT_AD_CONVERT(AC_Volt_zeroP);
uint16 L3_AD0_AC_Volt_fast_zeroN_Ct_u16 = AC_VOLT_AD_CONVERT(AC_Volt_zeroN);

uint8  pfcEnAtACzeroState = FALSE;

#ifdef  BMS_CAN_ENABLE 
	uint8_t bms_can_available = 1;//是否与BMS通信，用于调试变量
#else
	uint8_t bms_can_available = 0;//是否与BMS通信，用于调试变量
#endif
#define PRECHARGE2_VREF   360
//#define PRECHARGE2_VREF   10
#define PRECHARGE2_OFFSET  10
volatile uint16 L3_Dcdc_Vout_Precharge2 = DCDC_VOLT_AD_CONVERT(PRECHARGE2_VREF);
volatile uint16 L3_Dcdc_Vout_Precharge2High = DCDC_VOLT_AD_CONVERT((PRECHARGE2_VREF+PRECHARGE2_OFFSET));
volatile uint16 L3_Dcdc_Vout_Precharge2Low = DCDC_VOLT_AD_CONVERT((PRECHARGE2_VREF-PRECHARGE2_OFFSET));

 uint8 L5_precharge2_CMD_FLAG = FALSE;
 uint16 L3_PRECHARGE2_BMS_MIN = 0;
 uint16 L3_PRECHARGE2_BMS_MAX = 0;

 uint16 L3_PRECHARGE2_BMS_OFFSET = DCDC_VOLT_AD_CONVERT(PRECHARGE2_BMS_OFFSET);

//#define AfterRun_PFC_VREF   60
#define AfterRun_PFC_VREF   30
volatile uint16 L3_PFC_Vout_AfterRun = PFC_VOLT_AD_CONVERT(AfterRun_PFC_VREF);

volatile uint8 L5_OBC_cmd = FALSE;

StateTimerTag mStateTimerTag =
{
	0,
	0,
	0,
	50/APP_STATEFLOW_THREAD_CYCLE_TIME,//50ms
	50/APP_STATEFLOW_THREAD_CYCLE_TIME,//50ms
	0,
	0,
	0,
	0
};


VARCntrTag mVARCntrTag = {0};
VARTimerTag mVARTimerTag = {
10/APP_STATEFLOW_THREAD_CYCLE_TIME,//10ms
10000/APP_STATEFLOW_THREAD_CYCLE_TIME,//10s
2/APP_STATEFLOW_THREAD_CYCLE_TIME,//2ms
10/APP_STATEFLOW_THREAD_CYCLE_TIME,//10ms
10/APP_STATEFLOW_THREAD_CYCLE_TIME,//10ms afterRunPFC_enCntr
10/APP_STATEFLOW_THREAD_CYCLE_TIME,//10ms
(5*60*1000)/APP_STATEFLOW_THREAD_CYCLE_TIME,//5 min
(1*1000)/APP_STATEFLOW_THREAD_CYCLE_TIME,//1 s
//(30*1000)/APP_STATEFLOW_THREAD_CYCLE_TIME//30s pre_changer2PGKeepTime
(3*60*1000)/APP_STATEFLOW_THREAD_CYCLE_TIME//3 min pre_changer2PGKeepTime
};


uint8_t acVoltSampleTimeCnt = 0;
uint8_t acVoltSampleTimeMax = 22/APP_STATEFLOW_THREAD_CYCLE_TIME;//22ms

uint8_t I_GLB_ENLowTimeCnt = 0;
uint8_t I_GLB_ENLowTimeMax = 10/APP_STATEFLOW_THREAD_CYCLE_TIME;//10ms

uint8_t I_GLB_ENHighTimeCnt = 0;
uint8_t I_GLB_ENHighTimeMax = 10/APP_STATEFLOW_THREAD_CYCLE_TIME;//10ms

uint8_t stayInFailure = 0;

uint8_t opetrationDelayOver = FALSE;

uint8_t CONNECT_BMS_OK = FALSE;//忽略BMS CMD   
uint8_t L5_AC_FAULT = FALSE;// 
uint8_t BMS_CHARGE_OVER = FALSE;//BMS 充电机结束

volatile uint16 PowerLimSet = POWER_DEFAULT_SET; 

volatile uint16 k_Dcdc_MIN_Iref_limt = DCDC_CURRENT_AD_CONVERT(DCDC_LOOP_CAN_CURRENT_SET_LIMT);
volatile uint16 k_Dcdc_MAX_Iref_limt = DCDC_CURRENT_AD_CONVERT(DCDC_LOOP_CAN_CURRENT_SET_MAX);

void FSM_init(void) {
	//初始化状态
	pFSMAct[STATE_INIT] = &in_INIT;
	pFSMAct[STATE_STANDBY] = &in_STANDBY;
	pFSMAct[STATE_PRECHARGE1] = &in_PRECHARGE1;
	pFSMAct[STATE_PFC_RUN] = &in_PFC_RUN;
	pFSMAct[STATE_PRECHARGE2] = &in_PRECHARGE2;
	pFSMAct[STATE_OPETRATION] = &in_OPETRATION;
	pFSMAct[STATE_AFTER_RUN] = &in_AFTER_RUN;
	pFSMAct[STATE_SLEEP] = &in_SLEEP;
	pFSMAct[STATE_FAILURE] = &in_FAILURE;
	pFSMAct[STATE_PREFAILURE] = &in_PREFAILURE;
	//一上电初始化状态
	stSysFSMCtrl.ucCurrentState = STATE_INIT;
	stSysFSMCtrl.ucLastState = STATE_INIT;
	stSysFSMCtrl.ucLastSysState = STATE_INIT;
	
}

void FSM_run(void) {
	//状态执行调用
	pFSMAct[stSysFSMCtrl.ucCurrentState]();
}




void in_INIT(void) {

	uint8_t ucStateRecd = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;
	OBCPOWERTag.ACPowMaxCurrentLimt = DCDC_CURRENT_AD_CONVERT(POWER_DEFAULT_SET/POWER_BMS_LIMT_CURRENT_VOLT_SET);
	
	OBCPOWERTag.HWLimtMAXCurrent = DCDC_CURRENT_AD_CONVERT(CURRENT_MAX_LIMT);
	
	//OBCPOWERTag.ACInputPowLimt = (uint16)POWER_DEFAULT_SET;
	//OBCPOWERTag.ACPowSetVoltCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(DCDC_LOOP_CURRENT_SET);
	//OBCPOWERTag.ACPowSetVoltCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(POWER_DEFAULT_SET/DCDC_LOOP_VOLT_SET);
	
	
	OBCPOWERTag.TEMPStateCurrentLimt = MAX_CURRENT_INIT;
	OBCPOWERTag.CCStateCurrentLimt = MAX_CURRENT_INIT;
	OBCPOWERTag.CPStateCurrentLimt = MAX_CURRENT_INIT;
	OBCPOWERTag.CANCmdSETVolt = MAX_CURRENT_INIT;
	OBCPOWERTag.CANCmdSETCurrent = MAX_CURRENT_INIT;
	
	
	 k_hardware_version_integer = HARDWARE_VERSION_INTEGER;
	 k_hardware_version_decimal = HARDWARE_VERSION_DECIMAL;
	 k_software_version_integer = SOFTWARE_VERSION_INTEGER;	
	 k_software_version_decimal = SOFTWARE_VERSION_DECIMAL;
	 k_software_data_version = 	SOFTWARE_DATA_VERSION;
	 //stopAllPwm();
	 //PWM_OCP_softRest();//clear pwm fault0 in init
	
/*	if (stSysFSMCtrl.ucLastState != STATE_INIT)
	{

//		osalThreadSleepMilliseconds(10);
		
		1. 记录唤醒源，2. 置位O_PG;5604B?
		3. 拉低O_PFC_EN、O_S_RlyCTL1、GLB_EN、O_PFC_DRV_EN、O_PFC_EN，
		4.上电自检，
		A、关断路径检测 
		B、参见故障诊断流程
		
		
		powerOnDiag();

	}else{

	}*/
	/***************** 诊断  *********************/


	/*
	1. 记录唤醒源，2. 置位O_PG;5604B?
	3. 拉低O_PFC_EN、O_S_RlyCTL1、GLB_EN、O_PFC_DRV_EN、O_PFC_EN，
	4.上电自检，
	A、关断路径检测 
	B、参见故障诊断流程
	*/
	wakeupSignal = WAKEUP_AC;

	//O_S_RlyCTL1 = HIGH;

	powerOnDiag();
	S2_CTR = HIGH;//不检测CC直接闭合S2，检测cc以cc状态来闭合继电器
	
	//故障诊断
	/*if ((faultCodeTag.uDWORD & ALL_FAULT_CODE_FLAG) != 0) {
		stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
	}*/
	stSysFSMCtrl.ucCurrentState = STATE_STANDBY;
	//if(glbDiag(ucStateRecd))
	//{
		
	//}
	//else
	//{


	//	stSysFSMCtrl.ucCurrentState = STATE_STANDBY;
		/*
		//上电自检
		//A、关断路径检测
		//(1)先拉低O_MCU_FAT，然后读 I_glb_en是否为低
		//(2)O_MCU_FAT拉高，o_glb_rset拉高10ms,然后读I_Glb_en是否为高
		//以上两个条件不满足都报failure
		O_MCU_FAT = LOW;//系统CPU初始化为高

		if(I_GLB_ENLowTimeCnt >=  I_GLB_ENLowTimeMax)
		{
			I_GLB_ENLowTimeCnt = 0;
			if(I_GLB_EN == LOW)
			{
				O_MCU_FAT = HIGH;
				O_GLB_RSET = HIGH;

				if(I_GLB_ENHighTimeCnt >= I_GLB_ENHighTimeMax)
				{
					I_GLB_ENHighTimeCnt = 0;
					if(I_GLB_EN == HIGH)
					{
						stSysFSMCtrl.ucCurrentState = STATE_STANDBY;
					}
					else
					{
						stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
					}
				}
				else
				{
					I_GLB_ENHighTimeCnt++;
				}



			}
			else
			{
				stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
			}
		}
		else
		{
			I_GLB_ENLowTimeCnt++;
		}
		*/

	//}

	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}

}

//1、判断充电模式，暂时不发送
void in_STANDBY() {
	uint8_t ucStateRecd = 0;

	ucStateRecd = stSysFSMCtrl.ucCurrentState;
	//TEST1 = HIGH;

	if (stSysFSMCtrl.ucLastState != STATE_STANDBY)
	{

//		osalThreadSleepMilliseconds(10);
		//stSysFSMCtrl.ucLastState = STATE_STANDBY;
		
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;

	}else{

	}
	L5_precharge2_CMD_FLAG = FALSE;
	#ifndef CC_STATE_DIAG_ENABLE
			S2_CTR = HIGH;//不检测CC直接闭合S2，检测cc以cc状态来闭合继电器
	#endif
	
	/*
	if(AC_Volt_fast_limtLow_Ct_u16<=L5_AC_Volt_fast_max_buff && L5_AC_Volt_fast_max_buff <= AC_Volt_fast_maxHigh_Ct_u16)
	{

		if(bms_can_available)
		{
		
			//if((CC_STATE_Tag[BMSTag.CCState].IMax > 0) && (BMSTag.EnCharger == BMS_EN_CHARGER))
			if(BMSTag.EnCharger == BMS_EN_CHARGER)
			{
				stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;
			}

		}
		else
		{
			stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;
		}

	}
	
	*/
	
	
	/***************** 诊断  *********************/


	//1、判断充电模式
	//故障诊断
	/*if ((faultCodeTag.uDWORD & ALL_FAULT_CODE_FLAG) != 0) {
		stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
	}*/
	
	if(glbDiag(ucStateRecd))
	{
		
	}
	else
	{
		//1、BMS03_EnCharger=1;
		//2、 检测AC侧电压有效值在85VAC~265VAC或者（CP_MCU 30和56pin）信号正常；
		//3、软件接受bms发来的CC状态，满足充电要求。
		#ifndef AC_DIAG_ENABLE
			if(1)
		#else
			if(AC_Volt_fast_limtLow_Ct_u16<=L5_AC_Volt_fast_maxBuffCPS && L5_AC_Volt_fast_maxBuffCPS <= AC_Volt_fast_maxHigh_Ct_u16 && (protect_TEM <= TEMP_PROTECT_CANCLE) && (derating_TEM <= TEMP_DERATING_CANCLE))
		#endif
		{
			////////////////////
			//if(bms_can_available)
			//{
			
				////if((CC_STATE_Tag[BMSTag.CCState].IMax > 0) && (BMSTag.EnCharger == BMS_EN_CHARGER))
				////if(BMSTag.EnCharger == BMS_EN_CHARGER)
				////{
				////	stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;
				////}
				
			//	stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;

			//}
		//	else
		//	{
			//	stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;
			//}
			/////////////////////////////////////////////////////
			if(BMS_CHARGE_OVER != TRUE)
			{
			
				if(bms_can_available)
				{
					if(O_PG == HIGH)
					{
						if(OBCTag.bFilterWorkCMD == TRUE)
						{
							#ifndef CC_STATE_DIAG_ENABLE
								if(1)
							#else
								if(OBCTag.bFilterCCState == TRUE)
							#endif
							{
								stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;
							}
						}
					}
					else
					{
						stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;
					}
					
					
				}
				else
				{
					#ifndef CC_STATE_DIAG_ENABLE
						if(1)
					#else
						if(OBCTag.bFilterCCState == TRUE)
					#endif
					{
						stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE1;
					}
				}
				
			}
			
			
			
		}
	
	}
	
	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
		
//		}
}
//Precharge1
//1、闭合S2
void in_PRECHARGE1() {
	uint8_t ucStateRecd = 0;
	int16_t acVolt_pfcVol_err = 0;
	int16_t acVolt_pfcVol_absErr = 0;
	uint8_t PFC_AC_FLAG = 0;
	
	ucStateRecd = stSysFSMCtrl.ucCurrentState;

	if (stSysFSMCtrl.ucLastState != STATE_PRECHARGE1)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
//		osalThreadSleepMilliseconds(10);

	}else{

	}
	/***************** 诊断  *********************/


	//故障诊断
	/*if ((faultCodeTag.uDWORD & ALL_FAULT_CODE_FLAG) != 0) {
		stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
	}*/
	if(glbDiag(ucStateRecd))
	{
		
	}
	else
	{
		//AC侧电压峰值-PFC输出的母线电压<20V
		//acVolt_pfcVol_err = (int16_t)((int32_t)L5_AD0_AC_Volt_fast_max_buff_Ct_u16/1.5-L3_I_AD_PFC_slow_Ct_u16/2);
		//acVolt_pfcVol_err = (int16_t)((int32_t)(L5_AC_Volt_fast_max_buff*2/3)-(L3_I_AD_PFC_slow_Ct_u16/2));
		
		//acVolt_pfcVol_err = (int16_t)((int32_t)(L5_AC_Volt_fast_max_buff-512)-(L3_I_AD_PFC_slow_Ct_u16/1.7));
		
		//acVolt_pfcVol_err = (int16_t)((int32_t)(AC_AD_CONVERT_VOLT(L5_AC_Volt_fast_max_buff))-(PFC_AD_CONVERT_VOLT(L3_I_AD_PFC_slow_Ct_u16)));
		acVolt_pfcVol_err = (int16_t)((int32_t)((PFC_AD_CONVERT_VOLT(L3_I_AD_PFC_slow_Ct_u16))-AC_AD_CONVERT_VOLT(L5_AC_Volt_fast_maxBuffCPS)));
		
		//PFC_AC_FLAG = 1;
		PFC_AC_FLAG = (PFC_AD_CONVERT_VOLT(L3_I_AD_PFC_slow_Ct_u16) + ACVolt_pfcVolt_err_u16) >AC_AD_CONVERT_VOLT(L5_AC_Volt_fast_maxBuffCPS) ? 1:0;

		//acVolt_pfcVol_absErr = acVolt_pfcVol_err >0?acVolt_pfcVol_err:(-acVolt_pfcVol_err);
			#ifndef AC_DIAG_ENABLE
			if(1)
		#else
			
			if(L5_AC_Volt_fast_maxBuffCPS >= preC1ToPfcRunACVolt_Ct_u16) 
		#endif
		{
			
			if(mVARCntrTag.ACVoltCntr >= mVARTimerTag.ACVoltTime)
			{
			
			}
			else
			{
				mVARCntrTag.ACVoltCntr++;
			}	
		}
		else
		{
			mVARCntrTag.ACVoltCntr = 0;
		}
		
		if(PFC_AC_FLAG == 1)
		{
			mVARCntrTag.acVolt_pfcVol_errCntr = 0;
		}
		else
		{
			mVARCntrTag.acVolt_pfcVol_errCntr++;
		}
		
		if(mVARCntrTag.ACVoltCntr >= mVARTimerTag.ACVoltTime && PFC_AC_FLAG ==1)
		{
			mVARCntrTag.ACVoltCntr = 0;
			stSysFSMCtrl.ucCurrentState = STATE_PFC_RUN;
		}
		
		/*
		if(acVolt_pfcVol_err > 0 && acVolt_pfcVol_err >= ACVolt_pfcVolt_err_u16)
			{
			mVARCntrTag.acVolt_pfcVol_errCntr = 0;
		}
		else
		{
			mVARCntrTag.acVolt_pfcVol_errCntr++;
		}
		
		if(mVARCntrTag.ACVoltCntr >= mVARTimerTag.ACVoltTime && (acVolt_pfcVol_err > 0 && acVolt_pfcVol_err >= ACVolt_pfcVolt_err_u16))
		{
			mVARCntrTag.ACVoltCntr = 0;
			stSysFSMCtrl.ucCurrentState = STATE_PFC_RUN;
		}
		*/
		/*
		if(acVolt_pfcVol_absErr <=  ACVolt_pfcVolt_err_u16)
		{
			mVARCntrTag.acVolt_pfcVol_errCntr = 0;
		}
		else
		{
			mVARCntrTag.acVolt_pfcVol_errCntr++;
		}
		
		if(mVARCntrTag.ACVoltCntr >= mVARTimerTag.ACVoltTime && acVolt_pfcVol_absErr <=  ACVolt_pfcVolt_err_u16)
		{
			mVARCntrTag.ACVoltCntr = 0;
			stSysFSMCtrl.ucCurrentState = STATE_PFC_RUN;
		}
		*/
		
		else if(mVARCntrTag.acVolt_pfcVol_errCntr >= mVARTimerTag.acVolt_pfcVol_errTime)
		{
			//10s内pfc母线电压和ac电压的峰值 还 不能满足条件
			mVARCntrTag.ACVoltCntr = 0;
			mVARCntrTag.acVolt_pfcVol_errCntr = 0;
			stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
			//goPREFAILURE();
		}
		else if(mVARCntrTag.ACVoltCntr >=  mVARTimerTag.acVolt_pfcVol_errTime)
		{
			//10s AC 峰值不高于 105
			mVARCntrTag.ACVoltCntr = 0;
			mVARCntrTag.acVolt_pfcVol_errCntr = 0;
			stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
			//goPREFAILURE();
		}
		
		
		
	}

	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}
}
/*
PFCRun
1. 置位O_S_RlyCTL1,并延时100ms；
//2.置位GLB_EN
3. 置位O_PFC_DRV_EN
4. 拉低 O_PFC_EN
*/
void in_PFC_RUN() {
	uint8_t ucStateRecd = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;

	if (stSysFSMCtrl.ucLastState != STATE_PFC_RUN)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
		O_S_RlyCTL1 = HIGH;
		mStateCntrTag.PFC_RUNCntr = 0;
		//O_S_RlyCTL2 = HIGH;//调试使用跳过DCDC预充

	}else{
		
	}
	
	if(mStateCntrTag.PFC_RUNCntr >= mStateTimerTag.PFC_RUNTime)
	{
		//mStateCntrTag.PFC_RUNCntr = 0;
		//O_PFC_DRV_EN = HIGH;
		//O_PFC_EN = LOW;
		//TEST1 = LOW;
		if(pfcEnAtACzeroState == TRUE)
		{
			O_PFC_EN = HIGH;
		//	TEST1 = LOW;
		}
		else
		{
			stSysFSMCtrl.ucLastState = ucStateRecd;
			if(mStateCntrTag.PFC_RUNCntr == mStateTimerTag.PFC_RUNTime)
			{
				mStateCntrTag.PFC_RUNCntr ++;
			}
			glbDiag(ucStateRecd);
			return;
		}
		
	
	}
	else
	{
		mStateCntrTag.PFC_RUNCntr++;
		
		glbDiag(ucStateRecd);

		
		return;
	}
	
	//延时也需要诊断？？？后续加入
	
	/***************** 诊断  *********************/

	//故障诊断
	/*if ((faultCodeTag.uDWORD & ALL_FAULT_CODE_FLAG) != 0) {
		stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
	}*/
	if(glbDiag(ucStateRecd))
	{
		
	}
	else
	{
		//if(1)
		#ifndef AC_DIAG_ENABLE
			if(1)
		#else
			if(L3_I_AD_PFC_slow_Ct_u16 >= pfcRunToPreC2PfcVolt_Ct_u16)//需要加滤波处理，否则采到的大概需要50MS才满足条件
		#endif
		{
				#ifdef NEED_DCDCPrechange2
					O_PG = HIGH;
					O_MCU_FAT = LOW;
					stopAllPwm();
					stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE2;
				#else
				#ifndef PFC_DIAG_ENABLE
					if(1)
					#else
						if(L3_I_AD_PFC_slow_Ct_u16 >= k_Dcdc_startOnVref_Ct_u16)
					#endif
					{
						O_PG = HIGH;
						O_MCU_FAT = LOW;
						stopAllPwm();
						stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;//调试阶段，不需要预充
					}
			
				#endif	
		}
	
	
	}

	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}
}

/*
Precharge2
1. 置位O_DCDC_DRV_EN；
2.DCDC输出电容电压预充完成后，发送继电器闭合请求：CHR01_ReqCloseRly=1
*/
void in_PRECHARGE2() {
	uint8_t ucStateRecd = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;

	if (stSysFSMCtrl.ucLastState != STATE_PRECHARGE2)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
		mVARCntrTag.pre_changer2PGKeepCntr = 0;
//		osalThreadSleepMilliseconds(10);
		//O_DCDC_DRV_EN = HIGH;

	}else{

	}
	/***************** 诊断  *********************/

	//故障诊断
	/*if ((faultCodeTag.uDWORD & ALL_FAULT_CODE_FLAG) != 0) {
		stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
	}*/
	if(glbDiag(ucStateRecd))
	{
		
	}
	else
	{
		//1.预充
		//a)、继电器没有闭合（BMS04_ACChrRlySt=0）的情况下，DCDC输出电容电压（320V）预充完成后， 拉高PG信号
		//等待BMS04_ACChrRlySt=1
		//延时50ms
		//跳转到DCDC工作状态
		//b)、继电器闭合（BMS04_ACChrRlySt=1）的情况下，跳转到DCDC工作状态
		//2、回读BMS CAN cc信号 限流
		//if(bms_can_available && BMSTag.ACChrRlySt == OPEN_RLY)
		if(bms_can_available)
		{
		//if((L3_I_AD_PFC_slow_Ct_u16 >= preC2TodcOpetrationDCVolt_Ct_u16) && (L3_Dcdc_Vout_Ct_u16 >= L3_Dcdc_Vout_Precharge2))
		//	if((L3_I_AD_PFC_slow_Ct_u16 >= preC2TodcOpetrationDCVolt_Ct_u16) && (( (BMSTag.actVoltageADRow-L3_PRECHARGE2_BMS_OFFSET) <= L3_Dcdc_Vout_Ct_u16 &&  L3_Dcdc_Vout_Ct_u16<=(BMSTag.actVoltageADRow+L3_PRECHARGE2_BMS_OFFSET) || (O_PG == HIGH&&BMSTag.ACChrRlySt == CLOSE_RLY && BMSTag.EnCharger == TRUE)))
			//if((L3_I_AD_PFC_slow_Ct_u16 >= preC2TodcOpetrationDCVolt_Ct_u16) && (( (BMSTag.actVoltageADRow-L3_PRECHARGE2_BMS_OFFSET) <= L3_Dcdc_Vout_Ct_u16 &&  L3_Dcdc_Vout_Ct_u16<=(BMSTag.actVoltageADRow+L3_PRECHARGE2_BMS_OFFSET))))
			if((L3_I_AD_PFC_slow_Ct_u16 >= preC2TodcOpetrationDCVolt_Ct_u16) && (L5_precharge2_CMD_FLAG == TRUE) && (( L3_PRECHARGE2_BMS_MIN <= L3_Dcdc_Vout_Ct_u16 &&  L3_Dcdc_Vout_Ct_u16<= L3_PRECHARGE2_BMS_MAX)))
			//if((L3_I_AD_PFC_slow_Ct_u16 >= preC2TodcOpetrationDCVolt_Ct_u16) )
			{
				/*
				if(mVARCntrTag.pre_changer2PGKeepCntr<mVARTimerTag.pre_changer2PGKeepTime)
				{
					mVARCntrTag.pre_changer2PGKeepCntr ++;
				}
				else
				{
					O_PG = HIGH;
				}*/
				//O_PG = HIGH;
	  			//O_MCU_FAT = HIGH;
	  			//O_GLB_RSET = HIGH;
	  			//startAllPwm();
	  			if(bms_can_available)
				{
					OBCTag.ReqCloseRly = CLOSE_RLY;
					//等待超时 ?
					//if(BMSTag.ACChrRlySt == CLOSE_RLY && BMSTag.EnCharger == TRUE)
					if(BMSTag.PosRlySt == CLOSE_RLY && BMSTag.EnCharger == TRUE)
					
					{
						CONNECT_BMS_OK = TRUE;
						if(mStateCntrTag.PRECHARGE2Cntr >= mStateTimerTag.PRECHARGE2Time)
						{
							mStateCntrTag.PRECHARGE2Cntr = 0;
							
							//stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
							//*
							#ifndef CC_STATE_DIAG_ENABLE
								if(1)
							#else
								if(OBCTag.bFilterCCState == TRUE && OBCPOWERTag.CANCmdSETCurrent != 0)
							#endif
								{
									stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
								}
							//*/
							// 硬件去除 DCDC 输出继电器//////////
							//O_S_RlyCTL2 = HIGH;
							//mVARCntrTag.dcdcRelayCloseDelayCntr = 0;
	  						//opetrationDelayOver = FALSE;
	  						///////////////////////////////
						}
						else
						{
							mStateCntrTag.PRECHARGE2Cntr++;
						}
					}
				}
				else
				{
					if(mStateCntrTag.PRECHARGE2Cntr >= mStateTimerTag.PRECHARGE2Time)
					{
						mStateCntrTag.PRECHARGE2Cntr = 0;
					//stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
							//*
							#ifndef CC_STATE_DIAG_ENABLE
								if(1)
							#else
								if(OBCTag.bFilterCCState == TRUE && OBCPOWERTag.CANCmdSETCurrent != 0)
							#endif
								{
									stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
								}
							//*/
						///////////////////////////////
						//O_S_RlyCTL2 = HIGH;
						//mVARCntrTag.dcdcRelayCloseDelayCntr = 0;
	  					//opetrationDelayOver = FALSE;
	  					///////////////////////////////

					}
					else
					{
						mStateCntrTag.PRECHARGE2Cntr++;
					}
				}




			}
				/*
				//if Pre_changer2 to long,everyone 6s reset PG 
				if(mVARCntrTag.pre_changer2PGResetCntr >= mVARTimerTag.pre_changer2PGResetTime)
				{	
					if(O_PG == HIGH)
					{
						O_PG = LOW;	
						mVARCntrTag.pre_changer2PGResetCntr = 0;
						mVARCntrTag.pre_changer2PGKeepCntr = 0;
					}
					
				}
				else
				{
					mVARCntrTag.pre_changer2PGResetCntr++;
					stSysFSMCtrl.ucLastState = ucStateRecd;
					return;
				}	
				*/
			}
			else
			{
				//stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;//不接电池包， 调试阶段，不需要预充
				if((L3_I_AD_PFC_slow_Ct_u16 >= preC2TodcOpetrationDCVolt_Ct_u16) && (L3_Dcdc_Vout_Ct_u16 >= L3_Dcdc_Vout_Precharge2))
				{
				
					O_PG = HIGH;
		  			//O_MCU_FAT = HIGH;
		  			//O_GLB_RSET = HIGH;
		  			startAllPwm();
		  			//delay sometime to OPETRATION state
		  			if(mStateCntrTag.PRECHARGE2Cntr >= mStateTimerTag.PRECHARGE2Time)
					{
						mStateCntrTag.PRECHARGE2Cntr = 0;
						//stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
							//*
							#ifndef CC_STATE_DIAG_ENABLE
								if(1)
							#else
								if(OBCTag.bFilterCCState == TRUE && OBCPOWERTag.CANCmdSETCurrent != 0)
							#endif
								{
									stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
								}
							//*/
						///////////////////////////////
						//O_S_RlyCTL2 = HIGH;
						//mVARCntrTag.dcdcRelayCloseDelayCntr = 0;
	  					//opetrationDelayOver = FALSE;
	  					///////////////////////////////

					}
					else
					{
						mStateCntrTag.PRECHARGE2Cntr++;
					}




				}
			}
		
	
			
				
			if(mVARCntrTag.pre_changer2PGKeepCntr>=mVARTimerTag.pre_changer2PGKeepTime)
			{
				
				//stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;//超过3min钟 进入 afterRun
				stSysFSMCtrl.ucCurrentState = STATE_STANDBY;//超过3min钟 进入 STANDBY
			}
			else
			{
				mVARCntrTag.pre_changer2PGKeepCntr ++;
			}
		
		
		
		
		
		
		
		
		
		
		
		
		
		//DCDC输出电容电压（320V）预充完成后， 拉高PG信号
		//等待BMS04_ACChrRlySt=1
		//延时50ms
		//跳转到DCDC工作状态
		/*
		if((L3_I_AD_PFC_slow_Ct_u16 >= preC2TodcOpetrationDCVolt_Ct_u16) && (L3_Dcdc_Vout_Ct_u16 >= L3_Dcdc_Vout_Precharge2))
		{

			O_PG = HIGH;
  			O_MCU_FAT = HIGH;
  			O_GLB_RSET = HIGH;
  			if(bms_can_available)
			{
				OBCTag.ReqCloseRly = CLOSE_RLY;
				if(BMSTag.ACChrRlySt == CLOSE_RLY)
				{
					if(mStateCntrTag.PRECHARGE2Cntr >= mStateTimerTag.PRECHARGE2Time)
					{
						mStateCntrTag.PRECHARGE2Cntr = 0;
						stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
						// 硬件去除 DCDC 输出继电器//////////
						//O_S_RlyCTL2 = HIGH;
						//mVARCntrTag.dcdcRelayCloseDelayCntr = 0;
  						//opetrationDelayOver = FALSE;
  						///////////////////////////////
					}
					else
					{
						mStateCntrTag.PRECHARGE2Cntr++;
					}
				}
			}
			else
			{
				if(mStateCntrTag.PRECHARGE2Cntr >= mStateTimerTag.PRECHARGE2Time)
				{
					mStateCntrTag.PRECHARGE2Cntr = 0;
					stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;
					///////////////////////////////
					//O_S_RlyCTL2 = HIGH;
					//mVARCntrTag.dcdcRelayCloseDelayCntr = 0;
  					//opetrationDelayOver = FALSE;
  					///////////////////////////////

				}
				else
				{
					mStateCntrTag.PRECHARGE2Cntr++;
				}
			}




		}
		*/
		
	}

	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}
}

void in_OPETRATION() {
	uint8_t ucStateRecd = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;

	if (stSysFSMCtrl.ucLastState != STATE_OPETRATION)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
  		//O_GLB_RSET = HIGH;
  		startOver = 0;
  		/*
  		O_S_RlyCTL2 = HIGH;
  		opetrationDelayOver = FALSE;
  		mVARCntrTag.dcdcRelayCloseDelayCntr = 0;
  		*/
		OBC_initialize();
		(void)mPWM_offset_Advance((0),0);
		L3_last_OBC_Y_Ct_u16  = 0xffff;
		//O_MCU_FAT = HIGH;
		startAllPwm();
	

	}
	else
	{
		O_GLB_RSET = LOW;
	}
	/*
	if(mVARCntrTag.dcdcRelayCloseDelayCntr >= mVARTimerTag.dcdcRelayCloseDelayTime)
	{
		O_MCU_FAT = HIGH;
		opetrationDelayOver = TRUE;
	}
	else
	{
		mVARCntrTag.dcdcRelayCloseDelayCntr++;
		stSysFSMCtrl.ucLastState = ucStateRecd;
		return;
	}	
	*/
	
	/***************** 诊断  *********************/


	//故障诊断
	glbDiag(ucStateRecd);

	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}
}

/*

After run
1. 关闭DCDC的PWM输出；
2. 拉低O_DCDC_DRV_EN，延迟10ms；
3.拉低O_PFC_EN，O_PFC_DRV_EN，延迟10ms
4.拉低GLB_EN;延迟10ms
5.拉低O_S_RlyCTL1
*/

void in_AFTER_RUN() {
	uint8_t ucStateRecd = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;

	if (stSysFSMCtrl.ucLastState != STATE_AFTER_RUN)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
		mVARCntrTag.afterRunPFC_enCntr = 0;
		mVARCntrTag.afterRunACRelayDelayCntr = 0;
		mVARCntrTag.afterRunGlbEnCntr = 0;
		OBCTag.ReqCloseRly = OPEN_RLY;
//		osalThreadSleepMilliseconds(10);

	}else{
		
	}
	
	//1、PG信号拉低 并且断开S2。
	//2  关闭28070 拉低O_PFC_EN ，delay 10ms  AC继电器 OR  2、AC继电器 关闭28070 拉低O_PFC_EN
	// delay 10ms
	//3. DCDC的PWM输出1%进行放电，检测电压少于60V，或者超过5分钟拉低GLB_EN(mcu_fat)；
	
	O_PG = LOW;
	S2_CTR = LOW;
	
	
	O_PFC_EN = LOW;
	if(mVARCntrTag.afterRunPFC_enCntr >= mVARTimerTag.afterRunPFC_enTime)
	{
	
	}
	else
	{
		mVARCntrTag.afterRunPFC_enCntr++;
		stSysFSMCtrl.ucLastState = ucStateRecd;
		return;
	}	
	O_S_RlyCTL1 = LOW;
	
	if(mVARCntrTag.afterRunACRelayDelayCntr >= mVARTimerTag.afterRunACRelayDelayTime)
	{
	
	}
	else
	{
		mVARCntrTag.afterRunACRelayDelayCntr++;
		stSysFSMCtrl.ucLastState = ucStateRecd;
		return;
	}	
	
	
	//if((L3_I_AD_PFC_slow_Ct_u16 <= L3_PFC_Vout_AfterRun ) || (mVARCntrTag.afterRunGlbEnCntr >= mVARTimerTag.afterRunGlbEnTime))
	//no need discharge the PFC voltage,so,it can sleep quickly.
	if(1)
	{
			//O_MCU_FAT = LOW;
			stopAllPwm();
	}
	else
	{
		mVARCntrTag.afterRunGlbEnCntr++;
		stSysFSMCtrl.ucLastState = ucStateRecd;
		return;
	}
	
	#ifdef NEED_SLEEP
		stSysFSMCtrl.ucCurrentState = STATE_SLEEP;
	#endif

	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}
}

void in_SLEEP() {
	uint8_t ucStateRecd = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;

	if (stSysFSMCtrl.ucLastState != STATE_SLEEP)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
//		osalThreadSleepMilliseconds(10);

	}else{

	}
	
	SBC_L3_CfgSleepMode();
	
}
//failure状态需要关闭DCDC的PWM输出，关闭PFC使能，断开输入继电器，并且断开S2。输出继电器暂时不做处理。
void in_FAILURE() {
	uint8_t ucStateRecd = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;

	if (stSysFSMCtrl.ucLastState != STATE_FAILURE)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
		mVARCntrTag.afterRunPFC_enCntr = 0;
		mVARCntrTag.afterRunACRelayDelayCntr = 0;
		mVARCntrTag.afterRunGlbEnCntr = 0;
		OBCTag.ReqCloseRly = OPEN_RLY;
	}else{

	}

	O_PFC_EN = LOW;
	if(mVARCntrTag.afterRunPFC_enCntr >= mVARTimerTag.afterRunPFC_enTime)
	{
	
	}
	else
	{
		mVARCntrTag.afterRunPFC_enCntr++;
		stSysFSMCtrl.ucLastState = ucStateRecd;
		return;
	}	
	O_S_RlyCTL1 = LOW;
	
	if(mVARCntrTag.afterRunACRelayDelayCntr >= mVARTimerTag.afterRunACRelayDelayTime)
	{
	
	}
	else
	{
		mVARCntrTag.afterRunACRelayDelayCntr++;
		stSysFSMCtrl.ucLastState = ucStateRecd;
		return;
	}	

	//O_MCU_FAT = LOW;
	stopAllPwm();

	if(bms_can_available)
	{
		//if(O_PG == HIGH)
		if(CONNECT_BMS_OK == TRUE)
		{
			//与BMS通信建立完好，接受BMS 指令 正常下电,响应瞬速
			if(BMSTag.EnCharger == BMS_DIS_CHARGER || L3_S_BMSMsgTimeOut_Uls_G_u08 )
			{
				//stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
				//O_PG = LOW;
				//BMS_CHARGE_OVER = TRUE;
				//goStandBy();
				//return;
			}
		}
		else
		{

		}
		

	}
	
	if(faultCodeTag.bit.bUnderUinVolt == TRUE)
	{
		stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
		FSM_run();
		return;
	}


	/***************** 诊断  *********************/


	/***************** 最终状态  *********************/
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}
}


void in_PREFAILURE(void)
{
	
	uint8_t ucStateRecd = 0;
	static uint8_t O_GLB_RSET_CNT = O_GLB_RSET_DELAYToHightTIME;
	static uint8_t O_GLB_RSET_needFlag = 0;
	ucStateRecd = stSysFSMCtrl.ucCurrentState;
	
	if (stSysFSMCtrl.ucLastState != STATE_PREFAILURE)
	{
		stSysFSMCtrl.ucLastSysState = stSysFSMCtrl.ucLastState;
		//powerDown();
	}else{

	}
	
	if(L5_AC_FAULT == TRUE)
	{
		powerDown();
	}

	
	if((faultCodeTag.uDWORD & DCDC_FAULT_CODE_FLAG) != FALSE)
	{
		stopDcdc();
	}
	
	
	if((faultCodeTag.uDWORD & PFC_DCDC_DOWN_FAULT) != FALSE)
	{
		powerDown();
	}
	
	
	if((faultCodeTag.uDWORD & HW_FAULT) != FALSE)
	{
		
		if(faultCodeTag.bit.bHWDCDC_OVP == TRUE && mHWInResetTag.HWDCDC_OVPInReset != TRUE)
		{
			mHWInResetTag.HWDCDC_OVPInReset = 1;//硬线reset中...
			O_OVP_RSET = HIGH;
			O_GLB_RSET_needFlag = 1;
			O_GLB_RSET_CNT = 0;
		}


		if(faultCodeTag.bit.bHWDCDC_OCP == TRUE && mHWInResetTag.HWDCDC_OCPInReset != TRUE)
		{
			if(L3_I_AD_PFC_slow_Ct_u16 >= pfcPreFailureVolt_Ct_u16)
			{
				stopDcdc();
			}
			else
			{
				powerDown();
			}
			mHWInResetTag.HWDCDC_OCPInReset = 1;//硬线reset中...
			O_OCP_RSET = HIGH;
			O_GLB_RSET_needFlag = 1;
			PWM_OCP_softRest();
			O_GLB_RSET_CNT = 0;
		}

		if(faultCodeTag.bit.bHWPFC_OVP == TRUE && mHWInResetTag.HWPFC_OVPInReset != TRUE)
		{
			mHWInResetTag.HWPFC_OVPInReset = 1;//硬线reset中...
			O_PFC_OVP_RSET = HIGH;
			O_GLB_RSET_needFlag = 1;
			O_GLB_RSET_CNT = 0;
		}
		if(faultCodeTag.bit.bHWPFC_OCP == TRUE && mHWInResetTag.HWPFC_OCPInReset != TRUE)
		{
			mHWInResetTag.HWPFC_OCPInReset = 1;//硬线reset中...
			O_PFC_OCP_RSET = HIGH;
			O_GLB_RSET_needFlag = 1;
			O_GLB_RSET_CNT = 0;
		}

		if(O_GLB_RSET_CNT < O_GLB_RSET_DELAYToHightTIME){
			O_GLB_RSET_CNT ++;
		}else{
			if(O_GLB_RSET_needFlag){
				O_GLB_RSET_needFlag = 0;
				O_GLB_RSET = HIGH;
				if(mHWInResetTag.HWDCDC_OVPInReset){
					O_OVP_RSET = LOW;
					mHWInResetTag.HWDCDC_OVPInReset = FALSE;//reset 执行完毕
				}
				if(mHWInResetTag.HWDCDC_OCPInReset){
					O_OCP_RSET = LOW;
					mHWInResetTag.HWDCDC_OCPInReset = FALSE;//reset 执行完毕
					//stateCntTag.HWDCDC_OCPStateCnt++;
				}

				if(mHWInResetTag.HWPFC_OVPInReset){
					O_PFC_OVP_RSET = LOW;
					mHWInResetTag.HWPFC_OVPInReset = FALSE;//reset 执行完毕
				}
				if(mHWInResetTag.HWPFC_OCPInReset){
					O_PFC_OCP_RSET = LOW;
					mHWInResetTag.HWPFC_OCPInReset = FALSE;//reset 执行完毕
				}
			}
		}
	}



	//***************** 诊断  ********************
	//故障诊断
	/*if ((faultCodeTag.uDWORD & ALL_FAULT_CODE_FLAG) != 0) {
		stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
	}*/
	if(glbDiag(ucStateRecd))
	{
		
	}
	else
	{

		//如果某些故障恢复则跳转到STANDBY状态
		/*
		O_MCU_FAT = HIGH;
		O_GLB_RSET = HIGH;
		(void)mPWM_offset_Advance((0),0);
		*/
		
		if(O_PFC_EN == LOW)
		{
			stSysFSMCtrl.ucCurrentState = STATE_STANDBY;
		}
		else
		{
			//stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE2;
			
			#ifdef NEED_DCDCPrechange2
					stSysFSMCtrl.ucCurrentState = STATE_PRECHARGE2;
				#else
					stSysFSMCtrl.ucCurrentState = STATE_OPETRATION;//调试阶段，不需要预充
				#endif	
		}
	}
	//***************** 最终状态  *********************
//		if (ucStateRecd != stSysFSMCtrl.ucCurrentState) {
//			stSysFSMCtrl.ucStateUnkonw = 0;
			stSysFSMCtrl.ucLastState = ucStateRecd;
//		}

}

void app_stateflow_task(void) {
	FSM_run();
	if(acVoltSampleTimeCnt >= acVoltSampleTimeMax)
	{
		//20ms 采集一次ac volt 峰值
		L5_AC_Volt_fast_max_buff = L3_AD0_AC_Volt_fast_max_Ct_u16;
		//L5_AC_Volt_fast_maxBuffCPS = (uint16)(LCPS_FACTOR*(float)L5_AC_Volt_fast_max_buff + LCPS_OFFSET);
		L5_AC_Volt_fast_maxBuffCPS = (uint16)AC_VOLT_AD_CONVERT(LCPS_FACTOR*(float)AC_AD_CONVERT_VOLT(L5_AC_Volt_fast_max_buff) + LCPS_OFFSET);

		
		L3_AD0_AC_Volt_fast_max_Ct_u16 = 0;
		
		L5_AC_current_max_buff = L3_I_AD_Curr_InputMax_Ct_u16;
		L3_I_AD_Curr_InputMax_Ct_u16 = 0;
		
		acVoltSampleTimeCnt = 0;  	
	}
	else
	{
		acVoltSampleTimeCnt++;
	}
	

	/*
	if(bms_can_available)
	{
		if(stSysFSMCtrl.ucLastState != STATE_OPETRATION || stSysFSMCtrl.ucLastState != STATE_PRECHARGE2)
		{
			OBCTag.ReqCloseRly = OPEN_RLY;
		}
		else
		{
			//OBCTag.ReqCloseRly = OPEN_RLY;
		}
	}
	else
	{
		OBCTag.ReqCloseRly = CLOSE_RLY;
	}
	*/
	//setResetIOLow();
	
	 //SBC_L3_Per();   
	 

}


void setResetIOLow(void) {
	static uint8_t O_GLB_ResetToLow_CNT = 0;
	if(O_GLB_RSET == HIGH){
		if(O_GLB_ResetToLow_CNT >= O_GLB_RSET_DELAYToLowTIME){
			O_GLB_RSET = LOW;
		}else{
			O_GLB_ResetToLow_CNT++;
		}
	}else{
		O_GLB_ResetToLow_CNT = 0;
	}

}

void stopDcdc(void)
{
	
	(void)mPWM_offset_Advance((0),0);
	//O_MCU_FAT = LOW;
	stopAllPwm();
	
	OBC_initialize();
}

void startDcdc(void)
{
	OBC_initialize();
	(void)mPWM_offset_Advance((0),0);
	//O_MCU_FAT = HIGH;
	//O_GLB_RSET = HIGH;
	startAllPwm();
}

void powerDown(void) {
	//O_PG = LOW;
	//OBCTag.ReqCloseRly = OPEN_RLY;
	
	(void)mPWM_offset_Advance((0),0);
	//failure状态需要关闭DCDC的PWM输出，关闭PFC使能，断开输入继电器，并且断开S2。输出继电器暂时不做处理。

//	O_PFC_DRV_EN = LOW;
	//O_PFC_EN = HIGH;
	O_PFC_EN = LOW;
	
	//O_S_RlyCTL2 = LOW;
	
	O_S_RlyCTL1 = LOW;
	
	
	
	//O_MCU_FAT = LOW;
	stopAllPwm();
	
	S2_CTR = LOW;
	
	OBC_initialize();
	
	
}


void goStandBy(void)
 {
	
	
	(void)mPWM_offset_Advance((0),0);
	

	O_PFC_EN = LOW;
	
	O_S_RlyCTL1 = LOW;
	
	//O_MCU_FAT = LOW;
	stopAllPwm();
	
	//S2_CTR = LOW;
	
	if(	stSysFSMCtrl.ucCurrentState != STATE_STANDBY && stSysFSMCtrl.ucCurrentState  != STATE_INIT  && stSysFSMCtrl.ucCurrentState  != STATE_FAILURE && stSysFSMCtrl.ucCurrentState  != STATE_AFTER_RUN)
	{
		stSysFSMCtrl.ucCurrentState = STATE_STANDBY;
		FSM_run();
	}

	OBC_initialize();

}

void goPREFAILURE(void)
 {
	if(stSysFSMCtrl.ucCurrentState != STATE_PREFAILURE && stSysFSMCtrl.ucCurrentState  != STATE_INIT  && stSysFSMCtrl.ucCurrentState  != STATE_FAILURE && stSysFSMCtrl.ucCurrentState  != STATE_AFTER_RUN)
	{
		stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
		//FSM_run();
	}
}



BOOL glbDiag(uint8_t ucStateRecd) {
	BOOL ret = FALSE;
	//故障诊断
	if(0)
	{
		stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
		ret = TRUE;
	}
	else if ((faultCodeTag.uDWORD & ALL_FAULT_CODE_FLAG) != 0) {
		//stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
		goPREFAILURE();
		ret = TRUE;
	}
	else
	{
		#ifdef AC_DIAG_ENABLE
		//AC 电源异常，OBC 直接 跳回standby，CAN DBC 做一个5s 防抖再发给BMS
		if(AC_Volt_fast_limtLow_Ct_u16 > L5_AC_Volt_fast_maxBuffCPS || L5_AC_Volt_fast_maxBuffCPS > AC_Volt_fast_maxHigh_Ct_u16)
		{
			//这里也需要防抖
			CONNECT_BMS_OK = FALSE;
			
			if(stSysFSMCtrl.ucCurrentState == STATE_OPETRATION)
			{
				L5_AC_FAULT = TRUE;
				stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
				FSM_run();
				ret = TRUE;
				return ret;
				
			}
			else
			{
				
				//stSysFSMCtrl.ucCurrentState = STATE_PREFAILURE;
				goPREFAILURE();
			}
			
		
			ret = TRUE;
		}
		#endif
	}
	//进入afterRun的条件
	//1、与BMS 通信正常后，收到指令进入
	//2、AC异常情况下，5s debunce进入
	//3、AC正常情况下，与BMS一直不正常，等待3 min钟进入afterRun
	if(bms_can_available)
	{
		//if(O_PG == HIGH)
		if(CONNECT_BMS_OK == TRUE )
		{
			//与BMS通信建立完好，接受BMS 指令 正常下电,响应瞬速
			if(BMSTag.EnCharger == BMS_DIS_CHARGER || L3_S_BMSMsgTimeOut_Uls_G_u08 )
			{
				/*
				stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
				FSM_run();
				ret = TRUE;
				return ret;
				*/
				O_PG = LOW;
				BMS_CHARGE_OVER = TRUE;
				goStandBy();
				ret = TRUE;
				return ret;
			}
		}
		else
		{
			//与BMS通信还未建立好 任何状态不轻易进入afterRun，当检测到AC欠压时候。再进入afterRun
			
			if(faultCodeTag.bit.bUnderUinVolt == TRUE)
			{
				stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
				FSM_run();
				ret = TRUE;
				return ret;
			}
		}
		

	}
	else
	{
		#ifdef  NEED_SLEEP 
		if(faultCodeTag.bit.bUnderUinVolt == TRUE)
		{
			stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
			FSM_run();
			ret = TRUE;
			return ret;
		}
		#endif
	}
	
	if(L5_OBC_cmd == POWEROFF)
	{
		stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
	}
	
	stSysFSMCtrl.ucLastState = ucStateRecd;
	return ret;
}


void stopAllPwm(void)
{
	mPWM_Sub_All_Stop();
	O_MCU_FAT = LOW;
}
void startAllPwm(void)
{
	PWM_OCP_softRest();
	O_MCU_FAT = HIGH;
	O_GLB_RSET = HIGH;
}