/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_EEPROM_Drv.c
*
* @brief    DataFlash Module emulate EEPROM Function, Store and Erase
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/05/22      CODER2       	   	N/A          Original
*     1.1        2013/06/07      CODER2       	   	N/A          Delete Stc_Value input, Add Ext_WatchDog Hook
*     1.2        2013/06/19      CODER2       	   	N/A          Modify Write Function, in case of no Data in EEPROM
*******************************************************************************/
#ifndef M_EEPROM_DRV_C
#define M_EEPROM_DRV_C
#endif


/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_EEPROM_Drv.h"
#include 	"m_EEPROM_Cfg.h"


/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mEEPROM_Init
   Description:     EEPROM Function Init
   Parameters:      Input:		
                    Output:
		                    EEPROM_OK,	success
		                    another,	failed
   Notes:           EEPROM_OK = 0
                   
   ***************************************************************************** */
INT8U	mEEPROM_Init(void)
{
	return(mFlash_Init());
}


/* *****************************************************************************
   Function:        mEEPROM_Read_Flash
   Description:     Read from EEPROM and store in *pArray_DTC
   Parameters:      Input:	*pArray_DTC:	Array of information , read from EEPROM
                    Output:
		                    EEPROM_OK,	success
		                    others,	failed
   Notes:           EEPROM_OK = 0
                   
   ***************************************************************************** */
INT8U	mEEPROM_Read_Flash(INT32U *pArray_DTC)
{
	INT8U	RetValue;
	INT8U	i = 0;
	INT32U	u32Address;
	INT32U	u32Index;
	INT32U	u32CurrIndex = 0;
	INT32U	u32CurrAddress = EEPROM_BLOCK_ADDR_1;
	
	RetValue = EEPROM_OK;
	
	/* Check in EEPROM_BLOCK_1 */
	for(i=0; i<(EEPROM_ERASE_SIZE/EEPROM_BLOCK_STORE_SIZE); i++)
	{
		/* check First 8 bytes for no blank Info Header */
		u32Address = EEPROM_BLOCK_ADDR_1 + i*EEPROM_BLOCK_STORE_SIZE;
		
		if(*(INT64U *)u32Address == EEPROM_DWORD_MASK )
		{
			;	/* do nothing (continue) */
		}
		else
		{
			/* Avavilable Info Header, then Check Index */
			u32Index = *(INT32U *)(u32Address + EEPROM_INDEX_OFFSET);
			
			if(	(0x0 != u32Index) 					&& 		/* Avavilable */
				(EEPROM_WORD_MASK != u32Index)		&&		/* not blank (0xFF) */
				(u32Index > u32CurrIndex)  )				/* More Latest */
			{
				u32CurrAddress	= u32Address;
				u32CurrIndex	= u32Index;
			}
			else
			{
				;/* do nothing */
			}
		}			
	}
	
	/* Check in EEPROM_BLOCK_2 */
	for(i=0; i<(EEPROM_ERASE_SIZE/EEPROM_BLOCK_STORE_SIZE); i++)
	{
		/* check First 8 bytes for no blank Info Header */
		u32Address = EEPROM_BLOCK_ADDR_2 + i*EEPROM_BLOCK_STORE_SIZE;
		
		if(*(INT64U *)u32Address == EEPROM_DWORD_MASK )
		{
			;	/* do nothing (continue) */
		}
		else
		{
			/* Avavilable Info Header, then Check Index */
			u32Index = *(INT32U *)(u32Address + EEPROM_INDEX_OFFSET);
			
			if(	(0x0 != u32Index) 					&& 		/* Avavilable */
				(EEPROM_WORD_MASK != u32Index)		&&		/* not blank (0xFF) */
				(u32Index > u32CurrIndex)  )				/* More Latest */
			{
				u32CurrAddress	= u32Address;
				u32CurrIndex	= u32Index;
			}
			else
			{
				;/* do nothing */
			}
		}			
	}

	/* if new Index available and exit */
	if(0x0 != u32CurrIndex)
	{
		Memory_Copy_Src_to_Dest((void *)pArray_DTC, (void *)(u32CurrAddress), EEPROM_WRITE_SIZE);
	}
	else
	{
		RetValue = EEPROM_ADDR_NO_FOUND;
	}

	return(RetValue);	
}


/* *****************************************************************************
   Function:        mEEPROM_Update_StoreAddress
   Description:     Input Address and find Address available for Store information
   Parameters:      Input:	*pStoreState:	struct of Store State,
   							u32Address:		Last information's Address
                    Output:
		                    EEPROM_OK,	success
		                    others,		failed
   Notes:           EEPROM_OK = 0
                   
   ***************************************************************************** */
static	INT8U	mEEPROM_Update_StoreAddress(stc_EEPROM_StoreStatus *pStoreState, INT32U	u32Address)
{
	INT8U	RetValue;
	INT16U	i;
	
	/* Address located in Block_1, then rest all need to check */
	if(pStoreState -> StoreAddr < EEPROM_BLOCK_ADDR_2)
	{
		for(i= 1; i<(EEPROM_BLOCK_ADDR_1+EEPROM_BLOCK_SIZE_ALL- pStoreState->StoreAddr)/EEPROM_BLOCK_STORE_SIZE; i++)
		{
			u32Address = pStoreState -> StoreAddr + i*EEPROM_BLOCK_STORE_SIZE;
			/* Blank Check */
			if(EEPROM_OK == mFlash_BlankCheck(u32Address, EEPROM_BLOCK_STORE_SIZE))
			{
				pStoreState -> StoreAddr = u32Address;	/* Location found */
				RetValue = EEPROM_OK;
				break;
			}
			else
			{
				;	/* do nothing */
			}
		}
	}
	/* Address is the last one, then all Block_1 all need to check */
	else if(pStoreState -> StoreAddr == EEPROM_BLOCK_ADDR_1 + EEPROM_BLOCK_SIZE_ALL - EEPROM_BLOCK_STORE_SIZE)
	{
		for(i= 0; i<(EEPROM_ERASE_SIZE)/EEPROM_BLOCK_STORE_SIZE; i++)
		{
			u32Address = EEPROM_BLOCK_ADDR_1 + i*EEPROM_BLOCK_STORE_SIZE;
			/* Blank Check */
			if(EEPROM_OK == mFlash_BlankCheck(u32Address, EEPROM_BLOCK_STORE_SIZE))
			{
				pStoreState -> StoreAddr = u32Address;	/* Location found */
				RetValue = EEPROM_OK;
				break;
			}
			else
			{
				;	/* do nothing */
			}
		}
				
	}
	/* Address located in Block_2, first check rest, then check Block_1 */
	else
	{
		for(i= 1; i<(EEPROM_BLOCK_ADDR_1+EEPROM_BLOCK_SIZE_ALL- pStoreState->StoreAddr)/EEPROM_BLOCK_STORE_SIZE; i++)
		{
			u32Address = pStoreState -> StoreAddr + i*EEPROM_BLOCK_STORE_SIZE;
			/* Blank Check */
			if(EEPROM_OK == mFlash_BlankCheck(u32Address, EEPROM_BLOCK_STORE_SIZE))
			{
				pStoreState -> StoreAddr = u32Address;	/* Location found */
				RetValue = EEPROM_OK;
				break;
			}
			else
			{
				;	/* do nothing */
			}
		}
		
		if(EEPROM_OK != RetValue)
		{
			for(i= 0; i<(EEPROM_ERASE_SIZE)/EEPROM_BLOCK_STORE_SIZE; i++)
			{
				u32Address = EEPROM_BLOCK_ADDR_1 + i*EEPROM_BLOCK_STORE_SIZE;
				/* Blank Check */
				if(EEPROM_OK == mFlash_BlankCheck(u32Address, EEPROM_BLOCK_STORE_SIZE))
				{
					pStoreState -> StoreAddr = u32Address;	/* Location found */
					RetValue = EEPROM_OK;
					break;
				}
				else
				{
					;	/* do nothing */
				}
			}
		}
		else
		{
			;	/* do nothing */
		}	
	}
	
}


/* *****************************************************************************
   Function:        mEEPROM_Write_Flash
   Description:     store information into EEPROM
   Parameters:      Input:	*pArray_Store:	Array of information , to be wriiten into EEPROM		
                    Output:
		                    EEPROM_OK,	success
		                    others,		failed
   Notes:           EEPROM_OK = 0
                   
   ***************************************************************************** */
/* extern	void	mEEPROM_Ext_WatchDog_Feed_Hook(void); */ /*chjguo debug */
   
INT8U	mEEPROM_Write_Flash(INT32U *pArray_Store)
{
	INT8U	RetValue;
	INT16U	i;
	INT32U	u32Address;
	INT32U	u32Index = 0;
	INT32U	StoreTmp[2];			/* CheckSum + Index, 8 Bytes */
	INT8U	blkLockEnabled;			/* block lock enabled state */
    INT32U	blkLockState;			/* block lock status to be retrieved */
    INT32U  *pArray_Tmp;
	stc_EEPROM_StoreStatus stcStoreState;
	
	/* (1) Update the Index to be written */
	Memory_Set_Dest((void *)&stcStoreState, 0x0, sizeof(stc_EEPROM_StoreStatus));
	for(i=0; i<(EEPROM_BLOCK_SIZE_ALL/EEPROM_BLOCK_STORE_SIZE); i++)
	{
		/* Search the Latest Index */
		u32Address = EEPROM_BLOCK_ADDR_1 + i*EEPROM_BLOCK_STORE_SIZE;
		
		/* Avavilable Info Header, then Check Index */
		u32Index = *(INT32U *)(u32Address + EEPROM_INDEX_OFFSET);

		if(	(0x0 != u32Index) 					&& 			/* Avavilable */
			(EEPROM_WORD_MASK != u32Index)		&&			/* not blank (0xFF) */
			(u32Index >= stcStoreState.StoreIndex)  )		/* More Latest */
		{
			/* new Index to be written */
			stcStoreState.StoreIndex	= u32Index + 1;
			stcStoreState.StoreAddr		= u32Address;
			stcStoreState.LastAddr		= u32Address;
			stcStoreState.ErrFlag		= EEPROM_ERRFLAG_DATA_FOUND;
		}
		else
		{
			;	/* do nothing */
		}	
	}
	
	/* in case of on data ever in EEPROM, then Init StoreAddr and LastAddr */
	if(EEPROM_ERRFLAG_DATA_FOUND == stcStoreState.ErrFlag)
	{
		stcStoreState.ErrFlag = 0;
	}
	else
	{
		/* no Data found, then Init StoreAddr and LastAddr */
		stcStoreState.StoreIndex	= 1;
		stcStoreState.StoreAddr		= EEPROM_BLOCK_ADDR_1;
		stcStoreState.LastAddr		= EEPROM_BLOCK_ADDR_1;
	}

	/* (2) Compare Data if they are the same */
	RetValue = EEPROM_COMPARE_SAME;
	pArray_Tmp = pArray_Store;
	for(i=0; i<EEPROM_WRITE_SIZE/4; i++)
	{
		if(*pArray_Tmp != *( INT32U *) (stcStoreState.LastAddr + 4*i))
		{
			RetValue = EEPROM_COMPARE_DIFF;
			break;
		}
		pArray_Tmp ++ ;
	}

	/* (3) Check for Flash Location Blank and not used after Updated Index */
	if(EEPROM_COMPARE_DIFF == RetValue)
	{
		RetValue = mEEPROM_Update_StoreAddress(&stcStoreState, u32Address);
	}
	else
	{
		;	/* return all, do not store */
	}

	/* (4) Store Data */
	if(EEPROM_OK == RetValue)
	{
		/* program main array */
		stcStoreState.WriteFlag = TRUE;	/* WriteFlag=false in Fail-Loop */
		stcStoreState.FailCount = 0;
		stcStoreState.ErrFlag	= EEPROM_OK;

		(void)mFlash_GetLock(FLASH_LOCK_LOW_PRIMARY, &blkLockEnabled, &blkLockState);
		(void)mFlash_SetLock(FLASH_LOCK_LOW_PRIMARY, (blkLockState & (~EEPROM_BLOCK_MASK)), FLASH_LML_PASSWORD);
		(void)mFlash_GetLock(FLASH_LOCK_LOW_SECONDARY, &blkLockEnabled, &blkLockState);
		(void)mFlash_SetLock(FLASH_LOCK_LOW_SECONDARY, (blkLockState & (~EEPROM_BLOCK_MASK)), FLASH_SLL_PASSWORD);

		/* do while Loop in case of Program Failed */
		do
		{
			pArray_Tmp = pArray_Store;
			/*	mEEPROM_Ext_WatchDog_Feed_Hook();	/* Ext WatchDog Feed in case MCU Reset  /* chjguo debug */
			RetValue = mFlash_DFlashProgram((INT32U)(stcStoreState.StoreAddr), EEPROM_WRITE_SIZE, (INT32U)pArray_Tmp);
			if(EEPROM_OK == RetValue)
			{
				/* Verify the programmed data */
				pArray_Tmp = pArray_Store;
				RetValue = mFlash_DFlashVerify((INT32U)(stcStoreState.StoreAddr), EEPROM_WRITE_SIZE, (INT32U)pArray_Tmp );
				stcStoreState.ErrFlag = RetValue;
			}
			else
			{
				/* Program Failed */
				stcStoreState.ErrFlag = RetValue;
			}
			
			
			/* Program Failed or Verify Failed */
			if(EEPROM_OK != stcStoreState.ErrFlag)
			{
				/* Index program 0 */
				StoreTmp[0] = 0;
				StoreTmp[1] = 0;
			/*	mEEPROM_Ext_WatchDog_Feed_Hook();	/* Ext WatchDog Feed in case MCU Reset /*chjguo debug */
				(void)mFlash_DFlashProgram((INT32U)(stcStoreState.StoreAddr + EEPROM_CHECKSUM_OFFSET), EEPROM_DWORD_SIZE, (INT32U)StoreTmp);	
				
				/* Update Store Address */
				(void)mEEPROM_Update_StoreAddress(&stcStoreState, u32Address);
				/* Failed Count +1 */
				stcStoreState.FailCount ++;
			}
			else
			{
				/* do nothing */
			}
		}
		while( ( EEPROM_OK != stcStoreState.ErrFlag) && (stcStoreState.FailCount < EEPROM_WRITE_RETRY_COUNT) );	
	}
	else
	{
		;	/* do nothing */
	}
	
	/* (5) Calculate CheckSum; if Program failed, CheckSum = 0, Index = 0 */
	if( (EEPROM_OK == RetValue) && (TRUE == stcStoreState.WriteFlag) )
	{
		RetValue = mFlash_CheckSum((INT32U)(stcStoreState.StoreAddr), EEPROM_WRITE_SIZE, &(stcStoreState.CheckSum));
		if(EEPROM_OK == RetValue)
		{
			StoreTmp[0] = stcStoreState.CheckSum;
			StoreTmp[1] = stcStoreState.StoreIndex;
		}
		else
		{
			/* CheckSum Failed */
			StoreTmp[0] = 0;
			StoreTmp[1] = 0;
		}
	}
	else
	{
		/* if Program failed, CheckSum = 0, Index = 0 */
		StoreTmp[0] = 0;
		StoreTmp[1] = 0;
	}
	
	
	/* (6) Program CheckSum and Index (Write Index no matter Data available or not) */ 
	/* But, Program Index cannot be reWritten */
	if( TRUE == stcStoreState.WriteFlag )
	{
		(void)mFlash_GetLock(FLASH_LOCK_LOW_PRIMARY, &blkLockEnabled, &blkLockState);
		(void)mFlash_SetLock(FLASH_LOCK_LOW_PRIMARY, (blkLockState & (~EEPROM_BLOCK_MASK)), FLASH_LML_PASSWORD);
		(void)mFlash_GetLock(FLASH_LOCK_LOW_SECONDARY, &blkLockEnabled, &blkLockState);
		(void)mFlash_SetLock(FLASH_LOCK_LOW_SECONDARY, (blkLockState & (~EEPROM_BLOCK_MASK)), FLASH_SLL_PASSWORD);

	/*	mEEPROM_Ext_WatchDog_Feed_Hook();	/* Ext WatchDog Feed in case MCU Reset  /*chjguo debug */
		RetValue = mFlash_DFlashProgram((INT32U)(stcStoreState.StoreAddr + EEPROM_CHECKSUM_OFFSET), EEPROM_DWORD_SIZE, (INT32U)StoreTmp);	
		if(EEPROM_OK == RetValue)
		{
			/* Verify the programmed data */
			RetValue = mFlash_DFlashVerify((INT32U)(stcStoreState.StoreAddr + EEPROM_CHECKSUM_OFFSET), EEPROM_DWORD_SIZE, (INT32U)StoreTmp);
			stcStoreState.ErrFlag = RetValue;
		}
		else
		{
			/* Program Failed */
			stcStoreState.ErrFlag = RetValue;
		}
	}
	else
	{
		;	/* do nothing */
	}
	
	/* (7) Page Earse */
	if(EEPROM_OK == RetValue)
	{
		/* Earse BLOCK_1 */
		if(stcStoreState.StoreAddr >= EEPROM_BLOCK_ADDR_2 )
		{
			stcStoreState.FailCount = 0;
			stcStoreState.ErrFlag	= EEPROM_OK;
			
			do
			{
				/* not Blank , Earsable */
				if(EEPROM_ERR_NOT_BLANK == mFlash_BlankCheck(EEPROM_BLOCK_ADDR_1, EEPROM_ERASE_SIZE) )
				{
				/*	mEEPROM_Ext_WatchDog_Feed_Hook();	/* Ext WatchDog Feed in case MCU Reset /*chjguo debug */
					RetValue = mFlash_DFlashErase(EEPROM_BLOCK_ADDR_1, EEPROM_BLOCK_INDEX_1);
				/*	mEEPROM_Ext_WatchDog_Feed_Hook();	/* Ext WatchDog Feed in case MCU Reset  /*chjguo debug */
					stcStoreState.ErrFlag = RetValue;
				}
				else
				{
					stcStoreState.ErrFlag = RetValue;
				}
				
				/* BlankCheck Failed or Erase Failed */
				if(EEPROM_OK != stcStoreState.ErrFlag)
				{
					/* Failed Count +1 */
					stcStoreState.FailCount ++;
				}
				else
				{
					;	/* do nothing */
				}
			}			
			while( ( EEPROM_OK != stcStoreState.ErrFlag) && (stcStoreState.FailCount < EEPROM_EARSE_RETRY_COUNT) );
		}
		/* Earse BLOCK_2 */
		else
		{
			stcStoreState.FailCount = 0;
			stcStoreState.ErrFlag	 = EEPROM_OK;
			
			do
			{
				/* not Blank , Earsable */
				if(EEPROM_ERR_NOT_BLANK == mFlash_BlankCheck(EEPROM_BLOCK_ADDR_2, EEPROM_ERASE_SIZE) )
				{
				/*	mEEPROM_Ext_WatchDog_Feed_Hook();	/* Ext WatchDog Feed in case MCU Reset /*chjguo debug */
					RetValue = mFlash_DFlashErase(EEPROM_BLOCK_ADDR_2, EEPROM_BLOCK_INDEX_2);
				/*	mEEPROM_Ext_WatchDog_Feed_Hook();	/* Ext WatchDog Feed in case MCU Reset  /*chjguo debug */
					stcStoreState.ErrFlag = RetValue;
				}
				else
				{
					stcStoreState.ErrFlag = RetValue;
				}
				
				/* BlankCheck Failed or Erase Failed */
				if(EEPROM_OK != stcStoreState.ErrFlag)
				{
					/* Failed Count +1 */
					stcStoreState.FailCount ++;
				}
				else
				{
					;	/* do nothing */
				}
			}			
			while( ( EEPROM_OK != stcStoreState.ErrFlag) && (stcStoreState.FailCount < EEPROM_EARSE_RETRY_COUNT) );
		}
	}
	else
	{
		;	/* do nothing */
	}

	return(RetValue);	
}


/* End of file */