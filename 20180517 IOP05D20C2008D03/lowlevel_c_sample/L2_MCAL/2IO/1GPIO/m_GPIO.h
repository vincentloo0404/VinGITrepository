/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_GPIO.h
*
* @brief    Drive Header file for "m_GPIO.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.2        2016/04/06      jiaoyu			N/A          deliver to ChuangQu
*     
************************************************************************************************/
#ifndef _M_GPIO_H_
#define _M_GPIO_H_
/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"MPC560xP.h"
#include  	"Std_Types.h"

/* *****************************************************************************
   *****************************************************************************
   macro definition
   *****************************************************************************
   ***************************************************************************** */
/* Config Value Macro PCR[n] */
/* Pad Configuration Registers (PCR[0:107])
            0     1     2     3     4    5     6     7     8     9     10    11    12    13    14    15
         +-----+-----+-----+-----+----------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
     R   |  0  |     |     |  0  |          |     |     |  0  |  0  |     |  0  |  0  |     |     |     |
         +-----+ SMC | APC +-----+  PA[1:0] | OBE | IBE +-----+-----+ ODE +-----+-----+ SRC | WPE | WPS |
     W   |  -  |     |     |  -  |          |     |     |  -  |  -  |     |  -  |  -  |     |     |     |
         +-----+-----+-----+-----+----------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
   ReSet    0     0     0     0     0    0     0     0     0     0     0     0     0     0     0     0
*/  
/*---------------------------------------------------------------------------*/
/***	((SME<<14)| (APC<< 13)| (PA<<10)| (OBE<<9)| (IBE <<8 )|  	       ***/
/***	(ODE<<5)|(SRC<<2)| (WPE<<1)| (WPS))                                ***/
/*---------------------------------------------------------------------------*/
#define		B_SME				(1<<14)
#define		B_APC				(1<<13)
#define		B_PA				(0<<10)
#define		B_OBE				(1<<9)
#define		B_IBE				(1<<8)
#define		B_ODE				(1<<5)
#define		B_SRC				(1<<2)
#define		B_WPE				(1<<1)
#define		B_WPS				(1<<0)

/*---------------------------------------------------------------------------*/
/***	PA SEL                                                             ***/
/*---------------------------------------------------------------------------*/
#define		GPIO				(0<<10)
#define		ALT1				(1<<10)
#define		ALT2				(2<<10)
#define		ALT3				(3<<10)

/*---------------------------------------------------------------------------*/
/***	PCR In/Out Config                                                  ***/
/*---------------------------------------------------------------------------*/
#define		PCR_PIN_OUT			(GPIO|B_OBE|B_ODE)
#define		PCR_PIN_IN			(GPIO|B_IBE)
#define		PCR_PIN_IN_OUT		(GPIO|B_OBE|B_IBE|B_ODE)
#define     PCR_PIN_OUT_WPE     (GPIO|B_OBE|B_WPE)
#define     PCR_PIN_OUT_ODE     (GPIO|B_OBE|B_ODE)

/*---------------------------------------------------------------------------*/
/***	Port A			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		PCR_A0				(B_PA|B_OBE|B_ODE)
#define		PCR_A1				(B_PA|B_OBE|B_ODE)
#define		PCR_A2				(B_PA|B_OBE|B_ODE)
#define		PCR_A3				(B_PA|B_OBE|B_ODE)
#define		PCR_A4				(B_PA|B_OBE|B_ODE)
#define		PCR_A5				(B_PA|B_OBE|B_ODE)
#define		PCR_A6				(B_PA|B_OBE|B_ODE)
#define		PCR_A7				(B_PA|B_OBE|B_ODE)
#define		PCR_A8				(B_PA|B_OBE|B_ODE)
#define		PCR_A9				(B_PA|B_OBE|B_ODE)
#define		PCR_A10				(B_PA|B_OBE|B_ODE)
#define		PCR_A11				(B_PA|B_OBE|B_ODE)
#define		PCR_A12				(B_PA|B_OBE|B_ODE)
#define		PCR_A13				(B_PA|B_OBE|B_ODE)
#define		PCR_A14				(B_PA|B_OBE|B_ODE)
#define		PCR_A15				(B_PA|B_OBE|B_ODE)

/*---------------------------------------------------------------------------*/
/***	Port B			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		PCR_B0				(B_PA|B_OBE|B_ODE)
#define		PCR_B1				(B_PA|B_OBE|B_ODE)
#define		PCR_B2				(B_PA|B_OBE|B_ODE)
#define		PCR_B3				(B_PA|B_OBE|B_ODE)
#define		PCR_B4				(B_PA|B_OBE|B_ODE)
#define		PCR_B5				(B_PA|B_OBE|B_ODE)
#define		PCR_B6				(B_PA|B_OBE|B_ODE)
#define		PCR_B7				(B_PA|B_OBE|B_ODE)
#define		PCR_B8				(B_PA|B_OBE|B_ODE)
#define		PCR_B9				(B_PA|B_OBE|B_ODE)
#define		PCR_B10				(B_PA|B_OBE|B_ODE)
#define		PCR_B11				(B_PA|B_OBE|B_ODE)
#define		PCR_B12				(B_PA|B_OBE|B_ODE)
#define		PCR_B13				(B_PA|B_OBE|B_ODE)
#define		PCR_B14				(B_PA|B_OBE|B_ODE)
#define		PCR_B15				(B_PA|B_OBE|B_ODE)

/*---------------------------------------------------------------------------*/
/***	Port C			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		PCR_C0				(B_PA|B_OBE|B_ODE)
#define		PCR_C1				(B_PA|B_OBE|B_ODE)
#define		PCR_C2				(B_PA|B_OBE|B_ODE)
#define		PCR_C3				(B_PA|B_OBE|B_ODE)
#define		PCR_C4				(B_PA|B_OBE|B_ODE)
#define		PCR_C5				(B_PA|B_OBE|B_ODE)
#define		PCR_C6				(B_PA|B_OBE|B_ODE)
#define		PCR_C7				(B_PA|B_OBE|B_ODE)
#define		PCR_C8				(B_PA|B_OBE|B_ODE)
#define		PCR_C9				(B_PA|B_OBE|B_ODE)
#define		PCR_C10				(B_PA|B_OBE|B_ODE)
#define		PCR_C11				(B_PA|B_OBE|B_ODE)
#define		PCR_C12				(B_PA|B_OBE|B_ODE)
#define		PCR_C13				(B_PA|B_OBE|B_ODE)
#define		PCR_C14				(B_PA|B_OBE|B_ODE)
#define		PCR_C15				(B_PA|B_OBE|B_ODE)

/*---------------------------------------------------------------------------*/
/***	Port D			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		PCR_D0				(B_PA|B_IBE)
#define		PCR_D1				(B_PA|B_IBE)
#define		PCR_D2				(B_PA|B_IBE)
#define		PCR_D3				(B_PA|B_IBE)
#define		PCR_D4				(B_PA|B_OBE|B_ODE)
#define		PCR_D5				(B_PA|B_OBE|B_ODE)
#define		PCR_D6				(B_PA|B_OBE|B_ODE)
#define		PCR_D7				(B_PA|B_OBE|B_ODE)
#define		PCR_D8				(B_PA|B_OBE|B_ODE)
#define		PCR_D9				(B_PA|B_OBE|B_ODE)
#define		PCR_D10				(B_PA|B_OBE|B_ODE)
#define		PCR_D11				(B_PA|B_OBE|B_ODE)
#define		PCR_D12				(B_PA|B_OBE|B_ODE)
#define		PCR_D13				(B_PA|B_OBE|B_ODE)
#define		PCR_D14				(B_PA|B_OBE|B_ODE)
#define		PCR_D15				(B_PA|B_OBE|B_ODE)

/*---------------------------------------------------------------------------*/
/***	Port E			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		PCR_E0				(B_PA|B_OBE|B_ODE)
#define		PCR_E1				(B_PA|B_OBE|B_ODE)
#define		PCR_E2				(B_PA|B_OBE|B_ODE)
#define		PCR_E3				(B_PA|B_OBE|B_ODE)
#define		PCR_E4				(B_PA|B_OBE|B_ODE)
#define		PCR_E5				(B_PA|B_OBE|B_ODE)
#define		PCR_E6				(B_PA|B_OBE|B_ODE)
#define		PCR_E7				(B_PA|B_OBE|B_ODE)
#define		PCR_E8				(B_PA|B_OBE|B_ODE)
#define		PCR_E9				(B_PA|B_OBE|B_ODE)
#define		PCR_E10				(B_PA|B_OBE|B_ODE)
#define		PCR_E11				(B_PA|B_OBE|B_ODE)
#define		PCR_E12				(B_PA|B_OBE|B_ODE)
#define		PCR_E13				(B_PA|B_OBE|B_ODE)
#define		PCR_E14				(B_PA|B_OBE|B_ODE)
#define		PCR_E15				(B_PA|B_OBE|B_ODE)

/*---------------------------------------------------------------------------*/
/***	Port F			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		PCR_F0				(B_PA|B_OBE|B_ODE)
#define		PCR_F1				(B_PA|B_OBE|B_ODE)
#define		PCR_F2				(B_PA|B_OBE|B_ODE)
#define		PCR_F3				(B_PA|B_OBE|B_ODE)
#define		PCR_F4				(B_PA|B_OBE|B_ODE)
#define		PCR_F5				(B_PA|B_OBE|B_ODE)
#define		PCR_F6				(B_PA|B_OBE|B_ODE)
#define		PCR_F7				(B_PA|B_OBE|B_ODE)
#define		PCR_F8				(B_PA|B_OBE|B_ODE)
#define		PCR_F9				(B_PA|B_OBE|B_ODE)
#define		PCR_F10				(B_PA|B_OBE|B_ODE)
#define		PCR_F11				(B_PA|B_OBE|B_ODE)
#define		PCR_F12				(B_PA|B_OBE|B_ODE)
#define		PCR_F13				(B_PA|B_OBE|B_ODE)
#define		PCR_F14				(B_PA|B_OBE|B_ODE)
#define		PCR_F15				(B_PA|B_OBE|B_ODE)

/*---------------------------------------------------------------------------*/
/***	Port G			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		PCR_G0				(B_PA|B_OBE|B_ODE)
#define		PCR_G1				(B_PA|B_OBE|B_ODE)
#define		PCR_G2				(B_PA|B_OBE|B_ODE)
#define		PCR_G3				(B_PA|B_OBE|B_ODE)
#define		PCR_G4				(B_PA|B_OBE|B_ODE)
#define		PCR_G5				(B_PA|B_OBE|B_ODE)
#define		PCR_G6				(B_PA|B_OBE|B_ODE)
#define		PCR_G7				(B_PA|B_OBE|B_ODE)
#define		PCR_G8				(B_PA|B_OBE|B_ODE)
#define		PCR_G9				(B_PA|B_OBE|B_ODE)
#define		PCR_G10				(B_PA|B_OBE|B_ODE)
#define		PCR_G11				(B_PA|B_OBE|B_ODE)
/* End of Config Value Macro PCR[n] */

/*---------------------------------------------------------------------------*/
/***	Config Instruction Macro PCR[n]			                           ***/
/*---------------------------------------------------------------------------*/
#define		PCR_CFG(PORT, PCR_VAL)	(SIU.PCR[PORT].R  = (PCR_VAL))

/*---------------------------------------------------------------------------*/
/***	Config Port InitValue Macro PCR[n]		                           ***/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/***	Port A			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		A0_INIT_OUT				LOW
#define		A1_INIT_OUT				LOW
#define		A2_INIT_OUT				LOW
#define		A3_INIT_OUT				LOW
#define		A4_INIT_OUT				LOW
#define		A5_INIT_OUT				LOW
#define		A6_INIT_OUT				LOW
#define		A7_INIT_OUT				LOW
#define		A8_INIT_OUT				LOW
#define		A9_INIT_OUT				LOW
#define		A10_INIT_OUT			LOW
#define		A11_INIT_OUT			LOW
#define		A12_INIT_OUT			LOW
#define		A13_INIT_OUT			LOW
#define		A14_INIT_OUT			LOW
#define		A15_INIT_OUT			LOW

/*---------------------------------------------------------------------------*/
/***	Port B			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		B0_INIT_OUT				LOW
#define		B1_INIT_OUT				LOW
#define		B2_INIT_OUT				LOW
#define		B3_INIT_OUT				LOW
#define		B4_INIT_OUT				LOW
#define		B5_INIT_OUT				LOW
#define		B6_INIT_OUT				LOW
#define		B7_INIT_OUT				LOW
#define		B8_INIT_OUT				LOW
#define		B9_INIT_OUT				LOW
#define		B10_INIT_OUT			LOW
#define		B11_INIT_OUT			LOW
#define		B12_INIT_OUT			LOW
#define		B13_INIT_OUT			LOW
#define		B14_INIT_OUT			LOW
#define		B15_INIT_OUT			LOW

/*---------------------------------------------------------------------------*/
/***	Port C			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		C0_INIT_OUT				LOW
#define		C1_INIT_OUT				LOW
#define		C2_INIT_OUT				LOW
#define		C3_INIT_OUT				LOW
#define		C4_INIT_OUT				LOW
#define		C5_INIT_OUT				LOW
#define		C6_INIT_OUT				LOW
#define		C7_INIT_OUT				LOW
#define		C8_INIT_OUT				LOW
#define		C9_INIT_OUT				LOW
#define		C10_INIT_OUT			LOW
#define		C11_INIT_OUT			LOW
#define		C12_INIT_OUT			LOW
#define		C13_INIT_OUT			LOW
#define		C14_INIT_OUT			LOW
#define		C15_INIT_OUT			LOW

/*---------------------------------------------------------------------------*/
/***	Port D			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		D0_INIT_OUT				LOW
#define		D1_INIT_OUT				LOW
#define		D2_INIT_OUT				LOW
#define		D3_INIT_OUT				LOW
#define		D4_INIT_OUT				HIGH
#define		D5_INIT_OUT				HIGH
#define		D6_INIT_OUT				HIGH
#define		D7_INIT_OUT				HIGH
#define		D8_INIT_OUT				LOW
#define		D9_INIT_OUT				LOW
#define		D10_INIT_OUT			LOW
#define		D11_INIT_OUT			LOW
#define		D12_INIT_OUT			LOW
#define		D13_INIT_OUT			LOW
#define		D14_INIT_OUT			LOW
#define		D15_INIT_OUT			LOW

/*---------------------------------------------------------------------------*/
/***	Port E			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		E0_INIT_OUT				LOW
#define		E1_INIT_OUT				LOW
#define		E2_INIT_OUT				LOW
#define		E3_INIT_OUT				LOW
#define		E4_INIT_OUT				LOW
#define		E5_INIT_OUT				LOW
#define		E6_INIT_OUT				LOW
#define		E7_INIT_OUT				LOW
#define		E8_INIT_OUT				LOW
#define		E9_INIT_OUT				LOW
#define		E10_INIT_OUT			LOW
#define		E11_INIT_OUT			LOW
#define		E12_INIT_OUT			LOW
#define		E13_INIT_OUT			LOW
#define		E14_INIT_OUT			LOW
#define		E15_INIT_OUT			LOW

/*---------------------------------------------------------------------------*/
/***	Port F			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		F0_INIT_OUT				LOW
#define		F1_INIT_OUT				LOW
#define		F2_INIT_OUT				LOW
#define		F3_INIT_OUT				LOW
#define		F4_INIT_OUT				LOW
#define		F5_INIT_OUT				LOW
#define		F6_INIT_OUT				LOW
#define		F7_INIT_OUT				LOW
#define		F8_INIT_OUT				LOW
#define		F9_INIT_OUT				LOW
#define		F10_INIT_OUT			LOW
#define		F11_INIT_OUT			LOW
#define		F12_INIT_OUT			LOW
#define		F13_INIT_OUT			LOW
#define		F14_INIT_OUT			LOW
#define		F15_INIT_OUT			LOW

/*---------------------------------------------------------------------------*/
/***	Port G			                                                   ***/
/*---------------------------------------------------------------------------*/
#define		G0_INIT_OUT				LOW
#define		G1_INIT_OUT				LOW
#define		G2_INIT_OUT				LOW
#define		G3_INIT_OUT				LOW
#define		G4_INIT_OUT				LOW
#define		G5_INIT_OUT				LOW
#define		G6_INIT_OUT				LOW
#define		G7_INIT_OUT				LOW
#define		G8_INIT_OUT				LOW
#define		G9_INIT_OUT				LOW
#define		G10_INIT_OUT			LOW
#define		G11_INIT_OUT			LOW

/*---------------------------------------------------------------------------*/
/***	Port PCR Output Config                                             ***/
/*---------------------------------------------------------------------------*/
#define		PCR_OUT(PORT, OUT_VAL)	(SIU.GPDO[PORT].B.PDO = (OUT_VAL))

/*---------------------------------------------------------------------------*/
/***	Pad Name definition                                                                       ***/
/*---------------------------------------------------------------------------*/
#define		PORT_All_CNT	108

/*---------------------------------------------------------------------------*/
/***	Pad A		fully available on 100-pin and 144-pin                 ***/
/*---------------------------------------------------------------------------*/
#define		PORT_A_CNT	16
#define		A0			0
#define		A1			1
#define		A2			2
#define		A3			3
#define		A4			4
#define		A5			5
#define		A6			6
#define		A7			7
#define		A8			8
#define		A9			9
#define		A10			10
#define		A11			11
#define		A12			12
#define		A13			13
#define		A14			14
#define		A15			15

/*---------------------------------------------------------------------------*/
/***	Pad B		fully available on 100-pin and 144-pin                 ***/
/*---------------------------------------------------------------------------*/
#define		PORT_B_CNT	16
#define		B0			16
#define		B1			17
#define		B2			18
#define		B3			19
#define		B4			20
#define		B5			21
#define		B6			22
#define		B7			23
#define		B8			24
#define		B9			25
#define		B10			26
#define		B11			27
#define		B12			28
#define		B13			29
#define		B14			30
#define		B15			31

/*---------------------------------------------------------------------------*/
/***	Pad C		fully available on 100-pin and 144-pin                 ***/
/*---------------------------------------------------------------------------*/
#define		PORT_C_CNT	16
#define		C0			32
#define		C1			33
#define		C2			34
#define		C3			35
#define		C4			36
#define		C5			37
#define		C6			38
#define		C7			39
#define		C8			40
#define		C9			41
#define		C10			42
#define		C11			43
#define		C12			44
#define		C13			45
#define		C14			46
#define		C15			47

/*---------------------------------------------------------------------------*/
/***	Pad D		fully available on 100-pin and 144-pin                 ***/
/*---------------------------------------------------------------------------*/
#define		PORT_D_CNT	16
#define		D0			48
#define		D1			49
#define		D2			50
#define		D3			51
#define		D4			52
#define		D5			53
#define		D6			54
#define		D7			55
#define		D8			56
#define		D9			57
#define		D10			58
#define		D11			59
#define		D12			60
#define		D13			61
#define		D14			62
#define		D15			63

/*---------------------------------------------------------------------------*/
/***	Pad E	fully available on 144-pin; E[0,1,2] available on 100-pin  ***/
/*---------------------------------------------------------------------------*/
#define		PORT_E_CNT	16
#define		E0			64
#define		E1			65
#define		E2			66
#define		E3			67
#define		E4			68
#define		E5			69
#define		E6			70
#define		E7			71
#define		E8			72
#define		E9			73
#define		E10			74
#define		E11			75
#define		E12			76
#define		E13			77
#define		E14			78
#define		E15			79

/*---------------------------------------------------------------------------*/
/***	Pad F		fully available on 144-pin							   ***/
/*---------------------------------------------------------------------------*/
#define		PORT_F_CNT	16
#define		F0			80
#define		F1			81
#define		F2			82
#define		F3			83
#define		F4			84
#define		F5			85
#define		F6			86
#define		F7			87
#define		F8			88
#define		F9			89
#define		F10			90
#define		F11			91
#define		F12			92
#define		F13			93
#define		F14			94
#define		F15			95

/*---------------------------------------------------------------------------*/
/***	Pad G		fully available on 144-pin							   ***/
/*---------------------------------------------------------------------------*/
#define		PORT_G_CNT	12
#define		G0			96
#define		G1			97
#define		G2			98
#define		G3			99
#define		G4			100
#define		G5			101
#define		G6			102
#define		G7			103
#define		G8			104
#define		G9			105
#define		G10			106
#define		G11			107
/* Pad Name Definition End */

/*---------------------------------------------------------------------------*/
/***	Port A --- Pin Out												   ***/
/*---------------------------------------------------------------------------*/
#define		A0_OUT		(SIU.GPDO[A0].B.PDO)
#define		A1_OUT		(SIU.GPDO[A1].B.PDO)
#define		A2_OUT		(SIU.GPDO[A2].B.PDO)
#define		A3_OUT		(SIU.GPDO[A3].B.PDO)
#define		A4_OUT		(SIU.GPDO[A4].B.PDO)
#define		A5_OUT		(SIU.GPDO[A5].B.PDO)
#define		A6_OUT		(SIU.GPDO[A6].B.PDO)
#define		A7_OUT		(SIU.GPDO[A7].B.PDO)
#define		A8_OUT		(SIU.GPDO[A8].B.PDO)
#define		A9_OUT		(SIU.GPDO[A9].B.PDO)
#define		A10_OUT		(SIU.GPDO[A10].B.PDO)
#define		A11_OUT		(SIU.GPDO[A11].B.PDO)
#define		A12_OUT		(SIU.GPDO[A12].B.PDO)
#define		A13_OUT		(SIU.GPDO[A13].B.PDO)
#define		A14_OUT		(SIU.GPDO[A14].B.PDO)
#define		A15_OUT		(SIU.GPDO[A15].B.PDO)

/*---------------------------------------------------------------------------*/
/***	Port B --- Pin Out												   ***/
/*---------------------------------------------------------------------------*/
#define		B0_OUT		(SIU.GPDO[B0].B.PDO)
#define		B1_OUT		(SIU.GPDO[B1].B.PDO)
#define		B2_OUT		(SIU.GPDO[B2].B.PDO)
#define		B3_OUT		(SIU.GPDO[B3].B.PDO)
#define		B4_OUT		(SIU.GPDO[B4].B.PDO)
#define		B5_OUT		(SIU.GPDO[B5].B.PDO)
#define		B6_OUT		(SIU.GPDO[B6].B.PDO)
#define		B7_OUT		(SIU.GPDO[B7].B.PDO)
#define		B8_OUT		(SIU.GPDO[B8].B.PDO)
#define		B9_OUT		(SIU.GPDO[B9].B.PDO)
#define		B10_OUT		(SIU.GPDO[B10].B.PDO)
#define		B11_OUT		(SIU.GPDO[B11].B.PDO)
#define		B12_OUT		(SIU.GPDO[B12].B.PDO)
#define		B13_OUT		(SIU.GPDO[B13].B.PDO)
#define		B14_OUT		(SIU.GPDO[B14].B.PDO)
#define		B15_OUT		(SIU.GPDO[B15].B.PDO)

/*---------------------------------------------------------------------------*/
/***	Port C --- Pin Out												   ***/
/*---------------------------------------------------------------------------*/
#define		C0_OUT		(SIU.GPDO[C0].B.PDO)
#define		C1_OUT		(SIU.GPDO[C1].B.PDO)
#define		C2_OUT		(SIU.GPDO[C2].B.PDO)
#define		C3_OUT		(SIU.GPDO[C3].B.PDO)
#define		C4_OUT		(SIU.GPDO[C4].B.PDO)
#define		C5_OUT		(SIU.GPDO[C5].B.PDO)
#define		C6_OUT		(SIU.GPDO[C6].B.PDO)
#define		C7_OUT		(SIU.GPDO[C7].B.PDO)
#define		C8_OUT		(SIU.GPDO[C8].B.PDO)
#define		C9_OUT		(SIU.GPDO[C9].B.PDO)
#define		C10_OUT		(SIU.GPDO[C10].B.PDO)
#define		C11_OUT		(SIU.GPDO[C11].B.PDO)
#define		C12_OUT		(SIU.GPDO[C12].B.PDO)
#define		C13_OUT		(SIU.GPDO[C13].B.PDO)
#define		C14_OUT		(SIU.GPDO[C14].B.PDO)
#define		C15_OUT		(SIU.GPDO[C15].B.PDO)

/*---------------------------------------------------------------------------*/
/***	Port D --- Pin Out												   ***/
/*---------------------------------------------------------------------------*/
#define		D0_OUT		(SIU.GPDO[D0].B.PDO)
#define		D1_OUT		(SIU.GPDO[D1].B.PDO)
#define		D2_OUT		(SIU.GPDO[D2].B.PDO)
#define		D3_OUT		(SIU.GPDO[D3].B.PDO)
#define		D4_OUT		(SIU.GPDO[D4].B.PDO)
#define		D5_OUT		(SIU.GPDO[D5].B.PDO)
#define		D6_OUT		(SIU.GPDO[D6].B.PDO)
#define		D7_OUT		(SIU.GPDO[D7].B.PDO)
#define		D8_OUT		(SIU.GPDO[D8].B.PDO)
#define		D9_OUT		(SIU.GPDO[D9].B.PDO)
#define		D10_OUT		(SIU.GPDO[D10].B.PDO)
#define		D11_OUT		(SIU.GPDO[D11].B.PDO)
#define		D12_OUT		(SIU.GPDO[D12].B.PDO)
#define		D13_OUT		(SIU.GPDO[D13].B.PDO)
#define		D14_OUT		(SIU.GPDO[D14].B.PDO)
#define		D15_OUT		(SIU.GPDO[D15].B.PDO)

/*---------------------------------------------------------------------------*/
/***	Port E --- Pin Out												   ***/
/*---------------------------------------------------------------------------*/
#define		E0_OUT		(SIU.GPDO[E0].B.PDO)
#define		E1_OUT		(SIU.GPDO[E1].B.PDO)
#define		E2_OUT		(SIU.GPDO[E2].B.PDO)
#define		E3_OUT		(SIU.GPDO[E3].B.PDO)
#define		E4_OUT		(SIU.GPDO[E4].B.PDO)
#define		E5_OUT		(SIU.GPDO[E5].B.PDO)
#define		E6_OUT		(SIU.GPDO[E6].B.PDO)
#define		E7_OUT		(SIU.GPDO[E7].B.PDO)
#define		E8_OUT		(SIU.GPDO[E8].B.PDO)
#define		E9_OUT		(SIU.GPDO[E9].B.PDO)
#define		E10_OUT		(SIU.GPDO[E10].B.PDO)
#define		E11_OUT		(SIU.GPDO[E11].B.PDO)
#define		E12_OUT		(SIU.GPDO[E12].B.PDO)
#define		E13_OUT		(SIU.GPDO[E13].B.PDO)
#define		E14_OUT		(SIU.GPDO[E14].B.PDO)
#define		E15_OUT		(SIU.GPDO[E15].B.PDO)

/*---------------------------------------------------------------------------*/
/***	Port F --- Pin Out												   ***/
/*---------------------------------------------------------------------------*/
#define		F0_OUT		(SIU.GPDO[F0].B.PDO)
#define		F1_OUT		(SIU.GPDO[F1].B.PDO)
#define		F2_OUT		(SIU.GPDO[F2].B.PDO)
#define		F3_OUT		(SIU.GPDO[F3].B.PDO)
#define		F4_OUT		(SIU.GPDO[F4].B.PDO)
#define		F5_OUT		(SIU.GPDO[F5].B.PDO)
#define		F6_OUT		(SIU.GPDO[F6].B.PDO)
#define		F7_OUT		(SIU.GPDO[F7].B.PDO)
#define		F8_OUT		(SIU.GPDO[F8].B.PDO)
#define		F9_OUT		(SIU.GPDO[F9].B.PDO)
#define		F10_OUT		(SIU.GPDO[F10].B.PDO)
#define		F11_OUT		(SIU.GPDO[F11].B.PDO)
#define		F12_OUT		(SIU.GPDO[F12].B.PDO)
#define		F13_OUT		(SIU.GPDO[F13].B.PDO)
#define		F14_OUT		(SIU.GPDO[F14].B.PDO)
#define		F15_OUT		(SIU.GPDO[F15].B.PDO)

/*---------------------------------------------------------------------------*/
/***	Port G --- Pin Out												   ***/
/*---------------------------------------------------------------------------*/
#define		G0_OUT		(SIU.GPDO[G0].B.PDO)
#define		G1_OUT		(SIU.GPDO[G1].B.PDO)
#define		G2_OUT		(SIU.GPDO[G2].B.PDO)
#define		G3_OUT		(SIU.GPDO[G3].B.PDO)
#define		G4_OUT		(SIU.GPDO[G4].B.PDO)
#define		G5_OUT		(SIU.GPDO[G5].B.PDO)
#define		G6_OUT		(SIU.GPDO[G6].B.PDO)
#define		G7_OUT		(SIU.GPDO[G7].B.PDO)
#define		G8_OUT		(SIU.GPDO[G8].B.PDO)
#define		G9_OUT		(SIU.GPDO[G9].B.PDO)
#define		G10_OUT		(SIU.GPDO[G10].B.PDO)
#define		G11_OUT		(SIU.GPDO[G11].B.PDO)

/*---------------------------------------------------------------------------*/
/***	Port A --- Pin In												   ***/
/*---------------------------------------------------------------------------*/
#define		A0_IN		(SIU.GPDI[A0].B.PDI)
#define		A1_IN		(SIU.GPDI[A1].B.PDI)
#define		A2_IN		(SIU.GPDI[A2].B.PDI)
#define		A3_IN		(SIU.GPDI[A3].B.PDI)
#define		A4_IN		(SIU.GPDI[A4].B.PDI)
#define		A5_IN		(SIU.GPDI[A5].B.PDI)
#define		A6_IN		(SIU.GPDI[A6].B.PDI)
#define		A7_IN		(SIU.GPDI[A7].B.PDI)
#define		A8_IN		(SIU.GPDI[A8].B.PDI)
#define		A9_IN		(SIU.GPDI[A9].B.PDI)
#define		A10_IN		(SIU.GPDI[A10].B.PDI)
#define		A11_IN		(SIU.GPDI[A11].B.PDI)
#define		A12_IN		(SIU.GPDI[A12].B.PDI)
#define		A13_IN		(SIU.GPDI[A13].B.PDI)
#define		A14_IN		(SIU.GPDI[A14].B.PDI)
#define		A15_IN		(SIU.GPDI[A15].B.PDI)

/*---------------------------------------------------------------------------*/
/***	Port B --- Pin In												   ***/
/*---------------------------------------------------------------------------*/
#define		B0_IN		(SIU.GPDI[B0].B.PDI)
#define		B1_IN		(SIU.GPDI[B1].B.PDI)
#define		B2_IN		(SIU.GPDI[B2].B.PDI)
#define		B3_IN		(SIU.GPDI[B3].B.PDI)
#define		B4_IN		(SIU.GPDI[B4].B.PDI)
#define		B5_IN		(SIU.GPDI[B5].B.PDI)
#define		B6_IN		(SIU.GPDI[B6].B.PDI)
#define		B7_IN		(SIU.GPDI[B7].B.PDI)
#define		B8_IN		(SIU.GPDI[B8].B.PDI)
#define		B9_IN		(SIU.GPDI[B9].B.PDI)
#define		B10_IN		(SIU.GPDI[B10].B.PDI)
#define		B11_IN		(SIU.GPDI[B11].B.PDI)
#define		B12_IN		(SIU.GPDI[B12].B.PDI)
#define		B13_IN		(SIU.GPDI[B13].B.PDI)
#define		B14_IN		(SIU.GPDI[B14].B.PDI)
#define		B15_IN		(SIU.GPDI[B15].B.PDI)

/*---------------------------------------------------------------------------*/
/***	Port C --- Pin In												   ***/
/*---------------------------------------------------------------------------*/
#define		C0_IN		(SIU.GPDI[C0].B.PDI)
#define		C1_IN		(SIU.GPDI[C1].B.PDI)
#define		C2_IN		(SIU.GPDI[C2].B.PDI)
#define		C3_IN		(SIU.GPDI[C3].B.PDI)
#define		C4_IN		(SIU.GPDI[C4].B.PDI)
#define		C5_IN		(SIU.GPDI[C5].B.PDI)
#define		C6_IN		(SIU.GPDI[C6].B.PDI)
#define		C7_IN		(SIU.GPDI[C7].B.PDI)
#define		C8_IN		(SIU.GPDI[C8].B.PDI)
#define		C9_IN		(SIU.GPDI[C9].B.PDI)
#define		C10_IN		(SIU.GPDI[C10].B.PDI)
#define		C11_IN		(SIU.GPDI[C11].B.PDI)
#define		C12_IN		(SIU.GPDI[C12].B.PDI)
#define		C13_IN		(SIU.GPDI[C13].B.PDI)
#define		C14_IN		(SIU.GPDI[C14].B.PDI)
#define		C15_IN		(SIU.GPDI[C15].B.PDI)

/*---------------------------------------------------------------------------*/
/***	Port D --- Pin In												   ***/
/*---------------------------------------------------------------------------*/
#define		D0_IN		(SIU.GPDI[D0].B.PDI)
#define		D1_IN		(SIU.GPDI[D1].B.PDI)
#define		D2_IN		(SIU.GPDI[D2].B.PDI)
#define		D3_IN		(SIU.GPDI[D3].B.PDI)
#define		D4_IN		(SIU.GPDI[D4].B.PDI)
#define		D5_IN		(SIU.GPDI[D5].B.PDI)
#define		D6_IN		(SIU.GPDI[D6].B.PDI)
#define		D7_IN		(SIU.GPDI[D7].B.PDI)
#define		D8_IN		(SIU.GPDI[D8].B.PDI)
#define		D9_IN		(SIU.GPDI[D9].B.PDI)
#define		D10_IN		(SIU.GPDI[D10].B.PDI)
#define		D11_IN		(SIU.GPDI[D11].B.PDI)
#define		D12_IN		(SIU.GPDI[D12].B.PDI)
#define		D13_IN		(SIU.GPDI[D13].B.PDI)
#define		D14_IN		(SIU.GPDI[D14].B.PDI)
#define		D15_IN		(SIU.GPDI[D15].B.PDI)

/*---------------------------------------------------------------------------*/
/***	Port E --- Pin In												   ***/
/*---------------------------------------------------------------------------*/
#define		E0_IN		(SIU.GPDI[E0].B.PDI)
#define		E1_IN		(SIU.GPDI[E1].B.PDI)
#define		E2_IN		(SIU.GPDI[E2].B.PDI)
#define		E3_IN		(SIU.GPDI[E3].B.PDI)
#define		E4_IN		(SIU.GPDI[E4].B.PDI)
#define		E5_IN		(SIU.GPDI[E5].B.PDI)
#define		E6_IN		(SIU.GPDI[E6].B.PDI)
#define		E7_IN		(SIU.GPDI[E7].B.PDI)
#define		E8_IN		(SIU.GPDI[E8].B.PDI)
#define		E9_IN		(SIU.GPDI[E9].B.PDI)
#define		E10_IN		(SIU.GPDI[E10].B.PDI)
#define		E11_IN		(SIU.GPDI[E11].B.PDI)
#define		E12_IN		(SIU.GPDI[E12].B.PDI)
#define		E13_IN		(SIU.GPDI[E13].B.PDI)
#define		E14_IN		(SIU.GPDI[E14].B.PDI)
#define		E15_IN		(SIU.GPDI[E15].B.PDI)

/*---------------------------------------------------------------------------*/
/***	Port F --- Pin In												   ***/
/*---------------------------------------------------------------------------*/
#define		F0_IN		(SIU.GPDI[F0].B.PDI)
#define		F1_IN		(SIU.GPDI[F1].B.PDI)
#define		F2_IN		(SIU.GPDI[F2].B.PDI)
#define		F3_IN		(SIU.GPDI[F3].B.PDI)
#define		F4_IN		(SIU.GPDI[F4].B.PDI)
#define		F5_IN		(SIU.GPDI[F5].B.PDI)
#define		F6_IN		(SIU.GPDI[F6].B.PDI)
#define		F7_IN		(SIU.GPDI[F7].B.PDI)
#define		F8_IN		(SIU.GPDI[F8].B.PDI)
#define		F9_IN		(SIU.GPDI[F9].B.PDI)
#define		F10_IN		(SIU.GPDI[F10].B.PDI)
#define		F11_IN		(SIU.GPDI[F11].B.PDI)
#define		F12_IN		(SIU.GPDI[F12].B.PDI)
#define		F13_IN		(SIU.GPDI[F13].B.PDI)
#define		F14_IN		(SIU.GPDI[F14].B.PDI)
#define		F15_IN		(SIU.GPDI[F15].B.PDI)

/*---------------------------------------------------------------------------*/
/***	Port G --- Pin In												   ***/
/*---------------------------------------------------------------------------*/
#define		G0_IN		(SIU.GPDI[G0].B.PDI)
#define		G1_IN		(SIU.GPDI[G1].B.PDI)
#define		G2_IN		(SIU.GPDI[G2].B.PDI)
#define		G3_IN		(SIU.GPDI[G3].B.PDI)
#define		G4_IN		(SIU.GPDI[G4].B.PDI)
#define		G5_IN		(SIU.GPDI[G5].B.PDI)
#define		G6_IN		(SIU.GPDI[G6].B.PDI)
#define		G7_IN		(SIU.GPDI[G7].B.PDI)
#define		G8_IN		(SIU.GPDI[G8].B.PDI)
#define		G9_IN		(SIU.GPDI[G9].B.PDI)
#define		G10_IN		(SIU.GPDI[G10].B.PDI)
#define		G11_IN		(SIU.GPDI[G11].B.PDI)

/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
extern void	mGPIO_Cfg_PinOut(uint8	PadName);
extern void	mGPIO_Cfg_PinIn(uint8	PadName);
extern void	mGPIO_Cfg_PinIO(uint8	PadName);
extern void	mGPIO_PinOut_High(uint8	PadName);
extern void	mGPIO_PinOut_Low(uint8	PadName);

extern void PORT_L2_Init(void);
extern void PORT_L2_MCU_FATInit(void);
#endif	
