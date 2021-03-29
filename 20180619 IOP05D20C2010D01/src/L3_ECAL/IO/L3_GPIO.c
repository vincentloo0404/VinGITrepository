
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_GPIO.h"
/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

void setGPIO( uint8* ctrGPIO,uint8* aliasGPIO,uint8 GpioState)
{
	*ctrGPIO = GpioState;
	*aliasGPIO = GpioState;
}


uint8 getGPIO(uint8 ctrGPIO)
{
	return ctrGPIO;
}
