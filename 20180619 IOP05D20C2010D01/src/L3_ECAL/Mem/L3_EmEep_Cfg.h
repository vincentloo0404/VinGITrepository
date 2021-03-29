#ifndef L3_EMEEP_CFG_H
#define L3_EMEEP_CFG_H  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/
/* EOL data address */
#define EOL_DATA_ROM_START_ADDR           (0x00808000U)
#define EOL_DATA_RAM_START_ADDR           (0x40001A00U)

#define EOL_DATA_RAM_LEN                  (0x200)        /*512 Bytes*/

#define EOL_WRITE_EN_START_ADDR     	  	  (EOL_DATA_RAM_START_ADDR + 0x200 - 2) //0x40001BFE

/* EOL data address */
#define DTC_DATA_ROM_START_ADDR           (0x0080C000U)
#define DTC_DATA_RAM_START_ADDR           (0x40001C00U)

#define DTC_DATA_RAM_LEN                  (0x200)        /*512 Bytes*/

#define DTC_DATA_ROM_EXIST_FLG(index)     (*(uint16*)(DTC_DATA_ROM_START_ADDR + DTC_DATA_RAM_LEN*(index) - 2))
#define DTC_DATA_RAM_EXIST_FLG            (*(uint16*)(DTC_DATA_RAM_START_ADDR + DTC_DATA_RAM_LEN - 2)) 

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
typedef enum
{
    e_TuningData_EMEEP,
    e_PrivateData_EMMEEP,
    e_EolData_EMMEEP,
    e_DtcData_EMMEEP,
    e_EMEEP_HANDLE
}EMEEP_BLOCK_INDEX_Enu;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern const uint16 CCITT_Ttab[256];
/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/

#endif
/* End of L3_EmEep.h file*/

