#ifndef L3_VOLTSIGNAL_H
#define L3_VOLTSIGNAL_H 1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "L3_AdcIf.h"

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
extern uint16 L3_S_BatCmmVolt_Volt_G_u16p08;
extern uint16 L3_S_BatCmmVolt_Volt_G_u16p10;
extern uint16 L3_S_BatMosVolt_Volt_G_u16p10;

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void VoltSignalAbstract_L3_Init(void);
extern void VoltSignalAbstract_L3_Per(void);

#endif
/*End of L3_Motor_Current_Signal.h file*/