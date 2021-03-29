
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_TemperatureSignal.h"

/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3POWERCIRCUITSIGNAL_START_SEC_VAR
#include "MemMap.h"

sint16 L3_S_MosfetTemp_DegC_G_s16p01;

#define d_L3POWERCIRCUITSIGNAL_STOP_SEC_VAR
#include "MemMap.h"
/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3POWERCIRCUITSIGNAL_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     TemperatureAbstarct_L3_Init
*
*   Description:  This function is use to get the temperature signal
*
*   Inputs:       None
*
*   Outputs:      none
*
*   Notes:
*
*****************************************************************************/
void TemperatureAbstarct_L3_Init(void)
{
	L3_S_MosfetTemp_DegC_G_s16p01 = 50;
}
/*****************************************************************************
*
*   Function:     TemperatureAbstarct_L3_Per
*
*   Description:  This function is use to get the temperature signal
*
*   Inputs:       None
*
*   Outputs:      diagnosis state
*
*   Notes:
*
*****************************************************************************/
void TemperatureAbstarct_L3_Per(void)
{
    
   // TempSig_L3_Per();
    
}
#define d_L3POWERCIRCUITSIGNAL_STOP_SEC_CODE
#include "MemMap.h"
/*End of L3_Temperature_Signal.c file*/