/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_CTU_Drv.h
*
* @brief    Drive Header file for "m_CTU_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/06/17      Lwt       	   	N/A          Original
*     1.1        2012/08/16      Lwt			N/A          Modify Drv, Add ADC_FIFO, Add Poll
*     1.2        2012/09/05      Lwt			N/A          Modify include file
*     1.3        2012/09/25      Lwt			N/A          Modify ADC Command List
*     1.4        2012/09/27      Lwt			N/A          Add Cfg file
*     1.5        2012/10/09      Lwt			N/A          Modify Drv and Cfg Files
*     1.6        2012/11/02      Lwt			N/A          Add History Comment
*     1.7        2013/02/26      Lwt			N/A          Code Simplify, Delete Reg_Bit Functions
************************************************************************************************/

#ifndef _M_CTU_DRV_H_
#define _M_CTU_DRV_H_

#ifdef 	M_CTU_DRV_C
#define M_CTU_DRV_EXT
#else
#define M_CTU_DRV_EXT 	extern
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
   Drive Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Register Address Define                                            ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_BASE_ADDRESS				0xFFE0C000ul
#define 	CTU_TGSISR_OFFSET				0x0ul
#define 	CTU_TGSCR_OFFSET				0x4ul
#define 	CTU_TCR_OFFSET(x)				(0x06ul+(x)*0x2)
#define 	CTU_TGSCCR_OFFSET				0x16ul
#define 	CTU_TGSCRR_OFFSET				0x18ul
#define 	CTU_CLCR1_OFFSET				0x1Cul
#define 	CTU_CLCR2_OFFSET				0x20ul
#define 	CTU_THCR1_OFFSET				0x24ul
#define 	CTU_THCR2_OFFSET				0x28ul
#define 	CTU_CLR_OFFSET(x)				(0x2Cul+(x)*0x2)
#define 	CTU_FDCR_OFFSET					0x6Cul
#define 	CTU_FCR_OFFSET					0x70ul
#define 	CTU_FTH_OFFSET					0x74ul
#define 	CTU_FST_OFFSET					0x7Cul
#define 	CTU_FR_OFFSET(x)				(0x80ul+(x)*0x4)
#define 	CTU_FL_OFFSET(x)				(0xA0ul+(x)*0x4)
#define 	CTU_CTUEFR_OFFSET				0xC0ul
#define 	CTU_CTUIFR_OFFSET				0xC2ul
#define 	CTU_CTUIR_OFFSET				0xC4ul
#define 	CTU_COTR_OFFSET					0xC6ul
#define 	CTU_CTUCR_OFFSET				0xC8ul
#define 	CTU_CTUDF_OFFSET				0xCAul
#define 	CTU_CTUPCR_OFFSET				0xCCul

/*---------------------------------------------------------------------------*/
/***	Trigger Generator Sub-unit Input Selection Register (TGSISR)       ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_TGSISR						(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_TGSISR_OFFSET))
#define 	CTU_TGSISR_IN15_FALL_EN_MASK		(1<<31)
#define 	CTU_TGSISR_IN15_RISE_EN_MASK		(1<<30)
#define 	CTU_TGSISR_IN14_FALL_EN_MASK		(1<<29)
#define 	CTU_TGSISR_IN14_RISE_EN_MASK		(1<<28)
#define 	CTU_TGSISR_IN13_FALL_EN_MASK		(1<<27)
#define 	CTU_TGSISR_IN13_RISE_EN_MASK		(1<<26)
#define 	CTU_TGSISR_IN12_FALL_EN_MASK		(1<<25)
#define 	CTU_TGSISR_IN12_RISE_EN_MASK		(1<<24)
#define 	CTU_TGSISR_IN11_FALL_EN_MASK		(1<<23)
#define 	CTU_TGSISR_IN11_RISE_EN_MASK		(1<<22)
#define 	CTU_TGSISR_IN10_FALL_EN_MASK		(1<<21)
#define 	CTU_TGSISR_IN10_RISE_EN_MASK		(1<<20)
#define 	CTU_TGSISR_IN9_FALL_EN_MASK			(1<<19)
#define 	CTU_TGSISR_IN9_RISE_EN_MASK			(1<<18)
#define 	CTU_TGSISR_IN8_FALL_EN_MASK			(1<<17)
#define 	CTU_TGSISR_IN8_RISE_EN_MASK			(1<<16)
#define 	CTU_TGSISR_IN7_FALL_EN_MASK			(1<<15)
#define 	CTU_TGSISR_IN7_RISE_EN_MASK			(1<<14)
#define 	CTU_TGSISR_IN6_FALL_EN_MASK			(1<<13)
#define 	CTU_TGSISR_IN6_RISE_EN_MASK			(1<<12)
#define 	CTU_TGSISR_IN5_FALL_EN_MASK			(1<<11)
#define 	CTU_TGSISR_IN5_RISE_EN_MASK			(1<<10)		/* PWMA Rise */
#define 	CTU_TGSISR_IN4_FALL_EN_MASK			(1<<9)
#define 	CTU_TGSISR_IN4_RISE_EN_MASK			(1<<8)
#define 	CTU_TGSISR_IN3_FALL_EN_MASK			(1<<7)
#define 	CTU_TGSISR_IN3_RISE_EN_MASK			(1<<6)
#define 	CTU_TGSISR_IN2_FALL_EN_MASK			(1<<5)
#define 	CTU_TGSISR_IN2_RISE_EN_MASK			(1<<4)
#define 	CTU_TGSISR_IN1_FALL_EN_MASK			(1<<3)
#define 	CTU_TGSISR_IN1_RISE_EN_MASK			(1<<2)
#define 	CTU_TGSISR_IN0_FALL_EN_MASK			(1<<1)
#define 	CTU_TGSISR_IN0_RISE_EN_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	Trigger Generator Sub-unit Control Register (TGSCR)                ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_TGSCR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_TGSCR_OFFSET))
#define 	CTU_TGSCR_ET_TM_MASK			(1<<8)
#define 	CTU_TGSCR_PRES_MASK				(0x3<<6)
#define 	CTU_TGSCR_MRS_SM_MASK			(0x1F<<1)
#define 	CTU_TGSCR_TGS_SM_MASK			(0x1<<0)

/*---------------------------------------------------------------------------*/
/***	 Trigger x Compare Register (TxCR, x = 0...7)                      ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_TCR(x)						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_TCR_OFFSET(x)))

/*---------------------------------------------------------------------------*/
/***	TGS Counter Compare Register (TGSCCR)                              ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_TGSCCR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_TGSCCR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	TGS Counter Reload Register (TGSCRR)                               ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_TGSCRR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_TGSCRR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	Commands List Control Register 1 (CLCR1)                           ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CLCR1						(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_CLCR1_OFFSET))
#define 	CTU_CLCR1_T3_INDEX_MASK			(0x1F<<24)
#define 	CTU_CLCR1_T2_INDEX_MASK			(0x1F<<16)
#define 	CTU_CLCR1_T1_INDEX_MASK			(0x1F<<8)
#define 	CTU_CLCR1_T0_INDEX_MASK			(0x1F<<0)

/*---------------------------------------------------------------------------*/
/***	Commands list control register 2 (CLCR2)                           ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CLCR2						(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_CLCR2_OFFSET))
#define 	CTU_CLCR2_T7_INDEX_MASK			(0x1F<<24)
#define 	CTU_CLCR2_T6_INDEX_MASK			(0x1F<<16)
#define 	CTU_CLCR2_T5_INDEX_MASK			(0x1F<<8)
#define 	CTU_CLCR2_T4_INDEX_MASK			(0x1F<<0)

/*---------------------------------------------------------------------------*/
/***	Trigger handler control register 1 (THCR1)                         ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_THCR1						(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_THCR1_OFFSET))
#define 	CTU_THCR1_T3_EN_MASK			(1<<28)
#define 	CTU_THCR1_T3_ETE_MASK			(1<<27)
#define 	CTU_THCR1_T3_T1E_MASK			(1<<26)
#define 	CTU_THCR1_T3_T0E_MASK			(1<<25)
#define 	CTU_THCR1_T3_ADCE_MASK			(1<<24)
#define 	CTU_THCR1_T2_EN_MASK			(1<<20)
#define 	CTU_THCR1_T2_ETE_MASK			(1<<19)
#define 	CTU_THCR1_T2_T1E_MASK			(1<<18)
#define 	CTU_THCR1_T2_T0E_MASK			(1<<17)
#define 	CTU_THCR1_T2_ADCE_MASK			(1<<16)
#define 	CTU_THCR1_T1_EN_MASK			(1<<12)
#define 	CTU_THCR1_T1_ETE_MASK			(1<<11)
#define 	CTU_THCR1_T1_T1E_MASK			(1<<10)
#define 	CTU_THCR1_T1_T0E_MASK			(1<<9)
#define 	CTU_THCR1_T1_ADCE_MASK			(1<<8)
#define 	CTU_THCR1_T0_EN_MASK			(1<<4)
#define 	CTU_THCR1_T0_ETE_MASK			(1<<3)
#define 	CTU_THCR1_T0_T1E_MASK			(1<<2)
#define 	CTU_THCR1_T0_T0E_MASK			(1<<1)
#define 	CTU_THCR1_T0_ADCE_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	Trigger handler control register 2 (THCR1)                         ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_THCR2						(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_THCR2_OFFSET))
#define 	CTU_THCR2_T7_EN_MASK			(1<<28)
#define 	CTU_THCR2_T7_ETE_MASK			(1<<27)
#define 	CTU_THCR2_T7_T1E_MASK			(1<<26)
#define 	CTU_THCR2_T7_T0E_MASK			(1<<25)
#define 	CTU_THCR2_T7_ADCE_MASK			(1<<24)
#define 	CTU_THCR2_T6_EN_MASK			(1<<20)
#define 	CTU_THCR2_T6_ETE_MASK			(1<<19)
#define 	CTU_THCR2_T6_T1E_MASK			(1<<18)
#define 	CTU_THCR2_T6_T0E_MASK			(1<<17)
#define 	CTU_THCR2_T6_ADCE_MASK			(1<<16)
#define 	CTU_THCR2_T5_EN_MASK			(1<<12)
#define 	CTU_THCR2_T5_ETE_MASK			(1<<11)
#define 	CTU_THCR2_T5_T1E_MASK			(1<<10)
#define 	CTU_THCR2_T5_T0E_MASK			(1<<9)
#define 	CTU_THCR2_T5_ADCE_MASK			(1<<8)
#define 	CTU_THCR2_T4_EN_MASK			(1<<4)
#define 	CTU_THCR2_T4_ETE_MASK			(1<<3)
#define 	CTU_THCR2_T4_T1E_MASK			(1<<2)
#define 	CTU_THCR2_T4_T0E_MASK			(1<<1)
#define 	CTU_THCR2_T4_ADCE_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	Commands list register x (x = 1,...,24) (CLRx)                     ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CLR(x)						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_CLR_OFFSET(x)))
#define 	CTU_CLR_CIR_MASK				(1<<15)
#define 	CTU_CLR_FC_MASK					(1<<14)
#define 	CTU_CLR_CMS_MASK				(1<<13)
#define 	CTU_CLR_FIFO_MASK				(0x03<<10)

/*---------------------------------------------------------------------------*/
/***	CTU ADC Sample single or Dual defination                           ***/
/*---------------------------------------------------------------------------*/
#ifdef	ADC_SINGLE_CONV	
	#define 	CTU_CLR_SU_MASK				(1<<5)
	#define 	CTU_CLR_CH_MASK				(0x0F<<0)
#else
	#define 	CTU_CLR_CH_B_MASK			(0x0F<<5)
	#define 	CTU_CLR_CH_A_MASK			(0x0F<<0)
#endif

/*---------------------------------------------------------------------------*/
/***	FIFO DMA control register (FDCR)                                   ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FDCR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_FDCR_OFFSET))
#define 	CTU_FDCR_DE3_MASK				(1<<3)
#define 	CTU_FDCR_DE2_MASK				(1<<2)
#define 	CTU_FDCR_DE1_MASK				(1<<1)
#define 	CTU_FDCR_DE0_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	FIFO control register (FCR)                                        ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FCR							(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_FCR_OFFSET))
#define 	CTU_FCR_OR_EN3_MASK				(1<<15)
#define 	CTU_FCR_OF_EN3_MASK				(1<<14)
#define 	CTU_FCR_EMPTY_EN3_MASK			(1<<13)
#define 	CTU_FCR_FULL_EN3_MASK			(1<<12)
#define 	CTU_FCR_OR_EN2_MASK				(1<<11)
#define 	CTU_FCR_OF_EN2_MASK				(1<<10)
#define 	CTU_FCR_EMPTY_EN2_MASK			(1<<9)
#define 	CTU_FCR_FULL_EN2_MASK			(1<<8)
#define 	CTU_FCR_OR_EN1_MASK				(1<<7)
#define 	CTU_FCR_OF_EN1_MASK				(1<<6)
#define 	CTU_FCR_EMPTY_EN1_MASK			(1<<5)
#define 	CTU_FCR_FULL_EN1_MASK			(1<<4)
#define 	CTU_FCR_OR_EN0_MASK				(1<<3)
#define 	CTU_FCR_OF_EN0_MASK				(1<<2)
#define 	CTU_FCR_EMPTY_EN0_MASK			(1<<1)
#define 	CTU_FCR_FULL_EN0_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	FIFO threshold register (FTH)                                      ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FTH							(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_FTH_OFFSET))
#define 	CTU_FTH_TH3_MASK				(0xFF<<24)
#define 	CTU_FTH_TH2_MASK				(0xFF<<16)
#define 	CTU_FTH_TH1_MASK				(0xFF<<8)
#define 	CTU_FTH_TH0_MASK				(0xFF<<0)

/*---------------------------------------------------------------------------*/
/***	FIFO status register (FST)                                         ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FST							(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_FST_OFFSET))
#define 	CTU_FST_P						((volatile uint32 *)(CTU_BASE_ADDRESS+CTU_FST_OFFSET))
#define 	CTU_FST_OR3_MASK				(1<<15)
#define 	CTU_FST_OF3_MASK				(1<<14)
#define 	CTU_FST_EMP3_MASK				(1<<13)
#define 	CTU_FST_FULL3_MASK				(1<<12)
#define 	CTU_FST_OR2_MASK				(1<<11)
#define 	CTU_FST_OF2_MASK				(1<<10)
#define 	CTU_FST_EMP2_MASK				(1<<9)
#define 	CTU_FST_FULL2_MASK				(1<<8)
#define 	CTU_FST_OR1_MASK				(1<<7)
#define 	CTU_FST_OF1_MASK				(1<<6)
#define 	CTU_FST_EMP1_MASK				(1<<5)
#define 	CTU_FST_FULL1_MASK				(1<<4)
#define 	CTU_FST_OR0_MASK				(1<<3)
#define 	CTU_FST_OF0_MASK				((uint16)(1<<2))
#define 	CTU_FST_EMP0_MASK				(1<<1)
#define 	CTU_FST_FULL0_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	FIFO Right aligned data x (x = 0,...,3) (FRx)                      ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FR(x)						(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_FR_OFFSET(x)))
#define 	CTU_FR_ADC0_MASK				(0x01<<20)
#define 	CTU_FR_N_CH_MASK				(0x0F<<16)
#define 	CTU_FR_DATA_MASK				(0x3FF<<0)


/*---------------------------------------------------------------------------*/
/***	FIFO signed Left aligned data x (x = 0,...,3) (FLx)                ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FL(x)						(*(volatile uint32 *)(CTU_BASE_ADDRESS+CTU_FL_OFFSET(x)))
#define 	CTU_FL_ADC0_MASK				(0x01<<20)
#define 	CTU_FL_N_CH_MASK				(0x0F<<16)
#define 	CTU_FL_DATA_MASK				(0x3FF<<5)

/*---------------------------------------------------------------------------*/
/***	Cross triggering unit error flag register (CTUEFR)                 ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CTUEFR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_CTUEFR_OFFSET))
#define 	CTU_CTUEFR_ET_OE_MASK			(1<<8)
#define 	CTU_CTUEFR_T1_OE_MASK			(1<<7)
#define 	CTU_CTUEFR_T0_OE_MASK			(1<<6)
#define 	CTU_CTUEFR_ADC_OE_MASK			(1<<5)
#define 	CTU_CTUEFR_TGS_OSM_MASK			(1<<4)
#define 	CTU_CTUEFR_MRS_O_MASK			(1<<3)
#define 	CTU_CTUEFR_ICE_MASK				(1<<2)
#define 	CTU_CTUEFR_SM_TO_MASK			(1<<1)
#define 	CTU_CTUEFR_MRS_RE_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	Cross triggering unit interrupt flag register (CTUIFR)             ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CTUIFR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_CTUIFR_OFFSET))
#define 	CTU_CTUIFR_ADC_I_MASK			(1<<9)
#define 	CTU_CTUIFR_T7_I_MASK			(1<<8)
#define 	CTU_CTUIFR_T6_I_MASK			(1<<7)
#define 	CTU_CTUIFR_T5_I_MASK			(1<<6)
#define 	CTU_CTUIFR_T4_I_MASK			(1<<5)
#define 	CTU_CTUIFR_T3_I_MASK			(1<<4)
#define 	CTU_CTUIFR_T2_I_MASK			(1<<3)
#define 	CTU_CTUIFR_T1_I_MASK			(1<<2)
#define 	CTU_CTUIFR_T0_I_MASK			(1<<1)
#define 	CTU_CTUIFR_MRS_I_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	Cross triggering unit interrupt/DMA register (CTUIR)               ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CTUIR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_CTUIR_OFFSET))
#define 	CTU_CTUIR_T7_IE_MASK			(1<<15)
#define 	CTU_CTUIR_T6_IE_MASK			(1<<14)
#define 	CTU_CTUIR_T5_IE_MASK			(1<<13)
#define 	CTU_CTUIR_T4_IE_MASK			(1<<12)
#define 	CTU_CTUIR_T3_IE_MASK			(1<<11)
#define 	CTU_CTUIR_T2_IE_MASK			(1<<10)
#define 	CTU_CTUIR_T1_IE_MASK			(1<<9)
#define 	CTU_CTUIR_T0_IE_MASK			(1<<8)
#define 	CTU_CTUIR_MRS_DMAE_MASK			(1<<2)
#define 	CTU_CTUIR_MRS_IE_MASK			(1<<1)
#define 	CTU_CTUIR_IEE_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	Control ON time register (COTR)                                    ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_COTR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_COTR_OFFSET))
#define 	CTU_COTR_COTR_MASK				(0xFF<<0)

/*---------------------------------------------------------------------------*/
/***	Cross triggering unit control register (CTUCR)                     ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CTUCR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_CTUCR_OFFSET))
#define 	CTU_CTUCR_T7_SG_MASK			(1<<15)
#define 	CTU_CTUCR_T6_SG_MASK			(1<<14)
#define 	CTU_CTUCR_T5_SG_MASK			(1<<13)
#define 	CTU_CTUCR_T4_SG_MASK			(1<<12)
#define 	CTU_CTUCR_T3_SG_MASK			(1<<11)
#define 	CTU_CTUCR_T2_SG_MASK			(1<<10)
#define 	CTU_CTUCR_T1_SG_MASK			(1<<9)
#define 	CTU_CTUCR_T0_SG_MASK			(1<<8)
#define 	CTU_CTUCR_CRU_ADC_R_MASK		(1<<7)
#define 	CTU_CTUCR_CTU_ODIS_MASK			(1<<6)
#define 	CTU_CTUCR_DFE_MASK				(1<<5)
#define 	CTU_CTUCR_CGRE_MASK				(1<<4)
#define 	CTU_CTUCR_FGRE_MASK				(1<<3)
#define 	CTU_CTUCR_MRS_SG_MASK			(1<<2)
#define 	CTU_CTUCR_GRE_MASK				(1<<1)
#define 	CTU_CTUCR_TGSISR_RE_MASK		(1<<0)

/*---------------------------------------------------------------------------*/
/***	Cross triggering unit digital filter (CTUDF)                       ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CTUDF						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_CTUDF_OFFSET))
#define 	CTU_CTUDF_N_MASK				(0xFF<<0)

/*---------------------------------------------------------------------------*/
/***	Cross triggering unit power control register (CTUPCR)              ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_CTUPCR						(*(volatile uint16 *)(CTU_BASE_ADDRESS+CTU_CTUPCR_OFFSET))
#define 	CTU_CTUPCR_MDIS_MASK			(1<<0)


/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	TGSCR PreScale								                       ***/
/*---------------------------------------------------------------------------*/
#define		PRES_1 					(uint8)0x0u
#define		PRES_2 					(uint8)0x1u
#define		PRES_3 					(uint8)0x2u
#define		PRES_4 					(uint8)0x3u

/*---------------------------------------------------------------------------*/
/***	TGS Mode	(0 Triggered Mode; 1 Sequential Mode)                  ***/
/*---------------------------------------------------------------------------*/
#define		TGS_TRIG 				(uint8)0x0u
#define		TGS_SEQUEN 				(uint8)0x1u

/*---------------------------------------------------------------------------*/
/***	TCR Number  Trigger Compare Register           	                   ***/
/*---------------------------------------------------------------------------*/
#define 	TCR_CH0 				(uint8)0x00u
#define 	TCR_CH1 				(uint8)0x01u
#define 	TCR_CH2 				(uint8)0x02u
#define 	TCR_CH3 				(uint8)0x03u
#define 	TCR_CH4 				(uint8)0x04u
#define 	TCR_CH5 				(uint8)0x05u
#define 	TCR_CH6 				(uint8)0x06u
#define 	TCR_CH7 				(uint8)0x07u

/*---------------------------------------------------------------------------*/
/***	CLR Number  Commands List Register            	                   ***/
/*---------------------------------------------------------------------------*/
#define 	CLR_CH1 				(uint8)0x00u
#define 	CLR_CH2 				(uint8)0x01u
#define 	CLR_CH3 				(uint8)0x02u
#define 	CLR_CH4 				(uint8)0x03u
#define 	CLR_CH5 				(uint8)0x04u
#define 	CLR_CH6 				(uint8)0x05u
#define 	CLR_CH7 				(uint8)0x06u
#define 	CLR_CH8 				(uint8)0x07u
#define 	CLR_CH9 				(uint8)0x08u
#define 	CLR_CH10 				(uint8)0x09u
#define 	CLR_CH11 				(uint8)0x0Au
#define 	CLR_CH12 				(uint8)0x0Bu
#define 	CLR_CH13 				(uint8)0x0Cu
#define 	CLR_CH14 				(uint8)0x0Du
#define 	CLR_CH15 				(uint8)0x0Eu
#define 	CLR_CH16 				(uint8)0x0Fu
#define 	CLR_CH17 				(uint8)0x10u
#define 	CLR_CH18 				(uint8)0x11u
#define 	CLR_CH19 				(uint8)0x12u
#define 	CLR_CH20 				(uint8)0x13u
#define 	CLR_CH21 				(uint8)0x14u
#define 	CLR_CH22 				(uint8)0x15u
#define 	CLR_CH23 				(uint8)0x16u
#define 	CLR_CH24 				(uint8)0x17u

/*---------------------------------------------------------------------------*/
/***	Commands list control CLC Trigger Index       	                   ***/
/*---------------------------------------------------------------------------*/
#define 	CLCR_T0 				(uint8)0x00u
#define 	CLCR_T1 				(uint8)0x01u
#define 	CLCR_T2 				(uint8)0x02u
#define 	CLCR_T3 				(uint8)0x03u
#define 	CLCR_T4 				(uint8)0x04u
#define 	CLCR_T5 				(uint8)0x05u
#define 	CLCR_T6 				(uint8)0x06u
#define 	CLCR_T7 				(uint8)0x07u

/*---------------------------------------------------------------------------*/
/***	Trigger handler control register Index        	                   ***/
/*---------------------------------------------------------------------------*/
#define 	THCR_T0 				(uint8)0x00u
#define 	THCR_T1 				(uint8)0x01u
#define 	THCR_T2 				(uint8)0x02u
#define 	THCR_T3 				(uint8)0x03u
#define 	THCR_T4 				(uint8)0x04u
#define 	THCR_T5 				(uint8)0x05u
#define 	THCR_T6 				(uint8)0x06u
#define 	THCR_T7 				(uint8)0x07u

/*---------------------------------------------------------------------------*/
/***	CTU ADC Channel Number                        	                   ***/
/*---------------------------------------------------------------------------*/
#define 	AD_CH0 					(uint8)0x00u
#define 	AD_CH1 					(uint8)0x01u
#define 	AD_CH2 					(uint8)0x02u
#define 	AD_CH3 					(uint8)0x03u
#define 	AD_CH4 					(uint8)0x04u
#define 	AD_CH5 					(uint8)0x05u
#define 	AD_CH6 					(uint8)0x06u
#define 	AD_CH7 					(uint8)0x07u
#define 	AD_CH8 					(uint8)0x08u
#define 	AD_CH9 					(uint8)0x09u
#define 	AD_CH10 				(uint8)0x0Au
#define 	AD_CH11 				(uint8)0x0Bu
#define 	AD_CH12 				(uint8)0x0Cu
#define 	AD_CH13 				(uint8)0x0Du
#define 	AD_CH14 				(uint8)0x0Eu
#define 	AD_CH15 				(uint8)0x0Fu

/*---------------------------------------------------------------------------*/
/***	Trigger handler Source                        	                   ***/
/*---------------------------------------------------------------------------*/
#define 	THCR_TRIG_EN			(uint8)0x00u
#define 	THCR_TRIG_EXT_EN 		(uint8)0x01u
#define 	THCR_TRIG_T1_EN			(uint8)0x02u
#define 	THCR_TRIG_T0_EN			(uint8)0x03u
#define 	THCR_TRIG_ADC_EN 		(uint8)0x04u

/*---------------------------------------------------------------------------*/
/***	Conversion mode selection                     	                   ***/
/*---------------------------------------------------------------------------*/
#define		CLR_CONV_SINGLE			(uint8)0x00u
#define		CLR_CONV_DUAL			(uint8)0x01u

/*---------------------------------------------------------------------------*/
/***	Single conversion mode Selection Unit bit      	                   ***/
/*---------------------------------------------------------------------------*/
#define 	CLR_SINGLE_ADC0_SEL		(uint8)0x00u
#define 	CLR_SINGLE_ADC1_SEL		(uint8)0x01u

/*---------------------------------------------------------------------------*/
/***	FIFO DMA Num			                    	                   ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FIFO0				(uint8)0x00u
#define 	CTU_FIFO1				(uint8)0x01u
#define 	CTU_FIFO2				(uint8)0x02u
#define 	CTU_FIFO3				(uint8)0x03u
#define 	CTU_FIFO_NULL			(uint8)0xFFu

/*---------------------------------------------------------------------------*/
/***	CTU	FIFO SIZE			                    	                   ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FIFO0_SIZE			(uint8)0x10u
#define 	CTU_FIFO1_SIZE			(uint8)0x10u
#define 	CTU_FIFO2_SIZE			(uint8)0x04u
#define 	CTU_FIFO3_SIZE			(uint8)0x04u

/*---------------------------------------------------------------------------*/
/***	Cross triggering unit control register (CTUCR) 	                   ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_TRIG0 				(uint8)0x00u
#define 	CTU_TRIG1 				(uint8)0x01u
#define 	CTU_TRIG2 				(uint8)0x02u
#define 	CTU_TRIG3 				(uint8)0x03u
#define 	CTU_TRIG4 				(uint8)0x04u
#define 	CTU_TRIG5 				(uint8)0x05u
#define 	CTU_TRIG6 				(uint8)0x06u
#define 	CTU_TRIG7 				(uint8)0x07u

/*---------------------------------------------------------------------------*/
/***	TGSISR Input Source 	                    	                   ***/
/*---------------------------------------------------------------------------*/
#define 	TGSISR_INPUT_NUM		(uint8)0x20u

/*---------------------------------------------------------------------------*/
/***	TimeOut Delay COUNT 	                    	                   ***/
/*---------------------------------------------------------------------------*/
#define		TIMEOUT_CTU_ADC			((uint16)0xFFFF)

/*---------------------------------------------------------------------------*/
/***	CTU Function Enabled Macro                  	                   ***/
/*---------------------------------------------------------------------------*/
#define		CTU_ENABLED
#ifdef		CTU_ENABLED
	/* TGSISR Input Source Select */
	#define		TGS_INPUT_SRC		CTU_TGSISR_IN0_RISE_EN_MASK
	
	/* TGSCR */
	#define		TGS_PRESCALE		PRES_1
	#define		TGS_SUBUNIT_MODE	TGS_TRIG
	
	/* TxCR Used for EXT_Trig 10KHz Square Generator, Half Cycle Offset */
	#define		TCR_EXT_OFFSET		6000

	/* TGSCCR  (TGS Counter Compare Reg) */
	/* PWM every 2 Period to Reload, Must Conform to PWM Reload Cycle. See CTRL.LDFQ and PRSC */
	#define		TGSCCR_VALUE	12000
	
	/* TGSCRR  (TGS Counter Reload Reg) */
	#define		TGSCRR_VALUE	0x0
	
	/* Control ON time register (COTR) */
	#define		COTR_VALUE			(uint8)0x7F

	/* Cross triggering unit digital filter (CTUDF) */
	#define		FILTER_VALUE		(uint8)0x00
#endif


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_CTU_DRV_EXT	void	mCTU_Trig_Handdle_Set(uint8 TrigNum, uint8 IntcSrc, uint32 ValEn);
M_CTU_DRV_EXT	void	mCTU_Init(void);
M_CTU_DRV_EXT	uint8	mCTU_FIFO_GetVal(uint8 FIFONum, uint32 *u32ADC_Val);

M_CTU_DRV_EXT	void	mCTU_Module_En(void);
M_CTU_DRV_EXT	void	mCTU_Module_Dis(void);

M_CTU_DRV_EXT	void	mCTU_ADC_StateM_Reset(uint16 ValRstEn);
M_CTU_DRV_EXT	void	mCTU_GRE_Set(uint16 ValEn);

#endif	
