#ifndef L3_SENSORVOLT_CFG_H
#define L3_SENSORVOLT_CFG_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "L3_SensorVoltageSignal.h"
#include "L3_SensorVolt_Diag_Cfg.h"
#include "L4_DTC.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
/* 传感器供电电压诊断结果 */
typedef struct
{
    boolean SenVoltLow_lgc ;
    boolean SenVoltHigh_lgc;
} FS_SenorVoltDiagType_Str;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern FS_SenorVoltDiagType_Str L3_S_SenorVoltDiagResult_Uls_G_Str;

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void FS_L3_SensorVoltDiagInit(void);
extern void FS_L3_SensorVoltDiagPer(void);

#endif
/*End of L3_SensorVolt_Diag.c file */

