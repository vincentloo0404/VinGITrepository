/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_CTU_Cfg.h
*
* @brief    Config Header file for "m_CTU_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/27      CODER2			N/A          Original
*     1.1        2012/10/09      CODER2	       	N/A          simplified, added Comment for CTU Events, CLR...
*     1.2        2012/10/22      WanXinshan    	N/A          Modify CTR0 for Motor
*     1.3        2012/11/02      CODER2			N/A          Add History Comment
*     1.4        2013/02/26      CODER2			N/A          Code Simplify, Delete Reg_Bit Functions
*     1.5        2013/04/15      CODER2			N/A			 Add CTU_FIFO_Thresh Macro from SysConfig.h
************************************************************************************************/

#ifndef _M_CTU_CFG_H_
#define _M_CTU_CFG_H_


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_CTU_Drv.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	CTU_ADC FIFO Enabled                                               ***/
/*---------------------------------------------------------------------------*/
#define		CTU_FIFO_ENABLED
#define     SYS_CTU_FIFO_USE_EDMA
#define     EDMA_CTU_FIFO_0_USED
#define     EDMA_CTU_FIFO_1_USED

#ifdef		CTU_ENABLED
/*---------------------------------------------------------------------------*/
/***	TxCR  (Trigger x Compare Reg)                                      ***/
/*---------------------------------------------------------------------------*/	
	/* Trig Compare Reg for Trig Events */
	#define		TCR0_VALUE		(1800-60) /* (3000-120*0.5) */     /* for Motor phase current ad sample*/
	//#define		TCR0_VALUE		(1800-300) /* (1800-120*2.5) */     /* for Motor phase current ad sample*/

	#define		TCR1_VALUE		(2400-60)    /* (28.8)*120  */
	#define		TCR2_VALUE		(1200)	
	#define		TCR3_VALUE		(TCR0_VALUE - 6000+4800)

	#define		TCR4_VALUE		(TCR0_VALUE - 6000+1200)
	#define		TCR5_VALUE		(TCR0_VALUE - 6000+2400)
	#define		TCR6_VALUE		(TCR0_VALUE - 6000+3000)  /* = offset */
	#define		TCR7_VALUE		(TCR0_VALUE - 6000)

/*---------------------------------------------------------------------------*/
/***	CLCRx   (Commands List Control Reg 1)                              ***/
/*---------------------------------------------------------------------------*/
	/* First Command Address of Trigger N Commands List, N(0--7) */
	#define		CLC_T0_FST_ADDR		CLR_CH1
	#define		CLC_T1_FST_ADDR		CLR_CH2
	#define		CLC_T2_FST_ADDR		CLR_CH3
	#define		CLC_T3_FST_ADDR		CLR_CH10
	#define		CLC_T4_FST_ADDR		CLR_CH10
	#define		CLC_T5_FST_ADDR		CLR_CH10
	#define		CLC_T6_FST_ADDR		CLR_CH10
	#define		CLC_T7_FST_ADDR		CLR_CH10
	
/*---------------------------------------------------------------------------*/
/***	THCRx   (Trigger Handler Control Reg x)                            ***/
/*---------------------------------------------------------------------------*/
	/* Set Handler: first TrigN Enabled, then EXT OutEN, eTimer1 OutEN, eTimer0 OutEN, ADC OutEN */
	#define		THC_T0_HANDLE_EN	ENABLE
	#define		THC_T0_EXT_EN		DISABLE
	#define		THC_T0_ET1_EN		DISABLE
	#define		THC_T0_ET0_EN		DISABLE
	#define		THC_T0_ADC_EN		ENABLE	
	
	#define		THC_T1_HANDLE_EN	ENABLE
	#define		THC_T1_EXT_EN		DISABLE
	#define		THC_T1_ET1_EN		DISABLE
	#define		THC_T1_ET0_EN		DISABLE
	#define		THC_T1_ADC_EN		ENABLE		
	
	#define		THC_T2_HANDLE_EN	ENABLE
	#define		THC_T2_EXT_EN		DISABLE
	#define		THC_T2_ET1_EN		DISABLE
	#define		THC_T2_ET0_EN		DISABLE
	#define		THC_T2_ADC_EN		ENABLE	
	
	#define		THC_T3_HANDLE_EN	DISABLE
	#define		THC_T3_EXT_EN		DISABLE
	#define		THC_T3_ET1_EN		DISABLE
	#define		THC_T3_ET0_EN		DISABLE
	#define		THC_T3_ADC_EN		DISABLE		
	
	#define		THC_T4_HANDLE_EN	DISABLE
	#define		THC_T4_EXT_EN		DISABLE
	#define		THC_T4_ET1_EN		DISABLE
	#define		THC_T4_ET0_EN		DISABLE
	#define		THC_T4_ADC_EN		DISABLE		
	
	#define		THC_T5_HANDLE_EN	DISABLE
	#define		THC_T5_EXT_EN		DISABLE
	#define		THC_T5_ET1_EN		DISABLE
	#define		THC_T5_ET0_EN		DISABLE
	#define		THC_T5_ADC_EN		DISABLE		
	
	#define		THC_T6_HANDLE_EN	DISABLE
	#define		THC_T6_EXT_EN		DISABLE
	#define		THC_T6_ET1_EN		DISABLE
	#define		THC_T6_ET0_EN		DISABLE
	#define		THC_T6_ADC_EN		DISABLE		
	
	#define		THC_T7_HANDLE_EN	DISABLE
	#define		THC_T7_EXT_EN		DISABLE
	#define		THC_T7_ET1_EN		DISABLE
	#define		THC_T7_ET0_EN		DISABLE
	#define		THC_T7_ADC_EN		DISABLE	

	
	#ifdef	CTU_FIFO_ENABLED
		/* FIFO threshold register (FTH), defined from SysConfig.h	*/
		#define		FTH_FIFO0_VAL	SYS_CTU_THRESH_0
		#define		FTH_FIFO1_VAL	SYS_CTU_THRESH_1
		#define		FTH_FIFO2_VAL	SYS_CTU_THRESH_2
		#define		FTH_FIFO3_VAL	SYS_CTU_THRESH_3
	
	#endif
	
	/* CLRx  Commands list register x (x = 1,...,24)*/
	#define		CLR_CONV_MODE		CLR_CONV_DUAL
	
	#ifndef ADC_SINGLE_CONV	
		/* CLR 1 */
		/* INTC_EN: Command Interrupt Request, (Enabled or Disabled) */
		/* FST_CMD: First Command, (yes or not) */
		/* FIFO_N:  FIFO Selected for ADC Results Stored */
		/* ADC_B:   ADC1 Channel Num */
		/* ADC_A:   ADC0 Channel Num */
/*---------------------------------------------------------------------------*/
/***	CLR 1				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH1_INTC_EN		DISABLE
		#define		CLR_CH1_FST_CMD		ENABLE
		#define		CLR_CH1_FIFO_N		CTU_FIFO0
		#define		CLR_CH1_ADC_B		AD_CH12     /* AD0_Sec_Curr_fast */
		#define		CLR_CH1_ADC_A		AD_CH5     /* AD0_Pri_Curr_High */

/*---------------------------------------------------------------------------*/
/***	CLR 2				                                               ***/
/*---------------------------------------------------------------------------*/		
		#define		CLR_CH2_INTC_EN		DISABLE
		#define		CLR_CH2_FST_CMD		ENABLE
		#define		CLR_CH2_FIFO_N		CTU_FIFO0
		#define		CLR_CH2_ADC_B		AD_CH5   /* AD0_Pri_Curr_Low */
		#define		CLR_CH2_ADC_A		AD_CH0	  /* I_AD_Vout */	
		
/*---------------------------------------------------------------------------*/
/***	CLR 3				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH3_INTC_EN		DISABLE
		#define		CLR_CH3_FST_CMD		ENABLE
		#define		CLR_CH3_FIFO_N		CTU_FIFO1
		//#define		CLR_CH3_ADC_B		AD_CH11     /* AD0_AC_Volt_fast */
		//#define		CLR_CH3_ADC_A		AD_CH4    /* I_AD_FB_TEM */
		#define		CLR_CH3_ADC_B		AD_CH3     /* AD0_AC_Volt_fast */
		#define		CLR_CH3_ADC_A		AD_CH11    /* I_AD_PFC_slow */

/*---------------------------------------------------------------------------*/
/***	CLR 4				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH4_INTC_EN		DISABLE
		//#define		CLR_CH4_FST_CMD		DISABLE
		#define		CLR_CH4_FST_CMD		DISABLE
		#define		CLR_CH4_FIFO_N		CTU_FIFO1
		#define		CLR_CH4_ADC_B		AD_CH0    //I_AD_Curr_Input
		#define		CLR_CH4_ADC_A		AD_CH3     	//I_AD_CP

/*---------------------------------------------------------------------------*/
/***	CLR 5				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH5_INTC_EN		DISABLE	
		#define		CLR_CH5_FST_CMD		DISABLE
		//#define		CLR_CH5_FST_CMD		ENABLE
		#define		CLR_CH5_FIFO_N		CTU_FIFO1
		//#define		CLR_CH5_ADC_B		AD_CH14 //I_AD_PFC_TEM
		
		#define		CLR_CH5_ADC_B		AD_CH1  // I_AD_PCB_TEM
		#define		CLR_CH5_ADC_A		AD_CH4  //I_AD_FB_TEM
				
/*---------------------------------------------------------------------------*/
/***	CLR 6				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH6_INTC_EN		DISABLE
		#define		CLR_CH6_FST_CMD		DISABLE
		//#define		CLR_CH6_FST_CMD		ENABLE
		#define		CLR_CH6_FIFO_N		CTU_FIFO1
		#define		CLR_CH6_ADC_B		AD_CH4    //I_AD_CC 
		#define		CLR_CH6_ADC_A		AD_CH2    //I_AD_Driver13V
	
/*---------------------------------------------------------------------------*/
/***	CLR 7				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH7_INTC_EN		DISABLE
		#define		CLR_CH7_FST_CMD		DISABLE
		#define		CLR_CH7_FIFO_N		CTU_FIFO1 
		#define		CLR_CH7_ADC_B		AD_CH2   //I_AD_12V_CMM  
		#define		CLR_CH7_ADC_A		AD_CH13	//I_AD_RelayCoil1	
		
/*---------------------------------------------------------------------------*/
/***	CLR 8				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH8_INTC_EN		DISABLE
		#define		CLR_CH8_FST_CMD		ENABLE
		#define		CLR_CH8_FIFO_N		CTU_FIFO1
		#define		CLR_CH8_ADC_B		AD_CH2
		#define		CLR_CH8_ADC_A		AD_CH13			
		
/*---------------------------------------------------------------------------*/
/***	CLR 9				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH9_INTC_EN		DISABLE
		#define		CLR_CH9_FST_CMD		DISABLE
		#define		CLR_CH9_FIFO_N		CTU_FIFO0
		#define		CLR_CH9_ADC_B		AD_CH5
		#define		CLR_CH9_ADC_A		AD_CH5	
		
/*---------------------------------------------------------------------------*/
/***	CLR 10				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH10_INTC_EN	DISABLE
		#define		CLR_CH10_FST_CMD	ENABLE
		#define		CLR_CH10_FIFO_N		CTU_FIFO0
		#define		CLR_CH10_ADC_B		AD_CH0     /* I_AD_ResolverCos */
		#define		CLR_CH10_ADC_A		AD_CH0     /* I_AD_ResolverSin */
			
/*---------------------------------------------------------------------------*/
/***	CLR 11				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH11_INTC_EN	DISABLE
		#define		CLR_CH11_FST_CMD	DISABLE
		#define		CLR_CH11_FIFO_N		CTU_FIFO1
		#define		CLR_CH11_ADC_B		AD_CH11   /* I_AD_ResolverEXR1 */
		#define		CLR_CH11_ADC_A		AD_CH12	  /* I_AD_ResolverEXR2 */	

/*---------------------------------------------------------------------------*/
/***	CLR 12				                                               ***/
/*---------------------------------------------------------------------------*/	
		#define		CLR_CH12_INTC_EN	DISABLE	
		#define		CLR_CH12_FST_CMD	DISABLE
		#define		CLR_CH12_FIFO_N		CTU_FIFO1
		#define		CLR_CH12_ADC_B		AD_CH1    /* I_AD_RelayCoil */
		#define		CLR_CH12_ADC_A		AD_CH2    /* I_AD_Sensor5V_M */	
	
/*---------------------------------------------------------------------------*/
/***	CLR 13				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH13_INTC_EN	DISABLE
		#define		CLR_CH13_FST_CMD	DISABLE
		#define		CLR_CH13_FIFO_N		CTU_FIFO1
		#define		CLR_CH13_ADC_B		AD_CH2    /* I_AD_12V&CMM_M  */
		#define		CLR_CH13_ADC_A		AD_CH3    /* I_AD_Reference2.5V_M */		
		
/*---------------------------------------------------------------------------*/
/***	CLR 14				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH14_INTC_EN	DISABLE
		#define		CLR_CH14_FST_CMD	DISABLE
		#define		CLR_CH14_FIFO_N		CTU_FIFO1
		#define		CLR_CH14_ADC_B		AD_CH3     /* I_AD_12V&MOS_M */
		#define		CLR_CH14_ADC_A		AD_CH13	   /* I_AD_IGN_M */
			
/*---------------------------------------------------------------------------*/
/***	CLR 15				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH15_INTC_EN	DISABLE
		#define		CLR_CH15_FST_CMD	DISABLE
		#define		CLR_CH15_FIFO_N		CTU_FIFO1
		#define		CLR_CH15_ADC_B		AD_CH4      /* I_AD_VCCR */
		#define		CLR_CH15_ADC_A		AD_CH14     /* I_AD_PCB&TEM_M */
				
/*---------------------------------------------------------------------------*/
/***	CLR 16				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH16_INTC_EN	DISABLE
		#define		CLR_CH16_FST_CMD	ENABLE
		#define		CLR_CH16_FIFO_N		CTU_FIFO0
		#define		CLR_CH16_ADC_B		AD_CH0
		#define		CLR_CH16_ADC_A		AD_CH0		
		
/*---------------------------------------------------------------------------*/
/***	CLR 17				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH17_INTC_EN	DISABLE
		#define		CLR_CH17_FST_CMD	ENABLE
		#define		CLR_CH17_FIFO_N		CTU_FIFO0
		#define		CLR_CH17_ADC_B		AD_CH0
		#define		CLR_CH17_ADC_A		AD_CH0		
			
/*---------------------------------------------------------------------------*/
/***	CLR 18				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH18_INTC_EN	DISABLE		
		#define		CLR_CH18_FST_CMD	ENABLE
		#define		CLR_CH18_FIFO_N		CTU_FIFO0
		#define		CLR_CH18_ADC_B		AD_CH0
		#define		CLR_CH18_ADC_A		AD_CH0
		
/*---------------------------------------------------------------------------*/
/***	CLR 19				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH19_INTC_EN	DISABLE
		#define		CLR_CH19_FST_CMD	ENABLE
		#define		CLR_CH19_FIFO_N		CTU_FIFO0
		#define		CLR_CH19_ADC_B		AD_CH0
		#define		CLR_CH19_ADC_A		AD_CH0
		
/*---------------------------------------------------------------------------*/
/***	CLR 20				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH20_INTC_EN	DISABLE
		#define		CLR_CH20_FST_CMD	ENABLE
		#define		CLR_CH20_FIFO_N		CTU_FIFO0
		#define		CLR_CH20_ADC_B		AD_CH0
		#define		CLR_CH20_ADC_A		AD_CH0

/*---------------------------------------------------------------------------*/
/***	CLR 21				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH21_INTC_EN	DISABLE
		#define		CLR_CH21_FST_CMD	ENABLE
		#define		CLR_CH21_FIFO_N		CTU_FIFO0
		#define		CLR_CH21_ADC_B		AD_CH0
		#define		CLR_CH21_ADC_A		AD_CH0
		
/*---------------------------------------------------------------------------*/
/***	CLR 22				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH22_INTC_EN	DISABLE
		#define		CLR_CH22_FST_CMD	ENABLE
		#define		CLR_CH22_FIFO_N		CTU_FIFO0
		#define		CLR_CH22_ADC_B		AD_CH0
		#define		CLR_CH22_ADC_A		AD_CH0
		
/*---------------------------------------------------------------------------*/
/***	CLR 23				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH23_INTC_EN	DISABLE
		#define		CLR_CH23_FST_CMD	ENABLE
		#define		CLR_CH23_FIFO_N		CTU_FIFO0
		#define		CLR_CH23_ADC_B		AD_CH0
		#define		CLR_CH23_ADC_A		AD_CH0
		
/*---------------------------------------------------------------------------*/
/***	CLR 24				                                               ***/
/*---------------------------------------------------------------------------*/
		#define		CLR_CH24_INTC_EN	DISABLE		
		#define		CLR_CH24_FST_CMD	ENABLE
		#define		CLR_CH24_FIFO_N		CTU_FIFO0
		#define		CLR_CH24_ADC_B		AD_CH0
		#define		CLR_CH24_ADC_A		AD_CH0

	#else	/* Single */		

	#endif	

#endif


#endif	
