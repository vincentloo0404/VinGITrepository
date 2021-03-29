/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_Clock_Drv.c
*
* @brief    Clock Module function, clock Init and config.
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2016/09/23     Jerry     		N/A          Original
*******************************************************************************/
#ifndef	M_CLOCK_DRV_C
#define M_CLOCK_DRV_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_Clock_Drv.h"
#include 	"m_Clock_Cfg.h"

/*---------------------------------------------------------------------------*/
/***	ME_PCTL	for " ME.PCTL[PCTL_ADC0].R = 0x00; "                       ***/
/*---------------------------------------------------------------------------*/
#define		PCTL_PIT			92
#define		PCTL_ADC0			32
#define		PCTL_ADC1			33

/* *****************************************************************************
   Function:        mSysClk_Sel
   Description:     Select System Clock source
   Parameters:      Input:
                    Output:   
                    	success or fail
   Notes:           Only RUN0 mode now , other modes later
                   
   ***************************************************************************** */
uint8	mSysClk_Sel(void)
{
	uint8	retVal = E_NOT_OK;
	uint32	TimeOutCnt = 0;
	
	/* Initialize Mode Entries */
	ME.MER.R = 0x0000001D;                	/* Enable DRUN, RUN0, SAFE, RESET Modes */

	/* Set CMU_0_CSR :	Monitor FXOSC > FIRC / 4 (4MHz); No PLL Monitor */
	CGM.CMU_0_CSR.B.RCDIV = ClkOut_Div_4;

	/* Set CMU_1_CSR : */
	CGM.CMU_1_CSR.B.CME_A = DISABLE;

	/* RUN0 Config	(enum_Sys_Clk eSel, uint8 Pll2_Flag, uint8 Pll1_Flag, uint8 Xosc_Flag) */
	CGM.FMPLL[0].CR.B.IDF  = 0;
	CGM.FMPLL[0].CR.B.ODF  = 2;
	CGM.FMPLL[0].CR.B.NDIV = 64;
	
	CGM.FMPLL[0].CR.B.EN_PLL_SW = ENABLE;		
	
	ME.RUN[0].R   = 0x001F00F0;				/* IRC XOSC, PLL0, PLL1 all Enable */
	ME.RUN[0].B.SYSCLK   = Sys_Clk_PLL0;	/* CGM_SC_SS ReadOnly to checkout */
	ME.RUNPC[0].R = 0x00000010;           	/* Peripheral Configuration 0 Settings: Only Run In RUN0 Mode */
	
	/* added 2012-05-28 for Timer */
	ME.PCTL[PCTL_PIT].R = 0x00;                 /* PIT, RTI: select ME_RUN_PC[0] */
	
	/* added 2012-06-05 for ADC */
	ME.PCTL[PCTL_ADC0].R = 0x00;                 /* ADC 1: Select ME.RUNPC[0] */
	ME.PCTL[PCTL_ADC1].R = 0x00;                 /* ADC 1: Select ME.RUNPC[0] */
	
	/* Mode Transition To Enter RUN0 Mode: */
	ME.MCTL.R = ME_CTRL_KEY;               	/* Enter RUN0 Mode & Key */
	ME.MCTL.R = ME_CTRL_KEY_INVERT;        	/* Enter RUN0 Mode & INVERTED Key */
	
	/* TimeOut Check for Dead While Loop */
	retVal = E_OK;
	while(ME.GS.B.S_MTRANS != 0)            	/* Wait For Mode Transition To Complete */
	{
		TimeOutCnt++;
		if(TimeOutCnt > ME_TRAN_TIME_OUT)
		{
			retVal = E_NOT_OK;
			break;
		}
		else
		{ }
	}
	
	
	if(retVal == E_OK)						
	{
		/* TimeOut Check for Dead While Loop */
		TimeOutCnt = 0;
		while(ME.GS.B.S_CURRENTMODE != Mode_Run0)  		/* Verify RUN0 Is The Current Mode */
		{
			TimeOutCnt++;
			if(TimeOutCnt > ME_CURR_MODE_TIME_OUT)
			{
				retVal = E_NOT_OK;
				break;
			}
			else
			{ }
		}
	}
	else
	{
		/* do nothing */
	}
	
	return(retVal);
}
/* *****************************************************************************
   Function:        mMcClk_Sel
   Description:     Select MC Clock Source, 120MHz
   Parameters:      Input:	
                    Output:   
                    	success or fail
   Notes:           Ref Page135 Fig, instead of Reg Desc
   ***************************************************************************** */
uint8	mMcClk_Sel(void)
{
	CGM.FMPLL[1].CR.B.IDF  = 0;
	CGM.FMPLL[1].CR.B.ODF  = 1;
	CGM.FMPLL[1].CR.B.NDIV = 60;	
	
	CGM.FMPLL[1].CR.B.EN_PLL_SW = ENABLE;	
	
	CGM.AC0SC.B.SELCTL = Aux_Clk_PLL1_120M;
	
	/* Config eDiv */
	CGM.AC0DC.B.DIV0 = 0;
	
	/* Enable Div && Output */
	CGM.AC0DC.B.DE0 = ENABLE;
	
	return(E_OK);
}
/* End of file */