/******************************************************************************
*
* ChuangQu Tech Inc.
* (c) Copyright 2016 ChuangQu Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     5604P_fls.h
*
* @brief    MPC5604P flash driver header
*
************************************************************************************************
*   Revision History:
* 
*    Version       Date          Author         CR#      Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2016/08/04       CODER4         N/A         Original
*     
************************************************************************************************/

#ifndef _5604P_FLS_H_
#define _5604P_FLS_H_

#include "Std_Types.h"
#include "ssd_c90fl.h"

#define C90FL_REG_BASE                  0xC3F88000
#define C90FL_DATA_REG_BASE             0xC3F8C000
#define MAIN_ARRAY_BASE                 0x00000000
#define MAIN_DATA_ARRAY_BASE            0x00800000

#define SHADOW_ROW_BASE                 0x00200000
#define SHADOW_ROW_SIZE                 0x00004000
#define FLASH_PAGE_SIZE                 C90FL_PAGE_SIZE_08

#define BUFFER_SIZE_BYTE                0x100

#define OFFSET_LOW_BLOCK0               0x0000  
#define LOW_BLOCK0_SIZE                 0x8000  

#define OFFSET_LOW_BLOCK1               0x8000  
#define LOW_BLOCK1_SIZE                 0x4000  

#define OFFSET_LOW_BLOCK2               0xC000  
#define LOW_BLOCK2_SIZE                 0x4000  

#define OFFSET_LOW_BLOCK3               0x10000 
#define LOW_BLOCK3_SIZE                 0x8000  

#define OFFSET_LOW_BLOCK4               0x18000 
#define LOW_BLOCK4_SIZE                 0x8000  

#define OFFSET_LOW_BLOCK5               0x20000 
#define LOW_BLOCK5_SIZE                 0x20000 

#define OFFSET_MID_BLOCK6               0x40000 
#define MID_BLOCK6_SIZE                 0x20000 

#define OFFSET_MID_BLOCK7               0x60000 
#define MID_BLOCK7_SIZE                 0x20000 

#define FLASH_ARRAY_SIZE                0x80000 


#define OFFSET_LOW_DATA_BLOCK0          0x800000  
#define LOW_DATA_BLOCK0_SIZE            0x4000    

#define OFFSET_LOW_DATA_BLOCK1          0x804000  
#define LOW_DATA_BLOCK1_SIZE            0x4000    

#define OFFSET_LOW_DATA_BLOCK2          0x808000  
#define LOW_DATA_BLOCK2_SIZE            0x4000    

#define OFFSET_LOW_DATA_BLOCK3          0x80C000  
#define LOW_DATA_BLOCK3_SIZE            0x4000    

#define DATA_FLASH_ARRAY_SIZE           0x10000   

#define FLASH_LMLR_PASSWORD             0xA1A11111  
#define FLASH_SLMLR_PASSWORD            0xC3C33333  
#define FLASH_HLR_PASSWORD              0xB2B22222  



#endif

/* End of file */

