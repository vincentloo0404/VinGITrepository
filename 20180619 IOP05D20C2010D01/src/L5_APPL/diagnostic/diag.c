/*
 * diag.c
 *
 *  Created on: 2016年4月21日
 *      Author: YCH
 */

#include "diag.h"
#include "dDiagDec.h"
#include "L5_APPL.h"
void Driver13V_diag_handle(void);
static void LV_12V_diag_handle(void);

static void PG_diag_handle(void);
static void CP_diag_handle(void);
static void CPVolt_diag_handle(void);
static void CCState_diag_handle(void);

static void Uin_diag_handle(void);

static void HWPFC_OVP_diag_handle(void);
static void PFC_Uout_diag_handle(void);
static void HWPFC_OCP_diag_handle(void);
static void PFC_Iout_diag_handle(void);

static void HWDCDC_OVP_diag_handle(void);
static void DCDC_Uout_diag_handle(void);
static void DCDC_Iout_diag_handle(void);
static void HWDCDC_OCP_diag_handle(void);

static void loadDump_diag_handle(void);
static void temperature_diag_handle(void);
static void TempPowerLimit_diag_handle(void);
static uint16 CurrentLimtKeepValueInTime(uint16	newCurrentLimt,uint16	oldCurrentLimt);

static void autoLimtCurrent(void);


void StateTimeOut_diag_handle(void);


static void dcdc_start_short_circuit(void);

static void getMinCurrent(void);

static int16_t  getTemperatureValue(uint16_t uiInputVlt,uint8_t tempTableId);
uint8 ChrPlugIn_diag_handle(void);
uint8_t powerStartCnt = POWER_CNT;


//uint16_t Driver13V_limtLow_Ct_u16 = V13_VOLT_AD_CONVERT(V13_DIAG_Volt_MIN);  
//uint16_t Driver13V_maxHigh_Ct_u16 = V13_VOLT_AD_CONVERT(V13_DIAG_Volt_MAX);  

uint16_t Driver13V_limtLow_Ct_u16 = 190;  
uint16_t Driver13V_maxHigh_Ct_u16 = 266; 

uint16_t LV_12V_limtLow_Ct_u16 = V12_VOLT_AD_CONVERT(V12_DIAG_Volt_MIN);  
uint16_t LV_12V_maxHigh_Ct_u16 = V12_VOLT_AD_CONVERT(V12_DIAG_Volt_MAX); 
//uint16_t VRelayCoil1High_Ct_u16 = VRelayCoil1_VOLT_AD_CONVERT(VRelayCoil1_DIAG_Volt_MAX);

uint16_t PG_limtLow_Ct_u16 = 274; //*(38.56623377)
uint16_t PG_maxHigh_Ct_u16 = 777; //17*(38.56623377) //?V~?V

/*
uint16_t AC_Volt_fast_limtLow_Ct_u16 = 184; //85*(1.531475187) *1.414
uint16_t AC_Volt_fast_maxHigh_Ct_u16 = 574; //265*(1.531475187) * 1.414  有效值 85V~265V
*/


uint16_t AC_Volt_fast_limtLow_Ct_u16 = AC_VOLT_AD_CONVERT_peak(AC_DIAG_Volt_MIN); //(2.5+(0.005*85))*1024/5*1.414
uint16_t AC_Volt_fast_maxHigh_Ct_u16 = AC_VOLT_AD_CONVERT_peak(AC_DIAG_Volt_MAX); //(2.5+(0.005*265))*1024/5*1.414  有效值 85V~265V
uint16_t AC_Volt_fast_OpenVolt_Ct_u16 = AC_VOLT_AD_CONVERT_peak(AC_DIAG_OPEN_Volt_MIN); //(2.5+(0.005*265))*1024/5*1.414  有效值 85V~265V


//volatile uint16 Dcdc_outVoltMax = (uint16) (410 * 1024 / 500);
//volatile uint16 Dcdc_outVoltLim = (uint16) (250 * 1024 / 500);

volatile uint16 Dcdc_outVoltMax = (uint16) DCDC_VOLT_AD_CONVERT(DCDC_DIAG_VOUT_MAX);
volatile uint16 Dcdc_outVoltLim = (uint16) DCDC_VOLT_AD_CONVERT(DCDC_DIAG_VOUT_MIN);
volatile uint16 Dcdc_outVoltShortCircuitLim = (uint16) DCDC_VOLT_AD_CONVERT(DCDC_DIAGShortCircuitVOUT_MIN);

volatile uint16 Dcdc_IoutMax = (uint16) DCDC_CURRENT_AD_CONVERT(DCDC_DIAG_IOUT_MAX);//dcdc输出电流
volatile uint16 Curr_Input_IoutMax = (uint16)AC_CURRENT_AD_CONVERT(DIAG_Curr_Input_IoutMax);// AC输入电流
//L3_I_AD_Curr_Input
volatile uint16 PFC_outVoltMax = PFC_VOLT_AD_CONVERT(PFC_DIAG_VOUT_MAX);//450*(2.01542149)//PFC输出电压
volatile uint16 PFC_outVoltLim = PFC_VOLT_AD_CONVERT(PFC_DIAG_VOUT_MIN);//380*(2.01542149)//PFC输出电压

volatile uint16 Dcdc_IoutFullMax = DCDC_CURRENT_AD_CONVERT(DCDC_DIAG_IOUT_FULL);//(uint16) ((12 + 2.5) * 71.68);//dcdc满功率输出电流
volatile sint16 PowerLimt_TEMP_Low = 65;//功率限制起始温度，超过线性限制 [(0,12A) (65,12A),(80,0)]
volatile sint16 PowerLimt_TEMP_Max = 80;//功率限制最大温度 超过不输出

volatile uint16 loadDumpLastVolt = 0;
//volatile uint16 loadDumpRefCurrent = (uint16) ((0.5 + 2.5) * 71.68);
volatile uint16 loadDumpRefCurrent = (uint16) ((0.5 + 2.5) * 49.152);
volatile uint16 loadDumpRefK = 20;
//volatile uint16 loadDumpUpVal = (uint16)(90*1024/500);
volatile uint16 loadDumpUpVal =   DCDC_VOLT_AD_CONVERT(90);
volatile sint16 loadDumpUpMaxVal = 0;
FaultCodeTag faultCodeTag = { 0 };
FaultCodeMoreTag faultCodeMoreTag = {0};
DiagCtrlTag diagCtrlTag = { 0 };
DiagRecoverTag diagRecoverTag = { 0 };

DiagDelayTag diagDelayTag = { 0 };

StateCntTag stateCntTag = { 0 };
uint16_t maxValue = 0;
uint16_t errormaxValue = 0;

RuntimerCntTag runtimerCntTag = { 0 };
HWInResetTag mHWInResetTag = {0xff,0xff,0xff,0xff};

volatile uint32 cp_pwm_width_percent;
volatile uint16 CP_CurrentLimt;
volatile uint16 CP_CurrentLimt1;

volatile uint16 L5_CP_CurrentPhy_1000dLimt = MAX_CURRENT_INIT;
volatile uint16 L5_CC_CurrentPhy_1000dLimt = MAX_CURRENT_INIT;


volatile uint16 L5_PowerLimtEnable = TRUE;
volatile uint16 L5_InputPowerLimt = MAX_POWER_INIT;
volatile uint16 L5_currentPowerLimt = MAX_POWER_INIT;
volatile uint16 L5_outPowerLimt = MAX_POWER_INIT;
volatile uint16 L5_actInputCurrentE = 0;
volatile uint16	l5_limtOutputVoltage = 0;
volatile uint8 l5_CurrentLimtTimer = 10;
volatile uint8 l5_powerLimtTimer = 10;
volatile uint8 l5_limtRampCnt = 5;


uint16 cp_pwm_senceCnt = 0;
const uint16 cp_pwm_senceTime = 6000 / DIAG_THREAD_CYCLE_TIME;//cp_pwm_senceTime CP 检查时间 ;

sint16 derating_TEM = 0;
sint16 protect_TEM = 0;

uint32 StateTimeOutCnt = 0;
//const uint32 StateTimeOutTime = 180000;// 状态timeout 3min 时间 ;
const uint32 StateTimeOutTime = 180000 / DIAG_THREAD_CYCLE_TIME;// 状态timeout 3min 时间 ;


uint8_t diagLastSysState = 0;

uint16 CP_CurrentLimt_buffter = 0;

const DiagTimerTag diagTimerTag = {

10 / DIAG_THREAD_CYCLE_TIME, //HWDCDC_OVPTime
		1000 / DIAG_THREAD_CYCLE_TIME, //OverDCUoutITime
		80/ DIAG_THREAD_CYCLE_TIME, //OverUinVoltTime
		1000/ DIAG_THREAD_CYCLE_TIME, //UnderUinVoltTime 

		20 / DIAG_THREAD_CYCLE_TIME, //OverDCUoutVoltTime
		30 / DIAG_THREAD_CYCLE_TIME, //UnderDCUoutVoltTime
		30 / DIAG_THREAD_CYCLE_TIME, //HWDCDC_OCPTime
		1000 * 10 / DIAG_THREAD_CYCLE_TIME, //OverTempCoolTime

		1000 * 10 / DIAG_THREAD_CYCLE_TIME, //loadDumpTime
		//1000 * 10 / DIAG_THREAD_CYCLE_TIME, //Driver13VFaultTime//
		//80 / 80, //Driver13VFaultTime//优先级比较高移动到80us
		0, //Driver13VFaultTime//优先级比较高移动到20us
		1000 * 10 / DIAG_THREAD_CYCLE_TIME, //LV12VFaultTime
		1000 * 10 / DIAG_THREAD_CYCLE_TIME, //HWPFC_OVPTime
		1000 * 10 / DIAG_THREAD_CYCLE_TIME, //HWPFC_OCPTime
		1000 / DIAG_THREAD_CYCLE_TIME, //OverPFCUoutVoltTime
		1000 / DIAG_THREAD_CYCLE_TIME, //UnderPFCUoutVoltTime
		1000/ DIAG_THREAD_CYCLE_TIME, //OverPFCUoutITime
		
		1000 * 5 / DIAG_THREAD_CYCLE_TIME, //TempDeratingTime
		1000 * 5 / DIAG_THREAD_CYCLE_TIME, //TempWarinOutOffTime
		1000 * 5 / DIAG_THREAD_CYCLE_TIME //OverTempTime

};

const DiagRecoverTimerTag diagRecoverTimerTag = {

5000 / DIAG_THREAD_CYCLE_TIME, //HWDCDC_OVPRecoverTime
		5000 / DIAG_THREAD_CYCLE_TIME, //OverDCUoutIRecoverTime
		2000 / DIAG_THREAD_CYCLE_TIME, //UinVoltRecoverTime
		500 / DIAG_THREAD_CYCLE_TIME, //DCUoutVoltRecoverTime
		0 / DIAG_THREAD_CYCLE_TIME, //HWDCDC_OCPRecoverTime
		0 / DIAG_THREAD_CYCLE_TIME, //OverTempCoolRecoverTime

		0 / DIAG_THREAD_CYCLE_TIME, //loadDumpRecoverTime
	//	0 / DIAG_THREAD_CYCLE_TIME, //Driver13VFaultRecoverTime//
	//	6250,//500*1000 / 80, //Driver13VFaultRecoverTime//优先级比较高移动到80us
		0,//500*1000 / 20, //Driver13VFaultRecoverTime//优先级比较高移动到20us
		500 / DIAG_THREAD_CYCLE_TIME, //LV12VFaultRecoverTime
		0 / DIAG_THREAD_CYCLE_TIME, //HWPFC_OVPRecoverTime
		0 / DIAG_THREAD_CYCLE_TIME, //HWPFC_OCPRecoverTime
		0 / DIAG_THREAD_CYCLE_TIME, //OverPFCUoutVoltRecoverTime
		0 / DIAG_THREAD_CYCLE_TIME, //PFCUoutVoltRecoverTime
		
		0 / DIAG_THREAD_CYCLE_TIME, //TempDeratingRecoverTime
		5000 / DIAG_THREAD_CYCLE_TIME, //TempWarinOutOffTime
		5000 / DIAG_THREAD_CYCLE_TIME //OverTempRecoverTime
};

const DiagDelayTimerTag diagDelayTimerTag = {

		0, //OverHWUoutVoltDelayTimer 不延时
		0, //OverSWUoutIDelayTimer  不延时
		0 / DIAG_THREAD_CYCLE_TIME, //UinVoltageDelayTimer  延时10ms不检测

		0, //UoutVolRecoverTime   不延时
		0, //OCPTime  不延时
		0 //OverTempCoolTime  不延时
		
		};

const RuntimerTag runtimerTag = { 60 * 1000 / DIAG_THREAD_CYCLE_TIME, //HWDCDC_OVPRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME, //OverDCUoutIRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME, //OverUinVoltRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME, //UnderUinVoltRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME, //OverDCUoutVoltRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME, //UnderDCUoutVoltRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME, //HWDCDC_OCPRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //OverTempCoolRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //loadDumpRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //Driver13VFaultRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //LV12VFaultRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //HWPFC_OVPRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //HWPFC_OCPRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //OverPFCUoutVoltRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //UnderPFCUoutVoltRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //OverPFCUoutIRuntimerTime
		60 * 1000 / DIAG_THREAD_CYCLE_TIME, //TempDeratingRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME, //TempWarinOutOffRuntimerTime
		5*60 * 1000 / DIAG_THREAD_CYCLE_TIME //OverTempRuntimerTime
};

const StateMaxCntTag stateMaxCntTag = {
		3, //HWDCDC_OVPStateMaxCnt
		3, //OverDCUoutIStateMaxCnt
		3, //OverUinVoltStateMaxCnt
		3, //UnderUinVoltStateMaxCnt
		3, //OverDCUoutVoltStateMaxCnt
		3, //UnderDCUoutVoltStateMaxCnt
		3, //HWDCDC_OCPStateMaxCnt
		3, //OverTempCoolStateMaxCnt
		3, //loadDumpStateMaxCnt
		3, //Driver13VFaultStateMaxCnt
		3, //LV12VFaultStateMaxCnt
		3, //HWPFC_OVPStateMaxCnt
		3, //HWPFC_OCPStateMaxCnt
		3, //OverPFCUoutVoltStateMaxCnt
		3, //UnderPFCUoutVoltStateMaxCnt
		3, //OverPFCUoutIStateMaxCnt
		3, //TempDeratingStateMaxCnt
		3, //TempWarinOutOffStateMaxCnt
		3 //OverTempStateMaxCnt
		};

#define I_AD_PCB_TEM_Table 0
#define I_AD_FB_TEM_Table 1
//const unsigned short FB_T_ADC_Count_X[] = { 25, 28, 31, 35, 39, 44, 50, 56,
//		63, 72, 81, 91, 102, 116, 131, 147, 165, 184, 205, 227, 250, 274, 297,
//		321, 344, 366, 386, 405, 421, 436, 449, 459, 468, 476 };
//
///********************************************************************/
///***             Degree celcius                                   ***/
///********************************************************************/
//const int FB_T_DegC_Y[] = { 125, 120, 115, 110, 105, 100, 95, 90, 85, 80, 75,
//		70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, -5, -10, -15,
//		-20, -25, -30, -35, -40 };

/*
volatile unsigned short FB_T_ADC_Count_X[46] = { 154,170,187,207,228,251,276,304,334,366,373, 379, 386, 393, 400, 407, 414, 422,
		429, 436, 444, 451, 459, 466, 474, 513, 554, 595, 636, 676, 715, 752, 788,
		820, 850,877, 901,922, 941, 956, 970, 981, 990, 998, 1004, 1009 };


volatile int FB_T_DegC_Y[46] = { 125, 120, 115, 110, 105, 100, 95, 90, 85, 80,79,78,77,76,75,74,73,72,71,
		70,69,68,67,66, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, -5, -10, -15,
		-20, -25, -30, -35, -40 };


volatile unsigned short PCB_T_ADC_Count_X[42] = { 18,20,23,26,29,33,38,43,49, 56, 64, 74, 85, 98, 113, 130,
		150, 173, 200, 230, 264, 302, 343, 389, 437, 487, 538, 589, 638, 685, 727,
		765, 799, 827, 850, 869, 884, 896, 905, 912, 917, 921 };

volatile int PCB_T_DegC_Y[42] = { 150,145,140,135,130,125, 120, 115, 110, 105, 100, 95, 90, 85, 80, 75,
		70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, -5, -10, -15,
		-20, -25, -30, -35, -40,-45,-50,-55 };
*/

const unsigned short FB_T_ADC_Count_X[42] = { 18,20,23,26,29,33,38,43,49, 56, 64, 74, 85, 98, 113, 130,
		150, 173, 200, 230, 264, 302, 343, 389, 437, 487, 538, 589, 638, 685, 727,
		765, 799, 827, 850, 869, 884, 896, 905, 912, 917, 921 };


const int FB_T_DegC_Y[42] = { 150,145,140,135,130,125, 120, 115, 110, 105, 100, 95, 90, 85, 80, 75,
		70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, -5, -10, -15,
		-20, -25, -30, -35, -40,-45,-50,-55 };


const unsigned short PCB_T_ADC_Count_X[46] = { 154,170,187,207,228,251,276,304,334,366,373, 379, 386, 393, 400, 407, 414, 422,
		429, 436, 444, 451, 459, 466, 474, 513, 554, 595, 636, 676, 715, 752, 788,
		820, 850,877, 901,922, 941, 956, 970, 981, 990, 998, 1004, 1009};

const int PCB_T_DegC_Y[46] = { 125, 120, 115, 110, 105, 100, 95, 90, 85, 80,79,78,77,76,75,74,73,72,71,
		70,69,68,67,66, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, -5, -10, -15,
		-20, -25, -30, -35, -40 };


void Driver13V_diag_handle(){
//	static uint8_t Driver13VInFAILUREFlag = 0;
//	if (!Driver13VInFAILUREFlag) 
	{
		//if (L3_I_AD_Driver13V > Driver13V_maxHigh_Ct_u16) {
		if (L3_I_AD_Driver13V > 266) {
		
		//过压
		
			diagRecoverTag.Driver13VFault_RecoverCntr = 0; //恢复清0
			//if (diagCtrlTag.Driver13VFaultCntr >= diagTimerTag.Driver13VFaultTime) {
		if (diagCtrlTag.Driver13VFaultCntr >= 2) {//100*2 = 200us

				//等于计数时间 判断错误
				faultCodeTag.bit.bDriver13VFault = 1;
				diagCtrlTag.Driver13VFaultCntr = 0;
				//Driver13VInFAILUREFlag = 1;
				//不可恢复
				//stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
			//	FSM_run();
			powerDown();
			}
			else
			{
					diagCtrlTag.Driver13VFaultCntr++; //开始计数
			}
		} 
		//else if (L3_I_AD_Driver13V < Driver13V_limtLow_Ct_u16)
		else if (L3_I_AD_Driver13V < 190) 
		 {
			//欠压
			
			diagRecoverTag.Driver13VFault_RecoverCntr = 0; //恢复清0
			//if (diagCtrlTag.Driver13VFaultCntr >= diagTimerTag.Driver13VFaultTime) {
			if (diagCtrlTag.Driver13VFaultCntr >= 2) {//100*2 = 200us
				//等于计数时间 判断错误
				faultCodeTag.bit.bDriver13VFault = 1;
				diagCtrlTag.Driver13VFaultCntr = 0;
				//Driver13VInFAILUREFlag = 1;
				//不可恢复
				//stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				//FSM_run();
				powerDown();
			}
			else
			{
				diagCtrlTag.Driver13VFaultCntr++; //开始计数
			}
		} else {
		/*
			if (L3_I_AD_Driver13V >= Driver13V_limtLow_Ct_u16
					&& L3_I_AD_Driver13V <= Driver13V_maxHigh_Ct_u16) {
				//if (faultCodeTag.bit.bDriver13VFault == 1) {
					diagRecoverTag.Driver13VFault_RecoverCntr++;
				//}
				diagCtrlTag.Driver13VFaultCntr = 0;
			}*/
			
			diagCtrlTag.Driver13VFaultCntr = 0;
			//if (diagRecoverTag.Driver13VFault_RecoverCntr >= diagRecoverTimerTag.Driver13VFaultRecoverTime) {
	 		//if (diagRecoverTag.Driver13VFault_RecoverCntr >= 6250) {//500*1000/80 = 6250
			//if (diagRecoverTag.Driver13VFault_RecoverCntr >= 1250) {//100*1000/80 = 6250
			if (diagRecoverTag.Driver13VFault_RecoverCntr >= 1000) {//100*1000/100 = 1000
				faultCodeTag.bit.bDriver13VFault = 0;
				diagRecoverTag.Driver13VFault_RecoverCntr = 0;

			}
			else
			{
				diagRecoverTag.Driver13VFault_RecoverCntr++;
			}
		}
	}

}
void LV_12V_diag_handle(){
	//static uint8_t LV12VInFAILUREFlag = 0;
	//	if (!LV12VInFAILUREFlag) 
		{
			if (L3_I_AD_12V_CMM > LV_12V_maxHigh_Ct_u16) {
			//过压
				diagCtrlTag.LV12VFaultCntr++; //开始计数
				diagRecoverTag.LV12VFault_RecoverCntr = 0; //恢复清0
				if (diagCtrlTag.LV12VFaultCntr >= diagTimerTag.LV12VFaultTime) {
					//等于计数时间 判断错误
					faultCodeTag.bit.bLV12VFault = 1;
					diagCtrlTag.LV12VFaultCntr = 0;
					//LV12VInFAILUREFlag = 1;
					//不可恢复
				//	stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				//	FSM_run();
				}
			} else if (L3_I_AD_12V_CMM < LV_12V_limtLow_Ct_u16) {
				//欠压
				diagCtrlTag.LV12VFaultCntr++; //开始计数
				diagRecoverTag.LV12VFault_RecoverCntr = 0; //恢复清0
				if (diagCtrlTag.LV12VFaultCntr >= diagTimerTag.LV12VFaultTime) {
					//等于计数时间 判断错误
					faultCodeTag.bit.bLV12VFault = 1;
					diagCtrlTag.LV12VFaultCntr = 0;
					//LV12VInFAILUREFlag = 1;
					//不可恢复
				//	stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				//	FSM_run();
				}
			} else {
			/*
				if (L3_I_AD_12V_CMM >= LV_12V_limtLow_Ct_u16
						&& L3_I_AD_12V_CMM <= LV_12V_maxHigh_Ct_u16) {
					if (faultCodeTag.bit.bLV12VFault == 1) {
						diagRecoverTag.LV12VFault_RecoverCntr++;
					}
					diagCtrlTag.LV12VFaultCntr = 0;
				}*/
				diagRecoverTag.LV12VFault_RecoverCntr++;
				diagCtrlTag.LV12VFaultCntr = 0;
				if (diagRecoverTag.LV12VFault_RecoverCntr
						>= diagRecoverTimerTag.LV12VFaultRecoverTime) {
					faultCodeTag.bit.bLV12VFault = 0;
					diagRecoverTag.LV12VFault_RecoverCntr = 0;

				}
			}
		}
}


void input_Relay_diag_handle(){
	static uint16_t diag_cnt = 0;
	if(O_S_RlyCTL1 == HIGH)
	{
		if(L3_I_AD_RelayCoil1 <= VRelayCoil1_DIAG_Volt_CLOSE)
		{
			diag_cnt = 0;
			faultCodeTag.bit.bINPUT_Relay = FALSE;
		}
		else
		{
			if(diag_cnt>500)
			{
				//DCM_FaultCode_La[faultCode_INPUT_Relay] = enable_DCM_DTC==TRUE?TRUE:FALSE;
				faultCodeTag.bit.bINPUT_Relay = TRUE;
				diag_cnt = 0;
			}
			else
			{
				diag_cnt++;
			}
			
		}
	}
	else
	{
		if(L3_I_AD_RelayCoil1 >= VRelayCoil1_DIAG_Volt_OPEN_AD_MIN)
		{
			diag_cnt = 0;
			faultCodeTag.bit.bINPUT_Relay = FALSE;
		
		}
		else
		{
		
			
			if(diag_cnt>500)
			{
				//DCM_FaultCode_La[faultCode_INPUT_Relay] = enable_DCM_DTC==TRUE?TRUE:FALSE;
				faultCodeTag.bit.bINPUT_Relay = TRUE;
				diag_cnt = 0;
			}
			else
			{
				diag_cnt++;
			}
		}
	}

}


void PG_diag_handle(){
	static uint16_t diag_cnt = 0;
	if(O_PG == HIGH)
	{
		if(PG_SENSE == HIGH)
		{
			diag_cnt = 0;
			faultCodeTag.bit.bPG_SENS = FALSE;
		}
		else
		{
			if(diag_cnt>500)
			{
				//DCM_FaultCode_La[faultCode_PG_SENS] = enable_DCM_DTC==TRUE?TRUE:FALSE;
				faultCodeTag.bit.bPG_SENS = TRUE;
				diag_cnt = 0;
			}
			else
			{
				diag_cnt++;
			}
			
		}
	}
	else
	{
		if(PG_SENSE == LOW)
		{
			diag_cnt = 0;
			faultCodeTag.bit.bPG_SENS = FALSE;
		
		}
		else
		{		
			if(diag_cnt>500)
			{
				//DCM_FaultCode_La[faultCode_PG_SENS] = enable_DCM_DTC==TRUE?TRUE:FALSE;
				faultCodeTag.bit.bPG_SENS = TRUE;
				diag_cnt = 0;
			}
			else
			{
				diag_cnt++;
			}
		}
	}
}
BOOL outputCurrentSen_diag_handle(){

	if(DCDC_DIAG_IOUT_ZERO_AD_MIN <= L3_Dcdc_Iout_Ct_u16 && L3_Dcdc_Iout_Ct_u16 <= DCDC_DIAG_IOUT_ZERO_AD_MAX )
	{
		return TRUE;
	}
	else
	{
		//DCM_FaultCode_La[faultCode_outputCurrentSenError] = enable_DCM_DTC==TRUE?TRUE:FALSE;
		//DCM_FaultCode_La[faultCode_outputCurrentSenError] = TRUE;//上电自检故不能等待诊断启动delay,否则启动时间太长。
		return FALSE;
	}

}


void CAN_diag_handle()
{

	if(bms_can_available && stSysFSMCtrl.ucCurrentState == STATE_OPETRATION )
	{
		//if(L3_S_BMSMsgTimeOut_Uls_G_u08 == TRUE && enable_DCM_DTC == TRUE)
		if(L3_S_BMSMsgTimeOut_Uls_G_u08 == TRUE )
		{
		//	DCM_FaultCode_La[faultCode_bCANMissing] = TRUE;
			faultCodeTag.bit.bCANMissing = TRUE;
		}
		else
		{
			faultCodeTag.bit.bCANMissing = FALSE;
		}
	}
	
	//if(L3_CanBusOff_error_Ct_u8 == TRUE && enable_DCM_DTC == TRUE)
	//if(hCanBus_u8GetBusOffState() == TRUE )//BUSOFF recovery mechanism 2, the code is not verified
	if(L3_CanBusOff_error_Ct_u8 == TRUE ) //BUSOFF recovery mechanism 1, the code is  verified
	{
		//DCM_FaultCode_La[faultCode_bCANBUSOFF] = TRUE;
		faultCodeTag.bit.bCANBUSOFF = TRUE;
	}
	else
	{
		faultCodeTag.bit.bCANBUSOFF = FALSE;
	}

	
}



uint8 ChrPlugIn_diag_handle()
{
	uint8 ret = FALSE;
	static uint16 chrPluginTimeoutCnt = 0;
		
	if(faultCodeTag.bit.bUinVoltOpen == TRUE)
	//if(L5_AC_Volt_fast_maxBuffCPS < AC_Volt_fast_OpenVolt_Ct_u16)
	{
		/*
		stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
		FSM_run();
		ret = TRUE;
		return ret;
			*/
		if(L3_I_AD_CP_max_buff_Ct_u16 < CP1V_VOLT_AD_SET_MAX)
		{
			if(UDS_TimeOutFlag == TRUE)
			{
				chrPluginTimeoutCnt++;
			}
			else
			{
				chrPluginTimeoutCnt = 0;
			}
			
			if(chrPluginTimeoutCnt >= 30000)//60*10000/2
			{
				ret = TRUE;
			}
			else
			{
				ret = FALSE;
			}
		}
		else
		{
			//模式2,3 枪还一直在车上
			ret = FALSE;
		}
	}
	else
	{
		ret = FALSE;
		chrPluginTimeoutCnt = 0;
	}
	
	return ret;

}






void CCState_diag_handle()
{
	static uint16_t CCStateKeepCnt = 0;
	uint16_t CCStateKeepMaxTime = 1000;//1000*2ms = 2s
	
	//cc state decide
	
	if(stSysFSMCtrl.ucCurrentState  == STATE_OPETRATION )
	{
		if(BMSTag.CCState != CCSTATE_C && BMSTag.CCState != CCSTATE_D && BMSTag.CCState != CCSTATE_E && BMSTag.CCState != CCSTATE_F)
		{
			CCStateKeepCnt = 0;
			OBCTag.bFilterCCState = FALSE;
			L5_CC_CurrentPhy_1000dLimt = 0;
			goStandBy();
			return;

		}
	}
	
	
	if(BMSTag.CCState != CCSTATE_C && BMSTag.CCState != CCSTATE_D && BMSTag.CCState != CCSTATE_E && BMSTag.CCState != CCSTATE_F)
	{


	}
	else
	{
		if(CCStateKeepCnt >= CCStateKeepMaxTime)
		{	
			CCStateKeepCnt = 0;
			OBCTag.bFilterCCState = TRUE;
		}
		else
		{
			CCStateKeepCnt++;
		}
		
	}
	
	/*
	if(stSysFSMCtrl.ucCurrentState  == STATE_OPETRATION)
	{
		if(BMSTag.CCState != CCSTATE_C && BMSTag.CCState != CCSTATE_D && BMSTag.CCState != CCSTATE_E && BMSTag.CCState != CCSTATE_F)
		{
		
			goStandBy();
			return;

		}
		else
		{
			S2_CTR = HIGH;
		}

	}
	else
	{
		if(BMSTag.CCState != CCSTATE_C && BMSTag.CCState != CCSTATE_D && BMSTag.CCState != CCSTATE_E && BMSTag.CCState != CCSTATE_F)
		{
			S2_CTR = LOW;
		}
		else
		{
			S2_CTR = HIGH;
		}
	}
	*/
	
	//current limt

	if(BMSTag.CCState > 0 && BMSTag.CCState < 11)
	{
		//CCState = BMSTag.CCState-1;
		//CC_IMax = CC_STATE_ARR[CCState];
		//tempCCTag = &CC_STATE_Tag[BMSTag.CCState];
	//	CC_IMax = *tempCCTag->IMax;;
		L5_CC_CurrentPhy_1000dLimt = CC_STATE_ARR[BMSTag.CCState-1] * 1000;
		OBCPOWERTag.CCStateCurrentLimt = DCDC_CURRENT_AD_CONVERT(CC_STATE_ARR[BMSTag.CCState-1]);
	}
	else
	{
		//发出的CAN 不在国标只给8A最大
		BMSTag.CCState = 1;
	//	CCState = BMSTag.CCState-1;
	//	CC_IMax = CC_STATE_ARR[CCState];
		//CC_IMax = CC_STATE_Tag[BMSTag.CCState]->IMax;
		L5_CC_CurrentPhy_1000dLimt = CC_STATE_ARR[BMSTag.CCState-1] * 1000;
		OBCPOWERTag.CCStateCurrentLimt = DCDC_CURRENT_AD_CONVERT(CC_STATE_ARR[BMSTag.CCState-1]);
	}
	

	

	
	
}




void CMDState_diag_handle()
{
	static uint16_t CMDStateKeepCnt = 0;
	static uint8_t CMDEnchargeStateDiagStart = FALSE;
	uint16_t CMDStateKeepMaxTime = 1000;//1000*2ms = 2s
	
	if(O_PG == LOW)
	{
		return; //未建立连接前不检BMS CAN CMD error
	}
	
	if(CMDEnchargeStateDiagStart == TRUE)
	{
		//if(BMSTag.EnCharger == BMS_DIS_CHARGER || L3_S_BMSMsgTimeOut_Uls_G_u08 )
		if(BMSTag.EnCharger == BMS_DIS_CHARGER )
			{
				O_PG = LOW;
				HW_O_PG = O_PG;
				BMS_CHARGE_OVER = TRUE;
				goStandBy();
				return ;
			}
	}
	
	//默认给定电流电压。收到CAN命令后变化
	if(bms_can_available && BMSTag.EnCharger == TRUE){
	
		CMDEnchargeStateDiagStart = TRUE;
		/*
		k_Dcdc_Vref_Ct_u16 = (uint16)((((uint32)BMSTag.ChrVoltSp/2)<<10)/500);
		tempCurrentAD = (uint16)((uint32)BMSTag.ChrCurrentSp*25/112+179);
		tempCurrentIMaxAD = (uint16)((uint32)CC_STATE_Tag[BMSTag.CCState].IMax*1792/25+179);
		*/
		
		OBCPOWERTag.CANCmdSETVolt= DCDC_VOLT_AD_DBC_CONVERT(BMSTag.ChrVoltSp);
		
		OBCPOWERTag.CANCmdSETCurrent= DCDC_CURRENT_AD_DBC_CONVERT(BMSTag.ChrCurrentSp);

	
		//if(OBCPOWERTag.CANCmdSETVolt < DCDC_LOOP_VOLT_AD_SET_LIMT || OBCPOWERTag.CANCmdSETCurrent == 0)
		if(OBCPOWERTag.CANCmdSETVolt < DCDC_LOOP_VOLT_AD_SET_LIMT || OBCPOWERTag.CANCmdSETCurrent < k_Dcdc_MIN_Iref_limt)
		{
		
			CMDStateKeepCnt = 0;
			OBCTag.bFilterWorkCMD = FALSE;
			goStandBy();
			return;

		}
		
		if(OBCPOWERTag.CANCmdSETVolt < DCDC_LOOP_VOLT_AD_SET_LIMT || OBCPOWERTag.CANCmdSETCurrent < k_Dcdc_MIN_Iref_limt)
		{


		}
		else
		{
			if(CMDStateKeepCnt >= CMDStateKeepMaxTime)
			{	
				CMDStateKeepCnt = 0;
				OBCTag.bFilterWorkCMD = TRUE;
			}
			else
			{
				CMDStateKeepCnt++;
			}
			
		}
		
	
		
		#ifdef HAS_INPUT_POWER_LIMT
		
		if( OBCPOWERTag.CANCmdSETVolt < DCDC_LOOP_VOLT_AD_SET_LIMT)
		{
			//OBCPOWERTag.ACPowSetVoltCurrentLimt = POWER_CURRENT_AD_SET(PowerLimSet,DCDC_LOOP_VOLT_SET_LIMT);
			goStandBy();
			//k_Dcdc_Vref_Ct_u16 = DCDC_LOOP_VOLT_AD_SET_LIMT;
			return;
		}
		else if(OBCPOWERTag.CANCmdSETVolt > DCDC_LOOP_VOLT_AD_SET_MAX)
		{
			//OBCPOWERTag.ACPowSetVoltCurrentLimt = POWER_CURRENT_AD_SET(PowerLimSet,DCDC_LOOP_VOLT_SET_MAX);
			k_Dcdc_Vref_Ct_u16 = DCDC_LOOP_VOLT_AD_SET_MAX;
		}
		else
		{
			//OBCPOWERTag.ACPowSetVoltCurrentLimt = POWER_CURRENT_AD_SET(PowerLimSet,DCDC_VOLT_PHY_DBC_CONVERT(BMSTag.ChrVoltSp));
			k_Dcdc_Vref_Ct_u16 = OBCPOWERTag.CANCmdSETVolt;
		}
		
		if(OBCPOWERTag.CANCmdSETCurrent == 0)
		{
			goStandBy();
			//OBCPOWERTag.CANCmdSETCurrent = k_Dcdc_MIN_Iref_limt;
			return;
		}else if(OBCPOWERTag.CANCmdSETCurrent > k_Dcdc_MAX_Iref_limt)
		{
			OBCPOWERTag.CANCmdSETCurrent = k_Dcdc_MAX_Iref_limt;
		}
		/*
		
		if( OBCPOWERTag.CANCmdSETVolt < DCDC_LOOP_VOLT_AD_SET_LIMT)
		{
			OBCPOWERTag.ACPowSetVoltCurrentLimt = POWER_CURRENT_AD_SET(PowerLimSet,DCDC_LOOP_VOLT_SET_LIMT);
			k_Dcdc_Vref_Ct_u16 = DCDC_LOOP_VOLT_AD_SET_LIMT;
		}
		else if(OBCPOWERTag.CANCmdSETVolt > DCDC_LOOP_VOLT_AD_SET_MAX)
		{
			OBCPOWERTag.ACPowSetVoltCurrentLimt = POWER_CURRENT_AD_SET(PowerLimSet,DCDC_LOOP_VOLT_SET_MAX);
			k_Dcdc_Vref_Ct_u16 = DCDC_LOOP_VOLT_AD_SET_MAX;
		}
		else
		{
			OBCPOWERTag.ACPowSetVoltCurrentLimt = POWER_CURRENT_AD_SET(PowerLimSet,DCDC_VOLT_PHY_DBC_CONVERT(BMSTag.ChrVoltSp));
			k_Dcdc_Vref_Ct_u16 = OBCPOWERTag.CANCmdSETVolt;
		}
		if(k_Dcdc_Iref_Ct_u16 > OBCPOWERTag.ACPowMaxCurrentLimt)
		{
			k_Dcdc_Iref_Ct_u16 = OBCPOWERTag.ACPowMaxCurrentLimt;
			k_Dcdc_SetpIref_Ct_u16 = L3_Dcdc_Iout_Ct_u16;
		}
		
		
		if(k_Dcdc_Iref_Ct_u16 > OBCPOWERTag.ACPowSetVoltCurrentLimt)
		{
			k_Dcdc_Iref_Ct_u16 = OBCPOWERTag.ACPowSetVoltCurrentLimt;
			k_Dcdc_SetpIref_Ct_u16 = L3_Dcdc_Iout_Ct_u16;
		}
		*/
		/*
		if(k_Dcdc_Iref_Ct_u16 > OBCPOWERTag.CANCmdSETCurrent)
		{
			k_Dcdc_Iref_Ct_u16 = OBCPOWERTag.CANCmdSETCurrent;
			k_Dcdc_SetpIref_Ct_u16 = L3_Dcdc_Iout_Ct_u16;
		}
		
		if(k_Dcdc_Iref_Ct_u16 > OBCPOWERTag.CCStateCurrentLimt)
		{
			k_Dcdc_Iref_Ct_u16 = OBCPOWERTag.CCStateCurrentLimt;
			k_Dcdc_SetpIref_Ct_u16 = L3_Dcdc_Iout_Ct_u16;
		}
		*/
		
		#elif OUTPUT_FULL_POWER_LIMT
	
		
		if( OBCPOWERTag.CANCmdSETVolt < DCDC_LOOP_VOLT_AD_SET_LIMT)
		{
			goStandBy();
			//k_Dcdc_Vref_Ct_u16 = DCDC_LOOP_VOLT_AD_SET_LIMT;
			return;
		}
		else if(OBCPOWERTag.CANCmdSETVolt > DCDC_LOOP_VOLT_AD_SET_MAX)
		{
			k_Dcdc_Vref_Ct_u16 = DCDC_LOOP_VOLT_AD_SET_MAX;
		}
		else
		{
			k_Dcdc_Vref_Ct_u16 = OBCPOWERTag.CANCmdSETVolt;
		}
		
		if(OBCPOWERTag.CANCmdSETCurrent == 0)
		{
			goStandBy();
			//OBCPOWERTag.CANCmdSETCurrent = k_Dcdc_MIN_Iref_limt;
			return;
		}else if(OBCPOWERTag.CANCmdSETCurrent > k_Dcdc_MAX_Iref_limt)
		{
			OBCPOWERTag.CANCmdSETCurrent = k_Dcdc_MAX_Iref_limt;
		}
		#endif
		
	}
}
/*
#define CP_NORMAL  (0)
#define CP_FRQ_LOW (1)
#define CP_FRQ_HIGH (2)
#define CP_DUTY_LOW (3)
#define CP_DUTY_HIGH (4)
#define CP_VOLT_LOW (5)
#define CP_VOLT_HIGH (6)
#define CP_NULL (7)
*/
void CPVolt_diag_handle()
{
	static uint16  cpOverVoltCnt = 0;
	static uint16  cpUnderVoltCnt = 0;
	static uint16  cpRecoverCnt = 0;
	
	static uint8  S2_CTR_lastState = LOW;
	
	uint16  cpOverVoltTime = 1000;//2s
	

	L3_I_AD_CP_Filter_Ct_u16 =  LPF((uint32)L3_I_AD_CP_max_buff_Ct_u16,(uint32)L3_I_AD_CP_Filter_Ct_u16,20,L3_I_AD_CP_Filter_Tau_Ct_u16);
	if(L5_OBC_model1_enable == TRUE)
	{
			OBCTag.bFilterCPVoltState = CP_NORMAL;
			faultCodeTag.bit.bFaultCP = 0;
			return;
	}
	
	if(S2_CTR_lastState != S2_CTR)
	{
		cpOverVoltCnt = 0; //开始计数
		cpUnderVoltCnt = 0;
		cpRecoverCnt = 0; //恢复清0
	}
	
	
	if(S2_CTR == HIGH)
	{
		
		if (L3_I_AD_CP_Filter_Ct_u16 > CP6V_VOLT_AD_SET_MAX) {
			//CP过压

			cpOverVoltCnt++; //开始计数
			cpUnderVoltCnt = 0;
			cpRecoverCnt = 0; //恢复清0
			if (cpOverVoltCnt >= cpOverVoltTime) {
				
				faultCodeTag.bit.bFaultCP = 1;
				cpOverVoltCnt = 0;
				OBCTag.bFilterCPVoltState = CP_VOLT_HIGH;
			}
		} else if (L3_I_AD_CP_Filter_Ct_u16 < CP6V_VOLT_AD_SET_LIMT) {
			//
			cpUnderVoltCnt++; //开始计数
			cpOverVoltCnt = 0;
			cpRecoverCnt = 0; //恢复清0
			if (cpUnderVoltCnt >= cpOverVoltTime) {
				faultCodeTag.bit.bFaultCP = 1;
				cpUnderVoltCnt = 0;
				OBCTag.bFilterCPVoltState = CP_VOLT_LOW;
			
			}
		} else {
			cpRecoverCnt++;
			if (cpRecoverCnt >= cpOverVoltTime) {
				OBCTag.bFilterCPVoltState = CP_NORMAL;
				cpUnderVoltCnt = 0;
				cpOverVoltCnt =  0;
					
				if(OBCTag.bFilterCPDutyState == CP_NORMAL && OBCTag.bFilterCPFrqState == CP_NORMAL)
				{
					faultCodeTag.bit.bFaultCP = 0;
				}
			}
		}
	
	}
	else
	{
		if (L3_I_AD_CP_Filter_Ct_u16 > CP9V_VOLT_AD_SET_MAX) {
			//CP过压

			cpOverVoltCnt++; //开始计数
			cpUnderVoltCnt = 0;
			cpRecoverCnt = 0; //恢复清0
			if (cpOverVoltCnt >= cpOverVoltTime) {
				
				faultCodeTag.bit.bFaultCP = 1;
				cpOverVoltCnt = 0;
				OBCTag.bFilterCPVoltState = CP_VOLT_HIGH;
			}
		} else if (L3_I_AD_CP_Filter_Ct_u16 < CP9V_VOLT_AD_SET_LIMT) {
			//
			cpUnderVoltCnt++; //开始计数
			cpOverVoltCnt = 0;
			cpRecoverCnt = 0; //恢复清0
			if (cpUnderVoltCnt >= cpOverVoltTime) {
				faultCodeTag.bit.bFaultCP = 1;
				cpUnderVoltCnt = 0;
				OBCTag.bFilterCPVoltState = CP_VOLT_LOW;
			
			}
		} else {
			cpRecoverCnt++;
			if (cpRecoverCnt >= cpOverVoltTime) {
			OBCTag.bFilterCPVoltState = CP_NORMAL;
			cpUnderVoltCnt = 0;
			cpOverVoltCnt =  0;
				
			if(OBCTag.bFilterCPDutyState == CP_NORMAL && OBCTag.bFilterCPFrqState == CP_NORMAL)
			{
				faultCodeTag.bit.bFaultCP = 0;
			}

			}
		}
	}
	
		S2_CTR_lastState = S2_CTR;
}


void CP_diag_handle(){
	uint8 isHW_line_connet = 0;
	uint8 isCP_MIN_connet = 0;
	uint16	CurrentLimt;
	uint32 temp_cp_pwm_current = 0;
	
	uint8 compareFlag = 0;
	uint8 changeFlag = 0;
	
	
	L3_CP_Per();
//	L3_CP_Per_ms_u16p12  = (uint16)((((uint32)(L2_eTimer0Chn5_Capt1_Ct_u16))<<12)/30000);
//	L3_CP_Duty_ms_u16p12 = (uint16)((((uint32)(L2_eTimer0Chn5_Capt2_Ct_u16))<<12)/30000);
	//占空比D=21.67%（供电电流≯13A）；PlugIn=???，占空比D=13.33%（供电电流≯8A）；
	
	
	
	if((L3_CP_Per_ms_u16p12 != 0 ) && (L3_CP_Per_ms_u16p12 > L3_CP_Duty_ms_u16p12))
	{
		cp_pwm_width_percent = ((uint32)L3_CP_Per_ms_u16p12 - L3_CP_Duty_ms_u16p12)*10000/L3_CP_Per_ms_u16p12;
		if(L3_CP_Per_ms_u16p12 > CP_500HZ)
		{
			cp_pwm_width_percent = 0;
			cp_pwm_width_percent_filter = 0;
			cp_pwm_width_percent_filter_cnt = 0;
			cpPwmWidthPFilterOffset = 0;
		}
		else
		{
		
			if(cp_pwm_width_percent_filter_cnt >= CP_FILTER_CNT)
			{
				cp_pwm_width_percent_filter_cnt = 0 ;
			}
			
			cp_pwm_width_percent_filter = (cp_pwm_width_percent_filter * cp_pwm_width_percent_filter_cnt + cp_pwm_width_percent)/(++cp_pwm_width_percent_filter_cnt);
			//cp_pwm_width_percent_filter = LPF(cp_pwm_width_percent,cp_pwm_width_percent_filter,CP_FILTER_Dt,CP_FILTER_Tau);
			cpPwmWidthPFilterOffset = cp_pwm_width_percent_filter+CP_offset;
		}
	}
	else
	{
		cp_pwm_width_percent = 0;
		cp_pwm_width_percent_filter = 0;
		cp_pwm_width_percent_filter_cnt = 0;
		cpPwmWidthPFilterOffset = 0;
		
		
	}

	
	if(cp_pwm_senceCnt >= cp_pwm_senceTime)
	{
		//1s后判断
		cp_pwm_senceCnt = 0;
		
		//小于 8%  不允许充电
		//8%~10% IMAX = 6A
		//10%~85% IMAX = (D*100)*0.6
		//85%~90% IMAX = (D*100-64)*2.5 且 IMAX<= 63
		//90%~97% 预留
		//>97%  不允许充电
		if(cp_pwm_width_percent_filter == 0)
		{
			if(L5_OBC_model1_enable == TRUE)
			{
					OBCTag.bFilterCPDutyState = CP_NORMAL;
					faultCodeTag.bit.bFaultCP = 0;
					
			}
			else
			{
				
				if(L3_I_AD_CP_max_buff_Ct_u16 > CP6V_VOLT_AD_SET_MAX)
				{
					OBCTag.bFilterCPDutyState = CP_DUTY_HIGH;
					faultCodeTag.bit.bFaultCP = 1;
					cp_pwm_width_percent_filter = 10000;
				}
				else
				{
					OBCTag.bFilterCPDutyState = CP_DUTY_LOW;
					faultCodeTag.bit.bFaultCP = 1;
				}
			
			}
		}
		else
		{
			if(L3_I_AD_CP_max_buff_Ct_u16 < CP1V_VOLT_AD_SET_MAX)
			{
				OBCTag.bFilterCPDutyState = CP_DUTY_LOW;
				faultCodeTag.bit.bFaultCP = 1;
			}
		}
		
		
		
		
		compareFlag = cpPwmWidthPFilterOffset_last > cpPwmWidthPFilterOffset;
		changeFlag = (!compareFlag && (cpPwmWidthPFilterOffset > (cpPwmWidthPFilterOffset_last + CP_debunce_offset)))
		|| (compareFlag && (cpPwmWidthPFilterOffset_last > (cpPwmWidthPFilterOffset + CP_debunce_offset)));
		if(!changeFlag && cpPwmWidthPFilterOffset != 0)
		{
			//return;
		}
		else
		{
			cpPwmWidthPFilterOffset_last = cpPwmWidthPFilterOffset;
		}
		
		L3_CP_Per_ms_u16p12 = 0;
		L3_CP_Duty_ms_u16p12 = 0;
		
		if(cpPwmWidthPFilterOffset == 0)
		{
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_10A_LIMT);
			//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_8A_LIMT);
			isHW_line_connet = TRUE;
		}
		else if(cpPwmWidthPFilterOffset < CP_D_8)
		{
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_0A_LIMT);
			/*
			faultCodeTag.bit.bFaultCP = 1;
			cp_pwm_width_percent = 0;
			cp_pwm_width_percent_filter = 0;
			cp_pwm_width_percent_filter_cnt = 0;
			cpPwmWidthPFilterOffset = 0;
			*/
			cp_pwm_width_percent = 0;
			cp_pwm_width_percent_filter = 0;
			cp_pwm_width_percent_filter_cnt = 0;
			cpPwmWidthPFilterOffset = 0;
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_10A_LIMT);
		//	CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_8A_LIMT);
			isHW_line_connet = TRUE;
			
			
			
			
			if(L5_OBC_model1_enable == TRUE)
			{
					OBCTag.bFilterCPDutyState = CP_NORMAL;
					faultCodeTag.bit.bFaultCP = 0;
			}
			else
			{
				OBCTag.bFilterCPDutyState = CP_DUTY_LOW;
				faultCodeTag.bit.bFaultCP = 1;
			}
		}
		else if(CP_D_8<=cpPwmWidthPFilterOffset &&  cpPwmWidthPFilterOffset<= CP_D_10)
		{
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_6A_LIMT);
			//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_6A_LIMT);
			isCP_MIN_connet = TRUE;
			OBCTag.bFilterCPDutyState = CP_NORMAL;
			if(OBCTag.bFilterCPVoltState == CP_NORMAL && OBCTag.bFilterCPFrqState == CP_NORMAL)
			{
				faultCodeTag.bit.bFaultCP = CP_NORMAL;
			}

		}
		else if(CP_D_10<=cpPwmWidthPFilterOffset &&  cpPwmWidthPFilterOffset<= CP_D_85)
		{
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_10double_CURRENT_AD_CONVERT((cp_pwm_width_percent_filter*6));
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_100double_CURRENT_AD_CONVERT((cp_pwm_width_percent_filter*6));
		//	OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_1000double_CURRENT_AD_CONVERT((cp_pwm_width_percent_filter*6));
			L5_CP_CurrentPhy_1000dLimt = cpPwmWidthPFilterOffset*6;
			
			CurrentLimt = (uint16)DCDC_1000double_CURRENT_AD_CONVERT(L5_CP_CurrentPhy_1000dLimt);
				
			isHW_line_connet = FALSE;
			OBCTag.bFilterCPDutyState = CP_NORMAL;
			if(OBCTag.bFilterCPVoltState == CP_NORMAL && OBCTag.bFilterCPFrqState == CP_NORMAL)
			{
				faultCodeTag.bit.bFaultCP = 0;
			}
		
		}
		else if(CP_D_85<=cpPwmWidthPFilterOffset &&  cpPwmWidthPFilterOffset<= CP_D_90)
		{
			temp_cp_pwm_current = (cpPwmWidthPFilterOffset-6400)*25;
			if(temp_cp_pwm_current >= (CP_CURRENT_MAX_LIMT*1000))
			{
				temp_cp_pwm_current = CP_CURRENT_MAX_LIMT*1000;
			}
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_10double_CURRENT_AD_CONVERT(temp_cp_pwm_width);
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_100double_CURRENT_AD_CONVERT(temp_cp_pwm_current);
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_1000double_CURRENT_AD_CONVERT(temp_cp_pwm_current);
			
			L5_CP_CurrentPhy_1000dLimt = temp_cp_pwm_current;
			
			CurrentLimt = (uint16)DCDC_1000double_CURRENT_AD_CONVERT(temp_cp_pwm_current);
			isHW_line_connet = FALSE;
			OBCTag.bFilterCPDutyState = CP_NORMAL;
			if(OBCTag.bFilterCPVoltState == CP_NORMAL && OBCTag.bFilterCPFrqState == CP_NORMAL)
			{
				faultCodeTag.bit.bFaultCP = 0;
			}
		}
		else if(cpPwmWidthPFilterOffset > CP_D_90)
		{
			/*
			faultCodeTag.bit.bFaultCP = 1;
			cp_pwm_width_percent = 0;
			cp_pwm_width_percent_filter = 0;
			cp_pwm_width_percent_filter_cnt = 0;
			cpPwmWidthPFilterOffset = 0;
			*/
			cp_pwm_width_percent = 0;
			cp_pwm_width_percent_filter = 0;
			cp_pwm_width_percent_filter_cnt = 0;
			cpPwmWidthPFilterOffset = 0;
			//OBCPOWERTag.CPStateCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_10A_LIMT);
			//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_8A_LIMT);
			isHW_line_connet = TRUE;
				if(L5_OBC_model1_enable == TRUE)
			{
					OBCTag.bFilterCPDutyState = CP_NORMAL;
					faultCodeTag.bit.bFaultCP = 0;
			}
			else
			{
				OBCTag.bFilterCPDutyState = CP_DUTY_HIGH;
				faultCodeTag.bit.bFaultCP = 1;
			}
		}
		#ifdef HAS_INPUT_POWER_LIMT
		/* not limt by input AC volt
		if(isHW_line_connet == TRUE)
		{
			CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_8A_LIMT);;
		} else if(isCP_MIN_connet)
		{
			CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_6A_LIMT);
		}
		else
		{
			
			if(OBCTag.ACRMSVolt <= (INPUT_ACVOLT_SET/2) || OBCTag.actChrVolt <= POWER_BMS_LIMT_CURRENT_VOLT_SET )
			{
				CP_CurrentLimt = CurrentLimt;
				CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_8A_LIMT);
				CP_CurrentLimt1 = CurrentLimt;
			}
			else
			{
				//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_CURRENT(OBCPOWERTag.CPStateCurrentLimt) * (float)OBCTag.ACRMSVolt) / OBCTag.actChrVolt);
			//	CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_CURRENT(CurrentLimt) * (float)OBCTag.ACRMSVolt) / OBCTag.actChrVolt);
				//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_100doubleCURRENT(CurrentLimt) *(float)OBCTag.ACRMSVolt) / OBCTag.actChrVolt/100);;
				CP_CurrentLimt = CurrentLimt;
				//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_100doubleCURRENT(CurrentLimt) *(float)OBCTag.ACRMSVolt) / OBCTag.actChrVolt/100);//批次需要修改为标准的
				CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_100doubleCURRENT(CurrentLimt) *(float)INPUT_ACVOLT_SET) / OBCTag.actChrVolt*2/100);

				CP_CurrentLimt1 = CurrentLimt; 
			}
			
			
		//	CurrentLimt = (uint16)DCDC_AD_CONVERT_CURRENT(OBCPOWERTag.CPStateCurrentLimt) * 220 / 370;
		//	CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_CURRENT(CurrentLimt) * (float)220) / 370);
		//	CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(13);
		//	CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((13 * (float)220) / 370);
			//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_100doubleCURRENT(CurrentLimt) * (float)207.0) / 314/100);


		}
		*/
		//limt by input AC volt of the GB in OBC
		if(isHW_line_connet == TRUE)
		{
			CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_8A_LIMT);
			
			L5_CP_CurrentPhy_1000dLimt = CP_CURRENT_HW_lINE_8A_LIMT *1000;
			
		} else if(isCP_MIN_connet)
		{
			CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_6A_LIMT);
			
			L5_CP_CurrentPhy_1000dLimt = CP_CURRENT_6A_LIMT *1000;
		}
		
		#ifdef USE_AUTO_LIMT
		
		#else
			if(OBCTag.ACRMSVolt <= (INPUT_ACVOLT_SET/2) || OBCTag.actChrVolt <= POWER_BMS_LIMT_CURRENT_VOLT_SET )
			{
				CP_CurrentLimt = CurrentLimt;
				CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CP_CURRENT_HW_lINE_8A_LIMT);
				CP_CurrentLimt1 = CurrentLimt;
			}
			else
			{
				CP_CurrentLimt = CurrentLimt;
				//CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_100doubleCURRENT(CurrentLimt) *(float)INPUT_ACVOLT_SET) / OBCTag.actChrVolt*2/100);
				CurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((DCDC_AD_CONVERT_100doubleCURRENT(CurrentLimt) *(float)OBCTag.ACRMSVolt) / OBCTag.actChrVolt*2/100);

				CP_CurrentLimt1 = CurrentLimt; 
			}
		
		#endif
		
		
		

		
	
		
		OBCPOWERTag.CPStateCurrentLimt = CurrentLimt;
		//OBCPOWERTag.CPStateCurrentLimt = CurrentLimtKeepValueInTime(CurrentLimt,CP_CurrentLimt_buffter);
		
		//autoLimtCurrent();
		
		
		
		if(OBCPOWERTag.CPStateCurrentLimt < k_Dcdc_MIN_Iref_limt)
		{
			OBCPOWERTag.CPStateCurrentLimt = k_Dcdc_MIN_Iref_limt;
		}
		
		if(k_Dcdc_Iref_Ct_u16 > OBCPOWERTag.CPStateCurrentLimt)
		{
			k_Dcdc_Iref_Ct_u16 = OBCPOWERTag.CPStateCurrentLimt;
			/*
			if(L3_Dcdc_Iout_Ct_u16 < k_Dcdc_SetpInitIref_Ct_u16)
			{
				k_Dcdc_SetpIref_Ct_u16 = k_Dcdc_SetpInitIref_Ct_u16;
			}
			*/
			/*
			else
			{
				k_Dcdc_SetpIref_Ct_u16 = L3_Dcdc_Iout_Ct_u16;
			}*/
		}
		#endif
		//reset 0
		cp_pwm_width_percent = 0;
		cp_pwm_width_percent_filter = 0;
		cp_pwm_width_percent_filter_cnt = 0;
		cpPwmWidthPFilterOffset = 0;
	}
	else
	{
		cp_pwm_senceCnt ++;
	}
}

void autoLimtCurrent()
{
	
	uint8 static runCnt = 0;
	uint8 static CurrentLimtCnt = 0;
	uint8 static powerLimtCnt = 0;
	

	if(runCnt > 100)
	{
		
		if(L5_CP_CurrentPhy_1000dLimt == MAX_CURRENT_INIT && L5_CC_CurrentPhy_1000dLimt == MAX_CURRENT_INIT)
		{
			OBCPOWERTag.ACPowMaxCurrentLimt = NO_CC_CP_LIMT*1000;
		}
		else
		{
			OBCPOWERTag.ACPowMaxCurrentLimt = L5_CP_CurrentPhy_1000dLimt> L5_CC_CurrentPhy_1000dLimt?L5_CC_CurrentPhy_1000dLimt:L5_CP_CurrentPhy_1000dLimt;
		}
		L5_InputPowerLimt = (float)POWER_FACTOR*OBCPOWERTag.ACPowMaxCurrentLimt/1000 * OBCTag.ACRMSVolt;
		//L5_outPowerLimt = (uint16)((float)DCDC_AD_CONVERT_VOLT(L3_Dcdc_Vout_Ct_u16)*DCDC_AD_CONVERT_100doubleCURRENT(L3_Dcdc_Iout_Ct_u16)/100);
		L5_outPowerLimt = (uint16)((float)DCDC_AD_CONVERT_VOLT(L3_Dcdc_Vout_Ct_u16)*DCDC_AD_CONVERT_100doubleCURRENT(L3_Dcdc_IoutFilter_Ct_u16)/100);
		
		L5_currentPowerLimt = L5_InputPowerLimt > POWER_FULL_DEFAULT_SET?POWER_FULL_DEFAULT_SET:L5_InputPowerLimt;
		
		//OBCPOWERTag.ACPowSetVoltCurrentLimt = k_Dcdc_Iref_Ct_u16;
		
		L5_actInputCurrentE = 707*(uint16)AC_AD_CONVERT_CURRENT(L5_AC_current_max_buff);
		
		if( BMSTag.actVoltage < DCDC_LOOP_VOLT_SET_LIMT)
		{
			l5_limtOutputVoltage = DCDC_LOOP_VOLT_SET_LIMT;
		}
		else if(BMSTag.actVoltage > DCDC_LOOP_VOLT_SET_MAX)
		{
			l5_limtOutputVoltage = DCDC_LOOP_VOLT_SET_MAX;
		}
		else
		{
			l5_limtOutputVoltage = BMSTag.actVoltage;
		}
		
		
		if( L5_actInputCurrentE > OBCPOWERTag.ACPowMaxCurrentLimt || L5_outPowerLimt > L5_currentPowerLimt)
		{
				
			OBCPOWERTag.ACPowSetVoltCurrentLimt = (uint16)DCDC_100double_CURRENT_AD_CONVERT((uint32)L5_currentPowerLimt*100/l5_limtOutputVoltage);

		}
		else
		{
			OBCPOWERTag.ACPowSetVoltCurrentLimt = MAX_CURRENT_INIT;
		}
	
		

		
		/*  方案二 震荡不受控
		//if( (1000*0.707*(uint16)AC_AD_CONVERT_CURRENT(L5_AC_current_max_buff)) < OBCPOWERTag.ACPowMaxCurrentLimt)
		if( L5_actInputCurrentE < OBCPOWERTag.ACPowMaxCurrentLimt)
		{
		//	CurrentLimtCnt = 0;
			CurrentLimtCnt = CurrentLimtCnt > 0?CurrentLimtCnt--:0;
			
			if(L5_outPowerLimt > L5_currentPowerLimt)
			{
				//输出功率超出最大功率（3.3KW或者输入功率x（效率））	
				if(powerLimtCnt > l5_powerLimtTimer)
				{
					OBCPOWERTag.ACPowSetVoltCurrentLimt = OBCPOWERTag.ACPowSetVoltCurrentLimt -l5_limtRampCnt;
					powerLimtCnt = powerLimtCnt > 0?powerLimtCnt--:0;
				}
				else
				{
					powerLimtCnt++;
				}
				
			}
			else
			{
				//没有超出功率
				OBCPOWERTag.ACPowSetVoltCurrentLimt = OBCPOWERTag.ACPowSetVoltCurrentLimt + l5_limtRampCnt;
				powerLimtCnt = 0;
			}
		
		}
		else
		{
			//输入电流超出，限功率
			if(CurrentLimtCnt > l5_CurrentLimtTimer)
			{
				OBCPOWERTag.ACPowSetVoltCurrentLimt = OBCPOWERTag.ACPowSetVoltCurrentLimt -l5_limtRampCnt;
				//CurrentLimtCnt = 0;
				CurrentLimtCnt = CurrentLimtCnt > 0?CurrentLimtCnt--:0;
			}
			else
			{
				CurrentLimtCnt++;
			}
		
		}
		*/
		runCnt = 0;
	}
	else
	{
		runCnt++;
	}
	
	
	

	
}

uint16 CurrentLimtKeepValueInTime(uint16	newCurrentLimt,uint16	oldCurrentLimt)
{
	uint16	CurrentLimt = oldCurrentLimt;
	static uint16 keepTimePostCnt = 0;
	static uint16 keepTimeNegCnt = 0;
	uint16 keepALLTime = 250;//250*2 MS = 500MS
	sint16	CurrentLimtError = newCurrentLimt - oldCurrentLimt;
	
	if( CurrentLimtError > 1  )
	{
		if(keepTimePostCnt >= keepALLTime)
		{
			CurrentLimt =  newCurrentLimt;
			keepTimePostCnt = 0;
			CP_CurrentLimt_buffter = newCurrentLimt;
		}
		else
		{
			keepTimePostCnt++;
		}
	}
	else if(CurrentLimtError < -1)
	{
		if(keepTimeNegCnt >= keepALLTime)
		{
			CurrentLimt =  newCurrentLimt;
			keepTimeNegCnt = 0;
			CP_CurrentLimt_buffter = newCurrentLimt;
		}
		else
		{
			keepTimeNegCnt++;
		}
	}
	
	
	return CurrentLimt;
	
}



void Uin_diag_handle(void) {
	/*
	 if(diagDelayTag.UinVoltage_DelayCntr < diagDelayTimerTag.UinVoltageDelayTime){
	 //延时10ms不检测
	 diagDelayTag.UinVoltage_DelayCntr++;
	 return;
	 }*/

	if (L5_AC_Volt_fast_maxBuffCPS > AC_Volt_fast_maxHigh_Ct_u16) {
		//220v过压

		diagCtrlTag.OverUinVoltCntr++; //开始计数
		diagRecoverTag.UinVolt_RecoverCntr = 0; //恢复清0
		if (diagCtrlTag.OverUinVoltCntr >= diagTimerTag.OverUinVoltTime) {
			//等于计数时间 判断错误
			faultCodeTag.bit.bOverUinVolt = 1;
			diagCtrlTag.OverUinVoltCntr = 0;
		}
	} else if (L5_AC_Volt_fast_maxBuffCPS < AC_Volt_fast_limtLow_Ct_u16) {
		//220v欠压
		diagCtrlTag.UnderUinVoltCntr++; //开始计数
		diagRecoverTag.UinVolt_RecoverCntr = 0; //恢复清0
		if (diagCtrlTag.UnderUinVoltCntr >= diagTimerTag.UnderUinVoltTime) {
			//等于计数时间 判断错误
			//faultCodeTag.bit.bUnderUinVolt = 1;
			diagCtrlTag.UnderUinVoltCntr = 0;
			if(L5_AC_Volt_fast_maxBuffCPS < AC_Volt_fast_OpenVolt_Ct_u16)
			{
				//DCM_FaultCode_La[faultCode_bUinVoltOpen] = enable_DCM_DTC==TRUE?TRUE:FALSE;
				faultCodeTag.bit.bUinVoltOpen = 1;
				faultCodeTag.bit.bUnderUinVolt = 0;
			}
			else
			{
				faultCodeTag.bit.bUnderUinVolt = 1;
				faultCodeTag.bit.bUinVoltOpen = 0;
			}
		}
	} else {
		if (L5_AC_Volt_fast_maxBuffCPS >= AC_Volt_fast_limtLow_Ct_u16
				&& L5_AC_Volt_fast_maxBuffCPS <= AC_Volt_fast_maxHigh_Ct_u16) {
				/*
			if (faultCodeTag.bit.bOverUinVolt == 1
					|| faultCodeTag.bit.bUnderUinVolt == 1) {
				diagRecoverTag.UinVolt_RecoverCntr++;
			}
			*/
			diagRecoverTag.UinVolt_RecoverCntr++;
			diagCtrlTag.OverUinVoltCntr = 0;
			diagCtrlTag.UnderUinVoltCntr = 0;
		}
		if (diagRecoverTag.UinVolt_RecoverCntr
				>= diagRecoverTimerTag.UinVoltRecoverTime) {
			faultCodeTag.bit.bOverUinVolt = 0;
			diagRecoverTag.UinVolt_RecoverCntr = 0;
			faultCodeTag.bit.bUnderUinVolt = 0;
			faultCodeTag.bit.bUinVoltOpen = 0;

		}
	}

}

void HWDCDC_OVP_diag_handle(void){
	static uint8_t HWDCDC_OVPRuntimerStartFlag = 0;
	static uint8_t HWDCDC_OVPInFAILUREFlag = 0;

	if(!HWDCDC_OVPInFAILUREFlag){
		if(I_DCDC_OVP == HIGH){
			faultCodeTag.bit.bHWDCDC_OVP = 1;
			if(mHWInResetTag.HWDCDC_OVPInReset == 0){
				stateCntTag.HWDCDC_OVPStateCnt++;
				HWDCDC_OVPRuntimerStartFlag = 1;
			}
		}else{
			if(mHWInResetTag.HWDCDC_OVPInReset == 0){
				//reset信号拉起操作都执行完毕，恢复软件故障标志
				faultCodeTag.bit.bHWDCDC_OVP = 0;
			}

//			HWDCDC_OVPRuntimerStartFlag = 0;
//			stateCntTag.HWDCDC_OVPStateCnt = 0;
		}

		if(HWDCDC_OVPRuntimerStartFlag){

			if (runtimerCntTag.HWDCDC_OVPRuntimerCnt
					>= runtimerTag.HWDCDC_OVPRuntimerTime) {
				if (stateCntTag.HWDCDC_OVPStateCnt
						>= stateMaxCntTag.HWDCDC_OVPStateMaxCnt) {
					faultCodeTag.bit.bHWDCDC_OVP = 1;
					HWDCDC_OVPInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.HWDCDC_OVPRuntimerCnt = 0;
					stateCntTag.HWDCDC_OVPStateCnt = 0;
					HWDCDC_OVPRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.HWDCDC_OVPStateCnt
					>= stateMaxCntTag.HWDCDC_OVPStateMaxCnt) {
				faultCodeTag.bit.bHWDCDC_OVP = 1;
				HWDCDC_OVPInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.HWDCDC_OVPRuntimerCnt++;
			}

		}
	}
}

void DCDC_Uout_diag_handle(void) {
	static uint8_t OverDCUoutVoltRuntimerStartFlag = 0;
	static uint8_t UnderDCUoutVoltRuntimerStartFlag = 0;
	static uint8_t DCUoutVoltInFAILUREFlag = 0;
	
	uint8_t DCUoutVoltNormalState = 0;
	uint8_t DCUoutVoltUnderState = 1;
	uint8_t DCUoutVoltOverState = 2;
	static uint8_t DCUoutVoltCurrentState = 0;
	
	if (!DCUoutVoltInFAILUREFlag) {

		if (L3_Dcdc_Vout_Ct_u16 > Dcdc_outVoltMax) {
			//过压
			diagCtrlTag.OverDCUoutVoltCntr++; //开始计数
			diagRecoverTag.DCUoutVolt_RecoverCntr = 0; //恢复清0
			if (diagCtrlTag.OverDCUoutVoltCntr
					>= diagTimerTag.OverDCUoutVoltTime) {
				//等于计数时间 判断错误
				faultCodeTag.bit.bOverDCUoutVolt = 1;
				diagCtrlTag.OverDCUoutVoltCntr = 0;//重新计数等待下一次判断错误出现，一分钟出现3次则进入failure状态

				
				OverDCUoutVoltRuntimerStartFlag = 1;
				if(DCUoutVoltCurrentState != DCUoutVoltOverState )
				{
					stateCntTag.OverDCUoutVoltStateCnt++;
				}
				
				DCUoutVoltCurrentState = DCUoutVoltOverState;
				

			}
		} 
		/*
		else if (L3_Dcdc_Vout_Ct_u16 < Dcdc_outVoltLim
		&& stSysFSMCtrl.ucCurrentState == STATE_OPETRATION
		&& OBC_Y.VLOOPbIT) {
		*/
		else if ((DCDC_UNDER_VOLT_DIAG_SELECT) && (L3_Dcdc_Vout_Ct_u16 < Dcdc_outVoltLim
		&& stSysFSMCtrl.ucCurrentState == STATE_OPETRATION)) {
		/*	
		else if ((DCDC_UNDER_VOLT_DIAG_SELECT) && (L3_Dcdc_Vout_Ct_u16 < Dcdc_outVoltLim
		&& stSysFSMCtrl.ucCurrentState == STATE_OPETRATION
		&& OBC_Y.VLOOPbIT)) {	
		*/		
			//欠压
			diagCtrlTag.UnderDCUoutVoltCntr++; //开始计数
			diagRecoverTag.DCUoutVolt_RecoverCntr = 0; //恢复清0
			if (diagCtrlTag.UnderDCUoutVoltCntr
					>= diagTimerTag.UnderDCUoutVoltTime) {
				//等于计数时间 判断错误
				faultCodeTag.bit.bUnderDCUoutVolt = 1;
				diagCtrlTag.UnderDCUoutVoltCntr = 0;

				
				UnderDCUoutVoltRuntimerStartFlag = 1;
				
				if(DCUoutVoltCurrentState != DCUoutVoltUnderState )
				{
					stateCntTag.UnderDCUoutVoltStateCnt++;
				}
				
				DCUoutVoltCurrentState = DCUoutVoltUnderState;
				
			}
		} else {
			if ((stSysFSMCtrl.ucCurrentState != STATE_OPETRATION||L3_Dcdc_Vout_Ct_u16 >= Dcdc_outVoltLim)
					&& L3_Dcdc_Vout_Ct_u16 <= Dcdc_outVoltMax) {
				if (faultCodeTag.bit.bOverDCUoutVolt == 1
						|| faultCodeTag.bit.bUnderDCUoutVolt == 1) {
					diagRecoverTag.DCUoutVolt_RecoverCntr++;
				}
				diagCtrlTag.OverDCUoutVoltCntr = 0;
				diagCtrlTag.UnderDCUoutVoltCntr = 0;
			}
			if (diagRecoverTag.DCUoutVolt_RecoverCntr
					>= diagRecoverTimerTag.DCUoutVoltRecoverTime) {
				faultCodeTag.bit.bOverDCUoutVolt = 0;
				diagRecoverTag.DCUoutVolt_RecoverCntr = 0;
				faultCodeTag.bit.bUnderDCUoutVolt = 0;
				
				DCUoutVoltCurrentState = DCUoutVoltNormalState;
			}
		}
		//计时
		if (OverDCUoutVoltRuntimerStartFlag) {
			if (runtimerCntTag.OverDCUoutVoltRuntimerCnt
					>= runtimerTag.OverDCUoutVoltRuntimerTime) {
				if (stateCntTag.OverDCUoutVoltStateCnt
						>= stateMaxCntTag.OverDCUoutVoltStateMaxCnt) {
					faultCodeTag.bit.bOverDCUoutVolt = 1;
					DCUoutVoltInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.OverDCUoutVoltRuntimerCnt = 0;
					stateCntTag.OverDCUoutVoltStateCnt = 0;
					OverDCUoutVoltRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.OverDCUoutVoltStateCnt
					>= stateMaxCntTag.OverDCUoutVoltStateMaxCnt) {
				faultCodeTag.bit.bOverDCUoutVolt = 1;
				DCUoutVoltInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.OverDCUoutVoltRuntimerCnt++;
			}
		}
		
		if (UnderDCUoutVoltRuntimerStartFlag) {
			if (runtimerCntTag.UnderDCUoutVoltRuntimerCnt
					>= runtimerTag.UnderDCUoutVoltRuntimerTime) {
				if (stateCntTag.UnderDCUoutVoltStateCnt
						>= stateMaxCntTag.UnderDCUoutVoltStateMaxCnt) {
					faultCodeTag.bit.bUnderDCUoutVolt = 1;
					DCUoutVoltInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.UnderDCUoutVoltRuntimerCnt = 0;
					stateCntTag.UnderDCUoutVoltStateCnt = 0;
					UnderDCUoutVoltRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.UnderDCUoutVoltStateCnt
					>= stateMaxCntTag.UnderDCUoutVoltStateMaxCnt) {
				faultCodeTag.bit.bUnderDCUoutVolt = 1;
				DCUoutVoltInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.UnderDCUoutVoltRuntimerCnt++;
			}
		}
		

	}

}



void DCDC_Iout_diag_handle(void) {
	static uint8_t OverDCIoutRuntimerStartFlag = 0;
	static uint8_t DCIoutInFAILUREFlag = 0;
	
	uint8_t DCIoutNormalState = 0;
	uint8_t DCIoutOverState = 1;

	static uint8_t DCIoutCurrentState = 0;
	
	
	uint32_t  trickleTime = 30000;//60 * 1000 / DIAG_THREAD_CYCLE_TIME
	static uint32_t  trickleCnt = 0;
	//*
	if((stSysFSMCtrl.ucCurrentState == STATE_OPETRATION && L3_Dcdc_IoutFilter_Ct_u16 < k_Dcdc_MIN_Iref_limt))
	{
		
		if(trickleCnt >= trickleTime)
		{
			trickleCnt = 0;
			O_PG = LOW;
			HW_O_PG = O_PG;
			BMS_CHARGE_OVER = TRUE;
			goStandBy();
			return ;
		}
		else
		{
			trickleCnt++;
		}
	}
	//*/
	
	
	if (!DCIoutInFAILUREFlag) {

		if (L3_Dcdc_Iout_Ct_u16 > Dcdc_IoutMax) {
			//过流
			diagCtrlTag.OverDCUoutICntr++; //开始计数
			diagRecoverTag.OverDCUoutI_RecoverCntr = 0; //恢复清0
			if (diagCtrlTag.OverDCUoutICntr
					>= diagTimerTag.OverDCUoutITime) {
				//等于计数时间 判断错误
				faultCodeTag.bit.bOverDCUoutI = 1;
				diagCtrlTag.OverDCUoutICntr = 0;//重新计数等待下一次判断错误出现，一分钟出现3次则进入failure状态

				
				OverDCIoutRuntimerStartFlag = 1;
				
				if(DCIoutCurrentState != DCIoutOverState )
				{
					stateCntTag.OverDCUoutIStateCnt++;
				}
				
				DCIoutCurrentState = DCIoutOverState;
			}
		}
		
		else {
			if ( L3_Dcdc_Iout_Ct_u16 <= Dcdc_IoutMax) {
				if (faultCodeTag.bit.bOverDCUoutI == 1) {
					diagRecoverTag.OverDCUoutI_RecoverCntr++;
				}
				diagCtrlTag.OverDCUoutICntr = 0;
			}
			if (diagRecoverTag.OverDCUoutI_RecoverCntr
					>= diagRecoverTimerTag.OverDCUoutIRecoverTime) {
				faultCodeTag.bit.bOverDCUoutI = 0;
				diagRecoverTag.OverDCUoutI_RecoverCntr = 0;
				
				DCIoutCurrentState = DCIoutNormalState;
			}
		}
		//计时
		if (OverDCIoutRuntimerStartFlag) {
			if (runtimerCntTag.OverDCUoutIRuntimerCnt
					>= runtimerTag.OverDCUoutIRuntimerTime) {
				if (stateCntTag.OverDCUoutIStateCnt
						>= stateMaxCntTag.OverDCUoutIStateMaxCnt) {
					faultCodeTag.bit.bOverDCUoutI = 1;
					DCIoutInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.OverDCUoutIRuntimerCnt = 0;
					stateCntTag.OverDCUoutIStateCnt = 0;
					OverDCIoutRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.OverDCUoutIStateCnt
					>= stateMaxCntTag.OverDCUoutIStateMaxCnt) {
				faultCodeTag.bit.bOverDCUoutI = 1;
				DCIoutInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.OverDCUoutIRuntimerCnt++;
			}
		}
	}

}



void HWDCDC_OCP_diag_handle(void){
	static uint8_t HWDCDC_OCPRuntimerStartFlag = 0;
	static uint8_t HWDCDC_OCPInFAILUREFlag = 0;
	
	
	uint8_t HWDCDC_OCPNormalState = 0;
	uint8_t HWDCDC_OCPOverState = 1;

	static uint8_t HWDCDC_OCPState = 0;
	

	if(!HWDCDC_OCPInFAILUREFlag){
		if(I_DCDC_OCP == HIGH){
			faultCodeTag.bit.bHWDCDC_OCP = 1;
			if(mHWInResetTag.HWDCDC_OCPInReset == 0){
				
				HWDCDC_OCPRuntimerStartFlag = 1;
				
				//if( HWDCDC_OCPState != HWDCDC_OCPOverState)
				//{
				//	stateCntTag.HWDCDC_OCPStateCnt++;
				//}
				stateCntTag.HWDCDC_OCPStateCnt++;
				HWDCDC_OCPState = HWDCDC_OCPOverState;
			}
		}else{
		
			if(mHWInResetTag.HWDCDC_OCPInReset == 0){
				//reset信号拉起操作都执行完毕，恢复软件故障标志
				faultCodeTag.bit.bHWDCDC_OCP = 0;
				HWDCDC_OCPState = HWDCDC_OCPNormalState;
				mHWInResetTag.HWDCDC_OCPInReset = 0xff;
				HWDCDC_OCPRuntimerStartFlag = 1;
				stateCntTag.HWDCDC_OCPStateCnt++;
			}
		}

		if(HWDCDC_OCPRuntimerStartFlag){

			if (runtimerCntTag.HWDCDC_OCPRuntimerCnt
					>= runtimerTag.HWDCDC_OCPRuntimerTime) {
				if (stateCntTag.HWDCDC_OCPStateCnt
						> stateMaxCntTag.HWDCDC_OCPStateMaxCnt) {
					faultCodeTag.bit.bHWDCDC_OCP = 1;
					HWDCDC_OCPInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.HWDCDC_OCPRuntimerCnt = 0;
					stateCntTag.HWDCDC_OCPStateCnt = 0;
					HWDCDC_OCPRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.HWDCDC_OCPStateCnt
					> stateMaxCntTag.HWDCDC_OCPStateMaxCnt) {
				faultCodeTag.bit.bHWDCDC_OCP = 1;
				HWDCDC_OCPInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.HWDCDC_OCPRuntimerCnt++;
			}

		}
	}
}




void HWPFC_OVP_diag_handle(void){
	static uint8_t HWPFC_OVPRuntimerStartFlag = 0;
		static uint8_t HWPFC_OVPInFAILUREFlag = 0;

		if(!HWPFC_OVPInFAILUREFlag){
			if(I_PFC_OVP == HIGH){
				faultCodeTag.bit.bHWPFC_OVP = 1;
				if(mHWInResetTag.HWPFC_OVPInReset == 0){
					stateCntTag.HWPFC_OVPStateCnt++;
					HWPFC_OVPRuntimerStartFlag = 1;
				}
			}else{
				if(mHWInResetTag.HWPFC_OVPInReset == 0){
					//reset信号拉起操作都执行完毕，恢复软件故障标志
					faultCodeTag.bit.bHWPFC_OVP = 0;
				}

			}

			if(HWPFC_OVPRuntimerStartFlag){

				if (runtimerCntTag.HWPFC_OVPRuntimerCnt
						>= runtimerTag.HWPFC_OVPRuntimerTime) {
					if (stateCntTag.HWPFC_OVPStateCnt
							>= stateMaxCntTag.HWPFC_OVPStateMaxCnt) {
						faultCodeTag.bit.bHWPFC_OVP = 1;
						HWPFC_OVPInFAILUREFlag = 1;
						//不可恢复
						stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
						FSM_run();
					} else {
						runtimerCntTag.HWPFC_OVPRuntimerCnt = 0;
						stateCntTag.HWPFC_OVPStateCnt = 0;
						HWPFC_OVPRuntimerStartFlag = 0;
					}
				} else if (stateCntTag.HWPFC_OVPStateCnt
						>= stateMaxCntTag.HWPFC_OVPStateMaxCnt) {
					faultCodeTag.bit.bHWPFC_OVP = 1;
					HWPFC_OVPInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.HWPFC_OVPRuntimerCnt++;
				}

			}
		}
}
void PFC_Uout_diag_handle(void){

	static uint8_t OverPFCUoutVoltRuntimerStartFlag = 0;
	static uint8_t UnderPFCUoutVoltRuntimerStartFlag = 0;
	static uint8_t PFCUoutVoltInFAILUREFlag = 0;
	
	uint8_t PFCUoutVoltNormalState = 0;
	uint8_t PFCUoutVoltUnderState = 1;
	uint8_t PFCUoutVoltOverState = 2;
	static uint8_t PFCUoutVoltCurrentState = 0;
	

	if (!PFCUoutVoltInFAILUREFlag) {

		if (L3_I_AD_PFC_slow_Ct_u16 > PFC_outVoltMax) {
			//过压
			diagCtrlTag.OverPFCUoutVoltCntr++; //开始计数
			diagRecoverTag.PFCUoutVolt_RecoverCntr = 0; //恢复清0
			if (diagCtrlTag.OverPFCUoutVoltCntr
					>= diagTimerTag.OverPFCUoutVoltTime) {
				//等于计数时间 判断错误
				faultCodeTag.bit.bOverPFCUoutVolt = 1;
				diagCtrlTag.OverPFCUoutVoltCntr = 0;//重新计数等待下一次判断错误出现，一分钟出现3次则进入failure状态

				
				OverPFCUoutVoltRuntimerStartFlag = 1;
				if(PFCUoutVoltCurrentState != PFCUoutVoltOverState )
				{
					stateCntTag.OverPFCUoutVoltStateCnt++;
				}
				
				PFCUoutVoltCurrentState = PFCUoutVoltOverState;

			}
		}
		/*
		 else if (L3_I_AD_PFC_slow_Ct_u16 < PFC_outVoltLim
				&& stSysFSMCtrl.ucCurrentState == STATE_OPETRATION) {
			//欠压
			diagCtrlTag.UnderPFCUoutVoltCntr++; //开始计数
			diagRecoverTag.PFCUoutVolt_RecoverCntr = 0; //恢复清0
			if (diagCtrlTag.UnderPFCUoutVoltCntr
					>= diagTimerTag.UnderPFCUoutVoltTime) {
				//等于计数时间 判断错误
				faultCodeTag.bit.bUnderPFCUoutVolt = 1;
				diagCtrlTag.UnderPFCUoutVoltCntr = 0;

				
				UnderPFCUoutVoltRuntimerStartFlag = 1;
				
				if(PFCUoutVoltCurrentState != PFCUoutVoltUnderState )
				{
					stateCntTag.UnderPFCUoutVoltStateCnt++;
				}
				
				PFCUoutVoltCurrentState = PFCUoutVoltUnderState;

			}
		}
		*/
		 else {
			if ((stSysFSMCtrl.ucCurrentState != STATE_OPETRATION||L3_I_AD_PFC_slow_Ct_u16 >= PFC_outVoltLim)
					&& L3_I_AD_PFC_slow_Ct_u16 <= PFC_outVoltMax) {
				if (faultCodeTag.bit.bOverPFCUoutVolt == 1
						|| faultCodeTag.bit.bUnderPFCUoutVolt == 1) {
					diagRecoverTag.PFCUoutVolt_RecoverCntr++;
				}
				diagCtrlTag.OverPFCUoutVoltCntr = 0;
				diagCtrlTag.UnderPFCUoutVoltCntr = 0;
			}
			if (diagRecoverTag.PFCUoutVolt_RecoverCntr
					>= diagRecoverTimerTag.PFCUoutVoltRecoverTime) {
				faultCodeTag.bit.bOverPFCUoutVolt = 0;
				diagRecoverTag.PFCUoutVolt_RecoverCntr = 0;
				faultCodeTag.bit.bUnderPFCUoutVolt= 0;
				
				PFCUoutVoltCurrentState = PFCUoutVoltNormalState;
			}
		}
		//计时
		if (OverPFCUoutVoltRuntimerStartFlag) {
			if (runtimerCntTag.OverPFCUoutVoltRuntimerCnt
					>= runtimerTag.OverPFCUoutVoltRuntimerTime) {
				if (stateCntTag.OverPFCUoutVoltStateCnt
						>= stateMaxCntTag.OverPFCUoutVoltStateMaxCnt) {
					faultCodeTag.bit.bOverPFCUoutVolt = 1;
					PFCUoutVoltInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.OverPFCUoutVoltRuntimerCnt = 0;
					stateCntTag.OverPFCUoutVoltStateCnt = 0;
					OverPFCUoutVoltRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.OverPFCUoutVoltStateCnt
					>= stateMaxCntTag.OverPFCUoutVoltStateMaxCnt) {
				faultCodeTag.bit.bOverPFCUoutVolt = 1;
				PFCUoutVoltInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.OverPFCUoutVoltRuntimerCnt++;
			}
		}
		/*
		if (UnderPFCUoutVoltRuntimerStartFlag) {
			if (runtimerCntTag.UnderPFCUoutVoltRuntimerCnt
					>= runtimerTag.UnderPFCUoutVoltRuntimerTime) {
				if (stateCntTag.UnderPFCUoutVoltStateCnt
						>= stateMaxCntTag.UnderPFCUoutVoltStateMaxCnt) {
					faultCodeTag.bit.bUnderPFCUoutVolt = 1;
					PFCUoutVoltInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.UnderPFCUoutVoltRuntimerCnt = 0;
					stateCntTag.UnderPFCUoutVoltStateCnt = 0;
					UnderPFCUoutVoltRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.UnderPFCUoutVoltStateCnt
					>= stateMaxCntTag.UnderPFCUoutVoltStateMaxCnt) {
				faultCodeTag.bit.bUnderPFCUoutVolt = 1;
				PFCUoutVoltInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.UnderPFCUoutVoltRuntimerCnt++;
			}
		}
		*/
	}
}
void HWPFC_OCP_diag_handle(void){
	static uint8_t HWPFC_OCPRuntimerStartFlag = 0;
	static uint8_t HWPFC_OCPInFAILUREFlag = 0;

	if(!HWPFC_OCPInFAILUREFlag){
		if(I_PFC_OCP == HIGH){
			faultCodeTag.bit.bHWPFC_OCP = 1;
			if(mHWInResetTag.HWPFC_OCPInReset == 0){
				stateCntTag.HWPFC_OCPStateCnt++;
				HWPFC_OCPRuntimerStartFlag = 1;
			}
		}else{
			if(mHWInResetTag.HWPFC_OCPInReset == 0){
				//reset信号拉起操作都执行完毕，恢复软件故障标志
				faultCodeTag.bit.bHWPFC_OCP = 0;
			}
		}

		if(HWPFC_OCPRuntimerStartFlag){

			if (runtimerCntTag.HWPFC_OCPRuntimerCnt
					>= runtimerTag.HWPFC_OCPRuntimerTime) {
				if (stateCntTag.HWPFC_OCPStateCnt
						>= stateMaxCntTag.HWPFC_OCPStateMaxCnt) {
					faultCodeTag.bit.bHWPFC_OCP = 1;
					HWPFC_OCPInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.HWPFC_OCPRuntimerCnt = 0;
					stateCntTag.HWPFC_OCPStateCnt = 0;
					HWPFC_OCPRuntimerStartFlag = 0;
				}
			} else if (stateCntTag.HWPFC_OCPStateCnt
					>= stateMaxCntTag.HWPFC_OCPStateMaxCnt) {
				faultCodeTag.bit.bHWPFC_OCP = 1;
				HWPFC_OCPInFAILUREFlag = 1;
				//不可恢复
				stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
				FSM_run();
			} else {
				runtimerCntTag.HWPFC_OCPRuntimerCnt++;
			}

		}
	}
}
void PFC_Iout_diag_handle(void){
	static uint8_t OverPFCIoutRuntimerStartFlag = 0;
		static uint8_t PFCIoutInFAILUREFlag = 0;

		if (!PFCIoutInFAILUREFlag) {

			if (L3_I_AD_Curr_Input > Curr_Input_IoutMax) {
				//过流
				diagCtrlTag.OverPFCUoutICntr++; //开始计数
				diagRecoverTag.OverPFCUoutI_RecoverCntr = 0; //恢复清0
				if (diagCtrlTag.OverPFCUoutICntr
						>= diagTimerTag.OverPFCUoutITime) {
					//等于计数时间 判断错误
					faultCodeTag.bit.bOverPFCUoutI = 1;
					diagCtrlTag.OverPFCUoutICntr = 0;//重新计数等待下一次判断错误出现，一分钟出现3次则进入failure状态

					stateCntTag.OverPFCUoutIStateCnt++;
					OverPFCIoutRuntimerStartFlag = 1;
				}
			}else {
				if ( L3_I_AD_Curr_Input <= Curr_Input_IoutMax) {
					if (faultCodeTag.bit.bOverPFCUoutI == 1) {
						diagRecoverTag.OverPFCUoutI_RecoverCntr++;
					}
					diagCtrlTag.OverPFCUoutICntr = 0;
				}
				if (diagRecoverTag.OverPFCUoutI_RecoverCntr
						>= diagRecoverTimerTag.OverPFCUoutIRecoverTime) {
					faultCodeTag.bit.bOverPFCUoutI = 0;
					diagRecoverTag.OverPFCUoutI_RecoverCntr = 0;
				}
			}
			//计时
			if (OverPFCIoutRuntimerStartFlag) {
				if (runtimerCntTag.OverPFCUoutIRuntimerCnt
						>= runtimerTag.OverPFCUoutIRuntimerTime) {
					if (stateCntTag.OverPFCUoutIStateCnt
							>= stateMaxCntTag.OverPFCUoutIStateMaxCnt) {
						faultCodeTag.bit.bOverPFCUoutI = 1;
						PFCIoutInFAILUREFlag = 1;
						//不可恢复
						stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
						FSM_run();
					} else {
						runtimerCntTag.OverPFCUoutIRuntimerCnt = 0;
						stateCntTag.OverPFCUoutIStateCnt = 0;
						OverPFCIoutRuntimerStartFlag = 0;
					}
				} else if (stateCntTag.OverPFCUoutIStateCnt
						>= stateMaxCntTag.OverPFCUoutIStateMaxCnt) {
					faultCodeTag.bit.bOverPFCUoutI = 1;
					PFCIoutInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else {
					runtimerCntTag.OverPFCUoutIRuntimerCnt++;
				}
			}
		}

}






void loadDump_diag_handle(void) {
	//sint16 tempK = ((sint16)L3_Dcdc_Vout_Ct_u16-loadDumpLastVolt)/loadDumpLastVolt;
	sint16 tempUpVal =
			(sint16) ((sint16) L3_Dcdc_Vout_Ct_u16 - loadDumpLastVolt);

	if (stSysFSMCtrl.ucCurrentState == STATE_OPETRATION) {

		/*if(L3_Dcdc_Iout_Ct_u16 < loadDumpRefCurrent && tempUpVal > loadDumpUpVal)
		 {
		 faultCodeTag.bit.bloadDump = 1;
		 }
		 */
		/*
		 if(tempUpVal > loadDumpUpMaxVal)
		 {
		 loadDumpUpMaxVal = tempUpVal;
		 }
		 */
		if (L3_Dcdc_Iout_Ct_u16 < loadDumpRefCurrent
				&& tempUpVal > loadDumpUpVal)
				//	if(L3_Dcdc_Iout_Ct_u16 < loadDumpRefCurrent && loadDumpUpMaxVal > loadDumpUpVal)
				//	if(loadDumpUpMaxVal > loadDumpUpVal)
						{
			faultCodeTag.bit.bloadDump = 1;
		}
	}

	loadDumpLastVolt = L3_Dcdc_Vout_Ct_u16;
}


void temperature_diag_handle()
{
	static uint8_t OverTempStartFlag = 0;
	static uint8_t OverTempInFAILUREFlag = 0;
	
	uint8_t TempNormalState = 0;
	uint8_t OverTempState = 1;

	static uint8_t TempState = 0;

	if (!OverTempInFAILUREFlag) 
	{

		if (protect_TEM >= TEMP_PROTECT) 
		{
			//过温
			diagCtrlTag.OverTempCntr++; //开始计数
			diagRecoverTag.OverTempRecoverCntr = 0; //恢复清0
		 
			if (diagCtrlTag.OverTempCntr >= diagTimerTag.OverTempTime) 
			{
				
					//OverTemp
				//等于计数时间 判断错误
				diagCtrlTag.OverTempCntr = 0;
				faultCodeTag.bit.bOverTempCool = 1;
				diagCtrlTag.OverTempCntr = 0;//重新计数等待下一次判断错误出现，一分钟出现3次则进入failure状态
				
				OverTempStartFlag = 1;
				
				if(TempState != OverTempState )
				{
					stateCntTag.OverTempStateCnt++;
				}
				
				TempState = OverTempState;
			}
		}else 
		{
			if ( protect_TEM <= TEMP_PROTECT_CANCLE) 
			{
				if (faultCodeTag.bit.bOverTempCool == 1) 
				{
					diagRecoverTag.OverTempRecoverCntr++;
				}
				diagCtrlTag.OverTempCntr = 0;
			
			}
			if (diagRecoverTag.OverTempRecoverCntr >= diagRecoverTimerTag.OverTempRecoverTime) 
			{
				faultCodeTag.bit.bOverTempCool = 0;
				diagRecoverTag.OverTempRecoverCntr = 0;
				
				TempState = TempNormalState;
			}
		}
		//计时
		if(OverTempStartFlag)
		{
			if (runtimerCntTag.OverTempRuntimerCnt >= runtimerTag.OverTempRuntimerTime) 
			{
				if (stateCntTag.OverTempStateCnt>= stateMaxCntTag.OverTempStateMaxCnt) 
				{
					faultCodeTag.bit.bOverTempCool = 1;
					OverTempInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else 
				{
					runtimerCntTag.OverTempRuntimerCnt = 0;
					stateCntTag.OverTempStateCnt = 0;
					OverTempStartFlag = 0;
				}
			} else if (stateCntTag.OverTempStateCnt>= stateMaxCntTag.OverTempStateMaxCnt) 
			{
					faultCodeTag.bit.bOverTempCool = 1;
					OverTempInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
			} else 
			{
				runtimerCntTag.OverTempRuntimerCnt++;
			}	
		}
		
	}
	
	
	
	/*
	
	
		if(protect_TEM > TEMP_PROTECT)
	{
		diagCtrlTag.OverTempCntr++;
	
		if(diagCtrlTag.OverTempCntr >= diagTimerTag.OverTempTime)
		{
			//OverTemp
			diagCtrlTag.OverTempCntr = 0;
			faultCodeTag.bit.bOverTempCool = 1;
		}
	}
	else
	{
		diagCtrlTag.OverTempCntr = 0;
	}
	
	
	*/
	
}


void TempPowerLimit_diag_handle()
{
		
	static uint8_t TempWarinOutOffStartFlag = 0;
	static uint8_t TempWarinOutOffInFAILUREFlag = 0;
	
	uint8_t TempNormalState = 0;
	uint8_t TempWarinOutOffState = 1;

	static uint8_t TempState = 0;

	uint16 ACPowSetVoltCurrentPhy = 0;
	OBCTag.chrPCB_TEM = getTemperatureValue(L3_I_AD_PCB_TEM,I_AD_PCB_TEM_Table);
	OBCTag.chrFB_TEM = getTemperatureValue(L3_I_AD_FB_TEM,I_AD_FB_TEM_Table);
	
	//OBCTag.ChrTemp = (OBCTag.chrPCB_TEM  > OBCTag.chrFB_TEM) ? OBCTag.chrPCB_TEM : OBCTag.chrFB_TEM;

	derating_TEM = OBCTag.chrFB_TEM ;
	protect_TEM = OBCTag.chrPCB_TEM;

	/*
	if (!TempWarinOutOffInFAILUREFlag) 
	{

		if (derating_TEM >= TEMP_DERATING_END) 
		{
			//过温
			diagCtrlTag.TempWarinOutOffCntr++; //开始计数
			diagRecoverTag.TempDeratingRecoverCntr = 0; //恢复清0
			diagRecoverTag.TempWarinOutOffRecoverCntr = 0; //恢复清0
			if (diagCtrlTag.TempWarinOutOffCntr >= diagTimerTag.TempWarinOutOffTime) 
			{
				
				//TempWarinOutOff
				//等于计数时间 判断错误
				faultCodeTag.bit.bTempWarinOutOff = 1;
				diagCtrlTag.TempWarinOutOffCntr = 0;//重新计数等待下一次判断错误出现，一分钟出现3次则进入failure状态
				diagCtrlTag.TempDeratingCntr = 0;
				//O_PG = LOW;
				TempWarinOutOffStartFlag = 1;
				
				if(TempState != TempWarinOutOffState )
				{
					stateCntTag.TempWarinOutOffStateCnt++;
				}
				
				TempState = TempWarinOutOffState;
			}
		}else 
		{
			if ( derating_TEM <= TEMP_DERATING_CANCLE) 
			{
				if (faultCodeTag.bit.bTempWarinOutOff == 1) 
				{
					diagRecoverTag.TempWarinOutOffRecoverCntr++;
				}
				diagCtrlTag.TempWarinOutOffCntr = 0;
				diagCtrlTag.TempDeratingCntr = 0;
				//O_PG = HIGH;
			}
			else
			{
				diagRecoverTag.TempWarinOutOffRecoverCntr = 0; //恢复清0
				diagRecoverTag.TempDeratingRecoverCntr = 0; //恢复清0

			}
			if (diagRecoverTag.TempWarinOutOffRecoverCntr >= diagRecoverTimerTag.TempWarinOutOffRecoverTime) 
			{
				faultCodeTag.bit.bTempWarinOutOff = 0;
				diagRecoverTag.OverDCUoutI_RecoverCntr = 0;
				
				TempState = TempNormalState;
			}
		}
		//计时
		if(TempWarinOutOffStartFlag)
		{
			if (runtimerCntTag.TempWarinOutOffRuntimerCnt >= runtimerTag.TempWarinOutOffRuntimerTime) 
			{
				if (stateCntTag.TempWarinOutOffStateCnt>= stateMaxCntTag.TempWarinOutOffStateMaxCnt) 
				{
					faultCodeTag.bit.bTempWarinOutOff = 1;
					TempWarinOutOffInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
				} else 
				{
					runtimerCntTag.TempWarinOutOffRuntimerCnt = 0;
					stateCntTag.TempWarinOutOffStateCnt = 0;
					TempWarinOutOffStartFlag = 0;
				}
			} else if (stateCntTag.TempWarinOutOffStateCnt>= stateMaxCntTag.TempWarinOutOffStateMaxCnt) 
			{
					faultCodeTag.bit.bTempWarinOutOff = 1;
					TempWarinOutOffInFAILUREFlag = 1;
					//不可恢复
					stSysFSMCtrl.ucCurrentState = STATE_FAILURE;
					FSM_run();
			} else 
			{
				runtimerCntTag.TempWarinOutOffRuntimerCnt++;
			}	
		}
		
	}

	
	*/
	
	
	
	/*
	
	
		
	if(derating_TEM >= TEMP_DERATING_END)
	{
		diagCtrlTag.TempWarinOutOffCntr++;
		diagRecoverTag.TempDeratingRecoverCntr = 0;
		if(diagCtrlTag.TempWarinOutOffCntr >= diagTimerTag.TempWarinOutOffTime)
		{
			//TempWarinOutOff
			
			diagCtrlTag.TempDeratingCntr = 0;
			
			faultCodeTag.bit.bTempWarinOutOff = 1;
		}
	}
	else
	{
		diagCtrlTag.TempDeratingCntr = 0;
		diagCtrlTag.TempWarinOutOffCntr = 0;
		OBCPOWERTag.TEMPStateCurrentLimt = 	OBCPOWERTag.ACPowSetVoltCurrentLimt;
		
	//	faultCodeTag.bit.bTempWarinOutOff = 0;
		
	
		
	}
	
	
	*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	if(derating_TEM >= TEMP_DERATING_END)
	{
		diagCtrlTag.TempWarinOutOffCntr++;
		diagRecoverTag.TempDeratingRecoverCntr = 0;
		if(diagCtrlTag.TempWarinOutOffCntr >= diagTimerTag.TempWarinOutOffTime)
		{
			//TempWarinOutOff
			
			diagCtrlTag.TempDeratingCntr = 0;
			
			faultCodeTag.bit.bTempWarinOutOff = 1;
		}
	}
	else if(TEMP_DERATING_BEIGIN<= derating_TEM  && derating_TEM<= TEMP_DERATING_END)
	{
		//
		diagCtrlTag.TempDeratingCntr++;
		diagRecoverTag.TempWarinOutOffRecoverCntr = 0;
		if(diagCtrlTag.TempDeratingCntr >= diagTimerTag.TempDeratingTime)
		{
			//TempDerating
			
			diagCtrlTag.TempDeratingCntr = 0;
			OBCTag.PowerLimit = 1;
			
			//y = (y1*x-y1*x2)/(x1-x2) = (y1*x2-y1*x)/(x2-x1)
		//	ACPowSetVoltCurrentPhy = DCDC_AD_CONVERT_CURRENT(OBCPOWERTag.ACPowSetVoltCurrentLimt);// everytime derating
			ACPowSetVoltCurrentPhy = DCDC_AD_CONVERT_CURRENT(OBCPOWERTag.HWLimtMAXCurrent);//12 derating
			
			OBCPOWERTag.TEMPStateCurrentLimt = DCDC_CURRENT_AD_CONVERT((ACPowSetVoltCurrentPhy*TEMP_DERATING_END-ACPowSetVoltCurrentPhy*derating_TEM)/(TEMP_DERATING_END-TEMP_DERATING_BEIGIN));
			#ifdef HAS_INPUT_POWER_LIMT
			if(OBCPOWERTag.TEMPStateCurrentLimt < k_Dcdc_MIN_Iref_limt)
			{
				OBCPOWERTag.TEMPStateCurrentLimt = k_Dcdc_MIN_Iref_limt;
			}
			
			if(k_Dcdc_Iref_Ct_u16 > OBCPOWERTag.TEMPStateCurrentLimt)
			{
				k_Dcdc_Iref_Ct_u16 = OBCPOWERTag.TEMPStateCurrentLimt;
				k_Dcdc_SetpIref_Ct_u16 = L3_Dcdc_Iout_Ct_u16;
			}
			#endif
		}
	}
	else
	{
		diagCtrlTag.TempDeratingCntr = 0;
		diagCtrlTag.TempWarinOutOffCntr = 0;
		//OBCPOWERTag.TEMPStateCurrentLimt = 	OBCPOWERTag.ACPowSetVoltCurrentLimt;
		faultCodeTag.bit.bTempWarinOutOff = 0;
		
	}
	
	
	
	


}


int16_t getTemperatureValue(uint16_t uiInputVlt,uint8_t tempTableId) {
	int16_t uiTemp = 0;
	if(I_AD_PCB_TEM_Table == tempTableId){
		uiTemp = Interpolate_16_To_16(uiInputVlt,
					No_Elems(PCB_T_ADC_Count_X), PCB_T_ADC_Count_X, PCB_T_DegC_Y);
	}else if(I_AD_FB_TEM_Table == tempTableId){
		uiTemp = Interpolate_16_To_16(uiInputVlt,
		No_Elems(FB_T_ADC_Count_X), FB_T_ADC_Count_X, FB_T_DegC_Y);
	}else{
		uiTemp = Interpolate_16_To_16(uiInputVlt,
		No_Elems(FB_T_ADC_Count_X), FB_T_ADC_Count_X, FB_T_DegC_Y);
	}

	return (uiTemp);
}

void sys_diag_task(void) {

	//TEST1 = HIGH;
//	Driver13V_diag_handle();
//	LV_12V_diag_handle();
//	PG_diag_handle();
	CPVolt_diag_handle();
	CP_diag_handle();
	#ifdef AC_DIAG_ENABLE
		Uin_diag_handle();
	#endif
	
	#ifdef DCDC_DIAG_ENABLE
		DCDC_Uout_diag_handle();
	#endif
	//HWDCDC_OVP_diag_handle();
	DCDC_Iout_diag_handle();
	
	#ifdef HWDCDC_OCP_DIAG_ENABLE
		HWDCDC_OCP_diag_handle();
	#endif
	


	//HWPFC_OVP_diag_handle();
	PFC_Uout_diag_handle();
	//HWPFC_OCP_diag_handle();
	
	#ifdef TEMP_DIAG_ENABLE
		TempPowerLimit_diag_handle();
		temperature_diag_handle();
	#endif
	

	#ifdef CC_STATE_DIAG_ENABLE
		CCState_diag_handle();
	#endif
	
	
	#ifdef USE_AUTO_LIMT
		autoLimtCurrent();
	#else
	
	#endif
	LV_12V_diag_handle();
	dcdc_start_short_circuit();
	Driver13V_diag_handle();
	input_Relay_diag_handle();
	PG_diag_handle();
	CAN_diag_handle();
	
	getMinCurrent();
	
	//StateTimeOut_diag_handle();
	
	CMDState_diag_handle();
	
	PFC_Iout_diag_handle();
	
	//TEST1 = LOW;

	//loadDump_diag_handle();
}

BOOL powerOnDiag(void) {
	BOOL ret = FALSE;
	static uint16 lv12KeepCnt = 0;
	if (L3_I_AD_12V_CMM >= LV_12V_limtLow_Ct_u16
						&& L3_I_AD_12V_CMM <= LV_12V_maxHigh_Ct_u16) 
	{
		
		if(lv12KeepCnt >= 250)//500/2//500ms
		{
				ret = TRUE;
				lv12KeepCnt=0;
		}
		else
		{
			lv12KeepCnt++;
		}
	
	
	}
	 return ret&&outputCurrentSen_diag_handle();
}


void getMinCurrent()
{

	if(L5_PowerLimtEnable == TRUE)
	{
		#ifdef HAS_INPUT_POWER_LIMT
		uint16 CURRENT_AD = 0xFFFF;
		
		
		if(CURRENT_AD >= OBCPOWERTag.HWLimtMAXCurrent)
		{
			CURRENT_AD = OBCPOWERTag.HWLimtMAXCurrent;
		}
		
		/*
		if(CURRENT_AD >= OBCPOWERTag.ACPowMaxCurrentLimt)
		{
			CURRENT_AD = OBCPOWERTag.ACPowMaxCurrentLimt;
		}
		*/
		#ifdef USE_AUTO_LIMT
			if(CURRENT_AD >= OBCPOWERTag.ACPowSetVoltCurrentLimt)
			{
				CURRENT_AD = OBCPOWERTag.ACPowSetVoltCurrentLimt;
			}
		#else
			if(CURRENT_AD >= OBCPOWERTag.CCStateCurrentLimt)
			{
				CURRENT_AD = OBCPOWERTag.CCStateCurrentLimt;
			}

			if(CURRENT_AD >= OBCPOWERTag.CPStateCurrentLimt)
			{
				CURRENT_AD = OBCPOWERTag.CPStateCurrentLimt;
			}
		
		#endif



		if(CURRENT_AD >= OBCPOWERTag.TEMPStateCurrentLimt)
		{
			CURRENT_AD = OBCPOWERTag.TEMPStateCurrentLimt;
		}
		/*
		
		*/
		if(CURRENT_AD >= OBCPOWERTag.CANCmdSETCurrent)
		{
			CURRENT_AD = OBCPOWERTag.CANCmdSETCurrent;
			if(CURRENT_AD == 0)
			{
				goStandBy();
				return;
			}
			
		}


		if(CURRENT_AD < k_Dcdc_MIN_Iref_limt)
		{
			CURRENT_AD = k_Dcdc_MIN_Iref_limt;
		}

		k_Dcdc_Iref_Ct_u16 = CURRENT_AD;
		OBCPOWERTag.MinCurrent = k_Dcdc_Iref_Ct_u16;
		
		//k_Dcdc_SetpIref_Ct_u16 = L3_Dcdc_Iout_Ct_u16;
		
		#elif defined OUTPUT_FULL_POWER_LIMT
		
		
		uint16 CURRENT_AD = 0xFFFF;
		
		if(CURRENT_AD >= OBCPOWERTag.HWLimtMAXCurrent)
		{
			CURRENT_AD = OBCPOWERTag.HWLimtMAXCurrent;
		}
		
		

		if(OBCTag.ACRMSVolt <= (INPUT_ACVOLT_SET/2) || OBCPOWERTag.CANCmdSETVolt <= DCDC_VOLT_AD_CONVERT(POWER_BMS_LIMT_CURRENT_VOLT_SET) )
		{
			
			OBCPOWERTag.ACPowSetVoltCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT(CURRENT_MAX_LIMT);
		
		}
		else
		{
			OBCPOWERTag.ACPowSetVoltCurrentLimt = (uint16)DCDC_CURRENT_AD_CONVERT((float)POWER_FULL_DEFAULT_SET/ DCDC_AD_CONVERT_VOLT(OBCPOWERTag.CANCmdSETVolt));
		}
		
		

		if(CURRENT_AD >= OBCPOWERTag.ACPowSetVoltCurrentLimt)
		{
			CURRENT_AD = OBCPOWERTag.ACPowSetVoltCurrentLimt;
		}
		
		
		if(CURRENT_AD >= OBCPOWERTag.TEMPStateCurrentLimt)
		{
			CURRENT_AD = OBCPOWERTag.TEMPStateCurrentLimt;
		}

		if(CURRENT_AD >= OBCPOWERTag.CANCmdSETCurrent)
		{
			CURRENT_AD = OBCPOWERTag.CANCmdSETCurrent;
			if(CURRENT_AD == 0)
			{
				goStandBy();
				return;
			}
			
		}

		if(CURRENT_AD < k_Dcdc_MIN_Iref_limt)
		{
			CURRENT_AD = k_Dcdc_MIN_Iref_limt;
		}

		k_Dcdc_Iref_Ct_u16 = CURRENT_AD;
		OBCPOWERTag.MinCurrent = k_Dcdc_Iref_Ct_u16;
		
		#endif
		
	}
	
	
	
}



void StateTimeOut_diag_handle()
{

	if((stSysFSMCtrl.ucCurrentState != STATE_AFTER_RUN) && (stSysFSMCtrl.ucCurrentState != STATE_OPETRATION))
	{
	
		
		if(stSysFSMCtrl.ucCurrentState == diagLastSysState)
		{
			
			if(StateTimeOutCnt >= StateTimeOutTime)
			{
				stSysFSMCtrl.ucCurrentState = STATE_AFTER_RUN;
				FSM_run();
			}
			else
			{
				StateTimeOutCnt ++;
			}
			
		}
		else
		{
			StateTimeOutCnt = 0;
		}
		diagLastSysState = stSysFSMCtrl.ucCurrentState;
		
		
	}

}


void dcdc_start_short_circuit(void)
{
	 uint16_t start_shortTime = 10000;//20000/2，20s报短路故障
	 uint16_t start_shortRecoveryTime = 2500;//5000/2 ,5s恢复
	 static uint16_t start_shortCnt = 0;
	 static uint16_t start_shortRecoverCnt = 0;
	if (stSysFSMCtrl.ucCurrentState == STATE_PRECHARGE2)
	{
		if (L3_Dcdc_Vout_Ct_u16 <= Dcdc_outVoltShortCircuitLim) {
			//
			start_shortCnt++; //开始计数
			start_shortRecoverCnt= 0; //恢复清0
			if (start_shortCnt >= start_shortTime) {
				faultCodeTag.bit.bStartShortCircuit = TRUE;	
			}
		}
	
		 else 
		{
			start_shortRecoverCnt++;
			start_shortCnt = 0;
			if (start_shortRecoverCnt 	>= start_shortRecoveryTime) 
			{
				faultCodeTag.bit.bStartShortCircuit = FALSE;
				start_shortRecoverCnt = 0;
				start_shortCnt = 0;

			}
		}
		
	}
	else 
	{
		start_shortRecoverCnt++;
		start_shortCnt = 0;
		if (start_shortRecoverCnt 	>= start_shortRecoveryTime) 
		{
			faultCodeTag.bit.bStartShortCircuit = FALSE;
			start_shortRecoverCnt = 0;
			start_shortCnt = 0;

		}
	}
	
	
	
	
}



void OCP_hanlde(void)
{
	
	//mPWM_Sub_CD_PWM_Stop();
	//TEST1 = ~TEST1;
	//OUTEN
}