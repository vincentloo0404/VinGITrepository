/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_EEPROM_Drv.h
*
* @brief    Drive Header file for "m_EEPROM_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/05/22      CODER2       	   	N/A          Original
*     1.1        2013/06/07      CODER2       	   	N/A          Add Read_return Macro, Delete Read_State stc
*     1.2        2013/06/19      CODER2       	   	N/A          Add ERRFLAG_DATA_FOUND macro, in case of no Data in EEPROM
************************************************************************************************/
#ifndef _M_EEPROM_DRV_H_
#define _M_EEPROM_DRV_H_

#ifdef 	M_EEPROM_DRV_C
#define M_EEPROM_DRV_EXT
#else
#define M_EEPROM_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include  	"m_GPIO.h"
#include 	"Common.h"
#include 	"m_Flash_Drv.h"


/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Return Code for EEPROM Functions								   ***/
/*---------------------------------------------------------------------------*/
#define		EEPROM_OK						0x0
#define		EEPROM_ERR_ALIGN				0x7
#define		EEPROM_ERR_RANGE				0x8
#define		EEPROM_ERR_BUSY					0x9
#define		EEPROM_ERR_PGOOD				0x0A
#define		EEPROM_ERR_EGOOD				0x0B
#define		EEPROM_ERR_NOT_BLANK			0x0C
#define		EEPROM_ERR_VERIFY				0x0D
#define		EEPROM_ERR_LOCK_INDR			0x0E
#define		EEPROM_ERR_PASSWORD				0x10
#define		EEPROM_COMPARE_SAME				0x01
#define		EEPROM_COMPARE_DIFF				0x00	
#define		EEPROM_ADDR_NO_FOUND			0x02	/* Read from EEPROM, no message found */

/*---------------------------------------------------------------------------*/
/***	Size of Double Word												   ***/
/*---------------------------------------------------------------------------*/
#define		EEPROM_DWORD_SIZE				8
#define		EEPROM_WORD_SIZE				4
#define		EEPROM_WORD_MASK				0xFFFFFFFF
#define		EEPROM_DWORD_MASK				0xFFFFFFFFFFFFFFFF

/*---------------------------------------------------------------------------*/
/***	EEPROM Address													   ***/
/*---------------------------------------------------------------------------*/
#define		EEPROM_BLOCK_ADDR_1				FLASH_D_ARRAY_BASE2_ADDRESS
#define		EEPROM_BLOCK_ADDR_2				FLASH_D_ARRAY_BASE3_ADDRESS

/*---------------------------------------------------------------------------*/
/***	EEPROM Erase Size												   ***/
/*---------------------------------------------------------------------------*/
#define		EEPROM_ERASE_SIZE				(0x1<<14)
#define		EEPROM_BLOCK_SIZE_ALL			(EEPROM_ERASE_SIZE * 2)

/*---------------------------------------------------------------------------*/
/***	EEPROM Index													   ***/
/*---------------------------------------------------------------------------*/
#define		EEPROM_BLOCK_INDEX_1			(1<<2)
#define		EEPROM_BLOCK_INDEX_2			(1<<3)
#define		EEPROM_BLOCK_MASK				0x0C

/*---------------------------------------------------------------------------*/
/***	Set ErrorFlag When Data found in EEPROM							   ***/
/***	(in case of no data in EEPROM)									   ***/
/*---------------------------------------------------------------------------*/
#define		EEPROM_ERRFLAG_DATA_FOUND		0xFF

/*---------------------------------------------------------------------------*/
/***	EEPROM Store struct												   ***/
/*---------------------------------------------------------------------------*/
typedef	struct _EEPROM_STORE_STATUS_ 
{
	INT32U		StoreAddr;		/* Address to be currently Stored in */
	INT32U		StoreIndex;		/* Index to be currently Stored in */
	INT32U		CheckSum;		/* Check Sum of Data which currently Stored in */
	INT32U		LastAddr;		/* the lastest Address before new Data Stored in */

	INT8U		WriteFlag;		/* Once programed in EEPROM */
	INT8U		FailCount;		/* Program or Erase Failed Count */
	INT8U		ErrFlag;		/* the Error Type of Program or Erase Failed */
}stc_EEPROM_StoreStatus;


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_EEPROM_DRV_EXT	INT8U	mEEPROM_Init(void);
M_EEPROM_DRV_EXT	INT8U	mEEPROM_Read_Flash(INT32U *pArray_DTC);
M_EEPROM_DRV_EXT	INT8U	mEEPROM_Write_Flash(INT32U *pArray_Store);


#endif	

