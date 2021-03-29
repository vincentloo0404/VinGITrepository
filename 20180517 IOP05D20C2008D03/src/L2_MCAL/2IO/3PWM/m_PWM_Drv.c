/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_PWM_Drv.c
*
* @brief    PWM module Function, All Sub Init, Duty Update and INTC_ISR
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/06/11      Lwt          	N/A          Original
*******************************************************************************/

#ifndef M_PWM_DRV_C
#define M_PWM_DRV_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_PWM_Drv.h"
#include 	"m_PWM_Cfg.h"
#include 	"m_PWM_Drv_InitVal.h"
#include    "SysConfig.h"


#define		PWM_SUB3_CAPTX_EN

/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mPWM_Sub_Start
   Description:     Load PRSC, INIT, VALx,  Start running and PWM parameter 
   					take effect at next PWM reload
   Parameters:      Input:    PWM_SUB_0, PWM_SUB_1, PWM_SUB_2, PWM_SUB_3 
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mPWM_Sub_Start(uint8 SubIndex)
{
	PWM_MCTRL |= 1<<(SubIndex + PWM_MCTRL_RUN_OFFSET);		/* Run enabled */
	PWM_MCTRL |= 1<<(SubIndex + PWM_MCTRL_LDOK_OFFSET);		/* Load New Sub Value */
}


/* *****************************************************************************
   Function:        mPWM_Sub_Stop
   Description:     Stop running PWM
   Parameters:      Input:    PWM_SUB_0, PWM_SUB_1, PWM_SUB_2, PWM_SUB_3 
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mPWM_Sub_Stop(uint8 SubIndex)
{
	PWM_MCTRL &= ~(1<<(SubIndex + PWM_MCTRL_RUN_OFFSET));	/* Run disabled */

}


/* *****************************************************************************
   Function:        mPWM_Sub_All_Stop
   Description:     Stop running All PWM Sub (Used)
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mPWM_Sub_All_Stop(void)
{
	//PWM_MCTRL &= ~PWM_MCTRL_RUN_MASK;
//	REG16_BIT_SET(PWM_FSTS, 0xFF0F);
	PWM_FSTS = 0xFF0F;
}


/* *****************************************************************************
   Function:        mPWM_Sub_All_Start
   Description:     Start running All PWM Sub (Used)
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mPWM_Sub_All_Start(void)
{
	PWM_MCTRL |= PWM_SUB_LOAD << PWM_MCTRL_RUN_OFFSET;		/* Run enabled All Sub */
	PWM_MCTRL |= PWM_SUB_LOAD << PWM_MCTRL_LDOK_OFFSET;		/* Load New Sub Value */
}




void	mPWM_Sub_OVP_OCP_PWM_Start(void)
{
		mPWM_Sub_Start(PWM_SUB_3);
}


void	mPWM_Sub_AB_PWM_Stop(void)
{
		mPWM_Sub_Stop(PWM_SUB_0);
}

void	mPWM_Sub_CD_PWM_Stop(void)
{
		mPWM_Sub_Stop(PWM_SUB_1);
}




void	mPWM_Sub_ABCD_PWM_Start(void)
{
		PWM_MCTRL |= PWM_ABCD_SUB_LOAD << PWM_MCTRL_RUN_OFFSET;		/* Run enabled ABCD Sub */
		PWM_MCTRL |= PWM_ABCD_SUB_LOAD << PWM_MCTRL_LDOK_OFFSET;		/* Load New Sub Value */
}


/* *****************************************************************************
   Function:        mPWM_General_Config
   Description:     Set Congfigurtiion such as Enable Sub ,Load PRSC, INIT, VALx
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mPWM_General_Config(void)
{
	/* PWM A B Output Enabled */
	PWM_OUTEN = PWM_OUT_EN;

	/* PWM MASK */
#ifdef 	PWM_MASK_VAL
	PWM_MASK = PWM_MASK_VAL;
#endif

	/* PWM DeadTime */
#ifdef	PWM_DEADTIME
	PWM_SWCOUT = PWM_SOFT_CTRL_OUT;
	PWM_DTSRCSEL = PWM_DEADTIME_SRC;	
#endif
	
	/* PWM Fault Input */
#ifdef	PWM_FAULT
	REG16_BIT_SET(PWM_FSTS, 0xF);
	PWM_FCTRL = 0xF0FF;
	PWM_FFILT = 0x0000;
#endif


#ifdef	PWM_FAULT_0_EN

	//REG16_BIT_SET(PWM_FSTS, 0xF);
	PWM_FSTS = 0xFF0F;
	//REG16_BIT_SET(PWM_FSTS, 0xFF0F);
	//PWM_FCTRL = 0xF0FF;
	//PWM_FCTRL = 0x1011;
	//PWM_FCTRL = 0x0011;
	//PWM_FCTRL = 0xe011;
	PWM_FCTRL = 0x0000;
	
	//PWM_FCTRL = 0x0101;//FRANK
	//PWM_FCTRL = 0x0101;
	PWM_FFILT = 0x0000;
	
#endif	
	
	/* PWM Independent Mode Ignord */
	/* FLEXPWM_0.MCTRL.B.IPOL= 0x9; */
	
	/* PWM Load Prescaler, Modulus, Values */
	PWM_MCTRL = PWM_SUB_LOAD;	/* Module 0,1,2,3 */
}


/* *****************************************************************************
   Function:        mPWM_CaptX_Start
   Description:     Start SUB's PWMX capture function
   Parameters:      Input:    PWM_SUB_0, PWM_SUB_1, PWM_SUB_2, PWM_SUB_3 
                    Output:   None
   Notes:    
              
   ***************************************************************************** */
void	mPWM_CaptX_Stop(uint8 SubIndex)
{
	PWM_CAPTCTRLX(SubIndex) &= ~(PWM_CAPTCTRLX_ARM_MASK);
}


/* *****************************************************************************
   Function:        mPWM_CaptX_Start
   Description:     Start SUB's PWMX capture function
   Parameters:      Input:    PWM_SUB_0, PWM_SUB_1, PWM_SUB_2, PWM_SUB_3 
                    Output:   None
   Notes:    
              
   ***************************************************************************** */
void	mPWM_CaptX_Start(uint8 SubIndex)
{
	PWM_CAPTCTRLX(SubIndex) |= PWM_CAPTCTRLX_ARM_MASK;
}

/* *****************************************************************************
   Function:        mPWM_Sub_0_Init
   Description:     Sub0 Init, such as PCR, CTRLx, INIT, VALx, then enable Sub
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mPWM_Sub_0_Init(void)
{
#ifdef	PWM_SUB_0_OUT_EN
	/* GPIO Pin Config */ 
	SIU.PCR[PWM_SUB_0_A_PIN].R  = PWM_SUB_0_PCR;
	SIU.PCR[PWM_SUB_0_B_PIN].R  = PWM_SUB_0_PCR;
	SIU.PSMI[PWM_0_A_PSMI].R	= PWM_0_A_PSMI_VAL;
	SIU.PSMI[PWM_0_B_PSMI].R	= PWM_0_B_PSMI_VAL;
	
	#ifdef	PWM_SUB0_CAPTX_EN
		SIU.PCR[PWM_SUB_0_X_PIN].R  = PWM_SUB_0_X_PCR;
	#endif	
	
	#ifdef	PWM_FAULT_0_EN
	
		SIU.PCR[PWM_FAULT_0_PIN].R  = PCR_PIN_IN;
		SIU.PSMI[PWM_FAULT0_PSMI].R	= PWM_FAULT0_PSMI_VAL;
	#endif	
	
	
	

	/* PWM Control 1 Reg */ 
#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN
	REG16_BIT_SET(PWM_CTRL1(0), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Enabled */
	REG16_BIT_CLEAR(PWM_CTRL1(0), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Disabled */
	//REG16_BIT_CLEAR(PWM_CTRL1(0), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Disabled */
	//REG16_BIT_SET(PWM_CTRL1(0), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Enabled */
#else
	REG16_BIT_SET(PWM_CTRL1(0), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Enabled */
	REG16_BIT_CLEAR(PWM_CTRL1(0), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Disabled */
#endif	
	REG16_BIT_CLEAR(PWM_CTRL1(0), PWM_CTRL1_DBLEN_MASK);	/* Double Switching Disabled */
	REG16_BIT_CLEAR(PWM_CTRL1(0), PWM_CTRL1_PRSC_MASK);
	REG16_BIT_SET(PWM_CTRL1(0), (PWM_PRSC_SUB_0<<4) );		/* PreScaler = 2 ^ PRSC, PWM Clock = fclk / PreScaler; */
	REG16_BIT_CLEAR(PWM_CTRL1(0), PWM_CTRL1_LDFQ_MASK);
	REG16_BIT_SET(PWM_CTRL1(0), (LOAD_EVERY_2<<12) );		/* PWM Reload Frequency Every n PWM Opportunity */

    /* PWM Control 2 Reg */
#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN
    REG16_BIT_SET(PWM_CTRL2(0), PWM_CTRL2_INDEP_MASK);		/* PWMA & PWMB Outputs Independent, 0,complementary; 1,independent.  */
	PWM_OCTRL(0) = 0;
#else
	REG16_BIT_CLEAR(PWM_CTRL2(0), PWM_CTRL2_INDEP_MASK);
	//PWM_OCTRL(0) = PWM_OCTRL_POLA_MASK;						/* PWM Output Control Reg */
	PWM_OCTRL(0) = 0;						/* PWM Output Control Reg */
#endif

	REG16_BIT_SET(PWM_CTRL2(0), PWM_CTRL2_DBGEN_MASK);		/* PWM Runs In DeBug Mode, 1,run while in debug */

	/* PWM INIT and VALx */
	PWM_INIT(0) = SUB_0_INIT_INIT;							/* PWM Init Count clock */
	PWM_VAL0(0) = SUB_0_VAL0_INIT;							/* Mid Cycle Reload Point */
	PWM_VAL1(0) = SUB_0_VAL1_INIT;							/* Max Count */

#if 0	
	PWM_VAL2(0) = SUB_0_VAL2_INIT;							/* PWMA High Value */
	PWM_VAL3(0) = SUB_0_VAL3_INIT;							/* PWMA Low  Value */
	PWM_VAL4(0) = SUB_0_VAL4_INIT;							/* PWMB High Value */
	PWM_VAL5(0) = SUB_0_VAL5_INIT;							/* PWMB Low  Value */
#endif
/*
#if 0
	PWM_VAL2(0) = SUB_0_INIT_INIT;							// PWMA High Value 
	PWM_VAL3(0) = SUB_0_VAL0_INIT;							// PWMA Low  Value 
	PWM_VAL4(0) = SUB_0_INIT_INIT;							// PWMB High Value 
	PWM_VAL5(0) = SUB_0_VAL0_INIT;							// PWMB Low  Value 
#endif

#if 1
	PWM_VAL2(0) = SUB_0_VAL0_INIT;							// PWMA High Value 
	PWM_VAL3(0) = SUB_0_VAL1_INIT;							// PWMA Low  Value 
	PWM_VAL4(0) = SUB_0_VAL0_INIT;							// PWMB High Value 
	PWM_VAL5(0) = SUB_0_VAL1_INIT;							// PWMB Low  Value 	
#endif
*/
#ifdef AB_before_CD


	PWM_VAL2(0) = SUB_0_VAL0_INIT;							// PWMA High Value 
	PWM_VAL3(0) = SUB_0_VAL1_INIT;							// PWMA Low  Value 
	PWM_VAL4(0) = SUB_0_VAL0_INIT;							// PWMB High Value 
	PWM_VAL5(0) = SUB_0_VAL1_INIT;							// PWMB Low  Value 	

		
#else	
	
	//PWM_VAL2(0) = SUB_0_INIT_INIT;							// PWMA High Value 
	//PWM_VAL3(0) = SUB_0_VAL0_INIT;							// PWMA Low  Value 
	//PWM_VAL4(0) = SUB_0_INIT_INIT;							// PWMB High Value 
	//PWM_VAL5(0) = SUB_0_VAL0_INIT;							// PWMB Low  Value 
	

	PWM_VAL2(0) = 0;//modify by ych 20170313
	PWM_VAL3(0) = 600;
	PWM_VAL4(0) = SUB_0_INIT_INIT;							// PWMB High Value 
	PWM_VAL5(0) = SUB_0_VAL0_INIT;							// PWMB Low  Value 
		
#endif




	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53 */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period  */
	#ifdef	PWM_SUB_0_DEADTIME_EN
		PWM_DISMAP(0) = DISMAP_VALUE;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(0) = SUB_0_DTCNT0_INIT;					/* PWMA Dead Time */
		PWM_DTCNT1(0) = SUB_0_DTCNT1_INIT;					/* PWMB Dead Time */
	#else
		PWM_DISMAP(0) = DISMAP_VALUE;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(0) = 0x0000;								/* PWMA Dead Time */
		PWM_DTCNT1(0) = 0x0000;								/* PWMB Dead Time */
	#endif
	
	
	PWM_TCTRL(0) = 0x0;										/* OUT_TRIGx not used */

	#ifdef	PWM_INTC_EN
	    PWM_INTEN(0) = PWM_SUB0_INTEN_VALUE;				/* intc source: Reload & Reload Error */
	#endif

	#ifdef	PWM_DMA
	    PWM_DMAEN(0) = PWM_DMAEN_VALUE;
	#endif
    
	#ifdef	PWM_CAPTURE
		PWM_CAPTCTRLX(0) = 0x0;
		PWM_CAPTCOMPX(0) = 0x0;
	#endif

	#ifdef	PWM_SUB0_CAPTX_EN
		PWM_CAPTCTRLX(0) = PWM_0_CAPCTRLX_VAL;
		PWM_CVAL0(0) = 0x0;
		PWM_CVAL1(0) = 0x0;
		mPWM_CaptX_Start(0);
	#endif
	
	/* Enable PWMA & PWMB Output */
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_0+PWM_OUTEN_PWMA_OFFSET) ) );
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_0+PWM_OUTEN_PWMB_OFFSET) ) );		
#endif
}

/* *****************************************************************************
   Function:        mPWM_Sub_0_A_Updata_Duty
   Description:     update SUB_0_A duty
   Parameters:      Input:    pwm_A_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_0_AB_Advance(uint16 Ct,sint16 Ct1)
{
	PWM_VAL2(0) = 0 - Ct;
	PWM_VAL3(0) = (uint16)((sint16)(600-Ct)+ Ct1);
	/* Load New Sub Module 0 Values */
	REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_0 + PWM_MCTRL_LDOK_OFFSET) ) );
	
	return(TRUE);
}


/* *****************************************************************************
   Function:        mPWM_Sub_0_A_Updata_Duty
   Description:     update SUB_0_A duty
   Parameters:      Input:    pwm_A_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_1_CD_Advance(uint16 Ct,sint16 Ct1)
{
	PWM_VAL2(1) = 0 - Ct;
	PWM_VAL3(1) = (uint16)((sint16)(600-Ct) + Ct1);
	/* Load New Sub Module 0 Values */
	REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_1 + PWM_MCTRL_LDOK_OFFSET) ) );
	
	return(TRUE);
}


uint8	mPWM_offset_Advance(uint16 Ct,sint16 Ct1)
{
	
	#ifdef AB_before_CD
		mPWM_Sub_1_CD_Advance(Ct,Ct1);
	#else
		mPWM_Sub_0_AB_Advance(Ct,Ct1);
	#endif
	return(TRUE);
}



uint8	mPWM_Sub_0_AB_Advance_pianci(uint16 Ct,sint16 Ct1,uint8 k_pianCiCnt_u08)
{
	PWM_VAL2(0) = 0 - Ct;
	if(5<k_pianCiCnt_u08 && k_pianCiCnt_u08 <= 0)
	{
		k_pianCiCnt_u08 = 0;
	}
	PWM_VAL3(0) = (uint16)((sint16)(600-Ct) +k_pianCiCnt_u08+ Ct1);
	/* Load New Sub Module 0 Values */
	REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_0 + PWM_MCTRL_LDOK_OFFSET) ) );
	
	return(TRUE);
}

/* *****************************************************************************
   Function:        mPWM_Sub_0_A_Updata_Duty
   Description:     update SUB_0_A duty
   Parameters:      Input:    pwm_A_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_0_A_Updata_Duty(uint16 pwm_A_Duty)
{
#ifdef	PWM_SUB_0_OUT_EN
	uint8	RetValue;
	uint16	pwm_A_Width_Val3;
	
	RetValue = FALSE;
	/* translate pwm_A_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(pwm_A_Duty * SUB_0_VAL1_INIT)>>15);
	
	if(SUB_0_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(0) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(0) = pwm_A_Width_Val3;
		/* Load New Sub Module 0 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_0 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;	
	}
	else
	{
	}
	
	return(RetValue);
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_0_B_Updata_Duty
   Description:     update SUB_0_B duty
   Parameters:      Input:    pwm_B_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_0_B_Updata_Duty(uint16 pwm_B_Duty)
{
#ifdef	PWM_SUB_0_OUT_EN
	uint8	RetValue;
	uint16	pwm_B_Width_Val5;
	
	RetValue = FALSE;
	/* translate pwm_B_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_B_Width_Val5 = (uint16)((uint32)(pwm_B_Duty * SUB_0_VAL1_INIT)>>15);
	
	if(SUB_0_VAL1_INIT >= pwm_B_Width_Val5)
	{
		PWM_VAL4(0) = 0xFFFF - pwm_B_Width_Val5 + 1;
		PWM_VAL5(0) = pwm_B_Width_Val5;
		/* Load New Sub Module 0 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_0 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;	
	}
	else
	{
	}
	
	return(RetValue);
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_1_Init
   Description:     Sub1 Init, such as PCR, CTRLx, INIT, VALx, then enable Sub
   Parameters:      Input:    None
                    Output:   None
   Notes:           

   ***************************************************************************** */
static	void	mPWM_Sub_1_Init(void)
{
#ifdef	PWM_SUB_1_OUT_EN
	/* GPIO Pin Config */ 
	SIU.PCR[PWM_SUB_1_A_PIN].R  = PWM_SUB_1_PCR;
	SIU.PCR[PWM_SUB_1_B_PIN].R  = PWM_SUB_1_PCR;
	SIU.PSMI[PWM_1_A_PSMI].R	= PWM_1_A_PSMI_VAL;
	SIU.PSMI[PWM_1_B_PSMI].R	= PWM_1_B_PSMI_VAL;
	
	#ifdef	PWM_SUB1_CAPTX_EN
		SIU.PCR[PWM_SUB_1_X_PIN].R  = PWM_SUB_1_X_PCR;
		SIU.PSMI[PWM_1_X_PSMI].R	= PWM_1_X_PSMI_VAL;
	#endif

	/* PWM Control 1 Reg */
#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN

	REG16_BIT_SET(PWM_CTRL1(1), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Enabled */
	REG16_BIT_CLEAR(PWM_CTRL1(1), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Disabled */
	/*
	REG16_BIT_CLEAR(PWM_CTRL1(1), PWM_CTRL1_FULL_MASK);		// Full Cycle ReLoad Disabled 
	REG16_BIT_SET(PWM_CTRL1(1), PWM_CTRL1_HALF_MASK);		// Half-Cycle Reload Enabled 
	*/
#else
	REG16_BIT_SET(PWM_CTRL1(1), PWM_CTRL1_FULL_MASK);		// Full Cycle ReLoad Enabled /
	REG16_BIT_CLEAR(PWM_CTRL1(1), PWM_CTRL1_HALF_MASK);		// Half-Cycle Reload Disabled /
#endif
	REG16_BIT_CLEAR(PWM_CTRL1(1), PWM_CTRL1_DBLEN_MASK);	/* Double Switching Disabled */
	REG16_BIT_CLEAR(PWM_CTRL1(1), PWM_CTRL1_PRSC_MASK);
	REG16_BIT_SET(PWM_CTRL1(1), (PWM_PRSC_SUB_1<<4) );		/* PreScaler = 2 ^ PRSC, PWM Clock = fclk / PreScaler; */
	REG16_BIT_CLEAR(PWM_CTRL1(1), PWM_CTRL1_LDFQ_MASK);
	REG16_BIT_SET(PWM_CTRL1(1), (LOAD_EVERY_2<<12) );		/* PWM Reload Frequency Every n PWM Opportunity */

    /* PWM Control 2 Reg */
#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN
    REG16_BIT_SET(PWM_CTRL2(1), PWM_CTRL2_INDEP_MASK);		/* PWMA & PWMB Outputs Independent, 0,complementary; 1,independent. */ 
	PWM_OCTRL(1) = 0;
#else
	REG16_BIT_CLEAR(PWM_CTRL2(1), PWM_CTRL2_INDEP_MASK);
	//PWM_OCTRL(1) = PWM_OCTRL_POLA_MASK;						/* PWM Output Control Reg */
	PWM_OCTRL(1) = 0;						/* PWM Output Control Reg */
#endif
	REG16_BIT_SET(PWM_CTRL2(1), PWM_CTRL2_DBGEN_MASK);		/* PWM Runs In DeBug Mode, 1,run while in debug */

	/* PWM INIT and VALx */
	PWM_INIT(1) = SUB_1_INIT_INIT;							/* PWM Init Count clock */
	PWM_VAL0(1) = SUB_1_VAL0_INIT;							/* Mid Cycle Reload Point */
	PWM_VAL1(1) = SUB_1_VAL1_INIT;							/* Max Count */

#if 0	
	PWM_VAL2(1) = SUB_1_VAL2_INIT;							/* PWMA High Value */
	PWM_VAL3(1) = SUB_1_VAL3_INIT;							/* PWMA Low  Value */
	PWM_VAL4(1) = SUB_1_VAL4_INIT;							/* PWMB High Value */
	PWM_VAL5(1) = SUB_1_VAL5_INIT;							/* PWMB Low  Value */
#endif

/*
#if 0
	PWM_VAL2(1) = SUB_0_VAL0_INIT;							// PWMA High Value 
	PWM_VAL3(1) = SUB_1_VAL1_INIT;							// PWMA Low  Value 
	PWM_VAL4(1) = SUB_0_VAL0_INIT;							// PWMB High Value 
	PWM_VAL5(1) = SUB_1_VAL1_INIT;							// PWMB Low  Value
#endif

#if 1
	//PWM_VAL2(1) = SUB_0_INIT_INIT;							// PWMA High Value 
	//PWM_VAL3(1) = SUB_0_VAL0_INIT;							// PWMA Low  Value
	PWM_VAL2(1) = 0;//modify by ych 20170304
	PWM_VAL3(1) = 600;

	PWM_VAL4(1) = SUB_0_INIT_INIT;							//PWMB High Value 
	PWM_VAL5(1) = SUB_0_VAL0_INIT;							//PWMB Low  Value 
#endif
*/


#ifdef AB_before_CD


	PWM_VAL2(1) = 0;//modify by ych 20170313
	PWM_VAL3(1) = 600;
	PWM_VAL4(1) = SUB_0_INIT_INIT;							/* PWMB High Value */
	PWM_VAL5(1) = SUB_0_VAL0_INIT;							/* PWMB Low  Value */
		
#else	
	
	PWM_VAL2(1) = SUB_0_VAL0_INIT;							// PWMA High Value 
	PWM_VAL3(1) = SUB_1_VAL1_INIT;							// PWMA Low  Value 
	PWM_VAL4(1) = SUB_0_VAL0_INIT;							// PWMB High Value 
	PWM_VAL5(1) = SUB_1_VAL1_INIT;							// PWMB Low  Value
#endif






	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53 */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period  */
	#ifdef	PWM_SUB_1_DEADTIME_EN
		PWM_DISMAP(1) = DISMAP_VALUE;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(1) = SUB_1_DTCNT0_INIT;					/* PWMA Dead Time */
		PWM_DTCNT1(1) = SUB_1_DTCNT1_INIT;					/* PWMB Dead Time */
	#else
		PWM_DISMAP(1) = DISMAP_VALUE;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(1) = 0x0000;								/* PWMA Dead Time */
		PWM_DTCNT1(1) = 0x0000;								/* PWMB Dead Time */
	#endif


	PWM_TCTRL(1) = 0x0;										/* OUT_TRIGx not used */

	#ifdef	PWM_INTC_EN
	    PWM_INTEN(1) = PWM_SUB1_INTEN_VALUE;				/* Intc source: Reload & Reload Error */
	#endif

	#ifdef	PWM_DMA
	    PWM_DMAEN(1) = PWM_DMAEN_VALUE;
	#endif

	#ifdef	PWM_CAPTURE
		PWM_CAPTCTRLX(1) = 0x0;
		PWM_CAPTCOMPX(1) = 0x0;
	#endif
	
	#ifdef	PWM_SUB1_CAPTX_EN
		PWM_CAPTCTRLX(1) = PWM_1_CAPCTRLX_VAL;
		PWM_CVAL0(1) = 0x0;
		PWM_CVAL1(1) = 0x0;
		mPWM_CaptX_Start(1);
	#endif

	/* Enable PWMA & PWMB Output */
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_1+PWM_OUTEN_PWMA_OFFSET) ) );
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_1+PWM_OUTEN_PWMB_OFFSET) ) );	
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_1_A_Updata_Duty
   Description:     update SUB_1_A duty
   Parameters:      Input:    pwm_A_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_1_A_Updata_Duty(uint16 pwm_A_Duty)
{
#ifdef	PWM_SUB_1_OUT_EN
	uint8	RetValue;
	uint16	pwm_A_Width_Val3;
	
	RetValue = FALSE;
	/* translate pwm_A_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(pwm_A_Duty * SUB_1_VAL1_INIT)>>15);
	
	if(SUB_1_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(1) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(1) = pwm_A_Width_Val3;
		/* Load New Sub Module 1 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_1 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;	
	}
	else
	{
	}
	
	return(RetValue);
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_1_B_Updata_Duty
   Description:     update SUB_1_B duty
   Parameters:      Input:    pwm_B_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_1_B_Updata_Duty(uint16 pwm_B_Duty)
{
#ifdef	PWM_SUB_1_OUT_EN
	uint8	RetValue;
	uint16	pwm_B_Width_Val5;
	
	RetValue = FALSE;
	/* translate pwm_B_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_B_Width_Val5 = (uint16)((uint32)(pwm_B_Duty * SUB_1_VAL1_INIT)>>15);
	
	if(SUB_1_VAL1_INIT >= pwm_B_Width_Val5)
	{
		PWM_VAL4(1) = 0xFFFF - pwm_B_Width_Val5 + 1;
		PWM_VAL5(1) = pwm_B_Width_Val5;
		/* Load New Sub Module 1 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_1 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;
	}
	else
	{
	}
	
	return(RetValue);
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_2_Init
   Description:     Sub2 Init, such as PCR, CTRLx, INIT, VALx, then enable Sub
   Parameters:      Input:    None
                    Output:   None
   Notes:           

   ***************************************************************************** */
static	void	mPWM_Sub_2_Init(void)
{
#ifdef	PWM_SUB_2_OUT_EN
	/* GPIO Pin Config */
	SIU.PCR[PWM_SUB_2_A_PIN].R  = PWM_SUB_2_PCR;
	SIU.PCR[PWM_SUB_2_B_PIN].R  = PWM_SUB_2_PCR;
	SIU.PSMI[PWM_2_A_PSMI].R	= PWM_2_A_PSMI_VAL;
	SIU.PSMI[PWM_2_B_PSMI].R	= PWM_2_B_PSMI_VAL;

	/* PWM Control 1 Reg */ 
#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN
	REG16_BIT_CLEAR(PWM_CTRL1(2), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Disabled */
	REG16_BIT_SET(PWM_CTRL1(2), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Enabled */
#else
	REG16_BIT_SET(PWM_CTRL1(2), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Enabled */
	REG16_BIT_CLEAR(PWM_CTRL1(2), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Disabled */
#endif
	REG16_BIT_CLEAR(PWM_CTRL1(2), PWM_CTRL1_DBLEN_MASK);	/* Double Switching Disabled */
	REG16_BIT_CLEAR(PWM_CTRL1(2), PWM_CTRL1_PRSC_MASK);
	REG16_BIT_SET(PWM_CTRL1(2), (PWM_PRSC_SUB_2<<4) );		/* PreScaler = 2 ^ PRSC, PWM Clock = fclk / PreScaler;  */
	REG16_BIT_CLEAR(PWM_CTRL1(2), PWM_CTRL1_LDFQ_MASK);
	REG16_BIT_SET(PWM_CTRL1(2), (LOAD_EVERY_2<<12) );		/* PWM Reload Frequency Every n PWM Opportunity */

    /* PWM Control 2 Reg */
#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN
    REG16_BIT_SET(PWM_CTRL2(2), PWM_CTRL2_INDEP_MASK);		/* PWMA & PWMB Outputs Independent, 0,complementary; 1,independent.  */
	PWM_OCTRL(2) = 0;
#else
	REG16_BIT_CLEAR(PWM_CTRL2(2), PWM_CTRL2_INDEP_MASK);
	PWM_OCTRL(2) = PWM_OCTRL_POLA_MASK;		/* PWM Output Control Reg */
#endif

	REG16_BIT_SET(PWM_CTRL2(2), PWM_CTRL2_DBGEN_MASK);		/* PWM Runs In DeBug Mode, 1,run while in debug */

	/* PWM INIT and VALx */
	PWM_INIT(2) = SUB_2_INIT_INIT;							/* PWM Init Count clock */
	PWM_VAL0(2) = SUB_2_VAL0_INIT;							/* Mid Cycle Reload Point */
	PWM_VAL1(2) = SUB_2_VAL1_INIT;							/* Max Count */
	
	PWM_VAL2(2) = SUB_2_VAL2_INIT;							/* PWMA High Value */
	PWM_VAL3(2) = SUB_2_VAL3_INIT;							/* PWMA Low  Value */
	PWM_VAL4(2) = SUB_2_VAL4_INIT;							/* PWMB High Value */
	PWM_VAL5(2) = SUB_2_VAL5_INIT;							/* PWMB Low  Value */

	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53 */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period  */
	#ifdef	PWM_SUB_2_DEADTIME_EN
		PWM_DISMAP(2) = 0xF000;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(2) = SUB_2_DTCNT0_INIT;					/* PWMA Dead Time */
		PWM_DTCNT1(2) = SUB_2_DTCNT1_INIT;					/* PWMB Dead Time */
	#else
		PWM_DISMAP(2) = 0xF000;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(2) = 0x0000;								/* PWMA Dead Time */
		PWM_DTCNT1(2) = 0x0000;								/* PWMB Dead Time */
	#endif


	PWM_TCTRL(2) = 0x0; 									/* OUT_TRIGx not used */

	#ifdef	PWM_INTC_EN
	    PWM_INTEN(2) = PWM_SUB2_INTEN_VALUE;				/* Intc source: Reload & Reload Error */
	#endif

	#ifdef	PWM_DMA
	    PWM_DMAEN(2) = PWM_DMAEN_VALUE;
	#endif    

	#ifdef	PWM_CAPTURE
		PWM_CAPTCTRLX(2) = 0x0;
		PWM_CAPTCOMPX(2) = 0x0;
	#endif

	/* Enable PWMA & PWMB Output */
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_2+PWM_OUTEN_PWMA_OFFSET) ) );
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_2+PWM_OUTEN_PWMB_OFFSET) ) );
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_2_A_Updata_Duty
   Description:     update SUB_2_A duty
   Parameters:      Input:    pwm_A_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_2_A_Updata_Duty(uint16 pwm_A_Duty)
{
#ifdef	PWM_SUB_2_OUT_EN
	uint8	RetValue;
	uint16	pwm_A_Width_Val3;
	
	RetValue = FALSE;
	/* translate pwm_A_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(pwm_A_Duty * SUB_2_VAL1_INIT)>>15);
	
	if(SUB_2_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(2) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(2) = pwm_A_Width_Val3;
		/* Load New Sub Module 0 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_2 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;	
	}
	else
	{
	}
#else
	uint8	RetValue;
	RetValue = FALSE;
	(void)pwm_A_Duty;
#endif

	return(RetValue);	
}


/* *****************************************************************************
   Function:        mPWM_Sub_2_B_Updata_Duty
   Description:     update SUB_2_B duty
   Parameters:      Input:    pwm_B_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_2_B_Updata_Duty(uint16 pwm_B_Duty)
{
#ifdef	PWM_SUB_2_OUT_EN
	uint8	RetValue;
	uint16	pwm_B_Width_Val5;
	
	RetValue = FALSE;
	/* translate pwm_B_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_B_Width_Val5 = (uint16)((uint32)(pwm_B_Duty * SUB_2_VAL1_INIT)>>15);
	
	if(SUB_2_VAL1_INIT >= pwm_B_Width_Val5)
	{
		PWM_VAL4(2) = 0xFFFF - pwm_B_Width_Val5 + 1;
		PWM_VAL5(2) = pwm_B_Width_Val5;
		/* Load New Sub Module 0 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_2 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;	
	}
	else
	{
	}
#else
	uint8	RetValue;
	RetValue = FALSE;
	(void)pwm_B_Duty;
#endif

	return(RetValue);	
}


/* *****************************************************************************
   Function:        mPWM_Sub_0_Init
   Description:     Sub0 Init, such as PCR, CTRLx, INIT, VALx, then enable Sub
   Parameters:      Input:    None
                    Output:   None
   Notes:           

   ***************************************************************************** */
static	void	mPWM_Sub_3_Init(void)
{
#ifdef	PWM_SUB_3_OUT_EN
	/* GPIO Pin Config */
	SIU.PCR[PWM_SUB_3_A_PIN].R  = PWM_SUB_3_PCR;
	SIU.PCR[PWM_SUB_3_B_PIN].R  = PWM_SUB_3_PCR;
	SIU.PSMI[PWM_3_A_PSMI].R	= PWM_3_A_PSMI_VAL;
	SIU.PSMI[PWM_3_B_PSMI].R	= PWM_3_B_PSMI_VAL;
		
	#ifdef	PWM_SUB3_CAPTX_EN
		SIU.PCR[PWM_SUB_3_X_PIN].R  = PWM_SUB_3_X_PCR;
		SIU.PSMI[PWM_3_X_PSMI].R	= PWM_3_X_PSMI_VAL;
	#endif
	

	/* PWM Control 1 Reg */
//#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN

#if 1
	REG16_BIT_CLEAR(PWM_CTRL1(3), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Disabled */
	REG16_BIT_SET(PWM_CTRL1(3), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Enabled */
#else
	REG16_BIT_SET(PWM_CTRL1(3), PWM_CTRL1_FULL_MASK);		/* Full Cycle ReLoad Enabled */
	REG16_BIT_CLEAR(PWM_CTRL1(3), PWM_CTRL1_HALF_MASK);		/* Half-Cycle Reload Disabled */
#endif
	REG16_BIT_CLEAR(PWM_CTRL1(3), PWM_CTRL1_DBLEN_MASK);	/* Double Switching Disabled */
	REG16_BIT_CLEAR(PWM_CTRL1(3), PWM_CTRL1_PRSC_MASK);
	REG16_BIT_SET(PWM_CTRL1(3), (PWM_PRSC_SUB_3<<4) );		/* PreScaler = 2 ^ PRSC, PWM Clock = fclk / PreScaler;  */
	REG16_BIT_CLEAR(PWM_CTRL1(3), PWM_CTRL1_LDFQ_MASK);
	REG16_BIT_SET(PWM_CTRL1(3), (LOAD_EVERY_2<<12) );		/* PWM Reload Frequency Every n PWM Opportunity  */

    /* PWM Control 2 Reg */
//#ifndef	PWM_SUB_AB_COMPLEMENTARY_EN
#if 1
    REG16_BIT_SET(PWM_CTRL2(3), PWM_CTRL2_INDEP_MASK);		/* PWMA & PWMB Outputs Independent, 0,complementary; 1,independent.  */
	PWM_OCTRL(3) = 0;
#else
	REG16_BIT_CLEAR(PWM_CTRL2(3), PWM_CTRL2_INDEP_MASK);
	//PWM_OCTRL(3) = PWM_OCTRL_POLA_MASK;						/* PWM Output Control Reg */
	PWM_OCTRL(3) = 0;						/* PWM Output Control Reg */
#endif

	REG16_BIT_SET(PWM_CTRL2(3), PWM_CTRL2_DBGEN_MASK);		/* PWM Runs In DeBug Mode, 1,run while in debug */

	/* PWM INIT and VALx */
	PWM_INIT(3) = SUB_3_INIT_INIT;							/* PWM Init Count clock */
	PWM_VAL0(3) = SUB_3_VAL0_INIT;							/* Mid Cycle Reload Point */
	PWM_VAL1(3) = SUB_3_VAL1_INIT;							/* Max Count */
	
	PWM_VAL2(3) = SUB_3_VAL2_INIT;							/* PWMA High Value */
	PWM_VAL3(3) = SUB_3_VAL3_INIT;							/* PWMA Low  Value */
	PWM_VAL4(3) = SUB_3_VAL4_INIT;							/* PWMB High Value */
	PWM_VAL5(3) = SUB_3_VAL5_INIT;							/* PWMB Low  Value */

	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53 */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period */
	//#ifdef	PWM_SUB_3_DEADTIME_EN
	#if 0
		PWM_DISMAP(3) = 0xF000;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(3) = SUB_3_DTCNT0_INIT;					/* PWMA Dead Time */
		PWM_DTCNT1(3) = SUB_3_DTCNT1_INIT;					/* PWMB Dead Time */
	#else
		PWM_DISMAP(3) = 0xF000;								/* ReSet PWMA & PWMB Fault Disable Mask */
		PWM_DTCNT0(3) = 0x0000;								/* PWMA Dead Time */
		PWM_DTCNT1(3) = 0x0000;								/* PWMB Dead Time */
	#endif
  

	PWM_TCTRL(3) = 0x0;										/* OUT_TRIGx not used */

	#ifdef	PWM_INTC_EN   
	    PWM_INTEN(3) = PWM_SUB3_INTEN_VALUE;				/* Intc source: Reload & Reload Error */
	#endif
    
	#ifdef	PWM_DMA
	    PWM_DMAEN(3) = PWM_DMAEN_VALUE;
	#endif
    
	#ifdef	PWM_CAPTURE
		PWM_CAPTCTRLX(3) = 0x0;
		PWM_CAPTCOMPX(3) = 0x0;
	#endif

	#ifdef	PWM_SUB3_CAPTX_EN
		PWM_CAPTCTRLX(3) = PWM_3_CAPCTRLX_VAL;
		PWM_CVAL0(3) = 0x0;
		PWM_CVAL1(3) = 0x0;
		mPWM_CaptX_Start(3);
	#endif
	/* Enable PWMA & PWMB Output */
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_3+PWM_OUTEN_PWMA_OFFSET) ) );
	REG16_BIT_SET(PWM_OUTEN, ( 1<<(PWM_SUB_3+PWM_OUTEN_PWMB_OFFSET) ) );
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_3_A_Updata_Duty
   Description:     update SUB_3_A duty
   Parameters:      Input:    pwm_A_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_3_A_Updata_Duty(uint16 pwm_A_Duty)
{
#ifdef	PWM_SUB_3_OUT_EN
	uint8	RetValue;
	uint16	pwm_A_Width_Val3;
	
	RetValue = FALSE;
	/* translate pwm_A_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(pwm_A_Duty * SUB_3_VAL1_INIT) >> 15);
	
	if(SUB_3_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(3) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(3) = pwm_A_Width_Val3;
		/* Load New Sub Module 0 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_3 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;	
	}
	else
	{
	}
	
	return(RetValue);
#endif	
}


/* *****************************************************************************
   Function:        mPWM_Sub_3_B_Updata_Duty
   Description:     update SUB_3_B duty
   Parameters:      Input:    pwm_B_Duty, Max = ( 2^15 - 1 ), stand for 100% duty
                    Output:   TRUE,		success
                    		  FALSE,	failed
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767               
   ***************************************************************************** */
uint8	mPWM_Sub_3_B_Updata_Duty(uint16 pwm_B_Duty)
{
#ifdef	PWM_SUB_3_OUT_EN
	uint8	RetValue;
	uint16	pwm_B_Width_Val5;
	
	RetValue = FALSE;
	/* translate pwm_B_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_B_Width_Val5 = (uint16)((uint32)(pwm_B_Duty * SUB_3_VAL1_INIT) >> 15);
	
	if(SUB_3_VAL1_INIT >= pwm_B_Width_Val5)
	{
		PWM_VAL4(3) = 0xFFFF - pwm_B_Width_Val5 + 1;
		PWM_VAL5(3) = pwm_B_Width_Val5;
		/* Load New Sub Module 0 Values */
		REG16_BIT_SET(PWM_MCTRL, ( 1<<(PWM_SUB_3 + PWM_MCTRL_LDOK_OFFSET) ) );
		RetValue = TRUE;	
	}
	else
	{
	}
	
	return(RetValue);
#endif	
}


/* *****************************************************************************
   Function:        mPWM_All_Init
   Description:     Init PWM all Sub
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mPWM_All_Init(void)
{
	mPWM_Sub_All_Stop();
	mPWM_Sub_0_Init();
	mPWM_Sub_1_Init();
	mPWM_Sub_2_Init();
	mPWM_Sub_3_Init();
	mPWM_General_Config();
//	mPWM_Sub_All_Start();	/* Sub 0,1,3;  */
}


/* *****************************************************************************
   Function:        mPWM_Sub_All_AB_Duty
   Description:     update all of 3 PWM AB duty, used for bridge voltage sample
   Parameters:      Input:    	Index0_Duty, 
   								Index1_Duty, 
   								Index2_Duty, 
                    Output:		None
   Notes:           
   (1) 100% pulse width , uint16 value is 32767 ,( 2^15 - 1 )  
   #define		DUTY_FULL				32767 
   (2) SUB_1_VAL1_INIT ,SUB_0_VAL1_INIT, SUB_3_VAL1_INIT  use one macro
   #define		SUB_ALL_VAL1_INIT		3000
   ***************************************************************************** */
#ifndef PWM_SUB_AB_COMPLEMENTARY_EN	/* Independent Mode */

void	mPWM_Sub_All_AB_Duty(uint16 Index0_Duty, uint16 Index1_Duty, uint16 Index2_Duty)
{
	uint16	pwm_A_Width_Val3;
	
	/* Sub 0  */
	/* translate Index0_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(Index0_Duty * SUB_1_VAL1_INIT)>>15);
	if(SUB_ALL_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SUB_INDEX0) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SUB_INDEX0) = pwm_A_Width_Val3;
		PWM_VAL4(SUB_INDEX0) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL5(SUB_INDEX0) = pwm_A_Width_Val3;
	}
	else
	{
	}
	
	/* translate Index1_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */	
	pwm_A_Width_Val3 = (uint16)((uint32)(Index1_Duty * SUB_0_VAL1_INIT)>>15);
	if(SUB_ALL_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SUB_INDEX1) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SUB_INDEX1) = pwm_A_Width_Val3;
		PWM_VAL4(SUB_INDEX1) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL5(SUB_INDEX1) = pwm_A_Width_Val3;	
	}
	else
	{
	}	
	
	/* translate Index2_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(Index2_Duty * SUB_3_VAL1_INIT)>>15);
	if(SUB_ALL_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SUB_INDEX2) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SUB_INDEX2) = pwm_A_Width_Val3;
		PWM_VAL4(SUB_INDEX2) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL5(SUB_INDEX2) = pwm_A_Width_Val3;
	}
	else
	{
	}
	
	/* must load synchronously */
	REG16_BIT_SET(PWM_MCTRL, ( (1<<(SUB_INDEX0+PWM_MCTRL_LDOK_OFFSET))|(1<<(SUB_INDEX1+PWM_MCTRL_LDOK_OFFSET))|(1<<(SUB_INDEX2+PWM_MCTRL_LDOK_OFFSET)) ));
}

#else	/* Compenmentary Mode */
/* Under Complementary Mode, A Inverted for the same phase as B, so */ 
/* take Deadtime = 0.8% * Period_A for example, then */
/* Duty_A = Duty_A_Before + Deadtime; ( 0.8% to 100%  ) */
/* Duty_B = Duty_B_Before - Deadtime; ( 0%   to 99.2% ) */
void	mPWM_Sub_All_AB_Duty(uint16 Index0_Duty, uint16 Index1_Duty, uint16 Index2_Duty)
{
	uint16	pwm_A_Width_Val3;
	
	/* Sub 0  */
	/* translate Index0_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(Index0_Duty * SUB_1_VAL1_INIT)>>15);
	/* SUB_A Output Inverted */
	if(SUB_ALL_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SUB_INDEX0) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SUB_INDEX0) = pwm_A_Width_Val3;	
	}
	else
	{
	}
	
	/* translate Index1_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */	
	pwm_A_Width_Val3 = (uint16)((uint32)(Index1_Duty * SUB_0_VAL1_INIT)>>15);
	/* SUB_A Output Inverted */
	if(SUB_ALL_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SUB_INDEX1) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SUB_INDEX1) = pwm_A_Width_Val3;	
	}
	else
	{
	}	
	
	/* translate Index2_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(Index2_Duty * SUB_3_VAL1_INIT)>>15);
	/* SUB_A Output Inverted */
	if(SUB_ALL_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SUB_INDEX2) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SUB_INDEX2) = pwm_A_Width_Val3;
	}
	else
	{
	}
	
	/* must load synchronously */
	REG16_BIT_SET(PWM_MCTRL, ( (1<<(SUB_INDEX0+PWM_MCTRL_LDOK_OFFSET))|(1<<(SUB_INDEX1+PWM_MCTRL_LDOK_OFFSET))|(1<<(SUB_INDEX2+PWM_MCTRL_LDOK_OFFSET)) ));
}

#endif

#ifdef	PWM_SUB0_RELOAD_ISR_EN
extern	void	pFUN_mPWM_IRQ179_RF0_Hook(void);
/* *****************************************************************************
   Function:        mPWM_Sub0_RF_ISR
   Description:     
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPWM_Sub0_RF_ISR(void)
{
	/* User Hook Operate */
	pFUN_mPWM_IRQ179_RF0_Hook();
	
	/* CLear ISR Flag, write 1 to clear */
	PWM_STS(0) = PWM_STS_RF_MASK;
}
#endif


#ifdef	PWM_SUB1_RELOAD_ISR_EN
extern	void	pFUN_mPWM_IRQ182_RF1_Hook(void);
/* *****************************************************************************
   Function:        mPWM_Sub1_RF_ISR
   Description:     
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPWM_Sub1_RF_ISR(void)
{
	/* User Hook Operate */
	pFUN_mPWM_IRQ182_RF1_Hook();
	
	/* CLear ISR Flag, write 1 to clear */
	PWM_STS(1) = PWM_STS_RF_MASK;			
}
#endif


#ifdef	PWM_SUB2_RELOAD_ISR_EN
extern	void	pFUN_mPWM_IRQ185_RF2_Hook(void);
/* *****************************************************************************
   Function:        mPWM_Sub2_RF_ISR
   Description:     
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPWM_Sub2_RF_ISR(void)
{
	/* User Hook Operate */
	pFUN_mPWM_IRQ185_RF2_Hook();
	
	/* CLear ISR Flag, write 1 to clear */
	PWM_STS(2) = PWM_STS_RF_MASK;			
}
#endif


#ifdef	PWM_SUB3_RELOAD_ISR_EN
extern	void	pFUN_mPWM_IRQ188_RF3_Hook(void);
/* *****************************************************************************
   Function:        mPWM_Sub3_RF_ISR
   Description:     
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPWM_Sub3_RF_ISR(void)
{
	/* User Hook Operate */
	pFUN_mPWM_IRQ188_RF3_Hook();
	
	/* CLear ISR Flag, write 1 to clear */
	PWM_STS(3) = PWM_STS_RF_MASK;			
}
#endif


#ifdef	PWM_RELOAD_ERR_ISR_EN
extern	void	pFUN_mPWM_IRQ192_ReloadErr_Hook(void);
/* *****************************************************************************
   Function:        mPWM_Reload_Err_ISR
   Description:     
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPWM_Reload_Err_ISR(void)
{
	/* User Hook Operate */
	pFUN_mPWM_IRQ192_ReloadErr_Hook();
	
	/* CLear ISR Flag, write 1 to clear	 */
	if(PWM_STS(0) & PWM_STS_REF_MASK )
	{
		PWM_STS(0) = PWM_STS_REF_MASK;
	}
	else
	{ }
	
	if(PWM_STS(1) & PWM_STS_REF_MASK )
	{
		PWM_STS(1) = PWM_STS_REF_MASK;
	}
	else
	{ }
	
	if(PWM_STS(2) & PWM_STS_REF_MASK )
	{
		PWM_STS(2) = PWM_STS_REF_MASK;
	}
	else
	{ }
	
	if(PWM_STS(3) & PWM_STS_REF_MASK )
	{
		PWM_STS(3) = PWM_STS_REF_MASK;
	}
	else
	{ }	
}
#endif


/* *****************************************************************************
   Function:        mPWM_Sub_All_AB_Duty
   Description:     update one of 4 PWM AB duty
   Parameters:      Input:    	SubIndex:		Sub Index (such as SUB_0)
   								Sub_A_Duty:		Sub A Duty Value
   								Sub_B_Duty:		Sub B Duty Value
                    Output:		None
   Notes:           only Value modified, pleas Call "mPWM_Sub_All_AB_Load" to make output update

   ***************************************************************************** */
void	mPWM_Sub_x_AB_SetValue(uint8 SubIndex, uint16 Sub_A_Duty, uint16 Sub_B_Duty)
{
	uint16	pwm_A_Width_Val3;
	
	/* translate pwm_A_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(Sub_A_Duty * SUB_0_VAL1_INIT)>>15);
	
	if(SUB_0_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SubIndex) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SubIndex) = pwm_A_Width_Val3;

	}
	else
	{
	}
	
	pwm_A_Width_Val3 = (uint16)((uint32)(Sub_B_Duty * SUB_0_VAL1_INIT)>>15);
	
	if(SUB_0_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL4(SubIndex) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL5(SubIndex) = pwm_A_Width_Val3;

	}
	else
	{
	}
}


/* *****************************************************************************
   Function:        mPWM_Sub_x_AB_SetDeadtime
   Description:     Modify DeadTime Value in App, in Complementary mode
   Parameters:      Input:    	SubIndex:			Sub Index (such as SUB_0)
   								Sub_A_Deadtime:		Sub A DeadTime Value
   								Sub_B_Deadtime:		Sub B DeadTime Value
                    Output:		None
   Notes:           only avaliable in Complementary mode

   ***************************************************************************** */
void	mPWM_Sub_x_AB_SetDeadtime(uint8 SubIndex, uint16 Sub_A_Deadtime, uint16 Sub_B_Deadtime)
{
	/* Only avaliable in Complementary Mode */
	PWM_DTCNT0(SubIndex) = Sub_A_Deadtime & 0x7FF;					/* PWMA Dead Time */
	PWM_DTCNT1(SubIndex) = Sub_B_Deadtime & 0x7FF;					/* PWMB Dead Time */
}


/* *****************************************************************************
   Function:        mPWM_Sub_x_SetValue_A_Only
   Description:     update duty of SUB_A of 4 PWM
   Parameters:      Input:    	SubIndex:		Sub Index (such as SUB_0)
   								Sub_A_Duty:		Sub A Duty Value
                    Output:		None
   Notes:           only Value modified, pleas Call "mPWM_Sub_All_AB_Load" to make output update

   ***************************************************************************** */
void	mPWM_Sub_x_SetValue_A_Only(uint8 SubIndex, uint16 Sub_A_Duty)
{
	uint16	pwm_A_Width_Val3;
	
	/* translate pwm_A_Duty(2^15 stand for 100% duty) to counter 3000(100% duty ) */
	pwm_A_Width_Val3 = (uint16)((uint32)(Sub_A_Duty * SUB_0_VAL1_INIT)>>15);
	
	if(SUB_0_VAL1_INIT >= pwm_A_Width_Val3)
	{
		PWM_VAL2(SubIndex) = 0xFFFF - pwm_A_Width_Val3 + 1;
		PWM_VAL3(SubIndex) = pwm_A_Width_Val3;

	}
	else
	{
	}
}


/* *****************************************************************************
   Function:        mPWM_Sub_All_AB_Load
   Description:     Load New Value to Reg, Output New duty PWM
   Parameters:      Input:    	Sub0_En:		SUB_0 Load Enabled or not
   								Sub1_En:		SUB_1 Load Enabled or not
   								Sub2_En:		SUB_2 Load Enabled or not
   								Sub3_En:		SUB_3 Load Enabled or not
                    Output:		None
   Notes:           

   ***************************************************************************** */
void	mPWM_Sub_All_AB_Load(uint8 Sub0_En, uint8 Sub1_En, uint8 Sub2_En, uint8 Sub3_En)
{
	uint8	SubEn_Tmp = 0;
	
	if(FALSE != Sub0_En)
	{
		SubEn_Tmp |= (1<<PWM_SUB_0);
	}
	else
	{ }
	
	if(FALSE != Sub1_En)
	{
		SubEn_Tmp |= (1<<PWM_SUB_1);
	}
	else
	{ }
	
	if(FALSE != Sub2_En)
	{
		SubEn_Tmp |= (1<<PWM_SUB_2);
	}
	else
	{ }
	
	if(FALSE != Sub3_En)
	{
		SubEn_Tmp |= (1<<PWM_SUB_3);
	}
	else
	{ }	
	
	REG16_BIT_SET(PWM_MCTRL, (SubEn_Tmp<<(PWM_MCTRL_LDOK_OFFSET) ) );
}


/* *****************************************************************************
   Function:        mPWM_Sub_x_AB_SetPolarity
   Description:     Update Polarityof SUB A and B
   Parameters:      Input:    	SubIndex:		Sub Index (such as SUB_0)
   								Sub_A_Pol:		Polarity of SUB_A Invert or not (1 for Invert)
   								Sub_B_Pol:		Polarity of SUB_B Invert or not (1 for Invert)
                    Output:		None
   Notes:           

   ***************************************************************************** */
void	mPWM_Sub_x_AB_SetPolarity(uint8 SubIndex, uint8 Sub_A_Pol, uint8 Sub_B_Pol)
{
	if(FALSE == Sub_A_Pol)
	{
		PWM_OCTRL(SubIndex) &= ~PWM_OCTRL_POLA_MASK;	
	}
	else
	{
		PWM_OCTRL(SubIndex) |= PWM_OCTRL_POLA_MASK;		
	}

	if(FALSE == Sub_B_Pol)
	{
		PWM_OCTRL(SubIndex) &= ~PWM_OCTRL_POLB_MASK;	
	}
	else
	{
		PWM_OCTRL(SubIndex) |= PWM_OCTRL_POLB_MASK;		
	}	
}


void PWM_OCP_Isr()
{
	//PWM_OUTEN = 0x0990;
	//PWM_OUTEN = 0x0980;
//	REG16_BIT_SET(PWM_FSTS, 0xF);
    PWM_FSTS = 0x000F;
	//OCP_hanlde();
}

void PWM_OCP_softRest()
{
	//PWM_OUTEN = 0x0990;
	//PWM_OUTEN = 0x0980;
	//REG16_BIT_SET(PWM_FSTS, 0xF);
	PWM_FSTS = 0x000F;
	//OCP_hanlde();
}

/* End of file */