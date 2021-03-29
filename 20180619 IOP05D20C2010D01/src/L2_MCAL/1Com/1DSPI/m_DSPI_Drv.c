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
* @brief    DSPI module Function, Init, Tx, Rx, different Config
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/07/06      CODER2       	   	N/A          Original
*     1.1        2012/09/05      CODER2			N/A          Modify include file
*     1.2        2012/09/13      CODER2			N/A          Add CTAS Function
*     1.3        2012/09/14      ----			N/A          deliver to ChuangQu
*     1.4        2012/09/27      CODER2			N/A          Add Cfg file
*     1.5        2012/10/10      CODER2			N/A          Add CTAR_Tx Function
*     1.6        2012/10/10      CODER2			N/A          Change CTAS for CATS
*     1.7        2012/11/02      CODER2			N/A          Add History Comment
*     1.8        2013/03/01      CODER2			N/A          Code Simplify, Delete Reg_Bit Functions
*******************************************************************************/

#ifndef M_DSPI_DRV_C
#define M_DSPI_DRV_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_DSPI_Drv.h"
#include 	"m_DSPI_Cfg.h"
#include    "SysConfig.h"



/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mDSPI_Module_En
   Description:     Enable DSPI clock, Enable DSPI module
   Parameters:      Input:    
   						ModuleNum:	Module Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mDSPI_Module_En(uint8 ModuleNum)
{
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_MDIS_MASK);	
}


/* *****************************************************************************
   Function:        mDSPI_Module_En
   Description:     Disable DSPI clock, put DSPI in a software controlled power-saving state.
   Parameters:      Input:    
   						ModuleNum:	Module Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mDSPI_Module_Dis(uint8 ModuleNum)
{
	DSPI_MCR(ModuleNum) |= DSPI_MCR_MDIS_MASK;	
}


/* *****************************************************************************
   Function:        mDSPI_Module_Start
   Description:     Start DSPI transfer
   Parameters:      Input:    
   						ModuleNum:	Module Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mDSPI_Module_Start(uint8 ModuleNum)
{
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_HALT_MASK);	
}


/* *****************************************************************************
   Function:        mDSPI_Module_Stop
   Description:     Stop DSPI transfer
   Parameters:      Input:    
   						ModuleNum:	Module Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mDSPI_Module_Stop(uint8 ModuleNum)
{
	DSPI_MCR(ModuleNum) |= DSPI_MCR_HALT_MASK;	
}


/* *****************************************************************************
   Function:        mDSPI_BaudRateSet
   Description:     Set DSPI BaudRate
   Parameters:      Input:
   						ModuleNum:	Module Index
   						ChanNum:	CTAR Reg Index
   						dbr:		Double Baud Rate
   						pbr:		Baud Rate Prescale
   						br:			Baud Rate Scaler
                    Output:   None
   Notes:           
		BaundRate = (Fbus*(1+DBR)) /(PBR*BR)                   
   ***************************************************************************** */
static	void	mDSPI_BaudRateSet(uint8 ModuleNum, uint8 ChanNum, uint32 dbr,uint32 pbr,uint32 br)
{
   br |= (dbr<<31)|(pbr<<16);
   DSPI_CTAR(ModuleNum, ChanNum) &= (~(DSPI_CTAR_DBR_MASK|DSPI_CTAR_PBR_MASK|DSPI_CTAR_BR_MASK));
   DSPI_CTAR(ModuleNum, ChanNum) |= br;	
}


/* *****************************************************************************
   Function:        mDSPI_Intc_En
   Description:     Set DSPI Intc Source Enable
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						IntcSrc:	INTC Source
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mDSPI_Intc_En(uint8 ModuleNum, uint8 IntcSrc)
{
	switch(IntcSrc)
	{
		case SPI_TCF:		/* Transmission complete request enable */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_TCF_MASK;
			break;
		case SPI_EOQF:		/* DSPI finished request enable */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_EQQF_MASK;
			break;
		case SPI_TFUF:		/* Transmit FIFO underflow request enable */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_TFUF_MASK;
			break;
		case SPI_TFFF_INT:	/* Transmit FIFO fill Interrupt request enable */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_TFFF_MASK;
			DSPI_RSER(ModuleNum) &= (~DSPI_RSER_TFFFDIR_MASK);
			break;
		case SPI_TFFF_DMA:	/* Transmit FIFO fill DMA request */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_TFFF_MASK;
			DSPI_RSER(ModuleNum) |= (DSPI_RSER_TFFFDIR_MASK);
			break;
		case SPI_RFOF:		/* Receive FIFO overflow request enable */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_RFOF_MASK;
			break;
		case SPI_RFDF_INT:	/* Receive FIFO drain Intc request enable */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_RFRD_MASK;
			DSPI_RSER(ModuleNum) &= (~DSPI_RSER_RFRDDIR_MASK);
			break;
		case SPI_RFDF_DMA:	/* Receive FIFO drain DMA request enable */
			DSPI_RSER(ModuleNum) |= DSPI_RSER_RFRD_MASK;
			DSPI_RSER(ModuleNum) |= (DSPI_RSER_RFRDDIR_MASK);
			break;
		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mDSPI_PUSH_CTAS_Set
   Description:     Select Clock and Transfer attributes
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						value:		CTAS Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mDSPI_PUSH_CTAS_Set(uint8 ModuleNum, uint32 value)
{
	uint16	RxDataTmp;

	DSPI_PUSHR(ModuleNum) &= (~DSPI_PUSHR_CTAS_MASK);
	DSPI_PUSHR(ModuleNum) |= ( (value & 0x07) <<28);	

	(void)mDSPI_Data_Rx16(ModuleNum, DSPI_CS0, &RxDataTmp);	
}


/* *****************************************************************************
   Function:        mDSPI_ByteRx
   Description:     Receive Data from DSPI, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
static	uint8	mDSPI_ByteRx(uint8 moduleNum, uint8 *pRxData)
{    
    uint8 returnVal;
    
	returnVal = FALSE;
	/* Check if RX FIFO is not empty */
    returnVal = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_RFRD_MASK, DSPI_SR_RFRD_MASK, DSPI_DELAY);
    
    if(returnVal == TRUE)
    {
    	/* Read Rx FIFO Data */
        *pRxData = (uint8)DSPI_POPR(moduleNum);
        DSPI_SR(moduleNum) = DSPI_SR_RFRD_MASK|DSPI_SR_TCF_MASK|DSPI_RSER_EQQF_MASK;
    }
    else
    {
        returnVal = FALSE;
    }

    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_ByteTx
   Description:     Transfer Data to DSPI, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
static	uint8	mDSPI_ByteTx(uint8 moduleNum, uint8 ChanNum, uint8 txData)
{
    uint8 	returnVal;
    uint32	txDataTmp;
    
	returnVal = FALSE;
	/* Remain the CTAS Config */
	txDataTmp = DSPI_PUSHR(moduleNum) & DSPI_PUSHR_CTAS_MASK;
	/* Select Peripheral chip select */
	txDataTmp |= (1<<(ChanNum+16));
	/* Check if TX FIFO is not full */
    returnVal = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TFFF_MASK, DSPI_SR_TFFF_MASK, DSPI_DELAY);
    
    if(returnVal == TRUE)
    {
		/* CS0 Beware */
		/* end of Queue, Clear SPI Transfer Counter */
		txDataTmp |= txData|DSPI_SINGLE_TRANSMIT; 
        DSPI_PUSHR(moduleNum) = txDataTmp;
        
        /* Check if Transfer Complete */
        if(TRUE == OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TCF_MASK, DSPI_SR_TCF_MASK, DSPI_DELAY))
        {
            #if(SPI_TXFIFO_EN == SPI_OFF)
                REG32_BIT_SET(DSPI_MCR(moduleNum), DSPI_MCR_CLR_TXF_MASK);	/* Tx FIFO Clear Contents */
            #endif
            
        	DSPI_SR(moduleNum) = DSPI_SR_TCF_MASK;
        }
        else
        {
        	returnVal = FALSE;	
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx8
   Description:     Transfer Data to DSPI and then Received Data from DSPI, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						txData:		Data to be Transfered
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx8(uint8 moduleNum, uint8 ChanNum, uint8 txData, uint8 *pRxData)
{ 
    uint8 returnVal;
    uint8 idlePointer;
    
    returnVal = FALSE;
    if(pRxData == DSPI_NULL)
    {
        pRxData = &idlePointer; 
    }
    else
    {
        /* do nothing */
    }
    
    if(mDSPI_ByteTx(moduleNum, ChanNum, txData) == TRUE)	/* Transfer txData to DSPI */
    {
        if(mDSPI_ByteRx(moduleNum, pRxData) == TRUE) 		/* Received *pRxData from DSPI */                     
        {
            returnVal = TRUE;
        }
        else
        {
            returnVal = FALSE;
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_Tx8
   Description:     Transfer Data to DSPI, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Tx8(uint8 moduleNum, uint8 ChanNum, uint8 txData)
{
    return(mDSPI_Data_TxRx8(moduleNum, ChanNum, txData, DSPI_NULL));
}


/* *****************************************************************************
   Function:        mDSPI_Data_Rx8
   Description:     Receive Data from DSPI, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Rx8(uint8 moduleNum, uint8 ChanNum, uint8 *pRxData)
{
    return(mDSPI_Data_TxRx8(moduleNum, ChanNum, DSPI_DUMMY_DATA, pRxData));
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx8_N
   Description:     Transfer Data to DSPI and then Received Data from DSPI, 
   					Data Width is 8-bit, Data Length N
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						*pTxData:	Data to be Transfered, Array
   						*pRxData:	Data to be Received, Array
   						len:		Data Counts
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx8_N(uint8 moduleNum, uint8 ChanNum, uint8 *pTxData, uint8 *pRxData, uint16 len)
{ 
    uint8 returnVal;
    
    returnVal = TRUE;
    while((len > 0) && (returnVal == TRUE))
    {
    	/* Transfer and Received once a byte */
        returnVal = mDSPI_Data_TxRx8(moduleNum, ChanNum, *pTxData, pRxData);
        if(returnVal == TRUE)
        {
            pTxData++;
            pRxData++;
        }
        else
        {
            /* do nothing */
        } 
        len--;  
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_WordRx
   Description:     Receive Data from DSPI, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
static	uint8	mDSPI_WordRx(uint8 moduleNum, uint16 *pRxData)
{    
    uint8 returnVal = DSPI_OK;
    
	returnVal = FALSE;
	/* Check if RX FIFO is not empty */
    returnVal = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_RFRD_MASK, DSPI_SR_RFRD_MASK, DSPI_DELAY);
    if(returnVal == TRUE)
    {
    	/* Read Rx FIFO Data */
        *pRxData = (uint16)DSPI_POPR(moduleNum);
        DSPI_SR(moduleNum) = DSPI_SR_RFRD_MASK|DSPI_SR_TCF_MASK|DSPI_RSER_EQQF_MASK;
    }
    else
    {
        returnVal = FALSE;
    }

    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_WordTx
   Description:     Transfer Data to DSPI, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
static	uint8	mDSPI_WordTx(uint8 moduleNum, uint8 ChanNum, uint16 txData)
{
    uint8 returnVal;
    uint32	txDataTmp;
    
	returnVal = FALSE;
	/* Remain the CTAS Config */
	txDataTmp = DSPI_PUSHR(moduleNum) & DSPI_PUSHR_CTAS_MASK;
	/* Select Peripheral chip select */
	txDataTmp |= (1<<(ChanNum+16));
	/* Check if TX FIFO is not full */
    returnVal = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TFFF_MASK, DSPI_SR_TFFF_MASK, DSPI_DELAY);
    
    if(returnVal == TRUE)
    {
    	/* end of Queue, Clear SPI Transfer Counter */
    	txDataTmp |= txData|DSPI_SINGLE_TRANSMIT;
        DSPI_PUSHR(moduleNum) = txDataTmp;
        
        /* Check if Transfer Complete */
        if(TRUE == OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TCF_MASK, DSPI_SR_TCF_MASK, DSPI_DELAY))
        {
        	/* Without REG32_BIT_SET(DSPI_MCR(moduleNum), DSPI_MCR_CLR_TXF_MASK);	/* Tx FIFO Clear Contents */
        	DSPI_SR(moduleNum) = DSPI_SR_TCF_MASK;
        }
        else
        {
        	returnVal = FALSE;	
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx16
   Description:     Transfer Data to DSPI and then Received Data from DSPI, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						txData:		Data to be Transfered
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx16(uint8 moduleNum, uint8 ChanNum, uint16 txData, uint16 *pRxData)
{
    uint8	returnVal;
    uint16	idlePointer;
    
    returnVal = FALSE;
    if(pRxData == DSPI_NULL)
    {
        pRxData = &idlePointer; 
    }
    else
    {
        /* do nothing */
    }
    
    if(mDSPI_WordTx(moduleNum, ChanNum, txData) == TRUE)	/* Transfer txData to DSPI */
    {
        if(mDSPI_WordRx(moduleNum, pRxData) == TRUE)		/* Received *pRxData from DSPI */
        {
            returnVal = TRUE;
        }
        else
        {
            returnVal = FALSE;
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_Tx16
   Description:     Transfer Data to DSPI, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Tx16(uint8 moduleNum, uint8 ChanNum, uint16 tData)
{  
    return(mDSPI_Data_TxRx16(moduleNum, ChanNum, tData, DSPI_NULL));
}


/* *****************************************************************************
   Function:        mDSPI_Data_Rx16
   Description:     Receive Data from DSPI, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Rx16(uint8 moduleNum, uint8 ChanNum, uint16 *pRxData)
{   
    return(mDSPI_Data_TxRx16(moduleNum, ChanNum, DSPI_DUMMY_DATA, pRxData));
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx16_N
   Description:     Transfer Data to DSPI and then Received Data from DSPI, 
   					Data Width is 16-bit, Data Length N
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						*pTxData:	Data to be Transfered, Array
   						*pRxData:	Data to be Received, Array
   						len:		Data Counts
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx16_N(uint8 moduleNum, uint8 ChanNum, uint16 *pTxData, uint16 *pRxData, uint16 len)
{ 
    uint8 returnVal;
    
    returnVal = TRUE;
    while((len > 0) && (returnVal == TRUE))
    {
    	/* Transfer and Received once a 16-bit */
        returnVal = mDSPI_Data_TxRx16(moduleNum, ChanNum, *pTxData, pRxData);
        if(returnVal == TRUE)
        {
            pTxData++;
            pRxData++;
        }
        else
        {
            /* do nothing */ 
        }  
        len--; 
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_TxConfig
   Description:     Config Tx Attributes, CTAS and Chip Select
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						CS:			PCS0бл7, Peripheral chip select
   						CTAS:		CTAR Reg Index
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mDSPI_TxConfig(uint8 moduleNum, uint16 CS, uint16 CTAS)
{
    /* DSPI_PUSHR_H(moduleNum) &= (~DSPI_PUSHR_H_PCS_MASK); */
	DSPI_PUSHR_H(moduleNum) = (CTAS<<12) | CS;
}

/* *****************************************************************************
   Function:        mDSPI_ByteTx_CTAS
   Description:     Transfer Data to DSPI, using User define CTAS, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
static	uint8	mDSPI_ByteTx_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 txData)
{
    uint8 	returnVal;
    uint32	txDataTmp;
    uint32	Ctar_Tmp;
    
	returnVal = FALSE;
	/* Select CTAS Config */
	Ctar_Tmp = Ctar_Val & 0x07;
	/* Select Peripheral chip select */
	txDataTmp = (1<<(ChanNum+16));
	/* Check if TX FIFO is not full */
    returnVal = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TFFF_MASK, DSPI_SR_TFFF_MASK, DSPI_DELAY);
    
    if(returnVal == TRUE)
    {
		/* Clock and transfer attributes Selected (CTAR) */
		txDataTmp |= txData|DSPI_SINGLE_TRANSMIT|(Ctar_Tmp<<28);
        DSPI_PUSHR(moduleNum) = txDataTmp;
        
        /* Check if Transfer Complete */
        if(TRUE == OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TCF_MASK, DSPI_SR_TCF_MASK, DSPI_DELAY))
        {
            #if(SPI_TXFIFO_EN == SPI_OFF)
                REG32_BIT_SET(DSPI_MCR(moduleNum), DSPI_MCR_CLR_TXF_MASK);	/* Tx FIFO Clear Contents */
            #endif
            
        	DSPI_SR(moduleNum) = DSPI_SR_TCF_MASK;
        }
        else
        {
        	returnVal = FALSE;	
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx8_CTAS
   Description:     Transfer Data to DSPI and then Received Data from DSPI, 
   					using User-define CTAS, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						txData:		Data to be Transfered
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx8_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 txData, uint8 *pRxData)
{ 
    uint8 returnVal;
    uint8 idlePointer;
    
    returnVal = FALSE;
    if(pRxData == DSPI_NULL)
    {
        pRxData = &idlePointer; 
    }
    else
    {
        /* do nothing */
    }
    
    if(mDSPI_ByteTx_CTAS(moduleNum, ChanNum, Ctar_Val, txData) == TRUE)	/* Transfer txData to DSPI */
    {
        if(mDSPI_ByteRx(moduleNum, pRxData) == TRUE) 					/* Received *pRxData from DSPI */
        {
            returnVal = TRUE;
        }
        else
        {
            returnVal = FALSE;
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_Tx8_CTAS
   Description:     Transfer Data to DSPI, using User-define CTAS, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Tx8_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 txData)
{
    return(mDSPI_Data_TxRx8_CTAS(moduleNum, ChanNum, Ctar_Val, txData, DSPI_NULL));
}


/* *****************************************************************************
   Function:        mDSPI_Data_Rx8_CTAS
   Description:     Receive Data from DSPI, using User-define CTAS, Data Width is 8-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Rx8_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 *pRxData)
{
    return(mDSPI_Data_TxRx8_CTAS(moduleNum, ChanNum, Ctar_Val, DSPI_DUMMY_DATA, pRxData));
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx8_N_CTAS
   Description:     Transfer Data to DSPI and then Received Data from DSPI, 
   					using User-define CTAS, Data Width is 8-bit, Data Length N
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						*pTxData:	Data to be Transfered, Array
   						*pRxData:	Data to be Received, Array
   						len:		Data Counts
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx8_N_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint8 *pTxData, uint8 *pRxData, uint16 len)
{ 
    uint8 returnVal;
    
    returnVal = TRUE;
    while((len > 0) && (returnVal == TRUE))
    {
    	/* Transfer and Received once a byte */
        returnVal = mDSPI_Data_TxRx8_CTAS(moduleNum, ChanNum, Ctar_Val, *pTxData, pRxData);
        if(returnVal == TRUE)
        {
            pTxData++;
            pRxData++;
        }
        else
        {
            /* do nothing */
        } 
        len--;  
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_WordTx_CTAS
   Description:     Transfer Data to DSPI, using User-define CTAS, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
static	uint8	mDSPI_WordTx_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 txData)
{
    uint8 returnVal;
    uint32	txDataTmp;
    uint32	Ctar_Tmp;
    
	returnVal = FALSE;
	/* Select CTAS Config */
	Ctar_Tmp = Ctar_Val & 0x07;
	/* Select Peripheral chip select */
	txDataTmp = (1<<(ChanNum+16));
	/* Check if TX FIFO is not full */
    returnVal = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TFFF_MASK, DSPI_SR_TFFF_MASK, DSPI_DELAY);
    
    if(returnVal == TRUE)
    {
    	/* Clock and transfer attributes Selected (CTAR) */
		txDataTmp |= txData|DSPI_SINGLE_TRANSMIT|(Ctar_Tmp<<28);
		DSPI_PUSHR(moduleNum) = txDataTmp;
        
        /* Check if Transfer Complete */
        if(TRUE == OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TCF_MASK, DSPI_SR_TCF_MASK, DSPI_DELAY))
        {
        	/* Without REG32_BIT_SET(DSPI_MCR(moduleNum), DSPI_MCR_CLR_TXF_MASK);	/* Tx FIFO Clear Contents */
        	DSPI_SR(moduleNum) = DSPI_SR_TCF_MASK;
        }
        else
        {
        	returnVal = FALSE;	
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx16_CTAS
   Description:     Transfer Data to DSPI and then Received Data from DSPI, 
   					using User-define CTAS, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						txData:		Data to be Transfered
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx16_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 txData, uint16 *pRxData)
{
    uint8	returnVal;
    uint16	idlePointer;
    
    returnVal = FALSE;
    if(pRxData == DSPI_NULL)
    {
        pRxData = &idlePointer; 
    }
    else
    {
        /* do nothing */
    }
    
    if(mDSPI_WordTx_CTAS(moduleNum, ChanNum, Ctar_Val, txData) == TRUE)	/* Transfer txData to DSPI */
    {
        if(mDSPI_WordRx(moduleNum, pRxData) == TRUE)					/* Received *pRxData from DSPI */
        {
            returnVal = TRUE;
        }
        else
        {
            returnVal = FALSE;
        }
    }
    else
    {
        returnVal = FALSE;
    }
    
    return(returnVal);
}


/* *****************************************************************************
   Function:        mDSPI_Data_Tx16_CTAS
   Description:     Transfer Data to DSPI, using User-define CTAS, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						txData:		Data to be Transfered
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Tx16_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 tData)
{  
    return(mDSPI_Data_TxRx16_CTAS(moduleNum, ChanNum, Ctar_Val, tData, DSPI_NULL));
}


/* *****************************************************************************
   Function:        mDSPI_Data_Rx16_CTAS
   Description:     Receive Data from DSPI, using User-define CTAS, Data Width is 16-bit
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						*pRxData:	Data to be Received
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_Rx16_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 *pRxData)
{   
    return(mDSPI_Data_TxRx16_CTAS(moduleNum, ChanNum, Ctar_Val, DSPI_DUMMY_DATA, pRxData));
}


/* *****************************************************************************
   Function:        mDSPI_Data_TxRx16_N_CTAS
   Description:     Transfer Data to DSPI and then Received Data from DSPI, 
   					using User-define CTAS, Data Width is 16-bit, Data Length N
   Parameters:      Input:    
   						ModuleNum:	Module Index
   						ChanNum:	PCS0бл7, Peripheral chip select
   						Ctar_Val:	CTAS0бл7, Clock and transfer attributes select
   						*pTxData:	Data to be Transfered, Array
   						*pRxData:	Data to be Received, Array
   						len:		Data Counts
                    Output:   Successed or Failed
   Notes:           
                   
   ***************************************************************************** */
uint8	mDSPI_Data_TxRx16_N_CTAS(uint8 moduleNum, uint8 ChanNum, uint8 Ctar_Val, uint16 *pTxData, uint16 *pRxData, uint16 len)
{ 
    uint8 returnVal;
    
    returnVal = TRUE;
    while((len > 0) && (returnVal == TRUE))
    {
    	/* Transfer and Received once a 16-bit */
        returnVal = mDSPI_Data_TxRx16_CTAS(moduleNum, ChanNum, Ctar_Val, *pTxData, pRxData);
        if(returnVal == TRUE)
        {
            pTxData++;
            pRxData++;
        }
        else
        {
            /* do nothing */
        }  
        len--; 
    }
    
    return(returnVal);
}



/* *****************************************************************************
   Function:        mDSPI_Init_Module0
   Description:     Initialze DSPI_0 
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mDSPI_Init_Module0(void)
{
	#ifdef	DSPI0_ENABLE
		REG32_BIT_SET(DSPI_MCR(DSPI0), DSPI_MCR_MSTR_MASK);	/* NODE: MASTER */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI0), DSPI_MCR_CONT_SCKE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI0), DSPI_MCR_FRZ_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI0), DSPI_MCR_MTFE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI0), DSPI_MCR_PCSSE_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI0), DSPI_MCR_ROOE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI0), DSPI_MCR_PCSIS_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI0), (DSPI0_CS<<16));	
		REG32_BIT_CLEAR(DSPI_MCR(DSPI0), DSPI_MCR_DIS_TXF_MASK);	/* Tx FIFO Enabled */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI0), DSPI_MCR_DIS_RXF_MASK);	/* Rx FIFO Enabled */
		REG32_BIT_SET(DSPI_MCR(DSPI0), DSPI_MCR_CLR_RXF_MASK);		/* Rx FIFO Clear Contents */
		REG32_BIT_SET(DSPI_MCR(DSPI0), DSPI_MCR_CLR_TXF_MASK);		/* Tx FIFO Clear Contents */
		
		mDSPI_Module_En(DSPI0);
		mDSPI_Module_Start(DSPI0);
		
		/* GPIO Pin Config */
		/* SIU.PCR[DSPI0_SCK_PIN].R  	= DSPI0_SCK_PCR; */
		
		/* Channel 0 */
		#ifdef	DSPI0_CH0
			DSPI_CTAR(DSPI0, CTAR0) = DSPI0_CH0_CONFIG;
		#endif
		
		/* Channel 1 */
		#ifdef	DSPI0_CH1
			DSPI_CTAR(DSPI0, CTAR1) = DSPI0_CH1_CONFIG;
		#endif
		
		/* Channel 2 */
		#ifdef	DSPI0_CH2
			DSPI_CTAR(DSPI0, CTAR2) = DSPI0_CH2_CONFIG;
		#endif
		
		/* Channel 3 */
		#ifdef	DSPI0_CH3
			DSPI_CTAR(DSPI0, CTAR3) = DSPI0_CH3_CONFIG;
		#endif
		
		/* Channel 4 */
		#ifdef	DSPI0_CH4
			DSPI_CTAR(DSPI0, CTAR4) = DSPI0_CH4_CONFIG;
		#endif
		
		/* Channel 5 */
		#ifdef	DSPI0_CH5
			DSPI_CTAR(DSPI0, CTAR5) = DSPI0_CH5_CONFIG;
		#endif
		
		/* Channel 6 */
		#ifdef	DSPI0_CH6
			DSPI_CTAR(DSPI0, CTAR6) = DSPI0_CH6_CONFIG;
		#endif
		
		/* Channel 7 */
		#ifdef	DSPI0_CH7
			DSPI_CTAR(DSPI0, CTAR7) = DSPI0_CH7_CONFIG;
		#endif
		
		/* INTC Source */
		#ifdef	DSPI0_INTC_ENABLE
			mDSPI_Intc_En(DSPI0, SPI_TCF);
			mDSPI_Intc_En(DSPI0, SPI_EOQF);
			mDSPI_Intc_En(DSPI0, SPI_TFUF);
			mDSPI_Intc_En(DSPI0, SPI_TFFF_INT);
			mDSPI_Intc_En(DSPI0, SPI_TFFF_DMA);
			mDSPI_Intc_En(DSPI0, SPI_RFOF);
			mDSPI_Intc_En(DSPI0, SPI_RFDF_INT);
			mDSPI_Intc_En(DSPI0, SPI_RFDF_DMA);
		#endif
	#endif	
}


/* *****************************************************************************
   Function:        mDSPI_Init_Module1
   Description:     Initialize DSPI_1
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mDSPI_Init_Module1(void)
{
	#ifdef	DSPI1_ENABLE
		REG32_BIT_SET(DSPI_MCR(DSPI1), DSPI_MCR_MSTR_MASK);	/* NODE: MASTER */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI1), DSPI_MCR_CONT_SCKE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI1), DSPI_MCR_FRZ_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI1), DSPI_MCR_MTFE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI1), DSPI_MCR_PCSSE_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI1), DSPI_MCR_ROOE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI1), DSPI_MCR_PCSIS_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI1), (DSPI1_CS<<16));	
		REG32_BIT_CLEAR(DSPI_MCR(DSPI1), DSPI_MCR_DIS_TXF_MASK);	/* Tx FIFO Enabled */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI1), DSPI_MCR_DIS_RXF_MASK);	/* Rx FIFO Enabled */
		REG32_BIT_SET(DSPI_MCR(DSPI1), DSPI_MCR_CLR_RXF_MASK);		/* Rx FIFO Clear Contents */
		REG32_BIT_SET(DSPI_MCR(DSPI1), DSPI_MCR_CLR_TXF_MASK);		/* Tx FIFO Clear Contents */
		
		mDSPI_Module_En(DSPI1);
		mDSPI_Module_Start(DSPI1);
		
		/* GPIO Pin Config */ 
		SIU.PCR[DSPI1_SCK_PIN].R  	= DSPI1_SCK_PCR;
		SIU.PCR[DSPI1_OUT_PIN].R  	= DSPI1_OUT_PCR;
		SIU.PCR[DSPI1_IN_PIN].R  	= DSPI1_IN_PCR;
		SIU.PCR[DSPI1_CS0_PIN].R  	= DSPI1_CS0_PCR;
		SIU.PCR[DSPI1_CS1_PIN].R  	= DSPI1_CS1_PCR;
		SIU.PCR[DSPI1_CS2_PIN].R  	= DSPI1_CS2_PCR;
		
		
		/* Channel 0 */
		#ifdef	DSPI1_CH0
			DSPI_CTAR(DSPI1, CTAR0) = DSPI1_CH0_CONFIG;					
		#endif
		
		/* Channel 1 */
		#ifdef	DSPI1_CH1
			DSPI_CTAR(DSPI1, CTAR1) = DSPI1_CH1_CONFIG;
		#endif
		
		/* Channel 2 */
		#ifdef	DSPI1_CH2
			DSPI_CTAR(DSPI1, CTAR2) = DSPI1_CH2_CONFIG;
		#endif
		
		/* Channel 3 */
		#ifdef	DSPI1_CH3
			DSPI_CTAR(DSPI1, CTAR3) = DSPI1_CH3_CONFIG;
		#endif
		
		/* INTC Source */
		#ifdef	DSPI1_INTC_ENABLE
			mDSPI_Intc_En(DSPI1, SPI_TCF);
			mDSPI_Intc_En(DSPI1, SPI_EOQF);
			mDSPI_Intc_En(DSPI1, SPI_TFUF);
			mDSPI_Intc_En(DSPI1, SPI_TFFF_INT);
			mDSPI_Intc_En(DSPI1, SPI_TFFF_DMA);
			mDSPI_Intc_En(DSPI1, SPI_RFOF);
			mDSPI_Intc_En(DSPI1, SPI_RFDF_INT);
			mDSPI_Intc_En(DSPI1, SPI_RFDF_DMA);
		#endif
	#endif	
}


/* *****************************************************************************
   Function:        mDSPI_Init_Module2
   Description:     Initialize DSPI_2
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mDSPI_Init_Module2(void)
{
	#ifdef	DSPI2_ENABLE
		REG32_BIT_SET(DSPI_MCR(DSPI2), DSPI_MCR_MSTR_MASK);	/* NODE: MASTER */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI2), DSPI_MCR_CONT_SCKE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI2), DSPI_MCR_FRZ_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI2), DSPI_MCR_MTFE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI2), DSPI_MCR_PCSSE_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI2), DSPI_MCR_ROOE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI2), DSPI_MCR_PCSIS_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI2), (DSPI2_CS<<16));	
		REG32_BIT_CLEAR(DSPI_MCR(DSPI2), DSPI_MCR_DIS_TXF_MASK);	/* Tx FIFO Enabled */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI2), DSPI_MCR_DIS_RXF_MASK);	/* Rx FIFO Enabled */
		REG32_BIT_SET(DSPI_MCR(DSPI2), DSPI_MCR_CLR_RXF_MASK);		/* Rx FIFO Clear Contents */
		REG32_BIT_SET(DSPI_MCR(DSPI2), DSPI_MCR_CLR_TXF_MASK);		/* Tx FIFO Clear Contents */
		
		mDSPI_Module_En(DSPI2);
		mDSPI_Module_Start(DSPI2);
		
		/* GPIO Pin Config */ 
		/* SIU.PCR[DSPI2_SCK_PIN].R  	= DSPI2_SCK_PCR; */
		
		/* Channel 0 */
		#ifdef	DSPI2_CH0
			DSPI_CTAR(DSPI2, CTAR0) = DSPI2_CH0_CONFIG;					
		#endif
		
		/* Channel 1 */
		#ifdef	DSPI2_CH1
			DSPI_CTAR(DSPI2, CTAR1) = DSPI2_CH1_CONFIG;
		#endif
		
		/* Channel 2 */
		#ifdef	DSPI2_CH2
			DSPI_CTAR(DSPI2, CTAR2) = DSPI2_CH2_CONFIG;
		#endif
		
		/* Channel 3 */
		#ifdef	DSPI2_CH3
			DSPI_CTAR(DSPI2, CTAR3) = DSPI2_CH3_CONFIG;
		#endif
		
		/* INTC Source */
		#ifdef	DSPI2_INTC_ENABLE
			mDSPI_Intc_En(DSPI2, SPI_TCF);
			mDSPI_Intc_En(DSPI2, SPI_EOQF);
			mDSPI_Intc_En(DSPI2, SPI_TFUF);
			mDSPI_Intc_En(DSPI2, SPI_TFFF_INT);
			mDSPI_Intc_En(DSPI2, SPI_TFFF_DMA);
			mDSPI_Intc_En(DSPI2, SPI_RFOF);
			mDSPI_Intc_En(DSPI2, SPI_RFDF_INT);
			mDSPI_Intc_En(DSPI2, SPI_RFDF_DMA);
		#endif
	#endif	
}


/* *****************************************************************************
   Function:        mDSPI_Init_Module3
   Description:     Initialize DSPI_3
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mDSPI_Init_Module3(void)
{
	#ifdef	DSPI3_ENABLE
		REG32_BIT_SET(DSPI_MCR(DSPI3), DSPI_MCR_MSTR_MASK);	/* NODE: MASTER */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI3), DSPI_MCR_CONT_SCKE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI3), DSPI_MCR_FRZ_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI3), DSPI_MCR_MTFE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI3), DSPI_MCR_PCSSE_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI3), DSPI_MCR_ROOE_MASK);
		REG32_BIT_CLEAR(DSPI_MCR(DSPI3), DSPI_MCR_PCSIS_MASK);
		REG32_BIT_SET(DSPI_MCR(DSPI3), (DSPI3_CS<<16));	
		REG32_BIT_CLEAR(DSPI_MCR(DSPI3), DSPI_MCR_DIS_TXF_MASK);	/* Tx FIFO Enabled */
		REG32_BIT_CLEAR(DSPI_MCR(DSPI3), DSPI_MCR_DIS_RXF_MASK);	/* Rx FIFO Enabled */
		REG32_BIT_SET(DSPI_MCR(DSPI3), DSPI_MCR_CLR_RXF_MASK);		/* Rx FIFO Clear Contents */
		REG32_BIT_SET(DSPI_MCR(DSPI3), DSPI_MCR_CLR_TXF_MASK);		/* Tx FIFO Clear Contents */
		
		mDSPI_Module_En(DSPI3);
		mDSPI_Module_Start(DSPI3);
		
		/* GPIO Pin Config */ 
		SIU.PCR[DSPI3_SCK_PIN].R  	= DSPI3_SCK_PCR;
		SIU.PCR[DSPI3_OUT_PIN].R  	= DSPI3_OUT_PCR;
		SIU.PCR[DSPI3_IN_PIN].R  	= DSPI3_IN_PCR;
		SIU.PCR[DSPI3_CS0_PIN].R  	= DSPI3_CS0_PCR;
		SIU.PCR[DSPI3_CS1_PIN].R  	= DSPI3_CS1_PCR;
		SIU.PSMI[DSPI3_SCK_PSMI].R	= DSPI3_SCK_PSMI_VAL;		/* PSMI SCK */
		SIU.PSMI[DSPI3_IN_PSMI].R	= DSPI3_IN_PSMI_VAL;		/* PSMI SIN_3 */
		SIU.PSMI[DSPI3_CS0_PSMI].R	= DSPI3_CS0_PSMI_VAL;		/* PSMI CS0_3 */
		
	
		/* Channel 0 */
		#ifdef	DSPI3_CH0
			DSPI_CTAR(DSPI3, CTAR0) = DSPI3_CH0_CONFIG;					
		#endif
		
		/* Channel 1 */
		#ifdef	DSPI3_CH1
			DSPI_CTAR(DSPI3, CTAR1) = DSPI3_CH1_CONFIG;
		#endif
		
		/* Channel 2 */
		#ifdef	DSPI3_CH2
			DSPI_CTAR(DSPI3, CTAR2) = DSPI3_CH2_CONFIG;
		#endif
		
		/* Channel 3 */
		#ifdef	DSPI3_CH3
			DSPI_CTAR(DSPI3, CTAR3) = DSPI3_CH3_CONFIG;
		#endif
		
		/* INTC Source */
		#ifdef	DSPI3_INTC_ENABLE
			mDSPI_Intc_En(DSPI3, SPI_TCF);
			mDSPI_Intc_En(DSPI3, SPI_EOQF);
			mDSPI_Intc_En(DSPI3, SPI_TFUF);
			mDSPI_Intc_En(DSPI3, SPI_TFFF_INT);
			mDSPI_Intc_En(DSPI3, SPI_TFFF_DMA);
			mDSPI_Intc_En(DSPI3, SPI_RFOF);
			mDSPI_Intc_En(DSPI3, SPI_RFDF_INT);
			mDSPI_Intc_En(DSPI3, SPI_RFDF_DMA);
		#endif
	#endif	
}


/* *****************************************************************************
   Function:        mDSPI_All_Init
   Description:     Initialize all DSPI
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mDSPI_All_Init(void)
{
	uint8	i;
	
	/*---------------------------------------------------------------------------*/
	/***                 DSPI0 - DSPI3 Reset                                   ***/
	/*---------------------------------------------------------------------------*/

    for(i=0; i<DSPI_NUM; i++)
    {
    	DSPI_MCR(i) 	= 0x0;
    	DSPI_CTAR(i,0)	= 0x38000000;
    	DSPI_CTAR(i,1)	= 0x38000000;
    	DSPI_CTAR(i,2)	= 0x38000000;
    	DSPI_CTAR(i,3)	= 0x38000000;
    	DSPI_CTAR(i,4)	= 0x38000000;
    	DSPI_CTAR(i,5)	= 0x38000000;
    	DSPI_CTAR(i,6)	= 0x38000000;
    	DSPI_CTAR(i,7)	= 0x38000000;
    	DSPI_RSER(i)	= 0x0;
    }
    
    /* DSPI0 Init */
    mDSPI_Init_Module0();
    
    /* DSPI1 Init */
    mDSPI_Init_Module1();

	/* DSPI2 Init */
    mDSPI_Init_Module2();

	/* DSPI3 Init */
    mDSPI_Init_Module3();
}










/* End of file */
