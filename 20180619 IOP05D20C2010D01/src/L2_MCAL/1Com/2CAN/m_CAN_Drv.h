/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_CAN_Drv.h
*
* @brief    Drive Header file for "m_CAN_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/07      Lwt       	   	N/A          Original
*     1.1        2012/09/27      Lwt			N/A          Add Cfg file
*     1.2        2012/10/10      Lwt			N/A          Modify CAN Cfg
*     1.3        2012/10/19      JiaoYu			N/A          Modify for CCP Protocol
*     1.4        2012/11/02      Lwt			N/A          Add History Comment
*     1.5        2013/01/11      Lwt			N/A          CAN Update, Separate SendMess and MB_ISR 
*     1.6        2013/01/14      Lwt			N/A          Add BusOff Recover Function
************************************************************************************************/

#ifndef _M_CAN_DRV_H_
#define _M_CAN_DRV_H_

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include  	"m_GPIO.h"
#include 	"Common.h"


/* *****************************************************************************
   *****************************************************************************
   Drive Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Register Address define											   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_BASE_ADDRESS				0xFFFC0000ul
#define 	CAN_MCR_OFFSET					0x0ul
#define 	CAN_CTRL_OFFSET					0x4ul
#define 	CAN_TIMER_OFFSET				0x8ul
#define 	CAN_RXGMASK_OFFSET				0x10ul
#define 	CAN_RX14MASK_OFFSET				0x14ul
#define 	CAN_RX15MASK_OFFSET				0x18ul
#define 	CAN_ECR_OFFSET					0x1Cul
#define 	CAN_ESR_OFFSET					0x20ul
#define 	CAN_IMASK1_OFFSET				0x28ul
#define 	CAN_IFLAG1_OFFSET				0x30ul
#define 	CAN_RXFIFO_OFFSET				0x80ul
#define 	CAN_MB_OFFSET(x)				(0x80ul+(x)*0x10)	/* 0--31 */
#define 	CAN_RXIMR_OFFSET(x)				(0x880ul+(x)*0x04)

/*---------------------------------------------------------------------------*/
/***	Module Configuration Register (MCR)								   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_MCR							(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_MCR_OFFSET))
#define 	CAN_MCR_MDIS_MASK				(1<<31)
#define 	CAN_MCR_FRZ_MASK				(1<<30)
#define 	CAN_MCR_FEN_MASK				(1<<29)
#define 	CAN_MCR_HALT_MASK				(1<<28)
#define 	CAN_MCR_NOT_READY_MASK			(1<<27)
#define 	CAN_MCR_WAK_MSK_MASK			(1<<26)
#define 	CAN_MCR_SOFT_RST_MASK			(1<<25)
#define 	CAN_MCR_FRZ_ACK_MASK			(1<<24)
#define 	CAN_MCR_SUPV_MASK				(1<<23)
#define 	CAN_MCR_WRN_EN_MASK				(1<<21)
#define 	CAN_MCR_LPM_ACK_MASK			(1<<20)
#define 	CAN_MCR_SRX_DIS_MASK			(1<<17)
#define 	CAN_MCR_BCC_MASK				(1<<16)
#define 	CAN_MCR_LPRIO_EN_MASK			(1<<13)
#define 	CAN_MCR_AEN_MASK				(1<<12)
#define 	CAN_MCR_IDAM_MASK				(0x3<<8)
#define 	CAN_MCR_MAXMB_MASK				(0x3F<<0)

/*---------------------------------------------------------------------------*/
/***	Control Register (CTRL)											   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_CTRL						(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_CTRL_OFFSET))
#define 	CAN_CTRL_PRESDIV_MASK			(0xFF<<24)
#define 	CAN_CTRL_RJW_MASK				(0x03<<22)
#define 	CAN_CTRL_PSEG1_MASK				(0x07<<19)
#define 	CAN_CTRL_PSEG2_MASK				(0x07<<16)
#define 	CAN_CTRL_BOFF_MSK_MASK			(1<<15)
#define 	CAN_CTRL_ERR_MSK_MASK			(1<<14)
#define 	CAN_CTRL_CLK_SRC_MASK			(1<<13)
#define 	CAN_CTRL_LPB_MASK				(1<<12)
#define 	CAN_CTRL_TWRN_MSK_MASK			(1<<11)
#define 	CAN_CTRL_RWRN_MSK_MASK			(1<<10)
#define 	CAN_CTRL_SMP_MASK				(1<<7)
#define 	CAN_CTRL_BOFF_REC_MASK			(1<<6)
#define 	CAN_CTRL_TSYN_MASK				(1<<5)
#define 	CAN_CTRL_LBUF_MASK				(1<<4)
#define 	CAN_CTRL_LOM_MASK				(1<<3)
#define 	CAN_CTRL_PROPSEG_MASK			(0x07<<0)

/*---------------------------------------------------------------------------*/
/***	Free Running Timer (TIMER)										   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_TIMER						(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_TIMER_OFFSET))
#define 	CAN_TIMER_TIMER_MASK			(0xFFFF<<0)

/*---------------------------------------------------------------------------*/
/***	Rx Global Mask register (RXGMASK)								   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_RXGMASK						(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_RXGMASK_OFFSET))

/*---------------------------------------------------------------------------*/
/***	Rx 14 Mask (RX14MASK)											   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_RX14MASK					(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_RX14MASK_OFFSET))

/*---------------------------------------------------------------------------*/
/***	Rx 15 Mask (RX15MASK)											   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_RX15MASK					(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_RX15MASK_OFFSET))

/*---------------------------------------------------------------------------*/
/***	Error Counter Register (ECR)									   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_ECR							(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_ECR_OFFSET))
#define 	CAN_ECR_RX_ERR_CNT_MASK			(0xFF<<8)
#define 	CAN_ECR_TX_ERR_CNT_MASK			(0xFF<<0)

/*---------------------------------------------------------------------------*/
/***	Error and Status Register (ESR)									   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_ESR							(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_ESR_OFFSET))
#define 	CAN_ESR_TWRN_INT_MASK			(1<<17)
#define 	CAN_ESR_RWRN_INT_MASK			(1<<16)
#define 	CAN_ESR_BIT1_ERR_MASK			(1<<15)
#define 	CAN_ESR_BIT0_ERR_MASK			(1<<14)
#define 	CAN_ESR_ACK_ERR_MASK			(1<<13)
#define 	CAN_ESR_CRC_ERR_MASK			(1<<12)
#define 	CAN_ESR_FRM_ERR_MASK			(1<<11)
#define 	CAN_ESR_STF_ERR_MASK			(1<<10)
#define 	CAN_ESR_TX_WRN_MASK				(1<<9)
#define 	CAN_ESR_RX_WRN_MASK				(1<<8)
#define 	CAN_ESR_IDLE_MASK				(1<<7)
#define 	CAN_ESR_TXRX_MASK				(1<<6)
#define 	CAN_ESR_FLT_CONF_MASK			(0x03<<4)
#define 	CAN_ESR_BOFF_INT_MASK			(1<<2)
#define 	CAN_ESR_ERR_INT_MASK			(1<<1)
#define 	CAN_ESR_WAK_INT_MASK			(1<<0)
#define 	CAN_ESR_BUSOFF_STS_MASK			(1<<5)

/*---------------------------------------------------------------------------*/
/***	Interrupt Masks 1 Register (IMASK1)								   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_IMASK1						(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_IMASK1_OFFSET))

/*---------------------------------------------------------------------------*/
/***	Interrupt Flags 1 Register (IFLAG1)								   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_IFLAG1						(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_IFLAG1_OFFSET))
#define 	CAN_IFLAG1_FIFO_AVAI_MASK		(1<<5)
#define 	CAN_IFLAG1_FIFO_WARN_MASK		(1<<6)
#define 	CAN_IFLAG1_FIFO_OVERRN_MASK		(1<<7)

/*---------------------------------------------------------------------------*/
/***	Rx Individual Mask Registers (RXIMR0 - CRXIMR31)				   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_RXIMR(x)					(*(volatile uint32 *)(CAN_BASE_ADDRESS+CAN_RXIMR_OFFSET(x)))

/*---------------------------------------------------------------------------*/
/***	Rx Individual Mask Registers Struct								   ***/
/*---------------------------------------------------------------------------*/
typedef	struct _CAN_MB_ 
{
	union 
	{
		vuint32_t Word;
		struct 
		{
			vuint32_t	:4;
			vuint32_t 	CODE:4;
			vuint32_t	:1;
			vuint32_t 	SRR:1;
			vuint32_t 	IDE:1;
			vuint32_t 	RTR:1;
			vuint32_t 	LENGTH:4;
			vuint32_t 	TIMESTAMP:16;
		} Bits;
	} CS;

	union 
	{
		vuint32_t Word;
		struct 
		{
			vuint32_t PRIO:3;
			vuint32_t STD_ID:11;
			vuint32_t EXT_ID:18;
		} Bits;
	} ID;

    union 
    {
        vuint8_t  Bytes[8];
    } DATA;
    
}stc_CAN_MB;

/*---------------------------------------------------------------------------*/
/***	Rx Individual Mask Registers (RXIMR0 - RXIMR31)					   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_MB(x)				(*(volatile stc_CAN_MB *)(CAN_BASE_ADDRESS+CAN_MB_OFFSET(x)))
#define 	CAN_MB_CS_MASK			0x0F7FFFFFul
#define 	CAN_MB_ID_STD_MASK		0x000003FFul
#define 	CAN_MB_ID_EXT_MASK		0x0003FFFFul

/*---------------------------------------------------------------------------*/
/***	Rx FIFO struct													   ***/
/*---------------------------------------------------------------------------*/
typedef	struct _CAN_RXFIFO_ 
{
	union 
	{
		vuint32_t Word;
		struct 
		{
			vuint32_t:9;
			vuint32_t SRR:1;
			vuint32_t IDE:1;
			vuint32_t RTR:1;
			vuint32_t LENGTH:4;
			vuint32_t TIMESTAMP:16;
		} Bits;
	} CS;

	union 
	{
		vuint32_t Word;
		struct 
		{
			vuint32_t:3;
			vuint32_t STD_ID:11;
			vuint32_t EXT_ID:18;
		} Bits;
	} ID;

	union 
	{
		vuint8_t  Bytes[8]; 
	} DATA;

	uint32_t RxFIFO_Rsv[20];   /* {0x00E0-0x0090}/0x4 = 0x14  */

	union 
	{
		vuint32_t Word;
	} ID_Table[8];

}stc_CAN_RxFIFO;                          /* end of CAN_RxFIFO */

/*---------------------------------------------------------------------------*/
/***	Rx FIFO															   ***/
/*---------------------------------------------------------------------------*/
#define 	CAN_RX_FIFO						(*(volatile stc_CAN_RxFIFO *)(CAN_BASE_ADDRESS+CAN_RXFIFO_OFFSET))



/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Rx FIFO Intc Mask												   ***/
/*---------------------------------------------------------------------------*/
#define 	FIFO_AVAI_MASK				(uint8)0x05u
#define 	FIFO_WARN_MASK				(uint8)0x06u
#define 	FIFO_OVERRN_MASK			(uint8)0x07u

/*---------------------------------------------------------------------------*/
/***	CAN Arbitration Mode											   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_ARBTR_ID				0
#define		CAN_ARBTR_NUM				1
#define		CAN_ARBTR_PRIO				2

/*---------------------------------------------------------------------------*/
/***	CAN Rx FIFO ID table Format										   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_ID_TABLE_A				0
#define		CAN_ID_TABLE_B				1
#define		CAN_ID_TABLE_C				2
#define		CAN_ID_TABLE_D				3

/*---------------------------------------------------------------------------*/
/***	CAN Tx MB Macro													   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_CS_SRR					0x01
#define		CAN_CS_IDE					0x00	/* Std or Ext */
#define		CAN_CS_RTR					0x00	/* Data or Remote */

/*---------------------------------------------------------------------------*/
/***	CAN CODE Command												   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_CODE_TX_INACTIVE		0x08	/* 1000 */
#define		CAN_CODE_TX_ABORT			0x09	/* 1001 */
#define		CAN_CODE_TX_TRANSMIT		0x0C	/* 1100 */
#define		CAN_CODE_TX_REQ_RTR			0x0C	/* 1100 "RTR = 1" */
#define		CAN_CODE_TX_AFTER_RTR		0x0A	/* 1010 */
#define		CAN_CODE_TX_AUTO_RTR		0x0E	/* 1110 */

#define		CAN_CODE_RX_INACTIVE		0x00	/* 0000 */
#define		CAN_CODE_RX_EMPTY			0x04	/* 0100 */
#define		CAN_CODE_RX_FULL			0x02	/* 0010 */
#define		CAN_CODE_RX_OVERRUN			0x06	/* 0110 */
#define		CAN_CODE_RX_BUSY_WR			0x03	/* 0011 */
#define		CAN_CODE_RX_BUSY_OVER		0x07	/* 0111 */

/*---------------------------------------------------------------------------*/
/***	Error and Status Register (ESR)									   ***/
/*---------------------------------------------------------------------------*/
#define 	mCAN_Clear_TxWarnIntc 		{CAN_ESR |= CAN_ESR_TWRN_INT_MASK;}
#define 	mCAN_Clear_RxWarnIntc 		{CAN_ESR |= CAN_ESR_RWRN_INT_MASK;}
#define 	mCAN_Clear_BusOffIntc 		{CAN_ESR |= CAN_ESR_BOFF_INT_MASK;}
#define 	mCAN_Clear_ErrIntc 			{CAN_ESR |= CAN_ESR_ERR_INT_MASK;}
#define 	mCAN_Clear_WakeUpIntc 		{CAN_ESR |= CAN_ESR_WAK_INT_MASK;}

/*---------------------------------------------------------------------------*/
/***	Interrupt Flags 1 Register (IFLAG1)								   ***/
/*---------------------------------------------------------------------------*/
#define 	mCAN_Clear_BufIntc(BufNum) 	{CAN_IFLAG1 = (1<<BufNum);}  /* '|=' will clear all IFlag */

/*---------------------------------------------------------------------------*/
/***	CAN Clk Use PLL													   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_CLK_USE_PLL

/*---------------------------------------------------------------------------*/
/***	CAN Arbitration Mode											   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_ARBTR_MODE		CAN_ARBTR_PRIO

/*---------------------------------------------------------------------------*/
/***	CAN RxFIFO Size													   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_RXFIFO_SIZE			0x06

/*---------------------------------------------------------------------------*/
/***	CAN BusOff Intc Enabled											   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_BOFF_INTC_En		{REG32_BIT_SET(CAN_CTRL, CAN_CTRL_BOFF_MSK_MASK);}
#define		CAN_BOFF_INTC_Dis		{REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_BOFF_MSK_MASK);}

/*---------------------------------------------------------------------------*/
/***	CAN BusOff Intc Recovery										   ***/
/*---------------------------------------------------------------------------*/
#define		CAN_BOFF_AutoRec_En		{REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_BOFF_REC_MASK);}
#define		CAN_BOFF_AutoRec_Dis	{REG32_BIT_SET(CAN_CTRL, CAN_CTRL_BOFF_REC_MASK);}


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
extern	uint8	mCAN_Init(void);
extern	uint8	mCAN_Send_MessageForCCP(stc_CAN_MB *pTxBuf);

extern	uint8	mCAN_MB_00_03_Send_Message(stc_CAN_MB *pTxBuf);
extern	uint8	mCAN_MB_04_07_Send_Message(stc_CAN_MB *pTxBuf);
extern	uint8	mCAN_MB_08_11_Send_Message(stc_CAN_MB *pTxBuf);
extern	uint8	mCAN_MB_12_15_Send_Message(stc_CAN_MB *pTxBuf);
extern	uint8	mCAN_MB_16_31_Send_Message(stc_CAN_MB *pTxBuf);

extern	void	mCAN_MB_All_Send_Clear(void);
extern	uint8	mCAN_Get_Fault_Conf_State(void);
extern	void	mCAN_Module_En(void);
extern	uint8	mCAN_Module_Dis(void);
extern	uint8	mCAN_Abort_Procedure(uint8 MessBufNum);
extern	uint8	mCAN_BusOff_Recovery(void);

extern void  CanRx_L2_Per(void);
extern void  CanTx_L2_Confirm(void);

#endif	

