/*
 * File: global.h
 *
 * Code generated for Simulink model 'OBC'.
 *
 * Model version                  : 1.2812
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Fri Feb 17 17:47:34 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 *    3. Safety precaution
 * Validation result: Passed (14), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_global_h_
#define RTW_HEADER_global_h_
#include "rtwtypes.h"
#include "OBC_types.h"

#define CURRENT_P ((int16_T)288)
#define CURRENT_I ((int16_T)300)

/* Exported data declaration */

/* Declaration for custom storage class: Default */
extern int16_T k_CurKi_Uls_s16p15;
extern int16_T k_CurKp_Uls_s16p12;
extern uint8_T k_DcDcLoopType_u08;
extern int16_T k_PfcCurErrDeadZone_Ct_s16;
extern int16_T k_PfcCurKp_Uls_s16p10;
extern int16_T k_VoltKi_Uls_s16p15;
extern int16_T k_VoltKp_Uls_s16p12;

extern uint16_T voltCurrentdiffCt;

#endif                                 /* RTW_HEADER_global_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
