/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_EDMA_Drv.h
*
* @brief    Drive Header file for "m_EDMA_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/04/12      CODER2       	   	N/A          Original
************************************************************************************************/

#ifndef _M_EDMA_DRV_H_
#define _M_EDMA_DRV_H_

#ifdef 	M_EDMA_DRV_C
#define M_EDMA_DRV_EXT
#else
#define M_EDMA_DRV_EXT 	extern
#endif


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
/***	eDMA Address define												   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_BASE_ADDRESS				0xFFF44000ul
#define 	EDMA_CR_OFFSET					0x0000ul
#define 	EDMA_ESR_OFFSET					0x0004ul
#define 	EDMA_ERQRL_OFFSET				0x000Cul
#define 	EDMA_EEIRL_OFFSET				0x0014ul
#define 	EDMA_SERQR_OFFSET				0x0018ul	/* 1 Byte */
#define 	EDMA_CERQR_OFFSET				0x0019ul	/* 1 Byte */
#define 	EDMA_SEEI_OFFSET				0x001Aul	/* 1 Byte */
#define 	EDMA_CEEI_OFFSET				0x001Bul	/* 1 Byte */
#define 	EDMA_CIRQR_OFFSET				0x001Cul	/* 1 Byte */
#define 	EDMA_CER_OFFSET					0x001Dul	/* 1 Byte */
#define 	EDMA_SSBR_OFFSET				0x001Eul	/* 1 Byte */
#define 	EDMA_CDSBR_OFFSET				0x001Ful	/* 1 Byte */
#define 	EDMA_IRQRL_OFFSET				0x0024ul
#define 	EDMA_ERL_OFFSET					0x002Cul
#define 	EDMA_HRSL_OFFSET				0x0034ul
#define 	EDMA_CPR_OFFSET					0x0100ul
#define 	EDMA_CPR_STEP					0x0001ul	/* 1 Byte */
#define 	EDMA_CPR_ADDRESS(x)				(EDMA_BASE_ADDRESS+EDMA_CPR_OFFSET+(x)*EDMA_CPR_STEP)
#define 	EDMA_TCD_OFFSET					0x1000ul
#define 	EDMA_TCD_STEP					0x0020ul	/* 20 Bytes */
#define 	EDMA_TCD_ADDRESS(x)				(EDMA_BASE_ADDRESS+EDMA_TCD_OFFSET+(x)*EDMA_TCD_STEP)

/*---------------------------------------------------------------------------*/
/***	eDMA_Mux Address define											   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMAMUX_BASE_ADDRESS			0xFFFDC000ul
#define 	EDMAMUX_CHCONFIG_OFFSET			0x0000ul
#define 	EDMAMUX_CHCONFIG_STEP			0x0001ul	/* 1 Byte */
#define 	EDMAMUX_CHCONFIG_ADDRESS(x)		(EDMAMUX_BASE_ADDRESS+EDMAMUX_CHCONFIG_OFFSET+(x)*EDMAMUX_CHCONFIG_STEP)

/*---------------------------------------------------------------------------*/
/***	EDMA_CR  Control Register (EDMA_CR)								   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_CR							(*(volatile uint32 *)(EDMA_BASE_ADDRESS+EDMA_CR_OFFSET))
#define 	EDMA_CR_ERCA_MASK				(1<<2)
#define 	EDMA_CR_EBDG_MASK				(1<<1)

/*---------------------------------------------------------------------------*/
/***	eDMA Error Status Registe (EDMA_ESR)							   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_ESR						(*(volatile uint32 *)(EDMA_BASE_ADDRESS+EDMA_ESR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Enable Request Register (EDMA_ERQRL)						   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_ERQRL						(*(volatile uint32 *)(EDMA_BASE_ADDRESS+EDMA_ERQRL_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Enable Error Interrupt Register (EDMA_EEIRL)				   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_EEIRL						(*(volatile uint32 *)(EDMA_BASE_ADDRESS+EDMA_EEIRL_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Set Enable Request Register (EDMA_SERQR)					   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_SERQR						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_SERQR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Clear Enable Request Register (EDMA_CERQR)					   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_CERQR						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_CERQR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Set Enable Error Interrupt Register (EDMA_SEEI)			   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_SEEI						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_SEEI_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Clear Enable Error Interrupt Register (EDMA_CEEI)			   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_CEEI						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_CEEI_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Clear Interrupt Request Register (EDMA_CIRQR)				   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_CIRQR						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_CIRQR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Clear Error Register (EDMA_CER)							   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_CER						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_CER_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Set START Bit Register (EDMA_SSBR)							   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_SSBR						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_SSBR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Clear DONE Status Register (EDMA_CDSBR)					   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_CDSBR						(*(volatile uint8 *)(EDMA_BASE_ADDRESS+EDMA_CDSBR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Interrupt Request Register (EDMA_IRQRL)					   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_IRQRL						(*(volatile uint32 *)(EDMA_BASE_ADDRESS+EDMA_IRQRL_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Error Register (EDMA_ERL)									   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_ERL						(*(volatile uint32 *)(EDMA_BASE_ADDRESS+EDMA_ERL_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Hardware Request Status Register (EDMA_HRSL)				   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_HRSL						(*(volatile uint32 *)(EDMA_BASE_ADDRESS+EDMA_HRSL_OFFSET))

/*---------------------------------------------------------------------------*/
/***	eDMA Channel n Priority Register ( EDMA_CPR(n) )				   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_CPR(x)						(*(volatile uint8 *)(EDMA_CPR_ADDRESS(x)))

/*---------------------------------------------------------------------------*/
/***	Transfer Control Descriptor ( EDMA_TCD(n) )						   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_TCD(x)						(*(volatile stc_eDMA_TCD *)(EDMA_TCD_ADDRESS(x)))

/*---------------------------------------------------------------------------*/
/***	Channel #n Configuration ( EDMAMUX_CHCONFIG(n) )				   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMAMUX_CHCONFIG(x)				(*(volatile uint8 *)(EDMAMUX_CHCONFIG_ADDRESS(x)))
#define		EDMAMUX_CHCONFIG_SRC_MASK		(0x3F<<0)
#define		EDMAMUX_CHCONFIG_TRIG_MASK		(1<<6)
#define		EDMAMUX_CHCONFIG_ENBL_MASK		(1<<7)

/*---------------------------------------------------------------------------*/
/***	Transfer Control Descriptor (TCD) Structure						   ***/
/*---------------------------------------------------------------------------*/
typedef	struct _eDMA_TCD_ 				/* 32 Bytes */
{
	vuint32_t SADDR;        /* source address */
	
	vuint16_t SMOD:5;       /* source address modulo */
	vuint16_t SSIZE:3;      /* source transfer size */
	vuint16_t DMOD:5;		/* destination address modulo */
	vuint16_t DSIZE:3;		/* destination transfer size */
	vint16_t  SOFF;			/* signed source address offset */

	vuint32_t NBYTES;       /* inner (minor) byte count */

	vint32_t SLAST;         /* last dest Address adjustment, or scatter/gather address (if e_sg = 1) */

	vuint32_t DADDR;        /* destination address */

	union
	{
		struct _stc_CITER_NoLink_
		{
			vuint16_t CITERE_LINK:1;
			vuint16_t CITER:15;		
		} stc_CITER_NoLink;
		
		struct _stc_CITER_Link_
		{
			vuint16_t CITERE_LINK:1;
			vuint16_t CITERLINKCH:6;
			vuint16_t CITER:9;		
		} stc_CITER_Link;
	} un_CITER;

	vint16_t DOFF;          /* signed destination address offset */

	vint32_t DLAST_SGA;

	union
	{
		struct _stc_BITER_NoLink_
		{
			vuint16_t BITERE_LINK:1;        /* beginning ("major") iteration count */
			vuint16_t BITER:15;	
		} stc_BITER_NoLink;
		
		struct _stc_BITER_Link_
		{
			vuint16_t BITERE_LINK:1;        /* beginning (major) iteration count */
			vuint16_t BITERLINKCH:6;
			vuint16_t BITER:9;		
		} stc_BITER_Link;
	} un_BITER;

	vuint16_t BWC:2;        		/* bandwidth control */
	vuint16_t MAJORLINKCH:6;        /* enable channel-to-channel link */
	vuint16_t DONE:1;       		/* channel done */
	vuint16_t ACTIVE:1;     		/* channel active */
	vuint16_t MAJORE_LINK:1;        /* enable channel-to-channel link */
	vuint16_t E_SG:1;       		/* enable scatter/gather descriptor */
	vuint16_t D_REQ:1;      		/* disable ipd_req when done */
	vuint16_t INT_HALF:1;   		/* interrupt on citer = (biter >> 1)  */
	vuint16_t INT_MAJ:1;    		/* interrupt on major loop completion  */
	vuint16_t START:1;      		/* explicit channel start */
	
}	stc_eDMA_TCD;

/*---------------------------------------------------------------------------*/
/***	TCD Structure User												   ***/
/*---------------------------------------------------------------------------*/
typedef	struct _eDMA_TCD_User_ 		/* 48 Bytes */
{
	uint32	SADDR;		/* source address */
	uint8	SMOD;		/* source address modulo */
	uint8	SSIZE;		/* source transfer size */
	uint16	SOFF;		/* signed source address offset */
	uint32	SLAST;      /* last dest Address adjustment, or scatter/gather address (if e_sg = 1) */
	
	uint32	DADDR;		/* destination address */
	uint8	DMOD;		/* destination address modulo */
	uint8	DSIZE;		/* destination transfer size */
	uint16	DOFF;		/* signed destination address offset */
	uint32	DLAST_SGA;
	
	uint32	NBYTES;		/* inner (minor) byte count	*/

	uint8	CITER_LINK_EN;
	uint8	CITER_LINK_CH;
	uint16	CITER;		/* Current ("major") iteration count */

	uint8	BITER_LINK_EN;
	uint8	BITER_LINK_CH;
	uint16	BITER;		/* beginning ("major") iteration count */
     
	uint8	MAJOR_LINK_EN;	/* enable channel-to-channel link */
	uint8	MAJOR_LINK_CH;	/* enable channel-to-channel link */
	uint8	BWC;		/* bandwidth control */
	uint8	E_SG;		/* enable scatter/gather descriptor */
	
	uint8	REQ_CH_DIS;	/* disable ipd_req when done */
	uint8	INT_HALF;	/* interrupt on citer = (biter >> 1)  */
	uint8	INT_MAJ;	/* interrupt on major loop completion  */
	uint8	RSV1;

	uint8	START;		/* explicit channel start */
	uint8	ACTIVE;		/* channel active */	
	uint8	DONE;		/* channel done */
	uint8	RSV2;

}	eDMA_TCD_User;


/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	EMDA Channel enum												   ***/
/*---------------------------------------------------------------------------*/
typedef	enum 
{
	eDMA_Ch_0	= 0,
	eDMA_Ch_1	= 1,
	eDMA_Ch_2	= 2,
	eDMA_Ch_3	= 3,
	eDMA_Ch_4	= 4,
	eDMA_Ch_5	= 5,
	eDMA_Ch_6	= 6,
	eDMA_Ch_7	= 7,
	eDMA_Ch_8	= 8,
	eDMA_Ch_9	= 9,
	eDMA_Ch_10	= 10,
	eDMA_Ch_11	= 11,
	eDMA_Ch_12	= 12,
	eDMA_Ch_13	= 13,
	eDMA_Ch_14	= 14,
	eDMA_Ch_15	= 15
}enum_EDMA_CH; 

/*---------------------------------------------------------------------------*/
/***	EDMAMUX Channel enum											   ***/
/*---------------------------------------------------------------------------*/
typedef	enum 
{
	eDMA_Mux_0	= 0,
	eDMA_Mux_1	= 1,
	eDMA_Mux_2	= 2,
	eDMA_Mux_3	= 3,
	eDMA_Mux_4	= 4,
	eDMA_Mux_5	= 5,
	eDMA_Mux_6	= 6,
	eDMA_Mux_7	= 7,
	eDMA_Mux_8	= 8,
	eDMA_Mux_9	= 9,
	eDMA_Mux_10	= 10,
	eDMA_Mux_11	= 11,
	eDMA_Mux_12	= 12,
	eDMA_Mux_13	= 13,
	eDMA_Mux_14	= 14,
	eDMA_Mux_15	= 15,
	eDMA_Mux_16	= 16,
	eDMA_Mux_17	= 17,
	eDMA_Mux_18	= 18,
	eDMA_Mux_19	= 19,
	eDMA_Mux_20	= 20,
	eDMA_Mux_21	= 21,
	eDMA_Mux_22	= 22,
	eDMA_Mux_23	= 23,
	eDMA_Mux_24	= 24,
	eDMA_Mux_25	= 25,
	eDMA_Mux_26	= 26,
	eDMA_Mux_27	= 27,
	eDMA_Mux_28	= 28,
	eDMA_Mux_29	= 29,
	eDMA_Mux_30	= 30
}enum_EDMA_Mux; 

/*---------------------------------------------------------------------------*/
/***	Source data transfer size										   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_SIZE_8_BIT				0
#define 	EDMA_SIZE_16_BIT			1
#define 	EDMA_SIZE_32_BIT			2
#define 	EDMA_SIZE_64_BIT			3
#define 	EDMA_SIZE_32_BIT_BURST		4
#define 	EDMA_SIZE_32_BYTE_BURST		5

/*---------------------------------------------------------------------------*/
/***	EDMA Mux Source													   ***/
/*---------------------------------------------------------------------------*/
#define 	EDMA_MUX_SRC_DSPI_0_TX		1
#define 	EDMA_MUX_SRC_DSPI_0_RX		2
#define 	EDMA_MUX_SRC_DSPI_1_TX		3
#define 	EDMA_MUX_SRC_DSPI_1_RX		4
#define 	EDMA_MUX_SRC_DSPI_2_TX		5
#define 	EDMA_MUX_SRC_DSPI_2_RX		6
#define 	EDMA_MUX_SRC_DSPI_3_TX		7
#define 	EDMA_MUX_SRC_DSPI_3_RX		8
#define 	EDMA_MUX_SRC_CTU_CONFIG		9
#define 	EDMA_MUX_SRC_CTU_FIFO_1		10
#define 	EDMA_MUX_SRC_CTU_FIFO_2		11
#define 	EDMA_MUX_SRC_CTU_FIFO_3		12
#define 	EDMA_MUX_SRC_CTU_FIFO_4		13
#define 	EDMA_MUX_SRC_PWM_WR			14
#define 	EDMA_MUX_SRC_PWM_RD			15
#define 	EDMA_MUX_SRC_ETIME0_CH_0	16
#define 	EDMA_MUX_SRC_ETIME0_CH_1	17
#define 	EDMA_MUX_SRC_ETIME1_CH_0	18
#define 	EDMA_MUX_SRC_ETIME1_CH_1	19
#define 	EDMA_MUX_SRC_ADC_0			20
#define 	EDMA_MUX_SRC_ADC_1			21

/*---------------------------------------------------------------------------*/
/***	DSPI Source Address												   ***/
/*---------------------------------------------------------------------------*/
#define		DSPI0_TX_PUSHR				0xFFF90034
#define		DSPI0_RX_POPR				0xFFF90038
#define		DSPI0_RX_POPR_2BYTE			0xFFF9003A
#define		DSPI1_TX_PUSHR				0xFFF94034
#define		DSPI1_RX_POPR				0xFFF94038
#define		DSPI1_RX_POPR_2BYTE			0xFFF9403A
#define		DSPI2_TX_PUSHR				0xFFF98034
#define		DSPI2_RX_POPR				0xFFF98038
#define		DSPI2_RX_POPR_2BYTE			0xFFF9803A
#define		DSPI3_TX_PUSHR				0xFFF9C034
#define		DSPI3_RX_POPR				0xFFF9C038
#define		DSPI3_RX_POPR_2BYTE			0xFFF9C03A

/*---------------------------------------------------------------------------*/
/***	CTU_FIFO_n Address												   ***/
/*---------------------------------------------------------------------------*/
#define 	CTU_FIFO_1_FR 				0xFFE0C080
#define 	CTU_FIFO_2_FR 				0xFFE0C084
#define 	CTU_FIFO_3_FR 				0xFFE0C088
#define 	CTU_FIFO_4_FR 				0xFFE0C08C
#define 	CTU_FIFO_1_FR_2BYTE 		0xFFE0C082
#define 	CTU_FIFO_2_FR_2BYTE 		0xFFE0C086
#define 	CTU_FIFO_3_FR_2BYTE			0xFFE0C08A
#define 	CTU_FIFO_4_FR_2BYTE 		0xFFE0C08E
#define 	CTU_FIFO_1_FL 				0xFFE0C0A0
#define 	CTU_FIFO_2_FL 				0xFFE0C0A4
#define 	CTU_FIFO_3_FL 				0xFFE0C0A8
#define 	CTU_FIFO_4_FL 				0xFFE0C0AC
#define 	CTU_FIFO_1_FL_2BYTE 		0xFFE0C0A2
#define 	CTU_FIFO_2_FL_2BYTE 		0xFFE0C0A6
#define 	CTU_FIFO_3_FL_2BYTE			0xFFE0C0AA
#define 	CTU_FIFO_4_FL_2BYTE 		0xFFE0C0AE


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_EDMA_DRV_EXT	void	mEDMA_CTU_FIFO_Init(void);
M_EDMA_DRV_EXT	void	mEDMA_Hard_Req_En(enum_EDMA_CH EDMA_Chan);
M_EDMA_DRV_EXT	void	mEDMA_Hard_Req_Dis(enum_EDMA_CH EDMA_Chan);


#endif	

