/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_PWM_Drv_InitVal.h
*
* @brief    All PWM_SUB's Init Value for PWM Init
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/10/09      CODER2       	   	N/A          Original
*     1.1        2012/11/02      CODER2			N/A          Add History Comment
*     1.2        2013/02/01      CODER2			N/A          Code Simplify, Delete "MPC560xP.h" Reg_Struct
*     1.3        2013/06/06      CODER2			N/A          Add DeadTime Value Macro, Modify Full-duty Macro (2^15)
************************************************************************************************/
#ifndef _M_PWM_DRV_INITVAL_H_
#define _M_PWM_DRV_INITVAL_H_

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_PWM_Drv.h"
#include    "m_PWM_Cfg.h"

/* *****************************************************************************
   *****************************************************************************
   macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	PWM Duty Full Value                                                ***/
/*---------------------------------------------------------------------------*/
#define		DUTY_FULL				32768
#define		PWM__DUTY_PERCENT_FULL	100

/*---------------------------------------------------------------------------*/
/***	PWM Deadtime Init Value                                            ***/
/*---------------------------------------------------------------------------*/
#define		SUB_ALL_DEADTIMR_INIT	48	/* 120-1us */

/* CD chaoqian(SUB1),Ab zhihou(SUB0) ,CD相位不变，改变AB相位*/
//#define		SUB_0_DEADTIMR_INIT	(0.180*120.0)	/* 120-1us */
//#define		SUB_0_DEADTIMR_INIT	(0.30*120.0)	/* 120-1us */
//#define		SUB_1_DEADTIMR_INIT	(0.200*120.0)	/* 120-1us */


#define AB_before_CD


#ifdef AB_before_CD
	#define		SUB_0_DEADTIMR_INIT	(0.200*120.0)	// 120-1us 
	#define		SUB_1_DEADTIMR_INIT	(0.150*120.0)	// 120-1us 
#else
	#define		SUB_0_DEADTIMR_INIT	(0.150*120.0)	// 120-1us 
	#define		SUB_1_DEADTIMR_INIT	(0.200*120.0)	// 120-1us 
#endif

/*
#ifdef AB_before_CD
	#define		SUB_0_DEADTIMR_INIT	(0.200*120.0)	// 120-1us /
	#define		SUB_1_DEADTIMR_INIT	(0.200*120.0)	// 120-1us /
#else
	#define		SUB_0_DEADTIMR_INIT	(0.200*120.0)	// 120-1us /
	#define		SUB_1_DEADTIMR_INIT	(0.200*120.0)	// 120-1us /
#endif
*/

//#define DISMAP_VALUE 0xF000
//#define DISMAP_VALUE 0xFF76
//#define DISMAP_VALUE 0xFF72
//#define DISMAP_VALUE 0xFF70
//#define DISMAP_VALUE 0xFF00
//#define DISMAP_VALUE 0xFF77

//#define DISMAP_VALUE 0xFFFF
//#define DISMAP_VALUE 0xFF72
//#define DISMAP_VALUE 0xF000
//#define DISMAP_VALUE 0xFFF0
//#define DISMAP_VALUE 0xFFF1
//#define DISMAP_VALUE 0xFF71
//#define DISMAP_VALUE 0xF000

//#define DISMAP_VALUE 0xFF11

//#define SUB_0_DISMAP_VALUE 0xF011
//#define SUB_1_DISMAP_VALUE 0xFF77
/*---------------------------------------------------------------------------*/
/***	Use one Macro to unit SUB_1_VAL1_INIT, SUB_0_VAL1_INIT,            ***/
/***	,SUB_3_VAL1_INIT for "mPWM_Sub_All_AB_Duty"                        ***/
/*---------------------------------------------------------------------------*/
//#define		SUB_ALL_VAL1_INIT		3333   /* (120M / 18K / 2) */
//#define		SUB_ALL_VAL1_INIT		3000   /* (120M / 20K / 2) */
#define		SUB_ALL_VAL1_INIT		600   /* (120M / 100K / 2) */

#define		PFC_SUB_VAL1_INIT		(60000/8)   /* (120M / 1K / 2) */


/*---------------------------------------------------------------------------*/
/***	PWM SUB0 Init parameter INIT, VALx                                 ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_0_OUT_EN
	#define		PWM_PRSC_SUB_0		0	/* PreScaler = 2 ^ PRSC, PWM Clock = fclk / PreScaler;  */
	/* Resolution (1/3000) */	
	#define		SUB_0_INIT_INIT			(0xFFFF - SUB_0_VAL1_INIT + 1)	/* (0xFFFF - V1 + 1) */
	#define		SUB_0_VAL0_INIT			0x0000
	
	/* PWM Period SUB_n_VAL1 , Related to MC_CLK */
	#ifdef	MC_CLK_120MHZ	
		#define		SUB_0_VAL1_INIT			SUB_ALL_VAL1_INIT	
	#endif	
	#ifdef	MC_CLK_64MHZ
		#define		SUB_0_VAL1_INIT			1600	/* (64M / 20K / 2) */
	#endif
	
	/* PWMA Duty (V3/V1) */
	#define		SUB_0_VAL2_INIT			(0xFFFF - SUB_0_VAL3_INIT + 1)	/* (0xFFFF - V3 + 1) */
	#define		SUB_0_VAL3_INIT			(SUB_0_VAL1_INIT * PWM_SUB_0_A_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)	
	/* PWMB Duty (V5/V1) */
	#define		SUB_0_VAL4_INIT			(0xFFFF - SUB_0_VAL5_INIT + 1)	/* (0xFFFF - V5 + 1) */
	#define		SUB_0_VAL5_INIT			(SUB_0_VAL1_INIT * PWM_SUB_0_B_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)
	
	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53  */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period   */
	#ifdef	PWM_SUB_0_DEADTIME_EN
		/* PWMA DeadTime */
		#define		SUB_0_DTCNT0_INIT		SUB_0_DEADTIMR_INIT		/* 120 for 1us */
		/* PWMB DeadTime */
		#define		SUB_0_DTCNT1_INIT		SUB_0_DEADTIMR_INIT
	#endif	
#endif

/*---------------------------------------------------------------------------*/
/***	PWM SUB1 Init parameter INIT, VALx                                 ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_1_OUT_EN
	#define		PWM_PRSC_SUB_1		0
	/* Resolution (1/3000) */	
	#define		SUB_1_INIT_INIT			(0xFFFF - SUB_1_VAL1_INIT + 1)
	#define		SUB_1_VAL0_INIT			0x0000
	
	/* PWM Period SUB_n_VAL1 , Related to MC_CLK  */
	#ifdef	MC_CLK_120MHZ	
		#define		SUB_1_VAL1_INIT			SUB_ALL_VAL1_INIT
	#endif	
	#ifdef	MC_CLK_64MHZ
		#define		SUB_1_VAL1_INIT			1600
	#endif
	
	/* PWMA Duty (V3/V1) */
	#define		SUB_1_VAL2_INIT			(0xFFFF - SUB_1_VAL3_INIT + 1)
	#define		SUB_1_VAL3_INIT			(SUB_1_VAL1_INIT * PWM_SUB_1_A_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)	
	/* PWMB Duty (V5/V1) */
	#define		SUB_1_VAL4_INIT			(0xFFFF - SUB_1_VAL5_INIT + 1)
	#define		SUB_1_VAL5_INIT			(SUB_1_VAL1_INIT * PWM_SUB_1_B_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)	

	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53  */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period  */
	#ifdef	PWM_SUB_1_DEADTIME_EN
		/* PWMA DeadTime */
		#define		SUB_1_DTCNT0_INIT		SUB_1_DEADTIMR_INIT			/* MAX = 0x7FF */
		/* PWMB DeadTime */
		#define		SUB_1_DTCNT1_INIT		SUB_1_DEADTIMR_INIT
	#endif	
#endif

/*---------------------------------------------------------------------------*/
/***	PWM SUB2 Init parameter INIT, VALx                                 ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_2_OUT_EN
	#define		PWM_PRSC_SUB_2		0
	/* Resolution (1/3000) */	
	#define		SUB_2_INIT_INIT			(0xFFFF - SUB_2_VAL1_INIT + 1)
	#define		SUB_2_VAL0_INIT			0x0000
	
	/* PWM Period SUB_n_VAL1 , Related to MC_CLK */
	#ifdef	MC_CLK_120MHZ	
		#define		SUB_2_VAL1_INIT			SUB_ALL_VAL1_INIT
	#endif	
	#ifdef	MC_CLK_64MHZ
		#define		SUB_2_VAL1_INIT			1600
	#endif
		
	/* PWMA Duty (V3/V1) */
	#define		SUB_2_VAL2_INIT			(0xFFFF - SUB_2_VAL3_INIT + 1)
	#define		SUB_2_VAL3_INIT			(SUB_2_VAL1_INIT * PWM_SUB_2_A_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)	
	/* PWMB Duty (V5/V1) */
	#define		SUB_2_VAL4_INIT			(0xFFFF - SUB_2_VAL5_INIT + 1)
	#define		SUB_2_VAL5_INIT			(SUB_2_VAL1_INIT * PWM_SUB_2_B_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)	

	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53  */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period  */
	#ifdef	PWM_SUB_2_DEADTIME_EN
		/* PWMA DeadTime */
		#define		SUB_2_DTCNT0_INIT		SUB_ALL_DEADTIMR_INIT		/* MAX = 0x7FF */
		/* PWMB DeadTime */
		#define		SUB_2_DTCNT1_INIT		SUB_ALL_DEADTIMR_INIT
	#endif	
#endif

/*---------------------------------------------------------------------------*/
/***	PWM SUB3 Init parameter INIT, VALx                                 ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_3_OUT_EN
	#define		PWM_PRSC_SUB_3		(3)
	/* Resolution (1/3000) */
	#define		SUB_3_INIT_INIT			(0xFFFF - SUB_3_VAL1_INIT + 1)
	#define		SUB_3_VAL0_INIT			0x0000
		
	/* PWM Period SUB_n_VAL1 , Related to MC_CLK */
	#ifdef	MC_CLK_120MHZ	
		#define		SUB_3_VAL1_INIT			PFC_SUB_VAL1_INIT
	#endif	
	#ifdef	MC_CLK_64MHZ
		#define		SUB_3_VAL1_INIT			1600
	#endif
	
	/* PWMA Duty (V3/V1) */
	#define		SUB_3_VAL2_INIT			(0xFFFF - SUB_3_VAL3_INIT + 1)
	#define		SUB_3_VAL3_INIT			(SUB_3_VAL1_INIT * PWM_SUB_3_A_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)	
	#define		SUB_3_VAL3_DCDC_RUN			(DUTY_FULL * PWM_SUB_3_A_DUTY_PERCENT_RUN/PWM__DUTY_PERCENT_FULL)
	/* PWMB Duty (V5/V1) */
	#define		SUB_3_VAL4_INIT			(0xFFFF - SUB_3_VAL5_INIT + 1)
	#define		SUB_3_VAL5_INIT			(SUB_3_VAL1_INIT * PWM_SUB_3_B_DUTY_PERCENT_INIT/ PWM__DUTY_PERCENT_FULL)	

	/* DeadTime config (DeadTime = DTCNTx / 120MHz ; unit: sencond) Ref Fig_26-53  */
	/* Duty Cycle with DeadTime ( duty% * Period - DeadTime) / Period  */
	#ifdef	PWM_SUB_3_DEADTIME_EN
		/* PWMA DeadTime */
		#define		SUB_3_DTCNT0_INIT		SUB_ALL_DEADTIMR_INIT		/* MAX = 0x7FF */
		/* PWMB DeadTime */
		#define		SUB_3_DTCNT1_INIT		SUB_ALL_DEADTIMR_INIT
	#endif	
#endif




#endif