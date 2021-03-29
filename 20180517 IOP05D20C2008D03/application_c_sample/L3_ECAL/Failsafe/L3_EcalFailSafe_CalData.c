
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "L3_EcalFailSafe_CalData.h"
#include "L3_EcalFailSafe_Cfg.h"

#if 0
#include "L3_Ecu_Diag_Cfg.h"
#include "L3_BattVolt_Diag_Cfg.h"
#include "L3_SensorVolt_Diag_Cfg.h"
#include "L3_StrAngleSensor_Diag_Cfg.h"
#include "L3_EngineStatus_Diag_Cfg.h"
#include "L3_VehicleSpeed_Diag_Cfg.h"
#include "L3_PreCharge_Diag_Cfg.h"
#include "L3_PowRelay_Diag_Cfg.h"
#include "L3_PreDriver_Diag_Cfg.h"
#include "L3_Temperature_Diag_Cfg.h"
#include "L3_HBridge_Diag_Cfg.h"
#include "L3_MotorPos_Diag_Cfg.h"
#include "L3_MotorVolt_Diag_Cfg.h"
#include "L3_MotorCurr_Diag_Cfg.h"
#endif

/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/
/* L3��Failsafe�궨��������RAM��ʼ��ַ */
//#define d_L3FSCALIBDATA_RAMSTARTADDR_u16        0xB100U

/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3ECALFAILSAFECALDATA_START_SEC_CALIB_VAR
#include "MemMap.h"

#if 0
#pragma push /* Save the current state */
#pragma section data_type ".abs.40010000" ".abs.40010000"
__declspec (section ".abs.40010000") static CAB_PARAM_T __cab_param_ram;
#pragma pop
#endif

/**********************************************************
 *  ���ڡ�L3_PreDriver_Diag.c���ı궨����
 **********************************************************/
/* Ԥ����Ϲ���ʹ�� */
#if 0
#pragma push /* Save the current state */
#pragma section data_type ".abs.40000000" ".abs.40000000"
__declspec (section ".abs.40000000") uint8 k_S_EnPreDrvDiag_Uls_u8;
#pragma pop


//uint8 k_S_PreDrvUnderVoltCntIncStep_Ct_u8;
uint8 k_S_PreDrvUnderVoltCntDecStep_Ct_u8;
uint16 k_S_PreDrvUnderVoltConfirmCntTh_Ct_u16;


#pragma push /* Save the current state */
#pragma section all_types ".abs.40000002" ".abs.40000002"
/* Ԥ��Ƿѹ���ϼ��������ӵĲ��� */
__declspec (section ".abs.40000002") uint8 k_S_PreDrvUnderVoltCntIncStep_Ct_u8;
#pragma pop


#pragma push /* Save the current state */
#pragma section data_type ".abs.40000002" ".abs.40000002"
/* Ԥ��Ƿѹ���ϼ�������С�Ĳ��� */
__declspec (section ".abs.40000002") uint8 k_S_PreDrvUnderVoltCntDecStep_Ct_u8;
#pragma pop

#pragma push /* Save the current state */
#pragma section data_type ".abs.40000004" ".abs.40000004"
/* Ԥ��Ƿѹ����ȷ�ϵļ������� 25ms */
__declspec (section ".abs.40000004") uint16 k_S_PreDrvUnderVoltConfirmCntTh_Ct_u16;
#pragma pop
#endif

#if 0
uint8 k_S_EnPreDrvDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 174) = 255U;

/* Ԥ��Ƿѹ���ϼ��������ӵĲ��� */
uint8 k_S_PreDrvUnderVoltCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 175) = 1U;
/* Ԥ��Ƿѹ���ϼ�������С�Ĳ��� */
uint8 k_S_PreDrvUnderVoltCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 176) = 5U;
/* Ԥ��Ƿѹ����ȷ�ϵļ������� 25ms */
uint16 k_S_PreDrvUnderVoltConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 178) \
		= (uint16)(2500 / d_PREDRIVERDIAG_TASKPERIOD_u16);

/* Ԥ����·���ϼ��������ӵĲ��� */
uint8 k_S_PreDrvShortCircuitCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 180) = 1U;
/* Ԥ����·���ϼ�������С�Ĳ��� */
uint8 k_S_PreDrvShortCircuitCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 181) = 5U;
/* Ԥ����·����ȷ�ϵļ������� 25ms */
uint16 k_S_PreDrvShortCircuitConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 182) \
		= (uint16)(2500 / d_PREDRIVERDIAG_TASKPERIOD_u16);

/* Ԥ����ѹ����ȹ��ϼ��������ӵĲ��� */
uint8 k_S_PreDrvOverVoltTempCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 184) = 1U;
/* Ԥ����ѹ����ȹ��ϼ�������С�Ĳ��� */
uint8 k_S_PreDrvOverVoltTempCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 185) = 5U;
/* Ԥ����ѹ����ȹ���ȷ�ϵļ�������25ms */
uint16 k_S_PreDrvOverVoltTempConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 186) \
		= (uint16)(2500 / d_PREDRIVERDIAG_TASKPERIOD_u16);

#endif
#if 0

/**********************************************************
 *  ���ڡ�L3_Ecu_Diag.c���ı궨����
 **********************************************************/
/* ALU������Ϲ���ʹ�� */
uint8 k_S_EnALUCalcDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16) = 255U;

/* ALU���������ϼ��������ӵĲ���  */
uint8 k_S_ALUCalcErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 1) = 1U;
/* ALU���������ϼ�������С�Ĳ���  */
uint8 k_S_ALUCalcErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 2) = 5U;
/* ALU����������ȷ�ϵļ�������50ms */
uint16 k_S_ALUCalcErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 4) \
		= (uint16)(5000 / d_ECUDIAG_TASKPERIOD_u16);

/* ADC������Ϲ���ʹ�� */
uint8 k_S_EnADCSampDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 6) = 255U;

/* ADC������ʱ���ϼ��������ӵĲ���  */
uint8 k_S_ADCTimeoutCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 7) = 1U;
/* ADC������ʱ���ϼ�������С�Ĳ���  */
uint8 k_S_ADCTimeoutCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 8) = 5U;
/* ADC������ʱ����ȷ�ϵļ�������50ms */
uint16 k_S_ADCTimeoutConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 10) \
		= (uint16)(5000 / d_ECUDIAG_TASKPERIOD_u16);

/* Taskִ����Ϲ���ʹ�� */
uint8 k_S_EnTaskLoopDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 12) = 255U;

/* Taskִ�г�ʱ���ϼ��������ӵĲ���  */
uint8 k_S_TaskTimeoutCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 13) = 1U;
/* Taskִ�г�ʱ���ϼ�������С�Ĳ���  */
uint8 k_S_TaskTimeoutCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 14) = 5U;
/* Taskִ�г�ʱ����ȷ�ϵļ�������25ms */
uint16 k_S_TaskTimeoutConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 16) \
		= (uint16)(2500 / d_ECUDIAG_TASKPERIOD_u16);

/* U0C1ͨ����Ϲ���ʹ�� */
uint8 k_S_EnU0C1CommDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 18) = 255U;

/* U0C1ͨ�Ź��ϼ��������ӵĲ���  */
uint8 k_S_U0C1CommErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 19) = 1U;
/* U0C1ͨ�Ź��ϼ�������С�Ĳ���  */
uint8 k_S_U0C1CommErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 20) = 5U;
/* U0C1ͨ�Ź���ȷ�ϵļ�������50ms */
uint16 k_S_U0C1CommErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 22) \
		= (uint16)(5000 / d_ECUDIAG_TASKPERIOD_u16);

/* U1C0ͨ����Ϲ���ʹ�� */
uint8 k_S_EnU1C0CommDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 24) = 255U;

/* U1C0ͨ�Ź��ϼ��������ӵĲ���  */
uint8 k_S_U1C0CommErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 25) = 1U;
/* U1C0ͨ�Ź��ϼ�������С�Ĳ���  */
uint8 k_S_U1C0CommErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 26) = 5U;
/* U1C0ͨ�Ź���ȷ�ϵļ�������150ms */
uint16 k_S_U1C0CommErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 28) \
		= (uint16)(15000 / d_ECUDIAG_TASKPERIOD_u16);

/* Monitor������Ϲ���ʹ�� */
uint8 k_S_EnMonitorOptDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 30) = 255U;

/* Monitor�������ϼ��������ӵĲ���  */
uint8 k_S_MonitorOptErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 31) = 1U;
/* Monitor�������ϼ�������С�Ĳ���  */
uint8 k_S_MonitorOptErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 32) = 5U;
/* Monitor��������ȷ�ϵļ�������50ms */
uint16 k_S_MonitorOptErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 34) \
		= (uint16)(5000 / d_ECUDIAG_TASKPERIOD_u16);

/* EEPROM������Ϲ���ʹ�� */
uint8 k_S_EnEEPROMOptDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 36) = 255U;

/* EEPROM�������ϼ��������ӵĲ���  */
uint8 k_S_EEPROMOptErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 37) = 1U;
/* EEPROM�������ϼ�������С�Ĳ���  */
uint8 k_S_EEPROMOptErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 38) = 5U;
/* EEPROM��������ȷ�ϵļ�������150ms */
uint16 k_S_EEPROMOptErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 40) \
		= (uint16)(15000 / d_ECUDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_BattVolt_Diag.c���ı궨����
 **********************************************************/
/* ��ص�ѹ����״̬������˳��ĵ�ѹ��ֵ */
uint16 k_S_BatOffStateEnterLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 42) = 1664U;  	/* 6.5V */
uint16 k_S_BatOffStateExitLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 44) = 1792U;   	/* 7.0V */

/* ��ص�ѹǷѹ״̬������˳��ĵ�ѹ��ֵ */
uint16 k_S_BatLowStateEnterLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 46) = 2304U;  	/* 9.0V */
uint16 k_S_BatLowStateExitLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 48) = 2432U;   	/* 9.5V */

/* ��ص�ѹ����1״̬������˳��ĵ�ѹ��ֵ */
uint16 k_S_BatNormal1StateEnterLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 50) = 2560U;  	/* 10.0V */
uint16 k_S_BatNormal1StateExitLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 52) = 2688U;   	/* 10.5V */

/* ��ص�ѹ��ѹ1״̬������˳��ĵ�ѹ��ֵ */
uint16 k_S_BatOver1StateEnterLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 54) = 4096U;	/* 16.0V */
uint16 k_S_BatOver1StateExitLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 56) = 3968U;   	/* 15.5V */

/* ��ص�ѹ��ѹ2״̬������˳��ĵ�ѹ��ֵ */
uint16 k_S_BatOver2StateEnterLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 58) = 4608U;	/* 18.0V */
uint16 k_S_BatOver2StateExitLimit_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 60) = 4480U;   	/* 17.5V */

/* ��ص�ѹ���ϼ��������ӵĲ��� */
uint8 k_S_BatErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 62) = 1U;
/* ��ص�ѹ���ϼ�������С�Ĳ��� */
uint8 k_S_BatErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 63) = 5U;

/* ��ص�ѹ�������ȷ��50ms������ļ�������500ms */
uint16 k_S_BatOffConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 64) \
		= (uint16)(5000 / d_BATTVOLTDIAG_TASKPERIOD_u16);
uint16 k_S_BatOffClearCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 66) \
		= (uint16)(50000 / d_BATTVOLTDIAG_TASKPERIOD_u16);

/* ��ص�ѹǷѹ����ȷ��1000ms������ļ�������500ms */
uint16 k_S_BatLowConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 68) \
		= (uint16)(100000 / d_BATTVOLTDIAG_TASKPERIOD_u16);
uint16 k_S_BatLowClearCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 70) \
		= (uint16)(50000 / d_BATTVOLTDIAG_TASKPERIOD_u16);

/* ��ص�ѹ����1����ȷ��500ms������ļ�������500ms */
uint16 k_S_BatNormal1ConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 72) \
		= (uint16)(50000 / d_BATTVOLTDIAG_TASKPERIOD_u16);
uint16 k_S_BatNormal1ClearCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 74) \
		= (uint16)(50000 / d_BATTVOLTDIAG_TASKPERIOD_u16);

/* ��ص�ѹ��ѹ1����ȷ��500ms������ļ�������1000ms */
uint16 k_S_BatOver1ConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 76) \
		= (uint16)(50000 / d_BATTVOLTDIAG_TASKPERIOD_u16);
uint16 k_S_BatOver1ClearCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 78) \
		= (uint16)(100000 / d_BATTVOLTDIAG_TASKPERIOD_u16);

/* ��ص�ѹ��ѹ2����ȷ��300ms������ļ�������1000ms */
uint16 k_S_BatOver2ConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 80) \
		= (uint16)(30000 / d_BATTVOLTDIAG_TASKPERIOD_u16);
uint16 k_S_BatOver2ClearCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 82) \
		= (uint16)(100000 / d_BATTVOLTDIAG_TASKPERIOD_u16);

/* ��ص�ѹ��Ϲ���ʹ�� */
uint8 k_S_EnBatVoltDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 84) = 255U;

/**********************************************************
 *  ���ڡ�L3_SensorVolt_Diag.c���ı궨����
 **********************************************************/
/* �����������ѹ��Ϲ���ʹ�� */
uint8 k_S_EnSenVoltDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 85) = 255U;

/* �����������ѹǷѹ��ֵ */
uint16 k_S_SenVoltLowTh_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 86) = 1152U;		/* 4.5V */
/* �����������ѹ��ѹ��ֵ */
uint16 k_S_SenVoltHighTh_V_u16p08 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 88) = 1408U;     	/* 5.5V */

/* �����������ѹǷѹ���ϼ��������ӵĲ���  */
uint8 k_S_SenVoltLowCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 90) = 1U;
/* �����������ѹǷѹ���ϼ�������С�Ĳ���  */
uint8 k_S_SenVoltLowCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 91) = 5U;
/* �����������ѹǷѹ����ȷ�ϵļ�������50ms */
uint16 k_S_SenVoltLowConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 92) \
		= (uint16)(5000 / d_SENSORVOLTDIAG_TASKPERIOD_u16);

/* �����������ѹ��ѹ���ϼ��������ӵĲ��� */
uint8 k_S_SenVoltHighCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 94) = 1U;
/* �����������ѹ��ѹ���ϼ�������С�Ĳ��� */
uint8 k_S_SenVoltHighCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 95) = 5U;
/* �����������ѹ��ѹ����ȷ�ϵļ�������50ms */
uint16 k_S_SenVoltHighConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 96) \
		= (uint16)(5000 / d_SENSORVOLTDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_StrAngleSensor_Diag.c���ı궨����
 **********************************************************/
/* ������ת����Ϲ���ʹ�� */
uint8 k_S_EnSASDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 98) = 0;//255U;

/* ������ת��CAN��Ϣ��ʼ���ȴ��ļ�������150ms */
uint16 k_S_SASMsgInitDelayCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 100) \
		= (uint16)(15000 / d_SASDIAG_TASKPERIOD_u16);

/* ������ת���ź���Ч���ϼ��������ӵĲ��� */
uint8 k_S_StrAngInvalidCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 102) = 1U;
/* ������ת���ź���Ч���ϼ�������С�Ĳ��� */
uint8 k_S_StrAngInvalidCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 103) = 5U;
/* ������ת���ź���Ч����ȷ�ϵļ�������100ms */
uint16 k_S_StrAngInvalidConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 104) \
		= (uint16)(10000 / d_SASDIAG_TASKPERIOD_u16);

/* ������ת���źŶ�ʧ���ϼ��������ӵĲ��� */
uint8 k_S_StrAngLostCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 106) = 1U;
/* ������ת���źŶ�ʧ���ϼ�������С�Ĳ��� */
uint8 k_S_StrAngLostCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 107) = 5U;
/* ������ת���źŶ�ʧ����ȷ�ϵļ�������600ms */
uint16 k_S_StrAngLostConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 108) \
		= (uint16)(60000 / d_SASDIAG_TASKPERIOD_u16);

/* ������ת���ź���Ч���ϼ��������ӵĲ��� */
uint8 k_S_StrAngSpdInvalidCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 110) = 1U;
/* ������ת���ź���Ч���ϼ�������С�Ĳ��� */
uint8 k_S_StrAngSpdInvalidCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 111) = 5U;
/* ������ת���ź���Ч����ȷ�ϵļ�������100ms */
uint16 k_S_StrAngSpdInvalidConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 112) \
		= (uint16)(10000 / d_SASDIAG_TASKPERIOD_u16);

/* ������ת���źŶ�ʧ���ϼ��������ӵĲ��� */
uint8 k_S_StrAngSpdLostCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 114) = 1U;
/* ������ת���źŶ�ʧ���ϼ�������С�Ĳ��� */
uint8 k_S_StrAngSpdLostCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 115) = 5U;
/* ������ת���źŶ�ʧ����ȷ�ϵļ�������600ms */
uint16 k_S_StrAngSpdLostConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 116) \
		= (uint16)(60000 / d_SASDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_EngineStatus_Diag.c���ı궨����
 **********************************************************/
/* ������״̬��Ϲ���ʹ�� */
uint8 k_S_EnEngStsDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 118) = 255U;

/* ������״̬��Ч���ϼ��������ӵĲ��� */
uint8 k_S_EngStsInvalidCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 119) = 1U;
/* ������״̬��Ч���ϼ�������С�Ĳ��� */
uint8 k_S_EngStsInvalidCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 120) = 5U;
/* ������״̬��Ч����ȷ�ϵļ�������600ms */
uint16 k_S_EngStsInvalidConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 122) \
		= (uint16)(60000 / d_ENGSPEEDDIAG_TASKPERIOD_u16);

/* ������״̬��ʧ���ϼ��������ӵĲ��� */
uint8 k_S_EngStsLostCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 124) = 1U;
/* ������״̬��ʧ���ϼ�������С�Ĳ��� */
uint8 k_S_EngStsLostCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 125) = 5U;
/* ������״̬��ʧ����ȷ�ϵļ�������600ms */
uint16 k_S_EngStsLostConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 126) \
		= (uint16)(60000 / d_ENGSPEEDDIAG_TASKPERIOD_u16);

/* ������״̬CAN��Ϣ��ʼ���ȴ��ļ�������200ms */
uint16 k_S_EngStsMsgInitDelayCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 128) \
		= (uint16)(20000 / d_ENGSPEEDDIAG_TASKPERIOD_u16);

/* ������״̬ȷ�ϵļ�������400ms */
uint16 k_S_EngStsRunConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 130) \
		= (uint16)(40000 / d_ENGSPEEDDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_VehicleSpeed_Diag.c���ı궨����
 **********************************************************/
/* �����ź���Ϲ���ʹ�� */
uint8 k_S_EnVehSpdDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 132) = 255U;

/* �����ź���Ч���ϼ��������ӵĲ��� */
uint8 k_S_VehSpdInvalidCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 133) = 1U;
/* �����ź���Ч���ϼ�������С�Ĳ��� */
uint8 k_S_VehSpdInvalidCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 134) = 5U;
/* �����ź���Ч����ȷ�ϵļ�������300ms */
uint16 k_S_VehSpdInvalidConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 136) \
		= (uint16)(30000 / d_VEHSPEEDDIAG_TASKPERIOD_u16);

/* �����źŶ�ʧ���ϼ��������ӵĲ��� */
uint8 k_S_VehSpdLostCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 138) = 1U;
/* �����źŶ�ʧ���ϼ�������С�Ĳ��� */
uint8 k_S_VehSpdLostCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 139) = 5U;
/* �����źŶ�ʧ����ȷ�ϵļ�������300ms */
uint16 k_S_VehSpdLostConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 140) \
		= (uint16)(30000 / d_VEHSPEEDDIAG_TASKPERIOD_u16);

/* �����ź�CAN��Ϣ��ʼ���ȴ��ļ�������150ms */
uint16 k_S_VehSpdMsgInitDelayCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 142) \
		= (uint16)(15000 / d_VEHSPEEDDIAG_TASKPERIOD_u16);

/* ����Ĭ��ֵ */
uint16 k_S_VehSpdDefaultValue_Kph_u16p01 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 144) = 120U;

uint16 k_S_VehSpdTranStepValue_Kph_u16p01 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 146) = 6U;

/* ����һ�׵�ͨ�˲����Ĳ���
 * 0.5Hz:  16281, 51
 * 1.0Hz:  16179, 102
 * 5.0Hz:  15386, 500
 * 10.0Hz: 14447, 968
 * 30.0Hz: 11187, 2599 */
uint16 k_N_VehSpdFltDen_Uls_u16p14 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 148) = 11187U;
uint16 k_N_VehSpdFltNum_Uls_u16p14 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 150) = 2599U;

/**********************************************************
 *  ���ڡ�L3_PreCharge_Diag.c���ı궨����
 **********************************************************/
/* Ԥ�����Ϲ���ʹ�� */
uint8 k_S_EnPreChargeDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 152) = 255U;

/* Ԥ��絼ͨѹ�������� */
uint16 k_S_PreChargeOnMaxTh_Vt_u16p11 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 154) = 5120U;	/* 2.5V */

/* Ԥ��絼ͨ���ϼ��������ӵĲ��� */
uint8 k_S_PreChargeOnErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 156) = 1U;
/* Ԥ��絼ͨ���ϼ�������С�Ĳ��� */
uint8 k_S_PreChargeOnErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 157) = 5U;
/* Ԥ��絼ͨ����ȷ�ϵļ�������25ms */
uint16 k_S_PreChargeOnErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 158) \
		= (uint16)(2500 / d_PRECHARGEDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_PowRelay_Diag.c���ı궨����
 **********************************************************/
/* �̵�����Ϲ���ʹ�� */
uint8 k_S_EnPowRelayDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 160) = 255U;

/* �̵�����ͨѹ�������� */
uint16 k_S_PowRelayOnMaxTh_Vt_u16p11 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 162) = 3072U;	/* 1.5V */
/* �̵����رյ�ѹ������ */
uint16 k_S_PowRelayOffMinTh_Vt_u16p11 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 164) = 9216U;	/* 4.5V */

/* �̵�����ͨ���ϼ��������ӵĲ��� */
uint8 k_S_PowRelayOnErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 166) = 1U;
/* �̵�����ͨ���ϼ�������С�Ĳ��� */
uint8 k_S_PowRelayOnErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 167) = 5U;
/* �̵�����ͨ����ȷ�ϵļ�������25ms */
uint16 k_S_PowRelayOnErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 168) \
		= (uint16)(2500 / d_POWRELAYDIAG_TASKPERIOD_u16);

/* �̵����رչ��ϼ��������ӵĲ��� */
uint8 k_S_PowRelayOffErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 170) = 1U;
/* �̵����رչ��ϼ�������С�Ĳ��� */
uint8 k_S_PowRelayOffErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 171) = 5U;
/* �̵����رչ���ȷ�ϵļ�������25ms */
uint16 k_S_PowRelayOffErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 172) \
		= (uint16)(2500 / d_POWRELAYDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_PreDriver_Diag.c���ı궨����
 **********************************************************/
/* Ԥ����Ϲ���ʹ�� */
uint8 k_S_EnPreDrvDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 174) = 255U;

/* Ԥ��Ƿѹ���ϼ��������ӵĲ��� */
uint8 k_S_PreDrvUnderVoltCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 175) = 1U;
/* Ԥ��Ƿѹ���ϼ�������С�Ĳ��� */
uint8 k_S_PreDrvUnderVoltCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 176) = 5U;
/* Ԥ��Ƿѹ����ȷ�ϵļ������� 25ms */
uint16 k_S_PreDrvUnderVoltConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 178) \
		= (uint16)(2500 / d_PREDRIVERDIAG_TASKPERIOD_u16);

/* Ԥ����·���ϼ��������ӵĲ��� */
uint8 k_S_PreDrvShortCircuitCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 180) = 1U;
/* Ԥ����·���ϼ�������С�Ĳ��� */
uint8 k_S_PreDrvShortCircuitCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 181) = 5U;
/* Ԥ����·����ȷ�ϵļ������� 25ms */
uint16 k_S_PreDrvShortCircuitConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 182) \
		= (uint16)(2500 / d_PREDRIVERDIAG_TASKPERIOD_u16);

/* Ԥ����ѹ����ȹ��ϼ��������ӵĲ��� */
uint8 k_S_PreDrvOverVoltTempCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 184) = 1U;
/* Ԥ����ѹ����ȹ��ϼ�������С�Ĳ��� */
uint8 k_S_PreDrvOverVoltTempCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 185) = 5U;
/* Ԥ����ѹ����ȹ���ȷ�ϵļ�������25ms */
uint16 k_S_PreDrvOverVoltTempConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 186) \
		= (uint16)(2500 / d_PREDRIVERDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_Temperature_Diag.c���ı궨����
 **********************************************************/
uint8 k_S_TempSenDiagENbFlg_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 188) = 255U;

uint16 k_S_TempSenShGndLmt_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 190) = 8U;//50U;

uint16 k_S_TempSenShVcLmt_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 192) = 980U;//970U;

sint16 k_S_TempSenHighUpLmt_Deg_s16p01 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 194) = 240;//250;

sint16 k_S_TempSenHighDnLmt_Deg_s16p01 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 196) = 220;

sint16 k_S_TempSenLowLmt_Deg_s16p01 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 198) = -80;//-90;

uint8 k_S_TempSenShGndCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 200) = 1U;

uint8 k_S_TempSenShGndCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 201) = 5U;

uint16 k_S_TempSenShGndConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 202) \
		= (uint16)(16000 / d_TEMPERATUREDIAG_TASKPERIOD_u16);

uint8 k_S_TempSenShVcCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 204) = 1U;

uint8 k_S_TempSenShVcCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 205) = 5U;

uint16 k_S_TempSenShVcConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 206) \
		= (uint16)(16000 / d_TEMPERATUREDIAG_TASKPERIOD_u16);

uint8 k_S_TempSenHighCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 208) = 1U;

uint8 k_S_TempSenHighCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 209) = 5U;

uint16 k_S_TempSenHighConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 210) \
		= (uint16)(16000 / d_TEMPERATUREDIAG_TASKPERIOD_u16);

uint8 k_S_TempSenLowCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 212) = 1U;

uint8 k_S_TempSenLowCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 213) = 5U;

uint16 k_S_TempSenLowConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 214) \
		= (uint16)(16000 / d_TEMPERATUREDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_HBridge_Diag.c���ı궨����
 **********************************************************/
uint8 k_S_EnHACOpenDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 216) = 255U;

uint8 k_S_EnHBOpenDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 217) = 255U;

uint16 k_S_H1Diag_InitDutyU_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 218) = 800U;

uint16 k_S_H1Diag_InitDutyV_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 220) = 1100U;

uint16 k_S_H1Diag_InitDutyW_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 222) = 1100U;

uint16 k_S_H2Diag_InitDutyU_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 224) = 1100U;

uint16 k_S_H2Diag_InitDutyV_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 226) = 800U;

uint16 k_S_H2Diag_InitDutyW_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 228) = 1100U;

sint16 k_S_HACOpenCurThresh_A_G_s16p8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 230) = 450;

sint16 k_S_HBOpenCurThresh_A_G_s16p8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 232) = 450;

uint8 k_S_HAOpenErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 234) = 1;//2;

uint8 k_S_HAOpenErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 235) = 2;//1;

uint16 k_S_HAOpenErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 236) = 3;//4;

uint8 k_S_HBOpenErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 238) = 1;//2;

uint8 k_S_HBOpenErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 239) = 2;//1;

uint16 k_S_HBOpenErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 240) = 3;//4;

uint8 k_S_HCOpenErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 242) = 1;//2;

uint8 k_S_HCOpenErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 243) = 2;//1;

uint16 k_S_HCOpenErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 244) = 3;//4;

uint8 k_S_HABCOpenErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 246) = 1;//2;

uint8 k_S_HABCOpenErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 247) = 2;//1;

uint16 k_S_HABCOpenErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 248) = 3;//4;

/**********************************************************
 *  ���ڡ�L3_MotorCurr_Diag.c���ı궨����
 **********************************************************/
uint8 k_S_EnCurOfstDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 250) = 255U;

uint16 k_S_CurOfstSmpLoLmt_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 252) = 504U;

uint16 k_S_CurOfstSmpHiLmt_Cnt_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 254) = 520U;

uint8 k_S_CurUOfstErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 256) = 1;

uint8 k_S_CurUOfstErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 257) = 2;

uint16 k_S_CurUOfstErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 258) \
	= (uint16)(2500 / d_MOTORCURRDIAG_TASKPERIOD_u16);

uint8 k_S_CurWOfstErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 260) = 1;

uint8 k_S_CurWOfstErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 261) = 2;

uint16 k_S_CurWOfstErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 262) \
	= (uint16)(2500 / d_MOTORCURRDIAG_TASKPERIOD_u16);

uint8 k_S_EnCurReadRsnDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 264) = 255U;

uint8 k_S_EnCurReadBlnDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 265) = 255U;

uint16 k_S_MtrConRes_Ohm_u16p16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 266) = 39322U;//6554U;//16384U;

uint16 k_S_CurRdUnrsnErrLmt_A_G_u16p8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 268) = 512U;

uint16 k_S_CurUWTolerence_A_G_u16p8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 270) = 256U;

uint8 k_S_CurURsnErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 272) = 1;

uint8 k_S_CurURsnErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 273) = 2;

uint16 k_S_CurURsnErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 274) \
	= (uint16)(2500 / d_MOTORCURRDIAG_TASKPERIOD_u16);

uint8 k_S_CurWRsnErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 276) = 1;

uint8 k_S_CurWRsnErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 277) = 2;

uint16 k_S_CurWRsnErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 278) \
	= (uint16)(2500 / d_MOTORCURRDIAG_TASKPERIOD_u16);

uint8 k_S_CurUWBlnErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 280) = 1;

uint8 k_S_CurUWBlnErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 281) = 2;

uint16 k_S_CurUWBlnErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 282) \
	= (uint16)(2500 / d_MOTORCURRDIAG_TASKPERIOD_u16);

uint8 k_S_EnCurSenOverDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 284) = 255U;

uint8 k_S_EnCurSenOpenDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 285) = 0U;

uint16 k_S_CurSenOverLmt_A_G_u16p8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 286) = 35000U;//30720U;//24320U;

uint16 k_S_CurSenOpenLmt_A_G_u16p8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 288) = 3840U;//2560U;//1280U;

uint16 k_S_CurSenOpenSpdThresh_rpm_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 290) = 800U;

uint16 k_S_CurSenOpenMtrTrqThresh_NM_u16p11 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 292) = 4096U;

sint16 k_S_CurSenOpenCurThresh1_A_G_s16p8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 294) = 384;//512;

sint16 k_S_CurSenOpenCurThresh2_A_G_s16p8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 296) = 256;

uint8 k_S_CurOverErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 298) = 1;

uint8 k_S_CurOverErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 299) = 2;

uint16 k_S_CurOverErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 300) \
	= (uint16)(2500 / d_MOTORCURRDIAG_TASKPERIOD_u16);

uint8 k_S_CurOpenLoSpdErrCntIncStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 302) = 1;//2;

uint8 k_S_CurOpenLoSpdErrCntDecStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 303) = 10;//6;

uint8 k_S_CurOpenHiSpdErrCntIncStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 304) = 1;//2;

uint8 k_S_CurOpenHiSpdErrCntDecStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 305) = 10;//6;

uint8 k_S_CurOpenUVWErrCntIncStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 306) = 1;//2;

uint8 k_S_CurOpenUVWErrCntDecStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 307) = 10;//6;

uint16 k_S_CurOpenErrConfirmCntTh_Ct_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 308) \
    = (uint16)(2500 / d_MOTORCURRDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_MotorVolt_Diag.c���ı궨����
 **********************************************************/
uint8 k_S_EnMtrVoltCutDiag_Uls_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 310) = 255U;

uint16 k_S_MtrVoltDiffLim_V_u16p11 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 312) = 410U;

uint8 k_S_MtrVoltCutErrCntIncStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 314) = 1;

uint8 k_S_MtrVoltCutErrCntDecStep_Ct_u8 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 315) = 2;

uint16 k_S_MtrVoltCutErrConfirmCntTh_Ct_u16 \
	__at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 316) \
	= (uint16)(2500 / d_MOTORVOLTDIAG_TASKPERIOD_u16);

/**********************************************************
 *  ���ڡ�L3_MotorPos_Diag.c���ı궨����
 **********************************************************/
uint8 k_S_EnHallSenDiag_Uls_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 318) = 255U;

uint16 k_S_HallSenDiagTime_Cnt_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 320) = 1U;

uint16 k_S_MtrSpdDiagLoLmt_rpm_u16p3 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 322) = 80U;

uint16 k_S_MtrSpdDiagHiLmt_rpm_u16p3 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 324) = 32000U;

uint16 k_S_HallEdgIntCnt_uls_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 326) = 20000U;

uint8 k_S_HallSenErrCntIncStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 328) = 1;

uint8 k_S_HallSenErrCntDecStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 329) = 1;

uint16 k_S_HallSenErrConfirmCntTh_Ct_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 330) = 3;

uint8 k_S_EnEncoderDiag_Uls_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 332) = 0U;

uint16 k_S_EncoderDiagTime_Cnt_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 334) = 8U;

uint16 k_S_EncoderDifMaxLoLmt_Cnt_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 336) = 36U;

uint16 k_S_EncoderDifMaxHiLmt_Cnt_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 338) = 44U;

uint16 k_S_EncoderDifMinLoLmt_Cnt_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 340) = 4U;

uint16 k_S_EncoderDifMinHiLmt_Cnt_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 342) = 12U;

uint8 k_S_EncoderErrCntIncStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 344) = 1;

uint8 k_S_EncoderErrCntDecStep_Ct_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 345) = 5;//3;

uint16 k_S_EncoderErrConfirmCntTh_Ct_u16 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 346) = 5;//6;

/**********************************************************
 *  ���ڡ�TorqueAndAngle.c���ı궨����
 **********************************************************/
uint8 k_S_EnHwTrqSenDiag_Uls_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 352) = 255U;

uint8 k_S_EnHwPosSenDiag_Uls_u8 \
    __at(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 353) = 255U;

#endif

#define d_L3ECALFAILSAFECALDATA_STOP_SEC_CALIB_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/

/*End of L3_EcalFailSafe_CalData.c file*/
