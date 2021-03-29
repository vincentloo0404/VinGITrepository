/*
 * File: OBC.h
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

#ifndef RTW_HEADER_OBC_h_
#define RTW_HEADER_OBC_h_
#include <string.h>
#include <stddef.h>
#ifndef OBC_COMMON_INCLUDES_
# define OBC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* OBC_COMMON_INCLUDES_ */

#include "OBC_types.h"

/* Child system includes */
#include "DcDc.h"
#include "PianCi.h"

/* Includes for objects with custom storage classes. */
#include "global.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  int32_T Delay2_DSTATE;               /* '<S3>/Delay2' */
  int32_T Delay2_DSTATE_h;             /* '<S4>/Delay2' */
  int16_T Delay1_DSTATE;               /* '<S3>/Delay1' */
  int16_T Delay1_DSTATE_j;             /* '<S4>/Delay1' */
} D_Work_OBC;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  int16_T VoErr;                       /* '<Root>/VoErr' */
  int16_T IoErr;                       /* '<Root>/IoErr' */
  int16_T PfcCurErr;                   /* '<Root>/PfcCurErr' */
} ExternalInputs_OBC;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  uint16_T Ct;                         /* '<Root>/Ct' */
  boolean_T VLOOPbIT;                  /* '<Root>/VLOOPbIT' */
  int16_T Ct1;                         /* '<Root>/Ct1' */
  uint16_T VloopCt;                    /* '<Root>/VloopCt' */
  uint16_T CurrentLoopCt;              /* '<Root>/CurrentLoopCt' */
} ExternalOutputs_OBC;

/* Block signals and states (auto storage) */
extern D_Work_OBC OBC_DWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_OBC OBC_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_OBC OBC_Y;

/* Model entry point functions */
void OBC_initialize(void);
void OBC_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'OBC'
 * '<S1>'   : 'OBC/DcDc'
 * '<S2>'   : 'OBC/PianCi'
 * '<S3>'   : 'OBC/DcDc/CurrentLoop'
 * '<S4>'   : 'OBC/DcDc/VoltageLoop'
 * '<S5>'   : 'OBC/DcDc/CurrentLoop/Saturation Dynamic2'
 * '<S6>'   : 'OBC/DcDc/VoltageLoop/Saturation Dynamic2'
 * '<S7>'   : 'OBC/PianCi/Pianci'
 * '<S8>'   : 'OBC/PianCi/Pianci/Compare To Zero'
 * '<S9>'   : 'OBC/PianCi/Pianci/Dead Zone Dynamic'
 */

/*-
 * Requirements for '<Root>': OBC
 */
#endif                                 /* RTW_HEADER_OBC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
