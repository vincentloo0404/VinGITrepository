/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_CAN_Cfg.h
*
* @brief    Config Header file for "m_CAN_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/27      Lwt       	   	N/A          Original
*     1.1        2012/10/10      Lwt			N/A          Modify CAN Cfg
*     1.2        2012/10/19      JiaoYu			N/A          Modify for CCP Protocol
*     1.3        2012/11/02      Lwt			N/A          Add History Comment
*     1.4        2013/01/11      Lwt			N/A          CAN Update, Separate SendMess and MB_ISR 
*     1.5        2013/01/14      Lwt			N/A          Add BusOff Recover Function 
************************************************************************************************/

#ifndef _M_CAN_CFG_H_
#define _M_CAN_CFG_H_


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_CAN_Drv.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   Config Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	CAN Time Out Delay												   ***/
/*---------------------------------------------------------------------------*/
#define 	TIMEOUT_CAN_SOFT_RST	1000

/*---------------------------------------------------------------------------*/
/***	MB BUSY Time Out Delay											   ***/
/*---------------------------------------------------------------------------*/
#define 	TIMEOUT_CAN_BUSY		100

/*---------------------------------------------------------------------------*/
/***	MB Abort porcedure Time Out currently transmitted				   ***/
/*---------------------------------------------------------------------------*/
#define 	TIMEOUT_CAN_ABORT		100

/*---------------------------------------------------------------------------*/
/***	CAN Bus Off Recovery Time Out Delay								   ***/
/*---------------------------------------------------------------------------*/
#define 	TIMEOUT_CAN_BUSOFF		100

/*---------------------------------------------------------------------------*/
/***	CAN PCR															   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_TX_PIN				B0
#define		CAN_TX_PCR				(ALT1|B_OBE)
#define		CAN_RX_PIN				B1	
#define		CAN_RX_PCR				(GPIO|B_IBE)

#define		CAN_USE_FIFO					/* CAN Use FIFO Enabled */
#define		CAN_USE_ABORT					/* CAN Use Abort Enabled */
#define		CAN_BUSOFF_RECOVERY		FALSE	/* CAN BusOff Self-Recovery */


////////////////////////////////////////SAFEPORT_CAN    ////////////////////////
#define		SAFEPORT_CAN_TX_PIN				A14
#define		SAFEPORT_CAN_TX_PCR				(ALT1|B_OBE)
#define		SAFEPORT_CAN_RX_PIN				A15	
#define		SAFEPORT_CAN_RX_PCR				(GPIO|B_IBE)
#define		SAFEPORT_CAN_USE_FIFO					/* CAN Use FIFO Enabled */
#define		SAFEPORT_CAN_USE_ABORT					/* CAN Use Abort Enabled */
#define		SAFEPORT_CAN_BUSOFF_RECOVERY		FALSE	/* CAN BusOff Self-Recovery */
/*---------------------------------------------------------------------------*/
/***	CAN Time Out Delay												   ***/
/*---------------------------------------------------------------------------*/
#define 	SAFEPORT_TIMEOUT_CAN_SOFT_RST	1000

/*---------------------------------------------------------------------------*/
/***	MB BUSY Time Out Delay											   ***/
/*---------------------------------------------------------------------------*/
#define 	SAFEPORT_TIMEOUT_CAN_BUSY		100

/*---------------------------------------------------------------------------*/
/***	MB Abort porcedure Time Out currently transmitted				   ***/
/*---------------------------------------------------------------------------*/
#define 	SAFEPORT_TIMEOUT_CAN_ABORT		100

/*---------------------------------------------------------------------------*/
/***	CAN Bus Off Recovery Time Out Delay								   ***/
/*---------------------------------------------------------------------------*/
#define 	SAFEPORT_TIMEOUT_CAN_BUSOFF		100

/////////////////////////////////////////////////////////////////////////////////

#if 0
	#define		CAN_USE_COMPAT_MASK			/* Backwards Compatibility Config */
	#define		CAN_SELF_TEST_DEBUG			/* Self Reception Config */
#endif

#define		CAN_TX_STD_FRAME				/* Transmit only Standard CAN Frame */
#define		CAN_RX_STD_FRAME				/* Receive only Standard CAN Frame */
#define		CAN_RX_DATA_FRAME				/* Receive only Data Frame */

/*---------------------------------------------------------------------------*/
/***	CAN MB Enabled													   ***/
/*---------------------------------------------------------------------------*/
#define 	MB_USE_NONE    			0
#define 	MB_USE_RX    			1		/* MB used for Rx, ISR */
#define 	MB_USE_TX    			2		/* MB used for Tx, ISR */

#ifndef 	CAN_USE_FIFO
	#define 	CAN_MB_00_03_USE	MB_USE_RX
	#define 	CAN_MB_04_07_USE	MB_USE_RX
#endif
#define 	CAN_MB_08_11_USE		MB_USE_TX
#define 	CAN_MB_12_15_USE		MB_USE_TX
#define 	CAN_MB_16_31_USE		MB_USE_TX

/*---------------------------------------------------------------------------*/
/***	CAN RxFIFO Config												   ***/
/*---------------------------------------------------------------------------*/
#ifdef CAN_USE_FIFO
	/* CAN Rx FIFO ID table Format */
	#define		CAN_ID_TABLE_FORMAT		CAN_ID_TABLE_A
	
	/* CAN Rx FIFO ID table Value	( <= 0x3FF ) */
	#ifdef	CAN_RX_DATA_FRAME
		#define		CAN_ID_TABLE_REM	0x0
	#else
		#define		CAN_ID_TABLE_REM	0x1
	#endif

	#ifdef	CAN_RX_STD_FRAME
		#define		CAN_ID_TABLE_EXT	0x0
	#else
		#define		CAN_ID_TABLE_EXT	0x1
	#endif

/*---------------------------------------------------------------------------*/
/***	Rx FIFO ID table Value											   ***/
/*---------------------------------------------------------------------------*/
/*
	#define		CAN_ID_TABLE_0			0x16D    // MG GT ABS_DSC_HSC_FrP00 vehSpd 
	#define		CAN_ID_TABLE_1			0x4CC    //  ABS_DSC_HSC_FrP01 WheelSpd 
	#define		CAN_ID_TABLE_2			0x512    //  ABS_DSC_HSC_FrP02 WheelRollingCount 
//	#define		CAN_ID_TABLE_3			0x600    // BCM_HSC_FrP02,KeySwitch 
	#define		CAN_ID_TABLE_3			0x7DF    //  UDS Fun Request 
	#define		CAN_ID_TABLE_4			0x05E    //  EMS_HSC_FrP00,EngineRunningST 
	#define		CAN_ID_TABLE_5			0x608    //  EMS_HSC_FrP05,EnASSStaHSC
//	#define		CAN_ID_TABLE_6			0x57E    //  EMS_HSC_FrP02,EngineType 
	#define		CAN_ID_TABLE_6			0x723    //  UDS Phy Request 
	#define		CAN_ID_TABLE_7			0x635    //  MG GT CCP CRO 
*/

	#define		CAN_ID_TABLE_0			0x4F4    // 
	#define		CAN_ID_TABLE_1			0x7DF    //  ABS_DSC_HSC_FrP01 WheelSpd 
	#define		CAN_ID_TABLE_2			0x395    //  ABS_DSC_HSC_FrP02 WheelRollingCount 
	#define		CAN_ID_TABLE_3			0x7DF    //  UDS Fun Request 
	#define		CAN_ID_TABLE_4			0x723     //  0x6E
	#define		CAN_ID_TABLE_5			0x723    //  EMS_HSC_FrP05,EnASSStaHSC
	#define		CAN_ID_TABLE_6			0x723    //  UDS Phy Request 
	#define		CAN_ID_TABLE_7			0x635    //  MG GT CCP CRO 
	
/*---------------------------------------------------------------------------*/
/***	Rx FIFO Used MB0--7 MASK as Mask								   ***/
/*---------------------------------------------------------------------------*/
	#define 	CAN_MASK_TABLE_0		0xFFFF0000
	#define 	CAN_MASK_TABLE_1		0xFFFF0000
	#define 	CAN_MASK_TABLE_2		0xFFFF0000
	#define 	CAN_MASK_TABLE_3		0xFFFF0000
	#define 	CAN_MASK_TABLE_4		0xFFFF0000
	#define 	CAN_MASK_TABLE_5		0xFFFF0000
	#define 	CAN_MASK_TABLE_6		0xFFFF0000
	#define 	CAN_MASK_TABLE_7		0xFFFF0000
#endif

/*---------------------------------------------------------------------------*/
/***	MB_00_03 IRQ_68													   ***/
/*---------------------------------------------------------------------------*/
#if(CAN_MB_00_03_USE == MB_USE_RX)
	#define 	CAN_MB_00_03_ID_STD		0x213
	#define 	CAN_MB_00_03_ID_EXT		0x0
	/* CAN Individual Rx Mask */
	/* RXIMR: 	0, corresponding bit in the filter is don¡¯t care; 
				1, corresponding bit in the filter is checked against the one received. */
	#define 	CAN_MB_00_03_MASK		0xFFFF0000			/* 0xC0000000	 all frame can rx for test */
#elif(CAN_MB_00_03_USE == MB_USE_TX)
	#define 	CAN_MB_00_03_ID_PRIO	CAN_ID_APP_PRIO
#elif(CAN_MB_00_03_USE == MB_USE_NONE)

#endif

/*---------------------------------------------------------------------------*/
/***	MB_04_07 IRQ_69													   ***/
/*---------------------------------------------------------------------------*/
#if(CAN_MB_04_07_USE == MB_USE_RX)
	#define 	CAN_MB_04_07_ID_STD		0x308
	#define 	CAN_MB_04_07_ID_EXT		0x0
	/* CAN Individual Rx Mask */
	/* RXIMR: 	0, corresponding bit in the filter is don¡¯t care; 
				1, corresponding bit in the filter is checked against the one received. */
	#define 	CAN_MB_04_07_MASK		0xFFFF0000
#elif(CAN_MB_04_07_USE == MB_USE_TX)
	#define 	CAN_MB_04_07_ID_PRIO	CAN_ID_APP_PRIO
#elif(CAN_MB_04_07_USE == MB_USE_NONE)
	
#endif

/*---------------------------------------------------------------------------*/
/***	MB_08_11 IRQ_70													   ***/
/*---------------------------------------------------------------------------*/
#if(CAN_MB_08_11_USE == MB_USE_RX)
	#define 	CAN_MB_08_11_ID_STD		0x213
	#define 	CAN_MB_08_11_ID_EXT		0x0
	/* CAN Individual Rx Mask */
	/* RXIMR: 	0, corresponding bit in the filter is don¡¯t care; 
				1, corresponding bit in the filter is checked against the one received. */
	#define 	CAN_MB_08_11_MASK		0xFFFF0000
#elif(CAN_MB_08_11_USE == MB_USE_TX)
	#define 	CAN_MB_08_11_ID_PRIO	CAN_ID_APP_PRIO		/* CAN_ID_CCP_PRIO */
#elif(CAN_MB_08_11_USE == MB_USE_NONE)

#endif

/* MB_12_15 IRQ_71 */
#if(CAN_MB_12_15_USE == MB_USE_RX)
	#define 	CAN_MB_12_15_ID_STD		0x355
	#define 	CAN_MB_12_15_ID_EXT		0x0
	/* CAN Individual Rx Mask */
	/* RXIMR: 	0, corresponding bit in the filter is don¡¯t care; 
				1, corresponding bit in the filter is checked against the one received. */
	#define 	CAN_MB_12_15_MASK		0xFFFF0000
#elif(CAN_MB_12_15_USE == MB_USE_TX)
	#define 	CAN_MB_12_15_ID_PRIO	CAN_ID_CCP_PRIO		/* CAN_ID_APP_PRIO */
#elif(CAN_MB_12_15_USE == MB_USE_NONE)

#endif

/*---------------------------------------------------------------------------*/
/***	MB_16_31 IRQ_72													   ***/
/*---------------------------------------------------------------------------*/
#if(CAN_MB_16_31_USE == MB_USE_RX)
	#define 	CAN_MB_16_31_ID_STD		0x333
	#define 	CAN_MB_16_31_ID_EXT		0x0
	/* CAN Individual Rx Mask */
	/* RXIMR: 	0, corresponding bit in the filter is don¡¯t care; 
				1, corresponding bit in the filter is checked against the one received. */
	#define 	CAN_MB_16_31_MASK		0xFFFF0000
#elif(CAN_MB_16_31_USE == MB_USE_TX)
	#define 	CAN_MB_16_31_ID_PRIO	CAN_ID_BOOT_PRIO		/* CAN_ID_APP_PRIO */
#elif(CAN_MB_16_31_USE == MB_USE_NONE)

#endif

/*---------------------------------------------------------------------------*/
/***	CAN Use MB Number (1 to 32)										   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_MB_NUM			32

/*---------------------------------------------------------------------------*/
/***	CAN USE MB Number for Tx MB										   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_TXMB_START		8
#define		CAN_TXMB_END		(CAN_MB_NUM - 1)

/*---------------------------------------------------------------------------*/
/***	CAN Tx C/S Word Mask											   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_CS_WORD_MASK			0x0F7FFFFF
#define		CAN_CS_WORD_CODE_DEL		0x007FFFFF

/*---------------------------------------------------------------------------*/
/***	CAN Tx Message's ID Prio ,0-high,7-low							   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_ID_APP_PRIO				0x00
#define		CAN_ID_CCP_PRIO				0x01
#define		CAN_ID_BOOT_PRIO			0x02

/*---------------------------------------------------------------------------*/
/***	CAN Tx Message's ID Std											   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_ID_APP_STD				0x315
#define		CAN_ID_CCP_STD				0x101
#define		CAN_ID_BOOT_STD				0x729 

/*---------------------------------------------------------------------------*/
/***	CAN Baud Samples												   ***/
/*---------------------------------------------------------------------------*/
/* *****************************************************************************
BitRate = fCAN / (PRESDIV+1) / (1+ (PROPSEG+1 + PSEG1+1) + PSEG2+1) ;
Sample Rate = (1+ (PROPSEG+1 + PSEG1+1)) / ((1+ (PROPSEG+1 + PSEG1+1) + PSEG2+1))

Condition:
(1)	4 <= (PROPSEG+1 + PSEG1+1) <= 16 ; 
(2)	2 <= (PSEG2+1) <= 8 ;
(3)	8 <=  ((1+ (PROPSEG+1 + PSEG1+1) + PSEG2+1)) <= 25 ;
(4)	fCAN = 64MHz, (SYS_CLK)

   ***************************************************************************** */


/*---------------------------------------------------------------------------*/
/***	(PRESDIV<<24)|(RJW<<22)|(PSEG1<<19)|(PSEG2<<16)|(SMP<<7)|(PROPSEG) ***/
/*---------------------------------------------------------------------------*/
#define		CAN_BAUD_1M_1		((3<<24)|(0<<22)|(5<<19)|(3<<16)|(0<<7)|(4))	/* 75% */
#define		CAN_BAUD_500K_1		((7<<24)|(0<<22)|(5<<19)|(3<<16)|(0<<7)|(4))	/* 75% */
#define		CAN_BAUD_500K_2		((7<<24)|(0<<22)|(4<<19)|(4<<16)|(0<<7)|(4))	/* 68.75% */
#define		CAN_BAUD_250K_1		((15<<24)|(0<<22)|(5<<19)|(3<<16)|(0<<7)|(4))	/* 75% */
#define		CAN_BAUD_250K_2		((15<<24)|(0<<22)|(4<<19)|(4<<16)|(0<<7)|(4))	/* 68.75% */
#define		CAN_BAUD_125K_1		
#define		CAN_BAUD_125K_2	

/*---------------------------------------------------------------------------*/
/***	Select CAN Baud													   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_BAUD_SELECT		CAN_BAUD_500K_1



#endif	

