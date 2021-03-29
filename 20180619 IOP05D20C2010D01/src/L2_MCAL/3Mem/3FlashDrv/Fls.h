/******************************************************************************
*
* ChuangQu Tech Inc.
* (c) Copyright 2016 ChuangQu Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     Fls.h
*
* @brief    SSD flash driver wrapped routine header file
*
************************************************************************************************
*   Revision History:
* 
*    Version       Date          Author         CR#      Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2016/08/04       CODER4         N/A         Original
*     
************************************************************************************************/
#ifndef _FLS_H_
#define _FLS_H_

#include "typedefs.h"
#include "std_types.h"
#include "5604P_fls.h"





typedef void (*FunptrType) (void);
typedef uint32  Fls_AddressType;
typedef uint32  Fls_LengthType;

/**modify by ych 20160908 start***/
#ifndef UDS_FBL_Fls_SectorType_MACRO


#define UDS_FBL_Fls_SectorType_MACRO

typedef struct
{
    uint32  startaddress;
    uint32  length;
}Fls_SectorType;
#endif 
/**modify by ych 20160908 end ***/

#define FLS_SECTOR_NUM                  12u
#define FLS_LOW_SECTOR_NUM_START        0u
#define FLS_MID_SECTOR_NUM_START        6u

#define FLS_ERASE_L                     131
#define FLS_INIT_L                      95
#define FLS_PROGRAM_L                   194
#define FLS_GETLOCK_L                   64
#define FLS_SETLOCK_L                   66

#define kFlashOk                        0x00000000  
#define kFlashFailed                    0x00000001  

#define FLASH_SEGMENT_SIZE              8

typedef unsigned short  Fls_ErrType;


extern void             Fls_Init(void);
extern Std_ReturnType   Fls_Read(uint8* TargetAddressPtr, Fls_AddressType SourceAddress, Fls_LengthType Length);
extern Std_ReturnType   Fls_Write(Fls_AddressType TargetAddress, const uint8* SourceAddressPtr, Fls_LengthType Length, FunptrType funp);
extern Std_ReturnType   Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length, FunptrType funp);

extern Fls_SectorType              Fls_Sector[];
#endif

/* End of file */

