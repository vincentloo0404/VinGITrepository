#ifndef L4_DTC_H
#define L4_DTC_H  

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L4_DTC_CFG.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
typedef struct  
{
   uint16 ErrCnt;
   uint16 *ConfirmCntTh;
   uint8  *CntIncStep;
   uint8  *CntDecStep;

}DTC_Check_Str;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void DTC_L4_vInit(void);
extern void DTC_L4_SetError(uint8 index);
extern void DTC_L4_ClrError(uint8 index);
extern uint8 DTC_L4_GetErrorSta(uint8 index);
extern uint8 DTC_L4_GetErrorStaB0(uint8 index);
extern uint8 DTC_L4_GetErrorStaB1(uint8 index);
extern void DTC_L4_Enable(uint8 index);
extern void DTC_L4_Disable(uint8 index);
extern uint8 DTC_L4_GetSta(uint8 index);
extern void DTC_L4_ClrSta(void);
extern void DTC_L4_POLLING_2ms(void);

#endif
/*End of L4_DTC.h file*/

