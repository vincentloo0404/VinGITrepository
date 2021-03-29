#ifndef L3_BATTVOLT_DIAG_H
#define L3_BATTVOLT_DIAG_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"
#include "L3_AdcIf.h"
#include "L3_BattVolt_Diag_Cfg.h"

#include "L4_DTC.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
/* 电池电压等级 */
typedef enum
{
    e_BAT_OFF = 0,     /* 0V    <= Batt Volt < 6.5V  */
    e_BAT_LOW,         /* 6.5V  <= Batt Volt < 9.0V  */
    e_BAT_NORMAL_1,    /* 9.0V  <= Batt Volt < 10.0V */
    e_BAT_NORMAL_2,    /* 10.0V <= Batt Volt < 16.0V */
    e_BAT_OVER_1,      /* 16.0V <= Batt Volt < 18.0V */
    e_BAT_OVER_2       /* 18.0V <= Batt Volt < 20.0V */
} BattDiag_BattLevel_Enu;

/* 电池管理状态 */
typedef enum
{
    e_BAT_STATE_OFF = 0,
	e_BAT_STATE_LOW,
    e_BAT_STATE_NORMAL1,
    e_BAT_STATE_NORMAL2,
    e_BAT_STATE_OVER1,
    e_BAT_STATE_OVER2
} BattDiag_BattState_Enu;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern BattDiag_BattLevel_Enu L3_S_BatLevel_Uls_G_Enu;
extern BattDiag_BattState_Enu L3_S_BatState_Uls_G_Enu;

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void FS_L3_BatVoltDiagInit(void);
extern void FS_L3_BatVoltDiagPer(void);

#endif  /* L3_BATTVOLT_DIAG_H */

