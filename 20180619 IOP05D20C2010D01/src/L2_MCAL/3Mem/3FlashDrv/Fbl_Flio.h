/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     Fbl_Flio.h
*
* @brief    Flash I/O driver header file
*
************************************************************************************************
*   Revision History:
* 
*    Version       Date          Author         CR#      Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2013/09/23       CODER3         N/A         Original
*     
************************************************************************************************/

#ifndef __FBL_FLASH_IO_H
#define __FBL_FLASH_IO_H

#include "IoTypes.h"
#include "Fls.h"

#define V_API_NEAR

//extern IO_U8 V_INTERNAL_NEAR   flashCode[];

extern void* MEMCPY(void* dest, void* source, uint32 count);

uint8    FlashDriver_InitSync(void);
uint8    FlashDriver_RReadSync(IO_MemPtrType, IO_SizeType, IO_PositionType);
uint8    FlashDriver_RWriteSync(IO_MemPtrType, IO_SizeType, IO_PositionType);
uint8    FlashDriver_REraseSync(IO_SizeType, IO_PositionType);
uint8    FlashDriver_RReadSync(IO_MemPtrType, IO_SizeType, IO_PositionType);

#endif

/* End of file */

