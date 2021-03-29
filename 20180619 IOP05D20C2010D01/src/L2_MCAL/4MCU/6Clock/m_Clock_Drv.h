/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_Clock_Drv.h
*
* @brief    Drive Header file for "m_Clock_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/05/23      Lwt       		N/A          Original
*     1.1        2012/09/05      Lwt			N/A          Modify include file
*     1.2        2012/09/27      Lwt			N/A          Add Cfg file
*     1.3        2012/11/02      Lwt			N/A          Add History Comment
*     1.4        2013/03/12      Lwt			N/A          Add KEY and Mode's Macro
************************************************************************************************/

#ifndef _M_CLOCK_DRV_H_
#define _M_CLOCK_DRV_H_

#ifdef 	M_CLOCK_DRV_C
#define M_CLOCK_DRV_EXT
#else
#define M_CLOCK_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"MPC560xP.h"
#include	"Std_Types.h"


/* *****************************************************************************
   *****************************************************************************
   structure definiton
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Xosc Input enum													   ***/
/*---------------------------------------------------------------------------*/
typedef	enum 
{
	Xosc_8M 	= 0,
	Xosc_12M 	= 1,
	Xosc_16M 	= 2,
	Xosc_40M 	= 3
}enum_XOSC_IN; 

/*---------------------------------------------------------------------------*/
/***	PLL Output enum													   ***/
/*---------------------------------------------------------------------------*/
typedef	enum 
{
	Pll_Out_40M		= 0,
	Pll_Out_48M		= 1,
	Pll_Out_64M		= 2,
	Pll_Out_80M		= 3,
	Pll_Out_120M	= 4
}enum_Pll_Tag; 

/*---------------------------------------------------------------------------*/
/***	System Clock Input enum											   ***/
/*---------------------------------------------------------------------------*/
typedef	enum	
{
	Sys_Clk_IRC		= 0,	
	Sys_Clk_Xosc	= 2,
	Sys_Clk_PLL0	= 4,
	Sys_Clk_PLL1	= 5,
	Sys_Clk_Disable	= 15,
	Sys_Clk_Rsv		= 1
}enum_Sys_Clk;	

/*---------------------------------------------------------------------------*/
/***	Aux Clock Input enum											   ***/
/*---------------------------------------------------------------------------*/
typedef	enum	
{
	Aux_Clk_IRC			= 0,	
	Aux_Clk_Xosc		= 2,
	Aux_Clk_PLL0		= 4,
	Aux_Clk_PLL1_120M	= 5,
	Aux_Clk_PLL1_80M	= 8,
	Aux_Clk_Rsv			= 1
}enum_Aux_Clk;

/*---------------------------------------------------------------------------*/
/***	Aux1 Clock Output enum											   ***/
/*---------------------------------------------------------------------------*/
typedef	enum	
{
	Aux1_PLL1_120M	= 0,
	Aux1_Rsv		= 1
}enum_Aux1_Clk;

/*---------------------------------------------------------------------------*/
/***	Clock Output's input enum										   ***/
/*---------------------------------------------------------------------------*/
typedef	enum
{
	ClkOut_IRC			= 0,	
	ClkOut_Xosc			= 1,
	ClkOut_PLL0			= 2,
	ClkOut_PLL1_120M	= 3
}enum_Clk_Out;

/*---------------------------------------------------------------------------*/
/***	Clock Output's divide enum										   ***/
/*---------------------------------------------------------------------------*/
typedef	enum
{
	ClkOut_Div_1		= 0,	
	ClkOut_Div_2		= 1,
	ClkOut_Div_4		= 2,
	ClkOut_Div_8		= 3
}enum_Clk_Out_Div;

/*---------------------------------------------------------------------------*/
/***	Aux1 Clock Output Divide enum									   ***/
/*---------------------------------------------------------------------------*/
typedef	enum
{
	Aux_Div_1			= 0,	
	Aux_Div_2			= 1,
	Aux_Div_3			= 2,
	Aux_Div_4			= 3,
	Aux_Div_5			= 4,	
	Aux_Div_6			= 5,
	Aux_Div_7			= 6,
	Aux_Div_8			= 7,
	Aux_Div_9			= 8,	
	Aux_Div_10			= 9,
	Aux_Div_11			= 10,
	Aux_Div_12			= 11,
	Aux_Div_13			= 12,	
	Aux_Div_14			= 13,
	Aux_Div_15			= 14,
	Aux_Div_16			= 15
}enum_Aux_Div;

/*---------------------------------------------------------------------------*/
/***	Mode Entry enum													   ***/
/*---------------------------------------------------------------------------*/
typedef	enum
{
	Mode_Reset		= 0,	
	Mode_Test		= 1,
	Mode_Safe		= 2,
	Mode_Drun		= 3,
	Mode_Run0		= 4,
	Mode_Run1		= 5,
	Mode_Run2		= 6,
	Mode_Run3		= 7,
	Mode_Halt0		= 8,
	Mode_Reserved	= 9,
	Mode_Stop0		= 10	
}enum_Current_Mode;

/*---------------------------------------------------------------------------*/
/***	Clock Start Key													   ***/
/*---------------------------------------------------------------------------*/
#define		ME_CTRL_KEY				0x40005AF0
#define		ME_CTRL_KEY_INVERT		0x4000A50F

/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
extern	uint8	mSysClk_Sel(void);
extern	uint8	mMcClk_Sel(void);


#endif	