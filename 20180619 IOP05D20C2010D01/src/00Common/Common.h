/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     Common.h
*
* @brief    Header file for "Common.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        	CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2016/10/19      ----			N/A          Original
************************************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include  	"Std_Types.h"


/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Macros for Accessing the Registers  32-bit      	               ***/
/*---------------------------------------------------------------------------*/
#define		REG32_BIT_SET(reg32, mask)			((reg32) |= (mask))
#define		REG32_BIT_CLEAR(reg32, mask)		((reg32) &= ~(mask))
#define		REG32_BIT_TEST(reg32, mask)			((reg32) & (mask))
#define		REG32_WRITE(reg32, value)			((reg32) = (value))
#define		REG32_READ(reg32)					((uint32)(reg32))
#define		REG32_GET_BIT(value, position)		(uint32)(((value) >> (position)) & 0x01)

/*---------------------------------------------------------------------------*/
/***	Macros for Accessing the Registers  16-bit                  	   ***/
/*---------------------------------------------------------------------------*/
#define		REG16_BIT_SET(reg16, mask)			((reg16) |= (mask))
#define		REG16_BIT_CLEAR(reg16, mask)		((reg16) &= ~(mask))
#define		REG16_BIT_TEST(reg16, mask)			((reg16) & (mask))
#define		REG16_WRITE(reg16, value)			((reg16) = (value))
#define		REG16_READ(reg16)					((uint16)(reg16))

/*---------------------------------------------------------------------------*/
/***	Macros for Accessing the Registers  8-bit                  	   ***/
/*---------------------------------------------------------------------------*/
#define		REG8_BIT_SET(reg8, mask)			((reg8) |= (mask))
#define		REG8_BIT_CLEAR(reg8, mask)			((reg8) &= ~(mask))
#define		REG8_BIT_TEST(reg8, mask)			((reg8) & (mask))
#define		REG8_WRITE(reg8, value)				((reg8) = (value))
#define		REG8_READ(reg8)						((uint8)(reg8))

/*---------------------------------------------------------------------------*/
/***	TimeOut Macro								                 	   ***/
/*---------------------------------------------------------------------------*/
#define		TIMER_TIME_OUT       				0x01
#define		TIMER_TIME_IN        				0x00

/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
extern	void	mDalay_Nms(uint32 delay);
extern	uint8	OverTimeCheckLong(volatile uint32 *pModuleSR, uint32 checkMask, uint32 checkResult, uint32 delayTime);
extern	uint8	OverTimeCheckLong_16U(volatile uint16 *pModuleSR, uint32 checkMask, uint32 checkResult, uint32 delayTime);
extern	void	Memory_Copy_Src_to_Dest(uint8 *dest, uint8 *source, uint16 u16Len);
extern	void	Memory_Set_Dest(uint8 *dest, uint8 Char_Val, uint16 u16Len);
extern	void	mComm_vTimeInit(void);
extern	void	mComm_vTimeTick(void);
extern	uint16	mComm_u16GetCurrCnt(void);
extern	uint8	mComm_u8CheckTimeOut(uint16 startTimer, uint16 nowTimer, uint16 timeOut);

#endif	