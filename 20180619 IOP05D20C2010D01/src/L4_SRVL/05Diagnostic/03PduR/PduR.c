/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   PduR.c  (AUTOSAR)
*
* @brief  Pdu transmission router.
*
*******************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26     CODER1      N/A           Original
*     
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "PduR.h"
#include "PduR_Cfg.h"
#include "PduR_CanTp.h"
#include "PduR_Dcm.h"
#include "Dcm_Cbk.h"
#include "CanTp.h"

 /* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name: PduR_CanTpStartOfReception
* Description:   be called to starting receive SDU message;
*
* Inputs:id,TpSduLength,bufferSizePtr
*
* Outputs: None
*
* Limitations: None

********************************************************************
 END_FUNCTION_HDR*/

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception
                                      (
                                        PduIdType id,
                                        PduLengthType TpSduLength,
                                        PduLengthType* bufferSizePtr
                                      )
{
    BufReq_ReturnType result=BUFREQ_OK;
    result=Dcm_StartOfReception(id,TpSduLength,bufferSizePtr);
    return result;
}


/********************************************************************************************************************
| NAME:             PduR_CanTpCopyRxData
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR350 for a complete API description
********************************************************************************************************************/

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData
                                      (
                                        PduIdType id,
                                        PduInfoType* info,
                                        PduLengthType* bufferSizePtr
                                      )
{
     BufReq_ReturnType result=BUFREQ_OK;
     result=Dcm_CopyRxData(id,info,bufferSizePtr);
     return result;
}


/*******************************************************************************************************************
| NAME:             PduR_CanTpRxIndication
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR353 for a complete API description
*******************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpRxIndication(PduIdType CanTpRxPduId, NotifResultType Result)
{
    Dcm_RxIndication(CanTpRxPduId, Result);
    /*CanTp_ChannelInit(CANTP_RX_CHANNEL,CanTpRxPduId);*//* JMC dele, add into Dcm_TxConfirmation */
}


/******************************************************************************************************************
| NAME:             PduR_CanTpProvideTxBuffer
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR356 for a complete API description
*******************************************************************************************************************/

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData
                                      (
                                        PduIdType id,
                                        PduInfoType* info,
                                        RetryInfoType* retry,
                                        PduLengthType* availableDataPtr
                                      )
{
     BufReq_ReturnType result=BUFREQ_OK;
     result=Dcm_CopyTxData(id,info,retry, availableDataPtr);
     return result;   /*Buffer request accomplished successful.*/

}


/*****************************************************************************************************************
| NAME:             PduR_CanTpTxConfirmation
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR359 for a complete API description
******************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation (PduIdType CanTpTxPduId, NotifResultType Result)
{
    Dcm_TxConfirmation(CanTpTxPduId,Result);
    /*CanTp_ChannelInit(CANTP_TX_CHANNEL,CanTpTxPduId);*/ /* JMC dele, add into Dcm_TxConfirmation */
}



/*****************************************************************************************************************
| NAME:             PduR_DcmTransmit
| CALLED BY:        DCM
| DESCRIPTION:      See PDUR408 for a complete API description
*****************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit( PduIdType DcmTxPduId,PduInfoType* PduInfoPtr)
{
     Std_ReturnType result=E_OK;
     result=CanTp_Transmit(DcmTxPduId, PduInfoPtr);
     return result;
}

/***************************************************** End *******************************************************/
