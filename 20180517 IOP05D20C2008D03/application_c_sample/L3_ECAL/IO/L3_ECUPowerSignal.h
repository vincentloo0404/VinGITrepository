#ifndef L3_ECUPOWERTSIGNAL_H
#define L3_ECUPOWERTSIGNAL_H 1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "m_GPIO.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/
/*Macro function for Precharge control*/
#define PreCharge_L3_Ctrl_On()       (C4_OUT = (HIGH))
#define PreCharge_L3_Ctrl_Off()      (C4_OUT = (LOW))

/*Macro function for discharge control*/
#define DisCharge_L3_Ctrl_On()       (C5_OUT = (HIGH))
#define DisCharge_L3_Ctrl_Off()      (C5_OUT = (LOW))

/*Macro function for Relay mosfet power control*/
#define RlyMosPower_L3_Ctrl_On()     (A12_OUT = (HIGH))
#define RlyMosPower_L3_Ctrl_Off()    (A12_OUT = (LOW))

/*Macro function for RslvVcc enable control*/
#define RslvVcc_L3_Ctrl_On()         (D7_OUT = (HIGH))    
#define RslvVcc_L3_Ctrl_Off()        (D7_OUT = (LOW))

/*Macro function for Sensor5V enable control*/
#define SenVolt_L3_Ctrl_On()         (C3_OUT = (HIGH))    
#define SenVolt_L3_Ctrl_Off()        (C3_OUT = (LOW))

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/

#endif
/*End of L3_ECUPowerSignal.h file*/
