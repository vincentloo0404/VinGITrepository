/******************************************************************************
*
* Lingtong Tech Inc.
* (c) Copyright 2012 Lingtong Tech, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_Flash_Drv.c
*
* @brief    DataFlash Module Function, Erase, Program, Lock, check and so on
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/11/15      CODER2	       N/A          Original
*     1.1        2012/12/04      CODER2       	   N/A          Delete Unused Function
*     1.2        2013/05/08      CODER2       	   N/A          Add Comment and modify while dead loop
*     1.3        2013/05/08      CODER2       	   N/A          modify Flash_Program function align judge
*******************************************************************************/
#ifndef M_FLASH_DRV_C
#define M_FLASH_DRV_C
#endif


/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_Flash_Drv.h"
#include 	"m_Flash_Cfg.h"


/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mFlash_BlankCheck
   Description:     check on the specified flash range for blank state.
   Parameters:      Input:	dest: 	Destination address to be checked.
   							size:	Size, in bytes, of the flash region to check.
                    Output:	
						FLASH_OK
						FLASH_ERR_ALIGN
						FLASH_ERR_RANGE
						FLASH_ERR_NOT_BLANK
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_BlankCheck(INT32U dest, INT32U size)
{
	INT8U	RetValue;
	INT32U	i;
	
	
	RetValue = FLASH_OK;
	
	/* Check Alignment */
	if(((dest | size) % FLASH_DWORD_SIZE) != 0)
	{
		RetValue = FLASH_ERR_ALIGN;
	}
	else
	{
		/* Check Range */
		if( FALSE ==   ((dest >= FLASH_D_ARRAY_BASE0_ADDRESS) 	&&
			 			(size <= FLASH_DF_ALL_SIZE)				&&
			 			((dest + size) <= (FLASH_D_ARRAY_BASE0_ADDRESS + FLASH_DF_ALL_SIZE)) ) )
		{
			RetValue = FLASH_ERR_RANGE;
		}
		else
		{
			/* Check Blank */
			for(i=0; i<(size / FLASH_WORD_SIZE); i++)
			{
				if( (*(INT32U *)dest) != FLASH_DWORD_MASK)
				{
					RetValue = FLASH_ERR_NOT_BLANK;
					break;
				}
				else
				{ }
				
				dest += FLASH_WORD_SIZE;
			}
		}	
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_CheckSum
   Description:     Perform a 32-bit sum over the specified flash memory range 
   					without carry, which provides a rapid method for checking 
   					data integrity.
   Parameters:      Input:	dest: 	Destination address to be checked.
   							size:	Size, in bytes, of the flash region to check.
   							pSum:	Returns the sum value
                    Output:	
						FLASH_OK
						FLASH_ERR_ALIGN
						FLASH_ERR_RANGE
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_CheckSum(INT32U dest, INT32U size, INT32U *pSum)
{
	INT8U	RetValue;
	INT32U	i;
	
	RetValue = FLASH_OK;
	
	/* Check Alignment */
	if(((dest | size) % FLASH_DWORD_SIZE) != 0)
	{
		RetValue = FLASH_ERR_ALIGN;
	}
	else
	{
		/* Check Range */
		if(FALSE == ((dest >= FLASH_D_ARRAY_BASE0_ADDRESS) 		&&
			 		 (size <= FLASH_DF_ALL_SIZE)				&&
			 		 ((dest + size) <= (FLASH_D_ARRAY_BASE0_ADDRESS + FLASH_DF_ALL_SIZE)) ) )
		{
			RetValue = FLASH_ERR_RANGE;
		}
		else
		{
			*pSum = 0;
			
			/* word by word CheckSum */
			for(i=0; i<(size / FLASH_WORD_SIZE); i++)
			{
				*pSum += *(INT32U *)dest;
				dest += FLASH_WORD_SIZE;
			}
			
			RetValue = FLASH_OK;	/* Redundance */
		}
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_DFlashErase
   Description:     Erase the enabled blocks in the main array or the shadow row. 
   					Input arguments together with relevant flash module status 
   					will be checked, and relevant error code will be returned 
   					if there is any error.
   Parameters:      Input:	EraseAddrBase:		Data Flash Base Address to be erased
   							lowEnabledBlocks:	To select the array blocks in low address space for erasing.
                    Output: 
                    	FLASH_OK
                    	FLASH_ERR_BUSY
                    	FLASH_ERR_EGOOD
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_DFlashErase(INT32U EraseAddrBase, INT32U lowEnabledBlocks)
{
	INT8U	RetValue, StateRet;
	INT32U	interlockWriteAddress;   /* interlock write address */
	INT32U	BlockEn;
	INT32U	PFCR1_Tmp;

	/* program and/or erase operation in progress */
	if(FLASH_MCR & (FLASH_MCR_ERS_MASK | FLASH_MCR_PGM_MASK))
	{
		RetValue = FLASH_ERR_BUSY;
	}
	else
	{
		RetValue = FLASH_OK;
		
		/* erase the main array blocks */
        interlockWriteAddress = EraseAddrBase;	/* FLASH_D_ARRAY_BASE0_ADDRESS */
        
        /* mask off reserved bits for low address space */
        BlockEn = lowEnabledBlocks & FLASH_LMS_DF_SEL_MASK;
        
        if(FALSE == BlockEn)		/* no Block Selected for Erase */
        {
        	/* do nothing, and Return */
        	RetValue = FLASH_ERR_EGOOD;
        }
        else
        {
        	FLASH_LMS = BlockEn;		/* Select Block0,1,2,3 */
	        
	        /* Disable IRQ */
	        FLASH_IRQ_DISABLE();
	        
        	/* set MCR-ERS to start erase operation */
        	REG32_BIT_SET(FLASH_MCR, FLASH_MCR_ERS_MASK);
        	
        	/* interlock write */
        	*( (INT32U *)interlockWriteAddress ) = FLASH_DWORD_MASK;
        	
        	/* write a 1 to MCR-EHV */
        	REG32_BIT_SET(FLASH_MCR, FLASH_MCR_EHV_MASK);
        	
        	/* wait until MCR-DONE set */
        	StateRet = OverTimeCheckLong(&FLASH_MCR, FLASH_MCR_DONE_MASK, FLASH_MCR_DONE_MASK, TIMEOUT_DFLASH_ERASE);
        	
        	if(FALSE == StateRet)
        	{
        		RetValue = FLASH_ERR_EGOOD;
        	}
        	else
        	{
        		/* clear MCR-EHV bit */
        		REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_EHV_MASK);
        		
        		/* confirm MCR-PEG = 1 */
        		if(FALSE == (FLASH_MCR & FLASH_MCR_PEG_MASK))
        		{
        			RetValue = FLASH_ERR_EGOOD;
        		}
        		else
        		{
        			/* DFLASH */ /* save PFB_CR1 */
        			PFCR1_Tmp = FLASH_PFCR1;
        			
					/* Invalidate the PFBIU holding register */
        			REG32_BIT_CLEAR(FLASH_PFCR1, FLASH_PFCR1_B1_P0_BFE_MASK);
        			REG32_BIT_CLEAR(FLASH_PFCR1, FLASH_PFCR1_B1_P1_BFE_MASK);

					/* clear MCR-ERS bit */
					REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_ERS_MASK);

					/* restore PFB_CR1 */
					FLASH_PFCR1 = PFCR1_Tmp;
        		}
        	}
        	
        	/* Enable IRQ */
	        FLASH_IRQ_ENABLE();    
        }			
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_Init
   Description:     read the flash configuration information from the flash 
   					control registers and initialize parameters.
   					mFlash_Init must be called prior to any other flash operations
   Parameters:      Input:    None
                    Output:
                    	FLASH_OK
                    	FLASH_INFO_EER
						FLASH_INFO_RWE
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_Init(void)
{
	INT8U	RetValue;	
	
	RetValue = FLASH_OK;
	/* Check MCR-EER and MCR-RWE bits */
	if(FLASH_MCR & (FLASH_MCR_EER_MASK | FLASH_MCR_RWE_MASK) )
	{
		REG32_BIT_SET(FLASH_MCR, FLASH_MCR_EER_MASK);
		REG32_BIT_SET(FLASH_MCR, FLASH_MCR_RWE_MASK);
	}
	else
	{
		/* do nothing */
	}

	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_DFlashProgram
   Description:     Program the specified flash areas with the provided source data. 
   					Input arguments together with relevant flash module status will 
   					be checked, and relevant error code will be returned if there is any error.
   Parameters:      Input:	dest: 	Destination address to be programmed in flash memory.
   							size:	Size, in bytes, of the flash region to be programmed.
   							source:	Source program buffer address.
                    Output:	
						FLASH_OK
						FLASH_ERR_ALIGN
						FLASH_ERR_RANGE
						FLASH_ERR_PGOOD
						FLASH_ERR_BUSY
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_DFlashProgram(INT32U dest, INT32U size, INT32U source)
{
	INT8U	RetValue, StateRet;
	INT32U	i, temp;
	INT32U	PFCR1_Tmp;
	
	RetValue = FLASH_OK;

	/* Check Alignment */
	if( (((dest | size) % FLASH_DWORD_SIZE) != 0) )
	{
		RetValue = FLASH_ERR_ALIGN;
	}
	else
	{
		/* Check Range */
		if(FALSE == ((dest >= FLASH_D_ARRAY_BASE0_ADDRESS) 		&&
			 		 (size <= FLASH_DF_ALL_SIZE)				&&
				 	 ((dest + size) <= (FLASH_D_ARRAY_BASE0_ADDRESS + FLASH_DF_ALL_SIZE)) ) )
		{
			RetValue = FLASH_ERR_RANGE;
		}
		else
		{
			if(0 == size)	/* Error Size */
			{
				RetValue = FLASH_ERR_PGOOD;
			}
			else
			{
				/* Check if program and/or erase operation in progress */
				if(FLASH_MCR & (FLASH_MCR_PGM_MASK | FLASH_MCR_ERS_MASK | FLASH_MCR_ESUS_MASK) )
				{
					RetValue = FLASH_ERR_BUSY;
				}
				else
				{
			        /* Disable IRQ */
			        FLASH_IRQ_DISABLE();
			        
					/* Set MCR-PGM to start program operation */
					REG32_BIT_SET(FLASH_MCR, FLASH_MCR_PGM_MASK);
					
					temp = size / FLASH_WORD_SIZE;
					/* Program data page by page, with special attention to incomplete page */
					for(i=0; i<temp; i++)
					{
						*(INT32U *)dest = *(INT32U *)source;
						dest += FLASH_WORD_SIZE;
						source += FLASH_WORD_SIZE;
						
						/* Do the Programming */
						if( ((dest % DFLASH_PROGRAM_SIZE) == 0) || (i == temp-1) )
						{
							/* Set MCR-EHV bit */
							REG32_BIT_SET(FLASH_MCR, FLASH_MCR_EHV_MASK);
							
							/* Wait until MCR-DONE set */
				        	StateRet = OverTimeCheckLong(&FLASH_MCR, FLASH_MCR_DONE_MASK, FLASH_MCR_DONE_MASK, TIMEOUT_DFLASH_ERASE);
							
							if(FALSE == StateRet)
				        	{
				        		RetValue = FLASH_ERR_PGOOD;
				        	}
				        	else
				        	{
								/* Confirm MCR-PEG = 1 */
								if(0 == (FLASH_MCR & FLASH_MCR_PEG_MASK))
								{
									RetValue = FLASH_ERR_PGOOD;
									
									/* Clear MCR-EHV bit */
									REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_EHV_MASK);
									
									/* Clear MCR-PGM bit */
									REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_PGM_MASK);
																		
				        			/* DFLASH */ /* save PFB_CR1 */
				        			PFCR1_Tmp = FLASH_PFCR1;
				        			
									/* Invalidate the PFBIU holding register */        			
				        			REG32_BIT_CLEAR(FLASH_PFCR1, FLASH_PFCR1_B1_P0_BFE_MASK);
									REG32_BIT_CLEAR(FLASH_PFCR1, FLASH_PFCR1_B1_P1_BFE_MASK);

									/* clear MCR-ERS bit */
									REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_ERS_MASK);

									/* restore PFB_CR1 */
									FLASH_PFCR1 = PFCR1_Tmp;			
								}
								else
								{
									/* Clear MCR-EHV bit */
									REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_EHV_MASK);
								}
				        	}	
						}
						else
						{
							/* do nothing */
						}
					}
					
					/* Clear MCR-PGM bit */
					REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_PGM_MASK);
														
        			/* DFLASH */ /* save PFB_CR1 */
        			PFCR1_Tmp = FLASH_PFCR1;
        			
					/* Invalidate the PFBIU holding register */        			
        			REG32_BIT_CLEAR(FLASH_PFCR1, FLASH_PFCR1_B1_P0_BFE_MASK);
					REG32_BIT_CLEAR(FLASH_PFCR1, FLASH_PFCR1_B1_P1_BFE_MASK);

					/* clear MCR-ERS bit */
					REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_ERS_MASK);

					/* restore PFB_CR1 */
					FLASH_PFCR1 = PFCR1_Tmp;
					
			        /* Enable IRQ */
			        FLASH_IRQ_ENABLE();
				}
			}
		}
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_DFlashVerify
   Description:     check if a programmed flash range matches the corresponding 
   					source data buffer. In case of mismatch, the failed address, 
   					destination value and source value will be saved and 
   					relevant error code will be returned.
   Parameters:      Input:	dest: 	Destination address to be verified in flash memory.
   							size:	Size, in bytes, of the flash region to verify.
   							source:	Source verify buffer address.
                    Output: 
						FLASH_OK
						FLASH_ERR_ALIGN
						FLASH_ERR_RANGE
						FLASH_ERR_VERIFY
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_DFlashVerify(INT32U dest, INT32U size, INT32U source)
{
	INT8U	RetValue;
	INT32U	i, temp;

	RetValue = FLASH_OK;
	
	/* Check Alignment */
	if( (((dest | size) % FLASH_DWORD_SIZE) != 0))
	{
		RetValue = FLASH_ERR_ALIGN;
	}
	else
	{
		/* Check Range */
		if(FALSE == ((dest >= FLASH_D_ARRAY_BASE0_ADDRESS) 		&&
			 		 (size <= FLASH_DF_ALL_SIZE)				&&
			 		 ((dest + size) <= (FLASH_D_ARRAY_BASE0_ADDRESS + FLASH_DF_ALL_SIZE)) ) )
		{
			RetValue = FLASH_ERR_RANGE;
		}
		else
		{
			temp = size / FLASH_WORD_SIZE;
			/* Verify data word by word */
			for(i=0; i<temp; i++)
			{
				if( *(INT32U *)dest != *(INT32U *)source )
				{
					RetValue = FLASH_ERR_VERIFY;
					break;
				}
				else
				{ }
				
				dest += FLASH_WORD_SIZE;
				source += FLASH_WORD_SIZE;
			}
		}
	}

	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_SetLock
   Description:     set the block lock state for Shadow/Low/Middle/High address space 
   					on the C90LC module to protect them from program/erase. 
   					The API will provide password to enable block lock register writes 
   					when needed and write the block lock value to block lock register 
   					for the requested address space.
   Parameters:      Input:	
   						blkLockIndicator:	Indicating the address space and the protection 
   											level of the block lock register to be read.
						blkLockState:		The block locks to be set to the specified 
											address space and protection level.
						password:			The block locks to be set to the specified 
											address space and protection level.
                    Output: 
						FLASH_OK
						FLASH_ERR_LOCK_INDR
						FLASH_ERR_PASSWORD
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_SetLock(INT8U blkLockIndicator, INT32U blkLockState, INT32U password)
{
	INT8U	RetValue;
	
	if(blkLockIndicator > FLASH_LOCK_MID_SECONDARY)
	{
		RetValue = FLASH_ERR_LOCK_INDR;
	}
	else
	{
		RetValue = FLASH_OK;
		
		/* write password to block lock register if it's locked for register writes */
		switch(blkLockIndicator)
		{
			case FLASH_LOCK_SHADOW_PRIMARY:
			case FLASH_LOCK_LOW_PRIMARY:
			case FLASH_LOCK_MID_PRIMARY:
				if( 0 == (FLASH_LML & FLASH_LML_LME_MASK) )
				{
					/* write user provided password to block lock register */
					FLASH_LML = password;
					
					/* check if the block lock register is enabled for register writes after writing password */
					if( 0 == (FLASH_LML & FLASH_LML_LME_MASK) )
					{
						RetValue = FLASH_ERR_PASSWORD;
					}
					else
					{
						/* do nothing */
					}
				}
				else
				{
					/* do nothing */
				}
				break;
			
			case FLASH_LOCK_SHADOW_SECONDARY:
			case FLASH_LOCK_LOW_SECONDARY:
			case FLASH_LOCK_MID_SECONDARY:
				if( 0 == (FLASH_SLL & FLASH_SLL_SLE_MASK) )
				{
					/* write user provided password to block lock register */
					FLASH_SLL = password;
					
					/* check if the block lock register is enabled for register writes after writing password */
					if( 0 == (FLASH_SLL & FLASH_SLL_SLE_MASK) )
					{
						RetValue = FLASH_ERR_PASSWORD;
					}
					else
					{
						/* do nothing */
					}
				}
				else
				{
					/* do nothing */
				}
				break;
				
			default:
				break;
		}
		
		if(FLASH_OK != RetValue)
		{
			/* do nothing, and return */
		}
		else
		{
			/* set the new value to the block lock field */
			switch(blkLockIndicator)
			{
				case FLASH_LOCK_SHADOW_PRIMARY:
					if(ENABLE == blkLockState)
					{
						REG32_BIT_SET(FLASH_LML, FLASH_LML_TSLK_MASK);		
					}
					else
					{
						REG32_BIT_CLEAR(FLASH_LML, FLASH_LML_TSLK_MASK);		
					}
					break;
				case FLASH_LOCK_SHADOW_SECONDARY:
					if(ENABLE == blkLockState)
					{
						REG32_BIT_SET(FLASH_SLL, FLASH_SLL_STSLK_MASK);		
					}
					else
					{
						REG32_BIT_CLEAR(FLASH_SLL, FLASH_SLL_STSLK_MASK);		
					}
					break;
				case FLASH_LOCK_LOW_PRIMARY:
					if(ENABLE == blkLockState)
					{
						REG32_BIT_SET(FLASH_LML, FLASH_LML_LLK_MASK);		
					}
					else
					{
						REG32_BIT_CLEAR(FLASH_LML, FLASH_LML_LLK_MASK);		
					}
					break;
				case FLASH_LOCK_LOW_SECONDARY:
					if(ENABLE == blkLockState)
					{
						REG32_BIT_SET(FLASH_SLL, FLASH_SLL_SLK_MASK);		
					}
					else
					{
						REG32_BIT_CLEAR(FLASH_SLL, FLASH_SLL_SLK_MASK);		
					}
					break;
				case FLASH_LOCK_MID_PRIMARY:
					if(ENABLE == blkLockState)
					{
						REG32_BIT_SET(FLASH_LML, FLASH_LML_MLK_MASK);		
					}
					else
					{
						REG32_BIT_CLEAR(FLASH_LML, FLASH_LML_MLK_MASK);		
					}
					break;
				case FLASH_LOCK_MID_SECONDARY:
					if(ENABLE == blkLockState)
					{
						REG32_BIT_SET(FLASH_SLL, FLASH_SLL_SMK_MASK);		
					}
					else
					{
						REG32_BIT_CLEAR(FLASH_SLL, FLASH_SLL_SMK_MASK);		
					}
					break;
				default:
					break;
			}		
		}
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_GetLock
   Description:     Check the block locking status of Shadow/Low/Middle/High 
   					address spaces in the C90LC module
   Parameters:      Input:	
   						blkLockIndicator:	Indicating the address space and the block 
   											locking level, which determines the address
   											space block locking register to be checked. 
						blkLockEnAddr:		Indicate whether the address space block 
											locking register is enabled for register writes
						blkLockStateAddr:	Returns the blocks' locking status of indicated 
											locking level in the given address space
                    Output: 
						FLASH_OK
						FLASH_ERR_LOCK_INDR
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_GetLock(INT8U blkLockIndicator, INT8U *blkLockEnAddr, INT32U *blkLockStateAddr)
{
	INT8U	RetValue;
	
	
	*blkLockEnAddr = FALSE;
	if(blkLockIndicator > FLASH_LOCK_MID_SECONDARY)
	{
		RetValue = FLASH_ERR_LOCK_INDR;
	}
	else
	{
		RetValue = FLASH_OK;
		
		/* Check block lock register if Enabled */
		switch(blkLockIndicator)
		{
			case FLASH_LOCK_SHADOW_PRIMARY:
			case FLASH_LOCK_LOW_PRIMARY:
			case FLASH_LOCK_MID_PRIMARY:
				if( FLASH_LML & FLASH_LML_LME_MASK )
				{
					*blkLockEnAddr = TRUE;
				}
				else
				{
					/* do nothing */
				}
				break;
			
			case FLASH_LOCK_SHADOW_SECONDARY:
			case FLASH_LOCK_LOW_SECONDARY:
			case FLASH_LOCK_MID_SECONDARY:
				if( FLASH_SLL & FLASH_SLL_SLE_MASK )
				{
					*blkLockEnAddr = TRUE;
				}
				else
				{
					/* do nothing */
				}
				break;
				
			default:
				break;
		}
		
		/* Get the lockState */
		switch(blkLockIndicator)
		{
			case FLASH_LOCK_SHADOW_PRIMARY:
		        *blkLockStateAddr = (FLASH_LML & FLASH_LML_TSLK_MASK) >> 20;
				break;
			case FLASH_LOCK_SHADOW_SECONDARY:
				*blkLockStateAddr = (FLASH_SLL & FLASH_SLL_STSLK_MASK) >> 20;
				break;
			case FLASH_LOCK_LOW_PRIMARY:
				*blkLockStateAddr = (FLASH_LML & FLASH_LML_LLK_MASK) >> 0;
				break;
			case FLASH_LOCK_LOW_SECONDARY:
				*blkLockStateAddr = (FLASH_SLL & FLASH_SLL_SLK_MASK) >> 0;
				break;
			case FLASH_LOCK_MID_PRIMARY:
				*blkLockStateAddr = (FLASH_LML & FLASH_LML_MLK_MASK) >> 16;
				break;
			case FLASH_LOCK_MID_SECONDARY:
				*blkLockStateAddr = (FLASH_SLL & FLASH_SLL_SMK_MASK) >> 16;
				break;
			default:
				break;
		}
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_Suspend
   Description:     Check if there is any high voltage operation, erase or program, 
   					in progress on the C90LC module and if the operation can be 
   					suspended. This function will suspend the ongoing operation 
   					if it can be suspended 
   					(for C90LC modules it applies only to erase operation). 
   Parameters:      Input:	SuspendStateAddr:	Indicate the suspend state of C90LC 
   												module after the function being called.
   							SuspendFlagAddr:	Return whether the suspended operation,
   												if there is any, is suspended by this call.
                    Output:
                    	FLASH_OK
                    	FLASH_ERR_SUSP
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_Suspend(INT8U *SuspendStateAddr, INT8U *SuspendFlagAddr)
{
	INT8U	RetValue, StateRet, SuspState;

	RetValue = FLASH_OK;
	*SuspendStateAddr = FLASH_NO_OPERATION;
	*SuspendFlagAddr = FALSE;
	SuspState = SUSP_NORMAL;
	
    /* no P/E sequence: PGM=0 and ERS=0

       possible stages for program sequece:
          a. interlock write;               (PGM=1;EHV=0;  PSUS=0;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1)
          b. high voltage active;           (PGM=1;EHV=1;  PSUS=0;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)
          c. entering suspend state;        (PGM=1;EHV=1;  PSUS=1;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)  Not possible for flash LC
          d. in suspend state;              (PGM=1;EHV=1/0;PSUS=1;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1)    Not possible for flash LC
          e. resuming from suspend state;   (PGM=1;EHV=1;  PSUS=0;DONE=1; ignore PEG)  OR (ERS=1;ESUS=1) Not possible for flash LC
          f. high voltage stopped;          (PGM=1;EHV=1;  PSUS=0;DONE=1; valid  PEG)  OR (ERS=1;ESUS=1)
          g. abort period.                  (PGM=1;EHV=0;  PSUS=0;DONE=0; ignore PEG)  OR (ERS=1;ESUS=1)
       Note: 1. Only stage e and f has the same condition;
             2. PGM  set: STOP=0 and ERS=0 or ERS=1 and ESUS=1 and EHV=0
             3. PGM  clear: EHV=0 and PSUS=0 and DONE=1
             4. PSUS set: PGM=1 and EHV=1;
             5. PSUS clear: DONE=1 and EHV=1

       possible stages for erase sequece:
          a. interlock write;               (ERS=1;EHV=0;  ESUS=0;DONE=1; ignore PEG)  AND (PGM=0;PSUS=0)
          b. high voltage active;           (ERS=1;EHV=1;  ESUS=0;DONE=0; ignore PEG)  AND (PGM=0;PSUS=0)
          c. entering suspend state;        (ERS=1;EHV=1;  ESUS=1;DONE=0; ignore PEG)  AND (PGM=0;PSUS=0)
          d. in suspend state;              (ERS=1;EHV=1/0;ESUS=1;DONE=1; ignore PEG)  AND (PGM=0;PSUS=0)
          e. resuming from suspend state;   (ERS=1;EHV=1;  ESUS=0;DONE=1; ignore PEG)  AND (PGM=0;PSUS=0)
          f. high voltage stopped;          (ERS=1;EHV=1;  ESUS=0;DONE=1; valid  PEG)  AND (PGM=0;PSUS=0)
          g. abort period.                  (ERS=1;EHV=0;  ESUS=0;DONE=0; ignore PEG)  AND (PGM=0;PSUS=0)
       Note: 1. Only stage e and f has the same condition
             2. ERS  set: STOP=0 and ERS=0 and PGM=0
             3. ERS  clear: EHV=0 and ESUS=0 and DONE=1
             4. ESUS set: ERS=1 and EHV=1 and PGM=0
             5. ESUS clear: DONE=1 and EHV=1 and PGM=0

       FlashSuspend procedures:
       no sequence: NO_OPERATION
       stage     a: PGM_WRITE, ERS_WRITE
       stage b,e,f: suspend and return the current state for erase  return error for program
       stage   c,d: return the current state for erase  return error for program
       stage     g: switch to stage "a" and return the current state */

	/* No program/erase sequence */
	if( 0 == (FLASH_MCR & (FLASH_MCR_PGM_MASK | FLASH_MCR_ERS_MASK)) )
	{
		/* do nothing */
	}
	else
	{
		if( (FLASH_MCR & FLASH_MCR_PGM_MASK) || 
		  ( (FLASH_MCR & FLASH_MCR_ERS_MASK) && ( 0 == (FLASH_MCR & FLASH_MCR_ESUS_MASK) ))  )
		{
			if ( 0 == (FLASH_MCR & FLASH_MCR_EHV_MASK) )
			{
				/* a. interlock write */
            	/* g. abort period */
            	
            	if (FLASH_MCR & FLASH_MCR_PGM_MASK)
            	{
            		*SuspendStateAddr = FLASH_PGM_WRITE;
            	}
            	else
            	{
            		/* do nothing */
            	}
            	
            	if (FLASH_MCR & FLASH_MCR_ERS_MASK)
	            {
	                *SuspendStateAddr = FLASH_ERS_WRITE;
	            }
            	else
            	{
            		/* do nothing */
            	}
            	
            	/* for interlock write stage, MCR-DONE bit already high */
            	/* for abort transition stage, wait MCR-DONE bit set */
            	SuspState = SUSP_WAIT;
			}
			else
        	{
	            /* b. high voltage active */
	            /* e. resuming from suspend state */
	            /* f. high voltage stopped */
	            if (FLASH_MCR & FLASH_MCR_PGM_MASK)
	            {
	                /* Programming operation cannot be suspended */
	                RetValue = FLASH_ERR_SUSP;
	                *SuspendStateAddr = FLASH_NO_SUS;
	                SuspState = SUSP_RETURN;
				}
				else	/*  ERS =1 */
				{
					/* set MCR-ESUS bit */
					REG32_BIT_SET(FLASH_MCR, FLASH_MCR_ESUS_MASK);
					
					*SuspendFlagAddr = TRUE;
					SuspState = SUSP_NORMAL;
				}
        	}
			
		}
		else
		{
			/* do nothing */
		}
		
		if(SUSP_NORMAL == SuspState)
		{
			SuspState = SUSP_WAIT;
					
			/* Stages b, e, f, c and d will become a suspend state */
			if(FLASH_MCR & FLASH_MCR_ESUS_MASK)
			{
				*SuspendStateAddr = FLASH_ERS_SUS;
				
				/* check MCR-PEAS bit */
				if(FLASH_MCR & FLASH_MCR_PEAS_MASK)
				{
					*SuspendStateAddr = FLASH_SHADOW_ERS_SUS;
				}
				else
				{
					/* do nothing */
				}
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}
		
		if(SUSP_WAIT == SuspState)
		{
			/* Wait until MCR-DONE = 1 */
	    	StateRet = OverTimeCheckLong(&FLASH_MCR, FLASH_MCR_DONE_MASK, FLASH_MCR_DONE_MASK, TIMEOUT_DFLASH_ERASE);
			
			if(StateRet == TRUE)
			{
				/* Set MCR-EHV to 0 */
				REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_EHV_MASK);			
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_Resume
   Description:     Check if there is any suspended erase or program operation on 
   					the C90LC module, and will resume the suspended operation 
   					if there is any.
   Parameters:      Input:	
   						ResumeStateAddr:	Indicate the resume state of C90LC 
   											module after the function being called
                    Output:   
                    	FLASH_OK
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_Resume(INT8U *ResumeStateAddr)
{
	INT8U	RetValue;
	INT32U	WatiCnt;
	
	WatiCnt = FLASH_RESUME_WAIT;
	RetValue = FLASH_OK;
	*ResumeStateAddr = FLASH_RES_NOTHING;
	
	/* erase in suspend state or entering suspend state */
	if( 0 == (FLASH_MCR & FLASH_MCR_ESUS_MASK) )
	{
		/* No suspended operation */ /* do nothing */
	}
	else
	{
		*ResumeStateAddr = FLASH_RES_ERS;
		
		/* Set MCR-EHV bit */
		REG32_BIT_SET(FLASH_MCR, FLASH_MCR_EHV_MASK);
		
		/* clear the MCR-ESUS bit or MCR-PSUS bit */
		REG32_BIT_CLEAR(FLASH_MCR, FLASH_MCR_ESUS_MASK);
		
		/* wait the MCR-DONE bit goes low */
	    while((FLASH_MCR & FLASH_MCR_DONE_MASK) && (WatiCnt > 0))
	    {
	    	WatiCnt--;
	    }		
	}

	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_ArrayIntergrityCheck
   Description:     Check the array integrity of the Flash. The user specified address 
   					sequence is used for array integrity reads and the operation is done
   					on the specified blocks. 
   					The MISR values calculated by the hardware is compared to the values
   					passed by the user, if they are not the same, then an error code is returned. 
   Parameters:      Input:
   						LowEnBlock:	To select the array blocks in low address space
   						MidEnBlock:	To select the array blocks in mid address space
   						ArrSeqMode:	To determine the address sequence to be used during array integrity checks.
   						MisrValue:	A structure variable containing the MISR values calculated by the user 
   									using the offline MISR generation tool.
                    Output:
                    	FLASH_OK
                    	FLASH_ERR_AIC_MISMATCH
                    	FLASH_ERR_AIC_NO_BLOCK
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_ArrayIntergrityCheck(INT32U LowEnBlock, INT32U MidEnBlock, INT8U ArrSeqMode, stc_Flash_MISR MisrValue)
{
	INT8U	RetValue, StateRet;
	stc_Flash_MISR	stcMISR_Tmp;
	
	RetValue = FLASH_OK;
	
	/* mask off reserved bits for low address space */
	LowEnBlock &= FLASH_LMS_LSL_MASK;
	/* mask off reserved bits for mid address space */
	LowEnBlock |= (MidEnBlock & FLASH_LMS_MSL_MASK)<<16;
	
	if(FALSE == LowEnBlock)
	{
		/* no blocks to be selected for evaluation */
		RetValue = FLASH_ERR_AIC_NO_BLOCK;
	}
	else
	{
		/* write password to UT0 register to enable test mode */
		FLASH_UT0 = FLASH_UT0_PASSWORD;
		
		/* set UTO-UTE bit to enable User Test Mode */
		REG32_BIT_SET(FLASH_UT0, FLASH_UT0_UTE_MASK);
		
		/* set the block selection registers */
		FLASH_LMS = LowEnBlock;
		
		/* set the seed values of the MISR in UMx registers */
		FLASH_UMISR(0) = 0;
		FLASH_UMISR(1) = 0;
		FLASH_UMISR(2) = 0;
		FLASH_UMISR(3) = 0;
		FLASH_UMISR(4) = 0;
		
		/* set the Address sequence to be used */
		if( FLASH_AIS_SEQL == ArrSeqMode )
		{
			/* initiate the Array Integrity Check by writing 1 to Ut0_AIE bit*/
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_UTE_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_AIE_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_AIS_MASK);
		}
		else
		{
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_UTE_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_AIE_MASK);
		}
		
		/* wait until UT0-AID is set */
    	StateRet = OverTimeCheckLong(&FLASH_MCR, FLASH_UT0_AID_MASK, FLASH_UT0_AID_MASK, TIMEOUT_DFLASH_ERASE);
		
		if(StateRet == TRUE)
		{
			stcMISR_Tmp.W0 = FLASH_UMISR(0);
			stcMISR_Tmp.W1 = FLASH_UMISR(1);
			stcMISR_Tmp.W2 = FLASH_UMISR(2);
			stcMISR_Tmp.W3 = FLASH_UMISR(3);
			stcMISR_Tmp.W4 = FLASH_UMISR(4);
			
			if(	(MisrValue.W0 == stcMISR_Tmp.W0) 	&&
				(MisrValue.W1 == stcMISR_Tmp.W1) 	&&
				(MisrValue.W2 == stcMISR_Tmp.W2) 	&&
				(MisrValue.W3 == stcMISR_Tmp.W3) 	&&
				(MisrValue.W4 == stcMISR_Tmp.W4) )
			{
				/* clear UTO-AIE bit */
				REG32_BIT_CLEAR(FLASH_UT0, FLASH_UT0_AIE_MASK);
				
				/* Clear the Address sequence bit used */
				if( FLASH_AIS_SEQL == ArrSeqMode )
				{
					/* the sequential sequence bit is cleared */
					REG32_BIT_CLEAR(FLASH_UT0, FLASH_UT0_AIS_MASK);
				}
				else
				{
					/* the default sequence doen't need to be cleared */
				}
				
				/* clear UTO-UTE bit to disable User Test Mode */
				FLASH_UT0 = 0;				
			}
			else
			{
        		RetValue = FLASH_ERR_AIC_MISMATCH;
			}			
		}
		else
		{
			RetValue = FLASH_ERR_BUSY;	/* do nothing */
		}
	}

	return(RetValue);	
}


/* *****************************************************************************
   Function:        mFlash_ECCLogicCheck
   Description:     Check the ECC logic of the Flash. The API will simulate a single 
   					or double bit fault depending on the user input. 
   					If the simulated ECC error is not detected, then the error code 
   					FLASH_ERROR_ECC_LOGIC is returned.
   Parameters:      Input:    
   						DataVal:	The 64 bits of data for which the ECC is calculated. 
   									The bits of dataValue are flipped to generate single 
   									or double bit faults.
   						ErrBits:	Is a 64-bit mask of the bits at which the user intends to inject error.
   						EccVal:		It's a 32 bit value which has to be passed by user. This is calculated
   									by using an offline ECC Calculator.
                    Output:   
                    	FLASH_OK
                    	FLASH_ERR_ECC_LOGIC
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_ECCLogicCheck(INT64U DataVal, INT64U ErrBits, INT8U EccVal)
{
	INT8U	RetValue, StateRet;
	INT32U	DataMSB_Tmp, DataLSB_Tmp, flipMSB_Tmp, flipLSB_Tmp;
	INT64U	flipDataWord;            /* Contains the flipped the data word */
	INT8U	ErrBitSet, i;
	INT64U	temp;
	INT32U	u32EccError;
	
	RetValue = FLASH_OK;
	
	/* split the 64 bit value into two 32 bit words */
	DataLSB_Tmp = (INT32U)DataVal;
	DataMSB_Tmp = (INT32U)(DataVal >> 32);	
	
	/* write password to UT0 register to enable test mode */
	FLASH_UT0 = FLASH_UT0_PASSWORD;
	
	/* Flip the bits of the data words to simulate single or double bit faults */
	flipDataWord = DataVal ^ ErrBits;
	
	/* split the 64 bit flipped data word value into two 32 bit words */
	flipLSB_Tmp = (INT32U)flipDataWord;
	flipMSB_Tmp = (INT32U)(flipDataWord >> 32);
	
	/* initiate the ECC Logic Check by wirting 1 to UT0_EIE bit*/
	REG32_BIT_SET(FLASH_UT0, FLASH_UT0_EIE_MASK);

	/* write the flipped data words and the calculated ecc bits */
	FLASH_UT1 = flipLSB_Tmp;
	FLASH_UT2 = flipMSB_Tmp;
	
	/* to write the ECC bits to UT0-DSI bits without affecting the other bits */
	REG32_BIT_CLEAR(FLASH_UT0, FLASH_UT1_DSI_MASK);
	FLASH_UT0 |= ((EccVal & 0xFF)<<16);
	
	/* set errBits to zero */
	ErrBitSet = FLASH_ECC_ERR_BIT_SET_ZERO;
	temp = ErrBits;
	
	/* to find if single or double bit fault should be simulated */
	for(i = 0; i < FLASH_UT_DAI_CNT; i++)
	{
		if(temp & 0x01)
		{
			ErrBitSet++;
		}
		else
		{ }
		
		temp = temp>>1;
	}
	
	/* initiate the ECC Logic check  by writing 1 to Ut0_AIE bit*/
	REG32_BIT_SET(FLASH_UT0, FLASH_UT0_AIE_MASK);
	
	/* wait until UT0-AID is set */
	StateRet = OverTimeCheckLong(&FLASH_MCR, FLASH_UT0_AID_MASK, FLASH_UT0_AID_MASK, TIMEOUT_DFLASH_ERASE);
	
	if(StateRet == TRUE)
	{
		/* Read ECC logic check results */
		flipLSB_Tmp = FLASH_UMISR(0);
		flipMSB_Tmp = FLASH_UMISR(1);		
		u32EccError = FLASH_UMISR(4) & FLASH_ECC_ERR_MASK;
		
		/* Check if a double bit fault has occured */
		if( ( (flipLSB_Tmp != DataLSB_Tmp) || (flipMSB_Tmp != flipMSB_Tmp) ) && (u32EccError))
		{
			/* double bit fault detected */
        	/* if no error bits were set, or a single bit was set, then a double bit fault should not occur
                          ECC logic check failed */
			if(ErrBitSet < FLASH_ECC_ERR_BIT_SET_TWO)
			{
				RetValue = FLASH_ERR_ECC_LOGIC;
			}
			else
			{
				/* do nothing */
			}
		}
		/* Check if a single bit fault has occcured and has been corrected */
    	/* the data written in UT1-DAI is the flipped word flipDataWord1 and MCR-SBC bit is set */
		else if( (flipLSB_Tmp == DataLSB_Tmp) && (flipMSB_Tmp == flipMSB_Tmp) && (u32EccError))
		{
	        /* the single bit fault has been corrected */
	        /* if error bits set was not one, then a single bit fault should not occur
                          ECC logic check fails */	
			if( FLASH_ECC_ERR_BIT_SET_ONE != ErrBitSet )
			{
				RetValue = FLASH_ERR_ECC_LOGIC;
			}
			else
			{
				/* do nothing */
			}
		}
		/* Single or Double bit faults have not occurred */
		else
		{
			/* if no error bits were set, then a single or double bit fault should not occur */
			if( FLASH_ECC_ERR_BIT_SET_ZERO != ErrBitSet )
			{
				RetValue = FLASH_ERR_ECC_LOGIC;
			}
			else
			{
				/* do nothing */
			}
		}
		
		/* clear UTO-AIE bit */
		REG32_BIT_CLEAR(FLASH_UT0, FLASH_UT0_AIE_MASK);

		/* clear UTO-EIE bit */
		REG32_BIT_CLEAR(FLASH_UT0, FLASH_UT0_EIE_MASK);

		/* clear UTO-UTE bit to disable User Test Mode */
		FLASH_UT0 = 0;
	}
	else
	{
		RetValue = FLASH_ERR_BUSY;	/* do nothing */
	}
	
	return(RetValue);
}


/* *****************************************************************************
   Function:        mFlash_FactoryMarginReadCheck
   Description:     Check the Factory Margin reads of the Flash. The user specified 
   					margin level is used for reads and the operation is done on the 
   					specified blocks. 
   					The MISR values calculated by the hardware is compared to the 
   					values passed by the user, if they are not the same, 
   					then an error code is returned. 
   Parameters:      Input:    
   						LowEnBlock:		To select the array blocks in low address space
   						MidEnBlock:		To select the array blocks in mid address space
   						MarginLevel:	To determine the margin level to be used 
   										during factory margin read checks. 
   						MisrValue:		A structure variable containing the MISR values 
   										calculated by the user using the offline MISR generation tool.
                    Output:
                    	FLASH_OK
                    	FLASH_ERR_FMR_MISMATCH
                    	FLASH_ERR_FMR_NO_BLOCK
   Notes:           
                   
   ***************************************************************************** */
INT8U	mFlash_FactoryMarginReadCheck(INT32U LowEnBlock, INT32U MidEnBlock, INT8U MarginLevel, stc_Flash_MISR MisrValue)
{
	INT8U	RetValue, StateRet;
	stc_Flash_MISR	stcMISR_Tmp;

	RetValue = FLASH_OK;
	
	/* mask off reserved bits for low address space */
	LowEnBlock &= FLASH_LMS_LSL_MASK;
	/* mask off reserved bits for mid address space */
	LowEnBlock |= (MidEnBlock & FLASH_LMS_MSL_MASK)<<16;
	
	if(FALSE == LowEnBlock)
	{
		/* no blocks to be selected for evaluation */
		RetValue = FLASH_ERR_FMR_NO_BLOCK;
	}
	else
	{
		/* write password to UT0 register to enable test mode */
		FLASH_UT0 = FLASH_UT0_PASSWORD;
		
		/* set UTO-UTE bit to enable User Test Mode */
		REG32_BIT_SET(FLASH_UT0, FLASH_UT0_UTE_MASK);
		
		/* set the block selection registers */
		FLASH_LMS = LowEnBlock;
		
		/* set the seed values of the MISR in UMx registers */
		FLASH_UMISR(0) = 0;
		FLASH_UMISR(1) = 0;
		FLASH_UMISR(2) = 0;
		FLASH_UMISR(3) = 0;
		FLASH_UMISR(4) = 0;
		
		/* set the Margin level to be used */
		if( FLASH_FMR_ERASED_LEVEL != MarginLevel )
		{
	        /* the erase level is used */
	        /* initiate the Factory Margin Read Check by writing 1 to UT0_AIE bit*/
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_UTE_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_MRE_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_MRV_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_AIE_MASK);
		}
		else
		{
	        /* the programmed level is used */
	        /* the erase level is used */
	        /* initiate the Factory Margin Read Check by writing 1 to UT0_AIE bit*/			
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_UTE_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_MRE_MASK);
			REG32_BIT_SET(FLASH_UT0, FLASH_UT0_AIE_MASK);
		}
		
		/* wait until UT0-AID is set */
		StateRet = OverTimeCheckLong(&FLASH_MCR, FLASH_UT0_AID_MASK, FLASH_UT0_AID_MASK, TIMEOUT_DFLASH_ERASE);
		
		if(StateRet == TRUE)
		{
			/* clear UTO-AIE bit */
			REG32_BIT_CLEAR(FLASH_UT0, FLASH_UT0_AIE_MASK);
			
			stcMISR_Tmp.W0 = FLASH_UMISR(0);
			stcMISR_Tmp.W1 = FLASH_UMISR(1);
			stcMISR_Tmp.W2 = FLASH_UMISR(2);
			stcMISR_Tmp.W3 = FLASH_UMISR(3);
			stcMISR_Tmp.W4 = FLASH_UMISR(4);
			
			if(	(MisrValue.W0 == stcMISR_Tmp.W0) 	&&
				(MisrValue.W1 == stcMISR_Tmp.W1) 	&&
				(MisrValue.W2 == stcMISR_Tmp.W2) 	&&
				(MisrValue.W3 == stcMISR_Tmp.W3) 	&&
				(MisrValue.W4 == stcMISR_Tmp.W4) )
			{
				/* clear UTO-UTE bit to disable User Test Mode */
				FLASH_UT0 = 0;				
			}
			else
			{
        		RetValue = FLASH_ERR_FMR_MISMATCH;
			}			
		}
		else
		{
			RetValue = FLASH_ERR_BUSY;	/* do nothing */
		}
	}

	return(RetValue);
}




/* End of file */