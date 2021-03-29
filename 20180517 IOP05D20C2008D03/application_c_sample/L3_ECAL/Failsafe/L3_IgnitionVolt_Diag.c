
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_IgnitionVolt_Diag.h"

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
//static void FS_L3_SensorVoltLow(void);
//static void FS_L3_SensorVoltHigh(void);

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
#define d_L3IGNITIONVOLTDIAG_START_SEC_VAR
#include "MemMap.h"

/* Igniton voltage diagnostic */
static uint8 L3_N_IgnVoltDiagResult_Uls_G_u08;
static uint16 L3_N_IgnVoltErrCnt_Ct_F_u16;

#define d_L3IGNITIONVOLTDIAG_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3IGNITIONVOLTDIAG_START_SEC_VAR
#include "MemMap.h"


#define d_L3IGNITIONVOLTDIAG_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3IGNITIONVOLTDIAG_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************
*
*   Function:     FS_L4_VehSpeedDiagInit
*
*   Description:  扭矩传感器供电电压诊断初始化函数
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FS_L3_IgnitionVoltDiagInit(void)
{
	L3_N_IgnVoltDiagResult_Uls_G_u08 = FALSE;

	L3_N_IgnVoltErrCnt_Ct_F_u16 = 0;
}
/*****************************************************************************
*
*   Function:     FS_L3_IgnitionVoltDiagPer
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
void FS_L3_IgnitionVoltDiagPer(void)
{
}
#define d_L3IGNITIONVOLTDIAG_STOP_SEC_CODE
#include "MemMap.h"

/*End of L3_IgnitionVolt_Diag.c file */

