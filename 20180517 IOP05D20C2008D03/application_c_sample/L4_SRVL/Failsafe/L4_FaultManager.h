#ifndef L4_FAULTMANAGER_H
#define L4_FAULTMANAGER_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L4_SrvlFailsafe_CalData.h"
#include "L3_CAN.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
/*Type for System Fault*/
typedef enum
{
    System_No_Fault = 0,
    System_F1_Fault,
    System_F2_Fault,
    System_F3_Fault,
    System_F4_Fault,
    System_F5_Fault
} FM_SystemFault_Enu;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern FM_SystemFault_Enu L4_S_SysFaultState_Uls_G_Enu;

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void FM_L4_ColdInit(void);
extern void FM_L4_WarmInit(void);
extern void FM_L4_Per(void);
extern void FM_L4_ShutDown(void);

#endif 
/* End of L4_FaultManager.h file */
