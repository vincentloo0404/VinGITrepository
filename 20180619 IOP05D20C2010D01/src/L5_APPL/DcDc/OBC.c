/*
 * File: OBC.c
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

#include "OBC.h"
#include "OBC_private.h"

/* Block signals and states (auto storage) */
D_Work_OBC OBC_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_OBC OBC_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_OBC OBC_Y;

/* Model step function */
void OBC_step(void)
{
  /* Outputs for Atomic SubSystem: '<Root>/DcDc' */
  OBC_DcDc();

  /* End of Outputs for SubSystem: '<Root>/DcDc' */

  /* Outputs for Atomic SubSystem: '<Root>/PianCi' */
  OBC_PianCi();

  /* End of Outputs for SubSystem: '<Root>/PianCi' */
}

/* Model initialize function */
void OBC_initialize(void)
{
  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)&OBC_DWork, 0,
                sizeof(D_Work_OBC));

  /* external inputs */
  (void) memset((void *)&OBC_U, 0,
                sizeof(ExternalInputs_OBC));

  /* external outputs */
  (void) memset((void *)&OBC_Y, 0,
                sizeof(ExternalOutputs_OBC));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
