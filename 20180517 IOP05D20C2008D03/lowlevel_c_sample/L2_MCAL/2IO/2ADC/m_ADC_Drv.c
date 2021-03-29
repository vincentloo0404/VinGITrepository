/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_ADC_Drv.c
*
* @brief    ADC Module Operation, Init, get ADC value, convert ADC operation mode 
*
********************************************************************************
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
*******************************************************************************/

#ifndef M_ADC_DRV_C
#define M_ADC_DRV_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_ADC_Drv.h"
#include 	"m_ADC_Cfg.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */
/* *****************************************************************************
   Function:        mADC_Align_Set
   Description:     Set ADC_data align mode
   Parameters:      Input:		ModuleNum: ADC module Index
   								Mode: Align mode, 0,right-align; 1, left-align
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Align_Set(uint8 ModuleNum, uint32 Mode)
{
	ADC_MCR(ModuleNum) &= (~ADC_MCR_WLSIDE_MASK);
	ADC_MCR(ModuleNum) |= ((Mode & 0x01)<<30);
}


/* *****************************************************************************
   Function:        mADC_Mode_Set
   Description:     Set ADC Conversion Mode, OneShot or Scan
   Parameters:      Input:		ModuleNum: ADC module Index
   								Mode: Conversion mode, 0,OneShot; 1, Scan
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Mode_Set(uint8 ModuleNum, uint32 Mode)
{
	ADC_MCR(ModuleNum) &= (~ADC_MCR_MODE_MASK);
	ADC_MCR(ModuleNum) |= ((Mode & 0x01)<<29);
}


/* *****************************************************************************
   Function:        mADC_Normal_Stop
   Description:     Causes Current Chain Conversion to finish and then stops operation
   Parameters:      Input:		ModuleNum: ADC module Index
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mADC_Normal_Stop(uint8 ModuleNum)
{
	ADC_MCR(ModuleNum) &= (~ADC_MCR_NSTART_MASK);
}


/* *****************************************************************************
   Function:        mADC_Normal_Start
   Description:     Starts the chain or scan conversion
   Parameters:      Input:		ModuleNum: ADC module Index
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mADC_Normal_Start(uint8 ModuleNum)
{
	ADC_MCR(ModuleNum) |= ADC_MCR_NSTART_MASK;
}


/* *****************************************************************************
   Function:        mADC_CTU_En_Set
   Description:     Enable or Disable CTU Trgigged ADC
   Parameters:      Input:		ModuleNum: ADC module Index
   								ValEn: 0,Disable; 1, Enable
                    Output:   	None
   Notes:           CTU_ADC Operation should Enable CTUEN
                   
   ***************************************************************************** */
void	mADC_CTU_En_Set(uint8 ModuleNum, uint32 ValEn)
{
	ADC_MCR(ModuleNum) &= (~ADC_MCR_CTUEN_MASK);
	ADC_MCR(ModuleNum) |= ((ValEn & 0x01)<<17);
}


/* *****************************************************************************
   Function:        mADC_Intc_En
   Description:     Set Intc Source Enabled
   Parameters:      Input:		ModuleNum: ADC module Index
   								IntcSrc: Intc Source, Use Macro Def input
                    Output:   None
   Notes:           

   ***************************************************************************** */
static	void	mADC_Intc_En(uint8 ModuleNum, uint8 IntcSrc)
{
	switch(IntcSrc)
	{
		case ADC_EOCTU:		/* End of CTU conversion (EOCTU) interrupt */
			ADC_IMR(ModuleNum) |= ADC_IMR_MSKEOCTU_MASK;
			break;
		case ADC_JEOC:		/* End of injected channel conversion (JEOC) interrupt */
			ADC_IMR(ModuleNum) |= ADC_IMR_MSKJEOC_MASK;
			break;
		case ADC_JECH:		/* End of injected chain conversion (JECH) interrupt */
			ADC_IMR(ModuleNum) |= ADC_IMR_MSKJECH_MASK;
			break;
		case ADC_EOC:		/* End of channel conversion (EOC) interrupt */
			ADC_IMR(ModuleNum) |= ADC_IMR_MSKEOC_MASK;
			break;
		case ADC_ECH:		/* End of chain conversion (ECH) interrupt */
			ADC_IMR(ModuleNum) |= ADC_IMR_MSKECH_MASK;
			break;	

		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mADC_Intc_WatchDog_En
   Description:     Set Watcgdog Threshold Intc Source Enabled
   Parameters:      Input:		ModuleNum: ADC module Index
   								IntcSrc: WT Intc Source, Use Macro Def input
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Intc_WatchDog_En(uint8 ModuleNum, uint8 IntcSrc)
{
	switch(IntcSrc)
	{
		case WTIM_0L:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG0L_MASK;
			break;
		case WTIM_1L:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG1L_MASK;
			break;
		case WTIM_2L:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG2L_MASK;
			break;
		case WTIM_3L:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG3L_MASK;
			break;
		case WTIM_0H:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG0H_MASK;
			break;
		case WTIM_1H:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG1H_MASK;
			break;
		case WTIM_2H:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG2H_MASK;
			break;
		case WTIM_3H:
			ADC_WTIMR(ModuleNum) |= ADC_WTIMR_MSKWDG3H_MASK;
			break;			

		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mADC_DMA_Chan_En
   Description:     Set ADC Channel Enabled to transfer data in DMA mode
   Parameters:      Input:		ModuleNum: ADC module Index
   								ChanNum:   ADC Channel Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_DMA_Chan_En(uint8 ModuleNum, uint8 ChanNum)
{
	switch(ChanNum)
	{
		case ADC_CH0:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA0_MASK;
			break;
		case ADC_CH1:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA1_MASK;
			break;
		case ADC_CH2:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA2_MASK;
			break;
		case ADC_CH3:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA3_MASK;
			break;
		case ADC_CH4:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA4_MASK;
			break;
		case ADC_CH5:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA5_MASK;
			break;
		case ADC_CH6:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA6_MASK;
			break;
		case ADC_CH7:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA7_MASK;
			break;
		case ADC_CH8:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA8_MASK;
			break;
		case ADC_CH9:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA9_MASK;
			break;
		case ADC_CH10:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA10_MASK;
			break;
		case ADC_CH11:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA11_MASK;
			break;
		case ADC_CH12:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA12_MASK;
			break;
		case ADC_CH13:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA13_MASK;
			break;
		case ADC_CH14:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA14_MASK;
			break;
		case ADC_CH15:
			ADC_DMAR0(ModuleNum) |= ADC_DMAR0_DMA15_MASK;
			break;

		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mADC_Thrsh_En_Set
   Description:     Enable or Disable Threshold Intc Source
   Parameters:      Input:		ModuleNum: ADC module Index
   								ThrNum:    TRCx Index
   								ValEn:	1,Enable or 0,Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Thrsh_En_Set(uint8 ModuleNum, uint8 ThrNum, uint32 ValEn)
{
	ADC_TRC(ModuleNum, ThrNum) &= (~ADC_TRC_THREN_MASK);
	ADC_TRC(ModuleNum, ThrNum) |= ((ValEn & 0x01)<<15);
}


/* *****************************************************************************
   Function:        mADC_Thrsh_High_Set
   Description:     Set Threshold Upper Value
   Parameters:      Input:		ModuleNum: ADC module Index
   								ThrNum:    TRCx Index
   								ValEn:	Threshold Upper Value
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Thrsh_High_Set(uint8 ModuleNum, uint8 ThrNum, uint32 ValThrshHigh)
{
	ADC_THRHLR(ModuleNum, ThrNum) &= (~ADC_THRHLR_THRH_MASK);
	ADC_THRHLR(ModuleNum, ThrNum) |= ((ValThrshHigh & 0x3FF)<<16);
}


/* *****************************************************************************
   Function:        mADC_Thrsh_Low_Set
   Description:     Set Threshold Lower Value
   Parameters:      Input:		ModuleNum: ADC module Index
   								ThrNum:    TRCx Index
   								ValEn:	Threshold Lower Value
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Thrsh_Low_Set(uint8 ModuleNum, uint8 ThrNum, uint32 ValThrshLow)
{
	ADC_THRHLR(ModuleNum, ThrNum) &= (~ADC_THRHLR_THRL_MASK);
	ADC_THRHLR(ModuleNum, ThrNum) |= ((ValThrshLow & 0x3FF)<<0);
}


/* *****************************************************************************
   Function:        mADC_Normal_Chan_En
   Description:     Enable bits of Normal Sampling for Channel 0 to 15
   Parameters:      Input:		ModuleNum: ADC module Index
   								ChanNum:   ADC Channel Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Normal_Chan_En(uint8 ModuleNum, uint8 ChanNum)
{
	switch(ChanNum)
	{
		case ADC_CH0:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH0_MASK;
			break;
		case ADC_CH1:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH1_MASK;
			break;
		case ADC_CH2:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH2_MASK;
			break;
		case ADC_CH3:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH3_MASK;
			break;			
		case ADC_CH4:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH4_MASK;
			break;
		case ADC_CH5:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH5_MASK;
			break;
		case ADC_CH6:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH6_MASK;
			break;
		case ADC_CH7:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH7_MASK;
			break;			
		case ADC_CH8:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH8_MASK;
			break;
		case ADC_CH9:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH9_MASK;
			break;
		case ADC_CH10:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH10_MASK;
			break;
		case ADC_CH11:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH11_MASK;
			break;			
		case ADC_CH12:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH12_MASK;
			break;
		case ADC_CH13:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH13_MASK;
			break;
		case ADC_CH14:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH14_MASK;
			break;
		case ADC_CH15:
			ADC_NCMR0(ModuleNum) |= ADC_NCMR0_CH15_MASK;
			break;			
		
		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mADC_Normal_Chan_Dis
   Description:     Disable bits of Normal Sampling for Channel 0 to 15
   Parameters:      Input:		ModuleNum: ADC module Index
   								ChanNum:   ADC Channel Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Normal_Chan_Dis(uint8 ModuleNum, uint8 ChanNum)
{
	switch(ChanNum)
	{
		case ADC_CH0:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH0_MASK);
			break;
		case ADC_CH1:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH1_MASK);
			break;
		case ADC_CH2:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH2_MASK);
			break;
		case ADC_CH3:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH3_MASK);
			break;
		case ADC_CH4:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH4_MASK);
			break;
		case ADC_CH5:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH5_MASK);
			break;
		case ADC_CH6:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH6_MASK);
			break;
		case ADC_CH7:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH7_MASK);
			break;
		case ADC_CH8:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH8_MASK);
			break;
		case ADC_CH9:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH9_MASK);
			break;
		case ADC_CH10:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH10_MASK);
			break;
		case ADC_CH11:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH11_MASK);
			break;
		case ADC_CH12:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH12_MASK);
			break;
		case ADC_CH13:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH13_MASK);
			break;
		case ADC_CH14:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH14_MASK);
			break;
		case ADC_CH15:
			ADC_NCMR0(ModuleNum) &= (~ADC_NCMR0_CH15_MASK);
			break;

		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mADC_Inject_Chan_En
   Description:     Enable bits of Injected Sampling for Channel 0 to 15
   Parameters:      Input:		ModuleNum: ADC module Index
   								ChanNum:   ADC Channel Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mADC_Inject_Chan_En(uint8 ModuleNum, uint8 ChanNum)
{
	switch(ChanNum)
	{
		case ADC_CH0:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH0_MASK;
			break;
		case ADC_CH1:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH1_MASK;
			break;
		case ADC_CH2:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH2_MASK;
			break;
		case ADC_CH3:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH3_MASK;
			break;			
		case ADC_CH4:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH4_MASK;
			break;
		case ADC_CH5:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH5_MASK;
			break;
		case ADC_CH6:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH6_MASK;
			break;
		case ADC_CH7:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH7_MASK;
			break;			
		case ADC_CH8:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH8_MASK;
			break;
		case ADC_CH9:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH9_MASK;
			break;
		case ADC_CH10:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH10_MASK;
			break;
		case ADC_CH11:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH11_MASK;
			break;			
		case ADC_CH12:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH12_MASK;
			break;
		case ADC_CH13:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH13_MASK;
			break;
		case ADC_CH14:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH14_MASK;
			break;
		case ADC_CH15:
			ADC_JCMR0(ModuleNum) |= ADC_JCMR0_CH15_MASK;
			break;			
		
		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mADC0_Init
   Description:     Initation ADC0 Module
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mADC0_Init(void)
{
	/* ABORT State, No Conversion */
	REG32_BIT_SET(ADC_MCR(ADC0), ADC_MCR_PWDN_MASK);	/* in powerdown mode */
	REG32_BIT_SET(ADC_MCR(ADC0), ADC_MCR_ABORT_MASK);	/* Aborts Conversion */

	/* ADC Sampling and ThresHold Configuration */
	/* ADC0_CTR0_VALUE */
	/* ((1<<B_LATCH)|(0<<B_SHIFT)|(3<<B_CMP)|(17<<B_SAMP)); */
	/* ADC0 Sample Comment */
	/* Tck = 2/Mclk 
	/* Tsamp = (INPSAMP - Ndelay)*Tck 
	/* Teval = 10*INPCMP*Tck 
	/* Tconv = Tsamp + Teval + Ndelay*Tck = (INPSAMP + 10*INPCMP)*Tck 
	/* Tconv = (17 + 10*3)*Tck = 47*Tck 	*/
	REG32_WRITE(ADC_CTR0(ADC0), ADC0_CTR0_VALUE);		/* Conversion Timing */
	REG32_BIT_CLEAR(ADC_MCR(ADC0), ADC_MCR_PWDN_MASK);	/* Exit powerdown mode */
	
	/* ADC General Setup   (MCR_OWREN|MCR_SHOT|MCR_CTUEN) */
	REG32_BIT_SET(ADC_MCR(ADC0), ADC_MCR_OWREN_MASK);	/* ADC0 OverWrite Enabled */
	mADC_Mode_Set(ADC0, ADC0_MCR_MODE);					/* ADC Mode: OneShot or Scan */
	mADC_Align_Set(ADC0, ADC0_MCR_ALIGN_MODE);			/* Align: Left or Right */
	
	/* ADC CTU Configuration */
#ifdef	ADC_CTU_INIT
	mADC_CTU_En_Set(ADC0, ENABLE);
#else
	mADC_CTU_En_Set(ADC0, DISABLE);
#endif	
	ADC_PDEDR(ADC0) &= (~ADC_PDEDR_PDED_MASK);
	ADC_PDEDR(ADC0) |= ((ADC0_PDEDR_DELAY & 0xFF)<<0);	/* Delay between power-down reset and conversion */
	
	/* ADC Interrupt Configuration */
#ifdef	ADC0_IMR_ENABLED
	mADC_Intc_En(ADC0, ADC_EOCTU);						/* End of CTU conversion (EOCTU) interrupt */
	mADC_Intc_En(ADC0, ADC_JEOC);						/* End of injected channel conversion (JEOC) interrupt */
	mADC_Intc_En(ADC0, ADC_JECH);						/* End of injected chain conversion (JECH) interrupt */
	mADC_Intc_En(ADC0, ADC_EOC);						/* End of channel conversion (EOC) interrupt */
	mADC_Intc_En(ADC0, ADC_ECH);						/* End of chain conversion (ECH) interrupt */
#endif

	/* ADC0 Channel Configuration */
#ifdef	ADC0_CH0_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH0);
#endif
#ifdef	ADC0_CH1_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH1);
#endif
#ifdef	ADC0_CH2_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH2);
#endif
#ifdef	ADC0_CH3_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH3);
#endif
#ifdef	ADC0_CH4_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH4);
#endif
#ifdef	ADC0_CH5_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH5);
#endif
#ifdef	ADC0_CH6_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH6);
#endif
#ifdef	ADC0_CH7_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH7);
#endif
#ifdef	ADC0_CH8_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH8);
#endif
#ifdef	ADC0_CH9_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH9);
#endif
#ifdef	ADC0_CH10_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH10);
#endif
#ifdef	ADC0_CH11_PIN
	mADC_Normal_Chan_En(ADC0, ADC_CH11);
#endif
#ifdef	ADC0_CH12_PIN	
	mADC_Normal_Chan_En(ADC0, ADC_CH12);
#endif
#ifdef	ADC0_CH13_PIN	
	mADC_Normal_Chan_En(ADC0, ADC_CH13);
#endif
#ifdef	ADC0_CH14_PIN	
	mADC_Normal_Chan_En(ADC0, ADC_CH14);
#endif

	/* Injected Conversion Enabled */
#ifdef	ADC0_JCMR_ENABLED
	#ifdef	ADC0_CH0_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH0);
	#endif
	#ifdef	ADC0_CH1_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH1);
	#endif
	#ifdef	ADC0_CH2_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH2);
	#endif
	#ifdef	ADC0_CH3_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH3);
	#endif
	#ifdef	ADC0_CH4_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH4);
	#endif
	#ifdef	ADC0_CH5_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH5);
	#endif
	#ifdef	ADC0_CH6_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH6);
	#endif
	#ifdef	ADC0_CH7_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH7);
	#endif
	#ifdef	ADC0_CH8_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH8);
	#endif
	#ifdef	ADC0_CH9_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH9);
	#endif
	#ifdef	ADC0_CH10_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH10);
	#endif
	#ifdef	ADC0_CH11_PIN
		mADC_Inject_Chan_En(ADC0, ADC_CH11);
	#endif
	#ifdef	ADC0_CH12_PIN	
		mADC_Inject_Chan_En(ADC0, ADC_CH12);
	#endif
	#ifdef	ADC0_CH13_PIN	
		mADC_Inject_Chan_En(ADC0, ADC_CH13);
	#endif
	#ifdef	ADC0_CH14_PIN	
		mADC_Inject_Chan_En(ADC0, ADC_CH14);
	#endif
#endif	

	/* SIU Channel Conifg */
#ifdef	ADC0_CH0_PIN
	SIU.PCR[ADC0_CH0_PIN].R   = ADC_PCR;		/* AN0_0 */
#endif
#ifdef	ADC0_CH1_PIN
	SIU.PCR[ADC0_CH1_PIN].R   = ADC_PCR;		/* AN0_1 */
#endif
#ifdef	ADC0_CH2_PIN
	SIU.PCR[ADC0_CH2_PIN].R   = ADC_PCR;		/* AN0_2 */
#endif
#ifdef	ADC0_CH3_PIN
	SIU.PCR[ADC0_CH3_PIN].R   = ADC_PCR;		/* AN0_3 */
#endif
#ifdef	ADC0_CH4_PIN
	SIU.PCR[ADC0_CH4_PIN].R   = ADC_PCR;		/* AN0_4 */
#endif
#ifdef	ADC0_CH5_PIN
	SIU.PCR[ADC0_CH5_PIN].R   = ADC_PCR;		/* AN0_5 */
#endif
#ifdef	ADC0_CH6_PIN
	SIU.PCR[ADC0_CH6_PIN].R   = ADC_PCR;		/* AN0_6 */
#endif
#ifdef	ADC0_CH7_PIN
	SIU.PCR[ADC0_CH7_PIN].R   = ADC_PCR;		/* AN0_7 */
#endif
#ifdef	ADC0_CH8_PIN
	SIU.PCR[ADC0_CH8_PIN].R   = ADC_PCR;		/* AN0_8 */
#endif
#ifdef	ADC0_CH9_PIN
	SIU.PCR[ADC0_CH9_PIN].R   = ADC_PCR;		/* AN0_9 */
#endif
#ifdef	ADC0_CH10_PIN
	SIU.PCR[ADC0_CH10_PIN].R  = ADC_PCR;		/* AN0_10 */
#endif
#ifdef	ADC0_CH11_PIN
	SIU.PCR[ADC0_CH11_PIN].R  = ADC_PCR;		/* AN0_11 */
#endif
#ifdef	ADC0_CH12_PIN	
	SIU.PCR[ADC0_CH12_PIN].R  = ADC_PCR;		/* AN0_12 */
#endif
#ifdef	ADC0_CH13_PIN	
	SIU.PCR[ADC0_CH13_PIN].R  = ADC_PCR;		/* AN0_13 */
#endif
#ifdef	ADC0_CH14_PIN	
	SIU.PCR[ADC0_CH14_PIN].R  = ADC_PCR;		/* AN0_14 */
#endif

	/* ADC0 Threshold Enabled */
#ifdef	ADC0_THRESH_ENABLED
	mADC_Thrsh_En_Set(ADC0, ADC_THR0, DISABLE);
	mADC_Thrsh_En_Set(ADC0, ADC_THR1, DISABLE);
	mADC_Thrsh_En_Set(ADC0, ADC_THR2, DISABLE);
	mADC_Thrsh_En_Set(ADC0, ADC_THR3, DISABLE);
	mADC_Thrsh_High_Set(ADC0, ADC_THR0, ADC0_THR0_HIGH);
	mADC_Thrsh_Low_Set(ADC0, ADC_THR0, ADC0_THR0_LOW);
	mADC_Thrsh_High_Set(ADC0, ADC_THR1, ADC0_THR1_HIGH);
	mADC_Thrsh_Low_Set(ADC0, ADC_THR1, ADC0_THR1_LOW);
	mADC_Thrsh_High_Set(ADC0, ADC_THR2, ADC0_THR2_HIGH);
	mADC_Thrsh_Low_Set(ADC0, ADC_THR2, ADC0_THR2_LOW);
	mADC_Thrsh_High_Set(ADC0, ADC_THR3, ADC0_THR3_HIGH);
	mADC_Thrsh_Low_Set(ADC0, ADC_THR3, ADC0_THR3_LOW);
#endif

	/* ADC0 WatchDog Enabled */
#ifdef	ADC0_WATCHDOG_INTC
	mADC_Intc_WatchDog_En(ADC0, WTIM_0L);
	mADC_Intc_WatchDog_En(ADC0, WTIM_1L);
	mADC_Intc_WatchDog_En(ADC0, WTIM_2L);
	mADC_Intc_WatchDog_En(ADC0, WTIM_3L);
	mADC_Intc_WatchDog_En(ADC0, WTIM_0H);
	mADC_Intc_WatchDog_En(ADC0, WTIM_1H);
	mADC_Intc_WatchDog_En(ADC0, WTIM_2H);
	mADC_Intc_WatchDog_En(ADC0, WTIM_3H);
#endif

	/* ADC Trigger Configuration */
	REG32_BIT_SET(ADC_MCR(ADC0), ADC_MCR_JTRGEN_MASK);	/* Ext Trig Enabled for Channel Injection */
	REG32_BIT_SET(ADC_MCR(ADC0), ADC_MCR_JEDGE_MASK);	/* Rising Edge for Ext Trig */

	/* DMA Setup Function(s) */
#ifdef ADC0_DMA_ENABLED
	ADC_DMAE(ADC0) &= (~ADC_DMAE_DCLR_MASK);
	ADC_DMAE(ADC0) |= ((ADC0_DMA_CLR_SEQ_EN & 0x01)<<1);
	ADC_DMAE(ADC0) &= (~ADC_DMAE_DMAEN_MASK);
	ADC_DMAE(ADC0) |= ((ADC0_DMA_EN & 0x01)<<0);

	#ifdef	ADC0_CH0_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH0);
	#endif
	#ifdef	ADC0_CH1_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH1);
	#endif
	#ifdef	ADC0_CH2_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH2);
	#endif
	#ifdef	ADC0_CH3_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH3);
	#endif
	#ifdef	ADC0_CH4_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH4);
	#endif
	#ifdef	ADC0_CH5_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH5);
	#endif
	#ifdef	ADC0_CH6_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH6);
	#endif
	#ifdef	ADC0_CH7_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH7);
	#endif
	#ifdef	ADC0_CH8_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH8);
	#endif
	#ifdef	ADC0_CH9_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH9);
	#endif
	#ifdef	ADC0_CH10_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH10);
	#endif
	#ifdef	ADC0_CH11_PIN
		mADC_DMA_Chan_En(ADC0, ADC_CH11);
	#endif
	#ifdef	ADC0_CH12_PIN	
		mADC_DMA_Chan_En(ADC0, ADC_CH12);
	#endif
	#ifdef	ADC0_CH13_PIN	
		mADC_DMA_Chan_En(ADC0, ADC_CH13);
	#endif
	#ifdef	ADC0_CH14_PIN	
		mADC_DMA_Chan_En(ADC0, ADC_CH14);
	#endif
#endif

	/* ADC0 Exit Abort */
	REG32_BIT_CLEAR(ADC_MCR(ADC0), ADC_MCR_ABORT_MASK);	/* Conversion no affected */
}


/* *****************************************************************************
   Function:        mADC1_Init
   Description:     Initation ADC1 Module
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mADC1_Init(void)
{
	/* ABORT State, No Conversion */
	REG32_BIT_SET(ADC_MCR(ADC1), ADC_MCR_PWDN_MASK);	/* in powerdown mode */
	REG32_BIT_SET(ADC_MCR(ADC1), ADC_MCR_ABORT_MASK);	/* Aborts Conversion */

	/* ADC Sampling and ThresHold Configuration */
	/* ADC1_CTR0_VALUE */
	/* ((1<<B_LATCH)|(0<<B_SHIFT)|(3<<B_CMP)|(17<<B_SAMP)); */
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
	REG32_WRITE(ADC_CTR0(ADC1), ADC1_CTR0_VALUE);		/* Conversion Timing */
	REG32_BIT_CLEAR(ADC_MCR(ADC1), ADC_MCR_PWDN_MASK);	/* Exit powerdown mode */
	
	/* ADC General Setup   (MCR_OWREN|MCR_SHOT|MCR_CTUEN) */
	REG32_BIT_SET(ADC_MCR(ADC1), ADC_MCR_OWREN_MASK);	/* ADC1 OverWrite Enabled */
	mADC_Mode_Set(ADC1, ADC1_MCR_MODE);					/* ADC Mode, OneShot or Scan */
	mADC_Align_Set(ADC1, ADC1_MCR_ALIGN_MODE);			/* Align: Left or Right */
	
#ifdef	ADC_CTU_INIT
	mADC_CTU_En_Set(ADC1, ENABLE);
#else
	mADC_CTU_En_Set(ADC1, DISABLE);
#endif
	ADC_PDEDR(ADC1) &= (~ADC_PDEDR_PDED_MASK);
	ADC_PDEDR(ADC1) |= ((ADC1_PDEDR_DELAY & 0xFF)<<0);	/* Delay between power-down reset and conversion */
	
	/* ADC Interrupt Configuration */
#ifdef	ADC1_IMR_ENABLED
	mADC_Intc_En(ADC1, ADC_EOCTU);						/* End of CTU conversion (EOCTU) interrupt */
	mADC_Intc_En(ADC1, ADC_JEOC);						/* End of injected channel conversion (JEOC) interrupt */
	mADC_Intc_En(ADC1, ADC_JECH);						/* End of injected chain conversion (JECH) interrupt */
	mADC_Intc_En(ADC1, ADC_EOC);						/* End of channel conversion (EOC) interrupt */
	mADC_Intc_En(ADC1, ADC_ECH);						/* End of chain conversion (ECH) interrupt */
#endif

	/* ADC1 Channel Configuration */	
#ifdef	ADC1_CH0_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH0);
#endif
#ifdef	ADC1_CH1_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH1);
#endif
#ifdef	ADC1_CH2_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH2);
#endif
#ifdef	ADC1_CH3_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH3);
#endif
#ifdef	ADC1_CH4_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH4);
#endif
#ifdef	ADC1_CH5_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH5);
#endif
#ifdef	ADC1_CH6_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH6);
#endif
#ifdef	ADC1_CH7_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH7);
#endif
#ifdef	ADC1_CH8_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH8);
#endif
#ifdef	ADC1_CH9_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH9);
#endif
#ifdef	ADC1_CH10_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH10);
#endif
#ifdef	ADC1_CH11_PIN
	mADC_Normal_Chan_En(ADC1, ADC_CH11);
#endif
#ifdef	ADC1_CH12_PIN	
	mADC_Normal_Chan_En(ADC1, ADC_CH12);
#endif
#ifdef	ADC1_CH13_PIN	
	mADC_Normal_Chan_En(ADC1, ADC_CH13);
#endif
#ifdef	ADC1_CH14_PIN	
	mADC_Normal_Chan_En(ADC1, ADC_CH14);
#endif
	
	/* Injected Conversion Enabled */
#ifdef	ADC1_JCMR_ENABLED
	#ifdef	ADC1_CH0_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH0);
	#endif
	#ifdef	ADC1_CH1_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH1);
	#endif
	#ifdef	ADC1_CH2_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH2);
	#endif
	#ifdef	ADC1_CH3_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH3);
	#endif
	#ifdef	ADC1_CH4_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH4);
	#endif
	#ifdef	ADC1_CH5_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH5);
	#endif
	#ifdef	ADC1_CH6_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH6);
	#endif
	#ifdef	ADC1_CH7_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH7);
	#endif
	#ifdef	ADC1_CH8_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH8);
	#endif
	#ifdef	ADC1_CH9_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH9);
	#endif
	#ifdef	ADC1_CH10_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH10);
	#endif
	#ifdef	ADC1_CH11_PIN
		mADC_Inject_Chan_En(ADC1, ADC_CH11);
	#endif
	#ifdef	ADC1_CH12_PIN	
		mADC_Inject_Chan_En(ADC1, ADC_CH12);
	#endif
	#ifdef	ADC1_CH13_PIN	
		mADC_Inject_Chan_En(ADC1, ADC_CH13);
	#endif
	#ifdef	ADC1_CH14_PIN	
		mADC_Inject_Chan_En(ADC1, ADC_CH14);
	#endif
#endif	

	/* SIU Channel Conifg */
#ifdef	ADC1_CH0_PIN
	SIU.PCR[ADC1_CH0_PIN].R   = ADC_PCR;		/* AN1_0 */
#endif
#ifdef	ADC1_CH1_PIN
	SIU.PCR[ADC1_CH1_PIN].R   = ADC_PCR;		/* AN1_1 */
#endif
#ifdef	ADC1_CH2_PIN
	SIU.PCR[ADC1_CH2_PIN].R   = ADC_PCR;		/* AN1_2 */
#endif
#ifdef	ADC1_CH3_PIN
	SIU.PCR[ADC1_CH3_PIN].R   = ADC_PCR;		/* AN1_3 */
#endif
#ifdef	ADC1_CH4_PIN
	SIU.PCR[ADC1_CH4_PIN].R   = ADC_PCR;		/* AN1_4 */
#endif
#ifdef	ADC1_CH5_PIN
	SIU.PCR[ADC1_CH5_PIN].R   = ADC_PCR;		/* AN1_5 */
#endif
#ifdef	ADC1_CH6_PIN
	SIU.PCR[ADC1_CH6_PIN].R   = ADC_PCR;		/* AN1_6 */
#endif
#ifdef	ADC1_CH7_PIN
	SIU.PCR[ADC1_CH7_PIN].R   = ADC_PCR;		/* AN1_7 */
#endif
#ifdef	ADC1_CH8_PIN
	SIU.PCR[ADC1_CH8_PIN].R   = ADC_PCR;		/* AN1_8 */
#endif
#ifdef	ADC1_CH9_PIN
	SIU.PCR[ADC1_CH9_PIN].R   = ADC_PCR;		/* AN1_9 */
#endif
#ifdef	ADC1_CH10_PIN
	SIU.PCR[ADC1_CH10_PIN].R  = ADC_PCR;		/* AN1_10 */
#endif
#ifdef	ADC1_CH11_PIN
	SIU.PCR[ADC1_CH11_PIN].R  = ADC_PCR;		/* AN1_11 */
#endif
#ifdef	ADC1_CH12_PIN	
	SIU.PCR[ADC1_CH12_PIN].R  = ADC_PCR;		/* AN1_12 */
#endif
#ifdef	ADC1_CH13_PIN	
	SIU.PCR[ADC1_CH13_PIN].R  = ADC_PCR;		/* AN1_13 */
#endif
#ifdef	ADC1_CH14_PIN	
	SIU.PCR[ADC1_CH14_PIN].R  = ADC_PCR;		/* AN1_14 */
#endif

	/* ADC1 Threshold Enabled */
#ifdef	ADC1_THRESH_ENABLED
	mADC_Thrsh_En_Set(ADC1, ADC_THR0, DISABLE);
	mADC_Thrsh_En_Set(ADC1, ADC_THR1, DISABLE);
	mADC_Thrsh_En_Set(ADC1, ADC_THR2, DISABLE);
	mADC_Thrsh_En_Set(ADC1, ADC_THR3, DISABLE);
	mADC_Thrsh_High_Set(ADC1, ADC_THR0, ADC1_THR0_HIGH);
	mADC_Thrsh_Low_Set(ADC1, ADC_THR0, ADC1_THR0_LOW);
	mADC_Thrsh_High_Set(ADC1, ADC_THR1, ADC1_THR1_HIGH);
	mADC_Thrsh_Low_Set(ADC1, ADC_THR1, ADC1_THR1_LOW);
	mADC_Thrsh_High_Set(ADC1, ADC_THR2, ADC1_THR2_HIGH);
	mADC_Thrsh_Low_Set(ADC1, ADC_THR2, ADC1_THR2_LOW);
	mADC_Thrsh_High_Set(ADC1, ADC_THR3, ADC1_THR3_HIGH);
	mADC_Thrsh_Low_Set(ADC1, ADC_THR3, ADC1_THR3_LOW);
#endif

	/* ADC Trigger Configuration */
	REG32_BIT_SET(ADC_MCR(ADC1), ADC_MCR_JTRGEN_MASK);	/* Ext Trig Enabled for Channel Injection */
	REG32_BIT_SET(ADC_MCR(ADC1), ADC_MCR_JEDGE_MASK);	/* Rising Edge for Ext Trig */

	/* DMA Setup Function(s) */
#ifdef ADC1_DMA_ENABLED
	ADC_DMAE(ADC1) &= (~ADC_DMAE_DCLR_MASK);
	ADC_DMAE(ADC1) |= ((ADC1_DMA_CLR_SEQ_EN & 0x01)<<1);
	ADC_DMAE(ADC1) &= (~ADC_DMAE_DMAEN_MASK);
	ADC_DMAE(ADC1) |= ((ADC1_DMA_EN & 0x01)<<0);

	#ifdef	ADC1_CH0_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH0);
	#endif
	#ifdef	ADC1_CH1_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH1);
	#endif
	#ifdef	ADC1_CH2_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH2);
	#endif
	#ifdef	ADC1_CH3_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH3);
	#endif
	#ifdef	ADC1_CH4_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH4);
	#endif
	#ifdef	ADC1_CH5_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH5);
	#endif
	#ifdef	ADC1_CH6_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH6);
	#endif
	#ifdef	ADC1_CH7_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH7);
	#endif
	#ifdef	ADC1_CH8_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH8);
	#endif
	#ifdef	ADC1_CH9_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH9);
	#endif
	#ifdef	ADC1_CH10_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH10);
	#endif
	#ifdef	ADC1_CH11_PIN
		mADC_DMA_Chan_En(ADC1, ADC_CH11);
	#endif
	#ifdef	ADC1_CH12_PIN	
		mADC_DMA_Chan_En(ADC1, ADC_CH12);
	#endif
	#ifdef	ADC1_CH13_PIN	
		mADC_DMA_Chan_En(ADC1, ADC_CH13);
	#endif
	#ifdef	ADC1_CH14_PIN	
		mADC_DMA_Chan_En(ADC1, ADC_CH14);
	#endif
#endif

	/* ADC1 Exit Abort */
	REG32_BIT_CLEAR(ADC_MCR(ADC1), ADC_MCR_ABORT_MASK);	/* Conversion no affected */
}


/* *****************************************************************************
   Function:        mADC0_ValGet
   Description:     Get ADC0 Channel's Value
   Parameters:      Input:		ChanNum:   ADC0 Channel Index
   								*ValAddr:  ADC0 Channel's Value
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
uint8	mADC0_ValGet(uint8 ChanNum, uint16 *ValAddr)
{
	uint8	StateRet;

	StateRet = FALSE;
	if(ChanNum <= ADC_CH15)
	{
		StateRet = OverTimeCheckLong(ADC_CDR_P(ADC0, ChanNum), ADC_CDR_VALID_MASK, ADC_CDR_VALID_MASK, TIMEOUT_ADC);
		if(StateRet)
		{
			*ValAddr = (uint16)(ADC_CDR(ADC0, ChanNum) & ADC0_CDR_CDATA_MASK);
		}
		else
		{
			*ValAddr = 0;
		}		
	}
	else
	{
		/* do nothing */
	}

	return(StateRet);
}


/* *****************************************************************************
   Function:        mADC1_ValGet
   Description:     Get ADC1 Channel's Value
   Parameters:      Input:		ChanNum:   ADC1 Channel Index
   								*ValAddr:  ADC1 Channel's Value
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
uint8	mADC1_ValGet(uint8 ChanNum, uint16 *ValAddr)
{
	uint8	StateRet;
	
	StateRet = FALSE;
	if(ChanNum <= ADC_CH15)
	{
		StateRet = OverTimeCheckLong(ADC_CDR_P(ADC1, ChanNum), ADC_CDR_VALID_MASK, ADC_CDR_VALID_MASK, TIMEOUT_ADC);
		
		if(StateRet)
		{
			*ValAddr = (uint16)(ADC_CDR(ADC1, ChanNum) & ADC1_CDR_CDATA_MASK);
		}
		else
		{
			*ValAddr = 0;
		}		
	}
	else
	{
		/* do nothing */
	}

	return(StateRet);
}


/* *****************************************************************************
   Function:        mADC_Oneshot_ValGet
   Description:     Get ADC Channel's Value once in OneShot Mode
   Parameters:      Input:		ModuleNum: ADC module Index
   								ChanNum:   ADC Channel Index
   								*ValAddr:  ADC Channel's Value
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
uint8	mADC_Oneshot_ValGet(uint8 ModuleNum, uint8 ChanNum, uint16 *ValAddr)
{
	uint8	StateRet;
	
	StateRet = FALSE;
	if(ChanNum <= ADC_CH15 && ModuleNum<= ADC1)
	{
		mADC_Normal_Start(ModuleNum);
		StateRet = OverTimeCheckLong(ADC_CDR_P(ModuleNum, ChanNum), ADC_CDR_VALID_MASK, ADC_CDR_VALID_MASK, TIMEOUT_ADC);
		
		if(StateRet)
		{
			*ValAddr = (uint16)(ADC_CDR(ModuleNum, ChanNum) & ADC1_CDR_CDATA_MASK);
			mADC_Normal_Stop(ModuleNum);
		}
		else
		{
			*ValAddr = 0;
		}		
	}
	else
	{
		/* do nothing */
	}
	
	return(StateRet);
}





/* End of file */