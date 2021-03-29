#ifndef L3_TEMPERATURESIGNAL_H
#define L3_TEMPERATURESIGNAL_H 1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"
#include "L3_TemperatureSignal_Cfg.h"
#include "L3_AdcIf.h"
//#include "L3_ECU_Diagnosis.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern sint16 L3_S_MosfetTemp_DegC_G_s16p01;
extern const uint16 ADresult_Table[34];
extern const sint16 Temperature_Table[34];
/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void TemperatureAbstarct_L3_Per(void);
extern void TemperatureAbstarct_L3_Init(void);
#endif
/*End of L3_Temperature_Signal.h file*/
