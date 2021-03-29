/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_PWM_Cfg.h
*
* @brief    Config Header file for "m_PWM_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/27      Lwt          	N/A          Original
*     1.1        2012/10/09      Lwt	       	N/A          Simplified, define Pin and Init_Duty
*     1.2        2012/11/02      Lwt			N/A          Add History Comment
*     1.3        2013/02/01      Lwt			N/A          Code Simplify, Delete "MPC560xP.h" Reg_Struct
*     1.4        2013/06/06      Lwt			N/A          Add SUB_A_B Outputs Complementary Macro
*     1.5        2014/07/22      Lwt			N/A          Add PWMX Capt Config for V1.6 HW
*     1.6        2017/02/26      ych			N/A          Add SUB_3_A_B 
************************************************************************************************/

#ifndef _M_PWM_CFG_H_
#define _M_PWM_CFG_H_


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_PWM_Drv.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   Config Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Module used for MCTRL.LDOK                                         ***/
/*---------------------------------------------------------------------------*/
#define		PWM_SUB_LOAD			((1<<PWM_SUB_0)|(1<<PWM_SUB_1)|(1<<PWM_SUB_3))	/* Module 0, 1, 3 */
#define		PWM_ABCD_SUB_LOAD			((1<<PWM_SUB_0)|(1<<PWM_SUB_1))	/* Module 0, 1 */

/*---------------------------------------------------------------------------*/
/***	PWM SUB DUTY Update Macro                                          ***/
/*---------------------------------------------------------------------------*/
#define		SUB_INDEX0		3
#define		SUB_INDEX1		0
#define		SUB_INDEX2		1

/* SUB[] PWMX used for Capt Macro */
#define		PWM_SUB0_CAPTX_EN
#define		PWM_SUB1_CAPTX_EN
#define		PWM_SUB3_CAPTX_EN

/*---------------------------------------------------------------------------*/
/***	Out Enabled                                                        ***/
/*---------------------------------------------------------------------------*/
#define		PWM_OUT_EN		(PWM_SUB0_A_MASK|PWM_SUB1_A_MASK|PWM_SUB3_A_MASK|PWM_SUB0_B_MASK|PWM_SUB1_B_MASK|PWM_SUB3_B_MASK)	// 0x0BB0



/*---------------------------------------------------------------------------*/
/***	PWM SUB OUT Enabled Macro                                          ***/
/*---------------------------------------------------------------------------*/
#define		PWM_SUB_0_OUT_EN
#define		PWM_SUB_1_OUT_EN	
#define		PWM_SUB_3_OUT_EN

/*---------------------------------------------------------------------------*/
/***	PWM SUB DeadTime Enabled Macro                                     ***/
/*---------------------------------------------------------------------------*/
#define		PWM_SUB_0_DEADTIME_EN
#define		PWM_SUB_1_DEADTIME_EN
#define		PWM_SUB_3_DEADTIME_EN

/*---------------------------------------------------------------------------*/
/***	PWM SUB AB Outputs Complementary Macro                             ***/
/*---------------------------------------------------------------------------*/
#if 1
	#define		PWM_SUB_AB_COMPLEMENTARY_EN
#endif

/*---------------------------------------------------------------------------*/
/***	PWM SUB AB Duty Init Macro (%)                                     ***/
/*---------------------------------------------------------------------------*/
#define		PWM_SUB_0_A_DUTY_PERCENT_INIT		50
#define		PWM_SUB_0_B_DUTY_PERCENT_INIT		PWM_SUB_0_A_DUTY_PERCENT_INIT
#define		PWM_SUB_1_A_DUTY_PERCENT_INIT		50
#define		PWM_SUB_1_B_DUTY_PERCENT_INIT		PWM_SUB_1_A_DUTY_PERCENT_INIT
//#define		PWM_SUB_3_A_DUTY_PERCENT_INIT		(5)   /* O_PWM_OCP_Set ?*/
//#define		PWM_SUB_3_A_DUTY_PERCENT_INIT		(52)   /* O_PWM_OCP_Set ?*/

#ifdef VEHICLE
#define		PWM_SUB_3_A_DUTY_PERCENT_INIT		(46)   /* O_PWM_OCP_Set ?*/
#else
#define		PWM_SUB_3_A_DUTY_PERCENT_INIT		(56)   /* O_PWM_OCP_Set ?*/
#endif

//#define		PWM_SUB_3_A_DUTY_PERCENT_INIT		(95)   /* O_PWM_OCP_Set */
#define		PWM_SUB_3_A_DUTY_PERCENT_RUN		(52)   /* O_PWM_OCP_Set DCDC RUN*/
//#define		PWM_SUB_3_B_DUTY_PERCENT_INIT		(90)     /* O_PWM_OVP_Set 500v */
//#define		PWM_SUB_3_B_DUTY_PERCENT_INIT		(95)     /* O_PWM_OVP_Set */
#define		PWM_SUB_3_B_DUTY_PERCENT_INIT		(95)     /* O_PWM_OVP_Set */

#define PWM_FAULT_0_EN

/*---------------------------------------------------------------------------*/
/***	PWM SUB0 PINSEL                                                    ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_0_OUT_EN
	#define		PWM_SUB_0_A_PIN		A11	
	#define		PWM_SUB_0_B_PIN		A10	
	#define		PWM_SUB_0_PCR		(ALT2|B_OBE)
	#define		PWM_0_A_PSMI		20
	#define		PWM_0_A_PSMI_VAL	0x0
	#define		PWM_0_B_PSMI		24
	#define		PWM_0_B_PSMI_VAL	0x0	
	
	#ifdef	PWM_SUB0_CAPTX_EN
		#define		PWM_SUB_0_X_PIN		D9
		#define		PWM_SUB_0_X_PCR		(ALT1|B_IBE)
		/* no PSMI for PWMX0 */

		#define		PWM0_CAPT_THRSH		0x0
		#define		PWM0_CAPT1_EDGE		PWMX_CPT_RISE_EDGE
		#define		PWM0_CAPT0_EDGE		PWMX_CPT_FALL_EDGE
		#define		PWM0_CAPT_MODE		PWMX_CPT_ONESHOT
		#define		PWM_0_CAPCTRLX_VAL	((PWM0_CAPT_THRSH<<8)|(PWM0_CAPT1_EDGE<<4)|(PWM0_CAPT0_EDGE<<2)|(PWM0_CAPT_MODE<<1))
	#endif
	
	#ifdef	PWM_FAULT_0_EN
		#define		PWM_FAULT_0_PIN		A9
		#define		PWM_FAULT_0_PCR		PCR_PIN_IN
		
		/*  PSMI */
		#define		PWM_FAULT0_PSMI		16
		#define		PWM_FAULT0_PSMI_VAL	0x0
		
		#define DISMAP_VALUE 0xFF11
		
	#else
		#define DISMAP_VALUE 0xF000
	#endif
	
#endif

/*---------------------------------------------------------------------------*/
/***	PWM SUB1 PINSEL                                                    ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_1_OUT_EN
	#define		PWM_SUB_1_A_PIN		C15
	#define		PWM_SUB_1_B_PIN		D0
	#define		PWM_SUB_1_PCR		(ALT3|B_OBE)
	#define		PWM_1_A_PSMI		21
	#define		PWM_1_A_PSMI_VAL	0x01
	#define		PWM_1_B_PSMI		25
	#define		PWM_1_B_PSMI_VAL	0x01		
	
	#ifdef	PWM_SUB1_CAPTX_EN
		#define		PWM_SUB_1_X_PIN		D12
		#define		PWM_SUB_1_X_PCR		(ALT1|B_IBE)
		#define		PWM_1_X_PSMI		28
		#define		PWM_1_X_PSMI_VAL	0x01

		#define		PWM1_CAPT_THRSH		0x0
		#define		PWM1_CAPT1_EDGE		PWMX_CPT_RISE_EDGE
		#define		PWM1_CAPT0_EDGE		PWMX_CPT_FALL_EDGE
		#define		PWM1_CAPT_MODE		PWMX_CPT_ONESHOT
		#define		PWM_1_CAPCTRLX_VAL	((PWM1_CAPT_THRSH<<8)|(PWM1_CAPT1_EDGE<<4)|(PWM1_CAPT0_EDGE<<2)|(PWM1_CAPT_MODE<<1))
	#endif
#endif

/*---------------------------------------------------------------------------*/
/***	PWM SUB2 PINSEL                                                    ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_2_OUT_EN
	#define		PWM_SUB_2_A_PIN		
	#define		PWM_SUB_2_B_PIN		A12
	#define		PWM_SUB_2_PCR		(ALT3|B_OBE)
	#define		PWM_2_A_PSMI		22
	#define		PWM_2_A_PSMI_VAL	0x0
	#define		PWM_2_B_PSMI		26
	#define		PWM_2_B_PSMI_VAL	0x0
#endif

/*---------------------------------------------------------------------------*/
/***	PWM SUB3 PINSEL                                                    ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_SUB_3_OUT_EN
	#define		PWM_SUB_3_A_PIN		D3
	#define		PWM_SUB_3_B_PIN		D4
	#define		PWM_SUB_3_PCR		(ALT3|B_OBE)
	#define		PWM_3_A_PSMI		23
	#define		PWM_3_A_PSMI_VAL	0x02
	#define		PWM_3_B_PSMI		27
	#define		PWM_3_B_PSMI_VAL	0x02
	
	#ifdef	PWM_SUB3_CAPTX_EN
		#define		PWM_SUB_3_X_PIN		C9
		#define		PWM_SUB_3_X_PCR		(ALT3|B_IBE)
		#define		PWM_3_X_PSMI		30
		#define		PWM_3_X_PSMI_VAL	0x00

		#define		PWM3_CAPT_THRSH		0x0
		#define		PWM3_CAPT1_EDGE		PWMX_CPT_RISE_EDGE
		#define		PWM3_CAPT0_EDGE		PWMX_CPT_FALL_EDGE
		#define		PWM3_CAPT_MODE		PWMX_CPT_ONESHOT
		#define		PWM_3_CAPCTRLX_VAL	((PWM3_CAPT_THRSH<<8)|(PWM3_CAPT1_EDGE<<4)|(PWM3_CAPT0_EDGE<<2)|(PWM3_CAPT_MODE<<1))
	#endif
	
#endif

/*---------------------------------------------------------------------------*/
/***	PWM Intc Enabled                                                   ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_INTC_EN
	#define		RELOAD_ERR_INTC		(1<<13)
	#define		RELOAD_INTC			(1<<12)
	/* Intc source: Reload & Reload Error */
	#define		PWM_SUB0_INTEN_VALUE	(RELOAD_ERR_INTC|RELOAD_INTC)
	#define		PWM_SUB1_INTEN_VALUE	(RELOAD_ERR_INTC|RELOAD_INTC)
	#define		PWM_SUB3_INTEN_VALUE	(RELOAD_ERR_INTC|RELOAD_INTC)
#endif

#endif	

