/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_EDMA_Drv.c
*
* @brief    eDMA module Function, Set DMA require, Config and INTC_ISR
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/04/12      CODER2       	   	N/A          Original
*******************************************************************************/

#ifndef M_EDMA_DRV_C
#define M_EDMA_DRV_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_EDMA_Drv.h"
#include 	"m_EDMA_Cfg.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mEDMA_Config_TCD
   Description:     Config TCD[n] Settings, save in a TCD_strct variable
   Parameters:      Input:		eDMA_Ch,	DMA Channel Index
   								*pTCD_In,	TCD struct variable
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
static	void	mEDMA_Config_TCD(enum_EDMA_CH eDMA_Ch, eDMA_TCD_User *pTCD_In)
{
	/* Source Config */	
	EDMA_TCD(eDMA_Ch).SADDR		= pTCD_In->SADDR;		/* Source Address */
	EDMA_TCD(eDMA_Ch).SMOD		= pTCD_In->SMOD;		/* Source Address Modulo */
	EDMA_TCD(eDMA_Ch).SSIZE		= pTCD_In->SSIZE;		/* Source Transfer Size */
	EDMA_TCD(eDMA_Ch).SOFF		= pTCD_In->SOFF;		/* Signed Source Addr Offset */
	EDMA_TCD(eDMA_Ch).SLAST		= pTCD_In->SLAST;		/* Last signed Source Address Adjust */
	
	/* Destination Config */
	EDMA_TCD(eDMA_Ch).DADDR		= pTCD_In->DADDR;		/* Destination Address */
	EDMA_TCD(eDMA_Ch).DMOD		= pTCD_In->DMOD;		/* Destination Address Modulo */
	EDMA_TCD(eDMA_Ch).DSIZE		= pTCD_In->DSIZE;		/* Destination Transfer Size */
	EDMA_TCD(eDMA_Ch).DOFF		= pTCD_In->DOFF;		/* Signed Destination Addr Offset */
	EDMA_TCD(eDMA_Ch).DLAST_SGA	= pTCD_In->DLAST_SGA;	/* Signed Destination Address Adjust */

	/* Inner 'minor' byte count */
	EDMA_TCD(eDMA_Ch).NBYTES	= pTCD_In->NBYTES;
	
	/* Current Channel Link */
	if(pTCD_In->CITER_LINK_EN)	/* Enabled */
	{
		EDMA_TCD(eDMA_Ch).un_CITER.stc_CITER_Link.CITERE_LINK = 1;
		EDMA_TCD(eDMA_Ch).un_CITER.stc_CITER_Link.CITERLINKCH = pTCD_In->CITER_LINK_CH;
		EDMA_TCD(eDMA_Ch).un_CITER.stc_CITER_Link.CITER       = pTCD_In->CITER;
	}
	else	/* Disabled */				
	{
		EDMA_TCD(eDMA_Ch).un_CITER.stc_CITER_NoLink.CITERE_LINK = 0;
		EDMA_TCD(eDMA_Ch).un_CITER.stc_CITER_NoLink.CITER       = pTCD_In->CITER;
	}
	
	/* Beginning Channel Link */
	if(pTCD_In->BITER_LINK_EN)	/* Enabled */
	{
		EDMA_TCD(eDMA_Ch).un_BITER.stc_BITER_Link.BITERE_LINK = 1;
		EDMA_TCD(eDMA_Ch).un_BITER.stc_BITER_Link.BITERLINKCH = pTCD_In->BITER_LINK_CH;
		EDMA_TCD(eDMA_Ch).un_BITER.stc_BITER_Link.BITER       = pTCD_In->BITER;
	}
	else	/* Disabled	*/				
	{
		EDMA_TCD(eDMA_Ch).un_BITER.stc_BITER_NoLink.BITERE_LINK = 0;
		EDMA_TCD(eDMA_Ch).un_BITER.stc_BITER_NoLink.BITER       = pTCD_In->BITER;
	}
	
	/* Major Channel Link */
	if(pTCD_In->MAJOR_LINK_EN)	/* Enabled */
	{
		EDMA_TCD(eDMA_Ch).MAJORE_LINK = 1;
		EDMA_TCD(eDMA_Ch).MAJORLINKCH = pTCD_In->MAJOR_LINK_CH;
	}
	else	/* Disabled */
	{
		EDMA_TCD(eDMA_Ch).MAJORE_LINK = 0;
		EDMA_TCD(eDMA_Ch).MAJORLINKCH = 0;
	}
	
	EDMA_TCD(eDMA_Ch).BWC 		= pTCD_In->BWC;			/* Bandwidth control */
	EDMA_TCD(eDMA_Ch).E_SG		= pTCD_In->E_SG;		/* Enable Scatter/Gather: Disabled */

	EDMA_TCD(eDMA_Ch).D_REQ		= pTCD_In->REQ_CH_DIS;	/* Disable the DMA channel when Done */
	EDMA_TCD(eDMA_Ch).INT_HALF	= pTCD_In->INT_HALF;	/* Interrupt on Half Major Count completion */
	EDMA_TCD(eDMA_Ch).INT_MAJ	= pTCD_In->INT_MAJ;		/* Interrupt on major loop completion */
	
	EDMA_TCD(eDMA_Ch).START		= pTCD_In->START;		/* Explicit Channel Start bit */
	EDMA_TCD(eDMA_Ch).ACTIVE	= pTCD_In->ACTIVE;		/* Channel Active */
	EDMA_TCD(eDMA_Ch).DONE		= pTCD_In->DONE;		/* Channel Done */
}


/* *****************************************************************************
   Function:        mEDMA_Hard_Req_En
   Description:     mEDMA Hardware Request Enabled 
   Parameters:      Input:		EDMA_Chan,	DMA Channel
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_Hard_Req_En(enum_EDMA_CH EDMA_Chan)
{
	EDMA_ERQRL |= ( 1<<EDMA_Chan );
}


/* *****************************************************************************
   Function:        mEDMA_Hard_Req_Dis
   Description:     mEDMA Hardware Request Disabled 
   Parameters:      Input:		EDMA_Chan,	DMA Channel
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_Hard_Req_Dis(enum_EDMA_CH EDMA_Chan)
{
	EDMA_ERQRL &= ( ~(1<<EDMA_Chan) );
}


/* *****************************************************************************
   Function:        mEDMA_CTU_FIFO_Init
   Description:     Init EDMA CTU_FIFO, used as ADC sample
   Parameters:      Input:		None
                    Output:   	None
   Notes:           CTU_FIFO Intc and DMA can't be used at the same tine
                   
   ***************************************************************************** */
void	mEDMA_CTU_FIFO_Init(void)
{
	/* Init DMAMUX Config */
#ifdef	EDMA_CTU_FIFO_INDEX_0
	EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_0) = 0;
#endif
#ifdef	EDMA_CTU_FIFO_INDEX_1
	EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_1) = 0;
#endif

	REG32_BIT_SET(EDMA_CR, EDMA_CR_EBDG_MASK);		/* Enable debug */

/* Config TCD[EDMA_CTU_FIFO_INDEX_0] */
#ifdef	EDMA_CTU_FIFO_INDEX_0
	/* Source Config */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).SADDR			= (volatile uint32)EDMA_CTU_FIFO_INDEX_0_SRC_ADDR;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).SMOD			= EDMA_CTU_FIFO_INDEX_0_SMOD;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).SSIZE			= EDMA_CTU_FIFO_INDEX_0_SSIZE;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).SOFF			= EDMA_CTU_FIFO_INDEX_0_SOFF;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).SLAST			= EDMA_CTU_FIFO_INDEX_0_SLAST;
	
	/* Destination Config */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).DADDR			= (volatile uint32)EDMA_CTU_FIFO_INDEX_0_DEST_ADDR;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).DMOD			= EDMA_CTU_FIFO_INDEX_0_DMOD;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).DSIZE			= EDMA_CTU_FIFO_INDEX_0_DSIZE;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).DOFF			= EDMA_CTU_FIFO_INDEX_0_DOFF;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).DLAST_SGA		= EDMA_CTU_FIFO_INDEX_0_DLAST_SGA;
	
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).NBYTES			= EDMA_CTU_FIFO_INDEX_0_NBYTES;

	/* Current Channel Link */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_0_CITER_LINK_EN)
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_CITER.stc_CITER_Link.CITERE_LINK = ENABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_CITER.stc_CITER_Link.CITERLINKCH = EDMA_CTU_FIFO_INDEX_0_CITER_LINK_CH;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_CITER.stc_CITER_Link.CITER       = EDMA_CTU_FIFO_INDEX_0_CITER;
	}
	#else	/* Disabled */					
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_CITER.stc_CITER_NoLink.CITERE_LINK = DISABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_CITER.stc_CITER_NoLink.CITER       = EDMA_CTU_FIFO_INDEX_0_CITER;
	}
	#endif

	/* Beginning Channel Link */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_0_BITER_LINK_EN)
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_BITER.stc_BITER_Link.BITERE_LINK = ENABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_BITER.stc_BITER_Link.BITERLINKCH = EDMA_CTU_FIFO_INDEX_0_BITER_LINK_CH;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_BITER.stc_BITER_Link.BITER       = EDMA_CTU_FIFO_INDEX_0_BITER;
	}
	#else	/* Disabled */				
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_BITER.stc_BITER_NoLink.BITERE_LINK = DISABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).un_BITER.stc_BITER_NoLink.BITER       = EDMA_CTU_FIFO_INDEX_0_BITER;
	}
	#endif	
	
	/* Major Link */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).MAJORE_LINK	= EDMA_CTU_FIFO_INDEX_0_MAJOR_LINK_EN;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).MAJORLINKCH	= EDMA_CTU_FIFO_INDEX_0_MAJOR_LINK_CH;
	
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).BWC			= EDMA_CTU_FIFO_INDEX_0_BWC;		/* Bandwidth control */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).E_SG 		= EDMA_CTU_FIFO_INDEX_0_E_SG;		/* Enable Scatter/Gather: Disabled */

	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).D_REQ 		= EDMA_CTU_FIFO_INDEX_0_REQ_CH_DIS;	/* Disable the DMA channel when Done */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).INT_HALF 	= EDMA_CTU_FIFO_INDEX_0_INT_HALF;	/* Interrupt on Half Major Count completion */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).INT_MAJ 	= EDMA_CTU_FIFO_INDEX_0_INT_MAJ;	/* Interrupt on major loop completion */
	
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).START 		= EDMA_CTU_FIFO_INDEX_0_START;		/* Explicit Channel Start bit */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).ACTIVE 		= EDMA_CTU_FIFO_INDEX_0_ACTIVE;		/* Channel Active */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_0).DONE 		= EDMA_CTU_FIFO_INDEX_0_DONE;		/* Channel Done */
#endif

/* Config TCD[EDMA_CTU_FIFO_INDEX_1] */
#ifdef	EDMA_CTU_FIFO_INDEX_1
	/* Source Config */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).SADDR			= (volatile uint32)EDMA_CTU_FIFO_INDEX_1_SRC_ADDR;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).SMOD			= EDMA_CTU_FIFO_INDEX_1_SMOD;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).SSIZE			= EDMA_CTU_FIFO_INDEX_1_SSIZE;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).SOFF			= EDMA_CTU_FIFO_INDEX_1_SOFF;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).SLAST			= EDMA_CTU_FIFO_INDEX_1_SLAST;
	
	/* Destination Config */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).DADDR			= (volatile uint32)EDMA_CTU_FIFO_INDEX_1_DEST_ADDR;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).DMOD			= EDMA_CTU_FIFO_INDEX_1_DMOD;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).DSIZE			= EDMA_CTU_FIFO_INDEX_1_DSIZE;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).DOFF			= EDMA_CTU_FIFO_INDEX_1_DOFF;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).DLAST_SGA		= EDMA_CTU_FIFO_INDEX_1_DLAST_SGA;
	
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).NBYTES			= EDMA_CTU_FIFO_INDEX_1_NBYTES;

	/* Current Channel Link */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_1_CITER_LINK_EN)
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_CITER.stc_CITER_Link.CITERE_LINK = ENABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_CITER.stc_CITER_Link.CITERLINKCH = EDMA_CTU_FIFO_INDEX_1_CITER_LINK_CH;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_CITER.stc_CITER_Link.CITER       = EDMA_CTU_FIFO_INDEX_1_CITER;
	}
	#else	/* Disabled */				
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_CITER.stc_CITER_NoLink.CITERE_LINK = DISABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_CITER.stc_CITER_NoLink.CITER       = EDMA_CTU_FIFO_INDEX_1_CITER;
	}
	#endif

	/* Beginning Channel Link */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_1_BITER_LINK_EN)
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_BITER.stc_BITER_Link.BITERE_LINK = ENABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_BITER.stc_BITER_Link.BITERLINKCH = EDMA_CTU_FIFO_INDEX_1_BITER_LINK_CH;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_BITER.stc_BITER_Link.BITER       = EDMA_CTU_FIFO_INDEX_1_BITER;
	}
	#else	/* Disabled */					
	{
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_BITER.stc_BITER_NoLink.BITERE_LINK = DISABLE;
		EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).un_BITER.stc_BITER_NoLink.BITER       = EDMA_CTU_FIFO_INDEX_1_BITER;
	}
	#endif	

	/* Major Link */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).MAJORE_LINK		= EDMA_CTU_FIFO_INDEX_1_MAJOR_LINK_EN;
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).MAJORLINKCH		= EDMA_CTU_FIFO_INDEX_1_MAJOR_LINK_CH;
	
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).BWC				= EDMA_CTU_FIFO_INDEX_1_BWC;		/* Bandwidth control */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).E_SG 			= EDMA_CTU_FIFO_INDEX_1_E_SG;		/* Enable Scatter/Gather: Disabled */

	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).D_REQ 			= EDMA_CTU_FIFO_INDEX_1_REQ_CH_DIS;	/* Disable the DMA channel when Done */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).INT_HALF 		= EDMA_CTU_FIFO_INDEX_1_INT_HALF;	/* Interrupt on Half Major Count completion */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).INT_MAJ 		= EDMA_CTU_FIFO_INDEX_1_INT_MAJ;	/* Interrupt on major loop completion */
	
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).START 			= EDMA_CTU_FIFO_INDEX_1_START;		/* Explicit Channel Start bit */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).ACTIVE 			= EDMA_CTU_FIFO_INDEX_1_ACTIVE;		/* Channel Active */
	EDMA_TCD(EDMA_CTU_FIFO_INDEX_1).DONE 			= EDMA_CTU_FIFO_INDEX_1_DONE;		/* Channel Done */
#endif

/* Hardware Req Init */
EDMA_ERQRL = 0;

/* DMAMUX Config */
#ifdef	EDMA_CTU_FIFO_INDEX_0
	/* Enable Channel and choose Source */
	EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_0)  = EDMAMUX_CHCONFIG_ENBL_MASK;
	EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_0) |= EDMA_CTU_FIFO_INDEX_0_SRC;
	/* if PIT time trig */
	#ifdef	EDMA_CTU_FIFO_INDEX_0_TRIG
		EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_0) |= EDMAMUX_CHCONFIG_TRIG_MASK;
	#endif
#endif
#ifdef	EDMA_CTU_FIFO_INDEX_1
	/* Enable Channel and choose Source */
	EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_1)  = EDMAMUX_CHCONFIG_ENBL_MASK;
	EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_1) |= EDMA_CTU_FIFO_INDEX_1_SRC;
	/* if PIT time trig */
	#ifdef	EDMA_CTU_FIFO_INDEX_0_TRIG
		EDMAMUX_CHCONFIG(EDMA_CTU_FIFO_INDEX_1) |= EDMAMUX_CHCONFIG_TRIG_MASK;
	#endif	
#endif	

/* DMA Priority */
#ifdef	EDMA_CTU_FIFO_INDEX_0
	EDMA_CPR(EDMA_CTU_FIFO_INDEX_0) = EDMA_CTU_FIFO_INDEX_0_CPR;
#endif
#ifdef	EDMA_CTU_FIFO_INDEX_1
	EDMA_CPR(EDMA_CTU_FIFO_INDEX_1) = EDMA_CTU_FIFO_INDEX_1_CPR;
#endif

/* Hardware Req Enabled */
#ifdef	EDMA_CTU_FIFO_INDEX_0_HARD_REQ_ENABLED
	EDMA_SERQR = EDMA_CTU_FIFO_INDEX_0;
#endif
#ifdef	EDMA_CTU_FIFO_INDEX_1_HARD_REQ_ENABLED
	EDMA_SERQR = EDMA_CTU_FIFO_INDEX_1;
#endif

/* Explicit Software Req */
#ifdef	EDMA_CTU_FIFO_INDEX_0_SOFT_START
	EDMA_SSBR = EDMA_CTU_FIFO_INDEX_0;
#endif
	
}


#ifdef EDMA_CH0_ISR_EN
extern void pFUN_mEDMA_IRQ11_CH0_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH0_11_ISR
   Description:     Intc Service Rootine , vector 11 for DMA Channel 0
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH0_11_ISR(void)
{
	EDMA.CIRQR.R = 0;
	
	/* User Operation */
	pFUN_mEDMA_IRQ11_CH0_Hook();
}
#endif


#ifdef EDMA_CH1_ISR_EN
extern void pFUN_mEDMA_IRQ12_CH1_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH1_12_ISR
   Description:     Intc Service Rootine , vector 12 for DMA Channel 1
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH1_12_ISR(void)
{
	EDMA.CIRQR.R = 1;
	
	/* User Operation */
	pFUN_mEDMA_IRQ12_CH1_Hook();
}
#endif


#ifdef EDMA_CH2_ISR_EN
extern void pFUN_mEDMA_IRQ13_CH2_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH2_13_ISR
   Description:     Intc Service Rootine , vector 13 for DMA Channel 2
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH2_13_ISR(void)
{
	EDMA.CIRQR.R = 2;
	
	/* User Operation */
	pFUN_mEDMA_IRQ13_CH2_Hook();
}
#endif


#ifdef EDMA_CH3_ISR_EN
extern void pFUN_mEDMA_IRQ14_CH3_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH3_14_ISR
   Description:     Intc Service Rootine , vector 14 for DMA Channel 3
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH3_14_ISR(void)
{
	EDMA.CIRQR.R = 3;
	
	/* User Operation */
	pFUN_mEDMA_IRQ14_CH3_Hook();
}
#endif


#ifdef EDMA_CH4_ISR_EN
extern void pFUN_mEDMA_IRQ15_CH4_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH4_15_ISR
   Description:     Intc Service Rootine , vector 15 for DMA Channel 4
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH4_15_ISR(void)
{
	EDMA.CIRQR.R = 4;
	
	/* User Operation */
	pFUN_mEDMA_IRQ15_CH4_Hook();
}
#endif


#ifdef EDMA_CH5_ISR_EN
extern void pFUN_mEDMA_IRQ16_CH5_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH5_16_ISR
   Description:     Intc Service Rootine , vector 16 for DMA Channel 5
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH5_16_ISR(void)
{
	EDMA.CIRQR.R = 5;
	
	/* User Operation */
	pFUN_mEDMA_IRQ16_CH5_Hook();
}
#endif


#ifdef EDMA_CH6_ISR_EN
extern void pFUN_mEDMA_IRQ17_CH6_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH6_17_ISR
   Description:     Intc Service Rootine , vector 17 for DMA Channel 6
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH6_17_ISR(void)
{
	EDMA.CIRQR.R = 6;
	
	/* User Operation */
	pFUN_mEDMA_IRQ17_CH6_Hook();
}
#endif


#ifdef EDMA_CH7_ISR_EN
extern void pFUN_mEDMA_IRQ18_CH7_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH7_18_ISR
   Description:     Intc Service Rootine , vector 18 for DMA Channel 7
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH7_18_ISR(void)
{
	EDMA.CIRQR.R = 7;
	
	/* User Operation */
	pFUN_mEDMA_IRQ18_CH7_Hook();
}
#endif


#ifdef EDMA_CH8_ISR_EN
extern void pFUN_mEDMA_IRQ19_CH8_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH8_19_ISR
   Description:     Intc Service Rootine , vector 19 for DMA Channel 8
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH8_19_ISR(void)
{
	EDMA.CIRQR.R = 8;
	
	/* User Operation */
	pFUN_mEDMA_IRQ19_CH8_Hook();
}
#endif


#ifdef EDMA_CH9_ISR_EN
extern void pFUN_mEDMA_IRQ20_CH9_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH9_20_ISR
   Description:     Intc Service Rootine , vector 20 for DMA Channel 9
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH9_20_ISR(void)
{
	EDMA.CIRQR.R = 9;
	
	/* User Operation */
	pFUN_mEDMA_IRQ20_CH9_Hook();
}
#endif


#ifdef EDMA_CH10_ISR_EN
extern void pFUN_mEDMA_IRQ21_CH10_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH10_21_ISR
   Description:     Intc Service Rootine , vector 21 for DMA Channel 10
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH10_21_ISR(void)
{
	EDMA.CIRQR.R = 10;
	
	/* User Operation */
	pFUN_mEDMA_IRQ21_CH10_Hook();
}
#endif


#ifdef EDMA_CH11_ISR_EN
extern void pFUN_mEDMA_IRQ22_CH11_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH11_22_ISR
   Description:     Intc Service Rootine , vector 22 for DMA Channel 11
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH11_22_ISR(void)
{
	EDMA.CIRQR.R = 11;
	
	/* User Operation */
	pFUN_mEDMA_IRQ22_CH11_Hook();
}
#endif


#ifdef EDMA_CH12_ISR_EN
extern void pFUN_mEDMA_IRQ23_CH12_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH12_23_ISR
   Description:     Intc Service Rootine , vector 23 for DMA Channel 12
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH12_23_ISR(void)
{
	EDMA.CIRQR.R = 12;
	
	/* User Operation */
	pFUN_mEDMA_IRQ23_CH12_Hook();
}
#endif


#ifdef EDMA_CH13_ISR_EN
extern void pFUN_mEDMA_IRQ24_CH13_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH13_24_ISR
   Description:     Intc Service Rootine , vector 24 for DMA Channel 13
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH13_24_ISR(void)
{
	EDMA.CIRQR.R = 13;
	
	/* User Operation */
	pFUN_mEDMA_IRQ24_CH13_Hook();
}
#endif


#ifdef EDMA_CH14_ISR_EN
extern void pFUN_mEDMA_IRQ25_CH14_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH14_25_ISR
   Description:     Intc Service Rootine , vector 25 for DMA Channel 14
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH14_25_ISR(void)
{
	EDMA.CIRQR.R = 14;
	
	/* User Operation */
	pFUN_mEDMA_IRQ25_CH14_Hook();
}
#endif


#ifdef EDMA_CH15_ISR_EN
extern void pFUN_mEDMA_IRQ26_CH15_Hook(void);
/* *****************************************************************************
   Function:        mEDMA_CH15_26_ISR
   Description:     Intc Service Rootine , vector 26 for DMA Channel 15
   Parameters:      Input:		None
                    Output:   	None
   Notes:           
                   
   ***************************************************************************** */
void	mEDMA_CH15_26_ISR(void)
{
	EDMA.CIRQR.R = 15;
	
	/* User Operation */
	pFUN_mEDMA_IRQ26_CH15_Hook();
}
#endif


/* End of file */