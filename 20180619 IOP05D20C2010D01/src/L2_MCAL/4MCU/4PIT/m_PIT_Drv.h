/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_PIT_Drv.h
*
* @brief    Drive Header file for "m_PIT_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/08/30      CODER2       	   	N/A          Original
*     1.1        2012/09/14      ----			N/A          deliver to ChuangQu
*     1.2        2012/09/27      CODER2			N/A          Add Cfg file
*     1.3        2012/11/02      CODER2			N/A          Add History Comment
*     
************************************************************************************************/

#ifndef _M_PIT_DRV_H_
#define _M_PIT_DRV_H_

#ifdef 	M_PIT_DRV_C
#define M_PIT_DRV_EXT
#else
#define M_PIT_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"MPC560xP.h"
#include	"Std_Types.h"


/* *****************************************************************************
   *****************************************************************************
   Drv definiton
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	PIT Time for 1ms Macro                                             ***/
/*---------------------------------------------------------------------------*/
#define		TIMER_1MS_CYC	(SYS_CLK / 1000)		/* SysClk Cycle Count for 1ms */
#define		TIMER_100US_CYC	(SYS_CLK / 10000)		/* SysClk Cycle Count for 100us */
#define		TIMER_80US_CYC	(SYS_CLK / 12500)		/* SysClk Cycle Count for 80us */
#define		TIMER_50US_CYC	(SYS_CLK / 20000)		/* SysClk Cycle Count for 50us */


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_PIT_DRV_EXT	void	mPit_Timer0_Init(uint16	mInterval);
M_PIT_DRV_EXT	void	mPit_Timer1_Init(uint16	mInterval);
M_PIT_DRV_EXT	void	mPit_Timer2_Init(uint16	mInterval);
M_PIT_DRV_EXT	void	mPit_Timer3_Init(uint16	mInterval);


#endif	

