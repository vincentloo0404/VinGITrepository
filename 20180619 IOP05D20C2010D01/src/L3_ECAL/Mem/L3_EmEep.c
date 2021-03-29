
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_EmEep.h"

/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/
#define FLASH_NONE			((UINT8)0)
#define FLASH_WRITE         ((UINT8)1)
#define FLASH_ERASE         ((UINT8)2)
#define FLASH_READ          ((UINT8)3)

/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3EEP_START_SEC_VAR      
#include "MemMap.h"

uint8 L3_S_EmEepCalib_En_G_u08[e_EMEEP_HANDLE];
EMEEP_PROCESS_STA_Enu L3_S_EmEepSta_Ct_G_enu;
uint8 L3_Index_G_u08;
uint8 L3_S_EmEepRedundCnt_Ct_G_a[e_EMEEP_HANDLE];
uint8 L3_S_EmEepFlash_Ct_G_Enu;

#define d_L3EEP_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3EEP_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     
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
static void DataCopy(void)
{
	
	#define CAL_DATA_FLASH_ADDR ((uint32)(0x00804000))
	#define CAL_DATA_RAM_ADDR   ((uint32)(0x40000100))
//	#define CAL_DATA_SIZE       (uint16)(0x1400)
	#define CAL_DATA_SIZE       (uint16)(0x1300)

	uint16 temp;
	
	//for(temp = 0; temp < 0x1400; temp++)
	for(temp = 0; temp < CAL_DATA_SIZE; temp++)
	{
		*((uint8*)(CAL_DATA_RAM_ADDR + temp)) = *((uint8*)(CAL_DATA_FLASH_ADDR + temp));
	}
	
}
/*****************************************************************************
*
*   Function:     
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
void EmEep_L3_Init(void)
{
	DataCopy();
}
/*****************************************************************************
*
*   Function:     Emeep_L3_BatteryLoss
*
*   Description:  When battery off,the main function which process data store.
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void EmEep_L3_PowerDown(void)
{

 // (void)StoreEolFlash();
 // (void)StoreDtcFlash();
	
}
#define d_L3EEP_STOP_SEC_CODE
#include "MemMap.h"

/*End of L3_EmEep.c file*/
