/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     dDiagDecCfg.h
*
* @brief    Config file for Diag-Decision module.
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/07/25     CODER1      N/A          Original
*     1.1        2013/11/05     CODER1      N/A          Add Marco STEERING_ANGLE_SPD_MAX
************************************************************************************************/

#ifndef _D_DIAGDECCFG_H_
#define _D_DIAGDECCFG_H_

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include 	"MPC560xP.h"
//#include	"types.h"
#include    "SysConfig.h"
//#include    "GFLIB_Ramp.h"


/* *****************************************************************************
   *****************************************************************************
   macro definition
   *****************************************************************************
   ***************************************************************************** */

/* engine run condition */
#define ENGINE_SPD_UNIT_1RPM     (1/0.125)  /* 1RPM */
#define ENGINE_RUN_SPD_LMT       (INT16U)(330*ENGINE_SPD_UNIT_1RPM)   /* rmp */
#define ENGINE_RUN_TIME_LMT      (INT16U)(1500/TIMER_BASE)             /* ms */

/* vehicle speed */
#define VEH_SPD_UNIT             (1/0.05625)                 /* 1KMP */

#define VEH_SPD_RAMP_REPLACE     (INT16U)(40*VEH_SPD_UNIT)   /* 40kmph */
#define VEH_SPD_RAMP_UP          (INT16U)(0.1*VEH_SPD_UNIT)
#define VEH_SPD_RAMP_DOWN        (INT16U)(0.1*VEH_SPD_UNIT)

#define VEHICLE_SPD_LMT          (INT16U)(1*VEH_SPD_UNIT)    /* 1kmph */

/* Steering Angle */
#define STEERING_ANGLE_INVALID       0x7FFF
#define STEERING_ANGLE_SPD_INVALID   0xFF
#define STEERING_ANGLE_SPD_MAX       (0xFE<<2)               /* 1016бу/s */

#define ASSIT_DELAY_COUNTER      (INT16U)(10000u/TIMER_BASE)    /* ms, Assist stop delay time */ 
#define SLEEP_DELAY_COUNTER      (INT32U)(20000u/TIMER_BASE)    /* ms  Sleep delay time*/

#endif

/*********************************************** End ************************************************/
