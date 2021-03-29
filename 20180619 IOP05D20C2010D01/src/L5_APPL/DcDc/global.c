/*
 * File: global.c
 *
 * Real-Time Workshop code generated for Simulink model OBC.
 *
 * Model version                        : 1.2780
 * Real-Time Workshop file version      : 7.6  (R2010b)  03-Aug-2010
 * Real-Time Workshop file generated on : Mon Dec 19 14:28:59 2016
 * TLC version                          : 7.6 (Jul 13 2010)
 * C/C++ source code generated on       : Mon Dec 19 14:28:59 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 *    3. Safety precaution
 * Validation result: Passed (11), Warnings (2), Error (0)
 */

#include "rtwtypes.h"
#include "OBC_types.h"
#include "global.h"

/* Definition for custom storage class: Default */
//int16_T k_CurKi_Uls_s16p15 = 7;
//int16_T k_CurKp_Uls_s16p12 = 72;//1K

//int16_T k_CurKi_Uls_s16p15 = 28;
//int16_T k_CurKp_Uls_s16p12 = 144;//2K

//int16_T k_CurKi_Uls_s16p15 = 112;
//int16_T k_CurKp_Uls_s16p12 = 288;//4K

int16_T k_CurKi_Uls_s16p15 = CURRENT_I;
int16_T k_CurKp_Uls_s16p12 = CURRENT_P;//4K

//int16_T k_CurKi_Uls_s16p15 = 450;
//int16_T k_CurKp_Uls_s16p12 = 288;//4K


//int16_T k_CurKi_Uls_s16p15 = 252;//112*2.25
//int16_T k_CurKp_Uls_s16p12 = 432;//288*1.5   //6K

//uint8_T k_DcDcLoopType_u08 = 1U;//电压环
//uint8_T k_DcDcLoopType_u08 = 2U;//电流环
uint8_T k_DcDcLoopType_u08 = 3U;//电压环 电流环
int16_T k_PfcCurErrDeadZone_Ct_s16 = 10;
int16_T k_PfcCurKp_Uls_s16p10 = 0;

int16_T k_VoltKi_Uls_s16p15 = 58;
int16_T k_VoltKp_Uls_s16p12 = 1200;



//int16_T k_VoltKi_Uls_s16p15 = 58;
//int16_T k_VoltKp_Uls_s16p12 = 1200;
//int16_T k_VoltKi_Uls_s16p15 = 7000;
//int16_T k_VoltKi_Uls_s16p15 = 2800;
//int16_T k_VoltKp_Uls_s16p12 = 4800;

//int16_T k_VoltKi_Uls_s16p15 = 9000;
//int16_T k_VoltKp_Uls_s16p12 = 5000;

//int16_T k_VoltKp_Uls_s16p12 = 4000;

//int16_T k_VoltKi_Uls_s16p15 = 232;
//int16_T k_VoltKp_Uls_s16p12 = 2400;

//int16_T k_VoltKi_Uls_s16p15 = 232<<2;
//int16_T k_VoltKp_Uls_s16p12 = 4800;

//int16_T k_VoltKi_Uls_s16p15 = 232<<4;
//int16_T k_VoltKp_Uls_s16p12 = 4800<<1;

uint16_T voltCurrentdiffCt = 0;

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
