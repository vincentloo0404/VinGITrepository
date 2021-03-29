/*
 * File: PianCi.c
 *
 * Code generated for Simulink model 'OBC'.
 *
 * Model version                  : 1.2804
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jan 29 10:20:46 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 *    3. Safety precaution
 * Validation result: Passed (14), Warnings (2), Error (0)
 */

#include "PianCi.h"

/* Include model header file for global data */
#include "OBC.h"
#include "OBC_private.h"

/* Output and update for atomic system: '<Root>/PianCi' */
void OBC_PianCi(void)
{
  int16_T rtb_Abs;
  int16_T rtb_Abs_0;

  /* Abs: '<S7>/Abs' incorporates:
   *  Inport: '<Root>/PfcCurErr'
   */
  if (OBC_U.PfcCurErr < 0) {
    rtb_Abs = (int16_T)-OBC_U.PfcCurErr;
  } else {
    rtb_Abs = OBC_U.PfcCurErr;
  }

  /* End of Abs: '<S7>/Abs' */

  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S7>/Kp1'
   *  Constant: '<S7>/VxMax2'
   *  RelationalOperator: '<S9>/u_GTE_up'
   *  RelationalOperator: '<S9>/u_GT_lo'
   *  Switch: '<S9>/Switch1'
   */
  if (rtb_Abs >= k_PfcCurErrDeadZone_Ct_s16) {
    rtb_Abs_0 = k_PfcCurErrDeadZone_Ct_s16;
  } else if (rtb_Abs > 0) {
    /* Switch: '<S9>/Switch1' */
    rtb_Abs_0 = rtb_Abs;
  } else {
    rtb_Abs_0 = 0;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Product: '<S7>/Product1' incorporates:
   *  Constant: '<S7>/Kp'
   *  Sum: '<S9>/Diff'
   */
  OBC_Y.Ct1 = (int16_T)((int16_T)(rtb_Abs - rtb_Abs_0) * k_PfcCurKp_Uls_s16p10 >>
                        10);

  /* MinMax: '<S7>/MinMax1' */
  if (!(OBC_Y.Ct1 >= -5)) {
    /* Product: '<S7>/Product1' */
    OBC_Y.Ct1 = -5;
  }

  /* End of MinMax: '<S7>/MinMax1' */

  /* MinMax: '<S7>/MinMax' */
  if (5 <= OBC_Y.Ct1) {
    /* Product: '<S7>/Product1' */
    OBC_Y.Ct1 = 5;
  }

  /* End of MinMax: '<S7>/MinMax' */

  /* Switch: '<S7>/Switch' incorporates:
   *  Constant: '<S8>/Constant'
   *  Inport: '<Root>/PfcCurErr'
   *  RelationalOperator: '<S8>/Compare'
   */
  if (OBC_U.PfcCurErr < 0) {
    /* Product: '<S7>/Product1' incorporates:
     *  Outport: '<Root>/Ct1'
     *  Sum: '<S7>/Add'
     */
    OBC_Y.Ct1 = (int16_T)-OBC_Y.Ct1;
  }

  /* End of Switch: '<S7>/Switch' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
