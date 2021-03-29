/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     Fbl_Flio.c
*
* @brief    Flash wrapped I/O driver
*
************************************************************************************************
*   Revision History:
* 
*    Version       Date          Author         CR#      Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2013/09/23       CODER3         N/A         Original
*     
************************************************************************************************/


#include <string.h>
#include "fbl_flio.h"
#include "iotypes.h"

/* Flash code buffer */
//vuint8 flashCode[FLASH_SIZE];

FunptrType FblWdFun = NULL_CALLBACK;

/******************************************************************************
* Function Name     : MEMCPY
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : dest              destination pointer
*
*                     source            source pointer
*
*                     count             data size
*
* Parameters(Out)   : None
*
* Description       : This function copy memory for RAM.
*
* Limitation        : None
******************************************************************************/
void* MEMCPY(void* dest, void* source, uint32 count)
{
    uint8* sd  = dest;
    uint8* ss  = source;

    while (count > 0)
    {
        *sd++ = *ss++;
        count--;
    }
    
    return(sd);
}
/******************************************************************************
* Function Name     : FlashDriver_InitSync
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : address           dummy parameter
*
* Parameters(Out)   : uint8      result
*
* Description       : This wrapped function initializes Flash driver.
*
* Limitation        : None
******************************************************************************/
uint8 V_API_NEAR FlashDriver_InitSync(void)
{
    Fls_Init();
    
    FblWdFun = NULL_CALLBACK;
    
    return(kFlashOk);
}
/******************************************************************************
* Function Name     : FlashDriver_RWriteSync
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : writeBuffer               write buffer pointer
*
*                     writeLength               write length
*
*                     writeAddress              write address
*
* Parameters(Out)   : uint8              result
*
* Description       : This wrapped function write data to Flash.
*
* Limitation        : None
******************************************************************************/
uint8 V_API_NEAR FlashDriver_RWriteSync(IO_MemPtrType   writeBuffer, 
                                               IO_SizeType     writeLength, 
                                               IO_PositionType writeAddress)
{

    uint8 returnCode; 

    if ((writeAddress & (IO_SizeType)(8 - 1)) != 0)
    {
        return(kFlashFailed);
    }
    
    
    returnCode = Fls_BlankCheck(writeAddress,writeLength,FblWdFun);
    
    if (returnCode != E_OK)
    {
        return(kFlashFailed);
    }
    
    returnCode = Fls_Write(writeAddress, writeBuffer, writeLength, FblWdFun);

    if (returnCode == E_OK)
    {
        returnCode = kFlashOk;
    }
    else 
    {
        returnCode = kFlashFailed;
    }
    
    return(returnCode);
}

/******************************************************************************
* Function Name     : FlashDriver_RWriteSync
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : writeBuffer               write buffer pointer
*
*                     writeLength               write length
*
*                     writeAddress              write address
*
* Parameters(Out)   : uint8              result
*
* Description       : This wrapped function write data to Flash.
*
* Limitation        : None
******************************************************************************/
uint8 FlashDriver_RBlankCheck(IO_PositionType writeAddress,
                                               IO_SizeType     writeLength)
{

    uint8 returnCode; 
    
    returnCode = Fls_BlankCheck(writeAddress,writeLength,FblWdFun);
    
    if (returnCode != E_OK)
    {
        return(kFlashFailed);
    }
    
    return(returnCode);
}
/******************************************************************************
* Function Name     : FlashDriver_REraseSync
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : eraseLength               erase length
*
*                     eraseAddress              erase address
*
* Parameters(Out)   : uint8              result
*
* Description       : This function erase data block of flash.
*
* Limitation        : None
******************************************************************************/
uint8 V_API_NEAR FlashDriver_REraseSync(IO_SizeType     eraseLength, 
                                               IO_PositionType eraseAddress)
{

    uint8 returnCode; 

    returnCode = Fls_Erase(eraseAddress, eraseLength, FblWdFun);

    if (returnCode == E_OK)
    {
        returnCode = kFlashOk;
    }
    else 
    {
        returnCode = kFlashFailed;
    }
    
    return(returnCode);
}
/******************************************************************************
* Function Name     : FlashDriver_RReadSync
*
* Sync/Async        : Synchronous
*
* Parameters(In)    : readBuffer                read buffer pointer
*
*                     readLength                read length
*
*                     readAddress               read address
*
* Parameters(Out)   : uint8              result
*
* Description       : This function read data from flash.
*
* Limitation        : None
******************************************************************************/
uint8 V_API_NEAR FlashDriver_RReadSync(IO_MemPtrType   readBuffer, 
                                              IO_SizeType     readLength, 
                                              IO_PositionType readAddress)
{
    (void)MEMCPY(readBuffer, (IO_U8 *)readAddress, readLength);
    
    return(IO_E_OK);
}
/* End of file */