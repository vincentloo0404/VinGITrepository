/*
 * obc_app.h
 *
 *  Created on: 2017��2��14��
 *      Author: YCH
 */

#ifndef APP_CONTROL_INCLUDE_OBC_APP_H_
#define APP_CONTROL_INCLUDE_OBC_APP_H_
#include "my_all.h"




//#define AC_VOLT_AD_CONVERT(volt)   (uint16)(512+(uint32)volt*1.024) //((2.5+(0.005* volt ))*1024/5)
#define AC_VOLT_AD_CONVERT(volt)   (uint16)(512+(sint32)(volt)*1.024) //((2.5+(0.005* volt ))*1024/5)
//#define AC_AD_CONVERT_VOLT(AD)  (sint16)((AD)-512) 
#define AC_AD_CONVERT_VOLT(AD)  (sint16)((AD/1.024)-500) 
//#define AC_AD_CONVERT_VOLT(AD)  (float)(((float)(AD)/1.024)-500) 
#define AC_VOLT_AD_CONVERT_peak(volt)  (uint16)(AC_VOLT_AD_CONVERT((volt)*1.414)) 

#define LinearCompensation 1

#ifdef LinearCompensation
	#define LCPS_FACTOR (1.0452)
	#define LCPS_OFFSET (0.4465)
	

#else
		#define LCPS_FACTOR (1)
		#define LCPS_OFFSET (0)

#endif



#define CC_VOLT_AD_CONVERT(volt) (uint16)((uint32)((float)volt)*1024/5)
#define CC_STATE_D_VALUE (1.20)//1.201413428
#define CC_STATE_D1_VALUE (3.05)//3.056057866
#define CC_VALUE_OFFSET (0.5)


#define CC_STATE_D_VALUE_MIN (143)
#define CC_STATE_D_VALUE_MAX  (348)

#define CC_STATE_D1_VALUE_MIN  (522)
#define CC_STATE_D1_VALUE_MAX  (727)

/*

#define CC_STATE_D_VALUE_MIN CC_VOLT_AD_CONVERT((float)CC_STATE_D_VALUE-CC_VALUE_OFFSET) 
#define CC_STATE_D_VALUE_MAX CC_VOLT_AD_CONVERT((float)CC_STATE_D_VALUE+CC_VALUE_OFFSET) 

#define CC_STATE_D1_VALUE_MIN CC_VOLT_AD_CONVERT((float)CC_STATE_D1_VALUE-CC_VALUE_OFFSET) 
#define CC_STATE_D1_VALUE_MAX CC_VOLT_AD_CONVERT((float)CC_STATE_D1_VALUE+CC_VALUE_OFFSET) 
*/



//#define PFC_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt)*1024*8.3/5000)
//#define PFC_AD_CONVERT_VOLT(AD)  (uint16)((uint32)(AD)*5000/(1024*8.3))

#define PFC_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt)*1024*7.72/5000)
#define PFC_AD_CONVERT_VOLT(AD)  (uint16)((uint32)(AD)*5000/(1024*7.72))
#define PFC_AD_CONVERT_1000double_VOLT(AD)  (uint16)((uint32)(100*AD)*5000/(1024*7.72))

//#define DCDC_VOLT_AD_CONVERT(volt) (uint16)((uint32)volt*1024*9.975/5000)
//#define DCDC_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt)*1024*10.516/5000)
//#define DCDC_AD_CONVERT_VOLT(AD) (uint16)((uint32)(AD)*5000/(1024*10.516))

//#define DCDC_VOLT_OFFSET    (5)
//#define DCDC_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt-DCDC_VOLT_OFFSET)*1024*10.65/5000)
//#define DCDC_AD_CONVERT_VOLT(AD) (uint16)((uint32)(AD)*5000/(1024*10.65))
#define DCDC_VOLT_OFFSET    (0)
#define DCDC_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt-DCDC_VOLT_OFFSET)*1024*10.5115/5000)
#define DCDC_AD_CONVERT_VOLT(AD) (uint16)((uint32)(AD)*5000/(1024*10.5115))
#define DCDC_AD_CONVERT_100doubleVOLT(AD) (uint16)((uint32)(100*AD)*5000/(1024*10.5115))
#define DCDC_CURRENT_AD_CONVERT(Armp) (uint16)(((Armp) + 2.5)*49.152)

//#define DCDC_10double_CURRENT_AD_CONVERT(Armp_10) (uint16)(((Armp_10) + 25)*71.68/10) //��������Ŵ�10�� ����ȡ����
#define DCDC_10double_CURRENT_AD_CONVERT(Armp_10) (uint16)(((Armp_10) + 25)*49.152/10) //��������Ŵ�10�� ����ȡ����
#define DCDC_100double_CURRENT_AD_CONVERT(Armp_100) (uint16)(((uint32)(Armp_100) + 250)*49.152/100) //��������Ŵ�100�� ����ȡ����
#define DCDC_1000double_CURRENT_AD_CONVERT(Armp_1000) (uint16)(((uint32)(Armp_1000) + 2500)*49.152/1000) //��������Ŵ�1000�� ����ȡ����

#define DCDC_AD_CONVERT_CURRENT(AD) (uint16)(((AD) - 122.88)/49.152)
#define DCDC_AD_CONVERT_100doubleCURRENT(AD) (uint16)(((100*AD) - 122.88*100)/49.152)
#define DCDC_AD_CONVERT_1000doubleCURRENT(AD) (uint32)(((1000*AD) - 122.88*1000)/49.152)
//#define DCDC_AD_CONVERT_100doubleCURRENT(AD) (uint16)(((100*AD) - 179.2*100)/49.152)


#define INPUT_IMAX_SET (13)// 13
#define INPUT_ACVOLT_SET (220)// 220
#define POWER_DEFAULT_SET (INPUT_ACVOLT_SET*INPUT_IMAX_SET)// 220*13=2860w

#define POWER_FULL_DEFAULT_SET (3300)// 3300w


#define POWER_BMS_LIMT_CURRENT_VOLT_SET (275)// 
//#define POWER_CURRENT_AD_SET (POWER,VOLT)  DCDC_CURRENT_AD_CONVERT((float)(POWER/(float)VOLT))
#define POWER_CURRENT_AD_SET(POWER,VOLT)  DCDC_CURRENT_AD_CONVERT(POWER/VOLT)

//#define AC_INPUT_CURRENT_AD_CONVERT(Armp) (uint16)(512+(sint32)(Armp)*1.35168)
//#define AC_INPUT_AD_CONVERT_CURRENT(AD) (sint16)((AD/1.35168)-378.7878788)


#define V12_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt)*1024*2.23205506/50)
#define V12_AD_CONVERT_VOLT(AD)  (uint16)((uint32)(AD)*50/(1024*2.23205506))
#define V13_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt)*1024*9.2892201/500)
#define V13_AD_CONVERT_VOLT(AD)  (uint16)((uint32)(AD)*500/(1024*9.2892201))
#define VRelayCoil1_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt)*1024*9.2892201/500)
#define VRelayCoil1_AD_CONVERT_VOLT(AD)  (uint16)((uint32)(AD)*500/(1024*9.2892201))



#define CP_VOLT_AD_CONVERT(volt) (uint16)((uint32)(volt)*1024*36.0126917/500)
#define CP_AD_CONVERT_VOLT(AD)  (uint16)((uint32)(AD)*500/(1024*36.0126917))

//#define CP9V_VOLT_AD_SET_LIMT CP_VOLT_AD_CONVERT(8.2)  7.6
//#define CP9V_VOLT_AD_SET_MAX  CP_VOLT_AD_CONVERT(9.8)  9.2
//#define CP9V_VOLT_AD_SET_LIMT CP_VOLT_AD_CONVERT(7.4)
//#define CP9V_VOLT_AD_SET_MAX  CP_VOLT_AD_CONVERT(9.3)

#define CP9V_VOLT_AD_SET_LIMT CP_VOLT_AD_CONVERT(6.4)
#define CP9V_VOLT_AD_SET_MAX  CP_VOLT_AD_CONVERT(10.3)


//#define CP6V_VOLT_AD_SET_LIMT CP_VOLT_AD_CONVERT(5.2)  
//#define CP6V_VOLT_AD_SET_MAX  CP_VOLT_AD_CONVERT(6.8) 
//#define CP6V_VOLT_AD_SET_LIMT CP_VOLT_AD_CONVERT(4.4) 
//#define CP6V_VOLT_AD_SET_MAX  CP_VOLT_AD_CONVERT(6.3)
#define CP6V_VOLT_AD_SET_LIMT CP_VOLT_AD_CONVERT(3.1)
#define CP6V_VOLT_AD_SET_MAX  CP_VOLT_AD_CONVERT(7.2)
#define CP1V_VOLT_AD_SET_MAX  CP_VOLT_AD_CONVERT(1)

#define DCDC_LOOP_VOLT_AD_SET_LIMT DCDC_VOLT_AD_CONVERT(DCDC_LOOP_VOLT_SET_LIMT)
#define DCDC_LOOP_VOLT_AD_SET_MAX  DCDC_VOLT_AD_CONVERT(DCDC_LOOP_VOLT_SET_MAX)

//can ���� 0.5A���²����
//#define DCDC_LOOP_CAN_CURRENT_SET_LIMT  (0.5)

//can ���� 1A���²����
//#define DCDC_LOOP_CAN_CURRENT_SET_LIMT  (3.2)
#define DCDC_LOOP_CAN_CURRENT_SET_LIMT  (2)
#define DCDC_LOOP_CAN_CURRENT_SET_MAX  (12)

#define DCDC_LOOP_VOLT_SET 370
//#define DCDC_LOOP_CURRENT_SET 6
#define DCDC_LOOP_CURRENT_SET 8
#define DCDC_CURRENT_INIT_UP_SET 3

#define PFC_START_DCDC_SET 390
#define PFC_OFF_DCDC_SET 350

#define PRECHARGE2_BMS_OFFSET  20


#define DCDC_OPEN_LOOP 0
#define DCDC_V_I_LOOP 1
#define DCDC_STOP_LOOP 4
#define DCDC_CONTRL_LOOP DCDC_V_I_LOOP

/*
//ϵͳ״̬
#define STATE_TOTAL_CNT		15	// ϵͳ״̬����
#define STATE_INIT	 		0	// ��ʼ������״̬
#define STATE_STANDBY		2	// STANDBY״̬
#define STATE_PRECHARGE1	3	// Ԥ���״̬1
#define STATE_PFC_RUN		4	// pfc run
#define STATE_PRECHARGE2	5	// Ԥ���״̬2

#define STATE_OPETRATION	6	// ����״̬
#define STATE_CURRENTMODE	6	// ����������״̬
#define STATE_VOLTMODE		8	// ��ѹ������״̬

#define STATE_AFTER_RUN		0xA	// �µ�״̬
#define STATE_SLEEP			0xD	// ˯��״̬
#define STATE_FAILURE		0xC	// ����״̬
#define STATE_PREFAILURE	0xB	// �ɻָ�����״̬

*/

////ϵͳ״̬
//#define STATE_TOTAL_CNT		10	// ϵͳ״̬����
//#define STATE_INIT	 		0	// ��ʼ������״̬
//#define STATE_STANDBY		1	// STANDBY״̬
//#define STATE_PRECHARGE1	2	// Ԥ���״̬1
//#define STATE_PFC_RUN		3	// pfc run
//#define STATE_PRECHARGE2	4	// Ԥ���״̬2
//#define STATE_OPETRATION	5	// ����״̬
//#define STATE_AFTER_RUN		6	// �µ�״̬
//#define STATE_SLEEP			7	// ˯��״̬
//#define STATE_FAILURE		8	// ����״̬
//#define STATE_PREFAILURE	9	// �ɻָ�����״̬




//ϵͳ״̬
#define STATE_TOTAL_CNT		10	// ϵͳ״̬����
#define STATE_INIT	 		0	// ��ʼ������״̬
#define STATE_STANDBY		1	// STANDBY״̬
#define STATE_PRECHARGE1	2	// Ԥ���״̬1
#define STATE_PFC_RUN		3	// pfc run
#define STATE_PRECHARGE2	4	// Ԥ���״̬2
#define STATE_OPETRATION	5	// ����״̬
#define STATE_AFTER_RUN		6	// �µ�״̬
#define STATE_SLEEP			7	// ˯��״̬
#define STATE_FAILURE		8	// ����״̬
#define STATE_PREFAILURE	9	// �ɻָ�����״̬

#define DBC_STATE_INIT 0 //DBC STATE_INIT
#define DBC_STATE_STANDBY	1	// ����������״̬
#define DBC_STATE_PRECHARGE 2 //DBC STATE_PRECHARGE1  STATE_PFC_RUN STATE_PRECHARGE2
#define DBC_STATE_CURRENTMODE	3	// ����������״̬
#define DBC_STATE_VOLTMODE		4	// ��ѹ������״̬
#define DBC_STATE_AFTER_RUN		5	// AFTER_RUN	
#define DBC_STATE_FAILURE		6	// FAILURE	
#define DBC_STATE_PREFAILURE    7	// STATE_PREFAILURE	


//����Դ
#define WAKEUP_INT			0// δ֪����Դ
#define WAKEUP_AC			1// AC����Դ
#define WAKEUP_CP	 		2// CP����Դ
#define WAKEUP_HW_LINE		3// Ӳ��wakeup����
#define WAKEUP_CAN			4// CAN����

#define VEHICLE 1
//#define DurabilityTest 1
//#define LAB_POWER_TEST 1
//#define PCB_TEST 1

#ifdef VEHICLE
	#define USE_AUTO_LIMT (1)
	#define POWEROFF         	TRUE
	#define NEED_SLEEP          1
	#define HAS_INPUT_POWER_LIMT      1
	#define BMS_CAN_ENABLE      1
	#define NEED_DCDCPrechange2   1
	//#define DCDC_UNDER_VOLT_DIAG_SELECT   FALSE//FALSE OR TRUE
	#define DCDC_UNDER_VOLT_DIAG_SELECT   TRUE//FALSE OR TRUE
	#define AC_DIAG_ENABLE      1
	#define DCDC_DIAG_ENABLE    1
	#define PFC_DIAG_ENABLE     1

	#define TEMP_DIAG_ENABLE     1
	#define CC_STATE_DIAG_ENABLE    1
	#define HWDCDC_OCP_DIAG_ENABLE    1
	
	//200~410 10v offset
	//#define DCDC_LOOP_VOLT_SET_LIMT  200
	#define DCDC_LOOP_VOLT_SET_LIMT  250 // �������270V���
//	#define DCDC_LOOP_VOLT_SET_LIMT  100 // debug use 100
	#define DCDC_LOOP_VOLT_SET_MAX   410

	#define DCDC_DIAG_VOUT_MAX (450)
	#define DCDC_DIAG_VOUT_MIN (250)
	#define DCDC_DIAGShortCircuitVOUT_MIN (30)

	
#elif DurabilityTest
	#define POWEROFF         	TRUE
	#define NEED_SLEEP          1
	//#define HAS_INPUT_POWER_LIMT      1
	#define BMS_CAN_ENABLE      1
	#define NEED_DCDCPrechange2   1
	#define DCDC_UNDER_VOLT_DIAG_SELECT   FALSE//FALSE OR TRUE
	//#define DCDC_UNDER_VOLT_DIAG_SELECT   TRUE//FALSE OR TRUE
	#define AC_DIAG_ENABLE      1
	#define DCDC_DIAG_ENABLE    1
	#define PFC_DIAG_ENABLE     1
	#define TEMP_DIAG_ENABLE     1
	
	#define HWDCDC_OCP_DIAG_ENABLE    1	
	
	#define OUTPUT_FULL_POWER_LIMT      1
	
	#define DCDC_LOOP_VOLT_SET_LIMT  100
	#define DCDC_LOOP_VOLT_SET_MAX   410
	
	
	#define DCDC_DIAG_VOUT_MAX (450)
	#define DCDC_DIAG_VOUT_MIN (250)
	
#elif LAB_POWER_TEST
	#define POWEROFF         	TRUE
	//#define NEED_SLEEP          1
	//#define HAS_INPUT_POWER_LIMT      1
	//#define BMS_CAN_ENABLE      1
	//#define NEED_DCDCPrechange2   1
	#define DCDC_UNDER_VOLT_DIAG_SELECT   FALSE//FALSE OR TRUE
	//#define DCDC_UNDER_VOLT_DIAG_SELECT   TRUE//FALSE OR TRUE
	//#define AC_DIAG_ENABLE      1
	#define DCDC_DIAG_ENABLE    1
	#define PFC_DIAG_ENABLE     1
	#define TEMP_DIAG_ENABLE     1
	
	#define HWDCDC_OCP_DIAG_ENABLE    1
#elif PCB_TEST
	#define POWEROFF         	TRUE
	//#define NEED_SLEEP          1
	//#define HAS_INPUT_POWER_LIMT      1
	//#define BMS_CAN_ENABLE      1
	//#define NEED_DCDCPrechange2   1
	#define DCDC_UNDER_VOLT_DIAG_SELECT   FALSE//FALSE OR TRUE
	//#define DCDC_UNDER_VOLT_DIAG_SELECT   TRUE//FALSE OR TRUE
	//#define AC_DIAG_ENABLE      1
	//#define DCDC_DIAG_ENABLE    1
	//#define PFC_DIAG_ENABLE     1
	//#define TEMP_DIAG_ENABLE     1
	
	//#define HWDCDC_OCP_DIAG_ENABLE   1

#endif


//limt current param
#define MAX_POWER_INIT (0xFFFF)
#define MAX_CURRENT_INIT (0xFFFF)
#define NO_CC_CP_LIMT (CP_CURRENT_HW_lINE_8A_LIMT)
#define MAX_HW_INIT (0xFFFF)

#define POWER_FACTOR (0.95)



#define ACS724 1
//#define ACS712 1

#ifdef ACS724
	//#define AC_CURRENT_AD_CONVERT(Armp)  (uint16)(512+(sint32)(Armp)*27.2384)
	//#define AC_AD_CONVERT_CURRENT(AD)  (float)(((float)(AD)/27.2384)-18.797) 
	#define AC_CURRENT_AD_CONVERT(Armp)  (uint16)(102.4+(sint32)(Armp)*27.2384)
	#define AC_AD_CONVERT_CURRENT(AD)  (float)(((float)(AD)/27.2384)-3.759) 
#elif ACS712
	#define AC_CURRENT_AD_CONVERT(Armp)  (uint16)(uint16)(512+(sint32)(Armp)*13.5168)
	#define AC_AD_CONVERT_CURRENT(AD)  (float)(((float)(AD)/13.5168)-37.879) 
#endif




extern uint8_t opetrationDelayOver;
extern uint8_t CONNECT_BMS_OK;
extern uint8_t BMS_CHARGE_OVER;
extern uint8_t wakeupSignal;

extern uint16_t AC_Volt_fast_limtLow_Ct_u16;
extern uint16_t AC_Volt_fast_maxHigh_Ct_u16;
extern uint16_t AC_Volt_fast_OpenVolt_Ct_u16;
extern uint16_t ACVolt_pfcVolt_err_Ct_u16;
extern volatile uint16 L5_AC_Volt_fast_max_buff;
extern volatile  uint16 L5_AC_Volt_fast_maxBuffCPS;
extern volatile uint16 L5_AC_current_max_buff;

extern volatile uint16 k_Dcdc_MIN_Iref_limt;

extern volatile uint16 k_Dcdc_MAX_Iref_limt;


#define APP_STATEFLOW_THREAD_CYCLE_TIME 2  //2ms

#define O_GLB_RSET_DELAYToHightTIME (6/APP_STATEFLOW_THREAD_CYCLE_TIME)   //6ms
#define O_GLB_RSET_DELAYToLowTIME (10/APP_STATEFLOW_THREAD_CYCLE_TIME)   //10ms
extern void (*pFSMAct[STATE_TOTAL_CNT])(void);  // ϵͳ״̬��ִ�к����ӿ�

//ϵͳ״̬��
typedef struct {
	uint8_t ucStateUnkonw;		// ״̬��ʼ����־
	uint8_t ucLastSysState;			// ��һ ϵͳ״̬ ������ ucCurrentState ��ͬ��init״̬����
	uint8_t ucLastState;			// ��һ״̬ ���� ucCurrentState ��ͬ
	uint8_t ucCurrentState;			// ��ǰ״̬
} SysFSMCtrlTag;

extern SysFSMCtrlTag stSysFSMCtrl;


//���Ʋ���
typedef struct
{
	uint8_t	 ucSysInitFinish;			// ϵͳ��ʼ����� 0:δ��� 1:���
	uint8_t	 ucLastPlugIn;			// PlugIn�ź�

}CtrlParaTag;

extern CtrlParaTag ctrlParaTag;




//��Ͽ��ƽṹ��
typedef struct
{
	uint16_t INITStateCntr;
	uint16_t STANDBYCntr;
	uint16_t PRECHARGE1Cntr;
	uint16_t PFC_RUNCntr;
	uint16_t PRECHARGE2Cntr;
	uint16_t OPETRATIONCntr;
	uint16_t AFTER_RUNCntr;
	uint16_t SLEEPCntr;
	uint16_t FAILURECntr;
	uint16_t PREFAILURECntr;


}StateCntrTag;

//״̬�ṹ���ʱ��
typedef struct
{
	uint16_t INITTime;
	uint16_t STANDBYTime;
	uint16_t PRECHARGE1Time;
	uint16_t PFC_RUNTime;
	uint16_t PRECHARGE2Time;
	uint16_t OPETRATIONTime;
	uint16_t AFTER_RUNTime;
	uint16_t SLEEPTime;
	uint16_t FAILURETime;
	uint16_t PREFAILURETime;
}StateTimerTag;

extern StateCntrTag mStateCntrTag;
extern StateTimerTag mStateTimerTag;
//
typedef struct
{
	uint16_t ACVoltCntr;
	uint16_t acVolt_pfcVol_errCntr;
	uint16_t pfcEnAtACzeroStateDelayCntr;
	uint16_t dcdcRelayCloseDelayCntr;
	uint8_t afterRunPFC_enCntr;
	uint8_t afterRunACRelayDelayCntr;
	uint32_t afterRunGlbEnCntr;
	
	uint16_t pre_changer2PGResetCntr;
	uint32_t pre_changer2PGKeepCntr;

}VARCntrTag;

//״̬�ṹ���ʱ��
typedef struct
{
	uint16_t ACVoltTime;
	uint16_t acVolt_pfcVol_errTime;
	uint16_t pfcEnAtACzeroStateDelayTime;
	uint16_t dcdcRelayCloseDelayTime;
	
	uint16_t afterRunPFC_enTime;
	uint16_t afterRunACRelayDelayTime;
	
	uint32_t afterRunGlbEnTime;
	uint16_t pre_changer2PGResetTime;
	uint32_t pre_changer2PGKeepTime;
	

}VARTimerTag;

extern VARCntrTag mVARCntrTag;
extern VARTimerTag mVARTimerTag;


typedef struct
{
	uint8		CCState;
	uint8		EnCharger;
	uint8		ACChrRlySt;
	uint16		ChrTimeRemain;
	uint16		ChrCurrentSp;
	uint16		ChrVoltSp;
	uint16		actVoltage;
	uint16		actVoltageADRow;
	uint8		PosRlySt;
}BMSTAG;
extern BMSTAG BMSTag;

typedef struct
{
	uint8		bFaultCable;
	uint8		PowerLimit;
	uint8		ReqCloseRly;
	uint8		bWakeUp;
	uint8		bFaultDC;
	uint8		bFaultAC;
	uint8		bFaultHW;
	uint8		bOverTempCool;
	uint8		bErrorCOM;
	uint8		FaultID;
	uint8		ChrTemp;
	uint8		ChrOpMode;
	uint16		actChrVolt;
	uint16		actChrCurrent;
	sint16		chrFB_TEM;
	sint16		chrPCB_TEM;
	uint16		ACRMSVolt;
	uint8		bFilterCCState;
	uint8		bFilterCPState;
	uint8		bFilterCPVoltState;
	uint8		bFilterCPDutyState;
	uint8		bFilterCPFrqState;
	uint8		bFilterWorkCMD;
	uint16		PFCVolt;
}OBCTAG;
extern OBCTAG OBCTag;

#define CP_NORMAL  (0)
#define CP_FRQ_LOW (1)
#define CP_FRQ_HIGH (2)
#define CP_DUTY_LOW (3)
#define CP_DUTY_HIGH (4)
#define CP_VOLT_LOW (5)
#define CP_VOLT_HIGH (6)
#define CP_NULL (7)

typedef struct
{
	uint16		ACInputPowLimt; // ���빦������ Ĭ�� 3300w
	uint16		ACPowMaxCurrentLimt;//AC ����������������CC CP����
	uint16		ACPowSetVoltCurrentLimt;//�޹��ʺ������������������޹��ʣ�����DCDC���3.3KW�����������������
	
	uint16		TEMPStateCurrentLimt;
	uint16		CCStateCurrentLimt;
	uint16		CPStateCurrentLimt;
	uint16		CANCmdSETVolt;
	uint16		CANCmdSETCurrent;	
	uint16		HWLimtMAXCurrent;//OBC Ӳ����·��������ƣ�3.3kw�����12A��6.6KW����
	
	uint16		MinCurrent;	
}OBCPOWERTAG;
extern OBCPOWERTAG OBCPOWERTag;//��С��Ϊobc�������


extern uint8 bms_can_available;
extern volatile uint8 L5_OBC_model1_enable;
extern volatile uint16 L3_Dcdc_Vout_Precharge2;
extern volatile uint16 L3_Dcdc_Vout_Precharge2High;
extern volatile uint16 L3_Dcdc_Vout_Precharge2Low;
extern volatile uint8 startOver;
extern volatile uint16 L3_last_OBC_Y_Ct_u16;
extern volatile uint16 PowerLimSet;
extern  uint16 L3_PRECHARGE2_BMS_MIN;
extern  uint16 L3_PRECHARGE2_BMS_MAX;
extern  uint8 L5_precharge2_CMD_FLAG; 

extern uint8 HW_O_PFC_EN;
extern uint8 HW_O_MCU_FAT;
extern uint8 HW_O_GLB_RSET;
extern uint8 HW_O_S_RlyCTL1;
extern uint8 HW_PG_SENSE;
extern uint8 HW_O_PG;
extern uint8 HW_S2_CTR;
extern uint8 HW_I_GLB_EN;


void systemStart(void);
void systemShutdown(void);
void FSM_init(void);
void in_INIT(void);
void in_STANDBY(void);
void in_PRECHARGE1(void);
void in_PFC_RUN(void);
void in_PRECHARGE2(void);
void in_OPETRATION(void);
void in_AFTER_RUN(void);
void in_SLEEP(void);
void in_FAILURE(void);
void in_PREFAILURE(void);
void app_stateflow_task(void);
void setResetIOLow(void);
void powerDown(void);
void goStandBy(void);
void goPREFAILURE(void);
BOOL glbDiag(uint8_t ucStateRecd);
extern void startDcdc(void);
extern void stopDcdc(void);
extern void startAllPwm(void);
extern void stopAllPwm(void);

#endif /* APP_CONTROL_INCLUDE_OBC_APP_H_ */
