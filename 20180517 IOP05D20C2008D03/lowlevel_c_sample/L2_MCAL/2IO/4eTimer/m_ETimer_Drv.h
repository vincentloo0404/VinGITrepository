/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     m_ETimer_Drv.h
*
* @brief    Drive Header file for "m_ETimer_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/07/24      Lwt       	   	N/A          Original
*     1.1        2012/09/05      Lwt			N/A          Modify include file
*     1.2        2012/09/27      Lwt			N/A          Add Cfg file
*     1.3        2012/11/02      Lwt			N/A          Add History Comment
*     1.4        2012/12/04      Lwt			N/A          Modify eTimer Capt_Cfg, INTC and PIN_SEL
*     1.5        2012/12/11      Lwt			N/A          Code Simplify, Delete Reg_Bit Functions
*     1.6        2012/12/24      Lwt			N/A          Add C1FCNT, C2FCNT MASK for CAPT's Value
*     1.7        2013/01/18      Lwt			N/A          And CTU-eTimer Unit for 10KHz 50% Square Wave Out
************************************************************************************************/
#ifndef _M_ETIMER_DRV_H_
#define _M_ETIMER_DRV_H_


#ifdef 	M_ETIMER_DRV_C
#define M_ETIMER_DRV_EXT
#else
#define M_ETIMER_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include  	"m_GPIO.h"
#include	"Common.h"


/* *****************************************************************************
   *****************************************************************************
   macro definition
   *****************************************************************************
   ***************************************************************************** */
// register define
#define 	ET_BASE_ADDRESS				0xFFE18000ul
#define 	ET_MOUDLE_STEP				0x4000ul
#define 	ET_CHANNEL_STEP				0x0020ul
#define 	ET_MOUDLE_BASE_ADDRESS(x)	(ET_BASE_ADDRESS+(x)*ET_MOUDLE_STEP)
// channel define
#define 	ET_COMP1_OFFSET(x)			(0x00ul+(x)*ET_CHANNEL_STEP)
#define 	ET_COMP2_OFFSET(x)			(0x02ul+(x)*ET_CHANNEL_STEP)
#define 	ET_CAPT1_OFFSET(x)			(0x04ul+(x)*ET_CHANNEL_STEP)
#define 	ET_CAPT2_OFFSET(x)			(0x06ul+(x)*ET_CHANNEL_STEP)
#define 	ET_LOAD_OFFSET(x)			(0x08ul+(x)*ET_CHANNEL_STEP)
#define 	ET_HOLD_OFFSET(x)			(0x0Aul+(x)*ET_CHANNEL_STEP)
#define 	ET_CNTR_OFFSET(x)			(0x0Cul+(x)*ET_CHANNEL_STEP)
#define 	ET_CTRL1_OFFSET(x)			(0x0Eul+(x)*ET_CHANNEL_STEP)
#define 	ET_CTRL2_OFFSET(x)			(0x10ul+(x)*ET_CHANNEL_STEP)
#define 	ET_CTRL3_OFFSET(x)			(0x12ul+(x)*ET_CHANNEL_STEP)
#define 	ET_STS_OFFSET(x)			(0x14ul+(x)*ET_CHANNEL_STEP)
#define 	ET_INTDMA_OFFSET(x)			(0x16ul+(x)*ET_CHANNEL_STEP)
#define 	ET_CMPLD1_OFFSET(x)			(0x18ul+(x)*ET_CHANNEL_STEP)
#define 	ET_CMPLD2_OFFSET(x)			(0x1Aul+(x)*ET_CHANNEL_STEP)
#define 	ET_CCCTRL_OFFSET(x)			(0x1Cul+(x)*ET_CHANNEL_STEP)
#define 	ET_FILT_OFFSET(x)			(0x1Eul+(x)*ET_CHANNEL_STEP)
// channel common share
#define 	ET_WDTOL_OFFSET				0x0100ul
#define 	ET_WDTOH_OFFSET				0x0102ul
#define 	ET_ENBL_OFFSET				0x010Cul
#define 	ET_DREQ0_OFFSET				0x0110ul
#define 	ET_DREQ1_OFFSET				0x0112ul

// 
#define 	ETIMER_COMP1(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_COMP1_OFFSET(y)))
#define 	ETIMER_COMP2(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_COMP2_OFFSET(y)))
#define 	ETIMER_CAPT1(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CAPT1_OFFSET(y)))
#define 	ETIMER_CAPT2(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CAPT2_OFFSET(y)))
#define 	ETIMER_LOAD(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_LOAD_OFFSET(y)))
#define 	ETIMER_HOLD(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_HOLD_OFFSET(y)))
#define 	ETIMER_CNTR(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CNTR_OFFSET(y)))
#define 	ETIMER_CTRL1(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CTRL1_OFFSET(y)))
#define 	ETIMER_CTRL2(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CTRL2_OFFSET(y)))
#define 	ETIMER_CTRL3(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CTRL3_OFFSET(y)))
#define 	ETIMER_STS(x,y)				(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_STS_OFFSET(y)))
#define 	ETIMER_INTDMA(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_INTDMA_OFFSET(y)))
#define 	ETIMER_CMPLD1(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CMPLD1_OFFSET(y)))
#define 	ETIMER_CMPLD2(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CMPLD2_OFFSET(y)))
#define 	ETIMER_CCCTRL(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_CCCTRL_OFFSET(y)))
#define 	ETIMER_FILT(x,y)			(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_FILT_OFFSET(y)))

// PTR
#define 	ETIMER_STS_P(x,y)			((volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_STS_OFFSET(y)))

//
#define 	ETIMER_WDTOL(x)				(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_WDTOL_OFFSET))
#define 	ETIMER_WDTOH(x)				(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_WDTOH_OFFSET))
#define 	ETIMER_ENBL(x)				(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_ENBL_OFFSET))
#define 	ETIMER_DREQ0(x)				(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_DREQ0_OFFSET))
#define 	ETIMER_DREQ1(x)				(*(volatile uint16 *)(ET_MOUDLE_BASE_ADDRESS(x)+ET_DREQ1_OFFSET))

// Control register 1 (CTRL1)
#define 	ET_CTRL1_CNTMODE_MASK			(7<<13)
#define 	ET_CTRL1_PRI_MASK				(0x1F<<8)
#define 	ET_CTRL1_ONCE_MASK				(1<<7)
#define 	ET_CTRL1_LENGTH_MASK			(1<<6)
#define 	ET_CTRL1_DIR_MASK				(1<<5)
#define 	ET_CTRL1_SEC_MASK				(0x1F<<0)

// Control register 2 (CTRL2)
#define 	ET_CTRL2_OEN_MASK				(1<<15)
#define 	ET_CTRL2_RDNT_MASK				(1<<14)
#define 	ET_CTRL2_VAL_MASK				(1<<12)
#define 	ET_CTRL2_FORCE_MASK				(1<<11)
#define 	ET_CTRL2_COFRC_MASK				(1<<10)
#define 	ET_CTRL2_COINIT_MASK			(3<<8)
#define 	ET_CTRL2_SIPS_MASK				(1<<7)
#define 	ET_CTRL2_PIPS_MASK				(1<<6)
#define 	ET_CTRL2_OPS_MASK				(1<<5)
#define 	ET_CTRL2_MSTR_MASK				(1<<4)
#define 	ET_CTRL2_OUTMODE_MASK			(0x0F<<0)

// Control register 3 (CTRL3)
#define 	ET_CTRL3_STPEN_MASK				(1<<15)
#define 	ET_CTRL3_ROC_MASK				(3<<13)
#define 	ET_CTRL3_C1FCNT_MASK			(7<<2)
#define 	ET_CTRL3_C2FCNT_MASK			(7<<5)
#define 	ET_CTRL3_DBGEN_MASK				(3<<0)

// Status register (STS)
#define 	ET_SYS_WDF_MASK					(1<<9)
#define 	ET_SYS_RCF_MASK					(1<<8)
#define 	ET_SYS_ICF2_MASK				(1<<7)
#define 	ET_SYS_ICF1_MASK				(1<<6)
#define 	ET_SYS_IEHF_MASK				(1<<5)
#define 	ET_SYS_IELF_MASK				(1<<4)
#define 	ET_SYS_TOF_MASK					(1<<3)
#define 	ET_SYS_TCF2_MASK				(1<<2)
#define 	ET_SYS_TCF1_MASK				(1<<1)
#define 	ET_SYS_TCF_MASK					(1<<0)

// Interrupt and DMA enable register (INTDMA)
#define 	ET_INTDMA_ICF2DE_MASK			(1<<15)
#define 	ET_INTDMA_ICF1DE_MASK			(1<<14)
#define 	ET_INTDMA_CMPLD2DE_MASK			(1<<13)
#define 	ET_INTDMA_CMPLD1DE_MASK			(1<<12)
#define 	ET_INTDMA_WDF_MASK				(1<<9)
#define 	ET_INTDMA_RCF_MASK				(1<<8)
#define 	ET_INTDMA_ICF2_MASK				(1<<7)
#define 	ET_INTDMA_ICF1_MASK				(1<<6)
#define 	ET_INTDMA_IEHF_MASK				(1<<5)
#define 	ET_INTDMA_IELF_MASK				(1<<4)
#define 	ET_INTDMA_TOF_MASK				(1<<3)
#define 	ET_INTDMA_TCF2_MASK				(1<<2)
#define 	ET_INTDMA_TCF1_MASK				(1<<1)
#define 	ET_INTDMA_TCF_MASK				(1<<0)

// Compare and Capture Control register (CCCTRL)
#define 	ET_CCCTRL_CLC2_MASK				(7<<13)
#define 	ET_CCCTRL_CLC1_MASK				(7<<10)
#define 	ET_CCCTRL_CMPMODE_MASK			(3<<8)
#define 	ET_CCCTRL_CPT2MODE_MASK			(3<<6)
#define 	ET_CCCTRL_CPT1MODE_MASK			(3<<4)
#define 	ET_CCCTRL_CFWM_MASK				(3<<2)
#define 	ET_CCCTRL_ONESHOT_MASK			(1<<1)
#define 	ET_CCCTRL_ARM_MASK				(1<<0)

// Input Filter Register (FILT)
#define 	ET_FILT_CNT_MASK				(7<<8)
#define 	ET_FILT_PER_MASK				(0xFF<<0)


/* *****************************************************************************
   *****************************************************************************
   APP macro definition
   *****************************************************************************
   ***************************************************************************** */
// Moudle Number
#define 	ETIMER0  		0u
#define 	ETIMER1  		1u

// Channel Number
#define 	ET_CH_0  		0u
#define 	ET_CH_1  		1u
#define 	ET_CH_2  		2u
#define 	ET_CH_3  		3u
#define 	ET_CH_4  		4u
#define 	ET_CH_5  		5u

#define 	ET_CH_NUM  		6u

/* Compare Count */
#define 	ET_COMP_MAX				0xFFFF

// Count Mode
#define 	ET_CNT_NO_OPERATION			0u
#define 	ET_CNT_RISE					1u
#define 	ET_CNT_RISE_AND_FALL		2u
#define 	ET_CNT_RISE_WHILE_HIGH		3u
#define 	ET_CNT_QUAD					4u
#define 	ET_CNT_RISE_SEC_DIR			5u
#define 	ET_CNT_EDGE_SEC_TRG			6u
#define 	ET_CNT_CASCADED				7u

// Count Source 
#define 	ET_SRC_CNT0_INPUT			0x00u
#define 	ET_SRC_CNT1_INPUT			0x01u
#define 	ET_SRC_CNT2_INPUT			0x02u
#define 	ET_SRC_CNT3_INPUT			0x03u
#define 	ET_SRC_CNT4_INPUT			0x04u
#define 	ET_SRC_CNT5_INPUT			0x05u
#define 	ET_SRC_AUX0_INPUT			0x08u
#define 	ET_SRC_AUX1_INPUT			0x09u
#define 	ET_SRC_AUX2_INPUT			0x0Au
#define 	ET_SRC_CNT0_OUTPUT			0x10u
#define 	ET_SRC_CNT1_OUTPUT			0x11u
#define 	ET_SRC_CNT2_OUTPUT			0x12u
#define 	ET_SRC_CNT3_OUTPUT			0x13u
#define 	ET_SRC_CNT4_OUTPUT			0x14u
#define 	ET_SRC_CNT5_OUTPUT			0x15u
#define 	ET_SRC_IPB_DIV_1			0x18u
#define 	ET_SRC_IPB_DIV_2			0x19u
#define 	ET_SRC_IPB_DIV_4			0x1Au
#define 	ET_SRC_IPB_DIV_8			0x1Bu
#define 	ET_SRC_IPB_DIV_16			0x1Cu
#define 	ET_SRC_IPB_DIV_32			0x1Du
#define 	ET_SRC_IPB_DIV_64			0x1Eu
#define 	ET_SRC_IPB_DIV_128			0x1Fu

// Compare Mode
#define 	ET_CMPMODE_BOTH_UP			0x00u
#define 	ET_CMPMODE_CMP1_DOWN		0x01u
#define 	ET_CMPMODE_CMP1_UP			0x02u
#define 	ET_CMPMODE_BOTH_DOWN		0x03u

// Capture Mode
#define 	ET_CPTMODE_DIS				0x00u
#define 	ET_CPTMODE_FALL_EDGE		0x01u
#define 	ET_CPTMODE_RISE_EDGE		0x02u
#define 	ET_CPTMODE_BOTH_EDGE		0x03u

// ROC Mode	(Reload On Capture Mode)
#define 	ET_ROC_DIS					0x00u
#define 	ET_ROC_CAPT1				0x01u
#define 	ET_ROC_CAPT2				0x02u
#define 	ET_ROC_BOTH					0x03u

/* Input Transition Type */
#define 	ET_LENGTH_ROLL				0x00u
#define 	ET_LENGTH_REINIT			0x01u

/* Debug Actions Enable */
#define 	ET_DEBUG_NORMAL				0x00u
#define 	ET_DEBUG_HALT_CNT			0x01u
#define 	ET_DEBUG_OFLAG_LOW			0x02u
#define 	ET_DEBUG_BOTH				0x03u

/* Output Mode */
#define 	ET_OUTMODE_SOFT				0x00u
#define 	ET_OUTMODE_CLR				0x01u
#define 	ET_OUTMODE_SET				0x02u
#define 	ET_OUTMODE_TOGGLE			0x03u
#define 	ET_OUTMODE_TOGGLE_ALT		0x04u
#define 	ET_OUTMODE_SET_CMP1			0x05u
#define 	ET_OUTMODE_SET_CMP2			0x06u
#define 	ET_OUTMODE_SET_CLR_ROLL		0x07u
#define 	ET_OUTMODE_SET_CLR_CMP		0x08u
#define 	ET_OUTMODE_SET_CLR_ACT		0x09u
#define 	ET_OUTMODE_SET_CLR_UPDOWN	0x0Au
#define 	ET_OUTMODE_GATE_CLK			0x0Fu

/* *****************************************************************************
   *****************************************************************************
   variable declaration
   *****************************************************************************
   ***************************************************************************** */
extern volatile uint8  L2_eTimer0Chn0_flag_Uls_u08 ;
extern volatile uint16 L2_eTimer0Chn0_Capt1_Ct_u16 ;
extern volatile uint16 L2_eTimer0Chn0_Capt2_Ct_u16 ;

extern volatile uint8  L2_eTimer0Chn1_flag_Uls_u08 ;
extern volatile uint16 L2_eTimer0Chn1_Capt1_Ct_u16 ;
extern volatile uint16 L2_eTimer0Chn1_Capt2_Ct_u16 ;

extern volatile uint8  L2_eTimer0Chn4_flag_Uls_u08 ;
extern volatile uint16 L2_eTimer0Chn4_Capt1_Ct_u16 ;
extern volatile uint16 L2_eTimer0Chn4_Capt2_Ct_u16 ;

extern volatile uint8  L2_eTimer0Chn5_flag_Uls_u08 ;
extern volatile uint16 L2_eTimer0Chn5_Capt1_Ct_u16 ;
extern volatile uint16 L2_eTimer0Chn5_Capt2_Ct_u16 ;

/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
extern	void	mETimer_Channel_En(uint8 ModuleNum, uint8 ChanNum);
extern	void	mETimer_Channel_Dis(uint8 ModuleNum, uint8 ChanNum);
extern	void	mETimer_Capture_Start(uint8 ModuleNum, uint8 ChanNum);
extern	void	mETimer_Capture_Stop(uint8 ModuleNum, uint8 ChanNum);
extern	void	mETimer0_Init(void);
extern	void	mETimer1_Init(void);
extern	uint8	mETimer1_Capture_CH0(uint16 *CapVal1, uint16 *CapVal2);
extern	void	mETimer_Channel_Shut(uint8 ModuleNum, uint8 ChanNum);
extern	void	mETimer_Channel_Open(uint8 ModuleNum, uint8 ChanNum);

extern void L2_eTimer_Per1(void);


#endif						// _M_ETIMER_DRV_H_

