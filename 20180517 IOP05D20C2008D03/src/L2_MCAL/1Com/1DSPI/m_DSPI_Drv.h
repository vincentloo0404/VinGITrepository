/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_DSPI_Drv.h
*
* @brief    Drive Header file for "m_DSPI_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/07/06      Lwt       	   	N/A          Original
*     1.1        2012/09/05      Lwt			N/A          Modify include file
*     1.2        2012/09/13      Lwt			N/A          Add CTAS Function
*     1.3        2012/09/14      jiaoyu			N/A          deliver to ChuangQu
*     1.4        2012/09/27      Lwt			N/A          Add Cfg file
*     1.5        2012/10/10      Lwt			N/A          Add CTAR_Tx Function
*     1.6        2012/11/02      Lwt			N/A          Add History Comment
*     1.7        2013/03/01      Lwt			N/A          Code Simplify, Delete Reg_Bit Functions
************************************************************************************************/

#ifndef _M_DSPI_DRV_H_
#define _M_DSPI_DRV_H_

#ifdef 	M_DSPI_DRV_C
#define M_DSPI_DRV_EXT
#else
#define M_DSPI_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include  	"m_GPIO.h"
#include	"Common.h"



/* *****************************************************************************
   *****************************************************************************
   macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	COMMON DEFINE													   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_OK					1
#define 	DSPI_NOT_OK				0
#define 	DSPI_NULL				((void *)0)
#define 	DSPI_DUMMY_DATA 		0 

/*---------------------------------------------------------------------------*/
/***	Used to config the Single Data Transmit , No Chip Select		   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_SINGLE_TRANSMIT  0x0C000000ul /* 0x1C000000ul */

/*---------------------------------------------------------------------------*/
/***	Moudle Number													   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI0  		0u
#define 	DSPI1  		1u
#define 	DSPI2  		2u
#define 	DSPI3  		3u
#define 	DSPI_NUM  	4u

/*---------------------------------------------------------------------------*/
/***	Channel Config Macro											   ***/
/*---------------------------------------------------------------------------*/
#define 	CTAR0		0u
#define 	CTAR1		1u
#define 	CTAR2		2u
#define 	CTAR3		3u
#define 	CTAR4		4u
#define 	CTAR5		5u
#define 	CTAR6		6u
#define 	CTAR7		7u

/*---------------------------------------------------------------------------*/
/***	Channel Number													   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_CS0	0u
#define 	DSPI_CS1	1u
#define 	DSPI_CS2	2u
#define 	DSPI_CS3	3u
#define 	DSPI_CS4	4u
#define 	DSPI_CS5	5u
#define 	DSPI_CS6	6u
#define 	DSPI_CS7	7u

/*---------------------------------------------------------------------------*/
/***	Auto CS pin Select Parameter									   ***/
/*---------------------------------------------------------------------------*/
#define 	CS_NULL    	0
#define 	CS0    		(1<<0)
#define 	CS1    		(1<<1)
#define 	CS2    		(1<<2)
#define 	CS3    		(1<<3)
#define 	CS4    		(1<<4)
#define 	CS5    		(1<<5)
#define 	CS6    		(1<<6)
#define 	CS7    		(1<<7)

/*---------------------------------------------------------------------------*/
/***	Tx Data Width													   ***/
/*---------------------------------------------------------------------------*/
#define 	SPI_WIDTH(x)			(uint8)((x)-1)	/* x= 4 to 16 */

/*---------------------------------------------------------------------------*/
/***	LSB																   ***/
/*---------------------------------------------------------------------------*/
#define 	SPI_SYS_SHIFT_MSB		(uint8)0x00u   /* Most Significant Bit first */
#define 	SPI_SYS_SHIFT_LSB		(uint8)0x01u   /* Least Significant Bit first */

/*---------------------------------------------------------------------------*/
/***	CPOL & CPHA														   ***/
/*---------------------------------------------------------------------------*/
#define 	SPI_SCK_PHASE_ODD		(uint8)0x01   /* odd edges(1.3.5...)of the SCK clock */
#define 	SPI_SCK_PHASE_EVEN		(uint8)0x00   /* even edges(2.4.6...)of the SCK clock */
#define 	SPI_SCK_POLARITY_HIGH	(uint8)0x01   /* Active-high clocks selected.In idle state SCK is low */
#define 	SPI_SCK_POLARITY_LOW	(uint8)0x00   /* Active-low clocks selected.In idle state SCK is high */

/*---------------------------------------------------------------------------*/
/***	Interrupt source												   ***/
/*---------------------------------------------------------------------------*/
#define 	SPI_TCF					(uint8)0x00u
#define 	SPI_EOQF				(uint8)0x01u
#define 	SPI_TFUF				(uint8)0x02u
#define 	SPI_TFFF_INT			(uint8)0x03u
#define 	SPI_TFFF_DMA			(uint8)0x04u
#define 	SPI_RFOF				(uint8)0x05u
#define 	SPI_RFDF_INT			(uint8)0x06u
#define 	SPI_RFDF_DMA			(uint8)0x07u

/*---------------------------------------------------------------------------*/
/***	Register Address define											   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_BASE_ADDRESS  	  		  0xFFF90000ul
#define 	DSPI_MOUDLE_STEP   		  	  0x4000ul
#define 	DSPI_MOUDLE_BASE_ADDRESS(x)   (DSPI_BASE_ADDRESS+(x)*DSPI_MOUDLE_STEP)
#define 	DSPI_MCR_OFFSET   		      0x0ul
#define 	DSPI_TCR_OFFSET   		      0x8ul
#define 	DSPI_CTAR_OFFSET(x)   	      (0x0Cul+(x)*0x4)	/* CTAR0--CTAR7 */
#define 	DSPI_SR_OFFSET   		      0x2Cul
#define 	DSPI_RSER_OFFSET   		  	  0x30ul
#define 	DSPI_PUSHR_OFFSET   		  0x34ul
#define 	DSPI_POPR_OFFSET   		  	  0x38ul
#define 	DSPI_TXFR_OFFSET(x)   		  (0x3Cul+(x)*0x4)	/* TXFR0--TXFR4 */
#define 	DSPI_RXFR_OFFSET(x)   		  (0x7Cul+(x)*0x4)	/* RXFR0--RXFR4 */

/*---------------------------------------------------------------------------*/
/***	DSPI Module Configuration Register (DSPIx_MCR)					   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_MCR(x)		              (*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_MCR_OFFSET))
#define 	DSPI_MCR_MSTR_MASK  		  (1<<31)
#define 	DSPI_MCR_CONT_SCKE_MASK       (1<<30)
#define 	DSPI_MCR_DCONF_MASK       	  (3<<28)
#define 	DSPI_MCR_FRZ_MASK       	  (1<<27)
#define 	DSPI_MCR_MTFE_MASK       	  (1<<26)
#define 	DSPI_MCR_PCSSE_MASK       	  (1<<25)
#define 	DSPI_MCR_ROOE_MASK       	  (1<<24)
#define 	DSPI_MCR_PCSIS_MASK       	  (0xFF<<16)
#define 	DSPI_MCR_MDIS_MASK       	  (1<<14)
#define 	DSPI_MCR_DIS_TXF_MASK         0x00002000ul
#define 	DSPI_MCR_DIS_RXF_MASK         0x00001000ul
#define 	DSPI_MCR_CLR_TXF_MASK         0x00000800ul
#define 	DSPI_MCR_CLR_RXF_MASK         0x00000400ul
#define 	DSPI_MCR_SMPL_PT_MASK         0x00000300ul
#define 	DSPI_MCR_HALT_MASK  		  0x00000001ul

/*---------------------------------------------------------------------------*/
/***	DSPI Transfer Count Register (DSPIx_TCR)						   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_TCR(x)					(*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_TCR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	DSPI Clock and Transfer Attributes Registers 0--7 (DSPIx_CTARn)	   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_CTAR(x,y)				(*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_CTAR_OFFSET(y)))
#define 	DSPI_CTAR_DBR_MASK			0x80000000ul
#define 	DSPI_CTAR_FMSZ_MASK			0x78000000ul
#define 	DSPI_CTAR_CPOL_MASK			0x04000000ul
#define 	DSPI_CTAR_CPHA_MASK			0x02000000ul
#define 	DSPI_CTAR_LSBFE_MASK		0x01000000ul
#define 	DSPI_CTAR_PBR_MASK			0x00030000ul
#define 	DSPI_CTAR_BR_MASK			0x0000000Ful
#define 	DSPI_CTAR_DELAY_MASK		0x00FCFFF0ul

/*---------------------------------------------------------------------------*/
/***	DSPI Status Register (DSPIx_SR)									   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_SR(x)					(*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_SR_OFFSET))
#define 	DSPI_SR_P(x)				((volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_SR_OFFSET))
#define 	DSPI_SR_TCF_MASK			  0x80000000ul
#define 	DSPI_SR_TXRXS_MASK			  0x40000000ul
#define 	DSPI_SR_EOQF_MASK			  0x10000000ul
#define 	DSPI_SR_TFUF_MASK			  0x08000000ul
#define 	DSPI_SR_TFFF_MASK			  0x02000000ul
#define 	DSPI_SR_RFOF_MASK			  0x00080000ul
#define 	DSPI_SR_RFRD_MASK			  0x00020000ul

/*---------------------------------------------------------------------------*/
/***	DSPI DMA / Interrupt Request Select and Enable Register (DSPIx_RSER)**/
/*---------------------------------------------------------------------------*/
#define 	DSPI_RSER(x)		          (*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_RSER_OFFSET))
#define 	DSPI_RSER_TCF_MASK			  0x80000000ul
#define 	DSPI_RSER_EQQF_MASK			  0x10000000ul
#define 	DSPI_RSER_TFUF_MASK			  0x08000000ul
#define 	DSPI_RSER_TFFF_MASK			  0x02000000ul
#define 	DSPI_RSER_TFFFDIR_MASK		  0x01000000ul
#define 	DSPI_RSER_RFOF_MASK			  0x00080000ul
#define 	DSPI_RSER_RFRD_MASK			  0x00020000ul
#define 	DSPI_RSER_RFRDDIR_MASK		  0x00010000ul

/*---------------------------------------------------------------------------*/
/***	DSPI PUSH TX FIFO Register (DSPIx_PUSHR)						   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_PUSHR(x)		          (*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_PUSHR_OFFSET))
#define 	DSPI_PUSHR_H(x)		          (*(volatile uint16 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_PUSHR_OFFSET))
#define 	DSPI_PUSHR_H_PCS_MASK         0x003Fu
#define 	DSPI_PUSHR_CTAS_MASK		  (0x07<<28)

/*---------------------------------------------------------------------------*/
/***	DSPI POP RX FIFO Register (DSPIx_POPR)							   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_POPR(x)		          (*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_POPR_OFFSET))

/*---------------------------------------------------------------------------*/
/***	DSPI Transmit FIFO Registers 0--4 (DSPIx_TXFRn)					   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_TXFR(x,y)		          (*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_TXFR_OFFSET(y)))

/*---------------------------------------------------------------------------*/
/***	DSPI Receive FIFO Registers 0--4 (DSPIx_RXFRn)					   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_RXFR(x,y)		          (*(volatile uint32 *)(DSPI_MOUDLE_BASE_ADDRESS(x)+DSPI_RXFR_OFFSET(y)))

/*---------------------------------------------------------------------------*/
/***	MACRO FUNCTION													   ***/
/*---------------------------------------------------------------------------*/
#define 	DSPI_CLEAR_TCF(moduleNum) 		{DSPI_SR(moduleNum) |= DSPI_SR_TCF_MASK;}
#define 	DSPI_CLEAR_EOQF(moduleNum) 		{DSPI_SR(moduleNum) |= DSPI_SR_EOQF_MASK;}
#define 	DSPI_CLEAR_TFUF(moduleNum) 		{DSPI_SR(moduleNum) |= DSPI_RSER_TFUF_MASK;}
#define 	DSPI_CLEAR_TFFF(moduleNum) 		{DSPI_SR(moduleNum) |= DSPI_RSER_TFFF_MASK;}
#define 	DSPI_CLEAR_RFOF(moduleNum) 		{DSPI_SR(moduleNum) |= DSPI_RSER_RFOF_MASK;}
#define 	DSPI_CLEAR_RFDF(moduleNum) 		{DSPI_SR(moduleNum) |= DSPI_RSER_RFRD_MASK;}


/* *****************************************************************************
   *****************************************************************************
   APP macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	DSPI APP Macro													   ***/
/*---------------------------------------------------------------------------*/
#define		TRANS_WIDTH_8		SPI_WIDTH(8)	/* 0x07 */
#define		TRANS_WIDTH_16		SPI_WIDTH(16)	/* 0x0F */

#define		DSPI0_CS		(CS0|CS1|CS2|CS3|CS4|CS5|CS6|CS7)
#define		DSPI1_CS		(CS0|CS1|CS2|CS3|CS4|CS5)
#define		DSPI2_CS		(CS0|CS1|CS2|CS3|CS4|CS5)
#define		DSPI3_CS		(CS0|CS1|CS2|CS3|CS4|CS5)

#define		DBR_ON				0x1
#define		DBR_OFF				0x0


/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_DSPI_DRV_EXT	void	mDSPI_Module_En(uint8 ModuleNum);
M_DSPI_DRV_EXT	void	mDSPI_Module_Dis(uint8 ModuleNum);
M_DSPI_DRV_EXT	void	mDSPI_Module_Start(uint8 ModuleNum);
M_DSPI_DRV_EXT	void	mDSPI_Module_Stop(uint8 ModuleNum);

M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx8(uint8 moduleNum, uint8 ChanNum, uint8 txData, uint8 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Tx8(uint8 moduleNum, uint8 ChanNum, uint8 txData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Rx8(uint8 moduleNum, uint8 ChanNum, uint8 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx8_N(uint8 moduleNum, uint8 ChanNum, uint8 *pTxData, uint8 *pRxData, uint16 len);

M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx16(uint8 moduleNum, uint8 ChanNum, uint16 txData, uint16 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Tx16(uint8 moduleNum, uint8 ChanNum, uint16 tData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Rx16(uint8 moduleNum, uint8 ChanNum, uint16 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx16_N(uint8 moduleNum, uint8 ChanNum, uint16 *pTxData, uint16 *pRxData, uint16 len);

M_DSPI_DRV_EXT	void	mDSPI_TxConfig(uint8 moduleNum, uint16 CS, uint16 CTAS);
M_DSPI_DRV_EXT	void	mDSPI_All_Init(void);
M_DSPI_DRV_EXT	void	mDSPI_PUSH_CTAS_Set(uint8 ModuleNum, uint32 value);

M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx8_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 txData, uint8 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Tx8_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 txData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Rx8_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx8_N_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 *pTxData, uint8 *pRxData, uint16 len);

M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx16_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 txData, uint16 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Tx16_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 tData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_Rx16_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 *pRxData);
M_DSPI_DRV_EXT	uint8	mDSPI_Data_TxRx16_N_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 *pTxData, uint16 *pRxData, uint16 len);



#endif	
