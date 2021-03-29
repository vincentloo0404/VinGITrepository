/******************************************************************************
*
* ChuangQu Tech Inc.
* (c) Copyright 2016 ChuangQu Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     Fls.c
*
* @brief    SSD flash driver wrapped routine
*
************************************************************************************************
*   Revision History:
* 
*    Version       Date          Author         CR#      Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2016/08/04       CODER4         N/A         Original
*     
************************************************************************************************/
#include "Fls.h"

extern unsigned long        FlashInit_C[93];
extern unsigned long        FlashErase_C[131];
extern unsigned long        FlashProgram_C[194];
extern unsigned long        GetLock_C[64];
extern unsigned long        SetLock_C[66];

extern const unsigned long  kFlashInit_C[93];
extern const unsigned long  kFlashErase_C[131];
extern const unsigned long  kFlashProgram_C[194];
extern const unsigned long  kGetLock_C[64];
extern const unsigned long  kSetLock_C[66];

/* Pointer to Flash intialization function entry code */
pFLASHINIT                  pFlashInit                  = (pFLASHINIT)FlashInit_C;
/* Pointer to Flash erase function entry code */
pFLASHERASE                 pFlashErase                 = (pFLASHERASE)FlashErase_C;
/* Pointer to Flash program function entry code */
pFLASHPROGRAM               pFlashProgram               = (pFLASHPROGRAM)FlashProgram_C;

/* Pointer to Flash erase function entry code */
//pFLASHERASE                 pFlashErase                 = ((pFLASHERASE)(Flash_FlashErase_C_Addr));
/* Pointer to Flash program function entry code */
//pFLASHPROGRAM               pFlashProgram               = ((pFLASHPROGRAM)(Flash_FlashProgram_C_Addr));


/* Pointer to Flash get lock function entry code */
pGETLOCK                    pGetLock                    = (pGETLOCK)GetLock_C;
/* Pointer to Flash set lock function entry code */
pSETLOCK                    pSetLock                    = (pSETLOCK)SetLock_C;

/* SSD configuraion */
SSD_CONFIG                  ssdConfig                   =
{
    C90FL_REG_BASE,         
    MAIN_ARRAY_BASE,        
    0,                      
    SHADOW_ROW_BASE,        
    SHADOW_ROW_SIZE,        
    0,                      
    0,                      
    0,                      
    FLASH_PAGE_SIZE,        
    FALSE                   
};

/* SSD data configuraion */
SSD_CONFIG                  ssdDataConfig                   =
{
    C90FL_DATA_REG_BASE,    
    MAIN_DATA_ARRAY_BASE,   
    0,                      
    0,                      
    0,                      
    0,                      
    0,                      
    0,                      
    FLASH_PAGE_SIZE,        
    FALSE                   
};

/* Flash sector map */
Fls_SectorType              Fls_Sector[FLS_SECTOR_NUM]  =
{
    {
        0x00000000ul,
        0x00008000ul
    },
    
    {
        0x00008000ul,
        0x00004000ul
    },
    
    {
        0x0000c000ul,
        0x00004000ul
    },
    
    {
        0x00010000ul,
        0x00008000ul
    },
    
    {
        0x00018000ul,
        0x00008000ul
    },
    
    {
        0x00020000ul,
        0x00020000ul
    },
    
    {
        0x00040000ul,
        0x00020000ul
    },
    
    {
        0x00060000ul,
        0x00020000ul
    },
    
    {
        0x00800000ul,
        0x00004000ul
    },
    
    {
        0x00804000ul,
        0x00004000ul
    },
    
    {
        0x00808000ul,
        0x00004000ul
    },
    
    {
        0x0080C000ul,
        0x00004000ul
    }

};



/******************************************************************************
* Function Name     : Fls_GetSectorNum
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : phyaddr           physical address
*
*                     sectornum         sector number
*
* Parameters(Out)   : uint8             result
*
* Description       : Get Flash sector number.
*
* Limitation        : None
******************************************************************************/
static uint8 Fls_GetSectorNum(uint32 phyaddr, uint8* sectornum)
{
    uint8   tem = E_NOT_OK;
    uint8   i   = 0;

    for (i = 0; i < FLS_SECTOR_NUM; i++)
    {
        if (   (phyaddr >= Fls_Sector[i].startaddress) 
            && (phyaddr < Fls_Sector[i].startaddress + Fls_Sector[i].length))
        {
            *sectornum = i;
            tem = E_OK;
        }
    }

    return tem;
}

void Fls_DrvClear(void)
{
    uint32  index;
    
    for (index = 0; index < FLS_INIT_L; index++)
    {
        FlashInit_C[index] = 0;
    };
    
    for (index = 0; index < FLS_GETLOCK_L; index++)
    {
        GetLock_C[index] = 0;
    };
    
    for (index = 0; index < FLS_SETLOCK_L; index++)
    {
        SetLock_C[index] = 0;
    };

    for (index = 0; index < FLS_ERASE_L; index++)
    {
        FlashErase_C[index] = 0;
    };
    
    for (index = 0; index < FLS_PROGRAM_L; index++)
    {
        FlashProgram_C[index] = 0;
    };
  }


/******************************************************************************
* Function Name     : Fls_Init
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : None
*
* Parameters(Out)   : None
*
* Description       : This function initializes Flash driver.
*
* Limitation        : None
******************************************************************************/
void Fls_Init(void)
{
    uint32  index;
    
    #if 0
    for (index = 0; index < FLS_INIT_L; index++)
    {
        FlashInit_C[index] = kFlashInit_C[index];
    };
    
    for (index = 0; index < FLS_GETLOCK_L; index++)
    {
        GetLock_C[index] = kGetLock_C[index];
    };
    
    for (index = 0; index < FLS_SETLOCK_L; index++)
    {
        SetLock_C[index] = kSetLock_C[index];
    };

    for (index = 0; index < FLS_ERASE_L; index++)
    {
        FlashErase_C[index] = kFlashErase_C[index];
    };
    
    for (index = 0; index < FLS_PROGRAM_L; index++)
    {
        FlashProgram_C[index] = kFlashProgram_C[index];
    };
    
    #endif

    (void)pFlashInit(&ssdConfig);
    (void)pFlashInit(&ssdDataConfig);

    (void)pSetLock(&ssdConfig, LOCK_SHADOW_PRIMARY,   1, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_SHADOW_SECONDARY, 1, FLASH_SLMLR_PASSWORD);
   
    (void)pSetLock(&ssdConfig, LOCK_LOW_PRIMARY,   0, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_LOW_SECONDARY, 0, FLASH_SLMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_MID_PRIMARY,   0, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_MID_SECONDARY, 0, FLASH_SLMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_HIGH,          0, FLASH_HLR_PASSWORD);
    
    (void)pSetLock(&ssdDataConfig, LOCK_LOW_PRIMARY,   0, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdDataConfig, LOCK_LOW_SECONDARY, 0, FLASH_SLMLR_PASSWORD);
}



/******************************************************************************
* Function Name     : Fls_Read
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : SourceAddress                 read buffer pointer
*
*                     Length                        read length
*
*                     SourceAddress                 read address
*
* Parameters(Out)   : Std_ReturnType                result
*
* Description       : This function read data from flash.
*
* Limitation        : None
******************************************************************************/
Std_ReturnType Fls_Read(uint8* TargetAddressPtr, Fls_AddressType SourceAddress, Fls_LengthType Length)
{
    Std_ReturnType  ret = E_OK;
    uint32          i   = 0;
    
    for (i = 0; i < Length; i++)
    {
        TargetAddressPtr[i] = ((uint8 *)SourceAddress)[i];
    }
    return ret;
}



/******************************************************************************
* Function Name     : Fls_Write
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : SourceAddressPtr              write buffer pointer
*
*                     Length                        write length
*
*                     TargetAddress                 write address
*
*                     funp                          callback function pointer
*
* Parameters(Out)   : Std_ReturnType                result
*
* Description       : This function write data to Flash.
*
* Limitation        : None
******************************************************************************/
Std_ReturnType Fls_Write (Fls_AddressType TargetAddress, 
                          const uint8*    SourceAddressPtr, 
                          Fls_LengthType  Length, 
                          FunptrType      funp)
{
    static uint8    alignedbuffer[8];
    Std_ReturnType  ret         = E_OK;
    uint8           sectornum   = 0;
    uint32          destaddress = TargetAddress;
    uint32          srcaddress  = (uint32)SourceAddressPtr;
    uint32          head        = TargetAddress % 8;
    uint32          tail        = (TargetAddress + Length) % 8;
    uint32          buffernum   = (Length - tail + head - 8) / 8; 
    uint8           indexh      = 0;
    uint32          ssdRet      = 0;


    if (E_OK == Fls_GetSectorNum(destaddress, &sectornum))
    {
        indexh = 0;
        
        while (indexh < head)
        {
            ((uint8 *)alignedbuffer)[indexh] = 0xff;
            indexh++;
        }
        
        for (indexh = 0; indexh < (8 - head); indexh++)
        {
            ((uint8 *)alignedbuffer)[indexh + head] = ((uint8 *)srcaddress)[indexh];
        }

        if ((destaddress - head) >= 0x00800000)
        {
             ssdRet = pFlashProgram(&ssdDataConfig, (destaddress - head), 8, (uint32)alignedbuffer, funp);
        }
        else
        {
             ssdRet = pFlashProgram(&ssdConfig, (destaddress - head), 8, (uint32)alignedbuffer, funp);
        }

        if (C90FL_OK != ssdRet)
        {
            ret = E_NOT_OK;
        }

        destaddress = destaddress - head + 8;
        srcaddress = srcaddress - head + 8;

        if (destaddress < TargetAddress + Length)
        {
            while (buffernum > 0)
            {
                for (indexh = 0; indexh < 8; indexh++)
                {
                    ((uint8 *)alignedbuffer)[indexh] = ((uint8 *)srcaddress)[indexh];
                }
                
                if (destaddress > 0x00800000)
                {
                    ssdRet = pFlashProgram(&ssdDataConfig, destaddress, 8, (uint32)alignedbuffer, funp);
                }
                else
                {
                   ssdRet = pFlashProgram(&ssdConfig, destaddress, 8, (uint32)alignedbuffer, funp);
                }
                
                if (C90FL_OK != ssdRet)
                {
                    ret = E_NOT_OK;
                }
                
                destaddress += 8;
                srcaddress += 8;
                buffernum--;
            }
        }

        if (destaddress < TargetAddress + Length)
        {
            if (0 != tail)
            {
                for (indexh = 0; indexh < tail; indexh++)
                {
                    ((uint8 *)alignedbuffer)[indexh] = ((uint8 *)srcaddress)[indexh];
                }
                
                for (indexh = 0; indexh < (8 - tail); indexh++)
                {
                    ((uint8 *)alignedbuffer)[indexh + tail] = 0xff;
                }
                
                if (destaddress > 0x00800000)
                {
                    ssdRet = pFlashProgram(&ssdDataConfig, destaddress, 8, (uint32)alignedbuffer, funp);
                }
                else
                {
                   ssdRet = pFlashProgram(&ssdConfig, destaddress, 8, (uint32)alignedbuffer, funp);
                }

                if (C90FL_OK != ssdRet)
                {
                    ret = E_NOT_OK;
                }
            }
        }
    }
    else  
    {
        ret = E_NOT_OK;
    } 

    return ret;
}

void Callback(void)
{
	uint32 g_counter = 0; 

   g_counter++;
}


/******************************************************************************
* Function Name     : Fls_Erase
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : Length                    erase length
*
*                     TargetAddress             erase address
*
*                     funp                      callback function pointer
*
* Parameters(Out)   : Std_ReturnType            result
*
* Description       : This function erase data block of flash.
*
* Limitation        : None
******************************************************************************/
Std_ReturnType Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length, FunptrType funp)
{
    Std_ReturnType  ret         = E_NOT_OK;
    uint8           sectornum   = 0;
    uint32          lowEnabledBlocks = 0;     
    uint32          midEnabledBlocks = 0;     

    if (E_OK == Fls_GetSectorNum(TargetAddress, &sectornum))
    {
        if (Length == (Fls_Sector[sectornum].length))
        {
            if (sectornum < FLS_MID_SECTOR_NUM_START)
            {
                lowEnabledBlocks = 0x00000001 << (sectornum);
                midEnabledBlocks = 0x00000000;
                
                if (C90FL_OK == pFlashErase(&ssdConfig, FALSE, lowEnabledBlocks, midEnabledBlocks, 0x00000000, funp))
//			if (C90FL_OK == pFlashErase(&ssdConfig, FALSE, lowEnabledBlocks, midEnabledBlocks, 0x00000000, &Callback))
			{
                    ret = E_OK;
                }
            }
            else if ((sectornum >= FLS_MID_SECTOR_NUM_START) && (sectornum < 8))
            {
                lowEnabledBlocks = 0x00000000 ;
                midEnabledBlocks = 0x00000001 << (sectornum - FLS_MID_SECTOR_NUM_START);
                
                if (C90FL_OK == pFlashErase(&ssdConfig, FALSE, lowEnabledBlocks, midEnabledBlocks, 0x00000000, funp))
//				if (C90FL_OK == pFlashErase(&ssdConfig, FALSE, lowEnabledBlocks, midEnabledBlocks, 0x00000000, &Callback))
                {
                    ret = E_OK;
                }
            }
            else 
            {
                lowEnabledBlocks = 0x00000001 << (sectornum - 8);
                midEnabledBlocks = 0x00000000;
                if (C90FL_OK == pFlashErase(&ssdDataConfig, FALSE, lowEnabledBlocks, midEnabledBlocks, 0x00000000, funp))
                {
                    ret = E_OK;
                }
            }
//			 else //add by ych modify for Callback for watchdog not work
//            {

				//lowEnabledBlocks = (0xFFFFFFFF >> (32 - ssdDataConfig.lowBlockNum));
    			//midEnabledBlocks = 0x00000000;

//				lowEnabledBlocks = 0x00000001 << (sectornum - 8);
// 				midEnabledBlocks = 0x00000000;

                /* Select all blocks in low addr space */
			     //lowEnabledBlocks = 0x0000000F;
			     //midEnabledBlocks = 0x00000000;
//                if (C90FL_OK == pFlashErase(&ssdDataConfig, FALSE, lowEnabledBlocks, midEnabledBlocks, 0x00000000, &Callback ))
//                {
//                    ret = E_OK;
//                }
//            }
        }
    }
    
    return ret;
}

/* End of file */

