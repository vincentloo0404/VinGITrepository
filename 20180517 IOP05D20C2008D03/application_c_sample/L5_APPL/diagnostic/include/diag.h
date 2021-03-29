/*
 * diag.h
 *
 *  Created on: 2016年4月21日
 *      Author: YCH
 */

#ifndef APP_DIAGNOSTIC_INCLUDE_CHANGE_BOX_DIAG_H_
#define APP_DIAGNOSTIC_INCLUDE_CHANGE_BOX_DIAG_H_

#include "my_all.h"


#define DIAG_THREAD_CYCLE_TIME 2  //10单位都是ms
#define POWER_CNT 52  //上电计数器，目前  POWER_CNT*DIAG_THREAD_CYCLE_TIME*POWER_CNT ms


#define AC_DIAG_Volt_MAX (265)
#define AC_DIAG_Volt_MIN (80)//85


#define DCDC_DIAG_IOUT_MAX (13.5)
#define DCDC_DIAG_IOUT_FULL (12)

#define DIAG_Curr_Input_IoutMax (16)

#define PFC_DIAG_VOUT_MAX (450)
#define PFC_DIAG_VOUT_MIN (380)

//CP_Voltage 状态
typedef struct
{
	uint8_t CP_Voltage_LastVaule;			// 上一状态值
	uint8_t CP_Voltage_CurrentVaule;			// 当前状态值
}CP_Voltage_STATE;

extern CP_Voltage_STATE cp_voltage_state;


#define CP_Voltage_STATE_6V 1
#define CP_Voltage_STATE_9V 2
#define CP_Voltage_STATE_12V 3
#define CP_Voltage_STATE_UNKONW 0





void sys_diag_task(void);
void SysInitDiag(void);
void powerOnDiag(void);
extern void OCP_hanlde(void);



///////////////////// CP  //////////////////////
#define CP_500HZ 8170 
#define CP_CURRENT_0A_LIMT 0 
#define CP_CURRENT_6A_LIMT 6 
#define CP_CURRENT_HW_lINE_10A_LIMT 10
#define CP_CURRENT_HW_lINE_8A_LIMT 8
#define CP_CURRENT_MAX_LIMT 63

#define CURRENT_12A_LIMT 12
#define CURRENT_10A_LIMT 10

#define CURRENT_MAX_LIMT CURRENT_10A_LIMT

#define CP_debunce_offset 20 
#define CP_offset 40  //CP 占空比没有偏差 不需要加 offset 

//小于 8%  不允许充电
//8%~10% IMAX = 6A
//10%~85% IMAX = (D*100)*0.6
//85%~90% IMAX = (D*100-64)*2.5 且 IMAX<= 63
//90%~97% 预留
//>97%  不允许充电
#define CP_D_8 800     
#define CP_D_10 1000
#define CP_D_85 8500
#define CP_D_90 9000
#define CP_D_97 9700

//////////////////////  CP END /////////////////////



///////////////////// 温度 //////////////////////



//#define TEMP_DERATING_BEIGIN  70
//#define TEMP_DERATING_END  77

//#define TEMP_DERATING_BEIGIN  82
//#define TEMP_DERATING_END  82

#define TEMP_DERATING_BEIGIN  85
#define TEMP_DERATING_END  90
#define TEMP_DERATING_CANCLE  (TEMP_DERATING_END-10)
//#define TEMP_DERATING_BEIGIN  70
//#define TEMP_DERATING_END  77


#define TEMP_DBC  90

#define TEMP_PROTECT 110
#define TEMP_PROTECT_CANCLE (TEMP_PROTECT-5)

extern sint16 derating_TEM;
extern sint16 protect_TEM;


/////////////////////温度 END///////////////////////////


//故障结构体
typedef union
{
    struct
    {
    	uint8_t bHWDCDC_OVP			:1;// HWDCDC_OVP
    	uint8_t bOverDCUoutI			:1;// OverUoutI
    	uint8_t bOverUinVolt			:1;// Overvoltage  220v过压
    	uint8_t bUnderUinVolt			:1;// Undervoltage     220v欠压

    	uint8_t bOverDCUoutVolt		:1;//
    	uint8_t bUnderDCUoutVolt		:1;//
    	uint8_t bHWDCDC_OCP			:1;//
    	uint8_t bOverTempCool			:1;

    	uint8_t bloadDump				:1;
    	uint8_t bDriver13VFault		:1;
    	uint8_t bLV12VFault			:1;
    	uint8_t bHWPFC_OVP				:1;
    	
    	
    	uint8_t bHWPFC_OCP				:1;
    	uint8_t bOverPFCUoutVolt		:1;
    	uint8_t bUnderPFCUoutVolt		:1;
    	uint8_t bOverPFCUoutI			:1;
    	
    	uint8_t bTempWarinOutOff		:1;
    	uint8_t bFaultCP				:1;

        uint16_t bReserve:14       		;// Lowbyte
    }bit;
    uint32_t uDWORD;
}FaultCodeTag;


extern FaultCodeTag faultCodeTag;
//#define ALL_FAULT_CODE_FLAG (0xFF80)
//#define ALL_FAULT_CODE_FLAG (0x7F80)
//#define ALL_FAULT_CODE_FLAG (0xFF80)
//1111 1111 1111 1111 1100 0000 00000000
#define ALL_FAULT_CODE_FLAG (0xFFFFC000)

//HW_FAULT |  PFC_DCDC_DOWN_FAULT |  DCDC_FAULT_CODE_FLAG = ALL_FAULT_CODE_FLAG

//1000 0010 0001 1000 00000000 00000000
#define HW_FAULT  (0x82180000)

////0011 0001 0110 0111 10000000
//#define PFC_DCDC_DOWN_FAULT  (0x31678000)
//0011 0001 0110 0111 11000000 00000000
#define PFC_DCDC_DOWN_FAULT  (0x3167C000)

////0100 1100 1000 0000 01000000 00000000
//#define DCDC_FAULT_CODE_FLAG (0x4C040000)
//0100 1100 1000 0000 00000000  00000000   
#define DCDC_FAULT_CODE_FLAG (0x4C804000)


//诊断控制结构体
typedef struct
{

	uint16_t HWDCDC_OVPStateCnt;
	uint16_t OverDCUoutIStateCnt;
	uint16_t OverUinVoltStateCnt;
	uint16_t UnderUinVoltStateCnt;
	uint16_t OverDCUoutVoltStateCnt;
	uint16_t UnderDCUoutVoltStateCnt;
	uint16_t HWDCDC_OCPStateCnt;
	uint16_t OverTempCoolStateCnt;
	uint16_t loadDumpStateCnt;
	uint16_t Driver13VFaultStateCnt;
	uint16_t LV12VFaultStateCnt;
	uint16_t HWPFC_OVPStateCnt;
	uint16_t HWPFC_OCPStateCnt;
	uint16_t OverPFCUoutVoltStateCnt;
	uint16_t UnderPFCUoutVoltStateCnt;
	uint16_t OverPFCUoutIStateCnt;
	
	uint16_t TempDeratingStateCnt;
	uint16_t TempWarinOutOffStateCnt;
	uint16_t OverTempStateCnt;
}StateCntTag;

extern StateCntTag stateCntTag;

typedef struct
{

	uint8_t HWDCDC_OVPStateMaxCnt;
	uint8_t OverDCUoutIStateMaxCnt;
	uint8_t OverUinVoltStateMaxCnt;
	uint8_t UnderUinVoltStateMaxCnt;
	uint8_t OverDCUoutVoltStateMaxCnt;
	uint8_t UnderDCUoutVoltStateMaxCnt;
	uint8_t HWDCDC_OCPStateMaxCnt;
	uint8_t OverTempCoolStateMaxCnt;
	uint8_t loadDumpStateMaxCnt;
	uint8_t Driver13VFaultStateMaxCnt;
	uint8_t LV12VFaultStateMaxCnt;
	uint8_t HWPFC_OVPStateMaxCnt;
	uint8_t HWPFC_OCPStateMaxCnt;
	uint8_t OverPFCUoutVoltStateMaxCnt;
	uint8_t UnderPFCUoutVoltStateMaxCnt;
	uint8_t OverPFCUoutIStateMaxCnt;

	uint8_t TempDeratingStateMaxCnt;
	uint8_t TempWarinOutOffStateMaxCnt;
	uint8_t OverTempStateMaxCnt;
}StateMaxCntTag;


typedef struct
{
	uint32_t HWDCDC_OVPRuntimerCnt;
	uint32_t OverDCUoutIRuntimerCnt;
	uint32_t OverUinVoltRuntimerCnt;
	uint32_t UnderUinVoltRuntimerCnt;
	uint32_t OverDCUoutVoltRuntimerCnt;
	uint32_t UnderDCUoutVoltRuntimerCnt;
	uint32_t HWDCDC_OCPRuntimerCnt;
	uint32_t OverTempCoolRuntimerCnt;
	uint32_t loadDumpRuntimerCnt;
	uint32_t Driver13VFaultRuntimerCnt;
	uint32_t LV12VFaultRuntimerCnt;
	uint32_t HWPFC_OVPRuntimerCnt;
	uint32_t HWPFC_OCPRuntimerCnt;
	uint32_t OverPFCUoutVoltRuntimerCnt;
	uint32_t UnderPFCUoutVoltRuntimerCnt;
	uint32_t OverPFCUoutIRuntimerCnt;
	
	uint32_t TempDeratingRuntimerCnt;
	uint32_t TempWarinOutOffRuntimerCnt;
	uint32_t OverTempRuntimerCnt;
	
}RuntimerCntTag;

typedef struct
{
	uint32_t HWDCDC_OVPRuntimerTime;
	uint32_t OverDCUoutIRuntimerTime;
	uint32_t OverUinVoltRuntimerTime;
	uint32_t UnderUinVoltRuntimerTime;
	uint32_t OverDCUoutVoltRuntimerTime;
	uint32_t UnderDCUoutVoltRuntimerTime;
	uint32_t HWDCDC_OCPRuntimerTime;
	uint32_t OverTempCoolRuntimerTime;
	uint32_t loadDumpRuntimerTime;
	uint32_t Driver13VFaultRuntimerTime;
	uint32_t LV12VFaultRuntimerTime;
	uint32_t HWPFC_OVPRuntimerTime;
	uint32_t HWPFC_OCPRuntimerTime;
	uint32_t OverPFCUoutVoltRuntimerTime;
	uint32_t UnderPFCUoutVoltRuntimerTime;
	uint32_t OverPFCUoutIRuntimerTime;
	
	uint32_t TempDeratingRuntimerTime;
	uint32_t TempWarinOutOffRuntimerTime;
	uint32_t OverTempRuntimerTime;
}RuntimerTag;

//诊断控制结构体
typedef struct
{
	uint16_t HWDCDC_OVPCntr;
	uint16_t OverDCUoutICntr;
	uint16_t OverUinVoltCntr;
	uint16_t UnderUinVoltCntr;
	uint16_t OverDCUoutVoltCntr;
	uint16_t UnderDCUoutVoltCntr;
	uint16_t HWDCDC_OCPCntr;
	uint16_t OverTempCoolCntr;
	uint16_t loadDumpCntr;
	uint16_t Driver13VFaultCntr;
	uint16_t LV12VFaultCntr;
	uint16_t HWPFC_OVPCntr;
	uint16_t HWPFC_OCPCntr;
	uint16_t OverPFCUoutVoltCntr;
	uint16_t UnderPFCUoutVoltCntr;
	uint16_t OverPFCUoutICntr;
	
	uint16_t TempDeratingCntr;
	uint16_t TempWarinOutOffCntr;
	uint16_t OverTempCntr;

}DiagCtrlTag;

//extern DiagCtrlTag diagCtrlTag;


//诊断控制结构体计时器
typedef struct
{
	uint16_t HWDCDC_OVPTime;
	uint16_t OverDCUoutITime;
	uint16_t OverUinVoltTime;
	uint16_t UnderUinVoltTime;
	uint16_t OverDCUoutVoltTime;
	uint16_t UnderDCUoutVoltTime;
	uint16_t HWDCDC_OCPTime;
	uint16_t OverTempCoolTime;
	uint16_t loadDumpTime;
	uint16_t Driver13VFaultTime;
	uint16_t LV12VFaultTime;
	uint16_t HWPFC_OVPTime;
	uint16_t HWPFC_OCPTime;
	uint16_t OverPFCUoutVoltTime;
	uint16_t UnderPFCUoutVoltTime;
	uint16_t OverPFCUoutITime;
	
	uint16_t TempDeratingTime;
	uint16_t TempWarinOutOffTime;
	uint16_t OverTempTime;
	
}DiagTimerTag;

//extern DiagTimerTag diagTimerTag;
typedef struct
{
	uint16_t HWDCDC_OVP_RecoverCntr;
	uint16_t OverDCUoutI_RecoverCntr;
//	uint16_t OverUinVolt_RecoverCntr;
//	uint16_t UnderUinVolt_RecoverCntr;
	uint16_t UinVolt_RecoverCntr;

//	uint16_t OverDCUoutVolt_RecoverCntr;
//	uint16_t UnderDCUoutVolt_RecoverCntr;
	uint16_t DCUoutVolt_RecoverCntr;

	uint16_t HWDCDC_OCP_RecoverCntr;
	uint16_t OverTempCool_RecoverCntr;
	uint16_t loadDump_RecoverCntr;
	uint16_t Driver13VFault_RecoverCntr;
	uint16_t LV12VFault_RecoverCntr;
	uint16_t HWPFC_OVP_RecoverCntr;
	uint16_t HWPFC_OCP_RecoverCntr;
//	uint16_t OverPFCUoutVolt_RecoverCntr;
//	uint16_t UnderPFCUoutVolt_RecoverCntr;
	uint16_t PFCUoutVolt_RecoverCntr;
	uint16_t OverPFCUoutI_RecoverCntr;
	

	uint16_t TempDeratingRecoverCntr;
	uint16_t TempWarinOutOffRecoverCntr;
	uint16_t OverTempRecoverCntr;


}DiagRecoverTag;

//extern DiagRecoverTag diagRecoverTag;

//诊断控制结构体恢复计时器
typedef struct
{
	uint16_t HWDCDC_OVPRecoverTime;
	uint16_t OverDCUoutIRecoverTime;
//	uint16_t OverUinVoltRecoverTime;
//	uint16_t UnderUinVoltRecoverTime;
	uint16_t UinVoltRecoverTime;

//	uint16_t OverDCUoutVoltRecoverTime;
//	uint16_t UnderDCUoutVoltRecoverTime;
	uint16_t DCUoutVoltRecoverTime;

	uint16_t HWDCDC_OCPRecoverTime;
	uint16_t OverTempCoolRecoverTime;
	uint16_t loadDumpRecoverTime;
	uint16_t Driver13VFaultRecoverTime;
	uint16_t LV12VFaultRecoverTime;
	uint16_t HWPFC_OVPRecoverTime;
	uint16_t HWPFC_OCPRecoverTime;
//	uint16_t OverPFCUoutVoltRecoverTime;
//	uint16_t UnderPFCUoutVoltRecoverTime;

	uint16_t PFCUoutVoltRecoverTime;

	uint16_t OverPFCUoutIRecoverTime;
	
	
	uint16_t TempDeratingRecoverTime;
	uint16_t TempWarinOutOffRecoverTime;
	uint16_t OverTempRecoverTime;


}DiagRecoverTimerTag;


typedef struct
{
	uint16_t HWDCDC_OVP_DelayCntr;
	uint16_t OverDCUoutI_DelayCntr;
	uint16_t OverUinVolt_DelayCntr;
	uint16_t UnderUinVolt_DelayCntr;
	uint16_t OverDCUoutVolt_DelayCntr;
	uint16_t UnderDCUoutVolt_DelayCntr;
	uint16_t HWDCDC_OCP_DelayCntr;
	uint16_t OverTempCool_DelayCntr;
	uint16_t loadDump_DelayCntr;
	uint16_t Driver13VFault_DelayCntr;
	uint16_t LV12VFault_DelayCntr;
	uint16_t HWPFC_OVP_DelayCntr;
	uint16_t HWPFC_OCP_DelayCntr;
//	uint16_t OverPFCUoutVolt_DelayCntr;
//	uint16_t UnderPFCUoutVolt_DelayCntr;
	uint16_t PFCUoutVolt_DelayCntr;
	uint16_t OverPFCUoutI_DelayCntr;
	
	uint16_t TempDeratingDelayCntr;
	uint16_t TempWarinOutOffDelayCntr;
	uint16_t OverTempDelayCntr;
}DiagDelayTag;


//诊断控制结构体恢复计时器
typedef struct
{
	uint16_t HWDCDC_OVPDelayTime;
	uint16_t OverDCUoutIDelayTime;
	uint16_t OverUinVoltDelayTime;
	uint16_t UnderUinVoltDelayTime;
	uint16_t OverDCUoutVoltDelayTime;
	uint16_t UnderDCUoutVoltDelayTime;
	uint16_t HWDCDC_OCPDelayTime;
	uint16_t OverTempCoolDelayTime;
	uint16_t loadDumpDelayTime;
	uint16_t Driver13VFaultDelayTime;
	uint16_t LV12VFaultDelayTime;
	uint16_t HWPFC_OVPDelayTime;
	uint16_t HWPFC_OCPDelayTime;
//	uint16_t OverPFCUoutVoltDelayTime;
//	uint16_t UnderPFCUoutVoltDelayTime;
	uint16_t PFCUoutVoltDelayTime;

	uint16_t OverPFCUoutIDelayTime;
	
	uint16_t TempDeratingDelayTime;
	uint16_t TempWarinOutOffDelayTime;
	uint16_t OverTempDelayTime;


}DiagDelayTimerTag;


//诊断控制结构体
typedef struct
{

	uint16_t HWDCDC_OVPInReset;
	uint16_t HWDCDC_OCPInReset;
	uint16_t HWPFC_OVPInReset;
	uint16_t HWPFC_OCPInReset;
}HWInResetTag;

extern HWInResetTag mHWInResetTag;






#endif /* APP_DIAGNOSTIC_INCLUDE_CHANGE_BOX_DIAG_H_ */
