/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     m_ETimer_Drv.c
*
* @brief    eTimer Module Function, Init, Config eTimer Chan, ISR, used for compare or capture
*
********************************************************************************
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
*     1.6        2012/12/24      Lwt			N/A          Modify ISR function, get All of CAPT's Value
*     1.7        2013/01/18      Lwt			N/A          And CTU-eTimer Unit for 10KHz 50% Square Wave Out
*     1.8        2014/07/21      Lwt			N/A          Add and Modify eTimer Config for V1.6 HW
*******************************************************************************/
#ifndef M_ETIMER_DRV_C
#define M_ETIMER_DRV_C
#endif


/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_ETimer_Drv.h"
#include 	"m_ETimer_Cfg.h"
#include    "SysConfig.h"

volatile uint8  L2_eTimer0Chn0_flag_Uls_u08 = 0;
volatile uint16 L2_eTimer0Chn0_Capt1_Ct_u16 = 0;
volatile uint16 L2_eTimer0Chn0_Capt2_Ct_u16 = 0;

volatile uint8  L2_eTimer0Chn1_flag_Uls_u08 = 0;
volatile uint16 L2_eTimer0Chn1_Capt1_Ct_u16 = 0;
volatile uint16 L2_eTimer0Chn1_Capt2_Ct_u16 = 0;

volatile uint8  L2_eTimer0Chn4_flag_Uls_u08 = 0;
volatile uint16 L2_eTimer0Chn4_Capt1_Ct_u16 = 0;
volatile uint16 L2_eTimer0Chn4_Capt2_Ct_u16 = 0;

volatile uint8  L2_eTimer0Chn5_flag_Uls_u08 = 0;
volatile uint16 L2_eTimer0Chn5_Capt1_Ct_u16 = 0;
volatile uint16 L2_eTimer0Chn5_Capt2_Ct_u16 = 0;

/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mETimer_Channel_En
   Description:     Enable eTimer Channel
   Parameters:      Input:		ModuleNum: 	eTimer Module;
   								ChanNum:	eTimer Channel
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mETimer_Channel_En(uint8 ModuleNum, uint8 ChanNum)
{
	ETIMER_ENBL(ModuleNum) |= (1<<ChanNum);	
}


/* *****************************************************************************
   Function:        mETimer_Channel_Dis
   Description:     Disable eTimer Channel
   Parameters:      Input:		ModuleNum: 	eTimer Module;
   								ChanNum:	eTimer Channel
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer_Channel_Dis(uint8 ModuleNum, uint8 ChanNum)
{	
	ETIMER_ENBL(ModuleNum) &= (~(1<<ChanNum));		
}


/* *****************************************************************************
   Function:        mETimer_Capture_Start
   Description:     Start eTimer Channel
   Parameters:      Input:		ModuleNum: 	eTimer Module;
   								ChanNum:	eTimer Channel
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer_Capture_Start(uint8 ModuleNum, uint8 ChanNum)
{
	ETIMER_CCCTRL(ModuleNum, ChanNum) |= ET_CCCTRL_ARM_MASK;
}


/* *****************************************************************************
   Function:        mETimer_Capture_Stop
   Description:     Stop eTimer Channel
   Parameters:      Input:		ModuleNum: 	eTimer Module;
   								ChanNum:	eTimer Channel
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer_Capture_Stop(uint8 ModuleNum, uint8 ChanNum)
{
	ETIMER_CCCTRL(ModuleNum, ChanNum) &= (~ET_CCCTRL_ARM_MASK);
}


/* *****************************************************************************
   Function:        mETimer0_Init_CH0
   Description:     Initialize eTimer Mudule_0 Channel_0
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Not Used

   ***************************************************************************** */
void	mETimer0_Init_CH0(void)
{
#ifdef	ETIMER0_CH0
    #ifdef ET0_0_PIN
	    SIU.PCR[ET0_0_PIN].R  = ET0_0_PCR;
	#endif
	
	// COMP1 register 
    ETIMER_COMP1(ETIMER0, ET_CH_0) = ET_COMP_MAX;
    
	// COMP2 register
	ETIMER_COMP2(ETIMER0, ET_CH_0) = ET_COMP_MAX;
    
    // LOAD register
    #ifdef eTimer0_LOAD_CH0                 // LOAD register
        ETIMER_0.CHANNEL[0].LOAD.R    = eTimer0_LOAD_CH0;
    #endif
    
    // CTRL register
	REG32_WRITE(ETIMER_CTRL1(ETIMER0, ET_CH_0), ET0_CH0_CTRL1_VAL);
	

    // CTRL2 register 
    #ifdef eTimer0_CTRL2_CH0                
        ETIMER_0.CHANNEL[0].CTRL2.R   = eTimer0_CTRL2_CH0;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER0, ET_CH_0), ET0_CH0_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER0, ET_CH_0) = 0x00FF;
    REG32_WRITE(ETIMER_INTDMA(ETIMER0, ET_CH_0), ET0_CH0_INTDMA_VAL);
    
    #ifdef eTimer0_CMPLD1_CH0               // CMPLD1 register 
        ETIMER_0.CHANNEL[0].CMPLD1.R  = eTimer0_CMPLD1_CH0;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH0               // CMPLD2 register 
        ETIMER_0.CHANNEL[0].CMPLD2.R  = eTimer0_CMPLD2_CH0;
    #endif
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER0, ET_CH_0), ET0_CH0_CCCTRL_VAL);
    
    // FILT register 
    #ifdef eTimer0_FILT_CH0                 
        ETIMER_0.CHANNEL[0].FILT.R    = eTimer0_FILT_CH0;
    #endif
#endif
}


/* *****************************************************************************
   Function:        mETimer0_Init_CH1
   Description:     Initialize eTimer Mudule_0 Channel_1
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Not Used

   ***************************************************************************** */
void	mETimer0_Init_CH1(void)
{
#ifdef	ETIMER0_CH1
    #ifdef ET0_1_PIN
	    SIU.PCR[ET0_1_PIN].R  = ET0_1_PCR;
	#endif
	
	// COMP1 register 
    ETIMER_COMP1(ETIMER0, ET_CH_1) = ET_COMP_MAX;
    
	// COMP2 register
	ETIMER_COMP2(ETIMER0, ET_CH_1) = ET_COMP_MAX;
    
    // LOAD register
    #ifdef eTimer0_LOAD_CH1                 // LOAD register
        ETIMER_0.CHANNEL[1].LOAD.R    = eTimer0_LOAD_CH1;
    #endif
    
    // CTRL register
	REG32_WRITE(ETIMER_CTRL1(ETIMER0, ET_CH_1), ET0_CH1_CTRL1_VAL);
	

    // CTRL2 register 
    #ifdef eTimer0_CTRL2_CH1                
        ETIMER_0.CHANNEL[1].CTRL2.R   = eTimer0_CTRL2_CH1;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER0, ET_CH_1), ET0_CH1_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER0, ET_CH_1) = 0x00FF;
    REG32_WRITE(ETIMER_INTDMA(ETIMER0, ET_CH_1), ET0_CH1_INTDMA_VAL);
    
    #ifdef eTimer0_CMPLD1_CH1               // CMPLD1 register 
        ETIMER_0.CHANNEL[1].CMPLD1.R  = eTimer0_CMPLD1_CH1;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH1               // CMPLD2 register 
        ETIMER_0.CHANNEL[1].CMPLD2.R  = eTimer0_CMPLD2_CH1;
    #endif
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER0, ET_CH_1), ET0_CH1_CCCTRL_VAL);
    
    // FILT register 
    #ifdef eTimer0_FILT_CH1                
        ETIMER_0.CHANNEL[1].FILT.R    = eTimer0_FILT_CH1;
    #endif
#endif	
}


/* *****************************************************************************
   Function:        mETimer0_Init_CH2
   Description:     Initialize eTimer Mudule_0 Channel_2
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Not Used

   ***************************************************************************** */
void	mETimer0_Init_CH2(void)
{
#ifdef	ETIMER0_CH2
	#ifdef ET0_2_PIN                // GPIO Config ETC[2]
	    SIU.PCR[ET0_2_PIN].R  = ET0_2_PCR;
	#endif

	#ifdef eTimer0_COMP1_CH2                // COMP1 register 
	    ETIMER_0.CHANNEL[2].COMP1.R   = eTimer0_COMP1_CH2;
	#endif

	#ifdef eTimer0_COMP2_CH2                // COMP2 register 
	    ETIMER_0.CHANNEL[2].COMP2.R   = eTimer0_COMP2_CH2;
	#endif

	#ifdef eTimer0_LOAD_CH2                 // LOAD register
	    ETIMER_0.CHANNEL[2].LOAD.R    = eTimer0_LOAD_CH2;
	#endif

	#ifdef ET0_CTRL1_CH2                 // CTRL register 
	    ETIMER_0.CHANNEL[2].CTRL.R    = ET0_CTRL1_CH2;
	#endif

	#ifdef eTimer0_CTRL2_CH2                // CTRL2 register 
	    ETIMER_0.CHANNEL[2].CTRL2.R   = eTimer0_CTRL2_CH2;
	#endif

	#ifdef ET0_CTRL3_CH2                // CTRL3 register 
	    ETIMER_0.CHANNEL[2].CTRL3.R   = ET0_CTRL3_CH2;
	#endif

	#ifdef eTimer0_INTDMA_CH2               // INTDMA register 
	    ETIMER_0.CHANNEL[2].INTDMA.R  = eTimer0_INTDMA_CH2;
	#endif

	#ifdef eTimer0_CMPLD1_CH2               // CMPLD1 register 
	    ETIMER_0.CHANNEL[2].CMPLD1.R  = eTimer0_CMPLD1_CH2;
	#endif

	#ifdef eTimer0_CMPLD2_CH2               // CMPLD2 register 
	    ETIMER_0.CHANNEL[2].CMPLD2.R  = eTimer0_CMPLD2_CH2;
	#endif

	#ifdef ET0_CCCTRL_CH2               // CCCTRL register 
	    ETIMER_0.CHANNEL[2].CCCTRL.R  = ET0_CCCTRL_CH2;
	#endif

	#ifdef eTimer0_FILT_CH2                 // FILT register 
	    ETIMER_0.CHANNEL[2].FILT.R    = eTimer0_FILT_CH2;
	#endif
#endif	
}


/* *****************************************************************************
   Function:        mETimer0_Init_CH3
   Description:     Initialize eTimer Mudule_0 Channel_3
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Not Used

   ***************************************************************************** */
void	mETimer0_Init_CH3(void)
{
#ifdef	ETIMER0_CH3
	#ifdef ET0_3_PIN                // GPIO Config ETC[3]
	    SIU.PCR[ET0_3_PIN].R  = ET0_3_PCR;
	#endif

	#ifdef eTimer0_COMP1_CH3                // COMP1 register 
	    ETIMER_0.CHANNEL[3].COMP1.R   = eTimer0_COMP1_CH3;
	#endif

	#ifdef eTimer0_COMP2_CH3                // COMP2 register 
	    ETIMER_0.CHANNEL[3].COMP2.R   = eTimer0_COMP2_CH3;
	#endif

	#ifdef eTimer0_LOAD_CH3                 // LOAD register
	    ETIMER_0.CHANNEL[3].LOAD.R    = eTimer0_LOAD_CH3;
	#endif

	#ifdef eTimer0_CTRL_CH3                 // CTRL register 
	    ETIMER_0.CHANNEL[3].CTRL.R    = eTimer0_CTRL_CH3;
	#endif

	#ifdef eTimer0_CTRL2_CH3                // CTRL2 register 
	    ETIMER_0.CHANNEL[3].CTRL2.R   = eTimer0_CTRL2_CH3;
	#endif

	#ifdef eTimer0_CTRL3_CH3                // CTRL3 register 
	    ETIMER_0.CHANNEL[3].CTRL3.R   = eTimer0_CTRL3_CH3;
	#endif

	#ifdef eTimer0_INTDMA_CH3               // INTDMA register 
	    ETIMER_0.CHANNEL[3].INTDMA.R  = eTimer0_INTDMA_CH3;
	#endif

	#ifdef eTimer0_CMPLD1_CH3               // CMPLD1 register 
	    ETIMER_0.CHANNEL[3].CMPLD1.R  = eTimer0_CMPLD1_CH3;
	#endif

	#ifdef eTimer0_CMPLD2_CH3               // CMPLD2 register 
	    ETIMER_0.CHANNEL[3].CMPLD2.R  = eTimer0_CMPLD2_CH3;
	#endif

	#ifdef eTimer0_CCCTRL_CH3               // CCCTRL register 
	    ETIMER_0.CHANNEL[3].CCCTRL.R  = eTimer0_CCCTRL_CH3;
	#endif

	#ifdef eTimer0_FILT_CH3                 // FILT register 
	    ETIMER_0.CHANNEL[3].FILT.R    = eTimer0_FILT_CH3;
	#endif
#endif
}

void	mETimer0_Init_CH41(void)
{

#ifdef	ETIMER0_CH4
    #ifdef ET0_4_PIN                // GPIO Config ETC[4]
	    SIU.PCR[ET0_4_PIN].R  = 	(ALT1|B_OBE);
	    SIU.PSMI[ET0_4_PSMI].R	= ET0_4_PSMI_VAL;
	#endif
#endif	
	


    /*-------------------------------------------------------------------------
     * eTimer #0 Control registers
    --------------------------------------------------------------------------*/
        ETIMER_0.ENBL.R               = 0x001F;
    //    pETIMER_0->ENBL.R               = 0x10;
    
    /*-------------------------------------------------------------------------
     * eTimer #0 CHANNEL #4 Control registers
    --------------------------------------------------------------------------*/
        ETIMER_0.CHANNEL[4].CTRL.R    = 0xD848;
    
        ETIMER_0.CHANNEL[4].CTRL2.R   = 0x8003;
}
/* *****************************************************************************
   Function:        mETimer0_Init_CH4
   Description:     Initialize eTimer Mudule_0 Channel_4
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Used for Captrue

   ***************************************************************************** */
void	mETimer0_Init_CH4(void)
{
#ifdef	ETIMER0_CH4
    #ifdef ET0_4_PIN                // GPIO Config ETC[4]
	    SIU.PCR[ET0_4_PIN].R  = ET0_4_PCR;
	    SIU.PSMI[ET0_4_PSMI].R	= ET0_4_PSMI_VAL;
	#endif
	
	// COMP1 register 
    ETIMER_COMP1(ETIMER0, ET_CH_4) = ET_COMP_MAX;
    
	// COMP2 register
	ETIMER_COMP2(ETIMER0, ET_CH_4) = ET_COMP_MAX;
    
    // LOAD register
    #ifdef eTimer0_LOAD_CH4                 // LOAD register
        ETIMER_0.CHANNEL[4].LOAD.R    = eTimer0_LOAD_CH4;
    #endif
    
    // CTRL register
	REG32_WRITE(ETIMER_CTRL1(ETIMER0, ET_CH_4), ET0_CH4_CTRL1_VAL);
	

    // CTRL2 register 
    #ifdef eTimer0_CTRL2_CH4                
        ETIMER_0.CHANNEL[4].CTRL2.R   = eTimer0_CTRL2_CH4;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER0, ET_CH_4), ET0_CH4_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER0, ET_CH_4) = 0x00FF;
    REG32_WRITE(ETIMER_INTDMA(ETIMER0, ET_CH_4), ET0_CH4_INTDMA_VAL);
    
    #ifdef eTimer0_CMPLD1_CH4               // CMPLD1 register 
        ETIMER_0.CHANNEL[4].CMPLD1.R  = eTimer0_CMPLD1_CH4;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH4               // CMPLD2 register 
        ETIMER_0.CHANNEL[4].CMPLD2.R  = eTimer0_CMPLD2_CH4;
    #endif
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER0, ET_CH_4), ET0_CH4_CCCTRL_VAL);
    
    // FILT register 
    #ifdef eTimer0_FILT_CH4                 
        ETIMER_0.CHANNEL[4].FILT.R    = eTimer0_FILT_CH4;
    #endif
#endif
}


/* *****************************************************************************
   Function:        mETimer0_Init_CH5
   Description:     Initialize eTimer Mudule_0 Channel_5
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Not Used

   ***************************************************************************** */
void	mETimer0_Init_CH5(void)
{
#ifdef	ETIMER0_CH5
    #ifdef ET0_5_PIN                // GPIO Config ETC[4]
	    SIU.PCR[ET0_5_PIN].R  = ET0_5_PCR;
	    SIU.PSMI[ET0_5_PSMI].R	= ET0_5_PSMI_VAL;
	#endif
	
	// COMP1 register 
    ETIMER_COMP1(ETIMER0, ET_CH_5) = ET_COMP_MAX;
    
	// COMP2 register
	ETIMER_COMP2(ETIMER0, ET_CH_5) = ET_COMP_MAX;
    
    // LOAD register
    #ifdef eTimer0_LOAD_CH5                 // LOAD register
        ETIMER_0.CHANNEL[5].LOAD.R    = eTimer0_LOAD_CH5;
    #endif
    
    // CTRL register
	REG32_WRITE(ETIMER_CTRL1(ETIMER0, ET_CH_5), ET0_CH5_CTRL1_VAL);
	

    // CTRL2 register 
    #ifdef eTimer0_CTRL2_CH5                
        ETIMER_0.CHANNEL[5].CTRL2.R   = eTimer0_CTRL2_CH5;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER0, ET_CH_5), ET0_CH5_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER0, ET_CH_5) = 0x00FF;
    REG32_WRITE(ETIMER_INTDMA(ETIMER0, ET_CH_5), ET0_CH5_INTDMA_VAL);
    
    #ifdef eTimer0_CMPLD1_CH5               // CMPLD1 register 
        ETIMER_0.CHANNEL[5].CMPLD1.R  = eTimer0_CMPLD1_CH5;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH5               // CMPLD2 register 
        ETIMER_0.CHANNEL[5].CMPLD2.R  = eTimer0_CMPLD2_CH5;
    #endif
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER0, ET_CH_5), ET0_CH5_CCCTRL_VAL);
    
    // FILT register 
    #ifdef eTimer0_FILT_CH5                 
        ETIMER_0.CHANNEL[5].FILT.R    = eTimer0_FILT_CH5;
    #endif
#endif
}
   
/* *****************************************************************************
   Function:        mETimer0_Init
   Description:     Initialize eTimer Mudule_0 All of the Channels
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer0_Init(void)
{
    uint8	i;

    /* eTimer0 Reset */
    for (i=0; i<ET_CH_NUM; i++)
    {
    	ETIMER_CAPT1(ETIMER0, i)	= 0x0;
    	ETIMER_CAPT2(ETIMER0, i)	= 0x0;
    	ETIMER_COMP1(ETIMER0, i)	= 0x0;
    	ETIMER_COMP2(ETIMER0, i)	= 0x0;
		ETIMER_LOAD(ETIMER0, i)		= 0x0;
		ETIMER_HOLD(ETIMER0, i)		= 0x0;
		ETIMER_CNTR(ETIMER0, i)		= 0x0;
		ETIMER_CTRL1(ETIMER0, i)	= 0x0;
		ETIMER_CTRL2(ETIMER0, i)	= 0x0;
		ETIMER_CTRL3(ETIMER0, i)	= 0x0;
		ETIMER_INTDMA(ETIMER0, i)	= 0x0;
		ETIMER_CMPLD1(ETIMER0, i)	= 0x0;
		ETIMER_CMPLD2(ETIMER0, i)	= 0x0;
		ETIMER_STS(ETIMER0, i)		= 0x0;
		ETIMER_CCCTRL(ETIMER0, i)	= 0x0;
		ETIMER_FILT(ETIMER0, i)		= 0x0;
    }

    ETIMER_0.DREQ[0].R    = 0x0;
    ETIMER_0.DREQ[1].R    = 0x0;
    ETIMER_0.ENBL.R       = 0x0;
    ETIMER_0.WDTOH.R      = 0x0;
    ETIMER_0.WDTOL.R      = 0x0;
    
    
    // eTimer #0 Control registers
    #ifdef eTimer0_WDTOL                    // WDTOL register
        ETIMER_0.WDTOL.R              = eTimer0_WDTOL;
    #endif
    
    #ifdef eTimer0_WDTOH                    // WDTOH register
        ETIMER_0.WDTOH.R              = eTimer0_WDTOH;
    #endif
    
    // ENBL register
    #ifdef	ETIMER0_CH0	
    	mETimer_Channel_En(ETIMER0, ET_CH_0);
    #else
    	mETimer_Channel_Dis(ETIMER0, ET_CH_0);
    #endif
    
    #ifdef	ETIMER0_CH1
    	mETimer_Channel_En(ETIMER0, ET_CH_1);
    #else
    	mETimer_Channel_Dis(ETIMER0, ET_CH_1);
    #endif
    
    #ifdef	ETIMER0_CH2
    	mETimer_Channel_En(ETIMER0, ET_CH_2);
    #else
    	mETimer_Channel_Dis(ETIMER0, ET_CH_2);
    #endif
    
    #ifdef	ETIMER0_CH3
    	mETimer_Channel_En(ETIMER0, ET_CH_3);
    #else
    	mETimer_Channel_Dis(ETIMER0, ET_CH_3);
    #endif
    
    #ifdef	ETIMER0_CH4
    	mETimer_Channel_En(ETIMER0, ET_CH_4);
    #else
    	mETimer_Channel_Dis(ETIMER0, ET_CH_4);
    #endif
    
    #ifdef	ETIMER0_CH5
    	mETimer_Channel_En(ETIMER0, ET_CH_5);
    #else
    	mETimer_Channel_Dis(ETIMER0, ET_CH_5);
    #endif

    
    #ifdef eTimer0_DREQ0                    // DREQ[0] register
        ETIMER_0.DREQ[0].R            = eTimer0_DREQ0;
    #endif
    
    #ifdef eTimer0_DREQ1                    // DREQ[1] register
        ETIMER_0.DREQ[1].R            = eTimer0_DREQ1;
    #endif

    
    // eTimer #0 CHANNEL #0 Control registers
    mETimer0_Init_CH0();

    // eTimer #0 CHANNEL #1 Control registers
	mETimer0_Init_CH1();

    // eTimer #0 CHANNEL #2 Control registers
	mETimer0_Init_CH2();

    // eTimer #0 CHANNEL #3 Control registers
	mETimer0_Init_CH3();

    // eTimer #0 CHANNEL #4 Control registers
	mETimer0_Init_CH4();

    // eTimer #0 CHANNEL #5 Control registers
	mETimer0_Init_CH5();
}


/* *****************************************************************************
   Function:        mETimer1_Init_CH0
   Description:     Initialize eTimer Mudule_1 Channel_0
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Used for Capture

   ***************************************************************************** */
void	mETimer1_Init_CH0(void)
{
#ifdef	ETIMER1_CH0
    #ifdef ET1_0_PIN
    // GPIO Config ETC[0]
	SIU.PCR[ET1_0_PIN].R  = ET1_0_PCR;
	SIU.PSMI[ET1_0_PSMI].R	= ET1_0_PSMI_VAL;
	#endif
	
	// COMP1 register 
    ETIMER_COMP1(ETIMER1, ET_CH_0) = ET_COMP_MAX;
    
	// COMP2 register
	ETIMER_COMP2(ETIMER1, ET_CH_0) = ET_COMP_MAX;
    
    // LOAD register
    ETIMER_1.CHANNEL[0].LOAD.R    = ET1_CH0_LOAD;
    
    // CTRL register
	REG32_WRITE(ETIMER_CTRL1(ETIMER1, ET_CH_0), ET1_CH0_CTRL1_VAL);

    // CTRL2 register 
    #ifdef eTimer1_CTRL2_CH0                
        ETIMER_1.CHANNEL[0].CTRL2.R   = eTimer1_CTRL2_CH0;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER1, ET_CH_0), ET1_CH0_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER1, ET_CH_0) = 0x00FF;
    REG32_WRITE(ETIMER_INTDMA(ETIMER1, ET_CH_0), ET1_CH0_INTDMA_VAL);
    
    #ifdef eTimer1_CMPLD1_CH0               // CMPLD1 register 
        ETIMER_1.CHANNEL[0].CMPLD1.R  = eTimer1_CMPLD1_CH0;
    #endif
    
    #ifdef eTimer1_CMPLD2_CH0               // CMPLD2 register 
        ETIMER_1.CHANNEL[0].CMPLD2.R  = eTimer1_CMPLD2_CH0;
    #endif
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER1, ET_CH_0), ET1_CH0_CCCTRL_VAL);
    
    // FILT register 
    #ifdef eTimer1_FILT_CH0               
        ETIMER_1.CHANNEL[0].FILT.R    = eTimer1_FILT_CH1;
    #endif
#endif	
}
/* *****************************************************************************
   Function:        mETimer1_Init_CH1
   Description:     Initialize eTimer Mudule_1 Channel_1
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Used for Capture

   ***************************************************************************** */
void	mETimer1_Init_CH1(void)
{
#ifdef	ETIMER1_CH1
    #ifdef ET1_1_PIN
    // GPIO Config ETC[0]
	SIU.PCR[ET1_1_PIN].R  = ET1_1_PCR;
	SIU.PSMI[ET1_1_PSMI].R	= ET1_1_PSMI_VAL;
	#endif
	
	// COMP1 register 
    ETIMER_COMP1(ETIMER1, ET_CH_1) = ET_COMP_MAX;
    
	// COMP2 register
	ETIMER_COMP2(ETIMER1, ET_CH_1) = ET_COMP_MAX;
    
    // LOAD register
    ETIMER_1.CHANNEL[1].LOAD.R    = ET1_CH1_LOAD;
    
    // CTRL register
	REG32_WRITE(ETIMER_CTRL1(ETIMER1, ET_CH_1), ET1_CH1_CTRL1_VAL);

    // CTRL2 register 
    #ifdef eTimer1_CTRL2_CH1                
        ETIMER_1.CHANNEL[1].CTRL2.R   = eTimer1_CTRL2_CH1;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER1, ET_CH_1), ET1_CH1_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER1, ET_CH_1) = 0x00FF;
    REG32_WRITE(ETIMER_INTDMA(ETIMER1, ET_CH_1), ET1_CH1_INTDMA_VAL);
    
    #ifdef eTimer1_CMPLD1_CH1               // CMPLD1 register 
        ETIMER_1.CHANNEL[1].CMPLD1.R  = eTimer1_CMPLD1_CH1;
    #endif
    
    #ifdef eTimer1_CMPLD2_CH1               // CMPLD2 register 
        ETIMER_1.CHANNEL[1].CMPLD2.R  = eTimer1_CMPLD2_CH1;
    #endif
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER1, ET_CH_1), ET1_CH1_CCCTRL_VAL);
    
    // FILT register 
    #ifdef eTimer1_FILT_CH1               
        ETIMER_1.CHANNEL[1].FILT.R    = eTimer1_FILT_CH1;
    #endif
#endif	
}
/* *****************************************************************************
   Function:        mETimer1_Init_CH2
   Description:     Initialize eTimer Mudule_1 Channel_2
   Parameters:      Input:		None
                    Output:   	None
   Notes:           PIN[D1] used for CTU_eTimer Output to generate 10KHz Square Wave
   					with Phase progameable (by modifing Ctu_Cfg.h )
   ***************************************************************************** */
void	mETimer1_Init_CH2(void)
{
#ifdef	ETIMER1_CH2
    // GPIO Config ETC[0]
	SIU.PCR[ET1_2_PIN].R  = ET1_2_PCR;
	SIU.PSMI[ET1_2_PSMI].R	= ET1_2_PSMI_VAL;

	// COMP1 register 
	ETIMER_COMP1(ETIMER1, ET_CH_2) = ET1_CH2_COMP1_VAL;
	
    // COMP2 register
	ETIMER_COMP2(ETIMER1, ET_CH_2) = ET1_CH2_COMP2_VAL;

    // LOAD register
    #ifdef eTimer1_LOAD_CH2
        ETIMER_LOAD(ETIMER1, ET_CH_2)	= eTimer1_LOAD_CH2;
    #endif
    
    // CTRL register
    REG32_WRITE(ETIMER_CTRL1(ETIMER1, ET_CH_2), ET1_CH2_CTRL1_VAL);
    
    // CTRL2 register 
    #ifdef eTimer1_CTRL2_CH2
    	REG32_WRITE(ETIMER_CTRL2(ETIMER1, ET_CH_2), ET1_CH2_CTRL2_VAL);
	#endif
	
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER1, ET_CH_2), ET1_CH2_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER1, ET_CH_2) = 0x00FF;
    #ifdef eTimer1_INTDMA_CH2
		REG32_WRITE(ETIMER_INTDMA(ETIMER1, ET_CH_2), ET1_CH2_INTDMA_VAL);
    #endif
    
    // CMPLD1 register
    ETIMER_CMPLD1(ETIMER1, ET_CH_2) = ET1_CH2_CMPLD1_VAL;
    
    // CMPLD2 register
    ETIMER_CMPLD2(ETIMER1, ET_CH_2) = ET1_CH2_CMPLD2_VAL;
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER1, ET_CH_2), ET1_CH2_CCCTRL_VAL);
    
    // FILT register
    ETIMER_FILT(ETIMER1, ET_CH_2) = ET1_CH2_FILT_VAL;
#endif
}


/* *****************************************************************************
   Function:        mETimer1_Init_CH3
   Description:     Initialize eTimer Mudule_1 Channel_3
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Not Used

   ***************************************************************************** */
void	mETimer1_Init_CH3(void)
{
#ifdef	ETIMER1_CH3
    // GPIO Config ETC[3]
	SIU.PCR[ET1_3_PIN].R  = ET1_3_PCR;
	SIU.PSMI[ET1_3_PSMI].R	= ET1_3_PSMI_VAL;

	// COMP1 register 
    ETIMER_COMP1(ETIMER1, ET_CH_3) = ET_COMP_MAX;

    // COMP2 register
	ETIMER_COMP2(ETIMER1, ET_CH_3) = ET_COMP_MAX;
    
    // LOAD register
    #ifdef eTimer1_LOAD_CH3
        ETIMER_LOAD(ETIMER1, ET_CH_3)	= eTimer1_LOAD_CH3;
    #endif
    
    // CTRL register
    REG32_WRITE(ETIMER_CTRL1(ETIMER1, ET_CH_3), ET1_CH3_CTRL1_VAL);
    
    // CTRL2 register 
    #ifdef eTimer1_CTRL2_CH3
        ETIMER_1.CHANNEL[3].CTRL2.R   = eTimer1_CTRL2_CH3;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER1, ET_CH_3), ET1_CH3_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER1, ET_CH_3) = 0x00FF;
	REG32_WRITE(ETIMER_INTDMA(ETIMER1, ET_CH_3), ET1_CH3_INTDMA_VAL);
    
    // CMPLD1 register
    #ifdef eTimer1_CMPLD1_CH3
        ETIMER_CMPLD1(ETIMER1, ET_CH_3) = eTimer1_CMPLD1_CH3;
    #endif
    
    // CMPLD2 register
    #ifdef eTimer1_CMPLD2_CH3
        ETIMER_CMPLD2(ETIMER1, ET_CH_3) = eTimer1_CMPLD2_CH3;
    #endif
    
    // CCCTRL register
    REG32_WRITE(ETIMER_CCCTRL(ETIMER1, ET_CH_3), ET1_CH3_CCCTRL_VAL);
    
    // FILT register
    #ifdef eTimer1_FILT_CH3
        ETIMER_FILT(ETIMER1, ET_CH_3) = eTimer1_FILT_CH3;
    #endif
#endif
}


/* *****************************************************************************
   Function:        mETimer1_Init_CH4
   Description:     Initialize eTimer Mudule_1 Channel_4
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Used for Capture

   ***************************************************************************** */
void	mETimer1_Init_CH4(void)
{
#ifdef	ETIMER1_CH4
    // GPIO Config ETC[3]
	SIU.PCR[ET1_4_PIN].R  = ET1_4_PCR;
	SIU.PSMI[ET1_4_PSMI].R	= ET1_4_PSMI_VAL;

	// COMP1 register 
    ETIMER_COMP1(ETIMER1, ET_CH_4) = ET_COMP_MAX;

    // COMP2 register
	ETIMER_COMP2(ETIMER1, ET_CH_4) = ET_COMP_MAX;
    
    // LOAD register
    #ifdef eTimer1_LOAD_CH4
        ETIMER_LOAD(ETIMER1, ET_CH_4)	= eTimer1_LOAD_CH4;
    #endif
    
    // CTRL register
    REG32_WRITE(ETIMER_CTRL1(ETIMER1, ET_CH_4), ET1_CH4_CTRL1_VAL);
    
    // CTRL2 register 
    #ifdef eTimer1_CTRL2_CH4
        ETIMER_1.CHANNEL[4].CTRL2.R   = eTimer1_CTRL2_CH4;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER1, ET_CH_4), ET1_CH4_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER1, ET_CH_4) = 0x00FF;
    REG32_WRITE(ETIMER_INTDMA(ETIMER1, ET_CH_4), ET1_CH4_INTDMA_VAL);
    
    // CMPLD1 register
    #ifdef eTimer1_CMPLD1_CH4
        ETIMER_CMPLD1(ETIMER1, ET_CH_4) = eTimer1_CMPLD1_CH4;
    #endif
    
    // CMPLD2 register
    #ifdef eTimer1_CMPLD2_CH4
        ETIMER_CMPLD2(ETIMER1, ET_CH_4) = eTimer1_CMPLD2_CH4;
    #endif
    
    // CCCTRL register
	REG32_WRITE(ETIMER_CCCTRL(ETIMER1, ET_CH_4), ET1_CH4_CCCTRL_VAL);
    
    // FILT register
    #ifdef eTimer1_FILT_CH4
        ETIMER_FILT(ETIMER1, ET_CH_4) = eTimer1_FILT_CH4;
    #endif
#endif
}

void	mETimer1_Init_CH5(void)
{
	    SIU.PCR[A15].R  = 	(ALT2|B_OBE);
	    SIU.PSMI[14].R	= 0x01;
	
    /*-------------------------------------------------------------------------
     * eTimer #0 Control registers
    --------------------------------------------------------------------------*/
        ETIMER_1.ENBL.R               |= 0x0020;
    //    pETIMER_0->ENBL.R               = 0x10;
    
    /*-------------------------------------------------------------------------
     * eTimer #0 CHANNEL #4 Control registers
    --------------------------------------------------------------------------*/
        ETIMER_1.CHANNEL[5].CTRL.R    = 0xD848;
    
        ETIMER_1.CHANNEL[5].CTRL2.R   = 0x8003;
}

/* *****************************************************************************
   Function:        mETimer1_Init_CH5
   Description:     Initialize eTimer Mudule_1 Channel_5
   Parameters:      Input:		None
                    Output:   	None
   Notes:           Used for Capture

   ***************************************************************************** */
void	mETimer1_Init_CH5_(void)
{
#ifdef	ETIMER1_CH5
    // GPIO Config ETC[5]
	SIU.PCR[ET1_5_PIN].R  = ET1_5_PCR;
	SIU.PSMI[ET1_5_PSMI].R	= ET1_5_PSMI_VAL;

	// COMP1 register 
    ETIMER_COMP1(ETIMER1, ET_CH_5) = ET_COMP_MAX;

    // COMP2 register
	ETIMER_COMP2(ETIMER1, ET_CH_5) = ET_COMP_MAX;
    
    // LOAD register
    #ifdef eTimer1_LOAD_CH5
        ETIMER_LOAD(ETIMER1, ET_CH_5)	= eTimer1_LOAD_CH5;
    #endif
    
    // CTRL register
    REG32_WRITE(ETIMER_CTRL1(ETIMER1, ET_CH_5), ET1_CH5_CTRL1_VAL);
    
    // CTRL2 register 
    #ifdef eTimer1_CTRL2_CH5
        ETIMER_1.CHANNEL[5].CTRL2.R   = eTimer1_CTRL2_CH5;
    #endif
    
    // CTRL3 register
    REG32_WRITE(ETIMER_CTRL3(ETIMER1, ET_CH_5), ET1_CH5_CTRL3_VAL);
    
    // INTDMA register
    ETIMER_STS(ETIMER1, ET_CH_5) = 0x00FF;
	REG32_WRITE(ETIMER_INTDMA(ETIMER1, ET_CH_5), ET1_CH5_INTDMA_VAL);
    
    // CMPLD1 register
    #ifdef eTimer1_CMPLD1_CH5
        ETIMER_CMPLD1(ETIMER1, ET_CH_5) = eTimer1_CMPLD1_CH5;
    #endif
    
    // CMPLD2 register
    #ifdef eTimer1_CMPLD2_CH5
        ETIMER_CMPLD2(ETIMER1, ET_CH_5) = eTimer1_CMPLD2_CH5;
    #endif
    
    // CCCTRL register
	REG32_WRITE(ETIMER_CCCTRL(ETIMER1, ET_CH_5), ET1_CH5_CCCTRL_VAL);
    
    // FILT register
    #ifdef eTimer1_FILT_CH5
        ETIMER_FILT(ETIMER1, ET_CH_5) = eTimer1_FILT_CH5;
    #endif
#endif
}


/* *****************************************************************************
   Function:        mETimer0_Init
   Description:     Initialize eTimer Mudule_1 All of the Channels
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer1_Init(void)
{
    uint8	i;

    // eTimer1 Reset
    for (i=0; i<ET_CH_NUM; i++)
    {
    	ETIMER_CAPT1(ETIMER1, i)	= 0x0;
    	ETIMER_CAPT2(ETIMER1, i)	= 0x0;
    	ETIMER_COMP1(ETIMER1, i)	= 0x0;
    	ETIMER_COMP2(ETIMER1, i)	= 0x0;
		ETIMER_LOAD(ETIMER1, i)		= 0x0;
		ETIMER_HOLD(ETIMER1, i)		= 0x0;
		ETIMER_CNTR(ETIMER1, i)		= 0x0;
		ETIMER_CTRL1(ETIMER1, i)	= 0x0;
		ETIMER_CTRL2(ETIMER1, i)	= 0x0;
		ETIMER_CTRL3(ETIMER1, i)	= 0x0;
		ETIMER_INTDMA(ETIMER1, i)	= 0x0;
		ETIMER_CMPLD1(ETIMER1, i)	= 0x0;
		ETIMER_CMPLD2(ETIMER1, i)	= 0x0;
		ETIMER_STS(ETIMER1, i)		= 0x0;
		ETIMER_CCCTRL(ETIMER1, i)	= 0x0;
		ETIMER_FILT(ETIMER1, i)		= 0x0;
    }

    ETIMER_1.DREQ[0].R    = 0x0;
    ETIMER_1.DREQ[1].R    = 0x0;
    ETIMER_1.ENBL.R       = 0x0;
    
    
    // eTimer #0 Control registers
    // ENBL register 
	#ifdef	ETIMER1_CH0
    	mETimer_Channel_En(ETIMER1, ET_CH_0);
    #else
    	mETimer_Channel_Dis(ETIMER1, ET_CH_0);
    #endif
    
    #ifdef	ETIMER1_CH1
    	mETimer_Channel_En(ETIMER1, ET_CH_1);
    #else
    	mETimer_Channel_Dis(ETIMER1, ET_CH_1);
    #endif
    
    #ifdef	ETIMER1_CH2
    	mETimer_Channel_En(ETIMER1, ET_CH_2);
    #else
    	mETimer_Channel_Dis(ETIMER1, ET_CH_2);
    #endif
    
    #ifdef	ETIMER1_CH3
    	mETimer_Channel_En(ETIMER1, ET_CH_3);
    #else
    	mETimer_Channel_Dis(ETIMER1, ET_CH_3);
    #endif
    
    #ifdef	ETIMER1_CH4
    	mETimer_Channel_En(ETIMER1, ET_CH_4);
    #else
    	mETimer_Channel_Dis(ETIMER1, ET_CH_4);
    #endif
    
    #ifdef	ETIMER1_CH5
    	mETimer_Channel_En(ETIMER1, ET_CH_5);
    #else
    	mETimer_Channel_Dis(ETIMER1, ET_CH_5);
    #endif

    
    #ifdef eTimer1_DREQ0                    // DREQ[0] register 
        ETIMER_1.DREQ[0].R            = eTimer1_DREQ0;
    #endif
    
    #ifdef eTimer1_DREQ1                    // DREQ[1] register
        ETIMER_1.DREQ[1].R            = eTimer1_DREQ1;
    #endif

    // eTimer #0 CHANNEL #0 Control registers
    mETimer1_Init_CH0();

    // eTimer #0 CHANNEL #1 Control registers
    mETimer1_Init_CH1();

    // eTimer #0 CHANNEL #2 Control registers
	mETimer1_Init_CH2();

    // eTimer #0 CHANNEL #3 Control registers
	mETimer1_Init_CH3();

    // eTimer #0 CHANNEL #4 Control registers
	mETimer1_Init_CH4();

    // eTimer #0 CHANNEL #5 Control registers
    mETimer1_Init_CH5();
}


/* *****************************************************************************
   Function:        mETimer1_Capture_CH0
   Description:     Get the Value of the eTimer Module_0 Channel_0's CAPT1 and CAPT2, Interrupe Unused Mode 
   Parameters:      Input:		*CapVal1:	Value of CAPT1
   								*CapVal2:	Value of CAPT2
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:           Check Mode of Capture
                   
   ***************************************************************************** */
uint8	mETimer1_Capture_CH0(uint16 *CapVal1, uint16 *CapVal2)
{
	uint8	StateRet;
	
	StateRet = OverTimeCheckLong_16U(ETIMER_STS_P(ETIMER1, ET_CH_0), ET_SYS_ICF2_MASK, ET_SYS_ICF2_MASK, ET_DELAY);
	
	if(StateRet)
	{
		*CapVal1 =  ETIMER_CAPT1(ETIMER1, ET_CH_0);
		*CapVal2 =  ETIMER_CAPT2(ETIMER1, ET_CH_0);
		ETIMER_STS(ETIMER1, ET_CH_0) |= 0xFF;
	}
	else
	{
		// do nothing
	}
	
	return(StateRet);
}


#ifdef	ETIMER0_CH0_ISR_EN

extern	void	mETimer0_CH0_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer0_CH0_157_ISR
   Description:     eTimer Module_0 Channel_0 Interrupt Service Function, Vector_157
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer0_CH0_157_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_0);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER0, ET_CH_0);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER0, ET_CH_0);
	}
	
	mETimer0_CH0_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER0, ET_CH_0) = 0xFF;
}
#endif


#ifdef	ETIMER0_CH1_ISR_EN

extern	void	mETimer0_CH1_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer0_CH1_158_ISR
   Description:     eTimer Module_0 Channel_1 Interrupt Service Function, Vector_158
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer0_CH1_158_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_1);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER0, ET_CH_1);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER0, ET_CH_1);
	}
	
	mETimer0_CH1_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER0, ET_CH_1) = 0xFF;
}
#endif


#ifdef	ETIMER0_CH2_ISR_EN

extern	void	mETimer0_CH2_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer0_CH2_159_ISR
   Description:     eTimer Module_0 Channel_2 Interrupt Service Function, Vector_159
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer0_CH2_159_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_2);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER0, ET_CH_2);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER0, ET_CH_2);
	}
	
	mETimer0_CH2_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER0, ET_CH_2) = 0xFF;
}
#endif


#ifdef	ETIMER0_CH3_ISR_EN

extern	void	mETimer0_CH3_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer0_CH3_160_ISR
   Description:     eTimer Module_0 Channel_3 Interrupt Service Function, Vector_160
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer0_CH3_160_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_3);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER0, ET_CH_3);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER0, ET_CH_3);
	}
	
	mETimer0_CH3_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER0, ET_CH_3) = 0xFF;
}
#endif

#ifdef	ETIMER0_CH4_ISR_EN

extern	void	mETimer0_CH4_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer0_CH4_161_ISR
   Description:     eTimer Module_0 Channel_4 Interrupt Service Function, Vector_161
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer0_CH4_161_ISR1(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_4);
	/* Get the numble of CAPT2's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	/* Get the numble of CAPT1's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	/* Get all of the CAPT2's Value */
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER0, ET_CH_4);
	}
	
	/* Get all of the CAPT1's Value */
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER0, ET_CH_4);
	}
	
	mETimer0_CH4_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER0, ET_CH_4) = 0xFF;
}
void	mETimer0_CH4_161_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
        ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_4);
		/* Get the numble of CAPT2's Value */
	    stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	    /* Get the numble of CAPT1's Value */
	    stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	    /* Get all of the CAPT2's Value */
	    for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	    {
	    	stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER0, ET_CH_4);
	    	
	    	L2_eTimer0Chn4_Capt2_Ct_u16 = stc_eTimer_Tmp.CAPT2_Val[i];
	    }
	    
	    /* Get all of the CAPT1's Value */
	    for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	    {
	    	stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER0, ET_CH_4);
	    	
	    	L2_eTimer0Chn4_Capt1_Ct_u16 = stc_eTimer_Tmp.CAPT1_Val[i];
	    }

        L2_eTimer0Chn4_flag_Uls_u08 = 1;

	    mETimer0_CH4_ISR_Hook(&stc_eTimer_Tmp);
	    ETIMER_STS(ETIMER0, ET_CH_4) = 0xFF;
}

#endif


#ifdef	ETIMER0_CH5_ISR_EN

extern	void	mETimer0_CH5_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer0_CH5_162_ISR
   Description:     eTimer Module_0 Channel_5 Interrupt Service Function, Vector_162
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer0_CH5_162_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_5);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER0, ET_CH_5);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER0, ET_CH_5);
	}
	
	mETimer0_CH5_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER0, ET_CH_5) = 0xFF;
}
#endif

#define ETIMER_STS_ICF1 ((1<<6))
/* *****************************************************************************
   Function:        L2_eTimer_Per1
   Description:     
   Parameters:      
                    
   Notes:           eTimer0_Chn4&Chn5 for T1&T2

   ***************************************************************************** */
void L2_eTimer_Per1(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	/********************************************************************************
	************   Channel 5 TAS-Tp                                        **********
	*********************************************************************************/
	if(ETIMER_STS(ETIMER0, ET_CH_5)&ETIMER_STS_ICF1)
	{
		ValCtrl3 = 	ETIMER_CTRL3(ETIMER0, ET_CH_5);
		stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
		stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);

		for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
		{
			L2_eTimer0Chn5_Capt2_Ct_u16 = ETIMER_CAPT2(ETIMER0, ET_CH_5);
		}

		for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
		{
			L2_eTimer0Chn5_Capt1_Ct_u16 = ETIMER_CAPT1(ETIMER0, ET_CH_5);
		}

		L2_eTimer0Chn5_flag_Uls_u08 = 1;

		ETIMER_STS(ETIMER0, ET_CH_5) = 0xFF;
	}
}


#ifdef	ETIMER1_CH0_ISR_EN

extern	void	mETimer1_CH0_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer1_CH0_168_ISR
   Description:     eTimer Module_1 Channel_0 Interrupt Service Function, Vector_168
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer1_CH0_168_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	stc_eTimer_Tmp.CAPT1_Val[0] = 0;
	stc_eTimer_Tmp.CAPT1_Val[1] = 0;
	stc_eTimer_Tmp.CAPT2_Val[0] = 0;
	stc_eTimer_Tmp.CAPT2_Val[1] = 0;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER1, ET_CH_0);
	/* Get the numble of CAPT2's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	/* Get the numble of CAPT1's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	/* Get all of the CAPT2's Value */
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER1, ET_CH_0);
	}
	
	/* Get all of the CAPT1's Value */	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER1, ET_CH_0);
	}
	
	mETimer1_CH0_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER1, ET_CH_0) = 0xFF;
}
#endif


#ifdef	ETIMER1_CH1_ISR_EN

extern	void	mETimer1_CH1_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer1_CH0_169_ISR
   Description:     eTimer Module_1 Channel_1 Interrupt Service Function, Vector_169
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer1_CH1_169_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER1, ET_CH_1);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER1, ET_CH_1);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER1, ET_CH_1);
	}
	
	mETimer1_CH1_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER1, ET_CH_1) = 0xFF;

}
#endif


#ifdef	ETIMER1_CH2_ISR_EN

extern	void	mETimer1_CH2_ISR_Hook(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer1_CH2_170_ISR
   Description:     eTimer Module_1 Channel_2 Interrupt Service Function, Vector_170
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer1_CH2_170_ISR(void)
{
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER1, ET_CH_2);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER1, ET_CH_2);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER1, ET_CH_2);
	}
	
	mETimer1_CH2_ISR_Hook(&stc_eTimer_Tmp);
	ETIMER_STS(ETIMER1, ET_CH_2) = 0xFF;

}
#endif


#ifdef	ETIMER1_CH3_ISR_EN

extern	void	mETimer1_CH3_ISR_Hook(void);//(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer1_CH3_171_ISR
   Description:     eTimer Module_1 Channel_3 Interrupt Service Function, Vector_171
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer1_CH3_171_ISR(void)
{
#if 0
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER1, ET_CH_3);
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER1, ET_CH_3);
	}
		
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER1, ET_CH_3);
	}
	
	mETimer1_CH3_ISR_Hook(&stc_eTimer_Tmp);
#endif  
    mETimer1_CH3_ISR_Hook();
	ETIMER_STS(ETIMER1, ET_CH_3) = 0xFF;
}
#endif


#ifdef	ETIMER1_CH4_ISR_EN

extern	void	mETimer1_CH4_ISR_Hook(void);//(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer1_CH4_172_ISR
   Description:     eTimer Module_1 Channel_4 Interrupt Service Function, Vector_172
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer1_CH4_172_ISR(void)
{
#if 0
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER1, ET_CH_4);
	/* Get the numble of CAPT2's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	/* Get the numble of CAPT1's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	/* Get all of the CAPT2's Value */
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER1, ET_CH_4);
	}
	
	/* Get all of the CAPT1's Value */
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER1, ET_CH_4);
	}
	
	mETimer1_CH4_ISR_Hook(&stc_eTimer_Tmp);
#endif
    mETimer1_CH4_ISR_Hook();
	ETIMER_STS(ETIMER1, ET_CH_4) = 0xFF;
}
#endif


#ifdef	ETIMER1_CH5_ISR_EN

extern	void	mETimer1_CH5_ISR_Hook(void);//(stc_eTimer_CAPT *pETimerCapt);
/* *****************************************************************************
   Function:        mETimer1_CH5_173_ISR
   Description:     eTimer Module_1 Channel_5 Interrupt Service Function, Vector_173
   Parameters:      Input:		None
                    Output:   	None
   Notes:           

   ***************************************************************************** */
void	mETimer1_CH5_173_ISR(void)
{
#if 0
	uint16	ValCtrl3;
	uint8	i;
	stc_eTimer_CAPT	stc_eTimer_Tmp;
	
	ValCtrl3 = 	ETIMER_CTRL3(ETIMER1, ET_CH_5);
	/* Get the numble of CAPT2's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C2FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C2FCNT_MASK) >> 5);
	/* Get the numble of CAPT1's Value */
	stc_eTimer_Tmp.Fcnt.Bits.C1FCNT = (uint8) ((ValCtrl3 & ET_CTRL3_C1FCNT_MASK) >> 2);
	
	/* Get all of the CAPT2's Value */
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C2FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT2_Val[i] = ETIMER_CAPT2(ETIMER1, ET_CH_5);
	}
	
	/* Get all of the CAPT1's Value */	
	for(i=0; i<stc_eTimer_Tmp.Fcnt.Bits.C1FCNT; i++)
	{
		stc_eTimer_Tmp.CAPT1_Val[i] = ETIMER_CAPT1(ETIMER1, ET_CH_5);
	}
	
	mETimer1_CH5_ISR_Hook(&stc_eTimer_Tmp);
#endif
    mETimer1_CH5_ISR_Hook();
	ETIMER_STS(ETIMER1, ET_CH_5) = 0xFF;
}
#endif


/* *****************************************************************************
   Function:        mETimer_Channel_Shut
   Description:     Shut the eTimer Channel, while it is working during Capture Mode
   Parameters:      Input:		ModuleNum: 	eTimer Module;
   								ChanNum:	eTimer Channel
                    Output:   	None
   Notes:           Capture Mode Supported, Compare Mode UnChecked

   ***************************************************************************** */
void	mETimer_Channel_Shut(uint8 ModuleNum, uint8 ChanNum)
{
	mETimer_Capture_Stop(ModuleNum, ChanNum);
	ETIMER_STS(ModuleNum, ChanNum) |= 0xFF;
	mETimer_Channel_Dis(ModuleNum, ChanNum);
}


/* *****************************************************************************
   Function:        mETimer_Channel_Open
   Description:     Open the eTimer Channel again,  Shut by "mETimer_Channel_Shut" function before
   Parameters:      Input:		ModuleNum: 	eTimer Module;
   								ChanNum:	eTimer Channel
                    Output:   	None
   Notes:           Capture Mode Supported, Compare Mode UnChecked

   ***************************************************************************** */
void	mETimer_Channel_Open(uint8 ModuleNum, uint8 ChanNum)
{
	ETIMER_CAPT1(ModuleNum, ChanNum) = 0;
	ETIMER_CAPT2(ModuleNum, ChanNum) = 0;
	ETIMER_STS(ModuleNum, ChanNum) |= 0xFF;
	mETimer_Channel_En(ModuleNum, ChanNum);
	mETimer_Capture_Start(ModuleNum, ChanNum);
}

/* End of file */
