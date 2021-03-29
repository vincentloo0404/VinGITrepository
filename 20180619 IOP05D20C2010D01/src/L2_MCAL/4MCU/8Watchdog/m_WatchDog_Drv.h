/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_WatchDog_Drv.h
*
* @brief    Drive Header file for "m_WatchDog_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/05      CODER2       	   	N/A          Original
*     1.1        2012/09/27      CODER2       	   	N/A          Add Cfg file
*     1.2        2012/11/02      CODER2			N/A          Add History Comment
*     1.3        2013/03/12      CODER2			N/A          Add FEED and SOFT_LOCK Macro
************************************************************************************************/

#ifndef _M_WATCHDOG_DRV_H_
#define _M_WATCHDOG_DRV_H_

#ifdef 	M_WATCHDOG_DRV_C
#define M_WATCHDOG_DRV_EXT
#else
#define M_WATCHDOG_DRV_EXT extern
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"MPC560xP.h"
#include	"Std_Types.h"

/*---------------------------------------------------------------------------*/
/***	Service Code to clear Soft_Lock									   ***/
/*---------------------------------------------------------------------------*/
#define		SWT_SOFT_LOCK_KEY			0x0000C520
#define		SWT_SOFT_LOCK_KEY_INVERT	0x0000D928

/*---------------------------------------------------------------------------*/
/***	Service Code to Feed WatchDog									   ***/
/*---------------------------------------------------------------------------*/
#define		SWT_FEED_DOG_KEY			0x0000A602
#define		SWT_FEED_DOG_KEY_INVERT		0x0000B480


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_WATCHDOG_DRV_EXT	void	SWT_vDisableWatchDog(void);
M_WATCHDOG_DRV_EXT	void	mSWT_WatchDog_Dis(void);
M_WATCHDOG_DRV_EXT	void	mSWT_WatchDog_En(uint32 TimeOut_ms);
M_WATCHDOG_DRV_EXT	void	mSWT_WatchDog_Feed(void);

#endif	

/* End of file */