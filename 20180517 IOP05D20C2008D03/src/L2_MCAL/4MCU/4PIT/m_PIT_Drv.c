/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_PIT_Drv.c
*
* @brief    Periodic Interrupt Timer Module Intc_ISR and Init
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/08/30      Lwt       	   	N/A          Original
*     1.1        2012/09/14      jiaoyu			N/A          deliver to ChuangQu
*     1.3        2012/09/27      Lwt			N/A          Add Cfg file
*     1.2        2012/11/02      Lwt			N/A          Add History Comment
*     1.3        2013/03/05      Lwt			N/A          Add Comment
*******************************************************************************/

#ifndef M_PIT_DRV_C
#define M_PIT_DRV_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include	"m_PIT_Drv.h"
#include	"m_PIT_Cfg.h"
#include	"SysConfig.h"



/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */
#ifdef PIT_CH0_ISR_EN

extern void pFUN_mPIT_IRQ59_T0_Hook(void);

/* *****************************************************************************
   Function:        mPit_Timer0_ISR
   Description:     Pit0 Interrupt Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer0_ISR(void)
{
	/* User Hook Operate */
    pFUN_mPIT_IRQ59_T0_Hook();

	/* CLear PIT Flag */
	PIT.CH[0].TFLG.B.TIF = 1;			/* CLear PIT 1 flag by writing 1 */
}
#endif


/* *****************************************************************************
   Function:        mPit_Timer0_Init
   Description:     Pit0 Initalization
   Parameters:      Input:    
   						mInterval: Intc Period, unit: 1ms
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer0_Init(uint16	mInterval)
{
    PIT.CH[0].TFLG.B.TIF = 1;							/* CLear PIT Flag */
	PIT.PITMCR.R      = 0x00000001;       				/* Enable PIT and Config to stop in debug mode */
	PIT.CH[0].LDVAL.R = (mInterval * TIMER_50US_CYC);	/* Timeout= 64000 sysclks x 1sec/64M sysclks = 1 ms */
	PIT.CH[0].TCTRL.R = 0x000000003;      				/* Enable PIT1 interrupt & start PIT counting */
}


#ifdef PIT_CH1_ISR_EN

extern void pFUN_mPIT_IRQ60_T1_Hook(void);
/* *****************************************************************************
   Function:        mPit_Timer1_ISR
   Description:     Pit1 Interrupt Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer1_ISR(void)
{
	/* User Hook Operate */
    pFUN_mPIT_IRQ60_T1_Hook();
	
	/* CLear PIT Flag */
	PIT.CH[1].TFLG.B.TIF = 1;			/* MPC56xxP: CLear PIT 1 flag by writing 1 */
}
#endif
/* *****************************************************************************
   Function:        mPit_Timer1_Init
   Description:     Pit1 Initalization
   Parameters:      Input:
   						mInterval: Intc Period, unit: 1ms
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer1_Init(uint16	mInterval)
{
    PIT.CH[1].TFLG.B.TIF = 1;							/* CLear PIT Flag */
	PIT.PITMCR.R      = 0x00000001;       				/* Enable PIT and configure to stop in debug mode */
	PIT.CH[1].LDVAL.R = (mInterval * TIMER_1MS_CYC);	/* Timeout= 64000 sysclks x 1sec/64M sysclks = 1 ms */
	PIT.CH[1].TCTRL.R = 0x000000003;      				/* Enable PIT1 interrupt & start PIT counting */
}

#ifdef PIT_CH2_ISR_EN

extern void pFUN_mPIT_IRQ61_T2_Hook(void);
/* *****************************************************************************
   Function:        mPit_Timer2_ISR
   Description:     Pit2 Interrupt Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer2_ISR(void)
{
	/* User Hook Operate */
    pFUN_mPIT_IRQ61_T2_Hook();
	
	/* CLear PIT Flag, Write 1 to Clear */
	PIT.CH[2].TFLG.B.TIF = 1;
}
#endif


/* *****************************************************************************
   Function:        mPit_Timer2_Init
   Description:     Pit2 Initalization
   Parameters:      Input:
   						mInterval: Intc Period, unit: 1ms
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer2_Init(uint16	mInterval)
{
	PIT.PITMCR.R      = 0x00000001;       				/* Enable PIT and configure to stop in debug mode */
	PIT.CH[2].LDVAL.R = (mInterval * TIMER_1MS_CYC);	/* Timeout= 64000 sysclks x 1sec/64M sysclks = 1 ms */
	PIT.CH[2].TCTRL.R = 0x000000003;      				/* Enable PIT1 interrupt & start PIT counting */
	/* INTC_InstallINTCInterruptHandler(mPit_Timer2_ISR, PIT_VECT_CH2, PIT_PROI_CH2); */
	/* PIT.CH[2].TFLG.B.TIF = 1;							/* CLear PIT Flag */
}

#ifdef PIT_CH3_ISR_EN

extern void pFUN_mPIT_IRQ127_T3_Hook(void);
/* *****************************************************************************
   Function:        mPit_Timer3_ISR
   Description:     Pit3 Interrupt Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer3_ISR(void)
{
	/* User Hook Operate */
    pFUN_mPIT_IRQ127_T3_Hook();		
	
	/* CLear PIT Flag, Write 1 to Clear */
	PIT.CH[3].TFLG.B.TIF = 1;
}

#endif


/* *****************************************************************************
   Function:        mPit_Timer3_Init
   Description:     Pit3 Initalization
   Parameters:      Input:
   						mInterval: Intc Period, unit: 1ms
                    Output:   None
   Notes:           
   ***************************************************************************** */
void	mPit_Timer3_Init(uint16	mInterval)
{
    PIT.CH[3].TFLG.B.TIF = 1;							/* CLear PIT Flag */
	PIT.PITMCR.R      = 0x00000001;       				/* Enable PIT and configure to stop in debug mode */
	PIT.CH[3].LDVAL.R = (mInterval * TIMER_1MS_CYC);	/* Timeout= 64000 sysclks x 1sec/64M sysclks = 1 ms */
	PIT.CH[3].TCTRL.R = 0x000000003;      				/* Enable PIT1 interrupt & start PIT counting */
}






/* End of file */