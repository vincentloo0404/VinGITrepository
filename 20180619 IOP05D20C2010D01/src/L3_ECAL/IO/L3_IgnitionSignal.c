
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_IgnitionSignal.h"
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

uint8 L3_S_IgnitionState_G_u08;

static uint16 L3_S_IgnVolt_Volt_F_u16p10;
static uint8 L3_S_IgnitionHWStateCnt_M_u08;

#define d_L3POWERCIRCUITSIGNAL_STOP_SEC_VAR
#include "MemMap.h"
/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3POWERCIRCUITSIGNAL_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     IgnitionSignalAbstarct_L3_Init
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void IgnitionSignalAbstarct_L3_Init(void)
{
   L3_S_IgnitionState_G_u08      = STD_ON;
   L3_S_IgnVolt_Volt_F_u16p10    = 0;
   L3_S_IgnitionHWStateCnt_M_u08 = 0;
}
/*****************************************************************************
*
*   Function:     IgnitionSignalAbstarct_L3_Per
*
*   Description:  This function is use to get the ignition state
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void IgnitionSignalAbstarct_L3_Per(void)
{
    /* get ign signal volt */
    L3_S_IgnVolt_Volt_F_u16p10 = (uint16)((((uint32)L3_S_IgnVolt_Ct_G_u16) * 22938) >> 10);
    
   // Vad = IGN * 6.81/(6.81+23.7); 
    
    /* hardware signal */
    if(L3_S_IgnitionState_G_u08 == STD_ON)
    {
    	if(L3_S_IgnVolt_Volt_F_u16p10 < k_S_IgnOffVoltThre_Volt_u16p10)
    	{
    		if(L3_S_IgnitionHWStateCnt_M_u08++ >= k_S_IgnOffTimeOut_Ct_u08)
    		{
    			L3_S_IgnitionState_G_u08 = STD_OFF;
    			L3_S_IgnitionHWStateCnt_M_u08 = 0;
    		}
    		else
    		{
    			
    		}
    	}
    	else
    	{
    		L3_S_IgnitionHWStateCnt_M_u08 = 0;
    	}
    }
    else
    {
    	if(L3_S_IgnVolt_Volt_F_u16p10 >= k_S_IgnOnVoltThre_Volt_u16p10)
    	{
    		if(L3_S_IgnitionHWStateCnt_M_u08++ >= k_S_IgnOnTimeOut_Ct_u08)
    		{
    			L3_S_IgnitionState_G_u08 = STD_ON;
    			L3_S_IgnitionHWStateCnt_M_u08 = 0;
    		}
    		else
    		{
    			
    		}
    	}
    	else
    	{
    		L3_S_IgnitionHWStateCnt_M_u08 = 0;
    	}    	
    }
    
    if(k_N_IgnOvrEn_Uls_u08 != 0)
    {
    	L3_S_IgnitionState_G_u08 = k_N_IgnOvrVal_Uls_u08;
    }
}
#define d_L3POWERCIRCUITSIGNAL_STOP_SEC_CODE
#include "MemMap.h"
/*End of L3_Ignition_Signal.c file*/