#ifndef L3_ECALFAILSAFE_CALDATA_H
#define L3_ECALFAILSAFE_CALDATA_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_EmEep.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
#define d_L3FSCALIBDATA_RAMSTARTADDR_u16        (0x40000C00U)

#if 0

/**********************************************************
 *  用于“L3_PreDriver_Diag.c”的标定变量
 **********************************************************/
#define  k_S_EnPreDrvDiag_Uls_u8                 ((uint8*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 0))

#define  k_S_PreDrvUnderVoltCntIncStep_Ct_u8     ((uint8*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 2))
#define  k_S_PreDrvUnderVoltCntDecStep_Ct_u8     ((uint8*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 3))
#define  k_S_PreDrvUnderVoltConfirmCntTh_Ct_u16  ((uint16*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 4))

#define  k_S_PreDrvShortCircuitCntIncStep_Ct_u8      ((uint8*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 6))
#define  k_S_PreDrvShortCircuitCntDecStep_Ct_u8      ((uint8*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 7))
#define  k_S_PreDrvShortCircuitConfirmCntTh_Ct_u16   ((uint16*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 8))

#define  k_S_PreDrvOverVoltTempCntIncStep_Ct_u8      ((uint8*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 10))
#define  k_S_PreDrvOverVoltTempCntDecStep_Ct_u8      ((uint8*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 11))
#define  k_S_PreDrvOverVoltTempConfirmCntTh_Ct_u16   ((uint16*)(d_L3FSCALIBDATA_RAMSTARTADDR_u16 + 12))




/**********************************************************
 *  用于“L3_Ecu_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnALUCalcDiag_Uls_u8;
extern uint8 k_S_ALUCalcErrCntIncStep_Ct_u8;
extern uint8 k_S_ALUCalcErrCntDecStep_Ct_u8;
extern uint16 k_S_ALUCalcErrConfirmCntTh_Ct_u16;

extern uint8 k_S_EnADCSampDiag_Uls_u8;
extern uint8 k_S_ADCTimeoutCntIncStep_Ct_u8;
extern uint8 k_S_ADCTimeoutCntDecStep_Ct_u8;
extern uint16 k_S_ADCTimeoutConfirmCntTh_Ct_u16;

extern uint8 k_S_EnTaskLoopDiag_Uls_u8;
extern uint8 k_S_TaskTimeoutCntIncStep_Ct_u8;
extern uint8 k_S_TaskTimeoutCntDecStep_Ct_u8;
extern uint16 k_S_TaskTimeoutConfirmCntTh_Ct_u16;

extern uint8 k_S_EnU0C1CommDiag_Uls_u8;
extern uint8 k_S_U0C1CommErrCntIncStep_Ct_u8;
extern uint8 k_S_U0C1CommErrCntDecStep_Ct_u8;
extern uint16 k_S_U0C1CommErrConfirmCntTh_Ct_u16;

extern uint8 k_S_EnU1C0CommDiag_Uls_u8;
extern uint8 k_S_U1C0CommErrCntIncStep_Ct_u8;
extern uint8 k_S_U1C0CommErrCntDecStep_Ct_u8;
extern uint16 k_S_U1C0CommErrConfirmCntTh_Ct_u16;

extern uint8 k_S_EnMonitorOptDiag_Uls_u8;
extern uint8 k_S_MonitorOptErrCntIncStep_Ct_u8;
extern uint8 k_S_MonitorOptErrCntDecStep_Ct_u8;
extern uint16 k_S_MonitorOptErrConfirmCntTh_Ct_u16;

extern uint8 k_S_EnEEPROMOptDiag_Uls_u8;
extern uint8 k_S_EEPROMOptErrCntIncStep_Ct_u8;
extern uint8 k_S_EEPROMOptErrCntDecStep_Ct_u8;
extern uint16 k_S_EEPROMOptErrConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_BattVolt_Diag.c”的标定变量
 **********************************************************/
extern uint16 k_S_BatOffStateEnterLimit_V_u16p08;
extern uint16 k_S_BatOffStateExitLimit_V_u16p08;
extern uint16 k_S_BatLowStateEnterLimit_V_u16p08;
extern uint16 k_S_BatLowStateExitLimit_V_u16p08;
extern uint16 k_S_BatNormal1StateEnterLimit_V_u16p08;
extern uint16 k_S_BatNormal1StateExitLimit_V_u16p08;
extern uint16 k_S_BatOver1StateEnterLimit_V_u16p08;
extern uint16 k_S_BatOver1StateExitLimit_V_u16p08;
extern uint16 k_S_BatOver2StateEnterLimit_V_u16p08;
extern uint16 k_S_BatOver2StateExitLimit_V_u16p08;
extern uint8 k_S_BatErrCntIncStep_Ct_u8;
extern uint8 k_S_BatErrCntDecStep_Ct_u8;
extern uint16 k_S_BatOffConfirmCntTh_Ct_u16;
extern uint16 k_S_BatOffClearCntTh_Ct_u16;
extern uint16 k_S_BatLowConfirmCntTh_Ct_u16;
extern uint16 k_S_BatLowClearCntTh_Ct_u16;
extern uint16 k_S_BatNormal1ConfirmCntTh_Ct_u16;
extern uint16 k_S_BatNormal1ClearCntTh_Ct_u16;
extern uint16 k_S_BatOver1ConfirmCntTh_Ct_u16;
extern uint16 k_S_BatOver1ClearCntTh_Ct_u16;
extern uint16 k_S_BatOver2ConfirmCntTh_Ct_u16;
extern uint16 k_S_BatOver2ClearCntTh_Ct_u16;
extern uint8 k_S_EnBatVoltDiag_Uls_u8;

/**********************************************************
 *  用于“L3_SensorVolt_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnSenVoltDiag_Uls_u8;
extern uint16 k_S_SenVoltLowTh_V_u16p08;
extern uint16 k_S_SenVoltHighTh_V_u16p08;
extern uint8 k_S_SenVoltLowCntIncStep_Ct_u8;
extern uint8 k_S_SenVoltLowCntDecStep_Ct_u8;
extern uint16 k_S_SenVoltLowConfirmCntTh_Ct_u16;
extern uint8 k_S_SenVoltHighCntIncStep_Ct_u8;
extern uint8 k_S_SenVoltHighCntDecStep_Ct_u8;
extern uint16 k_S_SenVoltHighConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_StrAngleSensor_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnSASDiag_Uls_u8;
extern uint16 k_S_SASMsgInitDelayCntTh_Ct_u16;
extern uint8 k_S_StrAngInvalidCntIncStep_Ct_u8;
extern uint8 k_S_StrAngInvalidCntDecStep_Ct_u8;
extern uint16 k_S_StrAngInvalidConfirmCntTh_Ct_u16;
extern uint8 k_S_StrAngLostCntIncStep_Ct_u8;
extern uint8 k_S_StrAngLostCntDecStep_Ct_u8;
extern uint16 k_S_StrAngLostConfirmCntTh_Ct_u16;
extern uint8 k_S_StrAngSpdInvalidCntIncStep_Ct_u8;
extern uint8 k_S_StrAngSpdInvalidCntDecStep_Ct_u8;
extern uint16 k_S_StrAngSpdInvalidConfirmCntTh_Ct_u16;
extern uint8 k_S_StrAngSpdLostCntIncStep_Ct_u8;
extern uint8 k_S_StrAngSpdLostCntDecStep_Ct_u8;
extern uint16 k_S_StrAngSpdLostConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_EngineStatus_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnEngStsDiag_Uls_u8;
extern uint8 k_S_EngStsInvalidCntIncStep_Ct_u8;
extern uint8 k_S_EngStsInvalidCntDecStep_Ct_u8;
extern uint16 k_S_EngStsInvalidConfirmCntTh_Ct_u16;
extern uint8 k_S_EngStsLostCntIncStep_Ct_u8;
extern uint8 k_S_EngStsLostCntDecStep_Ct_u8;
extern uint16 k_S_EngStsLostConfirmCntTh_Ct_u16;
extern uint16 k_S_EngStsMsgInitDelayCntTh_Ct_u16;
extern uint16 k_S_EngStsRunConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_VehicleSpeed_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnVehSpdDiag_Uls_u8;
extern uint8 k_S_VehSpdInvalidCntIncStep_Ct_u8;
extern uint8 k_S_VehSpdInvalidCntDecStep_Ct_u8;
extern uint16 k_S_VehSpdInvalidConfirmCntTh_Ct_u16;
extern uint8 k_S_VehSpdLostCntIncStep_Ct_u8;
extern uint8 k_S_VehSpdLostCntDecStep_Ct_u8;
extern uint16 k_S_VehSpdLostConfirmCntTh_Ct_u16;
extern uint16 k_S_VehSpdMsgInitDelayCntTh_Ct_u16;
extern uint16 k_S_VehSpdDefaultValue_Kph_u16p01;
extern uint16 k_S_VehSpdTranStepValue_Kph_u16p01;
extern uint16 k_N_VehSpdFltDen_Uls_u16p14;
extern uint16 k_N_VehSpdFltNum_Uls_u16p14;

/**********************************************************
 *  用于“L3_PreCharge_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnPreChargeDiag_Uls_u8;
extern uint16 k_S_PreChargeOnMaxTh_Vt_u16p11;
extern uint8 k_S_PreChargeOnErrCntIncStep_Ct_u8;
extern uint8 k_S_PreChargeOnErrCntDecStep_Ct_u8;
extern uint16 k_S_PreChargeOnErrConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_PowRelay_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnPowRelayDiag_Uls_u8;
extern uint16 k_S_PowRelayOnMaxTh_Vt_u16p11;
extern uint16 k_S_PowRelayOffMinTh_Vt_u16p11;
extern uint8 k_S_PowRelayOnErrCntIncStep_Ct_u8;
extern uint8 k_S_PowRelayOnErrCntDecStep_Ct_u8;
extern uint16 k_S_PowRelayOnErrConfirmCntTh_Ct_u16;
extern uint8 k_S_PowRelayOffErrCntIncStep_Ct_u8;
extern uint8 k_S_PowRelayOffErrCntDecStep_Ct_u8;
extern uint16 k_S_PowRelayOffErrConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_PreDriver_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnPreDrvDiag_Uls_u8;
extern uint8 k_S_PreDrvUnderVoltCntIncStep_Ct_u8;
extern uint8 k_S_PreDrvUnderVoltCntDecStep_Ct_u8;
extern uint16 k_S_PreDrvUnderVoltConfirmCntTh_Ct_u16;
extern uint8 k_S_PreDrvShortCircuitCntIncStep_Ct_u8;
extern uint8 k_S_PreDrvShortCircuitCntDecStep_Ct_u8;
extern uint16 k_S_PreDrvShortCircuitConfirmCntTh_Ct_u16;
extern uint8 k_S_PreDrvOverVoltTempCntIncStep_Ct_u8;
extern uint8 k_S_PreDrvOverVoltTempCntDecStep_Ct_u8;
extern uint16 k_S_PreDrvOverVoltTempConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_Temperature_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_TempSenDiagENbFlg_Uls_u8;
extern uint16 k_S_TempSenShGndLmt_Cnt_u16;
extern uint16 k_S_TempSenShVcLmt_Cnt_u16;
extern sint16 k_S_TempSenHighUpLmt_Deg_s16p01;
extern sint16 k_S_TempSenHighDnLmt_Deg_s16p01;
extern sint16 k_S_TempSenLowLmt_Deg_s16p01;
extern uint8 k_S_TempSenShGndCntIncStep_Ct_u8;
extern uint8 k_S_TempSenShGndCntDecStep_Ct_u8;
extern uint16 k_S_TempSenShGndConfirmCntTh_Ct_u16;
extern uint8 k_S_TempSenShVcCntIncStep_Ct_u8;
extern uint8 k_S_TempSenShVcCntDecStep_Ct_u8;
extern uint16 k_S_TempSenShVcConfirmCntTh_Ct_u16;
extern uint8 k_S_TempSenHighCntIncStep_Ct_u8;
extern uint8 k_S_TempSenHighCntDecStep_Ct_u8;
extern uint16 k_S_TempSenHighConfirmCntTh_Ct_u16;
extern uint8 k_S_TempSenLowCntIncStep_Ct_u8;
extern uint8 k_S_TempSenLowCntDecStep_Ct_u8;
extern uint16 k_S_TempSenLowConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_HBridge_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnHACOpenDiag_Uls_u8;
extern uint8 k_S_EnHBOpenDiag_Uls_u8;
extern uint16 k_S_H1Diag_InitDutyU_Cnt_u16;
extern uint16 k_S_H1Diag_InitDutyV_Cnt_u16;
extern uint16 k_S_H1Diag_InitDutyW_Cnt_u16;
extern uint16 k_S_H2Diag_InitDutyU_Cnt_u16;
extern uint16 k_S_H2Diag_InitDutyV_Cnt_u16;
extern uint16 k_S_H2Diag_InitDutyW_Cnt_u16;
extern sint16 k_S_HACOpenCurThresh_A_G_s16p8;
extern sint16 k_S_HBOpenCurThresh_A_G_s16p8;
extern uint8 k_S_HAOpenErrCntIncStep_Ct_u8;
extern uint8 k_S_HAOpenErrCntDecStep_Ct_u8;
extern uint16 k_S_HAOpenErrConfirmCntTh_Ct_u16;
extern uint8 k_S_HBOpenErrCntIncStep_Ct_u8;
extern uint8 k_S_HBOpenErrCntDecStep_Ct_u8;
extern uint16 k_S_HBOpenErrConfirmCntTh_Ct_u16;
extern uint8 k_S_HCOpenErrCntIncStep_Ct_u8;
extern uint8 k_S_HCOpenErrCntDecStep_Ct_u8;
extern uint16 k_S_HCOpenErrConfirmCntTh_Ct_u16;
extern uint8 k_S_HABCOpenErrCntIncStep_Ct_u8;
extern uint8 k_S_HABCOpenErrCntDecStep_Ct_u8;
extern uint16 k_S_HABCOpenErrConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_MotorCurr_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnCurOfstDiag_Uls_u8;
extern uint16 k_S_CurOfstSmpLoLmt_Cnt_u16;
extern uint16 k_S_CurOfstSmpHiLmt_Cnt_u16;
extern uint8 k_S_CurUOfstErrCntIncStep_Ct_u8;
extern uint8 k_S_CurUOfstErrCntDecStep_Ct_u8;
extern uint16 k_S_CurUOfstErrConfirmCntTh_Ct_u16;
extern uint8 k_S_CurWOfstErrCntIncStep_Ct_u8;
extern uint8 k_S_CurWOfstErrCntDecStep_Ct_u8;
extern uint16 k_S_CurWOfstErrConfirmCntTh_Ct_u16;
extern uint8 k_S_EnCurReadRsnDiag_Uls_u8;
extern uint8 k_S_EnCurReadBlnDiag_Uls_u8;
extern uint16 k_S_MtrConRes_Ohm_u16p16;
extern uint16 k_S_CurRdUnrsnErrLmt_A_G_u16p8;
extern uint16 k_S_CurUWTolerence_A_G_u16p8;
extern uint8 k_S_CurURsnErrCntIncStep_Ct_u8;
extern uint8 k_S_CurURsnErrCntDecStep_Ct_u8;
extern uint16 k_S_CurURsnErrConfirmCntTh_Ct_u16;
extern uint8 k_S_CurWRsnErrCntIncStep_Ct_u8;
extern uint8 k_S_CurWRsnErrCntDecStep_Ct_u8;
extern uint16 k_S_CurWRsnErrConfirmCntTh_Ct_u16;
extern uint8 k_S_CurUWBlnErrCntIncStep_Ct_u8;
extern uint8 k_S_CurUWBlnErrCntDecStep_Ct_u8;
extern uint16 k_S_CurUWBlnErrConfirmCntTh_Ct_u16;
extern uint8 k_S_EnCurSenOverDiag_Uls_u8;
extern uint8 k_S_EnCurSenOpenDiag_Uls_u8;
extern uint16 k_S_CurSenOverLmt_A_G_u16p8;
extern uint16 k_S_CurSenOpenLmt_A_G_u16p8;
extern uint16 k_S_CurSenOpenSpdThresh_rpm_u16;
extern uint16 k_S_CurSenOpenMtrTrqThresh_NM_u16p11;
extern sint16 k_S_CurSenOpenCurThresh1_A_G_s16p8;
extern sint16 k_S_CurSenOpenCurThresh2_A_G_s16p8;
extern uint8 k_S_CurOverErrCntIncStep_Ct_u8;
extern uint8 k_S_CurOverErrCntDecStep_Ct_u8;
extern uint16 k_S_CurOverErrConfirmCntTh_Ct_u16;
extern uint8 k_S_CurOpenLoSpdErrCntIncStep_Ct_u8;
extern uint8 k_S_CurOpenLoSpdErrCntDecStep_Ct_u8;
extern uint8 k_S_CurOpenHiSpdErrCntIncStep_Ct_u8;
extern uint8 k_S_CurOpenHiSpdErrCntDecStep_Ct_u8;
extern uint8 k_S_CurOpenUVWErrCntIncStep_Ct_u8;
extern uint8 k_S_CurOpenUVWErrCntDecStep_Ct_u8;
extern uint16 k_S_CurOpenErrConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_MotorVolt_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnMtrVoltCutDiag_Uls_u8;
extern uint16 k_S_MtrVoltDiffLim_V_u16p11;
extern uint8 k_S_MtrVoltCutErrCntIncStep_Ct_u8;
extern uint8 k_S_MtrVoltCutErrCntDecStep_Ct_u8;
extern uint16 k_S_MtrVoltCutErrConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“L3_MotorPos_Diag.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnHallSenDiag_Uls_u8;
extern uint16 k_S_HallSenDiagTime_Cnt_u16;
extern uint16 k_S_MtrSpdDiagLoLmt_rpm_u16p3;
extern uint16 k_S_MtrSpdDiagHiLmt_rpm_u16p3;
extern uint16 k_S_HallEdgIntCnt_uls_u16;
extern uint8 k_S_HallSenErrCntIncStep_Ct_u8;
extern uint8 k_S_HallSenErrCntDecStep_Ct_u8;
extern uint16 k_S_HallSenErrConfirmCntTh_Ct_u16;
extern uint8 k_S_EnEncoderDiag_Uls_u8;
extern uint16 k_S_EncoderDiagTime_Cnt_u16;
extern uint16 k_S_EncoderDifMaxLoLmt_Cnt_u16;
extern uint16 k_S_EncoderDifMaxHiLmt_Cnt_u16;
extern uint16 k_S_EncoderDifMinLoLmt_Cnt_u16;
extern uint16 k_S_EncoderDifMinHiLmt_Cnt_u16;
extern uint8 k_S_EncoderErrCntIncStep_Ct_u8;
extern uint8 k_S_EncoderErrCntDecStep_Ct_u8;
extern uint16 k_S_EncoderErrConfirmCntTh_Ct_u16;

/**********************************************************
 *  用于“TorqueAndAngle.c”的标定变量
 **********************************************************/
extern uint8 k_S_EnHwTrqSenDiag_Uls_u8;
extern uint8 k_S_EnHwPosSenDiag_Uls_u8;

#endif

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/

#endif

/* End of L3_EcalFailSafe_CalData.h file */
