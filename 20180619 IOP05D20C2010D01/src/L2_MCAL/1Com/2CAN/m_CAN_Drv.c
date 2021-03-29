/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_CAN_Drv.c
*
* @brief    CAN Module Function, Init, Config CAN chan, Tx or Rx, Rx_ISR
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/07      CODER2       	   	N/A          Original
*     1.1        2012/09/27      CODER2			N/A          Add Cfg file
*     1.2        2012/10/19      ----			N/A          Modify for CCP Protocol
*     1.3        2012/11/02      CODER2			N/A          Add History Comment
*     1.4        2013/01/11      CODER2			N/A          CAN Update, Separate SendMess and MB_ISR 
*     1.5        2013/01/14      CODER2			N/A          Add BusOff Recover Function
*     1.6        2013/01/23      CODER2			N/A          Modify Rx_ISR's BUSY Timeout, and Clear-BufIntc; Add Tx_Send "MB[CODE]=ABORT" Can be Sent 
*******************************************************************************/

#ifndef M_CAN_DRV_C
#define M_CAN_DRV_C
#endif


/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_CAN_Drv.h"
#include 	"m_CAN_Cfg.h"
#include    "SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */

/* *****************************************************************************
   Function:        mCAN_Module_En
   Description:     Enable FlexCAN Module
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCAN_Module_En(void)
{
	CAN_MCR &= (~CAN_MCR_MDIS_MASK);	/* 0, Enable FlexCAN module */
}


/* *****************************************************************************
   Function:        mCAN_Module_Dis
   Description:     Disable FlexCAN Module
   Parameters:      Input:    	None
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:           
	LPM_ACK, This read-only bit indicates that FlexCAN is either in Disable Mode or Stop Mode.
	so the CPU can poll the LPM_ACK bit to know when FlexCAN has actually entered low power mode. 
	                  
   ***************************************************************************** */
uint8	mCAN_Module_Dis(void)
{
	uint8	StateRet;
	uint32	TimeOutCnt;
	
	TimeOutCnt = 0;
	StateRet = TRUE;
	
	CAN_MCR |= CAN_MCR_MDIS_MASK;				/* 1, Disable FlexCAN module */
	while(0 == (CAN_MCR & CAN_MCR_LPM_ACK_MASK) )	/* LPM_ACK = 1, FlexCAN either in Disable Mode or Stop mode */
	{
		TimeOutCnt++;
		if(TimeOutCnt > TIMEOUT_CAN_SOFT_RST)	/* Time Out */
		{
			StateRet = FALSE;
			break;
		}
		else
		{ }
	}
	
	return(StateRet);
}


/* *****************************************************************************
   Function:        mCAN_SoftRst
   Description:     Soft Reset
   					Reset: MCR (except the MDIS bit), TIMER, TCR, ECR, ESR, IMASK1, IFLAG1.
   					unaffected: CTRL,  RXIMR0--RXIMR63, RXGMASK, RX14MASK, RX15MASK, all Message Buffers
   Parameters:      Input:    None
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:           
   The SOFT_RST bit remains asserted while reset is pending, and is automatically 
   negated when reset completes. Therefore, software can poll this bit to know 
   when the soft reset has completed.
   ***************************************************************************** */
static	uint8	mCAN_SoftRst(void)
{
	uint8	StateRet;
	uint32	TimeOutCnt;
	
	TimeOutCnt = 0;
	StateRet = TRUE;
	CAN_MCR |= CAN_MCR_SOFT_RST_MASK;			/* 1, Resets Registers */
	
	while((CAN_MCR & CAN_MCR_SOFT_RST_MASK) )	/* 0, Soft Reset has completed */
	{		
		TimeOutCnt++;
		if(TimeOutCnt > TIMEOUT_CAN_SOFT_RST)	/* Time Out */
		{
			StateRet = FALSE;
			break;
		}
		else
		{ }
	}
	
	return(StateRet);
}


/* *****************************************************************************
   Function:        mCAN_IntcMask_En
   Description:     The corresponding buffer Interrupt is Enabled.
   Parameters:      Input:    	ValMaskBuf:	
   								Each bit enables or disables the respective FlexCAN Message Buffer (MB0 to MB31) Interrupt.
                    Output:  	None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCAN_IntcMask_En(uint8 ValMaskBuf)
{
	CAN_IMASK1 |= 1 << (ValMaskBuf & 0x1F);
}


/* *****************************************************************************
   Function:        mCAN_IntcMask_Dis
   Description:     The corresponding buffer Interrupt is Disabled.
   Parameters:      Input:    	ValMaskBuf:	
   								Each bit enables or disables the respective FlexCAN Message Buffer (MB0 to MB31) Interrupt.
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCAN_IntcMask_Dis(uint8 ValMaskBuf)
{
	CAN_IMASK1 &= ( ~( 1<< (ValMaskBuf & 0x1F)) );	
}


/* *****************************************************************************
   Function:        mCAN_RxFIFO_ID_Table_A_Set
   Description:     Set RxFIFO ID Table A format
   Parameters:      Input:	Index:		MB index
   							REM_Val: 	Remote Frame, bit_31; 0, Data_Frame; 1, Remote_Frame
							Ext_Val:	Extended Frame, bit_30; 0, Std_Frame; 1, Ext_Frame
							ID_Val:		ID, STD_ID, 11 most significant bits, shift 19
											EXT_ID, all bits, shift 1
                    Output:   None
   Notes: 		Format A: 
				Standard format, only 11 most significant bits (3 to 13) are used.
				Extended format, all bits are used.
   ***************************************************************************** */
static	void	mCAN_RxFIFO_ID_Table_A_Set(uint8 Index, uint32 REM_Val, uint32 Ext_Val, uint32 ID_Val)
{
	if(0 == Ext_Val)	/* Standard Frames */
	{
		ID_Val = (ID_Val & 0x7FF) << 19;		// STD_ID, 11 most significant bits, shift 19
	}
	else			/* Extended Frames */
	{
		ID_Val = (ID_Val & 0x1FFFFFFF) << 1;	/* EXT_ID, all bits, shift 1 */
		ID_Val |= (Ext_Val & 0x01) << 30;		/* EXT = 1, bit_30, for EXT_Frame */
	}
	ID_Val |= (REM_Val & 0x01) << 31;			/* bit_31; 0, Data_Frame; 1, Remote_Frame */
	
	CAN_RX_FIFO.ID_Table[Index].Word = ID_Val;
}


/* *****************************************************************************
   Function:        mCAN_RxFIFO_ID_Table_B_Set
   Description:     Set RxFIFO ID Table B format
   Parameters:      Input:	Index:		MB index
   							REM_Val: 	Remote Frame, bit_31; 0, Data_Frame; 1, Remote_Frame
							Ext_Val:	Extended Frame, bit_30; 0, Std_Frame; 1, Ext_Frame
							ID_High:	
							ID_Low:		
                    Output:   None
   Notes:       Format B:	
   				Standard format, 11 most significant bits (a full standard ID) (3 to 13) are used
   				Extended format, all 14 bits are used for 14 most significant bits ID.
   ***************************************************************************** */
static	void	mCAN_RxFIFO_ID_Table_B_Set(uint8 Index, uint32 REM_Val, uint32 Ext_Val, uint16 ID_High, uint16 ID_Low)
{
	if(0 == Ext_Val)	/* Standard Frames */
	{
		ID_High = (ID_High & 0x7FF) << 19;			// STD_ID, 11 most significant bits, shift 19
		ID_Low  = ID_High + (ID_Low & 0x7FF) << 3;	/* not used for STD_ID	*/	
	}
	else			/* Extended Frames */
	{
		ID_High = (ID_High & 0x3FFF) << 16;				
		ID_Low  = ID_High + (ID_Low & 0x3FFF) << 0;		/* EXT_ID */
		ID_Low += ((Ext_Val & 0x01) << 14) + ((Ext_Val & 0x01) << 30);	/* EXT = 1, bit_30, for EXT_Frame */
	}	
	ID_Low += ((REM_Val & 0x01) << 15) + ((REM_Val & 0x01) << 31);		/* bit_31; 0, Data_Frame; 1, Remote_Frame */
	
	CAN_RX_FIFO.ID_Table[Index].Word = ID_Low;
}


/* *****************************************************************************
   Function:        mCAN_RxFIFO_ID_Table_C_Set
   Description:     Set RxFIFO ID Table C format
   Parameters:      Input:	Index:		MB index
							ID_0, ID_1, ID_2, ID_3:	8 most significant bits of ID
                    Output:   None
   Notes:       Format C:          
                Standard and Extended, all 8 bits are used for 8 most significant bits ID.

   ***************************************************************************** */
static	void	mCAN_RxFIFO_ID_Table_C_Set(uint8 Index, uint32 ID_0, uint32 ID_1, uint32 ID_2, uint32 ID_3)
{
	ID_3 = (ID_3 & 0xFF) + ((ID_2 & 0xFF) << 8) + ((ID_1 & 0xFF) << 16) + ((ID_0 & 0xFF) << 24);
	CAN_RX_FIFO.ID_Table[Index].Word = ID_3;
}


/* *****************************************************************************
   Function:        mCAN_MB_ID_Set
   Description:     Set Tx MB's ID
   Parameters:      Input:	MessBufNum:		MB index
   							Prio_Val:		Local priority
   							ID_Std:			Standard ID
   							ID_Ext:			Extended ID
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
static	void	mCAN_MB_ID_Set(uint8 MessBufNum, uint32 Prio_Val, uint32 ID_Std, uint32 ID_Ext)
{
	uint32	ID_Tmp;
	
	ID_Tmp = ((Prio_Val & 0x07)<<29) + ((ID_Std & CAN_MB_ID_STD_MASK)<<18) + (ID_Ext & CAN_MB_ID_EXT_MASK);
	CAN_MB(MessBufNum).ID.Word = ID_Tmp;
}


/* *****************************************************************************
   Function:        mCAN_Enter_FreezeMode
   Description:     Enter Freeze Mode
   Parameters:      Input:    None
                    Output:   None
   Notes:           
				when MCR.HALT = 1 and MCR.FRZ = 1,then enter Freeze Mode.
				poll MCR.FRZ_ACK = 1? , 1, FlexCAN in Freeze mode.

   ***************************************************************************** */
static	uint8	mCAN_Enter_FreezeMode(void)
{
	uint8	StateRet;
	uint32	TimeOutCnt;
	
	TimeOutCnt = 0;
	StateRet = TRUE;	
	mCAN_Module_En();
	REG32_BIT_SET(CAN_MCR, CAN_MCR_FRZ_MASK);	/* MCR.FRZ = 1 */
	REG32_BIT_SET(CAN_MCR, CAN_MCR_HALT_MASK);	/* MCR.HALT = 1, to enter Freeze */
	while(0 == (CAN_MCR & CAN_MCR_FRZ_ACK_MASK) )	/* MCR.FRZ_ACK = 1, FlexCAN in Freeze mode */
	{
		TimeOutCnt++;
		if(TimeOutCnt > TIMEOUT_CAN_SOFT_RST)	/* Time Out */
		{
			StateRet = FALSE;
			break;
		}
		else
		{ }
	}
	
	return(StateRet);
}


/* *****************************************************************************
   Function:        mCAN_Modify_Baud
   Description:     Set
   Parameters:      Input:    BuadTag:	Buad Rate Macro, Ref in "m_CAN_Cfg.h"
                    Output:   None
   Notes:           
	EXP:	#define		CAN_BAUD_500K_1		((7<<24)|(0<<22)|(5<<19)|(3<<16)|(0<<7)|(4))
   ***************************************************************************** */
static	void	mCAN_Modify_Baud(uint32 BuadTag)
{
	/* PRESDIV */
	REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_PRESDIV_MASK);
	REG32_BIT_SET(CAN_CTRL, (BuadTag & CAN_CTRL_PRESDIV_MASK));
	/* PSEG1 */
	REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_PSEG1_MASK);
	REG32_BIT_SET(CAN_CTRL, (BuadTag & CAN_CTRL_PSEG1_MASK));
	/* PSEG2 */
	REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_PSEG2_MASK);
	REG32_BIT_SET(CAN_CTRL, (BuadTag & CAN_CTRL_PSEG2_MASK));
	/* PROPSEG */
	REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_PROPSEG_MASK);
	REG32_BIT_SET(CAN_CTRL, (BuadTag & CAN_CTRL_PROPSEG_MASK));
	/* SMP */
	REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_SMP_MASK);
	REG32_BIT_SET(CAN_CTRL, (BuadTag & CAN_CTRL_SMP_MASK));
	/* RJW */
	REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_RJW_MASK);
	REG32_BIT_SET(CAN_CTRL, (BuadTag & CAN_CTRL_RJW_MASK));
}


/* *****************************************************************************
   Function:        mCAN_Abort_Procedure
   Description:     
   Parameters:      Input:    	None
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:           
	(1) CPU writes 1001 into C/S word
	(2) CPU Read CODE, Compares it to the value that was written
	(3) If CODE different from 1001, Read IFLAG to check frame transmitted or being currently transmitted.
		if IFLAG.bit = 0, CPU must wait for it to be set,then Read CODE 
		to check aborted (CODE = 1001) or transmitted (CODE = 1000)
		
   ***************************************************************************** */
uint8	mCAN_Abort_Procedure(uint8 MessBufNum)
{
	uint8	StateRet;

	StateRet = FALSE;
#ifdef	CAN_USE_ABORT	
	/* (1) CPU writes 1001 into C/S word. */
	CAN_MB(MessBufNum).CS.Bits.CODE = CAN_CODE_TX_ABORT;
	
	/* (2) CPU Read CODE, Compares it to the value that was written. */
	if(CAN_MB(MessBufNum).CS.Bits.CODE != CAN_CODE_TX_ABORT)
	{
		/* (3) If CODE different from 1001, CPU must read corresponding IFLAG 
		   to check if the frame was transmitted or it is being currently transmitted.
		   if IFLAG.bit = 0, CPU must wait for it to be set, */
		StateRet = OverTimeCheckLong(&CAN_IFLAG1, (1<<MessBufNum), (1<<MessBufNum), TIMEOUT_CAN_ABORT);	
		if(StateRet == TRUE)
		{
			/* then CPU must Read CODE to check aborted (CODE = 1001) or transmitted (CODE = 1000). */
			if(	(CAN_MB(MessBufNum).CS.Bits.CODE == CAN_CODE_TX_ABORT)	||
				(CAN_MB(MessBufNum).CS.Bits.CODE == CAN_CODE_TX_INACTIVE)	)
			{
				StateRet = TRUE;
			}
			else
			{
				StateRet = FALSE;	/* failed */
			}
		}
		else
		{
			/* failed */
		}
	}
	else
	{
		StateRet = TRUE;
	}
#endif

	return(StateRet);
}


/* *****************************************************************************
   Function:        mCAN_BusOff_Recovery
   Description:     Bus Off Recovery by User
   Parameters:      Input:    	None
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:
	if CTRL.BOFF_REC = 1, then Auto-Recover from Bus Off is disabled. 
	User negate BOFF_REC (CTRL.BOFF_REC = 0) to recover from Bus Off State, 
	After 128 sequences of 11 recessive bits.
	Then re-asserted BOFF_REC bit again, to Disable Auto-Recover from Bus Off.	
   ***************************************************************************** */
uint8	mCAN_BusOff_Recovery(void)
{
	uint8	StateRet;
	
	StateRet = FALSE;	
#if(FALSE == CAN_BUSOFF_RECOVERY)
	/* CTRL.BOFF_REC = 1, to Recover from Bus Off */
	REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_BOFF_REC_MASK);
	/* Wait till 128 sequences of 11 recessive bits occur */
	StateRet = OverTimeCheckLong(&CAN_ESR, CAN_ESR_BUSOFF_STS_MASK, CAN_ESR_BUSOFF_STS_MASK, TIMEOUT_CAN_BUSOFF);		
	/* CTRL.BOFF_REC = 1, to Disable Auto-Recover from Bus Off */
	REG32_BIT_SET(CAN_CTRL, CAN_CTRL_BOFF_REC_MASK);	
#endif	
	return(StateRet);	
}

/* *****************************************************************************
   Function:        mCAN_Init
   Description:     Initialization of the CAN controller.
   Parameters:      Input:    None
                    Output:   None
   Notes:           
	(0) PCR CAN
	(1) soft reset, Disable Mode, Clock Source
	(2) Exit Disable, In Freeze
	(3) MCR Config
	(4) CTRL Config
	(5) Init MB C/S Word
	(6) Init MB Mask
	(7) Intc MASK
	(8) Exit Freeze to Complete Init
   ***************************************************************************** */
uint8	mCAN_Init(void)
{
	uint8	StateRet;
	uint8	i, j;
	
	i = 0;
	j = 0;
	StateRet = FALSE;
	
	/* (0) PCR CAN */
	SIU.PCR[CAN_TX_PIN].R  = CAN_TX_PCR;
	SIU.PCR[CAN_RX_PIN].R  = CAN_RX_PCR;
	
	/* (1) soft reset, Disable Mode, Clock Source */
	mCAN_Module_En();
	StateRet = mCAN_SoftRst();			/* Soft Reset */
	if(StateRet != TRUE)
	{
		;	/* do nothing, return */
	}
	else
	{
		StateRet = mCAN_Module_Dis();	/* Disable Mode */
		if(FALSE == StateRet)
		{
			;	/* do nothing, return */
		}
		else
		{
			/* Select Clock Source */
#ifdef	CAN_CLK_USE_PLL
			REG32_BIT_SET(CAN_CTRL, CAN_CTRL_CLK_SRC_MASK);		/* clock source is the bus clock. (driven by the PLL) */
#else
			REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_CLK_SRC_MASK);	/* clock source is the oscillator clock */
#endif
			/* (2) Exit Disable, In Freeze */
			StateRet = mCAN_Enter_FreezeMode();
			if(FALSE == StateRet)
			{
				;	/* do nothing, return */
			}
			else
			{
				/* (3) MCR Config */
				/* Backwards Compatibility Config */
#ifndef	CAN_USE_COMPAT_MASK
				REG32_BIT_SET(CAN_MCR, CAN_MCR_BCC_MASK);			/* Enable Individual Rx masking */
#else
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_BCC_MASK);			/* Disable Individual Rx masking, using RXGMASK, RX14MASK, RX15MASK */
#endif
				
				/* Self Reception Config */
#ifdef	CAN_SELF_TEST_DEBUG
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_SRX_DIS_MASK);
				REG32_BIT_SET(CAN_CTRL, CAN_CTRL_LPB_MASK);
#else
				REG32_BIT_SET(CAN_MCR, CAN_MCR_SRX_DIS_MASK);		/* Disable Self Reception */
				REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_LPB_MASK);		/* Disable Loop Back */				
#endif
				/* FIFO Enable Config */
#ifdef	CAN_USE_FIFO
				REG32_BIT_SET(CAN_MCR, CAN_MCR_FEN_MASK);
#else
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_FEN_MASK);
#endif
				/* Transmission Abort Mechanism */
#ifdef	CAN_USE_ABORT
				REG32_BIT_SET(CAN_MCR, CAN_MCR_AEN_MASK);			/* Enable Abort */
#else
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_AEN_MASK);
#endif

				/* Set Max Number of MB */
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_MAXMB_MASK);
				REG32_BIT_SET(CAN_MCR, ((CAN_MB_NUM-1)<<0));
				
				/* (4) CTRL Config */
				mCAN_Modify_Baud(CAN_BAUD_SELECT);					/* Selcet BaudRate */
#if(FALSE == CAN_BUSOFF_RECOVERY)	
				REG32_BIT_SET(CAN_CTRL, CAN_CTRL_BOFF_REC_MASK);	/* Disable Automatic Recovering from Bus-Off State */
#else
				REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_BOFF_REC_MASK);
#endif
				REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_TSYN_MASK);		/* Disable Timer Sync Feature */
				REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_LOM_MASK);		/* Not in Listen Only Mode */

				/* CAN Arbitration Mode (Local Priority) */
#if		(CAN_ARBTR_MODE == CAN_ARBTR_ID)
				REG32_BIT_SET(CAN_CTRL, CAN_CTRL_LBUF_MASK);	
#elif	(CAN_ARBTR_MODE == CAN_ARBTR_NUM)
				REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_LBUF_MASK);
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_LPRIO_EN_MASK);
#elif	(CAN_ARBTR_MODE == CAN_ARBTR_PRIO)
				REG32_BIT_CLEAR(CAN_CTRL, CAN_CTRL_LBUF_MASK);
				REG32_BIT_SET(CAN_MCR, CAN_MCR_LPRIO_EN_MASK);
#else
	#error  Error in 'm_CAN_Drv.h', CAN_SELF_TEST_DEBUG must be defined no more than CAN_ARBTR_PRIO
#endif

				/* (5)Init MB C/S Word */
#ifdef	CAN_USE_FIFO
				/* MB except FIFO Init */
				for(i=8; i<CAN_MB_NUM; i++)
				{
					CAN_MB(i).CS.Word = 0;
					CAN_MB(i).ID.Word = 0;

					for(j=0; j<8; j++)
					{
						CAN_MB(i).DATA.Bytes[j] = 0;
					}
				}

				/* Rx FIFO ID table Mode */
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_IDAM_MASK);
				REG32_BIT_SET(CAN_MCR, (CAN_ID_TABLE_FORMAT<<8));

				/* Rx FIFO ID table Mode */
	#if	(CAN_ID_TABLE_FORMAT == CAN_ID_TABLE_A)			/* One full ID */
				mCAN_RxFIFO_ID_Table_A_Set(0, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_0);
				mCAN_RxFIFO_ID_Table_A_Set(1, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_1);
				mCAN_RxFIFO_ID_Table_A_Set(2, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_2);
				mCAN_RxFIFO_ID_Table_A_Set(3, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_3);
				mCAN_RxFIFO_ID_Table_A_Set(4, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_4);
				mCAN_RxFIFO_ID_Table_A_Set(5, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_5);
				mCAN_RxFIFO_ID_Table_A_Set(6, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_6);
				mCAN_RxFIFO_ID_Table_A_Set(7, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_TABLE_7);

				/* Rx FIFO ID Mask */
				CAN_RXIMR(0)  = CAN_MASK_TABLE_0;
				CAN_RXIMR(1)  = CAN_MASK_TABLE_1;
				CAN_RXIMR(2)  = CAN_MASK_TABLE_2;
				CAN_RXIMR(3)  = CAN_MASK_TABLE_3;
				CAN_RXIMR(4)  = CAN_MASK_TABLE_4;
				CAN_RXIMR(5)  = CAN_MASK_TABLE_5;
				CAN_RXIMR(6)  = CAN_MASK_TABLE_6;
				CAN_RXIMR(7)  = CAN_MASK_TABLE_7;
				
	#elif	(CAN_ID_TABLE_FORMAT == CAN_ID_TABLE_B)		/* Two full std ID or two partial 14-bit ext ID */
				mCAN_RxFIFO_ID_Table_B_Set(0, CAN_ID_TABLE_REM, CAN_ID_TABLE_EXT, CAN_ID_HIGH, CAN_ID_TABLE_LOW);
	#elif	(CAN_ID_TABLE_FORMAT == CAN_ID_TABLE_C)		/* Four partial 8-bit IDs (std or ext) */
				mCAN_RxFIFO_ID_Table_C_Set(0, CAN_ID_0, CAN_ID_1, CAN_ID_2, CAN_ID_3);
	#elif	(CAN_ID_TABLE_FORMAT == CAN_ID_TABLE_D)
				/* All frames rejected.*/
	#else
		#error  Error in 'm_CAN_Drv.h', CAN_ID_TABLE_FORMAT must be defined no more than CAN_ID_TABLE_D
	#endif
	
#else
				/* All MB Init */
				for(i=0; i<CAN_MB_NUM; i++)
				{
					CAN_MB(i).CS.Word = 0;
					CAN_MB(i).ID.Word = 0;
					
					for(j=0; j<8; j++)
					{
						CAN_MB(i).DATA.Bytes[j] = 0;
					}
				}
				
				/* MB_00_03 IRQ_68 */
	#if(CAN_MB_00_03_USE == MB_USE_RX)
				for(i=0; i<4; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_EMPTY;
					mCAN_MB_ID_Set(i, 0, CAN_MB_00_03_ID_STD, CAN_MB_00_03_ID_EXT);
					CAN_RXIMR(i)  = CAN_MB_00_03_MASK;
				}
	#elif(CAN_MB_00_03_USE == MB_USE_TX)
				for(i=0; i<4; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
					CAN_MB(i).ID.Bits.PRIO = CAN_MB_00_03_ID_PRIO;
				}
	#elif(CAN_MB_00_03_USE == MB_USE_NONE)
				for(i=0; i<4; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_INACTIVE;
				}
	#endif

				/* MB_04_07 IRQ_69 */
	#if(CAN_MB_04_07_USE == MB_USE_RX)
				for(i=4; i<8; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_EMPTY;
					mCAN_MB_ID_Set(i, 0, CAN_MB_04_07_ID_STD, CAN_MB_04_07_ID_EXT);
					CAN_RXIMR(i)  = CAN_MB_04_07_MASK;
				}
	#elif(CAN_MB_04_07_USE == MB_USE_TX)
				for(i=4; i<8; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
					CAN_MB(i).ID.Bits.PRIO = CAN_MB_04_07_ID_PRIO;
				}
	#elif(CAN_MB_04_07_USE == MB_USE_NONE)
				for(i=4; i<8; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_INACTIVE;
				}
	#endif
#endif

				/* (5) Init MB C/S Word + (6) Init MB Mask */
				/* MB_08_11 IRQ_70 */
#if(CAN_MB_08_11_USE == MB_USE_RX)
				for(i=8; i<12; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_EMPTY;
					mCAN_MB_ID_Set(i, 0, CAN_MB_08_11_ID_STD, CAN_MB_08_11_ID_EXT);
					CAN_RXIMR(i)  = CAN_MB_08_11_MASK;
				}
#elif(CAN_MB_08_11_USE == MB_USE_TX)
				for(i=8; i<12; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
					CAN_MB(i).ID.Bits.PRIO = CAN_MB_08_11_ID_PRIO;
				}
#elif(CAN_MB_08_11_USE == MB_USE_NONE)
				for(i=8; i<12; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_INACTIVE;
				}
#endif

				/* MB_12_15 IRQ_71 */
#if(CAN_MB_12_15_USE == MB_USE_RX)
				for(i=12; i<16; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_EMPTY;
					mCAN_MB_ID_Set(i, 0, CAN_MB_12_15_ID_STD, CAN_MB_12_15_ID_EXT);
					CAN_RXIMR(i)  = CAN_MB_12_15_MASK;
				}
#elif(CAN_MB_12_15_USE == MB_USE_TX)
				for(i=12; i<16; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
					CAN_MB(i).ID.Bits.PRIO = CAN_MB_12_15_ID_PRIO;
				}
#elif(CAN_MB_12_15_USE == MB_USE_NONE)
				for(i=12; i<16; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_INACTIVE;
				}
#endif

				/* MB_16_31 IRQ_72 */
#if(CAN_MB_16_31_USE == MB_USE_RX)
				for(i=16; i<32; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_EMPTY;
					mCAN_MB_ID_Set(i, 0, CAN_MB_16_31_ID_STD, CAN_MB_16_31_ID_EXT);
					CAN_RXIMR(i)  = CAN_MB_16_31_MASK;
				}
#elif(CAN_MB_16_31_USE == MB_USE_TX)
				for(i=16; i<32; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
					CAN_MB(i).ID.Bits.PRIO = CAN_MB_16_31_ID_PRIO;
				}
#elif(CAN_MB_16_31_USE == MB_USE_NONE)
				for(i=16; i<32; i++)
				{
					CAN_MB(i).CS.Bits.CODE = CAN_CODE_RX_INACTIVE;
				}
#endif
	
#ifdef CAN_MB_ISR_EN
				/* (7) Intc MASK */
#ifdef CAN_USE_FIFO
				/* Rx FIFO Intc Mask */
				mCAN_IntcMask_En(FIFO_AVAI_MASK);
				mCAN_IntcMask_En(FIFO_WARN_MASK);
				mCAN_IntcMask_En(FIFO_OVERRN_MASK);
#else
				/* MB_00_07 Intc Mask */
				for(i=0; i<8; i++)
				{
					mCAN_IntcMask_En(i);
				}
#endif


				/* MB_08_31 Intc Mask */
				for(i=8; i<32; i++)
				{
					mCAN_IntcMask_En(i);
				}
#endif
						
				/* Other Intc Mask */
#ifdef	CAN_ERR_ISR_EN
				REG32_BIT_SET(CAN_CTRL, CAN_CTRL_ERR_MSK_MASK);		/* Error Intc */
#endif
#ifdef	CAN_BUSOFF_ISR_EN
				REG32_BIT_SET(CAN_MCR, CAN_MCR_WRN_EN_MASK);		/* Warning Intc */
				REG32_BIT_SET(CAN_CTRL, CAN_CTRL_BOFF_MSK_MASK);	/* Bus Off Intc */
				REG32_BIT_SET(CAN_CTRL, CAN_CTRL_TWRN_MSK_MASK);	/* Tx Warning Intc */
				REG32_BIT_SET(CAN_CTRL, CAN_CTRL_RWRN_MSK_MASK);	/* Rx Warning Intc */
#endif
#ifdef	CAN_WAKEUP_ISR_EN
				REG32_BIT_SET(CAN_MCR, CAN_MCR_WAK_MSK_MASK);		/* Wake Up Intc */
#endif

				/* (8) Exit Freeze to Complete Init */
				REG32_BIT_CLEAR(CAN_MCR, CAN_MCR_FRZ_MASK);
				mDalay_Nms(1);
				
				if(CAN_MCR & CAN_MCR_NOT_READY_MASK)
				{
					StateRet = FALSE;
				}
				else	/* Ready */
				{
					StateRet = TRUE;
				}
			}
		}
	}
	
	return(StateRet);
}


/* *****************************************************************************
   Function:        mCAN_MB_00_03_Send_Message
   Description:     Send CAN Frame through MB_00 to MB_03
   Parameters:      *pTxBuf:	Content of CAN Frame to be transmited
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:           
                   
   ***************************************************************************** */
uint8	mCAN_MB_00_03_Send_Message(stc_CAN_MB *pTxBuf)
{
	uint8 ret = FALSE;
#if(CAN_MB_00_03_USE == MB_USE_TX)
	uint8 i;
	
	for(i=0; i<4; i++)
	{
		/* MB can be still used after Abort (CODE=9) */
		if( (CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE) 	||
			(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_ABORT) 	)
		{
			pTxBuf->CS.Word &= CAN_CS_WORD_CODE_DEL;
			Memory_Copy_Src_to_Dest( (void *)&CAN_MB(i), (void *)pTxBuf, sizeof(stc_CAN_MB) );
   	        CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_TRANSMIT;
			
			ret = TRUE;
			break;
		}
		else
		{
			/* do nothing */
		}
	}
#else
	(void)pTxBuf;
#endif

	return(ret);		
}


/* *****************************************************************************
   Function:        mCAN_MB_04_07_Send_Message
   Description:     Send CAN Frame through MB_04 to MB_07
   Parameters:      *pTxBuf:	Content of CAN Frame to be transmited
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:

   ***************************************************************************** */
uint8	mCAN_MB_04_07_Send_Message(stc_CAN_MB *pTxBuf)
{
	uint8 ret = FALSE;
#if(CAN_MB_04_07_USE == MB_USE_TX)
	uint8 i;
	
	for(i=4; i<7; i++)
	{
		/* MB can be still used after Abort (CODE=9) */
		if( (CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE) 	||
			(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_ABORT) 	)
		{
			pTxBuf->CS.Word &= CAN_CS_WORD_CODE_DEL;
			Memory_Copy_Src_to_Dest( (void *)&CAN_MB(i), (void *)pTxBuf, sizeof(stc_CAN_MB) );
   	        CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_TRANSMIT;
			
			ret = TRUE;
			break;
		}
		else
		{
			/* do nothing */
		}
	}
#else
	(void)pTxBuf;
#endif

	return(ret);		
}


/* *****************************************************************************
   Function:        mCAN_MB_08_11_Send_Message
   Description:     Send CAN Frame through MB_08 to MB_11
   Parameters:      *pTxBuf:	Content of CAN Frame to be transmited
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:
                   
   ***************************************************************************** */
uint8	mCAN_MB_08_11_Send_Message(stc_CAN_MB *pTxBuf)
{
	uint8 ret = FALSE;
#if(CAN_MB_08_11_USE == MB_USE_TX)
	uint8 i;
	
	for(i=8; i<12; i++)
	{
		/* MB can be still used after Abort (CODE=9) */
		if( (CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE) 	||
			(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_ABORT) 	)
		{
			pTxBuf->CS.Word &= CAN_CS_WORD_CODE_DEL;
			Memory_Copy_Src_to_Dest( (void *)&CAN_MB(i), (void *)pTxBuf, sizeof(stc_CAN_MB) );
   	        CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_TRANSMIT;
			
			ret = TRUE;
			break;
		}
		else
		{
			/* do nothing */
		}
	}
#else
	(void)pTxBuf;
#endif

	return(ret);		
}


/* *****************************************************************************
   Function:        mCAN_MB_12_15_Send_Message
   Description:     Send CAN Frame through MB_12 to MB_15
   Parameters:      *pTxBuf:	Content of CAN Frame to be transmited
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:
                   
   ***************************************************************************** */
uint8	mCAN_MB_12_15_Send_Message(stc_CAN_MB *pTxBuf)
{
	uint8 ret = FALSE;
#if(CAN_MB_12_15_USE == MB_USE_TX)
	uint8 i;
	
	for(i=12; i<16; i++)
	{
		/* MB can be still used after Abort (CODE=9) */
		if( (CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE) 	||
			(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_ABORT) 	)
		{
			pTxBuf->CS.Word &= CAN_CS_WORD_CODE_DEL;
			Memory_Copy_Src_to_Dest( (void *)&CAN_MB(i), (void *)pTxBuf, sizeof(stc_CAN_MB) );
   	        CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_TRANSMIT;
			
			ret = TRUE;
			break;
		}
		else
		{
			/* do nothing */
		}
	}
#else
	(void)pTxBuf;
#endif

	return(ret);		
}


/* *****************************************************************************
   Function:        mCAN_MB_16_31_Send_Message
   Description:     Send CAN Frame through MB_16 to MB_31
   Parameters:      *pTxBuf:	Content of CAN Frame to be transmited
                    Output:   	TRUE,  success
                    			FALSE, fail
   Notes:
                   
   ***************************************************************************** */
uint8	mCAN_MB_16_31_Send_Message(stc_CAN_MB *pTxBuf)
{
	uint8 ret = FALSE;
#if(CAN_MB_16_31_USE == MB_USE_TX)
	uint8 i;
	
	for(i=16; i<31; i++)
	{
		/* MB can be still used after Abort (CODE=9) */
		if( (CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE) 	||
			(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_ABORT) 	)
		{
			pTxBuf->CS.Word &= CAN_CS_WORD_CODE_DEL;
			Memory_Copy_Src_to_Dest( (void *)&CAN_MB(i), (void *)pTxBuf, sizeof(stc_CAN_MB) );
   	        CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_TRANSMIT;
			
			ret = TRUE;
			break;
		}
		else
		{
			/* do nothing */
		}
	}
#else
	(void)pTxBuf;
#endif

	return(ret);		
}


/* *****************************************************************************
   Function:        mCAN_MB_All_Send_Clear
   Description:     Clear All Message Buffer
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCAN_MB_All_Send_Clear(void)
{
	uint8 i = 0;
#if(CAN_MB_00_03_USE == MB_USE_TX)
	for(i=0; i<4; i++)
	{
		Memory_Set_Dest( (void *)&CAN_MB(i), 0x0, sizeof(stc_CAN_MB) );
	}
#endif

#if(CAN_MB_04_07_USE == MB_USE_TX)
	for(i=4; i<8; i++)
	{
		Memory_Set_Dest( (void *)&CAN_MB(i), 0x0, sizeof(stc_CAN_MB) );
	}
#endif

#if(CAN_MB_08_11_USE == MB_USE_TX)
	for(i=8; i<12; i++)
	{
		Memory_Set_Dest( (void *)&CAN_MB(i), 0x0, sizeof(stc_CAN_MB) );
		CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
		CAN_MB(i).ID.Bits.PRIO = CAN_MB_08_11_ID_PRIO;
	}
#endif

#if(CAN_MB_12_15_USE == MB_USE_TX)
	for(i=12; i<16; i++)
	{
		Memory_Set_Dest( (void *)&CAN_MB(i), 0x0, sizeof(stc_CAN_MB) );
		CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
		CAN_MB(i).ID.Bits.PRIO = CAN_MB_12_15_ID_PRIO;
	}
#endif

#if(CAN_MB_16_31_USE == MB_USE_TX)
	for(i=16; i<32; i++)
	{
		Memory_Set_Dest( (void *)&CAN_MB(i), 0x0, sizeof(stc_CAN_MB) );
		CAN_MB(i).CS.Bits.CODE = CAN_CODE_TX_INACTIVE;
		CAN_MB(i).ID.Bits.PRIO = CAN_MB_16_31_ID_PRIO;
	}
#endif		
}


/* *****************************************************************************
   Function:        mCAN_Get_Fault_Conf_State
   Description:     get the state of Fault information from ESR reg. 
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
uint8	mCAN_Get_Fault_Conf_State(void)
{
	return( (uint8)( (CAN_ESR&CAN_ESR_FLT_CONF_MASK)>>4 ) );
}

extern void pFUN_mCAN_MB_FIFO_Hook(stc_CAN_MB *tCanBuf);

extern void pFUN_mCAN_MB_00_03_Hook(stc_CAN_MB *tCanBuf);
extern void pFUN_mCAN_MB_04_07_Hook(stc_CAN_MB *tCanBuf);
extern void pFUN_mCAN_MB_08_11_Hook(stc_CAN_MB *tCanBuf);
extern void pFUN_mCAN_MB_12_15_Hook(stc_CAN_MB *tCanBuf);
extern void pFUN_mCAN_MB_16_31_Hook(stc_CAN_MB *tCanBuf);
/* *****************************************************************************
   Function:        CanRx_L2_Per
   Description:     
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void  CanRx_L2_Per(void)
{
	stc_CAN_MB 	CANTxRxBuf;
	uint8	TimeOutCnt = 0;

	if(CAN_IFLAG1 & CAN_IFLAG1_FIFO_OVERRN_MASK)
	{
		mCAN_Clear_BufIntc(FIFO_OVERRN_MASK);
	}
	else
	{ }
	
	if(CAN_IFLAG1 & CAN_IFLAG1_FIFO_WARN_MASK)
	{
		mCAN_Clear_BufIntc(FIFO_WARN_MASK);
	}
	else
	{
	}	
	
	if(CAN_IFLAG1 & CAN_IFLAG1_FIFO_AVAI_MASK)
	{
		/* Clear Available Intc to release buffer and allow CPU to read next FIFO entry) */
		while(CAN_IFLAG1 & CAN_IFLAG1_FIFO_AVAI_MASK)
		{
			/* (1) Read the C/S word */
			/* (2) Read ID */
			/* (3) Read Data */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(0), sizeof(CANTxRxBuf) );
			
			/* (4) Clear Intc */
			mCAN_Clear_BufIntc(FIFO_AVAI_MASK);
			
			/* User Operation */
			pFUN_mCAN_MB_FIFO_DIAG_Hook(&CANTxRxBuf);/* gcj integrate */
			
			pFUN_mCAN_MB_FIFO_Hook(&CANTxRxBuf);
			
			/* Add while-quit judge, more than CAN_RXFIFO_SIZE then quit, and reEnter again */
			TimeOutCnt++;
			if(TimeOutCnt >= CAN_RXFIFO_SIZE)
			{
				break;
			}
			else
			{ }
		}		
	}
	else
	{ }  
	
}
/* *****************************************************************************
   Function:        CanTx_L2_Confirm
   Description:     
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void  CanTx_L2_Confirm(void)
{
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;

	for(i=8;i<(8 + 4);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{		
			if(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE)  /* tx success */
			{
				Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );

				/* Clear Intc Flag, before User Operation */
				mCAN_Clear_BufIntc(i);

				/* User Operation */
			//	pFUN_mCAN_MB_08_11_Hook(&CANTxRxBuf);
				//pFUN_mCAN_MB_16_31_Hook(&CANTxRxBuf);
			}
			else
			{
				mCAN_Clear_BufIntc(i);	/* Clear IFLAG */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	
	
	for(i=12;i<(12 + 4);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{
			/* Read MB, Read C/S (mandatory: Activates an Internal Lock ) */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );
			
			/* unlock the MB */
			CAN_TIMER;
			
			/* Clear Intc Flag, before User Operation */
			mCAN_Clear_BufIntc(i);
			
			/* User Operation */
			pFUN_mCAN_MB_12_15_Hook(&CANTxRxBuf);			
		}
		else
		{
			/* do nothing */
		}
	}	

}
/* *****************************************************************************
   Function:        mCAN_IRQ65_Err_ISR
   Description:     Error Interrupt, any Error Bit in the Error and Status Register.
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
#ifdef	CAN_ERR_ISR_EN
extern	void	pFUN_mCAN_IRQ65_Err_Hook(void);

void	mCAN_IRQ65_Err_ISR(void)
{
	if(CAN_ESR & CAN_ESR_ERR_INT_MASK)
	{
		mCAN_Clear_ErrIntc;
		/* User Hook Operation */
		pFUN_mCAN_IRQ65_Err_Hook();
	}
}
#endif


/* *****************************************************************************
   Function:        mCAN_IRQ66_BusOff_Warn_ISR
   Description:     Bus Off 										||
   					TX_Err_Counter transitioned from < 96 to >= 96 	||
   					RX_Err_Counter transitioned from < 96 to >= 96
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
#ifdef	CAN_BUSOFF_ISR_EN
extern	void	pFUN_mCAN_IRQ66_BusOff_Hook(void);
extern	void	pFUN_mCAN_IRQ66_TxWarn_Hook(void);
extern	void	pFUN_mCAN_IRQ66_RxWarn_Hook(void);

void	mCAN_IRQ66_BusOff_Warn_ISR(void)
{
	/* ¡®Bus Off¡¯ state. */
	if(CAN_ESR & CAN_ESR_BOFF_INT_MASK)
	{
		mCAN_Clear_BusOffIntc;
		/* User Operation */
		pFUN_mCAN_IRQ66_BusOff_Hook();
	}
	else
	{ }
	
	/* TX_Err_Counter transitioned from < 96 to >= 96 */
	if(CAN_ESR & CAN_ESR_TWRN_INT_MASK)
	{
		mCAN_Clear_TxWarnIntc;
		/* User Operation */
		pFUN_mCAN_IRQ66_TxWarn_Hook();
	}
	else
	{ }

	/* RX_Err_Counter transitioned from < 96 to >= 96  */
	if(CAN_ESR & CAN_ESR_RWRN_INT_MASK)
	{
		mCAN_Clear_RxWarnIntc;
		/* User Operation */
		pFUN_mCAN_IRQ66_RxWarn_Hook();
	}
	else
	{ }	
}
#endif

/* *****************************************************************************
   Function:        mCAN_IRQ67_WakeUp_ISR
   Description:     Wake-Up Interrupt,
   					a Recessive to Dominant transition received on the CAN bus 
   					when the FlexCAN module is in Stop Mode
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
#ifdef	CAN_WAKEUP_ISR_EN
extern	void	pFUN_mCAN_IRQ67_WakeUp_Hook(void);

void	mCAN_IRQ67_WakeUp_ISR(void)
{
	if(CAN_ESR & CAN_ESR_WAK_INT_MASK)
	{
		mCAN_Clear_WakeUpIntc;
		/* User Operation */
		pFUN_mCAN_IRQ67_WakeUp_Hook();
	}
	else
	{ }	
}
#endif



#ifdef	CAN_MB_ISR_EN
/* *****************************************************************************
   Function:        mCAN_IRQ68_MB_00_03_ISR
   Description:     Message Buffers 00 to 03 Interrupt, if FIFO not used, IRQ68
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCAN_IRQ68_MB_00_03_ISR(void)
{
#ifndef CAN_USE_FIFO
	#define MB_ST_INDEX 0
	#define MB_LEN      4

	/* Rx_ISR */
	#if(CAN_MB_00_03_USE == MB_USE_RX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;

	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{
			/* Read MB, Read C/S (mandatory: Activates an Internal Lock ) */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );
			
			/* unlock the MB */
			CAN_TIMER;
			
			/* Clear Intc Flag, before User Operation */
			mCAN_Clear_BufIntc(i);
					
			/* User Operation */
			pFUN_mCAN_MB_00_03_Hook(&CANTxRxBuf);
		}
		else
		{
			/* do nothing */
		}
	}

	/* Tx_ISR */
	#elif(CAN_MB_00_03_USE == MB_USE_TX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;

	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{		
				
			if(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE)  /* tx success */
			{
				Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );

				/* Clear Intc Flag, before User Operation */
				mCAN_Clear_BufIntc(i);

				/* User Operation */
				pFUN_mCAN_MB_00_03_Hook(&CANTxRxBuf);
			}
			else
			{
				mCAN_Clear_BufIntc(i);	/* Clear IFLAG */
			}
		}
		else
		{
			/* do nothing */
		}
	}

	/* MB_USE_NONE */
	#else
	
	uint8 i;
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++) /* error */
	{
		CAN_MB(i).CS.Bits.CODE;
		mCAN_Clear_BufIntc(i);
	    CAN_MB(i).CS.Bits.TIMESTAMP;
	    CAN_TIMER; /* unlock the MB */
	}
	
	#endif		
 
	#undef MB_ST_INDEX 
	#undef MB_LEN
#endif

}
/* *****************************************************************************
   Function:        mCAN_IRQ69_MB_04_07_ISR
   Description:     Message Buffers 04 to 07 Interrupt, include FIFO_ISR, IRQ69
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   ***************************************************************************** */
void	mCAN_IRQ69_MB_04_07_ISR(void)
{
	/* FIFO_ISR */
#ifdef CAN_USE_FIFO
  
	stc_CAN_MB 	CANTxRxBuf;
	uint8	TimeOutCnt = 0;

	if(CAN_IFLAG1 & CAN_IFLAG1_FIFO_OVERRN_MASK)
	{
		mCAN_Clear_BufIntc(FIFO_OVERRN_MASK);
	}
	else
	{ }
	
	if(CAN_IFLAG1 & CAN_IFLAG1_FIFO_WARN_MASK)
	{
		mCAN_Clear_BufIntc(FIFO_WARN_MASK);
	}
	else
	{ }	
	
	if(CAN_IFLAG1 & CAN_IFLAG1_FIFO_AVAI_MASK)
	{
		/* Clear Available Intc to release buffer and allow CPU to read next FIFO entry) */
		while(CAN_IFLAG1 & CAN_IFLAG1_FIFO_AVAI_MASK)
		{
			/* (1) Read the C/S word */
			/* (2) Read ID */
			/* (3) Read Data */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(0), sizeof(CANTxRxBuf) );
			
			/* (4) Clear Intc */
			mCAN_Clear_BufIntc(FIFO_AVAI_MASK);
			
			/* User Operation */
			//pFUN_mCAN_MB_FIFO_DIAG_Hook(&CANTxRxBuf);/* gcj integrate */
			
			pFUN_mCAN_MB_FIFO_Hook(&CANTxRxBuf);
			
			/* Add while-quit judge, more than CAN_RXFIFO_SIZE then quit, and reEnter again */
			TimeOutCnt++;
			if(TimeOutCnt >= CAN_RXFIFO_SIZE)
			{
				break;
			}
			else
			{ }
		}		
	}
	else
	{ }  

#else
	#define MB_ST_INDEX 4
	#define MB_LEN      4

	/* Rx_ISR */
	#if(CAN_MB_04_07_USE == MB_USE_RX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;
	
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{
			/* Read MB, Read C/S (mandatory: Activates an Internal Lock ) */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );
			
			/* unlock the MB */
			CAN_TIMER;
			
			/* Clear Intc Flag, before User Operation */
			mCAN_Clear_BufIntc(i);

			/* User Operation */
			pFUN_mCAN_MB_04_07_Hook(&CANTxRxBuf);
		}
		else
		{
			/* do nothing */
		}	
	}
	
	/* Tx_ISR */
	#elif(CAN_MB_04_07_USE == MB_USE_TX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;

	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{	
			if(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE)  /* tx success */
			{
				Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );
				
				/* Clear Intc Flag, before User Operation */
				mCAN_Clear_BufIntc(i);

				/* User Operation */
				pFUN_mCAN_MB_04_07_Hook(&CANTxRxBuf);
			}
			else
			{
				mCAN_Clear_BufIntc(i);	/* Clear IFLAG */
			}
		}
		else
		{
			/* do nothing */
		}
	}

	/* MB_USE_NONE */
	#else
	
	uint8 i;
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++) /* error */
	{
		CAN_MB(i).CS.Bits.CODE;
		mCAN_Clear_BufIntc(i);
	    CAN_MB(i).CS.Bits.TIMESTAMP;
	    CAN_TIMER; /* unlock the MB */
	}
	
	#endif		
 
	#undef MB_ST_INDEX 
	#undef MB_LEN     
#endif
}


/* *****************************************************************************
   Function:        mCAN_IRQ70_MB_08_11_ISR
   Description:     Message Buffers 08 to 11 Interrupt, IRQ70
   Parameters:      Input:    None
                    Output:   None
   Notes:           
 
   ***************************************************************************** */
void	mCAN_IRQ70_MB_08_11_ISR(void)
{
	#define	MB_ST_INDEX	8
	#define	MB_LEN		4
	
	/* Rx_ISR */
#if(CAN_MB_08_11_USE == MB_USE_RX)

	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;
	
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{
			/* Read MB, Read C/S (mandatory: Activates an Internal Lock ) */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );
			
			/* unlock the MB */
			CAN_TIMER;
			
			/* Clear Intc Flag, before User Operation */
			mCAN_Clear_BufIntc(i);

			/* User Operation */
			pFUN_mCAN_MB_08_11_Hook(&CANTxRxBuf);	
		}
		else
		{
			/* do nothing */
		}
	}
	
	/* Tx_ISR */
#elif(CAN_MB_08_11_USE == MB_USE_TX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;

	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{		
			if(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE)  /* tx success */
			{
				Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );

				/* Clear Intc Flag, before User Operation */
				mCAN_Clear_BufIntc(i);

				/* User Operation */
				pFUN_mCAN_MB_08_11_Hook(&CANTxRxBuf);
			}
			else
			{
				mCAN_Clear_BufIntc(i);	/* Clear IFLAG */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	
	/* MB_USE_NONE */
#else
	
	uint8 i;
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++) /* error */
	{
		CAN_MB(i).CS.Bits.CODE;
		mCAN_Clear_BufIntc(i);
		CAN_MB(i).CS.Bits.TIMESTAMP;
		CAN_TIMER; /* unlock the MB */
	}
#endif		
 
	#undef MB_ST_INDEX 
	#undef MB_LEN     
}


/* *****************************************************************************
   Function:        mCAN_IRQ71_MB_12_15_ISR
   Description:     Message Buffers 12 to 15 Interrupt, IRQ71
   Parameters:      Input:    None
                    Output:   None
   Notes:           
 
   ***************************************************************************** */
void	mCAN_IRQ71_MB_12_15_ISR(void)
{
	#define MB_ST_INDEX 12
	#define MB_LEN      4

	/* Rx_ISR */
#if(CAN_MB_12_15_USE == MB_USE_RX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;
		
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{
			/* Read MB, Read C/S (mandatory: Activates an Internal Lock ) */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );
			
			/* unlock the MB */
			CAN_TIMER;
			
			/* Clear Intc Flag, before User Operation */
			mCAN_Clear_BufIntc(i);
			
			/* User Operation */
			pFUN_mCAN_MB_12_15_Hook(&CANTxRxBuf);			
		}
		else
		{
			/* do nothing */
		}
	}
	
	/* Tx_ISR */
#elif(CAN_MB_12_15_USE == MB_USE_TX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;

	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{		
				
			if(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE)  /* tx success */
			{
				Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );

				/* Clear Intc Flag, before User Operation */
				mCAN_Clear_BufIntc(i);

				/* User Operation */
				pFUN_mCAN_MB_12_15_Hook(&CANTxRxBuf);
			}
			else
			{
				mCAN_Clear_BufIntc(i);	/* Clear IFLAG */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	
	/* MB_USE_NONE */
#else
	
	uint8 i;
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++) /* error */
	{
		CAN_MB(i).CS.Bits.CODE;
		mCAN_Clear_BufIntc(i);
	    CAN_MB(i).CS.Bits.TIMESTAMP;
	    CAN_TIMER; /* unlock the MB */
	}
	
#endif		
 
	#undef MB_ST_INDEX 
	#undef MB_LEN     
}


/* *****************************************************************************
   Function:        mCAN_IRQ72_MB_16_31_ISR
   Description:     Message Buffers 16 to 31 Interrupt, IRQ72
   Parameters:      Input:    None
                    Output:   None
   Notes:           
 
   ***************************************************************************** */
void	mCAN_IRQ72_MB_16_31_ISR(void)
{
	#define MB_ST_INDEX 16
	#define MB_LEN      16	/* 31 */

	/* Rx_ISR */
#if(CAN_MB_16_31_USE == MB_USE_RX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;
		
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{
			/* Read MB, Read C/S (mandatory: Activates an Internal Lock ) */
			Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );
			
			/* unlock the MB */
			CAN_TIMER;
			
			/* Clear Intc Flag, before User Operation */
			mCAN_Clear_BufIntc(i);
			
			/* User Operation */
			pFUN_mCAN_MB_16_31_Hook(&CANTxRxBuf);	
		}
		else
		{
			/* do nothing */
		}
	}

	/* Tx_ISR */
#elif(CAN_MB_16_31_USE == MB_USE_TX)
	
	uint8 i;
	stc_CAN_MB 	CANTxRxBuf;

	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++)
	{
		/* never perform polling by directly reading the C/S word of the MBs. */
		/* Instead, read the IFLAG registers. Page 753 */
		if(CAN_IFLAG1 & (1<<i)) 
		{		
				
			if(CAN_MB(i).CS.Bits.CODE == CAN_CODE_TX_INACTIVE)  /* tx success */
			{
				Memory_Copy_Src_to_Dest((void *)&CANTxRxBuf, (void *)&CAN_MB(i), sizeof(CANTxRxBuf) );

				/* Clear Intc Flag, before User Operation */
				mCAN_Clear_BufIntc(i);

				/* User Operation */
				pFUN_mCAN_MB_16_31_Hook(&CANTxRxBuf);
			}
			else
			{
				mCAN_Clear_BufIntc(i);	/* Clear IFLAG */
			}
		}
		else
		{
			/* do nothing */
		}
	}

	/* MB_USE_NONE */
#else
	uint8 i;
	for(i=MB_ST_INDEX;i<(MB_ST_INDEX + MB_LEN);i++) /* error */
	{
		CAN_MB(i).CS.Bits.CODE;
		mCAN_Clear_BufIntc(i);
	    CAN_MB(i).CS.Bits.TIMESTAMP;
	    CAN_TIMER; /* unlock the MB */
	}
	
#endif		
 
	#undef MB_ST_INDEX 
	#undef MB_LEN     
}



#endif

/* End of file */