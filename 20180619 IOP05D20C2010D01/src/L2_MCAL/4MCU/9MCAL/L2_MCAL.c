/***************************************************************************
*
* ChuangQu NewEnergy .
* (c) Copyright 2014 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************/
/*
*
* @file     
*
* @brief    
*
****************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2014/12/20      JiaoYu    	   	N/A          Original
****************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L2_MCAL.h"
/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L2MCAL_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************
*
*   Function:     MCU_L2_Init
*
*   Description:  This is the Initial function of MCU
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void MCU_L2_Init(void)
{
    /* disable soft watchdog */
    SWT_vDisableWatchDog();    
    
    /* init bus clock and mc clock */
	if((mSysClk_Sel() == E_OK) && (mMcClk_Sel() == E_OK))
	{
		/* init CTU */
		mCTU_Init();
		
		/* init ADC */
		mADC0_Init();
		mADC1_Init();
		
		/* init DSPI */
		mDSPI_All_Init();
		
		/* init CAN controller */
		(void)mCAN_Init();
		//(void)mSAFEPORT_CAN_Init();
		
		/* init interrupt */
		mINTC_Init();
		
		/* initialize eTimer */
		mETimer0_Init();

		mETimer_Channel_Open(ETIMER0,ET_CH_5); /* PWM-CP */

		/* eDMA init */
		mEDMA_CTU_FIFO_Init(); 

		/* init PWM */
		mPWM_All_Init();
		
		/* ecc */
		ECSM_Init();
		
		/* enable global interrupt */
		//mINTC_SetCurrPriority_Irq(PRIOR_0);
		//IRQ_ENABLE();
	}
	else
	{
	    /*Do nothing*/
	}    	
	
	/* ecc test */
//	EccTest();
    
 }
#define d_L2MCAL_STOP_SEC_CODE
#include "MemMap.h"
/*End of L2_MCAL.c file*/
