/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_CTU_Drv.c
*
* @brief    CTU Module Function, Init and Config by changing Configuration in "m_CTU_Cfg.h"
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/06/17      CODER2       	   	N/A          Original
*     1.1        2012/08/16      CODER2			N/A          Modify Drv, Add ADC_FIFO, Add Poll
*     1.2        2012/09/27      CODER2			N/A          Add Cfg file
*     1.3        2012/11/02      CODER2			N/A          Add History Comment
*     1.4        2013/02/26      CODER2			N/A          Code Simplify, Delete Reg_Bit Functions
*     1.5        2013/03/06      CODER2			N/A          Modify FTH_VAL and FIFO_OF_Intc bug, Use EMPTY_Flag for FIFO Reading
*     1.6        2013/04/19      CODER2			N/A          Add eDMA_CTU_FIFO Config
*******************************************************************************/

#ifndef M_CTU_DRV_C
#define M_CTU_DRV_C
#endif


/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_CTU_Drv.h"
#include 	"m_CTU_Cfg.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mCTU_Trig_FstCommand_Set
   Description:     Set ADC Command List's First command Address
   Parameters:      Input:    
   						TrigNum:	Trig Event Index
   						FstAddr:	First Command Address
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCTU_Trig_FstCommand_Set(uint8 TrigNum, uint32 FstAddr)
{
	/* Trigger Commands List first command address */
	switch(TrigNum)
	{
		case CLCR_T0:	/* Trigger 0 Commands List first command address */
			CTU_CLCR1 &= (~CTU_CLCR1_T0_INDEX_MASK);
			CTU_CLCR1 |= ((FstAddr & 0x1F)<<0);
			break;
		case CLCR_T1:	/* Trigger 1 Commands List first command address */
			CTU_CLCR1 &= (~CTU_CLCR1_T1_INDEX_MASK);
			CTU_CLCR1 |= ((FstAddr & 0x1F)<<8);
			break;	
		case CLCR_T2:	/* Trigger 2 Commands List first command address */
			CTU_CLCR1 &= (~CTU_CLCR1_T2_INDEX_MASK);
			CTU_CLCR1 |= ((FstAddr & 0x1F)<<16);
			break;
		case CLCR_T3:	/* Trigger 3 Commands List first command address */
			CTU_CLCR1 &= (~CTU_CLCR1_T3_INDEX_MASK);
			CTU_CLCR1 |= ((FstAddr & 0x1F)<<24);
			break;
		case CLCR_T4:	/* Trigger 4 Commands List first command address */
			CTU_CLCR2 &= (~CTU_CLCR2_T4_INDEX_MASK);
			CTU_CLCR2 |= ((FstAddr & 0x1F)<<0);
			break;
		case CLCR_T5:	/* Trigger 5 Commands List first command address */
			CTU_CLCR2 &= (~CTU_CLCR2_T5_INDEX_MASK);
			CTU_CLCR2 |= ((FstAddr & 0x1F)<<8);
			break;	
		case CLCR_T6:	/* Trigger 6 Commands List first command address */
			CTU_CLCR2 &= (~CTU_CLCR2_T6_INDEX_MASK);
			CTU_CLCR2 |= ((FstAddr & 0x1F)<<16);
			break;
		case CLCR_T7:	/* Trigger 7 Commands List first command address */
			CTU_CLCR2 &= (~CTU_CLCR2_T7_INDEX_MASK);
			CTU_CLCR2 |= ((FstAddr & 0x1F)<<24);
			break;
			
		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mCTU_Trig_Handdle_Set
   Description:     Set Trig Event Handle's source and whether Enabled
   Parameters:      Input:    
   						TrigNum:	Trig Event Index
   						IntcSrc:	Handle Source
   						ValEn:		Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_Trig_Handdle_Set(uint8 TrigNum, uint8 IntcSrc, uint32 ValEn)
{
	switch(TrigNum)
	{
		case THCR_T0:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR1 &= (~CTU_THCR1_T0_EN_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<4);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR1 &= (~CTU_THCR1_T0_ETE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<3);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR1 &= (~CTU_THCR1_T0_T1E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<2);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR1 &= (~CTU_THCR1_T0_T0E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<1);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR1 &= (~CTU_THCR1_T0_ADCE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<0);
					break;	
					
				default:
					break;
			}			
			break;
		case THCR_T1:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR1 &= (~CTU_THCR1_T1_EN_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<12);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR1 &= (~CTU_THCR1_T1_ETE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<11);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR1 &= (~CTU_THCR1_T1_T1E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<10);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR1 &= (~CTU_THCR1_T1_T0E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<9);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR1 &= (~CTU_THCR1_T1_ADCE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<8);
					break;	
					
				default:
					break;
			}			
			break;
		case THCR_T2:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR1 &= (~CTU_THCR1_T2_EN_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<20);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR1 &= (~CTU_THCR1_T2_ETE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<19);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR1 &= (~CTU_THCR1_T2_T1E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<18);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR1 &= (~CTU_THCR1_T2_T0E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<17);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR1 &= (~CTU_THCR1_T2_ADCE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<16);
					break;	
					
				default:
					break;
			}			
			break;		
		case THCR_T3:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR1 &= (~CTU_THCR1_T3_EN_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<28);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR1 &= (~CTU_THCR1_T3_ETE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<27);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR1 &= (~CTU_THCR1_T3_T1E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<26);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR1 &= (~CTU_THCR1_T3_T0E_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<25);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR1 &= (~CTU_THCR1_T3_ADCE_MASK);
					CTU_THCR1 |= ((ValEn & 0x01)<<24);
					break;	
					
				default:
					break;
			}			
			break;		
		
		case THCR_T4:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR2 &= (~CTU_THCR2_T4_EN_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<4);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR2 &= (~CTU_THCR2_T4_ETE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<3);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR2 &= (~CTU_THCR2_T4_T1E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<2);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR2 &= (~CTU_THCR2_T4_T0E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<1);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR2 &= (~CTU_THCR2_T4_ADCE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<0);
					break;	
					
				default:
					break;
			}			
			break;
		case THCR_T5:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR2 &= (~CTU_THCR2_T5_EN_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<12);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR2 &= (~CTU_THCR2_T5_ETE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<11);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR2 &= (~CTU_THCR2_T5_T1E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<10);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR2 &= (~CTU_THCR2_T5_T0E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<9);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR2 &= (~CTU_THCR2_T5_ADCE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<8);
					break;	
					
				default:
					break;
			}			
			break;
		case THCR_T6:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR2 &= (~CTU_THCR2_T6_EN_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<20);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR2 &= (~CTU_THCR2_T6_ETE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<19);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR2 &= (~CTU_THCR2_T6_T1E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<18);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR2 &= (~CTU_THCR2_T6_T0E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<17);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR2 &= (~CTU_THCR2_T6_ADCE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<16);
					break;	
					
				default:
					break;
			}			
			break;		
		case THCR_T7:
			switch(IntcSrc)
			{
				case THCR_TRIG_EN:
					CTU_THCR2 &= (~CTU_THCR2_T7_EN_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<28);
					break;
				case THCR_TRIG_EXT_EN:
					CTU_THCR2 &= (~CTU_THCR2_T7_ETE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<27);
					break;
				case THCR_TRIG_T1_EN:
					CTU_THCR2 &= (~CTU_THCR2_T7_T1E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<26);
					break;	
				case THCR_TRIG_T0_EN:
					CTU_THCR2 &= (~CTU_THCR2_T7_T0E_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<25);
					break;
				case THCR_TRIG_ADC_EN:
					CTU_THCR2 &= (~CTU_THCR2_T7_ADCE_MASK);
					CTU_THCR2 |= ((ValEn & 0x01)<<24);
					break;	
					
				default:
					break;
			}			
			break;		

		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mCTU_CLR_Dual_All_Set
   Description:     Set CLR Reg in Dual Sample Mode
   Parameters:      Input:    
   						ListNum:	CLR Reg Index 1бл24
   						IntcEn:		Intc Enable or Disable
   						FstEn:		First Command Address Enable or Disable
   						ValFIFONum:	ADC Data saved in which FIFO ?
   						ValChB:		ADC Channel to be sampled in ADC1 Moudule
   						ValChA:		ADC Channel to be sampled in ADC0 Moudule
                    Output:   None
   Notes:           
                
   ***************************************************************************** */
/* Dual conversion mode */
#ifndef	ADC_SINGLE_CONV	

static	void	mCTU_CLR_Dual_All_Set(uint8 ListNum, uint8 IntcEn, uint8 FstEn, uint8 ValFIFONum, uint8 ValChB, uint8 ValChA)
{
	CTU_CLR(ListNum) = 0;
	REG16_BIT_SET(CTU_CLR(ListNum), ((IntcEn & 0x01)<<15));			/* Command Interrupt Request */
	REG16_BIT_SET(CTU_CLR(ListNum), ((FstEn & 0x01)<<14));			/* First command */
	REG16_BIT_SET(CTU_CLR(ListNum), ((CLR_CONV_MODE & 0x01)<<13));	/* Conversion mode selection */
	REG16_BIT_SET(CTU_CLR(ListNum), ((ValFIFONum & 0x03)<<10));		/* FIFO for ADC unit A/B */
	REG16_BIT_SET(CTU_CLR(ListNum), ((ValChB & 0x0F)<<5));			/* ADC unit B channel number */
	REG16_BIT_SET(CTU_CLR(ListNum), ((ValChA & 0x0F)<<0));			/* ADC unit A channel number */
}

/* Single conversion mode */
#else

void	mCTU_CLR_Single_All_Set(uint8 ListNum, uint8 IntcEn, uint8 FstEn, uint8 ValFIFONum, uint8 ValUnit, uint8 ValChan)
{
	CTU_CLR(ListNum) = 0;
	REG16_BIT_SET(CTU_CLR(ListNum), ((IntcEn & 0x01)<<15));			/* Command Interrupt Request */
	REG16_BIT_SET(CTU_CLR(ListNum), ((FstEn & 0x01)<<14));			/* First command */
	REG16_BIT_SET(CTU_CLR(ListNum), ((CLR_CONV_MODE & 0x01)<<13));	/* Conversion mode selection */
	REG16_BIT_SET(CTU_CLR(ListNum), ((ValFIFONum & 0x03)<<10));		/* FIFO for ADC unit 0/1 */
	REG16_BIT_SET(CTU_CLR(ListNum), ((ValUnit & 0x01)<<5));			/* Selection Unit */
	REG16_BIT_SET(CTU_CLR(ListNum), ((ValChan & 0x0F)<<0));			/* ADC unit channel number */
}

#endif


/* *****************************************************************************
   Function:        mCTU_FIFO_DMA_En_Set
   Description:     Set DMA Attribute of ADC Data in FIFO 
   Parameters:      Input:    
   						FIFONum:	FIFO Index
   						ValEn:		Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCTU_FIFO_DMA_En_Set(uint8 FIFONum, uint16 ValEn)
{
	switch(FIFONum)
	{
		case CTU_FIFO0:
			CTU_FDCR &= (~CTU_FDCR_DE0_MASK);
			CTU_FDCR |= ((ValEn & 0x01)<<0);
			break;
		case CTU_FIFO1:
			CTU_FDCR &= (~CTU_FDCR_DE1_MASK);
			CTU_FDCR |= ((ValEn & 0x01)<<1);
			break;
		case CTU_FIFO2:
			CTU_FDCR &= (~CTU_FDCR_DE2_MASK);
			CTU_FDCR |= ((ValEn & 0x01)<<2);
			break;
		case CTU_FIFO3:
			CTU_FDCR &= (~CTU_FDCR_DE3_MASK);
			CTU_FDCR |= ((ValEn & 0x01)<<3);
			break;
		
		default:
			break;
	}	
}


/* *****************************************************************************
   Function:        mCTU_FIFO_Overrun_En_Set
   Description:     Set FIFO Overrun Intc Enabled
   Parameters:      Input:    
   						FIFONum:	FIFO Index
   						ValEn:		Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCTU_FIFO_Overrun_En_Set(uint8 FIFONum, uint32 ValEn)
{
	switch(FIFONum)
	{
		case CTU_FIFO0:
			CTU_FCR &= (~CTU_FCR_OR_EN0_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<3);
			break;
		case CTU_FIFO1:
			CTU_FCR &= (~CTU_FCR_OR_EN1_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<7);
			break;
		case CTU_FIFO2:
			CTU_FCR &= (~CTU_FCR_OR_EN2_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<11);
			break;
		case CTU_FIFO3:
			CTU_FCR &= (~CTU_FCR_OR_EN3_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<15);
			break;
		
		default:
			break;
	}	
}


/* *****************************************************************************
   Function:        mCTU_FIFO_Thresh_OverFlow_En_Set
   Description:     Set FIFO OverFlow Intc Enabled
   Parameters:      Input:    
   						FIFONum:	FIFO Index
   						ValEn:		Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCTU_FIFO_Thresh_OverFlow_En_Set(uint8 FIFONum, uint32 ValEn)
{
	switch(FIFONum)
	{
		case CTU_FIFO0:
			CTU_FCR &= (~CTU_FCR_OF_EN0_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<2);
			break;
		case CTU_FIFO1:
			CTU_FCR &= (~CTU_FCR_OF_EN1_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<6);
			break;
		case CTU_FIFO2:
			CTU_FCR &= (~CTU_FCR_OF_EN2_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<10);
			break;
		case CTU_FIFO3:
			CTU_FCR &= (~CTU_FCR_OF_EN3_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<14);
			break;
		
		default:
			break;
	}	
}


/* *****************************************************************************
   Function:        mCTU_FIFO_Empty_En_Set
   Description:     Set FIFO Empty Intc Enabled
   Parameters:      Input:    
   						FIFONum:	FIFO Index
   						ValEn:		Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCTU_FIFO_Empty_En_Set(uint8 FIFONum, uint32 ValEn)
{
	switch(FIFONum)
	{
		case CTU_FIFO0:
			CTU_FCR &= (~CTU_FCR_EMPTY_EN0_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<1);
			break;
		case CTU_FIFO1:
			CTU_FCR &= (~CTU_FCR_EMPTY_EN1_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<5);
			break;
		case CTU_FIFO2:
			CTU_FCR &= (~CTU_FCR_EMPTY_EN2_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<9);
			break;
		case CTU_FIFO3:
			CTU_FCR &= (~CTU_FCR_EMPTY_EN3_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<13);
			break;
		
		default:
			break;
	}	
}


/* *****************************************************************************
   Function:        mCTU_FIFO_Full_En_Set
   Description:     Set FIFO Full Intc Enabled
   Parameters:      Input:    
   						FIFONum:	FIFO Index
   						ValEn:		Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCTU_FIFO_Full_En_Set(uint8 FIFONum, uint32 ValEn)
{
	switch(FIFONum)
	{
		case CTU_FIFO0:
			CTU_FCR &= (~CTU_FCR_FULL_EN0_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<0);
			break;
		case CTU_FIFO1:
			CTU_FCR &= (~CTU_FCR_FULL_EN1_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<4);
			break;
		case CTU_FIFO2:
			CTU_FCR &= (~CTU_FCR_FULL_EN2_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<8);
			break;
		case CTU_FIFO3:
			CTU_FCR &= (~CTU_FCR_FULL_EN3_MASK);
			CTU_FCR |= ((ValEn & 0x01)<<12);
			break;
		
		default:
			break;
	}	
}


static	void	mCTU_FIFO_Intc_Dis_All(void)
{
	CTU_FCR = 0x0;
}

/* *****************************************************************************
   Function:        mCTU_FIFO_Thresh_Set
   Description:     Set FIFO Thresh Value while OverFlow,
   Parameters:      Input:    
   						FIFONum:	FIFO Index
   						ValThresh:	Thresh Value
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCTU_FIFO_Thresh_Set(uint8 FIFONum, uint32 ValThresh)
{
	switch(FIFONum)
	{
		case CTU_FIFO0:
			CTU_FTH &= (~CTU_FTH_TH0_MASK);
			CTU_FTH |= ((ValThresh & 0xFF)<<0);
			break;
		case CTU_FIFO1:
			CTU_FTH &= (~CTU_FTH_TH1_MASK);
			CTU_FTH |= ((ValThresh & 0xFF)<<8);
			break;
		case CTU_FIFO2:
			CTU_FTH &= (~CTU_FTH_TH2_MASK);
			CTU_FTH |= ((ValThresh & 0xFF)<<16);
			break;
		case CTU_FIFO3:
			CTU_FTH &= (~CTU_FTH_TH3_MASK);
			CTU_FTH |= ((ValThresh & 0xFF)<<24);
			break;
		
		default:
			break;
	}
}


/* *****************************************************************************
   Function:        mCTU_ADC_StateM_Reset
   Description:     Stop Operation to ADC, and Reset ADC Command List 
   Parameters:      Input:    
   						ValRstEn:	Reset Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_ADC_StateM_Reset(uint16 ValRstEn)
{
	CTU_CTUCR &= (~CTU_CTUCR_CRU_ADC_R_MASK);
	CTU_CTUCR |= ((ValRstEn & 0x01)<<7);	
}


/* *****************************************************************************
   Function:        mCTU_GRE_Set
   Description:     Set CTU General Reload Enable 
   Parameters:      Input:    
   						ValEn:		GRE Enable or Disable
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_GRE_Set(uint16 ValEn)
{
	CTU_CTUCR &= (~CTU_CTUCR_GRE_MASK);
	CTU_CTUCR |= ((ValEn & 0x01)<<1);
}


/* *****************************************************************************
   Function:        mCTU_Module_En
   Description:     CTU output Enabled
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_Module_En(void)
{
	CTU_CTUCR &= (~CTU_CTUCR_CTU_ODIS_MASK);	/* Enable CTU output */
}


/* *****************************************************************************
   Function:        mCTU_Module_Dis
   Description:     CTU output Disabled
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_Module_Dis(void)
{
	CTU_CTUCR |= CTU_CTUCR_CTU_ODIS_MASK;		/* Disable CTU output */
	mCTU_ADC_StateM_Reset(ENABLE);				/* Reset CTU/ADC state machine */
}


/* *****************************************************************************
   Function:        mCTU_Init
   Description:     CTU Initiation
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_Init(void)
{
#ifdef	CTU_ENABLED
	uint8	i;
	volatile uint32	readValue32;
	
#ifdef CTU_EXT_TRG
	SIU.PCR[CTU_EXT_PIN].R  = CTU_EXT_PCR;	/* CTU EXT_TRG GPIO, replaced by eTimer CompareOut */
#endif
		
	/* CTU Reg Reset All */
    CTU_0.TGSISR.R	= 0x0;
    CTU_0.CLCR1.R	= 0x0;
    CTU_0.CLCR2.R	= 0x0;

    for (i = 0; i<24; i++)
    {
    	CTU_0.CLR[i].R = 0x0;
    }
    
    CTU_0.COTR.R	= 0x0;
    CTU_0.CR.R		= 0x0;
    CTU_0.CTUCR.R	= 0x0;
    
    readValue32 = CTU_0.CTUEFR.R;
    CTU_0.CTUEFR.R = 0xFF;

    CTU_0.CTUFILTER.R	= 0x0;
    CTU_0.CTUIFR.R		= 0x0;
    CTU_0.CTUIR.R		= 0x0;
    CTU_0.CTUPCR.R		= 0x0;
    CTU_0.FCR.R			= 0x0;

    for (i = 0; i<4; i++)
    {
    	CTU_0.FLA[i].R = 0x0;
    }

    for (i = 0; i<4; i++)
    {
    	CTU_0.FRA[i].R = 0x0;
    }
    

    CTU_0.STATUS.R = 0x0;

    for (i = 0; i<8; i++)
    {
    	CTU_0.TCR[i].R = 0x0;
    }
    
    CTU_0.TGSCCR.R	= 0x0;
    CTU_0.TGSCR.R	= 0x0;
    CTU_0.TGSCRR.R	= 0x0;
    CTU_0.TGSISR.R	= 0x0;
    CTU_0.TH1.R		= 0x0;
    CTU_0.TH2.R		= 0x0;
    CTU_0.THCR1.R	= 0x0;
    CTU_0.THCR2.R	= 0x0;


	/* CTU Config */
	/* TGSISR */
	REG32_BIT_SET(CTU_TGSISR, TGS_INPUT_SRC);	/* TGSISR.I0_RE = 1 */

	/* TGSCR */
	REG16_BIT_SET(CTU_TGSCR, CTU_TGSCR_ET_TM_MASK);				/* TGSCR.ET_TM */
	REG16_BIT_CLEAR(CTU_TGSCR, CTU_TGSCR_PRES_MASK);
	REG16_BIT_SET(CTU_TGSCR, ((TGS_PRESCALE & 0x03)<<6));		/* TGSCR.PRES = TGS_PRESCALE */
	REG16_BIT_CLEAR(CTU_TGSCR, CTU_TGSCR_TGS_SM_MASK);
	REG16_BIT_SET(CTU_TGSCR, ((TGS_SUBUNIT_MODE & 0x01)<<0));	/* TGSCR.TGS_M = TGS_SUBUNIT_MODE */
	
	/* TxCR */
	CTU_TCR(TCR_CH0) = TCR0_VALUE;
	CTU_TCR(TCR_CH1) = TCR1_VALUE;
	CTU_TCR(TCR_CH2) = TCR2_VALUE;
	CTU_TCR(TCR_CH3) = TCR3_VALUE;
	CTU_TCR(TCR_CH4) = TCR4_VALUE;
	CTU_TCR(TCR_CH5) = TCR5_VALUE;
	CTU_TCR(TCR_CH6) = TCR6_VALUE;
	CTU_TCR(TCR_CH7) = TCR7_VALUE;	

	/* TGSCCR */
	CTU_TGSCCR = TGSCCR_VALUE;
	
	/* TGSCRR */
	CTU_TGSCRR = TGSCRR_VALUE;
	
	/* CLCRx */
	mCTU_Trig_FstCommand_Set(CLCR_T0, CLC_T0_FST_ADDR);
	mCTU_Trig_FstCommand_Set(CLCR_T1, CLC_T1_FST_ADDR);
	mCTU_Trig_FstCommand_Set(CLCR_T2, CLC_T2_FST_ADDR);
	mCTU_Trig_FstCommand_Set(CLCR_T3, CLC_T3_FST_ADDR);	
	mCTU_Trig_FstCommand_Set(CLCR_T4, CLC_T4_FST_ADDR);
	mCTU_Trig_FstCommand_Set(CLCR_T5, CLC_T5_FST_ADDR);
	mCTU_Trig_FstCommand_Set(CLCR_T6, CLC_T6_FST_ADDR);
	mCTU_Trig_FstCommand_Set(CLCR_T7, CLC_T7_FST_ADDR);	
	
	/* THCRx */
	mCTU_Trig_Handdle_Set(THCR_T0, THCR_TRIG_EN, 		THC_T0_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T0, THCR_TRIG_EXT_EN, 	THC_T0_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T0, THCR_TRIG_T1_EN, 	THC_T0_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T0, THCR_TRIG_T0_EN, 	THC_T0_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T0, THCR_TRIG_ADC_EN, 	THC_T0_ADC_EN);
	
	mCTU_Trig_Handdle_Set(THCR_T1, THCR_TRIG_EN, 		THC_T1_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T1, THCR_TRIG_EXT_EN, 	THC_T1_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T1, THCR_TRIG_T1_EN, 	THC_T1_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T1, THCR_TRIG_T0_EN, 	THC_T1_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T1, THCR_TRIG_ADC_EN, 	THC_T1_ADC_EN);

	mCTU_Trig_Handdle_Set(THCR_T2, THCR_TRIG_EN, 		THC_T2_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T2, THCR_TRIG_EXT_EN, 	THC_T2_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T2, THCR_TRIG_T1_EN, 	THC_T2_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T2, THCR_TRIG_T0_EN, 	THC_T2_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T2, THCR_TRIG_ADC_EN, 	THC_T2_ADC_EN);
	
	mCTU_Trig_Handdle_Set(THCR_T3, THCR_TRIG_EN, 		THC_T3_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T3, THCR_TRIG_EXT_EN, 	THC_T3_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T3, THCR_TRIG_T1_EN, 	THC_T3_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T3, THCR_TRIG_T0_EN, 	THC_T3_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T3, THCR_TRIG_ADC_EN, 	THC_T3_ADC_EN);
	
	mCTU_Trig_Handdle_Set(THCR_T4, THCR_TRIG_EN, 		THC_T4_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T4, THCR_TRIG_EXT_EN, 	THC_T4_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T4, THCR_TRIG_T1_EN, 	THC_T4_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T4, THCR_TRIG_T0_EN, 	THC_T4_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T4, THCR_TRIG_ADC_EN, 	THC_T4_ADC_EN);
		
	mCTU_Trig_Handdle_Set(THCR_T5, THCR_TRIG_EN, 		THC_T5_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T5, THCR_TRIG_EXT_EN, 	THC_T5_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T5, THCR_TRIG_T1_EN, 	THC_T5_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T5, THCR_TRIG_T0_EN, 	THC_T5_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T5, THCR_TRIG_ADC_EN, 	THC_T5_ADC_EN);

	mCTU_Trig_Handdle_Set(THCR_T6, THCR_TRIG_EN, 		THC_T6_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T6, THCR_TRIG_EXT_EN, 	THC_T6_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T6, THCR_TRIG_T1_EN, 	THC_T6_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T6, THCR_TRIG_T0_EN, 	THC_T6_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T6, THCR_TRIG_ADC_EN, 	THC_T6_ADC_EN);

	mCTU_Trig_Handdle_Set(THCR_T7, THCR_TRIG_EN, 		THC_T7_HANDLE_EN);
	mCTU_Trig_Handdle_Set(THCR_T7, THCR_TRIG_EXT_EN, 	THC_T7_EXT_EN);
	mCTU_Trig_Handdle_Set(THCR_T7, THCR_TRIG_T1_EN, 	THC_T7_ET1_EN);
	mCTU_Trig_Handdle_Set(THCR_T7, THCR_TRIG_T0_EN, 	THC_T7_ET0_EN);
	mCTU_Trig_Handdle_Set(THCR_T7, THCR_TRIG_ADC_EN, 	THC_T7_ADC_EN);

	/* CLRx */
#ifdef	CLR_CONV_MODE	/* DUAL Mode */
	/* CLR 1 */
	mCTU_CLR_Dual_All_Set(CLR_CH1, CLR_CH1_INTC_EN, CLR_CH1_FST_CMD, CLR_CH1_FIFO_N, CLR_CH1_ADC_B, CLR_CH1_ADC_A);
	/* CLR 2 */
	mCTU_CLR_Dual_All_Set(CLR_CH2, CLR_CH2_INTC_EN, CLR_CH2_FST_CMD, CLR_CH2_FIFO_N, CLR_CH2_ADC_B, CLR_CH2_ADC_A);	
	/* CLR 3 */
	mCTU_CLR_Dual_All_Set(CLR_CH3, CLR_CH3_INTC_EN, CLR_CH3_FST_CMD, CLR_CH3_FIFO_N, CLR_CH3_ADC_B, CLR_CH3_ADC_A);
	/* CLR 4 */
	mCTU_CLR_Dual_All_Set(CLR_CH4, CLR_CH4_INTC_EN, CLR_CH4_FST_CMD, CLR_CH4_FIFO_N, CLR_CH4_ADC_B, CLR_CH4_ADC_A);
	/* CLR 5 */
	mCTU_CLR_Dual_All_Set(CLR_CH5, CLR_CH5_INTC_EN, CLR_CH5_FST_CMD, CLR_CH5_FIFO_N, CLR_CH5_ADC_B, CLR_CH5_ADC_A);
	/* CLR 6 */
	mCTU_CLR_Dual_All_Set(CLR_CH6, CLR_CH6_INTC_EN, CLR_CH6_FST_CMD, CLR_CH6_FIFO_N, CLR_CH6_ADC_B, CLR_CH6_ADC_A);
	/* CLR 7 */
	mCTU_CLR_Dual_All_Set(CLR_CH7, CLR_CH7_INTC_EN, CLR_CH7_FST_CMD, CLR_CH7_FIFO_N, CLR_CH7_ADC_B, CLR_CH7_ADC_A);
	/* CLR 8 */
	mCTU_CLR_Dual_All_Set(CLR_CH8, CLR_CH8_INTC_EN, CLR_CH8_FST_CMD, CLR_CH8_FIFO_N, CLR_CH8_ADC_B, CLR_CH8_ADC_A);
	/* CLR 9 */
	mCTU_CLR_Dual_All_Set(CLR_CH9, CLR_CH9_INTC_EN, CLR_CH9_FST_CMD, CLR_CH9_FIFO_N, CLR_CH9_ADC_B, CLR_CH9_ADC_A);
	/* CLR 10 */
	mCTU_CLR_Dual_All_Set(CLR_CH10, CLR_CH10_INTC_EN, CLR_CH10_FST_CMD, CLR_CH10_FIFO_N, CLR_CH10_ADC_B, CLR_CH10_ADC_A);
	/* CLR 11 */
	mCTU_CLR_Dual_All_Set(CLR_CH11, CLR_CH11_INTC_EN, CLR_CH11_FST_CMD, CLR_CH11_FIFO_N, CLR_CH11_ADC_B, CLR_CH11_ADC_A);
	/* CLR 12 */
	mCTU_CLR_Dual_All_Set(CLR_CH12, CLR_CH12_INTC_EN, CLR_CH12_FST_CMD, CLR_CH12_FIFO_N, CLR_CH12_ADC_B, CLR_CH12_ADC_A);	
	/* CLR 13 */
	mCTU_CLR_Dual_All_Set(CLR_CH13, CLR_CH13_INTC_EN, CLR_CH13_FST_CMD, CLR_CH13_FIFO_N, CLR_CH13_ADC_B, CLR_CH13_ADC_A);
	/* CLR 14 */
	mCTU_CLR_Dual_All_Set(CLR_CH14, CLR_CH14_INTC_EN, CLR_CH14_FST_CMD, CLR_CH14_FIFO_N, CLR_CH14_ADC_B, CLR_CH14_ADC_A);	
	/* CLR 15 */
	mCTU_CLR_Dual_All_Set(CLR_CH15, CLR_CH15_INTC_EN, CLR_CH15_FST_CMD, CLR_CH15_FIFO_N, CLR_CH15_ADC_B, CLR_CH15_ADC_A);
	/* CLR 16 */
	mCTU_CLR_Dual_All_Set(CLR_CH16, CLR_CH16_INTC_EN, CLR_CH16_FST_CMD, CLR_CH16_FIFO_N, CLR_CH16_ADC_B, CLR_CH16_ADC_A);
	/* CLR 17 */
	mCTU_CLR_Dual_All_Set(CLR_CH17, CLR_CH17_INTC_EN, CLR_CH17_FST_CMD, CLR_CH17_FIFO_N, CLR_CH17_ADC_B, CLR_CH17_ADC_A);
	/* CLR 18 */
	mCTU_CLR_Dual_All_Set(CLR_CH18, CLR_CH18_INTC_EN, CLR_CH18_FST_CMD, CLR_CH18_FIFO_N, CLR_CH18_ADC_B, CLR_CH18_ADC_A);
	/* CLR 19 */
	mCTU_CLR_Dual_All_Set(CLR_CH19, CLR_CH19_INTC_EN, CLR_CH19_FST_CMD, CLR_CH19_FIFO_N, CLR_CH19_ADC_B, CLR_CH19_ADC_A);
	/* CLR 20 */
	mCTU_CLR_Dual_All_Set(CLR_CH20, CLR_CH20_INTC_EN, CLR_CH20_FST_CMD, CLR_CH20_FIFO_N, CLR_CH20_ADC_B, CLR_CH20_ADC_A);
	/* CLR 21 */
	mCTU_CLR_Dual_All_Set(CLR_CH21, CLR_CH21_INTC_EN, CLR_CH21_FST_CMD, CLR_CH21_FIFO_N, CLR_CH21_ADC_B, CLR_CH21_ADC_A);
	/* CLR 22 */
	mCTU_CLR_Dual_All_Set(CLR_CH22, CLR_CH22_INTC_EN, CLR_CH22_FST_CMD, CLR_CH22_FIFO_N, CLR_CH22_ADC_B, CLR_CH22_ADC_A);	
	/* CLR 23 */
	mCTU_CLR_Dual_All_Set(CLR_CH23, CLR_CH23_INTC_EN, CLR_CH23_FST_CMD, CLR_CH23_FIFO_N, CLR_CH23_ADC_B, CLR_CH23_ADC_A);
	/* CLR 24 */
	mCTU_CLR_Dual_All_Set(CLR_CH24, CLR_CH24_INTC_EN, CLR_CH24_FST_CMD, CLR_CH24_FIFO_N, CLR_CH24_ADC_B, CLR_CH24_ADC_A);	
	
	
#else	/* Single Mode */

#endif	


#ifdef	CTU_FIFO_ENABLED	/* Using CTU_FIFO */

	#ifdef 	SYS_CTU_FIFO_USE_EDMA
		/* CTU_FIFO eDMA Mode */
		/* FIFO DMA control register (FDCR) */
		#ifdef	EDMA_CTU_FIFO_0_USED
			mCTU_FIFO_DMA_En_Set(CTU_FIFO0, ENABLE);
		#endif
		#ifdef	EDMA_CTU_FIFO_1_USED
			mCTU_FIFO_DMA_En_Set(CTU_FIFO1, ENABLE);
		#endif
		#ifdef	EDMA_CTU_FIFO_2_USED
			mCTU_FIFO_DMA_En_Set(CTU_FIFO2, ENABLE);
		#endif
		#ifdef	EDMA_CTU_FIFO_3_USED
			mCTU_FIFO_DMA_En_Set(CTU_FIFO3, ENABLE);
		#endif
	#else
		/* CTU_FIFO Intc Mode */
		#ifdef	INTC_CTU_FIFO_OVERRUN_ENABLED
			/* FCR  (FIFO Control Reg) */
			mCTU_FIFO_Overrun_En_Set(CTU_FIFO0, ENABLE);
			mCTU_FIFO_Overrun_En_Set(CTU_FIFO1, ENABLE);	
			mCTU_FIFO_Overrun_En_Set(CTU_FIFO2, ENABLE);	
			mCTU_FIFO_Overrun_En_Set(CTU_FIFO3, ENABLE);	
		#endif
		#ifdef	INTC_CTU_FIFO_OVERFLOW_ENABLED	
			mCTU_FIFO_Thresh_OverFlow_En_Set(CTU_FIFO0, ENABLE);
			mCTU_FIFO_Thresh_OverFlow_En_Set(CTU_FIFO1, ENABLE);
			mCTU_FIFO_Thresh_OverFlow_En_Set(CTU_FIFO2, ENABLE);
			mCTU_FIFO_Thresh_OverFlow_En_Set(CTU_FIFO3, ENABLE);
		#endif
		#ifdef	INTC_CTU_FIFO_EMPTY_ENABLED	
			mCTU_FIFO_Empty_En_Set(CTU_FIFO0, DISABLE);
			mCTU_FIFO_Empty_En_Set(CTU_FIFO1, DISABLE);		
			mCTU_FIFO_Empty_En_Set(CTU_FIFO2, DISABLE);
			mCTU_FIFO_Empty_En_Set(CTU_FIFO3, DISABLE);
		#endif
		#ifdef	INTC_CTU_FIFO_FULL_ENABLED
			mCTU_FIFO_Full_En_Set(CTU_FIFO0, ENABLE);
			mCTU_FIFO_Full_En_Set(CTU_FIFO1, ENABLE);		
			mCTU_FIFO_Full_En_Set(CTU_FIFO2, ENABLE);
			mCTU_FIFO_Full_En_Set(CTU_FIFO3, ENABLE);
		#endif
	#endif
		/* FIFO threshold register (FTH) */
		mCTU_FIFO_Thresh_Set(CTU_FIFO0, FTH_FIFO0_VAL);
		mCTU_FIFO_Thresh_Set(CTU_FIFO1, FTH_FIFO1_VAL);
		mCTU_FIFO_Thresh_Set(CTU_FIFO2, FTH_FIFO2_VAL);
		mCTU_FIFO_Thresh_Set(CTU_FIFO3, FTH_FIFO3_VAL);	
		
		/* CTU interrupt/DMA register (CTUIR) */
		REG16_BIT_SET(CTU_CTUIR, CTU_CTUIR_IEE_MASK);	/* CTUIR.IEE = 1, Interrupt Error Enable */
		
#else			/* No Using CTU_FIFO */
	CTU_0.FCR.R			= 0x0;
	CTU_0.TH1.R			= 0x0;			
	CTU_0.CTUIR.R		= 0x0;		
#endif
	
	/* Control ON time register (COTR) */
	CTU_COTR = (COTR_VALUE & 0xFF);	
	

	/* Cross triggering unit digital filter (CTUDF) */
	REG16_WRITE(CTU_CTUDF, FILTER_VALUE);
	
	/* Cross triggering unit power control register (CTUPCR) */
	mCTU_Module_En();

	/* Cross triggering unit control register (CTUCR) */
	mCTU_GRE_Set(ENABLE);
	REG16_BIT_SET(CTU_CTUCR, CTU_CTUCR_TGSISR_RE_MASK);		/* CTUCR.TGSISR_RE = 1, TGS Input Selection Register Reload Enable */
	
#endif
}


/* *****************************************************************************
   Function:        mCTU_FIFO_GetVal
   Description:     Get ADC Data from FIFOx while INTC not used
   Parameters:      Input:    
   						FIFONum:	FIFO Index
   						*u32ADC_Val:ADC Data Value
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
uint8	mCTU_FIFO_GetVal(uint8 FIFONum, uint32 *u32ADC_Val)
{
	uint8	StateRet;
	uint32	State_OF_Mask;
	
	StateRet = FALSE;
	State_OF_Mask = 0;
	if(FIFONum <= CTU_FIFO3)
	{
		switch(FIFONum)
		{
			case CTU_FIFO0:
				State_OF_Mask = CTU_FST_OF0_MASK;
				break;
			case CTU_FIFO1:
				State_OF_Mask = CTU_FST_OF1_MASK;
				break;
			case CTU_FIFO2:
				State_OF_Mask = CTU_FST_OF2_MASK;
				break;
			case CTU_FIFO3:
				State_OF_Mask = CTU_FST_OF3_MASK;
				break;
			default:
				break;	
		}
		
		/* Wait for Data */
		StateRet = OverTimeCheckLong(CTU_FST_P, State_OF_Mask, State_OF_Mask, TIMEOUT_CTU_ADC);
		
		if(StateRet)
		{
#if (ADC_ALIGN_MODE	== ADC_AL_RIGHT)
			*u32ADC_Val = CTU_FR(FIFONum);
#else
			*u32ADC_Val = CTU_FL(FIFONum);			
#endif			
		}
		else
		{
			*u32ADC_Val = 0;
		}		
	}
	else
	{
		/* do nothing */
	}

	return(StateRet);	
}


#ifdef	CTU_FIFO_0_ISR_EN
extern	void	pFUN_mCTU_IRQ202_FIFO0_Hook1(uint32 u32ADC);
extern	void	pFUN_mCTU_IRQ202_FIFO0_Hook2(void);
/* *****************************************************************************
   Function:        mCTU_FIFO0_ISR
   Description:     FIFO0 INTC Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_FIFO0_ISR(void)
{
	uint32	u32ADC_Tmp;
	uint8	TimeOutCnt = 0;
	
	if(CTU_FST & CTU_FST_FULL0_MASK)	/* FIFO 0 Full interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_EMP0_MASK)	/* FIFO 0 Empty interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_OF0_MASK)
	{
		/* OF_Flag Can't used for Reading all Data in FIFO; EMPTY_Flag Can */
		while( !(CTU_FST & CTU_FST_EMP0_MASK) )		
		{
#if (ADC_ALIGN_MODE	== ADC_AL_RIGHT)
			u32ADC_Tmp = CTU_FR(CTU_FIFO0);
#else
			u32ADC_Tmp = CTU_FL(CTU_FIFO0);			
#endif			
						
			/* User Hook Operate */
			pFUN_mCTU_IRQ202_FIFO0_Hook1(u32ADC_Tmp);
			
			/* Add while-quit judge, more than SYS_CTU_THRESH_0 then quit, and reEnter ISR again */
			TimeOutCnt++;
			if(TimeOutCnt >= CTU_FIFO0_SIZE)
			{
				break;
			}
			else
			{ }
		}

		/* User Hook Operate 2 */
		pFUN_mCTU_IRQ202_FIFO0_Hook2();
	}
	else
	{
		/* do nothing */
	}		

	if(CTU_FST & CTU_FST_OR0_MASK)	/* FIFO 0 Overrun interrupt flag */
	{
		CTU_FST = CTU_FST_OR0_MASK;
	}
	else
	{
		/* do nothing */
	}	
}
#endif


#ifdef	CTU_FIFO_1_ISR_EN
extern	void	pFUN_mCTU_IRQ203_FIFO1_Hook1(uint32 u32ADC);
extern	void	pFUN_mCTU_IRQ203_FIFO1_Hook2(void);
/* *****************************************************************************
   Function:        mCTU_FIFO1_ISR
   Description:     FIFO1 INTC Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_FIFO1_ISR(void)
{
	uint32	u32ADC_Tmp;
	uint8	TimeOutCnt = 0;

	if(CTU_FST & CTU_FST_FULL1_MASK)		/* FIFO 1 Full interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_EMP1_MASK)		/* FIFO 1 Empty interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_OF1_MASK)		/* FIFO 1 threshold Overflow interrupt flag */
	{
		/* OF_Flag Can't used for Reading all Data in FIFO; EMPTY_Flag Can */
		while( !(CTU_FST & CTU_FST_EMP1_MASK) )	
		{
#if (ADC_ALIGN_MODE	== ADC_AL_RIGHT)
			u32ADC_Tmp = CTU_FR(CTU_FIFO1);
#else
			u32ADC_Tmp = CTU_FL(CTU_FIFO1);			
#endif			

			/* User Hook Operate */
			pFUN_mCTU_IRQ203_FIFO1_Hook1(u32ADC_Tmp);
			
			/* Add while-quit judge, more than SYS_CTU_THRESH_1 then quit, and reEnter ISR again */
			TimeOutCnt++;
			if(TimeOutCnt >= CTU_FIFO1_SIZE)
			{
				break;
			}
			else
			{ }
		}

		/* User Hook Operate 2 */
		pFUN_mCTU_IRQ203_FIFO1_Hook2();
	}
	else
	{
		/* do nothing */
	}

	if(CTU_FST & CTU_FST_OR1_MASK)		/* FIFO 1 Overrun interrupt flag */
	{
		CTU_FST = CTU_FST_OR1_MASK;
	}
	else
	{
		/* do nothing */
	}
	
}
#endif


#ifdef	CTU_FIFO_2_ISR_EN
extern	void	pFUN_mCTU_IRQ204_FIFO2_Hook1(uint32 u32ADC);
extern	void	pFUN_mCTU_IRQ204_FIFO2_Hook2(void);
/* *****************************************************************************
   Function:        mCTU_FIFO2_ISR
   Description:     FIFO2 INTC Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_FIFO2_ISR(void)
{
	uint32	u32ADC_Tmp;
	uint8	TimeOutCnt = 0;
	
	if(CTU_FST & CTU_FST_FULL2_MASK)		/* FIFO 2 Full interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_EMP2_MASK)		/* FIFO 2 Empty interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_OF2_MASK)		/* FIFO 2 threshold Overflow interrupt flag */
	{
		/* OF_Flag Can't used for Reading all Data in FIFO; EMPTY_Flag Can */
		while( !(CTU_FST & CTU_FST_EMP2_MASK) )	
		{
#if (ADC_ALIGN_MODE	== ADC_AL_RIGHT)
			u32ADC_Tmp = CTU_FR(CTU_FIFO2);
#else
			u32ADC_Tmp = CTU_FL(CTU_FIFO2);			
#endif			

			/* User Hook Operate */
			pFUN_mCTU_IRQ204_FIFO2_Hook1(u32ADC_Tmp);
			
			/* Add while-quit judge, more than SYS_CTU_THRESH_2 then quit, and reEnter ISR again */
			TimeOutCnt++;
			if(TimeOutCnt >= CTU_FIFO2_SIZE)
			{
				break;
			}
			else
			{ }
		}
		
		/* User Hook Operate 2 */
		pFUN_mCTU_IRQ204_FIFO2_Hook2();
	}
	else
	{
		/* do nothing */
	}		

	if(CTU_FST & CTU_FST_OR2_MASK)		/* FIFO 2 Overrun interrupt flag */
	{
		CTU_FST = CTU_FST_OR2_MASK;
	}
	else
	{
		/* do nothing */
	}
}
#endif


#ifdef	CTU_FIFO_3_ISR_EN
extern	void	pFUN_mCTU_IRQ205_FIFO3_Hook1(uint32 u32ADC);
extern	void	pFUN_mCTU_IRQ205_FIFO3_Hook2(void);
/* *****************************************************************************
   Function:        mCTU_FIFO3_ISR
   Description:     FIFO3 INTC Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCTU_FIFO3_ISR(void)
{
	uint32	u32ADC_Tmp;
	uint8	TimeOutCnt = 0;

	if(CTU_FST & CTU_FST_FULL3_MASK)		/* FIFO 3 Full interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_EMP3_MASK)		/* FIFO 3 Empty interrupt flag */
	{
		;
	}
	else
	{
		/* do nothing */
	}
	
	if(CTU_FST & CTU_FST_OF3_MASK)		/* FIFO 3 threshold Overflow interrupt flag */
	{
		/* OF_Flag Can't used for Reading all Data in FIFO; EMPTY_Flag Can */
		while( !(CTU_FST & CTU_FST_EMP3_MASK) )	
		{
#if (ADC_ALIGN_MODE	== ADC_AL_RIGHT)
			u32ADC_Tmp = CTU_FR(CTU_FIFO3);
#else
			u32ADC_Tmp = CTU_FL(CTU_FIFO3);			
#endif			

			/* User Hook Operate */
			pFUN_mCTU_IRQ205_FIFO3_Hook1(u32ADC_Tmp);
			
			/* Add while-quit judge, more than SYS_CTU_THRESH_3 then quit, and reEnter ISR again */
			TimeOutCnt++;
			if(TimeOutCnt >= CTU_FIFO3_SIZE)
			{
				break;
			}
			else
			{ }
		}
		
		/* User Hook Operate 2 */
		pFUN_mCTU_IRQ205_FIFO3_Hook2();
	}
	else
	{
		/* do nothing */
	}		

	if(CTU_FST & CTU_FST_OR3_MASK)		/* FIFO 3 Overrun interrupt flag */
	{
		CTU_FST = CTU_FST_OR3_MASK;
	}
	else
	{
		/* do nothing */
	}
}
#endif


#ifdef	CTU_ERROR_ISR_EN
extern	void	CTU_Error_ISR_Hook(void);
/* *****************************************************************************
   Function:        mCTU_Error_ISR
   Description:     Error INTC Service Route
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void mCTU_Error_ISR(void)
{
    volatile uint16 tempVal;

    /* User Hook */
    CTU_Error_ISR_Hook();

    tempVal = CTU_0.CTUEFR.R; 	/* Error Flag Reg */
    CTU_0.CTUEFR.R = 0x1F;
}
#endif






/* End of file */