
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_SensorVoltageSignal.h"
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

uint16 L3_S_Sensor5V_Volt_G_u16p08;
uint16 L3_S_RslvVcc_Volt_G_u16p08;

#define d_L3POWERCIRCUITSIGNAL_STOP_SEC_VAR
#include "MemMap.h"
/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3POWERCIRCUITSIGNAL_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     BatteryPowerAbstarct_L3_Per
*
*   Description:  This function is use to get the battery power voltage
*
*   Inputs:       None
*
*   Outputs:      diagnosis state
*
*   Notes:
*
*****************************************************************************/
void SensorVoltageAbstract_L3_Init(void)
{
	L3_S_Sensor5V_Volt_G_u16p08 = 1280;
	
	L3_S_RslvVcc_Volt_G_u16p08 = (uint16)(12<<8);
}
/*****************************************************************************
*
*   Function:     BatteryPowerAbstarct_L3_Per
*
*   Description:  This function is use to get the battery power voltage
*
*   Inputs:       None
*
*   Outputs:      diagnosis state
*
*   Notes:
*
*****************************************************************************/
void SensorVoltageAbstract_L3_Per(void)
{

    L3_S_Sensor5V_Volt_G_u16p08 = (L3_S_Sensor5V_Ct_G_u16 * 5) >> 1 ;
    
    /* volt = Ct*5/1024*(4.7+20)/4.7 = Ct * 6.569 = Ct*210>>5 */
    L3_S_RslvVcc_Volt_G_u16p08 = (L3_S_RslvVcc_Ct_G_u16 * 210) >> 5 ;

}
#define d_L3POWERCIRCUITSIGNAL_STOP_SEC_CODE
#include "MemMap.h"
/*End of L3_Sensor_Voltage_Signal.c file*/
