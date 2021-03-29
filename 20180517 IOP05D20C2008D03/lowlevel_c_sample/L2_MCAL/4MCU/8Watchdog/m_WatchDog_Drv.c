/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_WatchDog_Drv.c
*
* @brief    Function of Soft Watch Dog Timer.
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/05      Lwt       	   	N/A          Original
*     1.1        2012/09/27      Lwt       	   	N/A          Add Cfg file
*     1.2        2012/11/02      Lwt			N/A          Add History Comment
*     1.3        2013/03/11      Lwt			N/A          Add SWT_En and Feed_SWT fuction
*     1.4        2013/03/12      Lwt			N/A          Modify SWT_En fuction (Feed Key)
*     1.5        2013/04/23      Lwt			N/A          Add SWT_TimeOut_ISR fuction
*******************************************************************************/

#ifndef M_WATCHDOG_DRV_C
#define M_WATCHDOG_DRV_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include  	"m_WatchDog_Drv.h"
#include  	"m_WatchDog_Cfg.h"
#include	"SysConfig.h"


/* *****************************************************************************
   Function:        void SWT_vDisableWatchDog(void)
   Description:     Disable The Software WatchDog Timer (SWT)
   Parameters:      Input:    None
                    Output:   None
   Notes:           To Clear The SWT_CR[SLK] Soft Lock Bit,
                    The Value 0xC520 Followed By 0xD928 Is Written To The WSC Field.
   ***************************************************************************** */
void	SWT_vDisableWatchDog(void)
{
	SWT.SR.R = SWT_SOFT_LOCK_KEY;				/* Write Keys To Clear Soft Lock Bit */
	SWT.SR.R = SWT_SOFT_LOCK_KEY_INVERT;		/* Key Inverter */
	SWT.CR.R = 0x8000010A;						/* Clear WatchDog Enable (WEN) */
}


/* *****************************************************************************
   Function:        mSWT_WatchDog_Dis
   Description:     Disable The Software WatchDog Timer (SWT)
   Parameters:      Input:    None
                    Output:   None
   Notes:           To Clear The SWT_CR[SLK] Soft Lock Bit,
                    The Value 0xC520 Followed By 0xD928 Is Written To The WSC Field.
   ***************************************************************************** */
void	mSWT_WatchDog_Dis(void)
{
	SWT.SR.R = SWT_SOFT_LOCK_KEY;				/* Write Keys To Clear Soft Lock Bit */
	SWT.SR.R = SWT_SOFT_LOCK_KEY_INVERT;		/* Key Inverter */
	SWT.CR.R = 0x8000010A;						/* Clear WatchDog Enable (WEN) */
}


/* *****************************************************************************
   Function:        mSWT_WatchDog_En
   Description:     Enable The Software WatchDog Timer (SWT)
   Parameters:      Input:
   						TimeOut_ms:	Time Out for WatchDog (unit: ms)
                    Output:   None
   Notes:           To Clear The SWT_CR[SLK] Soft Lock Bit,
                    The Value 0xC520 Followed By 0xD928 Is Written To The WSC Field.
   ***************************************************************************** */
void	mSWT_WatchDog_En(uint32 TimeOut_ms)
{
	SWT.SR.R = SWT_SOFT_LOCK_KEY;				/* Write Keys To Clear Soft Lock Bit */
	SWT.SR.R = SWT_SOFT_LOCK_KEY_INVERT;		/* Key Inverter */
	SWT.TO.R = TimeOut_ms * SWT_TIMEOUT_1MS;	/* config Timeout N ms */
	SWT.CR.R = 0x8000010B;						/* Enable WatchDog  (WEN) */
}


/* *****************************************************************************
   Function:        mSWT_WatchDog_Feed
   Description:     Feed WatchDog Timer (SWT)
   Parameters:      Input:		None
                    Output:		None
   Notes:           to Service Watchdog, the
   					value 0xA602 followed by 0xB480 is written to the WSC field
   ***************************************************************************** */
void	mSWT_WatchDog_Feed(void)
{
	SWT.SR.R = SWT_FEED_DOG_KEY;				/* Write Keys To Service Watchdog, */
	SWT.SR.R = SWT_FEED_DOG_KEY_INVERT;			/* Key Inverter */
}


#ifdef SWT_TIMEOUT_ISR_EN
extern void pFUN_mSWT_IRQ28_TimeOut_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH14_25_ISR
   Description:     Intc Service Rootine , vector 25 for DMA Channel 14
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mSWT_TimeOut_28_ISR(void)
{
	SWT.IR.R = 1;
	
	/* User Operation */
	pFUN_mSWT_IRQ28_TimeOut_Hook();
}
#endif



/* End of file */