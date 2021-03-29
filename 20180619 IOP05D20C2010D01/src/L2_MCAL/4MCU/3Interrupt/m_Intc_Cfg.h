/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_Intc_Cfg.h
*
* @brief    Config Header file for "m_Intc_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2016/09/23     CODER4          	N/A          Original
************************************************************************************************/

#ifndef _M_INTC_CFG_H_
#define _M_INTC_CFG_H_

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include	"m_Intc_Drv.h"
#include	"SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   Config definiton
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	EDMA IRQ                                                           ***/
/*---------------------------------------------------------------------------*/
#define		IRQ_EDMA_PRIORITY		PRIOR_12
#define		IRQ_PIT_PRIORITY		PRIOR_11
#define		IRQ_CAN_PRIORITY	    PRIOR_8
#ifdef	EDMA_CH0_ISR_EN
	#define     IRQ_11_FCN				mEDMA_CH0_11_ISR
	#define     IRQ_11_PRIORITY			IRQ_EDMA_PRIORITY
#endif
#ifdef	EDMA_CH1_ISR_EN
	#define     IRQ_12_FCN				mEDMA_CH1_12_ISR
	#define     IRQ_12_PRIORITY			IRQ_EDMA_PRIORITY
#endif
#ifdef	PIT_CH1_ISR_EN
	#define     IRQ_60_FCN				mPit_Timer1_ISR
	#define     IRQ_60_PRIORITY			IRQ_PIT_PRIORITY
#endif
#ifdef	PIT_CH2_ISR_EN
	#define     IRQ_61_FCN				mPit_Timer2_ISR
	#define     IRQ_61_PRIORITY			IRQ_PIT_PRIORITY
#endif

/*---------------------------------------------------------------------------*/
/***	ECC                                                                ***/
/*---------------------------------------------------------------------------*/
#define IRQ_35_FCN                     ECC_DBD_Isr
#define IRQ_35_PRIORITY                0x5

/*---------------------------------------------------------------------------*/
/***	OCP INTC                                                            ***/
/*---------------------------------------------------------------------------*/
#ifdef	CAN_MB_ISR_EN
	#define     IRQ_72_FCN				mCAN_IRQ72_MB_16_31_ISR
	#define     IRQ_72_PRIORITY			IRQ_CAN_PRIORITY
#endif
//#define IRQ_191_FCN                     PWM_OCP_Isr
//#define IRQ_191_PRIORITY                PRIOR_15
#endif