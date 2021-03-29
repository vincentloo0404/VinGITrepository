/*
 * File: DcDc.c
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

#include "DcDc.h"

/* Include model header file for global data */
#include "OBC.h"
#include "OBC_private.h"

/* Output and update for atomic system: '<Root>/DcDc' */
void OBC_DcDc(void)
{
  /* Sum: '<S3>/Add2' incorporates:
   *  Constant: '<S3>/Ki'
   *  Constant: '<S3>/Kp'
   *  Delay: '<S3>/Delay1'
   *  Delay: '<S3>/Delay2'
   *  Inport: '<Root>/IoErr'
   *  Product: '<S3>/Product3'
   *  Product: '<S3>/Product4'
   *  Sum: '<S3>/Add3'
   */
  OBC_DWork.Delay2_DSTATE += ((int16_T)(OBC_U.IoErr - OBC_DWork.Delay1_DSTATE) *
    k_CurKp_Uls_s16p12 << 3) + OBC_U.IoErr * k_CurKi_Uls_s16p15;

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S3>/VxMax4'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (OBC_DWork.Delay2_DSTATE > 18677760) {
    OBC_DWork.Delay2_DSTATE = 18677760;
  } else {
    if (OBC_DWork.Delay2_DSTATE < 0) {
      /* Switch: '<S5>/Switch' incorporates:
       *  Constant: '<S3>/VxMax5'
       */
      OBC_DWork.Delay2_DSTATE = 0;
    }
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Outport: '<Root>/CurrentLoopCt' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   */
  OBC_Y.CurrentLoopCt = (uint16_T)(OBC_DWork.Delay2_DSTATE >> 15);

  /* Sum: '<S4>/Add2' incorporates:
   *  Constant: '<S4>/Ki1'
   *  Constant: '<S4>/Kp1'
   *  Delay: '<S4>/Delay1'
   *  Delay: '<S4>/Delay2'
   *  Inport: '<Root>/VoErr'
   *  Product: '<S4>/Product3'
   *  Product: '<S4>/Product4'
   *  Sum: '<S4>/Add3'
   */
  OBC_DWork.Delay2_DSTATE_h += ((int16_T)(OBC_U.VoErr -
    OBC_DWork.Delay1_DSTATE_j) * k_VoltKp_Uls_s16p12 << 3) + OBC_U.VoErr *
    k_VoltKi_Uls_s16p15;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S4>/VxMax4'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (OBC_DWork.Delay2_DSTATE_h > 18677760) {
    OBC_DWork.Delay2_DSTATE_h = 18677760;
  } else {
    if (OBC_DWork.Delay2_DSTATE_h < 0) {
      /* Switch: '<S6>/Switch' incorporates:
       *  Constant: '<S4>/VxMax5'
       */
      OBC_DWork.Delay2_DSTATE_h = 0;
    }
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Outport: '<Root>/VloopCt' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   */
  OBC_Y.VloopCt = (uint16_T)(OBC_DWork.Delay2_DSTATE_h >> 15);

  /* MultiPortSwitch: '<S1>/Multiport Switch' incorporates:
   *  Constant: '<S1>/Ki1'
   */
  switch (k_DcDcLoopType_u08) {
   case 1:
    /* Outport: '<Root>/Ct' */
    OBC_Y.Ct = OBC_Y.VloopCt;
    break;

   case 2:
    /* Outport: '<Root>/Ct' */
    OBC_Y.Ct = OBC_Y.CurrentLoopCt;
    break;

   case 3:
    /* MinMax: '<S1>/MinMax' */
    if (OBC_Y.VloopCt <= OBC_Y.CurrentLoopCt) {
      /* Outport: '<Root>/Ct' */
      OBC_Y.Ct = OBC_Y.VloopCt;
    } else {
      /* Outport: '<Root>/Ct' */
      OBC_Y.Ct = OBC_Y.CurrentLoopCt;
    }

    /* End of MinMax: '<S1>/MinMax' */
    break;

   default:
    /* Outport: '<Root>/Ct' incorporates:
     *  Constant: '<S1>/Ki2'
     */
    OBC_Y.Ct = 0U;
    break;
  }

  /* End of MultiPortSwitch: '<S1>/Multiport Switch' */

  /* Outport: '<Root>/VLOOPbIT' incorporates:
   *  RelationalOperator: '<S1>/Relational Operator'
   */
  OBC_Y.VLOOPbIT = OBC_Y.VloopCt <= OBC_Y.CurrentLoopCt;

  /* Update for Delay: '<S3>/Delay1' incorporates:
   *  Update for Inport: '<Root>/IoErr'
   */
  OBC_DWork.Delay1_DSTATE = OBC_U.IoErr;

  /* Update for Delay: '<S4>/Delay1' incorporates:
   *  Update for Inport: '<Root>/VoErr'
   */
  OBC_DWork.Delay1_DSTATE_j = OBC_U.VoErr;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
