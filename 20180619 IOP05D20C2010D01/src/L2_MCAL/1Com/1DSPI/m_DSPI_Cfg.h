/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_DSPI_Cfg.h
*
* @brief    Config Header file for "m_DSPI_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/27      CODER2       	   	N/A          Original
*     1.1        2012/10/11      ----			N/A          Modify SPI Config
*     1.2        2012/11/02      CODER2			N/A          Add History Comment
*     1.3        2013/03/01      CODER2			N/A          Code Simplify, Delete Reg_Bit Functions
*     1.4        2017/03/020     YCH			N/A          obc spi config
************************************************************************************************/

#ifndef _M_DSPI_CFG_H_
#define _M_DSPI_CFG_H_


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_DSPI_Drv.h"


/* *****************************************************************************
   *****************************************************************************
   Config Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Timeout for DSPI												   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_DELAY 				((uint16)0xFFFF)

/*---------------------------------------------------------------------------*/
/***	Module Used														   ***/
/*---------------------------------------------------------------------------*/
//#define		DSPI1_ENABLE
#define		DSPI3_ENABLE
//#define		DSPI0_ENABLE
//#define		DSPI2_ENABLE

/*---------------------------------------------------------------------------*/
/***	GPIO Pin Config													   ***/
/*---------------------------------------------------------------------------*/
#define		DSPI1_SCK_PIN		A6	
#define		DSPI1_SCK_PCR		(ALT1|B_OBE)
#define		DSPI1_OUT_PIN		A7
#define		DSPI1_OUT_PCR		(ALT1|B_OBE)
#define		DSPI1_IN_PIN		A8
#define		DSPI1_IN_PCR		(ALT1|B_IBE)
#define		DSPI1_CS0_PIN		A5
#define		DSPI1_CS0_PCR		(ALT1|B_OBE)
#define		DSPI1_CS1_PIN		C8
#define		DSPI1_CS1_PCR		(ALT1|B_OBE)
#define		DSPI1_CS2_PIN		D8
#define		DSPI1_CS2_PCR		(ALT1|B_OBE)

#define		DSPI3_SCK_PIN		D11	
#define		DSPI3_SCK_PCR		(ALT3|B_OBE)
#define		DSPI3_OUT_PIN		D13
#define		DSPI3_OUT_PCR		(ALT3|B_OBE)
#define		DSPI3_IN_PIN		D14
#define		DSPI3_IN_PCR		(ALT3|B_IBE)	/* PSMI */

#define		DSPI3_CS1_PIN		C12
#define		DSPI3_CS1_PCR		(ALT3|B_OBE)

#define		DSPI3_CS0_PIN		D10
#define		DSPI3_CS0_PCR		(ALT2|B_OBE)

#define		DSPI3_SCK_PSMI		0x04
#define		DSPI3_SCK_PSMI_VAL	0x01			/* D11 */
#define		DSPI3_IN_PSMI		0x05
#define		DSPI3_IN_PSMI_VAL	0x01			/* D14 */
#define		DSPI3_CS0_PSMI		0x06
#define		DSPI3_CS0_PSMI_VAL	0x01			/* D10 */

/*---------------------------------------------------------------------------*/
/***	Module Used														   ***/
/*---------------------------------------------------------------------------*/
#ifdef		DSPI0_ENABLE
	#define		DSPI0_CH0
	#define		DSPI0_CH1
	#define		DSPI0_CH2
	#define		DSPI0_CH3
	#define		DSPI0_CH4
	#define		DSPI0_CH5
	#define		DSPI0_CH6
	#define		DSPI0_CH7
#endif

/*---------------------------------------------------------------------------*/
/***	Channel Used													   ***/
/*---------------------------------------------------------------------------*/
#ifdef		DSPI1_ENABLE
	/*#define		DSPI1_CH0*/
	#define		DSPI1_CH1
	/*#define		DSPI1_CH2*/
#endif

#ifdef		DSPI2_ENABLE
	#define		DSPI2_CH0
	#define		DSPI2_CH1
	#define		DSPI2_CH2
	#define		DSPI2_CH3
#endif

#ifdef		DSPI3_ENABLE
	#define		DSPI3_CH0
	#define		DSPI3_CH1
#endif


#ifdef	DSPI0_ENABLE
	/* Interrupt Source Enalbed */
	#define		DSPI0_INTC_ENABLE

/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 0 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH0
		/* Transmit width */
		#define		DSPI0_CH0_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH0_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH0_DBR	DBR_OFF
		#define		DSPI0_CH0_PBR	0x0
		#define		DSPI0_CH0_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH0_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH0_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH0_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH0_CONFIG	(	(DSPI0_CH0_DBR<<31)		| \
										 	(DSPI0_CH0_WIDTH<<27)	| \
										 	(DSPI0_CH0_SPOL<<26)	| \
										 	(DSPI0_CH0_SPHA<<25)	| \
											(DSPI0_CH0_SHIFT<<24)	| \
											(DSPI0_CH0_PBR<<16)		| \
											(DSPI0_CH0_BR<<0)		| \
											(DSPI0_CH0_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 1 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH1
		/* Transmit width */
		#define		DSPI0_CH1_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH1_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH1_DBR	DBR_OFF
		#define		DSPI0_CH1_PBR	0x0
		#define		DSPI0_CH1_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH1_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH1_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH1_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH1_CONFIG	(	(DSPI0_CH1_DBR<<31)		| \
										 	(DSPI0_CH1_WIDTH<<27)	| \
										 	(DSPI0_CH1_SPOL<<26)	| \
										 	(DSPI0_CH1_SPHA<<25)	| \
											(DSPI0_CH1_SHIFT<<24)	| \
											(DSPI0_CH1_PBR<<16)		| \
											(DSPI0_CH1_BR<<0)		| \
											(DSPI0_CH1_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 2 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH2
		/* Transmit width */
		#define		DSPI0_CH2_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH2_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH2_DBR	DBR_OFF
		#define		DSPI0_CH2_PBR	0x0
		#define		DSPI0_CH2_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH2_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH2_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH2_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH2_CONFIG	(	(DSPI0_CH2_DBR<<31)		| \
										 	(DSPI0_CH2_WIDTH<<27)	| \
										 	(DSPI0_CH2_SPOL<<26)	| \
										 	(DSPI0_CH2_SPHA<<25)	| \
											(DSPI0_CH2_SHIFT<<24)	| \
											(DSPI0_CH2_PBR<<16)		| \
											(DSPI0_CH2_BR<<0)		| \
											(DSPI0_CH2_EDGE)	)
	#endif	
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 3 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH3
		/* Transmit width */
		#define		DSPI0_CH3_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH3_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH3_DBR	DBR_OFF
		#define		DSPI0_CH3_PBR	0x0
		#define		DSPI0_CH3_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH3_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH3_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH3_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH3_CONFIG	(	(DSPI0_CH3_DBR<<31)		| \
										 	(DSPI0_CH3_WIDTH<<27)	| \
										 	(DSPI0_CH3_SPOL<<26)	| \
										 	(DSPI0_CH3_SPHA<<25)	| \
											(DSPI0_CH3_SHIFT<<24)	| \
											(DSPI0_CH3_PBR<<16)		| \
											(DSPI0_CH3_BR<<0)		| \
											(DSPI0_CH3_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 4 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH4
		/* Transmit width */
		#define		DSPI0_CH4_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH4_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH4_DBR	DBR_OFF
		#define		DSPI0_CH4_PBR	0x0
		#define		DSPI0_CH4_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH4_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH4_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH4_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH4_CONFIG	(	(DSPI0_CH4_DBR<<31)		| \
										 	(DSPI0_CH4_WIDTH<<27)	| \
										 	(DSPI0_CH4_SPOL<<26)	| \
										 	(DSPI0_CH4_SPHA<<25)	| \
											(DSPI0_CH4_SHIFT<<24)	| \
											(DSPI0_CH4_PBR<<16)		| \
											(DSPI0_CH4_BR<<0)		| \
											(DSPI0_CH4_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 5 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH5
		/* Transmit width */
		#define		DSPI0_CH5_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH5_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH5_DBR	DBR_OFF
		#define		DSPI0_CH5_PBR	0x0
		#define		DSPI0_CH5_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH5_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH5_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH5_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH5_CONFIG	(	(DSPI0_CH5_DBR<<31)		| \
										 	(DSPI0_CH5_WIDTH<<27)	| \
										 	(DSPI0_CH5_SPOL<<26)	| \
										 	(DSPI0_CH5_SPHA<<25)	| \
											(DSPI0_CH5_SHIFT<<24)	| \
											(DSPI0_CH5_PBR<<16)		| \
											(DSPI0_CH5_BR<<0)		| \
											(DSPI0_CH5_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 6 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH6
		/* Transmit width */
		#define		DSPI0_CH6_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH6_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH6_DBR	DBR_OFF
		#define		DSPI0_CH6_PBR	0x0
		#define		DSPI0_CH6_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH6_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH6_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH6_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH6_CONFIG	(	(DSPI0_CH6_DBR<<31)		| \
										 	(DSPI0_CH6_WIDTH<<27)	| \
										 	(DSPI0_CH6_SPOL<<26)	| \
										 	(DSPI0_CH6_SPHA<<25)	| \
											(DSPI0_CH6_SHIFT<<24)	| \
											(DSPI0_CH6_PBR<<16)		| \
											(DSPI0_CH6_BR<<0)		| \
											(DSPI0_CH6_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 0 , Channel 7 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI0_CH7
		/* Transmit width */
		#define		DSPI0_CH7_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI0_CH7_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI0_CH7_DBR	DBR_OFF
		#define		DSPI0_CH7_PBR	0x0
		#define		DSPI0_CH7_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI0_CH7_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI0_CH7_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI0_CH7_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI0_CH7_CONFIG	(	(DSPI0_CH7_DBR<<31)		| \
										 	(DSPI0_CH7_WIDTH<<27)	| \
										 	(DSPI0_CH7_SPOL<<26)	| \
										 	(DSPI0_CH7_SPHA<<25)	| \
											(DSPI0_CH7_SHIFT<<24)	| \
											(DSPI0_CH7_PBR<<16)		| \
											(DSPI0_CH7_BR<<0)		| \
											(DSPI0_CH7_EDGE)	)
	#endif
#endif

#ifdef	DSPI1_ENABLE
	/* Interrupt Source Enalbed */
	/* #define		DSPI1_INTC_ENABLE */

/*---------------------------------------------------------------------------*/
/***	Module 1 , Channel 0 Config										   ***/
/*---------------------------------------------------------------------------*/	
	#ifdef	DSPI1_CH0
		/* Transmit width */
		#define		DSPI1_CH0_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI1_CH0_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI1_CH0_DBR	DBR_OFF
		#define		DSPI1_CH0_PBR	0x0
		#define		DSPI1_CH0_BR	0x03 		/* 4Mhz */
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI1_CH0_EDGE	((0<<22)|(0<<20)|(2<<18)|(2<<12)|(2<<8)|(9<<4)) /*t_DT = 80us @ sys_clc= 64Mhz*/
		
        /* #define		DSPI1_CH0_EDGE	((0<<22)|(0<<20)|(1<<18)|(2<<12)|(2<<8)|(9<<4))  */ /*t_DT = 48us @ sys_clc= 64Mhz*/		
		/* SPHA	&&	SPOL */
		#define		DSPI1_CH0_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI1_CH0_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI1_CH0_CONFIG	(	(DSPI1_CH0_DBR<<31)		| \
										 	(DSPI1_CH0_WIDTH<<27)	| \
										 	(DSPI1_CH0_SPOL<<26)	| \
										 	(DSPI1_CH0_SPHA<<25)	| \
											(DSPI1_CH0_SHIFT<<24)	| \
											(DSPI1_CH0_PBR<<16)		| \
											(DSPI1_CH0_BR<<0)		| \
											(DSPI1_CH0_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 1 , Channel 1 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI1_CH1
		/* Transmit width */
		#define		DSPI1_CH1_WIDTH		TRANS_WIDTH_16	/* TRANS_WIDTH_8 */
		/* Shift MSB & LSB */
		#define		DSPI1_CH1_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI1_CH1_DBR	DBR_OFF
		#define		DSPI1_CH1_PBR	0x0
		#define		DSPI1_CH1_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI1_CH1_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI1_CH1_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI1_CH1_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI1_CH1_CONFIG	(	(DSPI1_CH1_DBR<<31)		| \
										 	(DSPI1_CH1_WIDTH<<27)	| \
										 	(DSPI1_CH1_SPOL<<26)	| \
										 	(DSPI1_CH1_SPHA<<25)	| \
											(DSPI1_CH1_SHIFT<<24)	| \
											(DSPI1_CH1_PBR<<16)		| \
											(DSPI1_CH1_BR<<0)		| \
											(DSPI1_CH1_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 1 , Channel 2 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI1_CH2
		/* Transmit width */
		#define		DSPI1_CH2_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI1_CH2_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI1_CH2_DBR	DBR_OFF
		#define		DSPI1_CH2_PBR	0x0
		#define		DSPI1_CH2_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI1_CH2_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI1_CH2_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI1_CH2_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI1_CH2_CONFIG	(	(DSPI1_CH2_DBR<<31)		| \
										 	(DSPI1_CH2_WIDTH<<27)	| \
										 	(DSPI1_CH2_SPOL<<26)	| \
										 	(DSPI1_CH2_SPHA<<25)	| \
											(DSPI1_CH2_SHIFT<<24)	| \
											(DSPI1_CH2_PBR<<16)		| \
											(DSPI1_CH2_BR<<0)		| \
											(DSPI1_CH2_EDGE)	)
	#endif	
	
/*---------------------------------------------------------------------------*/
/***	Module 1 , Channel 3 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI1_CH3
		/* Transmit width */
		#define		DSPI1_CH3_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI1_CH3_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI1_CH3_DBR	DBR_OFF
		#define		DSPI1_CH3_PBR	0x0
		#define		DSPI1_CH3_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI1_CH3_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI1_CH3_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI1_CH3_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI1_CH3_CONFIG	(	(DSPI1_CH3_DBR<<31)		| \
										 	(DSPI1_CH3_WIDTH<<27)	| \
										 	(DSPI1_CH3_SPOL<<26)	| \
										 	(DSPI1_CH3_SPHA<<25)	| \
											(DSPI1_CH3_SHIFT<<24)	| \
											(DSPI1_CH3_PBR<<16)		| \
											(DSPI1_CH3_BR<<0)		| \
											(DSPI1_CH3_EDGE)	)
	#endif
	
#endif


#ifdef	DSPI2_ENABLE
	/* Interrupt Source Enalbed */
	#define		DSPI2_INTC_ENABLE

/*---------------------------------------------------------------------------*/
/***	Module 2 , Channel 0 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI2_CH0
		/* Transmit width */
		#define		DSPI2_CH0_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI2_CH0_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI2_CH0_DBR	DBR_OFF
		#define		DSPI2_CH0_PBR	0x0
		#define		DSPI2_CH0_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI2_CH0_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI2_CH0_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI2_CH0_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI2_CH0_CONFIG	(	(DSPI2_CH0_DBR<<31)		| \
										 	(DSPI2_CH0_WIDTH<<27)	| \
										 	(DSPI2_CH0_SPOL<<26)	| \
										 	(DSPI2_CH0_SPHA<<25)	| \
											(DSPI2_CH0_SHIFT<<24)	| \
											(DSPI2_CH0_PBR<<16)		| \
											(DSPI2_CH0_BR<<0)		| \
											(DSPI2_CH0_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 2 , Channel 1 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI2_CH1
		/* Transmit width */
		#define		DSPI2_CH1_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI2_CH1_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI2_CH1_DBR	DBR_OFF
		#define		DSPI2_CH1_PBR	0x0
		#define		DSPI2_CH1_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI2_CH1_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI2_CH1_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI2_CH1_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI2_CH1_CONFIG	(	(DSPI2_CH1_DBR<<31)		| \
										 	(DSPI2_CH1_WIDTH<<27)	| \
										 	(DSPI2_CH1_SPOL<<26)	| \
										 	(DSPI2_CH1_SPHA<<25)	| \
											(DSPI2_CH1_SHIFT<<24)	| \
											(DSPI2_CH1_PBR<<16)		| \
											(DSPI2_CH1_BR<<0)		| \
											(DSPI2_CH1_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 2 , Channel 2 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI2_CH2
		/* Transmit width */
		#define		DSPI2_CH2_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI2_CH2_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI2_CH2_DBR	DBR_OFF
		#define		DSPI2_CH2_PBR	0x0
		#define		DSPI2_CH2_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI2_CH2_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI2_CH2_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI2_CH2_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI2_CH2_CONFIG	(	(DSPI2_CH2_DBR<<31)		| \
										 	(DSPI2_CH2_WIDTH<<27)	| \
										 	(DSPI2_CH2_SPOL<<26)	| \
										 	(DSPI2_CH2_SPHA<<25)	| \
											(DSPI2_CH2_SHIFT<<24)	| \
											(DSPI2_CH2_PBR<<16)		| \
											(DSPI2_CH2_BR<<0)		| \
											(DSPI2_CH2_EDGE)	)
	#endif	
	
/*---------------------------------------------------------------------------*/
/***	Module 2 , Channel 3 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI2_CH3
		/* Transmit width */
		#define		DSPI2_CH3_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI2_CH3_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI2_CH3_DBR	DBR_OFF
		#define		DSPI2_CH3_PBR	0x0
		#define		DSPI2_CH3_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI2_CH3_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI2_CH3_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI2_CH3_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI2_CH3_CONFIG	(	(DSPI2_CH3_DBR<<31)		| \
										 	(DSPI2_CH3_WIDTH<<27)	| \
										 	(DSPI2_CH3_SPOL<<26)	| \
										 	(DSPI2_CH3_SPHA<<25)	| \
											(DSPI2_CH3_SHIFT<<24)	| \
											(DSPI2_CH3_PBR<<16)		| \
											(DSPI2_CH3_BR<<0)		| \
											(DSPI2_CH3_EDGE)	)
	#endif
	
#endif


#ifdef	DSPI3_ENABLE
	/* Interrupt Source Enalbed */
	/* #define		DSPI3_INTC_ENABLE */

/*---------------------------------------------------------------------------*/
/***	Module 3 , Channel 0 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI3_CH0
		/* Transmit width */
		#define		DSPI3_CH0_WIDTH		TRANS_WIDTH_16
		/* Shift MSB & LSB */
		#define		DSPI3_CH0_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI3_CH0_DBR	DBR_OFF
		#define		DSPI3_CH0_PBR	0x0
		#define		DSPI3_CH0_BR	0x4  /* 3 as 4MHz,4 as 2MHz,5 as 1MHz,UJA1076 max 3.125MHz */
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI3_CH0_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI3_CH0_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI3_CH0_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI3_CH0_CONFIG	(	(DSPI3_CH0_DBR<<31)		| \
										 	(DSPI3_CH0_WIDTH<<27)	| \
										 	(DSPI3_CH0_SPOL<<26)	| \
										 	(DSPI3_CH0_SPHA<<25)	| \
											(DSPI3_CH0_SHIFT<<24)	| \
											(DSPI3_CH0_PBR<<16)		| \
											(DSPI3_CH0_BR<<0)		| \
											(DSPI3_CH0_EDGE)	)
	#endif

/*---------------------------------------------------------------------------*/
/***	Module 3 , Channel 1 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI3_CH1
		/* Transmit width */
		#define		DSPI3_CH1_WIDTH		TRANS_WIDTH_16
		/* Shift MSB & LSB */
		#define		DSPI3_CH1_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI3_CH1_DBR	DBR_OFF
		#define		DSPI3_CH1_PBR	0x0
		#define		DSPI3_CH1_BR	0x2  /* 2~8MHz,3~4MHz,5~1MHz, L9907 Max8MHz */
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI3_CH1_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI3_CH1_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI3_CH1_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI3_CH1_CONFIG	(	(DSPI3_CH1_DBR<<31)		| \
										 	(DSPI3_CH1_WIDTH<<27)	| \
										 	(DSPI3_CH1_SPOL<<26)	| \
										 	(DSPI3_CH1_SPHA<<25)	| \
											(DSPI3_CH1_SHIFT<<24)	| \
											(DSPI3_CH1_PBR<<16)		| \
											(DSPI3_CH1_BR<<0)		| \
											(DSPI3_CH1_EDGE)	)
	#endif
	
/*---------------------------------------------------------------------------*/
/***	Module 3 , Channel 2 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI3_CH2
		/* Transmit width */
		#define		DSPI3_CH2_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI3_CH2_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI3_CH2_DBR	DBR_OFF
		#define		DSPI3_CH2_PBR	0x0
		#define		DSPI3_CH2_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI3_CH2_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI3_CH2_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI3_CH2_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI3_CH2_CONFIG	(	(DSPI3_CH2_DBR<<31)		| \
										 	(DSPI3_CH2_WIDTH<<27)	| \
										 	(DSPI3_CH2_SPOL<<26)	| \
										 	(DSPI3_CH2_SPHA<<25)	| \
											(DSPI3_CH2_SHIFT<<24)	| \
											(DSPI3_CH2_PBR<<16)		| \
											(DSPI3_CH2_BR<<0)		| \
											(DSPI3_CH2_EDGE)	)
	#endif	
	
/*---------------------------------------------------------------------------*/
/***	Module 3 , Channel 3 Config										   ***/
/*---------------------------------------------------------------------------*/
	#ifdef	DSPI3_CH3
		/* Transmit width */
		#define		DSPI3_CH3_WIDTH		TRANS_WIDTH_8
		/* Shift MSB & LSB */
		#define		DSPI3_CH3_SHIFT		SPI_SYS_SHIFT_MSB
		/* BAUD	= fSYS * (1+DBR) / PBR / BR ; 		[2,3,5,7] & (2^BR) */
		#define		DSPI3_CH3_DBR	DBR_OFF
		#define		DSPI3_CH3_PBR	0x0
		#define		DSPI3_CH3_BR	0x5
		/* Edge Delay	PCSSCK 22; PASC 20; PDT 18; CSSCK 12; ASC 8; DT 4; */
		/* tDelay = 1 / fSYS * PCSSCK * CSSCK ; 	[1,3,5,7] & ( 2^(CSSCK+1) ) */
		#define		DSPI3_CH3_EDGE	((0<<22)|(0<<20)|(0<<18)|(2<<12)|(2<<8)|(5<<4))
		/* SPHA	&&	SPOL */
		#define		DSPI3_CH3_SPHA	SPI_SCK_PHASE_ODD
		#define		DSPI3_CH3_SPOL	SPI_SCK_POLARITY_LOW
		/* All Config */
		#define		DSPI3_CH3_CONFIG	(	(DSPI3_CH3_DBR<<31)		| \
										 	(DSPI3_CH3_WIDTH<<27)	| \
										 	(DSPI3_CH3_SPOL<<26)	| \
										 	(DSPI3_CH3_SPHA<<25)	| \
											(DSPI3_CH3_SHIFT<<24)	| \
											(DSPI3_CH3_PBR<<16)		| \
											(DSPI3_CH3_BR<<0)		| \
											(DSPI3_CH3_EDGE)	)
	#endif
	
#endif


#endif	

