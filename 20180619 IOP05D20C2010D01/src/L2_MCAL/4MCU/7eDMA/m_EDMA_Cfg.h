/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_EDMA_Cfg.h
*
* @brief    Config Header file for "m_EDMA_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/04/12      CODER2       	   	N/A          Original
************************************************************************************************/

#ifndef _M_EDMA_CFG_H_
#define _M_EDMA_CFG_H_


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_EDMA_Drv.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   variable declaration
   *****************************************************************************
   ***************************************************************************** */
extern	uint32	RxDataRam0[SYS_CTU_THRESH_0+1];
extern	uint32	RxDataRam1[SYS_CTU_THRESH_1+1];


/* *****************************************************************************
   *****************************************************************************
   Config Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	EDMA TCD Channel Used Macro										   ***/
/*---------------------------------------------------------------------------*/
#define		EDMA_CTU_FIFO_INDEX_0		eDMA_Ch_0
#define		EDMA_CTU_FIFO_INDEX_1		eDMA_Ch_1
#if 0
	#define		EDMA_CTU_FIFO_INDEX_2		NONE
	#define		EDMA_CTU_FIFO_INDEX_3		NONE
#endif

/*---------------------------------------------------------------------------*/
/***	hardware Req Enabled											   ***/
/*---------------------------------------------------------------------------*/
#define		EDMA_CTU_FIFO_INDEX_0_HARD_REQ_ENABLED
#define		EDMA_CTU_FIFO_INDEX_1_HARD_REQ_ENABLED	
	
/*---------------------------------------------------------------------------*/
/***	EDMA_CTU_FIFO_SOFT_START										   ***/
/*---------------------------------------------------------------------------*/
#if 0
	#define		EDMA_CTU_FIFO_INDEX_0_SOFT_START
	#define		EDMA_CTU_FIFO_INDEX_1_SOFT_START
#endif

/*---------------------------------------------------------------------------*/
/***	TCD[INDEX_0] Config Macro										   ***/
/*---------------------------------------------------------------------------*/
#ifdef	EDMA_CTU_FIFO_INDEX_0
	/* TCD[INDEX_0] Source Address */
	#define		EDMA_CTU_FIFO_INDEX_0_SRC_ADDR		CTU_FIFO_1_FR
	
	/* TCD[INDEX_0] Source Address Modulo */
	#define		EDMA_CTU_FIFO_INDEX_0_SMOD			0
	
	/* TCD[INDEX_0] Source Transfer Size */
	#define		EDMA_CTU_FIFO_INDEX_0_SSIZE			EDMA_SIZE_32_BIT
	
	/* TCD[INDEX_0] Signed Source Addr Offset */
	#define		EDMA_CTU_FIFO_INDEX_0_SOFF			0
	
	/* TCD[INDEX_0] Last signed Source Address Adjust */
	#define		EDMA_CTU_FIFO_INDEX_0_SLAST			0

	/* TCD[INDEX_0] Destination Address */
	#define		EDMA_CTU_FIFO_INDEX_0_DEST_ADDR		RxDataRam0
	
	/* TCD[INDEX_0] Destination Address Modulo */
	#define		EDMA_CTU_FIFO_INDEX_0_DMOD			0
	
	/* TCD[INDEX_0] Destination Transfer Size */
	#define		EDMA_CTU_FIFO_INDEX_0_DSIZE			EDMA_SIZE_32_BIT
	
	/* TCD[INDEX_0] Signed Source Addr Offset */
	#define		EDMA_CTU_FIFO_INDEX_0_DOFF			4
	
	/* TCD[INDEX_0] Last signed Source Address Adjust */	
	#define		EDMA_CTU_FIFO_INDEX_0_DLAST_SGA		(-(EDMA_CTU_FIFO_INDEX_0_NBYTES * EDMA_CTU_FIFO_INDEX_0_BITER)) /* NBYTES * BITER */
	
	/* TCD[INDEX_0] Inner 'minor' byte count */
	#define		EDMA_CTU_FIFO_INDEX_0_NBYTES		((SYS_CTU_THRESH_0 + 1) * 4)
	
	/* TCD[INDEX_0] Current Link Enable */
	#define		EDMA_CTU_FIFO_INDEX_0_CITER_LINK_EN			DISABLE
	
	/* TCD[INDEX_0] Current Link Channel */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_0_CITER_LINK_EN)
		#define		EDMA_CTU_FIFO_INDEX_0_CITER_LINK_CH		eDMA_Ch_1
	#else
		#define		EDMA_CTU_FIFO_INDEX_0_CITER_LINK_CH		0
	#endif
	
	/* TCD[INDEX_0] Current Count */
	#define		EDMA_CTU_FIFO_INDEX_0_CITER					1	

	/* TCD[INDEX_0] Begining Link Enable */
	#define		EDMA_CTU_FIFO_INDEX_0_BITER_LINK_EN			DISABLE
	
	/* TCD[INDEX_0] Begining Link Channel */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_0_BITER_LINK_EN)
		#define		EDMA_CTU_FIFO_INDEX_0_BITER_LINK_CH		eDMA_Ch_1
	#else
		#define		EDMA_CTU_FIFO_INDEX_0_BITER_LINK_CH		0
	#endif
		
	/* TCD[INDEX_0] beginning ("major") iteration count */
	#define		EDMA_CTU_FIFO_INDEX_0_BITER					1	
	
	/* TCD[INDEX_0] Major Link Enable */
	#define		EDMA_CTU_FIFO_INDEX_0_MAJOR_LINK_EN			DISABLE
	
	/* TCD[INDEX_0] Major Link Channel */
	#define		EDMA_CTU_FIFO_INDEX_0_MAJOR_LINK_CH			0
	
	/* TCD[INDEX_0] bandwidth control */
	#define		EDMA_CTU_FIFO_INDEX_0_BWC			0
	
	/* TCD[INDEX_0] Enable scatter/gather descriptor */
	#define		EDMA_CTU_FIFO_INDEX_0_E_SG			0
	
	/* TCD[INDEX_0] disable Channel when done */
	#define		EDMA_CTU_FIFO_INDEX_0_REQ_CH_DIS	FALSE
	
	/* TCD[INDEX_0] interrupt on citer = (biter >> 1) */
	#define		EDMA_CTU_FIFO_INDEX_0_INT_HALF		DISABLE
	
	/* TCD[INDEX_0] interrupt on major loop completion */
	#define		EDMA_CTU_FIFO_INDEX_0_INT_MAJ		ENABLE
	
	/* TCD[INDEX_0] explicit channel start */
	#define		EDMA_CTU_FIFO_INDEX_0_START			0
	
	/* TCD[INDEX_0] channel active */
	#define		EDMA_CTU_FIFO_INDEX_0_ACTIVE		0
	
	/* TCD[INDEX_0] channel done */
	#define		EDMA_CTU_FIFO_INDEX_0_DONE			0
	
	/* DMAMUX[INDEX_0]  Source */
	#define		EDMA_CTU_FIFO_INDEX_0_SRC			EDMA_MUX_SRC_CTU_FIFO_1	
	
	/* TCD[INDEX_0] Channel Priority */
	#define		EDMA_CTU_FIFO_INDEX_0_CPR			0
#endif

/*---------------------------------------------------------------------------*/
/***	TCD[INDEX_1] Config Macro										   ***/
/*---------------------------------------------------------------------------*/
#ifdef	EDMA_CTU_FIFO_INDEX_1
	/* TCD[INDEX_1] Source Address */
	#define		EDMA_CTU_FIFO_INDEX_1_SRC_ADDR		CTU_FIFO_2_FR
	
	/* TCD[INDEX_1] Source Address Modulo */
	#define		EDMA_CTU_FIFO_INDEX_1_SMOD			0
	
	/* TCD[INDEX_1] Source Transfer Size */
	#define		EDMA_CTU_FIFO_INDEX_1_SSIZE			EDMA_SIZE_32_BIT
	
	/* TCD[INDEX_1] Signed Source Addr Offset */
	#define		EDMA_CTU_FIFO_INDEX_1_SOFF			0
	
	/* TCD[INDEX_1] Last signed Source Address Adjust */
	#define		EDMA_CTU_FIFO_INDEX_1_SLAST			0

	/* TCD[INDEX_1] Destination Address */
	#define		EDMA_CTU_FIFO_INDEX_1_DEST_ADDR		RxDataRam1
	
	/* TCD[INDEX_1] Destination Address Modulo */
	#define		EDMA_CTU_FIFO_INDEX_1_DMOD			0
	
	/* TCD[INDEX_1] Destination Transfer Size */
	#define		EDMA_CTU_FIFO_INDEX_1_DSIZE			EDMA_SIZE_32_BIT
	
	/* TCD[INDEX_1] Signed Source Addr Offset */
	#define		EDMA_CTU_FIFO_INDEX_1_DOFF			4
	
	/* TCD[INDEX_1] Last signed Source Address Adjust */	
	#define		EDMA_CTU_FIFO_INDEX_1_DLAST_SGA		(-(EDMA_CTU_FIFO_INDEX_1_NBYTES * EDMA_CTU_FIFO_INDEX_1_BITER)) /* NBYTES * BITER */
	
	/* TCD[INDEX_1] Inner 'minor' byte count */
	#define		EDMA_CTU_FIFO_INDEX_1_NBYTES		((SYS_CTU_THRESH_1 + 1) * 4)
	
	/* TCD[INDEX_1] Current Link Enable */
	#define		EDMA_CTU_FIFO_INDEX_1_CITER_LINK_EN			DISABLE
	
	/* TCD[INDEX_1] Current Link Channel */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_1_CITER_LINK_EN)
		#define		EDMA_CTU_FIFO_INDEX_1_CITER_LINK_CH		eDMA_Ch_1
	#else
		#define		EDMA_CTU_FIFO_INDEX_1_CITER_LINK_CH		0
	#endif
	
	/* TCD[INDEX_1] Current Count */
	#define		EDMA_CTU_FIFO_INDEX_1_CITER					1	

	/* TCD[INDEX_1] Begining Link Enable */
	#define		EDMA_CTU_FIFO_INDEX_1_BITER_LINK_EN			DISABLE
	
	/* TCD[INDEX_1] Begining Link Channel */
	#if (ENABLE == EDMA_CTU_FIFO_INDEX_1_BITER_LINK_EN)
		#define		EDMA_CTU_FIFO_INDEX_1_BITER_LINK_CH		eDMA_Ch_1
	#else
		#define		EDMA_CTU_FIFO_INDEX_1_BITER_LINK_CH		0
	#endif
		
	/* TCD[INDEX_1] beginning ("major") iteration count */
	#define		EDMA_CTU_FIFO_INDEX_1_BITER					1	
	
	/* TCD[INDEX_1] Major Link Enable */
	#define		EDMA_CTU_FIFO_INDEX_1_MAJOR_LINK_EN			DISABLE
	
	/* TCD[INDEX_1] Major Link Channel */
	#define		EDMA_CTU_FIFO_INDEX_1_MAJOR_LINK_CH			0
	
	/* TCD[INDEX_1] bandwidth control */
	#define		EDMA_CTU_FIFO_INDEX_1_BWC			0
	
	/* TCD[INDEX_1] Enable scatter/gather descriptor */
	#define		EDMA_CTU_FIFO_INDEX_1_E_SG			0
	
	/* TCD[INDEX_1] disable Channel when done */
	#define		EDMA_CTU_FIFO_INDEX_1_REQ_CH_DIS	FALSE
	
	/* TCD[INDEX_1] interrupt on citer = (biter >> 1) */
	#define		EDMA_CTU_FIFO_INDEX_1_INT_HALF		DISABLE
	
	/* TCD[INDEX_1] interrupt on major loop completion */
	#define		EDMA_CTU_FIFO_INDEX_1_INT_MAJ		ENABLE
	
	/* TCD[INDEX_1] explicit channel start */
	#define		EDMA_CTU_FIFO_INDEX_1_START			0
	
	/* TCD[INDEX_1] channel active */
	#define		EDMA_CTU_FIFO_INDEX_1_ACTIVE		0
	
	/* TCD[INDEX_1] channel done */
	#define		EDMA_CTU_FIFO_INDEX_1_DONE			0
	
	/* DMAMUX[INDEX_1]  Source */
	#define		EDMA_CTU_FIFO_INDEX_1_SRC			EDMA_MUX_SRC_CTU_FIFO_2	
	
	/* TCD[INDEX_0] Channel Priority */
	#define		EDMA_CTU_FIFO_INDEX_1_CPR			1
#endif



#endif	
