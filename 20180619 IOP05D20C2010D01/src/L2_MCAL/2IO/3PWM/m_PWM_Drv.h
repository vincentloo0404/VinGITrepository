/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_PWM_Drv.h
*
* @brief    Drive Header file for "m_PWM_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/06/11      CODER2          	N/A          Original
*     1.1        2012/09/05      CODER2			N/A          Modify include file
*     1.2        2012/09/20      CODER2			N/A          Modify Duty-Func
*     1.3        2012/09/24      CODER2			N/A          Modify Pins, Sub2, ISR_SRC, ISR_Predefine
*     1.4        2012/09/25      CODER2			N/A          Modify Duty Param-in
*     1.5        2012/09/27      CODER2			N/A          Add Cfg file
*     1.6        2012/10/09      CODER2	       	N/A          Modified All_Sub_Duty Function
*     1.7        2012/10/10      CODER2	       	N/A          Modified Func-Declaration in Header file
*     1.8        2012/11/02      CODER2			N/A          Add History Comment
*     1.9        2013/02/01      CODER2			N/A          Code Simplify, Delete "MPC560xP.h" Reg_Struct
*     1.10       2013/02/01      CODER2			N/A          Add Func-Declaration in Header
************************************************************************************************/

#ifndef _M_PWM_DRV_H_
#define _M_PWM_DRV_H_

#ifdef 	M_PWM_DRV_C
#define M_PWM_DRV_EXT
#else
#define M_PWM_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include	"Std_Types.h"
#include  	"m_GPIO.h"
#include	"Common.h"

/* *****************************************************************************
   *****************************************************************************
   macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	register Address define                                            ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_BASE_ADDRESS			0xFFE24000ul
#define 	PWM_MOUDLE_STEP				0x0050ul
#define 	PWM_SUBMOUDLE_ADDRESS(x)	(PWM_BASE_ADDRESS+(x)*PWM_MOUDLE_STEP)

/*---------------------------------------------------------------------------*/
/***	SubModule Register Address define                                  ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_CNT_OFFSET(x)			(0x00ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_INIT_OFFSET(x)			(0x02ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CTRL2_OFFSET(x)			(0x04ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CTRL1_OFFSET(x)			(0x06ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_VAL0_OFFSET(x)			(0x08ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_VAL1_OFFSET(x)			(0x0Aul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_VAL2_OFFSET(x)			(0x0Cul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_VAL3_OFFSET(x)			(0x0Eul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_VAL4_OFFSET(x)			(0x10ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_VAL5_OFFSET(x)			(0x12ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_OCTRL_OFFSET(x)			(0x18ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_STS_OFFSET(x)			(0x1Aul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_INTEN_OFFSET(x)			(0x1Cul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_DMAEN_OFFSET(x)			(0x1Eul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_TCTRL_OFFSET(x)			(0x20ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_DISMAP_OFFSET(x)		(0x22ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_DTCNT0_OFFSET(x)		(0x24ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_DTCNT1_OFFSET(x)		(0x26ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CAPTCTRLX_OFFSET(x)		(0x30ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CAPTCOMPX_OFFSET(x)		(0x32ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CVAL0_OFFSET(x)			(0x34ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CVAL0C_OFFSET(x)		(0x36ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CVAL1_OFFSET(x)			(0x38ul+PWM_SUBMOUDLE_ADDRESS(x))
#define 	PWM_CVAL1C_OFFSET(x)		(0x3Aul+PWM_SUBMOUDLE_ADDRESS(x))

/*---------------------------------------------------------------------------*/
/***	Common Share Register Address define                               ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_OUTEN_OFFSET			(0x140ul+PWM_BASE_ADDRESS)
#define 	PWM_MASK_OFFSET				(0x142ul+PWM_BASE_ADDRESS)
#define 	PWM_SWCOUT_OFFSET			(0x144ul+PWM_BASE_ADDRESS)
#define 	PWM_DTSRCSEL_OFFSET			(0x146ul+PWM_BASE_ADDRESS)
#define 	PWM_MCTRL_OFFSET			(0x148ul+PWM_BASE_ADDRESS)
#define 	PWM_FCTRL_OFFSET			(0x14Cul+PWM_BASE_ADDRESS)
#define 	PWM_FSTS_OFFSET				(0x14Eul+PWM_BASE_ADDRESS)
#define 	PWM_FFILT_OFFSET			(0x150ul+PWM_BASE_ADDRESS)

/*---------------------------------------------------------------------------*/
/***	Register Define                                                    ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_CNT(x)					(*(volatile uint16 *)PWM_CNT_OFFSET(x))
#define 	PWM_INIT(x)					(*(volatile uint16 *)PWM_INIT_OFFSET(x))
#define 	PWM_CTRL2(x)				(*(volatile uint16 *)PWM_CTRL2_OFFSET(x))
#define 	PWM_CTRL1(x)				(*(volatile uint16 *)PWM_CTRL1_OFFSET(x))
#define 	PWM_VAL0(x)					(*(volatile uint16 *)PWM_VAL0_OFFSET(x))
#define 	PWM_VAL1(x)					(*(volatile uint16 *)PWM_VAL1_OFFSET(x))
#define 	PWM_VAL2(x)					(*(volatile uint16 *)PWM_VAL2_OFFSET(x))
#define 	PWM_VAL3(x)					(*(volatile uint16 *)PWM_VAL3_OFFSET(x))
#define 	PWM_VAL4(x)					(*(volatile uint16 *)PWM_VAL4_OFFSET(x))
#define 	PWM_VAL5(x)					(*(volatile uint16 *)PWM_VAL5_OFFSET(x))

#define 	PWM_OCTRL(x)				(*(volatile uint16 *)PWM_OCTRL_OFFSET(x))
#define 	PWM_STS(x)					(*(volatile uint16 *)PWM_STS_OFFSET(x))
#define 	PWM_INTEN(x)				(*(volatile uint16 *)PWM_INTEN_OFFSET(x))
#define 	PWM_DMAEN(x)				(*(volatile uint16 *)PWM_DMAEN_OFFSET(x))
#define 	PWM_TCTRL(x)				(*(volatile uint16 *)PWM_TCTRL_OFFSET(x))
#define 	PWM_DISMAP(x)				(*(volatile uint16 *)PWM_DISMAP_OFFSET(x))
#define 	PWM_DTCNT0(x)				(*(volatile uint16 *)PWM_DTCNT0_OFFSET(x))
#define 	PWM_DTCNT1(x)				(*(volatile uint16 *)PWM_DTCNT1_OFFSET(x))

#define 	PWM_CAPTCTRLX(x)			(*(volatile uint16 *)PWM_CAPTCTRLX_OFFSET(x))
#define 	PWM_CAPTCOMPX(x)			(*(volatile uint16 *)PWM_CAPTCOMPX_OFFSET(x))
#define 	PWM_CVAL0(x)				(*(volatile uint16 *)PWM_CVAL0_OFFSET(x))
#define 	PWM_CVAL0C(x)				(*(volatile uint16 *)PWM_CVAL0C_OFFSET(x))
#define 	PWM_CVAL1(x)				(*(volatile uint16 *)PWM_CVAL1_OFFSET(x))
#define 	PWM_CVAL1C(x)				(*(volatile uint16 *)PWM_CVAL1C_OFFSET(x))

#define 	PWM_OUTEN					(*(volatile uint16 *)PWM_OUTEN_OFFSET)
#define 	PWM_MASK					(*(volatile uint16 *)PWM_MASK_OFFSET)
#define 	PWM_SWCOUT					(*(volatile uint16 *)PWM_SWCOUT_OFFSET)
#define 	PWM_DTSRCSEL				(*(volatile uint16 *)PWM_DTSRCSEL_OFFSET)
#define 	PWM_MCTRL					(*(volatile uint16 *)PWM_MCTRL_OFFSET)
#define 	PWM_FCTRL					(*(volatile uint16 *)PWM_FCTRL_OFFSET)
#define 	PWM_FSTS					(*(volatile uint16 *)PWM_FSTS_OFFSET)
#define 	PWM_FFILT					(*(volatile uint16 *)PWM_FFILT_OFFSET)

/*---------------------------------------------------------------------------*/
/***	Register Bit Mask                                                  ***/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/***	Control 2 Register (CTRL2)                                         ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_CTRL2_DBGEN_MASK		(1<<15)
#define 	PWM_CTRL2_WAITEN_MASK		(1<<14)
#define 	PWM_CTRL2_INDEP_MASK		(1<<13)
#define 	PWM_CTRL2_PWMA_INIT_MASK	(1<<12)
#define 	PWM_CTRL2_PWMB_INIT_MASK	(1<<11)
#define 	PWM_CTRL2_PWMC_INIT_MASK	(1<<10)
#define 	PWM_CTRL2_INIT_SEL_MASK		(0x3<<8)
#define 	PWM_CTRL2_FRCEN_MASK		(1<<7)
#define 	PWM_CTRL2_FORCE_MASK		(1<<6)
#define 	PWM_CTRL2_FRC_SEL_MASK		(0x7<<3)
#define 	PWM_CTRL2_RLD_SEL_MASK		(1<<2)
#define 	PWM_CTRL2_CLK_SEL_MASK		(0x3<<0)

/*---------------------------------------------------------------------------*/
/***	Control 1 Register (CTRL1)                                         ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_CTRL1_LDFQ_MASK			(0x7<<12)
#define 	PWM_CTRL1_HALF_MASK			(1<<11)
#define 	PWM_CTRL1_FULL_MASK			(1<<10)
#define 	PWM_CTRL1_DT_MASK			(0x3<<8)
#define 	PWM_CTRL1_PRSC_MASK			(0x7<<4)
#define 	PWM_CTRL1_DBLEN_MASK		(1<<0)

/*---------------------------------------------------------------------------*/
/***	Output Control register (OCTRL)                                    ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_OCTRL_PWMA_IN_MASK		(1<<15)
#define 	PWM_OCTRL_PWMB_IN_MASK		(1<<14)
#define 	PWM_OCTRL_PWMX_IN_MASK		(1<<13)
#define 	PWM_OCTRL_POLA_MASK			(1<<10)
#define 	PWM_OCTRL_POLB_MASK			(1<<9)
#define 	PWM_OCTRL_POLX_IN_MASK		(1<<8)
#define 	PWM_OCTRL_PWMAFS_MASK		(0x3<<4)
#define 	PWM_OCTRL_PWMBFS_MASK		(0x3<<2)
#define 	PWM_OCTRL_PWMXFS_MASK		(0x3<<0)

/*---------------------------------------------------------------------------*/
/***	Status register (STS)                                              ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_STS_RUF_MASK			(1<<14)
#define 	PWM_STS_REF_MASK			(1<<13)
#define 	PWM_STS_RF_MASK				(1<<12)
#define 	PWM_STS_CFX1_MASK			(1<<7)
#define 	PWM_STS_CFX0_MASK			(1<<6)
#define 	PWM_STS_CMPF_MASK			(0x3F<<0)

/*---------------------------------------------------------------------------*/
/***	Interrupt Enable register (INTEN)                                  ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_INTEN_REIE_MASK			(1<<13)
#define 	PWM_INTEN_RIE_MASK			(1<<12)
#define 	PWM_INTEN_CX1IE_MASK		(1<<7)
#define 	PWM_INTEN_CX0IE_MASK		(1<<6)
#define 	PWM_INTEN_CMPIE_MASK		(0x3F<<0)

/*---------------------------------------------------------------------------*/
/***	Output Enable register (OUTEN)                                     ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_OUTEN_PWMA_EN_MASK		(0xF<<8)
#define 	PWM_OUTEN_PWMB_EN_MASK		(0xF<<4)
#define 	PWM_OUTEN_PWMX_EN_MASK		(0xF<<0)
#define 	PWM_OUTEN_PWMA_OFFSET		8
#define 	PWM_OUTEN_PWMB_OFFSET		4
#define 	PWM_OUTEN_PWMX_OFFSET		0

/*---------------------------------------------------------------------------*/
/***	Master Control Register (MCTRL)                                    ***/
/*---------------------------------------------------------------------------*/
#define 	PWM_MCTRL_IPOL_MASK			(0xF<<12)
#define 	PWM_MCTRL_RUN_MASK			(0xF<<8)
#define 	PWM_MCTRL_CLDOK_MASK		(0xF<<4)
#define 	PWM_MCTRL_LDOK_MASK			(0xF<<0)
#define 	PWM_MCTRL_RUN_OFFSET		8
#define 	PWM_MCTRL_LDOK_OFFSET		0

/* Capture Control X register (CAPTCTRLX) */
#define 	PWM_CAPTCTRLX_ARM_MASK		(0x1<<0)
/* Capture Edge */
#define 	PWMX_CPT_DIS				0x00u
#define 	PWMX_CPT_FALL_EDGE			0x01u
#define 	PWMX_CPT_RISE_EDGE			0x02u
#define 	PWMX_CPT_BOTH_EDGE			0x03u

/* Capture Mode */
#define 	PWMX_CPT_RUN				0x00u
#define 	PWMX_CPT_ONESHOT			0x01u

/**************************************************************************************************/   
/*---------------------------------------------------------------------------*/
/***	PWM SUB Offset Macro                                               ***/
/*---------------------------------------------------------------------------*/
#define		PWM_SUB_0				0
#define		PWM_SUB_1				1
#define		PWM_SUB_2				2
#define		PWM_SUB_3				3

/*---------------------------------------------------------------------------*/
/***	Output Enable register (OUTEN)                                     ***/
/*---------------------------------------------------------------------------*/
#define		PWM_SUB3_A_MASK			(1<<11)
#define		PWM_SUB2_A_MASK			(1<<10)
#define		PWM_SUB1_A_MASK			(1<<9)
#define		PWM_SUB0_A_MASK			(1<<8)
#define		PWM_SUB3_B_MASK			(1<<7)
#define		PWM_SUB2_B_MASK			(1<<6)
#define		PWM_SUB1_B_MASK			(1<<5)
#define		PWM_SUB0_B_MASK			(1<<4)
#define		PWM_SUB3_X_MASK			(1<<3)
#define		PWM_SUB2_X_MASK			(1<<2)
#define		PWM_SUB1_X_MASK			(1<<1)
#define		PWM_SUB0_X_MASK			(1<<0)
#define		PWM_SUB_ALL_A_MASK		(0xF<<8)
#define		PWM_SUB_ALL_B_MASK		(0xF<<4)
#define		PWM_SUB_ALL_X_MASK		(0xF<<0)

//OUT PWM B C D DISABLE
#define		PWM_SUB1_AB_DISABLE	((!PWM_SUB1_A_MASK) | (!PWM_SUB1_B_MASK))
#define		PWM_SUB0_B_SUB1_AB_DISABLE	((!PWM_SUB0_B_MASK)|(!PWM_SUB1_A_MASK) | (!PWM_SUB1_B_MASK))

/*---------------------------------------------------------------------------*/
/***	PWM  CTRL.LDFQ                                                     ***/
/*---------------------------------------------------------------------------*/
#define		LOAD_EVERY_1				0
#define		LOAD_EVERY_2				1
#define		LOAD_EVERY_3				2
#define		LOAD_EVERY_4				3
#define		LOAD_EVERY_5				4
#define		LOAD_EVERY_6				5
#define		LOAD_EVERY_7				6
#define		LOAD_EVERY_8				7
#define		LOAD_EVERY_9				8
#define		LOAD_EVERY_10				9
#define		LOAD_EVERY_11				10
#define		LOAD_EVERY_12				11
#define		LOAD_EVERY_13				12
#define		LOAD_EVERY_14				13
#define		LOAD_EVERY_15				14
#define		LOAD_EVERY_16				15

/*---------------------------------------------------------------------------*/
/***	PWM DeadTime Enabled Macro, and so on                              ***/
/*---------------------------------------------------------------------------*/
#if 0
	#define		PWM_MASK_VAL
	#define		PWM_DEADTIME
	#define		PWM_FAULT
	#define		PWM_CAPTURE
	#define		PWM_DMA
#endif

/*---------------------------------------------------------------------------*/
/***	PWM Mask defination Macro 				                           ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_MASK_VAL
	#define		PWM_MASK_VAL		0x0FFF
#endif

/*---------------------------------------------------------------------------*/
/***	PWM DeadTime defination Macro 			                           ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_DEADTIME
	#define		PWM_SOFT_CTRL_OUT	0x00CF
	#define		PWM_DEADTIME_SRC	0xA0AA
#endif

/*---------------------------------------------------------------------------*/
/***	PWM Fault defination Macro 				                           ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_FAULT
	#define		PWM_SOFT_CTRL_OUT	0x00CF
	#define		PWM_DEADTIME_SRC	0xA0AA
#endif

/*---------------------------------------------------------------------------*/
/***	PWM DMA defination Macro 				                           ***/
/*---------------------------------------------------------------------------*/
#ifdef	PWM_DMA
	#define		PWM_DMAEN_VALUE		0x0000
#endif


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
extern	void	mPWM_Sub_All_Stop(void);
extern	uint8	mPWM_Sub_0_A_Updata_Duty(uint16 pwm_A_Duty);
extern	uint8	mPWM_Sub_0_B_Updata_Duty(uint16 pwm_B_Duty);
extern	uint8	mPWM_Sub_1_A_Updata_Duty(uint16 pwm_A_Duty);
extern	uint8	mPWM_Sub_1_B_Updata_Duty(uint16 pwm_B_Duty);
extern	uint8	mPWM_Sub_2_A_Updata_Duty(uint16 pwm_A_Duty);
extern	uint8	mPWM_Sub_2_B_Updata_Duty(uint16 pwm_B_Duty);
extern	uint8	mPWM_Sub_3_A_Updata_Duty(uint16 pwm_A_Duty);
extern	uint8	mPWM_Sub_3_B_Updata_Duty(uint16 pwm_B_Duty);
extern	void	mPWM_All_Init(void);
extern	void	mPWM_Sub_All_AB_Duty(uint16 Index0_Duty, uint16 Index1_Duty, uint16 Index2_Duty);
extern	void	mPWM_Sub_x_AB_SetValue(uint8 SubIndex, uint16 Sub_A_Duty, uint16 Sub_B_Duty);
extern	void	mPWM_Sub_x_AB_SetPolarity(uint8 SubIndex, uint8 Sub_A_Pol, uint8 Sub_B_Pol);
extern	void	mPWM_Sub_x_AB_SetDeadtime(uint8 SubIndex, uint16 Sub_A_Deadtime, uint16 Sub_B_Deadtime);
extern	void	mPWM_Sub_All_AB_Load(uint8 Sub0_En, uint8 Sub1_En, uint8 Sub2_En, uint8 Sub3_En);
extern	void	mPWM_Sub_x_SetValue_A_Only(uint8 SubIndex, uint16 Sub_A_Duty);
extern	void	mPWM_CaptX_Stop(uint8 SubIndex);
extern	void	mPWM_CaptX_Start(uint8 SubIndex);

extern void	mPWM_Sub_All_Start(void);
extern uint8	mPWM_Sub_0_AB_Advance(uint16 Ct,sint16 Ct1);

extern void mPWM_Sub_AB_PWM_Stop(void);
extern void	mPWM_Sub_CD_PWM_Stop(void);
extern void PWM_OCP_softRest(void);

#endif	

