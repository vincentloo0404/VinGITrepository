/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     SysConfig.h
*
* @brief    this file contain some Macros, which different Module's Header or Source file
*			may used 
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        	CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2016/09/23      CODER4			N/A          Original
*     1.1        2017/01/23      YCH			N/A          Original
************************************************************************************************/
#ifndef   _SYSCONFIG_H_
#define   _SYSCONFIG_H_

/* *****************************************************************************
   External Includes
   ***************************************************************************** */
#include  "Std_Types.h"

/* *****************************************************************************
   Hardware
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Xosc Input	{XOSC_4M, XOSC_8M, XOSC_12M, XOSC_16M, XOSC_40M}       ***/
/*---------------------------------------------------------------------------*/
#define		XOSC_8M				8000000
#define		XOSC_12M			12000000
#define		XOSC_16M			16000000
#define		XOSC_40M			40000000
#define		XOSC_INPUT			XOSC_8M		/* Used in Clock Module for SysClk Init */

/*---------------------------------------------------------------------------*/
/***	Need to Check Out SysClk EveryTime for App                         ***/
/*---------------------------------------------------------------------------*/
#define		CLK_64M				64000000	/* PIT Module Use for Timer Interval */
#define		SYS_CLK				CLK_64M
#define		MC_CLK_120MHZ

/*---------------------------------------------------------------------------*/
/***	ADC Align mode used in "m_ADC_Drv.h"        	                   ***/
/*---------------------------------------------------------------------------*/
#define		ADC_AL_RIGHT		0u
#define		ADC_AL_LEFT			1u
#define		ADC_ALIGN_MODE		ADC_AL_RIGHT

/*---------------------------------------------------------------------------*/
/***	CTU FIFO threshold register Val                                    ***/
/*---------------------------------------------------------------------------*/
//#define		SYS_CTU_THRESH_0		(6-1)		/* M=5+1 times ADC Sample (for DMA) */
//#define		SYS_CTU_THRESH_0		(12-1)		/* M=11+1 times ADC Sample (for DMA) */
//#define		SYS_CTU_THRESH_0		(10-1)		/* M=7+1 times ADC Sample (for DMA) */
//#define		SYS_CTU_THRESH_0		(8-1)		/* M=7+1 times ADC Sample (for DMA) */
//#define		SYS_CTU_THRESH_1		(6-1)		/* N=3+1 times ADC Sample (for DMA) */
//#define		SYS_CTU_THRESH_0		(6-1)		/* M=7+1 times ADC Sample (for DMA) */
//#define		SYS_CTU_THRESH_1		(8-1)		/* N=3+1 times ADC Sample (for DMA) */
#define		SYS_CTU_THRESH_0		(4-1)		/* M=7+1 times ADC Sample (for DMA) */
#define		SYS_CTU_THRESH_1		(10-1)		/* N=3+1 times ADC Sample (for DMA) */
#define		SYS_CTU_THRESH_2		0
#define		SYS_CTU_THRESH_3		0

/*---------------------------------------------------------------------------*/
/***	EDMA Intc Source Enabled Macro                                     ***/
/*---------------------------------------------------------------------------*/
#define		EDMA_CH0_ISR_EN
#define		PIT_CH1_ISR_EN
#define		PIT_CH2_ISR_EN
#define     CAN_MB_ISR_EN
#define TIMER_BASE 1
#endif  
/* End of file */