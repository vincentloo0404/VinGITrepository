/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     m_ETimer_Cfg.h
*
* @brief    Config Header file for "m_ETimer_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/27      CODER2       	   	N/A          Original
*     1.1        2012/11/02      CODER2			N/A          Add History Comment
*     1.2        2012/12/04      CODER2			N/A          Modify eTimer Capt_Cfg, INTC and PIN_SEL
*     1.3        2012/12/11      CODER2			N/A          Code Simplify, Delete Reg_Bit Functions
*     1.4        2012/12/24      CODER2			N/A          Modify eTimer CAPT's Mode and CFWM=0 ;
*     1.5        2013/01/18      CODER2			N/A          And CTU-eTimer Unit for 10KHz 50% Square Wave Out
*     1.6        2014/07/21      CODER2			N/A          Add and Modify eTimer Config for V1.6 HW
************************************************************************************************/
#ifndef _M_ETIMER_CFG_H_
#define _M_ETIMER_CFG_H_


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_ETimer_Drv.h"


/* *****************************************************************************
   *****************************************************************************
   Config Macro definition
   *****************************************************************************
   ***************************************************************************** */
/* Over Time Delay */
#define 	ET_DELAY				1000


/* Module Used */
#define		ETIMER0_ENABLE
#define		ETIMER1_ENABLE

/* Channel Used */
//#define		ETIMER0_CH0
//#define		ETIMER0_CH1
//#define		ETIMER0_CH4
#define		ETIMER0_CH5

//#define		ETIMER1_CH0 
//#define		ETIMER1_CH1
//#define		ETIMER1_CH2
//#define		ETIMER1_CH3
//#define		ETIMER1_CH4
//#define		ETIMER1_CH5

/* Quadrature Mode Enabled */
#define		ETIMER_QUAD_EN

/* Capt Strcture */
typedef	struct _eTimer_CAPT_ 
{
	uint16	CAPT1_Val[2];
	uint16	CAPT2_Val[2];
    union 
    {
        uint16  Bytes;
		struct 
		{
			uint8	C2FCNT;
			uint8	C1FCNT;
		} Bits;
    } Fcnt;
}stc_eTimer_CAPT;

/* Capt Strcture 2 */
typedef	struct _eTimer_CAPT_Level_ 
{
	uint16	CAPT1_Val;
	uint8	Capt_Level;
	uint8	RSV;
}stc_eTimer_Capt_Level;


#ifdef	ETIMER0_ENABLE
	/* Interrupt Source Enabled */
	#define		ETIMER0_INTC_ENABLE
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 0	                                           ***/
/*---------------------------------------------------------------------------*/
	#ifdef	ETIMER0_CH0
		/* ET0_4 PIN & PCR */
		#define		ET0_0_PIN			A0
		#define		ET0_0_PCR			(ALT1|B_IBE)	
		/* no PSMI */			
		/* Cfg */
		#define		ET0_CH0_CNT_MODE	ET_CNT_RISE
		#define		ET0_CH0_PRI_SRC		ET_SRC_IPB_DIV_32	
		#define		ET0_CH0_SEC_SRC		ET_SRC_CNT0_INPUT
		#define		ET0_CH0_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET0_CH0_CPT1_MODE	ET_CPTMODE_RISE_EDGE
		#define		ET0_CH0_CPT2_MODE	ET_CPTMODE_FALL_EDGE			
		#define		ET0_CH0_CPT_FIFO	0x0
		#define		ET0_CH0_ROC_MODE	ET_ROC_CAPT1
		#define		ET0_CH0_DBGEN_MODE	ET_DEBUG_HALT_CNT
		/* CTRL1 */
		#define		ET0_CH0_CTRL1_VAL	((ET0_CH0_CNT_MODE<<13)|(ET0_CH0_PRI_SRC<<8)|(ET0_CH0_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET0_CH0_CTRL3_VAL	((ET0_CH0_DBGEN_MODE<<0)|(ET0_CH0_ROC_MODE<<13))
		/* INTDMA */
		#define		ET0_CH0_INTDMA_VAL	0//(ET_INTDMA_ICF1_MASK)
		/* CCCTRL */
		#define		ET0_CH0_CCCTRL_VAL	((ET0_CH0_CMP_MODE<<8)|(ET0_CH0_CPT1_MODE<<4)|(ET0_CH0_CPT2_MODE<<6)|(ET0_CH0_CPT_FIFO<<2))
	#endif


/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 1	                                           ***/
/*---------------------------------------------------------------------------*/
	#ifdef	ETIMER0_CH1
		/* ET0_4 PIN & PCR */
		#define		ET0_1_PIN			A1
		#define		ET0_1_PCR			(ALT1|B_IBE)	
		/* no PSMI */			
		/* Cfg */
		#define		ET0_CH1_CNT_MODE	ET_CNT_RISE
		#define		ET0_CH1_PRI_SRC		ET_SRC_IPB_DIV_8	
		#define		ET0_CH1_SEC_SRC		ET_SRC_CNT1_INPUT
		#define		ET0_CH1_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET0_CH1_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET0_CH1_CPT2_MODE	ET_CPTMODE_RISE_EDGE			
		#define		ET0_CH1_CPT_FIFO	0x0
		#define		ET0_CH1_ROC_MODE	ET_ROC_CAPT1
		#define		ET0_CH1_DBGEN_MODE	ET_DEBUG_HALT_CNT
		/* CTRL1 */
		#define		ET0_CH1_CTRL1_VAL	((ET0_CH1_CNT_MODE<<13)|(ET0_CH1_PRI_SRC<<8)|(ET0_CH1_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET0_CH1_CTRL3_VAL	((ET0_CH1_DBGEN_MODE<<0)|(ET0_CH1_ROC_MODE<<13))
		/* INTDMA */
		#define		ET0_CH1_INTDMA_VAL	0//(ET_INTDMA_ICF1_MASK)
		/* CCCTRL */
		#define		ET0_CH1_CCCTRL_VAL	((ET0_CH1_CMP_MODE<<8)|(ET0_CH1_CPT1_MODE<<4)|(ET0_CH1_CPT2_MODE<<6)|(ET0_CH1_CPT_FIFO<<2))
	#endif

/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 4	                                           ***/
/*---------------------------------------------------------------------------*/
	#ifdef	ETIMER0_CH4
		/* ET0_4 PIN & PCR */
		#define		ET0_4_PIN			C11
		#define		ET0_4_PCR			(ALT1|B_IBE)	
		/* no PSMI */		
		/* ET9_4 PSMI */
		#define		ET0_4_PSMI			7
		#define		ET0_4_PSMI_VAL		0x01					

		/* Cfg */
		#define		ET0_CH4_CNT_MODE	ET_CNT_RISE
		#define		ET0_CH4_PRI_SRC		ET_SRC_IPB_DIV_4	
		#define		ET0_CH4_SEC_SRC		ET_SRC_CNT4_INPUT
		#define		ET0_CH4_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET0_CH4_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET0_CH4_CPT2_MODE	ET_CPTMODE_RISE_EDGE			
		#define		ET0_CH4_CPT_FIFO	0x0
		#define		ET0_CH4_ROC_MODE	ET_ROC_CAPT1
		#define		ET0_CH4_DBGEN_MODE	ET_DEBUG_HALT_CNT
		/* CTRL1 */		  
		#define		ET0_CH4_CTRL1_VAL	((ET0_CH4_CNT_MODE<<13)|(ET0_CH4_PRI_SRC<<8)|(ET0_CH4_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET0_CH4_CTRL3_VAL	((ET0_CH4_DBGEN_MODE<<0)|(ET0_CH4_ROC_MODE <<13))
		/* INTDMA */
		#define		ET0_CH4_INTDMA_VAL	0//(ET_INTDMA_ICF1_MASK)
		/* CCCTRL */
		#define		ET0_CH4_CCCTRL_VAL	((ET0_CH4_CMP_MODE<<8)|(ET0_CH4_CPT1_MODE<<4)|(ET0_CH4_CPT2_MODE<<6)|(ET0_CH4_CPT_FIFO<<2))
	#endif

/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 5	                                           ***/
/*---------------------------------------------------------------------------*/
	#ifdef	ETIMER0_CH5
//		/* ET0_5 PIN & PCR */
//		#define		ET0_5_PIN			B8
//		#define		ET0_5_PCR			(ALT3|B_IBE)
//		/* no PSMI */
//		#define		ET0_5_PSMI			8
//		#define		ET0_5_PSMI_VAL		0x01

		/* ET0_5 PIN & PCR */
		#define		ET0_5_PIN			C12
		#define		ET0_5_PCR			(ALT1|B_IBE)
		/* no PSMI */		
		#define		ET0_5_PSMI			8
		#define		ET0_5_PSMI_VAL		0x00

		/* Cfg */
		#define		ET0_CH5_CNT_MODE	ET_CNT_RISE
		#define		ET0_CH5_PRI_SRC		ET_SRC_IPB_DIV_4	
		#define		ET0_CH5_SEC_SRC		ET_SRC_CNT5_INPUT
		#define		ET0_CH5_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET0_CH5_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET0_CH5_CPT2_MODE	ET_CPTMODE_RISE_EDGE			
		#define		ET0_CH5_CPT_FIFO	0x0
		#define		ET0_CH5_ROC_MODE	ET_ROC_CAPT1
		#define		ET0_CH5_DBGEN_MODE	ET_DEBUG_HALT_CNT
		/* CTRL1 */		  
		#define		ET0_CH5_CTRL1_VAL	((ET0_CH5_CNT_MODE<<13)|(ET0_CH5_PRI_SRC<<8)|(ET0_CH5_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET0_CH5_CTRL3_VAL	((ET0_CH5_DBGEN_MODE<<0)|(ET0_CH5_ROC_MODE<<13))
		/* INTDMA */
		#define		ET0_CH5_INTDMA_VAL	0//(ET_INTDMA_ICF1_MASK)
		/* CCCTRL */
		#define		ET0_CH5_CCCTRL_VAL	((ET0_CH5_CMP_MODE<<8)|(ET0_CH5_CPT1_MODE<<4)|(ET0_CH5_CPT2_MODE<<6)|(ET0_CH5_CPT_FIFO<<2))
	#endif


#endif

#ifdef	ETIMER1_ENABLE
	/* Interrupt Source Enalbed */
	#define		ETIMER1_INTC_ENABLE


	/* Module 1 , Channel 0 , Quadrature A*/
	#if defined(ETIMER1_CH0) 

		/* Cfg */
		#define		ET1_CH0_CNT_MODE	ET_CNT_RISE
		#define		ET1_CH0_PRI_SRC		ET_SRC_IPB_DIV_128	
		#define		ET1_CH0_SEC_SRC		ET_SRC_CNT2_INPUT
		#define		ET1_CH0_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET1_CH0_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET1_CH0_CPT2_MODE	ET_CPTMODE_RISE_EDGE			
		#define		ET1_CH0_CPT_FIFO	0x0
		#define		ET1_CH0_ROC_MODE	ET_ROC_BOTH
		#define		ET1_CH0_DBGEN_MODE	ET_DEBUG_HALT_CNT
		
		/* LOAD */
		#define     ET1_CH0_LOAD        0x0000
		/* CTRL1 */	  	  
		#define		ET1_CH0_CTRL1_VAL	((ET1_CH0_CNT_MODE<<13)|(ET1_CH0_PRI_SRC<<8)|(ET1_CH0_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET1_CH0_CTRL3_VAL	(ET1_CH0_DBGEN_MODE<<0) | (ET1_CH0_ROC_MODE << 13)
		/* INTDMA */
		#define		ET1_CH0_INTDMA_VAL	0//(ET_INTDMA_ICF1_MASK )
		/* CCCTRL */
		#define		ET1_CH0_CCCTRL_VAL	((ET1_CH0_CMP_MODE<<8)|(ET1_CH0_CPT1_MODE<<4)|(ET1_CH0_CPT2_MODE<<6)|(ET1_CH0_CPT_FIFO<<2))
			
	#endif


	/* Module 1 , Channel 1, Quadrature B */
	#if defined(ETIMER1_CH1) 
		/* ET1_1 PIN & PCR */
		#define		ET1_1_PIN			C13
		#define		ET1_1_PCR			(ALT1|B_IBE)
		/* ET1_1 PSMI */
		#define		ET1_1_PSMI			10
		#define		ET1_1_PSMI_VAL		0x0		

		/* Cfg */
		#define		ET1_CH1_CNT_MODE	ET_CNT_RISE
		#define		ET1_CH1_PRI_SRC		ET_SRC_IPB_DIV_128	
		#define		ET1_CH1_SEC_SRC		ET_SRC_CNT1_INPUT
		#define		ET1_CH1_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET1_CH1_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET1_CH1_CPT2_MODE	ET_CPTMODE_RISE_EDGE			
		#define		ET1_CH1_CPT_FIFO	0x0
		#define		ET1_CH1_ROC_MODE	ET_ROC_BOTH
		#define		ET1_CH1_DBGEN_MODE	ET_DEBUG_HALT_CNT
		
		/* LOAD */
		#define     ET1_CH1_LOAD        0x0000
		/* CTRL1 */	  	  
		#define		ET1_CH1_CTRL1_VAL	((ET1_CH1_CNT_MODE<<13)|(ET1_CH1_PRI_SRC<<8)|(ET1_CH1_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET1_CH1_CTRL3_VAL	(ET1_CH1_DBGEN_MODE<<0) | (ET1_CH1_ROC_MODE << 13)
		/* INTDMA */
		#define		ET1_CH1_INTDMA_VAL	0//(ET_INTDMA_ICF1_MASK | ET_INTDMA_ICF2_MASK)
		/* CCCTRL */
		#define		ET1_CH1_CCCTRL_VAL	((ET1_CH1_CMP_MODE<<8)|(ET1_CH1_CPT1_MODE<<4)|(ET1_CH1_CPT2_MODE<<6)|(ET1_CH1_CPT_FIFO<<2))
			
	#endif


	/* Module 1 , Channel 2, Quadrature A */
	#if defined(ETIMER1_CH2) && defined(ETIMER_QUAD_EN)
		/* ET1_2 PIN & PCR */
		#define		ET1_2_PIN			C14
		#define		ET1_2_PCR			(ALT1|B_IBE)
		/* ET1_2 PSMI */
		#define		ET1_2_PSMI			11
		#define		ET1_2_PSMI_VAL		0x01
		/* Cfg */
		#define		ET1_CH2_CNT_MODE	ET_CNT_QUAD
		#define		ET1_CH2_PRI_SRC		ET_SRC_CNT2_INPUT
		#define		ET1_CH2_SEC_SRC		ET_SRC_CNT1_INPUT
		#define		ET1_CH2_LENGTH		ON
		#define		ET1_CH2_CLC2		0x6	/* Load CNTR with CMPLD2 upon successful compare with the value in COMP1. */
		#define		ET1_CH2_CLC1		0x7	/* Load CNTR with CMPLD1 upon successful compare with the value in COMP2. */
		#define		ET1_CH2_CMP_MODE	ET_CMPMODE_CMP1_DOWN	
		#define		ET1_CH2_DBGEN_MODE	ET_DEBUG_HALT_CNT
		#define		ET1_CH2_DOWN_VAL	0x0047
		#define		ET1_CH2_UP_VAL		0xFFB8
		#define		ET1_CH2_FILT_CNT	0x2
		#define		ET1_CH2_FILT_PER	0x02	/* {[(FILT_CNT + 3) ¡Á FILT_PER] + 2} IPBus clock periods. */

		/* CTRL1 */
		#define		ET1_CH2_CTRL1_VAL	((ET1_CH2_CNT_MODE<<13)|(ET1_CH2_PRI_SRC<<8)|(ET1_CH2_SEC_SRC<<0)|(ET1_CH2_LENGTH<<6))
		/* COMP1 */
		#define		ET1_CH2_COMP1_VAL	ET1_CH2_DOWN_VAL
		/* COMP2 */
		#define		ET1_CH2_COMP2_VAL	ET1_CH2_UP_VAL
		/* CMPLD1 */
		#define		ET1_CH2_CMPLD1_VAL	ET1_CH2_DOWN_VAL
		/* CMPLD2 */
		#define		ET1_CH2_CMPLD2_VAL	ET1_CH2_UP_VAL
		/* CTRL3 */
		#define		ET1_CH2_CTRL3_VAL	(ET1_CH2_DBGEN_MODE<<0)		
		/* CCCTRL */
		#define		ET1_CH2_CCCTRL_VAL	((ET1_CH2_CLC2<<13)|(ET1_CH2_CLC1<<10)|(ET1_CH2_CMP_MODE<<8))	
		/* FILT */
		#define		ET1_CH2_FILT_VAL	((ET1_CH2_FILT_CNT<<8)|(ET1_CH2_FILT_PER<<0))

			
	#endif


	/* Module 1 , Channel 3 */
	#ifdef	ETIMER1_CH3
		/* ET1_3 PIN & PCR */
		#define		ET1_3_PIN			D2
		#define		ET1_3_PCR			(ALT2|B_IBE)			
		/* ET1_3 PSMI */
		#define		ET1_3_PSMI			12
		#define		ET1_3_PSMI_VAL		0x01					
		/* Cfg */
		#define		ET1_CH3_CNT_MODE	ET_CNT_RISE_AND_FALL
		#define		ET1_CH3_PRI_SRC		ET_SRC_IPB_DIV_4
		#define		ET1_CH3_SEC_SRC		ET_SRC_CNT3_INPUT
		#define		ET1_CH3_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET1_CH3_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET1_CH3_CPT2_MODE	ET_CPTMODE_RISE_EDGE
		#define		ET1_CH3_CPT_FIFO	0x0
		#define		ET1_CH3_ROC_MODE	ET_ROC_DIS
		#define		ET1_CH3_DBGEN_MODE	ET_DEBUG_HALT_CNT
		/* CTRL1 */
		#define		ET1_CH3_CTRL1_VAL	((ET1_CH3_CNT_MODE<<13)|(ET1_CH3_PRI_SRC<<8)|(ET1_CH3_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET1_CH3_CTRL3_VAL	((ET1_CH3_ROC_MODE<<13)|(ET1_CH3_DBGEN_MODE<<0))
		/* INTDMA */
		#define		ET1_CH3_INTDMA_VAL	(ET_INTDMA_ICF1_MASK | ET_INTDMA_ICF2_MASK)
		/* CCCTRL */
		#define		ET1_CH3_CCCTRL_VAL	((ET1_CH3_CMP_MODE<<8)|(ET1_CH3_CPT1_MODE<<4)|(ET1_CH3_CPT2_MODE<<6)|(ET1_CH3_CPT_FIFO<<2))
	#endif


	/* Module 1 , Channel 4 */
	#ifdef	ETIMER1_CH4
		/* ET1_4 PIN & PCR */
		#define		ET1_4_PIN			A14
		#define		ET1_4_PCR			(ALT2|B_IBE)			
		/* ET1_4 PSMI */
		#define		ET1_4_PSMI			13
		#define		ET1_4_PSMI_VAL		0x00					
		/* Cfg */
		#define		ET1_CH4_CNT_MODE	ET_CNT_RISE_AND_FALL
		#define		ET1_CH4_PRI_SRC		ET_SRC_IPB_DIV_4
		#define		ET1_CH4_SEC_SRC		ET_SRC_CNT4_INPUT
		#define		ET1_CH4_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET1_CH4_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET1_CH4_CPT2_MODE	ET_CPTMODE_RISE_EDGE
		#define		ET1_CH4_CPT_FIFO	0x0
		#define		ET1_CH4_ROC_MODE	ET_ROC_DIS
		#define		ET1_CH4_DBGEN_MODE	ET_DEBUG_HALT_CNT
		/* CTRL1 */
		#define		ET1_CH4_CTRL1_VAL	((ET1_CH4_CNT_MODE<<13)|(ET1_CH4_PRI_SRC<<8)|(ET1_CH4_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET1_CH4_CTRL3_VAL	((ET1_CH4_ROC_MODE<<13)|(ET1_CH4_DBGEN_MODE<<0))
		/* INTDMA */
		#define		ET1_CH4_INTDMA_VAL	(ET_INTDMA_ICF1_MASK | ET_INTDMA_ICF2_MASK)
		/* CCCTRL */
		#define		ET1_CH4_CCCTRL_VAL	((ET1_CH4_CMP_MODE<<8)|(ET1_CH4_CPT1_MODE<<4)|(ET1_CH4_CPT2_MODE<<6)|(ET1_CH4_CPT_FIFO<<2))
	#endif

	
	/* Module 1 , Channel 5 */
	#ifdef	ETIMER1_CH5
		/* ET1_4 PIN & PCR */
		#define		ET1_5_PIN			A15
		#define		ET1_5_PCR			(ALT2|B_IBE)
		/* ET1_4 PSMI */
		#define		ET1_5_PSMI			14
		#define		ET1_5_PSMI_VAL		0x01							
		/* Cfg */
		#define		ET1_CH5_CNT_MODE	ET_CNT_RISE_AND_FALL
		#define		ET1_CH5_PRI_SRC		ET_SRC_IPB_DIV_4
		#define		ET1_CH5_SEC_SRC		ET_SRC_CNT5_INPUT
		#define		ET1_CH5_CMP_MODE	ET_CMPMODE_CMP1_UP
		#define		ET1_CH5_CPT1_MODE	ET_CPTMODE_FALL_EDGE
		#define		ET1_CH5_CPT2_MODE	ET_CPTMODE_RISE_EDGE		
		#define		ET1_CH5_CPT_FIFO	0x0
		#define		ET1_CH5_ROC_MODE	ET_ROC_DIS		
		#define		ET1_CH5_DBGEN_MODE	ET_DEBUG_HALT_CNT

		/* CTRL1 */
		#define		ET1_CH5_CTRL1_VAL	((ET1_CH5_CNT_MODE<<13)|(ET1_CH5_PRI_SRC<<8)|(ET1_CH5_SEC_SRC<<0))
		/* CTRL3 */
		#define		ET1_CH5_CTRL3_VAL	((ET1_CH5_ROC_MODE<<13)|(ET1_CH5_DBGEN_MODE<<0))
		/* INTDMA */
		#define		ET1_CH5_INTDMA_VAL	(ET_INTDMA_ICF1_MASK | ET_INTDMA_ICF2_MASK)
		/* CCCTRL */
		#define		ET1_CH5_CCCTRL_VAL	((ET1_CH5_CMP_MODE<<8)|(ET1_CH5_CPT1_MODE<<4)|(ET1_CH5_CPT2_MODE<<6)|(ET1_CH5_CPT_FIFO<<2))
	
	#endif

#endif

#endif						// _M_ETIMER_CFG_H_

