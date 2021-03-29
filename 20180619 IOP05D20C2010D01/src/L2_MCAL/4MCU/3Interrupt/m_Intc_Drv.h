/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_Intc_Drv.h
*
* @brief    Drive Header file for "m_Intc_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/06/01      CODER2       		N/A          Original
*     1.1        2012/09/05      CODER2           	N/A          Modify include file
*     1.2        2012/09/07      CODER2           	N/A          Move Func Declaration to Src File
*     1.3        2012/09/14      ----			N/A          deliver to ChuangQu
*     1.4        2012/09/24      CODER2           	N/A          Modify PWM ISR
*     1.5        2012/10/11      CODER2           	N/A          Modify include file
*     1.6        2012/11/02      CODER2			N/A          Add History Comment
*     
************************************************************************************************/

#ifndef _M_INTC_DRV_H_
#define _M_INTC_DRV_H_

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"MPC560xP.h"
#include "Std_Types.h"

/* *****************************************************************************
   *****************************************************************************
   macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	INTC.CPR                                                           ***/
/*---------------------------------------------------------------------------*/
#define		PRIOR_0					0
#define		PRIOR_1					1
#define		PRIOR_2					2
#define		PRIOR_3					3
#define		PRIOR_4					4
#define		PRIOR_5					5
#define		PRIOR_6					6
#define		PRIOR_7					7
#define		PRIOR_8					8
#define		PRIOR_9					9
#define		PRIOR_10				10
#define		PRIOR_11				11
#define		PRIOR_12				12
#define		PRIOR_13				13
#define		PRIOR_14				14
#define		PRIOR_15				15

/*---------------------------------------------------------------------------*/
/***	INTC.MCR                                                           ***/
/*---------------------------------------------------------------------------*/
#define		HVEN_HW					1
#define		HVEN_SW					0

/*---------------------------------------------------------------------------*/
/***	INTC.VTES                                                          ***/
/*---------------------------------------------------------------------------*/
#define		VTES_BYTE4				0
#define		VTES_BYTE8				1

/*---------------------------------------------------------------------------*/
/***	INTC.SSCIR                                                         ***/
/*---------------------------------------------------------------------------*/
#define		SSCIR_SET				2
#define		SSCIR_CLR				1

/*---------------------------------------------------------------------------*/
/***	eTimer Channel Number                                              ***/
/*---------------------------------------------------------------------------*/
#define 	ET_0  		0u
#define 	ET_1  		1u
#define 	ET_2  		2u
#define 	ET_3  		3u
#define 	ET_4  		4u
#define 	ET_5  		5u


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
extern	void 	mINTC_Enable_Irq(void);
extern	void 	mINTC_SetCurrPriority_Irq(uint8	Peri);
extern	void	dummy(void);
extern	void 	mINTC_Init(void);

#endif	

