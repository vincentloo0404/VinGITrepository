
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_VoltSignal.h"
#include "L3_VoltSignal_Cfg.h"

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
#define d_L3VOLTSIGNAL_START_ABSOLUTE_ADDRESS_VAR
#include "MemMap.h"

#define d_L3VOLTSIGNAL_STOP_ABSOLUTE_ADDRESS_VAR
#include "MemMap.h"

#define d_L3VOLTSIGNAL_START_SEC_VAR
#include "MemMap.h"

/* signal */
uint16 L3_S_BatCmmVolt_Volt_G_u16p08;
uint16 L3_S_BatCmmVolt_Volt_G_u16p10;
uint16 L3_S_BatMosVolt_Volt_G_u16p10;

uint16 L3_N_RlyCoilVolt_Volt_G_u16p10;

#define d_L3VOLTSIGNAL_STOP_SEC_VAR
#include "MemMap.h"
/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3VOLTSIGNAL_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     MotorCurrentSignalAbstract_L3_Init
*
*   Description:  This function is use to Initial the Motor Current Signal
*
*   Inputs:       None
*
*   Outputs:      Ecu diagnosis variable pointer
*
*   Notes:
*
*****************************************************************************/
void VoltSignalAbstract_L3_Init(void)
{
  /* signal */
  L3_S_BatCmmVolt_Volt_G_u16p10 = 12288;
  L3_S_BatCmmVolt_Volt_G_u16p08 = 3072;
  L3_S_BatMosVolt_Volt_G_u16p10 = 0;
}
/*****************************************************************************
*
*   Function:     MotorCurrentSignal_L3_Abstract
*
*   Description:  This function is use to abstract the Motor Current Signal
*
*   Inputs:       Ecu diagnosis variable pointer
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void VoltSignalAbstract_L3_Per(void)
{
   /* battery Volt */
   L3_S_BatCmmVolt_Volt_G_u16p08 = (uint16)((((uint32)L3_S_BatCmmVolt_Ct_G_u16) * 22938) >> 12);
   L3_S_BatCmmVolt_Volt_G_u16p10 = (uint16)((((uint32)L3_S_BatCmmVolt_Ct_G_u16) * 22938) >> 10);
   L3_S_BatMosVolt_Volt_G_u16p10 = (uint16)((((uint32)L3_S_BatMosVolt_Ct_G_u16) * 22938) >> 10);

   // Vad = volt * 6.81/(6.81+23.7); 

   /* relay coil */
   L3_N_RlyCoilVolt_Volt_G_u16p10 = (uint16)((((uint16)L3_S_RlyCoil_Ct_G_u16) * 5) );
}

#define d_L3VOLTSIGNAL_STOP_SEC_CODE
#include "MemMap.h"
/*End of L3_Motor_Current_Signal.c file*/