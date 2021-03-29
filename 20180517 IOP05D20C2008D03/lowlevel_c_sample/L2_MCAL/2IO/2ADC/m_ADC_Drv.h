/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_ADC_Drv.h
*
* @brief    Drive Header file for "m_ADC_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/06/07      Lwt       	   	N/A          Original
*     1.1        2012/08/03      Lwt       	   	N/A          Modify, ADC_CTU and ADC single
*     1.2        2012/09/05      Lwt			N/A          Modify include file
*     1.3        2012/09/27      Lwt			N/A          Add Cfg file
*     1.4        2012/10/09      Lwt			N/A          Modify Macro Defination
*     1.5        2012/11/02      Lwt			N/A          Add History Comment
*     1.6        2013/02/26      Lwt			N/A          Code Simplify, Delete Reg_Bit Functions
************************************************************************************************/

#ifndef _M_ADC_DRV_H_
#define _M_ADC_DRV_H_

#ifdef 	M_ADC_DRV_C
#define M_ADC_DRV_EXT
#else
#define M_ADC_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include  	"Std_Types.h"
#include  	"m_GPIO.h"
#include	"Common.h"

/* *****************************************************************************
   *****************************************************************************
   Drive Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Register define                                                    ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_BASE_ADDRESS				0xFFE00000ul
#define 	ADC_MOUDLE_STEP					0x4000ul
#define 	ADC_MOUDLE_BASE_ADDRESS(x)		(ADC_BASE_ADDRESS+(x)*ADC_MOUDLE_STEP)
#define 	ADC_MCR_OFFSET					0x0ul
#define 	ADC_MSR_OFFSET					0x4ul
#define 	ADC_ISR_OFFSET					0x10ul
#define 	ADC_IMR_OFFSET					0x20ul
#define 	ADC_CIMR0_OFFSET				0x24ul
#define 	ADC_WTISR_OFFSET				0x30ul
#define 	ADC_WTIMR_OFFSET				0x34ul
#define 	ADC_DMAE_OFFSET					0x40ul
#define 	ADC_DMAR0_OFFSET				0x44ul
#define 	ADC_TRC_OFFSET(x)				(0x50ul+(x)*0x4)	/* TRC0---3 */
#define 	ADC_THRHLR_OFFSET(x)			(0x60ul+(x)*0x4)	/* THRHLR0---3 */
#define 	ADC_CTR0_OFFSET					0x94ul
#define 	ADC_NCMR0_OFFSET				0xA4ul
#define 	ADC_JCMR0_OFFSET				0xB4ul
#define 	ADC_PDEDR_OFFSET				0xC8ul
#define 	ADC_CDR_OFFSET(x)				(0x100ul+(x)*0x4)	/* CDR0---15 */

/*---------------------------------------------------------------------------*/
/***	Main Configuration Register (MCR)                                  ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_MCR(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_MCR_OFFSET))
#define 	ADC_MCR_OWREN_MASK				(1<<31)
#define 	ADC_MCR_WLSIDE_MASK				(1<<30)
#define 	ADC_MCR_MODE_MASK				(1<<29)
#define 	ADC_MCR_NSTART_MASK				(1<<24)
#define 	ADC_MCR_JTRGEN_MASK				(1<<22)
#define 	ADC_MCR_JEDGE_MASK				(1<<21)
#define 	ADC_MCR_JSTART_MASK				(1<<20)
#define 	ADC_MCR_CTUEN_MASK				(1<<17)
#define 	ADC_MCR_ADCLKSEL_MASK			(1<<8)
#define 	ADC_MCR_ABORTCHAIN_MASK			(1<<7)
#define 	ADC_MCR_ABORT_MASK				(1<<6)
#define 	ADC_MCR_ACKO_MASK				(1<<5)
#define 	ADC_MCR_PWDN_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	Main Status Register (MSR)                                         ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_MSR(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_MSR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	Interrupt Status Register (ISR)                                    ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_ISR(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_ISR_OFFSET))
#define 	ADC_ISR_EOCTU_MASK				(1<<4)
#define 	ADC_ISR_JEOC_MASK				(1<<3)
#define 	ADC_ISR_JECH_MASK				(1<<2)
#define 	ADC_ISR_EOC_MASK				(1<<1)
#define 	ADC_ISR_ECH_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	Interrupt Mask Register (IMR)                                      ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_IMR(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_IMR_OFFSET))
#define 	ADC_IMR_MSKEOCTU_MASK			(1<<4)
#define 	ADC_IMR_MSKJEOC_MASK			(1<<3)
#define 	ADC_IMR_MSKJECH_MASK			(1<<2)
#define 	ADC_IMR_MSKEOC_MASK				(1<<1)
#define 	ADC_IMR_MSKECH_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	Channel Interrupt Mask Register (CIMR[0])                          ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_CIMR0(x)					(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_CIMR0_OFFSET))
#define 	ADC_CIMR0_CIM15_MASK			(1<<15)
#define 	ADC_CIMR0_CIM14_MASK			(1<<14)
#define 	ADC_CIMR0_CIM13_MASK			(1<<13)
#define 	ADC_CIMR0_CIM12_MASK			(1<<12)
#define 	ADC_CIMR0_CIM11_MASK			(1<<11)
#define 	ADC_CIMR0_CIM10_MASK			(1<<10)
#define 	ADC_CIMR0_CIM9_MASK				(1<<9)
#define 	ADC_CIMR0_CIM8_MASK				(1<<8)
#define 	ADC_CIMR0_CIM7_MASK				(1<<7)
#define 	ADC_CIMR0_CIM6_MASK				(1<<6)
#define 	ADC_CIMR0_CIM5_MASK				(1<<5)
#define 	ADC_CIMR0_CIM4_MASK				(1<<4)
#define 	ADC_CIMR0_CIM3_MASK				(1<<3)
#define 	ADC_CIMR0_CIM2_MASK				(1<<2)
#define 	ADC_CIMR0_CIM1_MASK				(1<<1)
#define 	ADC_CIMR0_CIM0_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	Watchdog Threshold Interrupt Status Register (WTISR)               ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_WTISR(x)					(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_WTISR_OFFSET))
#define 	ADC_WTISR_WDG3H_MASK			(1<<7)
#define 	ADC_WTISR_WDG2H_MASK			(1<<6)
#define 	ADC_WTISR_WDG1H_MASK			(1<<5)
#define 	ADC_WTISR_WDG0H_MASK			(1<<4)
#define 	ADC_WTISR_WDG3L_MASK			(1<<3)
#define 	ADC_WTISR_WDG2L_MASK			(1<<2)
#define 	ADC_WTISR_WDG1L_MASK			(1<<1)
#define 	ADC_WTISR_WDG0L_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	Watchdog Threshold Interrupt Mask Register (WTIMR)                 ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_WTIMR(x)					(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_WTIMR_OFFSET))
#define 	ADC_WTIMR_MSKWDG3H_MASK			(1<<7)
#define 	ADC_WTIMR_MSKWDG2H_MASK			(1<<6)
#define 	ADC_WTIMR_MSKWDG1H_MASK			(1<<5)
#define 	ADC_WTIMR_MSKWDG0H_MASK			(1<<4)
#define 	ADC_WTIMR_MSKWDG3L_MASK			(1<<3)
#define 	ADC_WTIMR_MSKWDG2L_MASK			(1<<2)
#define 	ADC_WTIMR_MSKWDG1L_MASK			(1<<1)
#define 	ADC_WTIMR_MSKWDG0L_MASK			(1<<0)

/*---------------------------------------------------------------------------*/
/***	DMA Enable Register (DMAE)                                         ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_DMAE(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_DMAE_OFFSET))
#define 	ADC_DMAE_DCLR_MASK				(1<<1)
#define 	ADC_DMAE_DMAEN_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	DMA Channel Select Register (DMAR[0])                              ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_DMAR0(x)					(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_DMAR0_OFFSET))
#define 	ADC_DMAR0_DMA15_MASK			(1<<15)
#define 	ADC_DMAR0_DMA14_MASK			(1<<14)
#define 	ADC_DMAR0_DMA13_MASK			(1<<13)
#define 	ADC_DMAR0_DMA12_MASK			(1<<12)
#define 	ADC_DMAR0_DMA11_MASK			(1<<11)
#define 	ADC_DMAR0_DMA10_MASK			(1<<10)
#define 	ADC_DMAR0_DMA9_MASK				(1<<9)
#define 	ADC_DMAR0_DMA8_MASK				(1<<8)
#define 	ADC_DMAR0_DMA7_MASK				(1<<7)
#define 	ADC_DMAR0_DMA6_MASK				(1<<6)
#define 	ADC_DMAR0_DMA5_MASK				(1<<5)
#define 	ADC_DMAR0_DMA4_MASK				(1<<4)
#define 	ADC_DMAR0_DMA3_MASK				(1<<3)
#define 	ADC_DMAR0_DMA2_MASK				(1<<2)
#define 	ADC_DMAR0_DMA1_MASK				(1<<1)
#define 	ADC_DMAR0_DMA0_MASK				(1<<0)

/*---------------------------------------------------------------------------*/
/***	Threshold Control Register (TRCx, x = [0..3])                      ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_TRC(x,y)					(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_TRC_OFFSET(y)))
#define 	ADC_TRC_THREN_MASK				(1<<15)
#define 	ADC_TRC_THRINV_MASK				(1<<14)
#define 	ADC_TRC_THROP_MASK				(1<<13)
#define 	ADC_TRC_THRCH_MASK				(0x7F<<0)

/*---------------------------------------------------------------------------*/
/***	Threshold Register (THRHLR[0:3])                                   ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_THRHLR(x,y)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_THRHLR_OFFSET(y)))
#define 	ADC_THRHLR_THRH_MASK				(0x3FF<<16)
#define 	ADC_THRHLR_THRL_MASK				(0x3FF<<0)

/*---------------------------------------------------------------------------*/
/***	Conversion timing registers CTR[0]                                 ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_CTR0(x)							(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_CTR0_OFFSET))
#define 	ADC_CTR0_INPLATCH_MASK				(1<<15)
#define 	ADC_CTR0_OFFSHIFT_MASK				(0x3<<12)
#define 	ADC_CTR0_INPCMP_MASK				(0x3<<9)
#define 	ADC_CTR0_INPSAMP_MASK				(0xFF<<0)

/*---------------------------------------------------------------------------*/
/***	Normal Conversion Mask Registers (NCMR[0])                         ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_NCMR0(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_NCMR0_OFFSET))
#define 	ADC_NCMR0_CH15_MASK					(1<<15)
#define 	ADC_NCMR0_CH14_MASK					(1<<14)
#define 	ADC_NCMR0_CH13_MASK					(1<<13)
#define 	ADC_NCMR0_CH12_MASK					(1<<12)
#define 	ADC_NCMR0_CH11_MASK					(1<<11)
#define 	ADC_NCMR0_CH10_MASK					(1<<10)
#define 	ADC_NCMR0_CH9_MASK					(1<<9)
#define 	ADC_NCMR0_CH8_MASK					(1<<8)
#define 	ADC_NCMR0_CH7_MASK					(1<<7)
#define 	ADC_NCMR0_CH6_MASK					(1<<6)
#define 	ADC_NCMR0_CH5_MASK					(1<<5)
#define 	ADC_NCMR0_CH4_MASK					(1<<4)
#define 	ADC_NCMR0_CH3_MASK					(1<<3)
#define 	ADC_NCMR0_CH2_MASK					(1<<2)
#define 	ADC_NCMR0_CH1_MASK					(1<<1)
#define 	ADC_NCMR0_CH0_MASK					(1<<0)

/*---------------------------------------------------------------------------*/
/***	Injected Conversion Mask Registers (JCMR[0])                       ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_JCMR0(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_JCMR0_OFFSET))
#define 	ADC_JCMR0_CH15_MASK					(1<<15)
#define 	ADC_JCMR0_CH14_MASK					(1<<14)
#define 	ADC_JCMR0_CH13_MASK					(1<<13)
#define 	ADC_JCMR0_CH12_MASK					(1<<12)
#define 	ADC_JCMR0_CH11_MASK					(1<<11)
#define 	ADC_JCMR0_CH10_MASK					(1<<10)
#define 	ADC_JCMR0_CH9_MASK					(1<<9)
#define 	ADC_JCMR0_CH8_MASK					(1<<8)
#define 	ADC_JCMR0_CH7_MASK					(1<<7)
#define 	ADC_JCMR0_CH6_MASK					(1<<6)
#define 	ADC_JCMR0_CH5_MASK					(1<<5)
#define 	ADC_JCMR0_CH4_MASK					(1<<4)
#define 	ADC_JCMR0_CH3_MASK					(1<<3)
#define 	ADC_JCMR0_CH2_MASK					(1<<2)
#define 	ADC_JCMR0_CH1_MASK					(1<<1)
#define 	ADC_JCMR0_CH0_MASK					(1<<0)

/*---------------------------------------------------------------------------*/
/***	Power-down Exit Delay Register (PDEDR)                             ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_PDEDR(x)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_PDEDR_OFFSET))
#define 	ADC_PDEDR_PDED_MASK					(0xFF<<0)

/*---------------------------------------------------------------------------*/
/***	Channel Data Register (CDR[0..15])                                 ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_CDR(x,y)						(*(volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_CDR_OFFSET(y)))
#define 	ADC_CDR_VALID_MASK					(1<<19)
#define 	ADC_CDR_OVERW_MASK					(1<<18)
#define 	ADC_CDR_RESULT_MASK					(1<<16)
#define 	ADC_CDR_CDATA_MASK					(0x3FF<<0)
#define 	ADC_CDR_P(x,y)						((volatile uint32 *)(ADC_MOUDLE_BASE_ADDRESS(x)+ADC_CDR_OFFSET(y)))


/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	TimeOut Delay COUNT                                                ***/
/*---------------------------------------------------------------------------*/
#define		TIMEOUT_ADC			((uint16)0xFFFF)

/*---------------------------------------------------------------------------*/
/***	Moudle Number                                                      ***/
/*---------------------------------------------------------------------------*/
#define 	ADC0 					0u
#define 	ADC1 					1u

/*---------------------------------------------------------------------------*/
/***	Channel Number                                                     ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_CH0 				(uint8)0x00u
#define 	ADC_CH1 				(uint8)0x01u
#define 	ADC_CH2 				(uint8)0x02u
#define 	ADC_CH3 				(uint8)0x03u
#define 	ADC_CH4 				(uint8)0x04u
#define 	ADC_CH5 				(uint8)0x05u
#define 	ADC_CH6 				(uint8)0x06u
#define 	ADC_CH7 				(uint8)0x07u
#define 	ADC_CH8 				(uint8)0x08u
#define 	ADC_CH9 				(uint8)0x09u
#define 	ADC_CH10 				(uint8)0x0Au
#define 	ADC_CH11 				(uint8)0x0Bu
#define 	ADC_CH12 				(uint8)0x0Cu
#define 	ADC_CH13 				(uint8)0x0Du
#define 	ADC_CH14 				(uint8)0x0Eu
#define 	ADC_CH15 				(uint8)0x0Fu

/*---------------------------------------------------------------------------*/
/***	MCR Bit Macro                                                      ***/
/*---------------------------------------------------------------------------*/
#define		ADC_WLSIDE_RIGHT		0u
#define		ADC_WLSIDE_LEFT			1u
#define		ADC_MODE_ONESHOT		0u
#define		ADC_MODE_SCAN			1u

/*---------------------------------------------------------------------------*/
/***	WatchDog Threshold Interrupt Mask                                  ***/
/*---------------------------------------------------------------------------*/
#define 	WTIM_0L 				(uint8)0x00u
#define 	WTIM_1L 				(uint8)0x01u
#define 	WTIM_2L 				(uint8)0x02u
#define 	WTIM_3L 				(uint8)0x03u
#define 	WTIM_0H 				(uint8)0x04u
#define 	WTIM_1H 				(uint8)0x05u
#define 	WTIM_2H 				(uint8)0x06u
#define 	WTIM_3H 				(uint8)0x07u

/*---------------------------------------------------------------------------*/
/***	Interrupt source                                                   ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_EOCTU 				(uint8)0x00u
#define 	ADC_JEOC 				(uint8)0x01u
#define 	ADC_JECH 				(uint8)0x02u
#define 	ADC_EOC 				(uint8)0x03u
#define 	ADC_ECH 				(uint8)0x04u

/*---------------------------------------------------------------------------*/
/***	TRC Threshold Control Register Number                              ***/
/*---------------------------------------------------------------------------*/
#define 	ADC_THR0 				(uint8)0x00u
#define 	ADC_THR1 				(uint8)0x01u
#define 	ADC_THR2 				(uint8)0x02u
#define 	ADC_THR3 				(uint8)0x03u

/*---------------------------------------------------------------------------*/
/***	Module Used                                                        ***/
/*---------------------------------------------------------------------------*/
#define		ADC0_ENABLE
#define		ADC1_ENABLE

/*---------------------------------------------------------------------------*/
/***	ADC0 Configration Macro                                            ***/
/*---------------------------------------------------------------------------*/
#ifdef	ADC0_ENABLE
	/* ADC0 Common Setting */
	/* ADC0 Sample Comment */
	/* Tck = 2/Mclk 
	/* Tsamp = (INPSAMP - Ndelay)*Tck 
	/* Teval = 10*INPCMP*Tck 
	/* Tconv = Tsamp + Teval + Ndelay*Tck = (INPSAMP + 10*INPCMP)*Tck 
	/* Tconv = (17 + 10*3)*Tck = 47*Tck 	*/	
	#define		ADC0_SAMP_LATCH			0x01
	#define		ADC0_SAMP_OFFSHIFT		0x00
	#define		ADC0_SAMP_INPCMP		0x03
	#define		ADC0_SAMP_INPSAMP		0x11
	#define		ADC0_CTR0_VALUE			((ADC0_SAMP_LATCH<<15) 		| \
										 (ADC0_SAMP_OFFSHIFT<<12)	| \
										 (ADC0_SAMP_INPCMP<<9)		| \
										 (ADC0_SAMP_INPSAMP<<0) 	)
	
	/* ADC0 PowerDown Delay Setting */
	#define		ADC0_PDEDR_DELAY		0x00
	#define		ADC0_MCR_MODE			ADC_MODE_ONESHOT
	
	/* ADC0 Write Align ;   Same as ADC_ALIGN_MODE in "SysConfig.h" */
	#define		ADC0_MCR_ALIGN_MODE		ADC_WLSIDE_RIGHT
	#if(ADC0_MCR_ALIGN_MODE == ADC_WLSIDE_RIGHT)
		#define 	ADC0_CDR_CDATA_MASK				(0x3FF<<0)
	#else
		#define 	ADC0_CDR_CDATA_MASK				(0x3FF<<6)
	#endif
	
	
	/* ADC0 Interrupt Source Enabled */
//	#define		ADC0_IMR_ENABLED
	
	/* ADC0 Inject Source Enabled */
	//#define		ADC0_JCMR_ENABLED
		
	#ifdef	ADC0_THRESH_ENABLED
		#define		ADC0_THR0_HIGH		(uint16)0x03FF
		#define		ADC0_THR0_LOW		(uint16)0x0000
		#define		ADC0_THR1_HIGH		(uint16)0x03FF
		#define		ADC0_THR1_LOW		(uint16)0x0000
		#define		ADC0_THR2_HIGH		(uint16)0x03FF
		#define		ADC0_THR2_LOW		(uint16)0x0000
		#define		ADC0_THR3_HIGH		(uint16)0x03FF
		#define		ADC0_THR3_LOW		(uint16)0x0000
	#endif
	
	#ifdef	ADC0_DMA_ENABLED
		#define		ADC0_DMA_CLR_SEQ_EN		DISABLE
		#define		ADC0_DMA_EN				DISABLE
	#endif
#endif

/*---------------------------------------------------------------------------*/
/***	ADC1 Configration Macro                                            ***/
/*---------------------------------------------------------------------------*/
#ifdef	ADC1_ENABLE
	/* ADC1 Common Setting	 ((1<<B_LATCH)|(0<<B_SHIFT)|(3<<B_CMP)|(17<<B_SAMP)); */
	/* ADC1 Sample Comment */
	/* Tck = 2/Mclk 
	/* Tsamp = (INPSAMP - 1)*Tck 
	/* Teval = 12*Tbiteval 
	/* Teval = 12*INPCMP*Tck  if(INPCMP>=1) 
	/* Teval = 48*Tck  if(INPCMP==0) 
	/* Tconv = Tsamp + Teval + Tck 
	/* Tconv = (INPSAMP + 12*INPCMP)*Tck  if(INPCMP>=1) 
	/* Tconv = (INPSAMP + 48)*Tck  if(INPCMP==0) 
	/* Tconv = (17 + 12*3)*Tck = 53*Tck  	*/
	#define		ADC1_SAMP_LATCH			0x01
	#define		ADC1_SAMP_OFFSHIFT		0x00
	#define		ADC1_SAMP_INPCMP		0x03
	#define		ADC1_SAMP_INPSAMP		0x11
	#define		ADC1_CTR0_VALUE			((ADC1_SAMP_LATCH<<15) 		| \
										 (ADC1_SAMP_OFFSHIFT<<12)	| \
										 (ADC1_SAMP_INPCMP<<9)		| \
										 (ADC1_SAMP_INPSAMP<<0) 	)
	
	/* ADC1 PowerDown Delay Setting */
	#define		ADC1_PDEDR_DELAY		0x00
	#define		ADC1_MCR_MODE			ADC_MODE_ONESHOT
	
	/* ADC1 Write Align ;  Same as ADC_ALIGN_MODE in "SysConfig.h" */
	#define		ADC1_MCR_ALIGN_MODE		ADC_WLSIDE_RIGHT
	#if(ADC1_MCR_ALIGN_MODE == ADC_WLSIDE_RIGHT)
		#define 	ADC1_CDR_CDATA_MASK				(0x3FF<<0)
	#else
		#define 	ADC1_CDR_CDATA_MASK				(0x3FF<<6)
	#endif
		
	/* ADC1 Interrupt Source Enabled */
//	#define		ADC1_IMR_ENABLED

	#ifdef	ADC1_THRESH_ENABLED
		#define		ADC1_THR0_HIGH		(uint16)0x03FF
		#define		ADC1_THR0_LOW		(uint16)0x0000
		#define		ADC1_THR1_HIGH		(uint16)0x03FF
		#define		ADC1_THR1_LOW		(uint16)0x0000
		#define		ADC1_THR2_HIGH		(uint16)0x03FF
		#define		ADC1_THR2_LOW		(uint16)0x0000
		#define		ADC1_THR3_HIGH		(uint16)0x03FF
		#define		ADC1_THR3_LOW		(uint16)0x0000
	#endif
	
	/* ADC1 Injection External Trigger Enable */
	#define			ADC1_INJ_TRIG_EN	ENABLE

	#ifdef	ADC1_DMA_ENABLED	
		#define		ADC1_DMA_CLR_SEQ_EN		DISABLE
		#define		ADC1_DMA_EN				DISABLE
	#endif
#endif


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_ADC_DRV_EXT	void	mADC_Normal_Stop(uint8 ModuleNum);
M_ADC_DRV_EXT	void	mADC_Normal_Start(uint8 ModuleNum);
M_ADC_DRV_EXT	void	mADC_CTU_En_Set(uint8 ModuleNum, uint32 ValEn);
M_ADC_DRV_EXT	void	mADC0_Init(void);
M_ADC_DRV_EXT	void	mADC1_Init(void);
M_ADC_DRV_EXT	uint8	mADC0_ValGet(uint8 ChanNum, uint16 *ValAddr);
M_ADC_DRV_EXT	uint8	mADC1_ValGet(uint8 ChanNum, uint16 *ValAddr);
M_ADC_DRV_EXT	uint8	mADC_Oneshot_ValGet(uint8 ModuleNum, uint8 ChanNum, uint16 *ValAddr);

#endif	
