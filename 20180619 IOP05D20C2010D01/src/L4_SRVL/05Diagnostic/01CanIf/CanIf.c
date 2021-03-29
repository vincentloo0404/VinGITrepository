/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanIf.c  
*
* @brief  interface for CanDrv and CanTp.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/25    CODER1     N/A           Original
*     1.1      2018/06/26    YCH        N/A           Original 
*     
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "CanTp_Cbk.h"
#include "L5_APPL.h"
//#include "hFbl_Serv.h"


static stc_CAN_MB CanTpTxPduObj;
static PduInfoType CanIf_TpRxPduInfo;

/* BEGIN_FUNCTION_HDR
 ********************************************************************
 * Function Name:dDiag_vCanIfInit
 * Description:
 * Inputs:
 *   None.
 * Outputs:
 *   None.
 * Limitations:
 *   None.
 ********************************************************************
 END_FUNCTION_HDR*/  
   
void dDiag_vCanIfInit(void)
{
	CanTpTxPduObj.CS.Word = 0x00000000u;
	CanIf_TpRxPduInfo.SduLength = 0u;
}

/* BEGIN_FUNCTION_HDR
 ********************************************************************
 * Function Name:CanIf_Transmit
 * Description:
 * Inputs:
 *   None.
 * Outputs:
 *   None.
 * Limitations:
 *   None.
 ********************************************************************
 END_FUNCTION_HDR*/
   
Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType* PduInfoPtr)
{
	uint8 i;
	Std_ReturnType CanTxResult= E_OK;
	stc_CAN_MB CanTpTxTestObj;
	if (CanTxPduId>CANIF_MAX_TXPDUHANDLE) 
	{
	    return E_NOT_OK;
	}
	else
	{
		
	}

	if (CanIf_TxPduConfig[CanTxPduId].CanIdType==STANDARD_CAN) 
	{
	    CanTpTxPduObj.ID.Bits.STD_ID= CanIf_TxPduConfig[CanTxPduId].CanId;
	} 
	else 
	{
	    CanTpTxPduObj.ID.Word = CanIf_TxPduConfig[CanTxPduId].CanId;
	}

	for (i=0;i<PduInfoPtr->SduLength;i++) 
	{
	    CanTpTxPduObj.DATA.Bytes[i]= PduInfoPtr->SduDataPtr[i];
	}

	CanTpTxPduObj.CS.Bits.LENGTH= (uint8)PduInfoPtr->SduLength;

	CanTxResult = (!mCAN_MB_16_31_Send_Message(&CanTpTxPduObj));
	
	
	
	if (CanIf_TxPduConfig[CanTxPduId].CanIdType==STANDARD_CAN) 
	{
	    CanTpTxTestObj.ID.Bits.STD_ID= 0x7B5;
	} 
	else 
	{
	    CanTpTxTestObj.ID.Word = CanIf_TxPduConfig[CanTxPduId].CanId;
	}

	for (i=0;i<PduInfoPtr->SduLength;i++) 
	{
	    CanTpTxTestObj.DATA.Bytes[i]= PduInfoPtr->SduDataPtr[i];
	}

	CanTpTxTestObj.CS.Bits.LENGTH= (uint8)PduInfoPtr->SduLength;
	CanTxResult = (!mCAN_MB_08_11_Send_Message(&CanTpTxTestObj));
	
	return CanTxResult;
}

/* BEGIN_FUNCTION_HDR
 ********************************************************************
 * Function Name:CanIf_RxIndication
 * Description:
 * Inputs:
 *   None.
 * Outputs:
 *   None.
 * Limitations:
 *   None.
 ********************************************************************
 END_FUNCTION_HDR*/
   
void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8* CanSduPtr)
{
	uint8 handle;
	PduIdType CanTpRxPduId;
	(void)Hrh;
	
	for (handle=0;handle<CANIF_MAX_RXPDUHANDLE;handle++) 
	{
		if (CanIf_RxPduIdConfig[handle].CanId==CanId) 
		{
			CanTpRxPduId= handle;            /*CAN L-PDU ID was found*/
			break;
		}
		else
		{
			
		}
	}

	if (handle >= CANIF_MAX_RXPDUHANDLE) 
	{
		return;
	}
	else
	{
		
	}
	
	if (CanDlc>8)                        /*DLC Check (optional)*/
	{
		return;
	}
	else
	{
		
	}

	CanIf_TpRxPduInfo.SduLength= CanDlc;
	CanIf_TpRxPduInfo.SduDataPtr= (uint8 *)CanSduPtr;
	CanTp_RxIndication(CanTpRxPduId, &CanIf_TpRxPduInfo);
}

/* BEGIN_FUNCTION_HDR
 ********************************************************************
 * Function Name:CanIf_TxConfirmation
 * Description:
 * Inputs:
 *   None.
 * Outputs:
 *   None.
 * Limitations:
 *   None.
 ********************************************************************
 END_FUNCTION_HDR*/
void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
	if (CanTxPduId>CANIF_MAX_TXPDUHANDLE) 
	{          
		return;
	}
	else
	{

	}

	CanTp_TxConfirmation(CanTxPduId);
}

#if (CANIF_TRANSMIT_CANCELLATION == STD_ON)

/* BEGIN_FUNCTION_HDR
 ********************************************************************
 * Function Name:CanIf_CancelTransmit
 * Description:
 * Inputs:
 *   None.
 * Outputs:
 *   None.
 * Limitations:
 *   None.
 ********************************************************************
 END_FUNCTION_HDR*/
Std_ReturnType CanIf_CancelTransmit(PduIdType CanTxPduId)
{
	(void)CanTxPduId;
	return E_OK;
}

#endif

/* BEGIN_FUNCTION_HDR
 ********************************************************************
 * Function Name:pFUN_mCAN_MB_FIFO_DIAG_Hook
 * Description:  hook function for diag request and called in Can receive Interrupt ISR.
 * Inputs:      *tCanBuf
 *   None.
 * Outputs:
 *   None.
 * Limitations: temp function debug for diag.
 *   None.
 ********************************************************************
 END_FUNCTION_HDR*/
void pFUN_mCAN_MB_FIFO_DIAG_Hook(stc_CAN_MB *tCanBuf)
{	
	uint8 i;

	uint32 canid = 0x0;	 

	for (i=0;i<CANIF_MAX_RXPDUHANDLE;i++) 
	{
		if (STANDARD_CAN == CanIf_RxPduIdConfig[i].CanIdType) 
		{
			canid = tCanBuf->ID.Bits.STD_ID;

			if (canid==CanIf_RxPduIdConfig[i].CanId)
			{
				/*
				//for BootLoader DownLoad//
				if (canid==CanIf_RxPduIdConfig[0].CanId 
				    && (tCanBuf->DATA.Bytes[0]==0x02) 
				    &&(tCanBuf->DATA.Bytes[1]==0x10)
				    &&((tCanBuf->DATA.Bytes[2]==0x02)||(tCanBuf->DATA.Bytes[2]==0x82)))
				{
					hFbl_vSet_BootRecFlag();
				} 
				else //for normal diagnose action//
				{
				    CanIf_RxIndication(0u,canid,(unsigned char)tCanBuf->CS.Bits.LENGTH,(const unsigned char*)tCanBuf->DATA.Bytes);	       
				}
				*/
				UDS_TimeOutCnt = 0;
				CanIf_RxIndication(0u,canid,(unsigned char)tCanBuf->CS.Bits.LENGTH,(const unsigned char*)tCanBuf->DATA.Bytes);	 
				break;
			}
			else
			{
				
			}		   
		}
		else
		{
			canid = tCanBuf->ID.Word;
				   
			if (canid==CanIf_RxPduIdConfig[i].CanId)
			{
				/*
			    //for BootLoader DownLoad//
			    if (canid==CanIf_RxPduIdConfig[0].CanId 
			        && (tCanBuf->DATA.Bytes[0]==0x02) 
			        &&(tCanBuf->DATA.Bytes[1]==0x10)
			        &&((tCanBuf->DATA.Bytes[2]==0x02)||(tCanBuf->DATA.Bytes[2]==0x82))) 
			    {
					;
			    } 
			    else //for normal diagnose action//
			    {
			       CanIf_RxIndication(0u,canid,(unsigned char)tCanBuf->CS.Bits.LENGTH,(const unsigned char*)tCanBuf->DATA.Bytes);
			    }
			    */
			    CanIf_RxIndication(0u,canid,(unsigned char)tCanBuf->CS.Bits.LENGTH,(const unsigned char*)tCanBuf->DATA.Bytes);
			    break;			    
			}
			else
			{
				
			}

		}

	}

}

/* BEGIN_FUNCTION_HDR
 ********************************************************************
 * Function Name:pFUN_mCAN_MB_16_31_Hook
 * Description:  hook function for diag response and called in Can Transmit Interrupt ISR.
 * Inputs:       *tCanBuf
 *   None.
 * Outputs:
 *   None.
 * Limitations: temp function debug for diag.
 *   None.
 ********************************************************************
 END_FUNCTION_HDR*/
   
void pFUN_mCAN_MB_16_31_Hook(stc_CAN_RxFIFO *tCanBuf) 
{
	uint8 i;
	uint32 TxCanId;

	for (i=0;i<CANIF_MAX_TXPDUHANDLE;i++) 
	{
		if(CanIf_TxPduConfig[i].CanIdType == STANDARD_CAN)
		{
			TxCanId = tCanBuf->ID.Bits.STD_ID;
		}
		else
		{
			TxCanId = tCanBuf->ID.Word;
		}
      
		if (TxCanId==CanIf_TxPduConfig[i].CanId) 
		{
			CanIf_TxConfirmation(i);     /*CAN L-PDU ID was found*/
			break;
		}
		else
		{

		}
   	}
}


/*********************************************** END *******************************************************/
