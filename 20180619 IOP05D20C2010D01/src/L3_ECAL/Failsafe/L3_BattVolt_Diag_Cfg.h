/*****************************************************************************
*   Copyright 2010 - 2011 Shanghai Aerospace Automobile Electromechanical 
*   Co., Ltd., all rights reserved.
*
*   Filename:    L3_BattVolt_Diag_Cfg.h
*
*   Description: 该文件是电池电压诊断模块的配置文件
*
*   Revision History:
*
*   Date            Author          Description
*   ----------      ----------      -----------------------------------------
*   2013-08-12      chunlin.zhu     CR000100: Initial created
*	2014-1-14		liujie.zhong	Divide cold & warm initial state
*									Design the state flow, fail safe strategy
*****************************************************************************/
#ifndef L3_BATTVOLT_DIAG_CFG_H
#define L3_BATTVOLT_DIAG_CFG_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_Data.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/
/* Batt Volt Diag的执行周期，以10us为单位 */
#define d_BATTVOLTDIAG_TASKPERIOD_u16		200U

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/

#endif  /* L3_BATTVOLT_DIAG_CFG_H */

/*End of L3_BattVolt_Diag_Cfg.h file */
