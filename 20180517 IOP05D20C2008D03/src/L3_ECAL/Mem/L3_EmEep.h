/*****************************************************************************
*   Copyright 2010 - 2011 
*   Co., Ltd., all rights reserved.
*
*   Filename:    .h
*
*   Description: This file is the C header file for EmEep
*
*   Revision History:
*
*   Date            Author          Description
*   ----------      ----------      -----------------------------------------
*   2016-10-28       JiaoYu         Initial created
*
*****************************************************************************/
#ifndef L3_EMEEP_H
#define L3_EMEEP_H  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_EmEep_Cfg.h"
#include "Std_Types.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/
#define BLOCK_PTR_PU8		((struct EMEEP_BLOCK0_Str*)ECAL_RAM_BEGIN_ADDR)

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
typedef enum
{
    e_EMEEP_IDLE,
    e_EMEEP_PROCESS
}EMEEP_PROCESS_STA_Enu;

typedef enum
{
    e_FLASH_IDLE,
    e_FLASH_ERASE,
    e_FLASH_WRITE
}EMEEP_FLUSH_STA_Enu;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/
#define BACKUPBLOCK(x)          (EmulationEep_Block_Str[x].BackupSize)
#define EMEEPSIZE(x)            (EmulationEep_Block_Str[x].EmeepSize)
#define EMEEPDATAPTR(x)         (EmulationEep_Block_Str[x].EmeepData_pu8)
#define EMEEPADDR(x)            (EmulationEep_Block_Str[x].BankBaseAddress)

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void EmEep_L3_Init(void);
extern void EmEep_L3_PowerDown(void);

#endif
/* End of L3_EmEep.h file*/

