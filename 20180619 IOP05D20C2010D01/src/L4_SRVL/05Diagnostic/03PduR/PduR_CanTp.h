/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   PduR_CanTp.h  (AUTOSAR)
*
* @brief  Pdu transmission callback for CanTp module.
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
#if !defined(PDUR_CANTP_H)
#define PDUR_CANTP_H

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "UDS_ComStack_Types.h"
#include "PduR_Cfg.h"

/*********************************************************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )                                                  */
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/* API declaration                                                                                                   */
/*********************************************************************************************************************/
#if(PDUR_CANTP_SUPPORT == STD_ON)

/*===========================================PDUR_START_SEC_CODE=====================================================*/
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
                                      );
/**********************************************************************************************************************
| NAME:             PduR_CanTpCopyRxData
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR350 for a complete API description
**********************************************************************************************************************/


FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData
                                      (
                                        PduIdType id,
                                        PduInfoType* info,
                                        PduLengthType* bufferSizePtr
                                      );
/**********************************************************************************************************************
| NAME:             PduR_CanTpRxIndication
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR353 for a complete API description
**********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpRxIndication(PduIdType CanTpRxPduId, NotifResultType Result);



/**********************************************************************************************************************
| NAME:             PduR_CanTpCopyTxData
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR356 for a complete API description
**********************************************************************************************************************/


FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData
                                      (
                                        PduIdType id,
                                        PduInfoType* info,
                                        RetryInfoType* retry,
                                        PduLengthType* availableDataPtr
                                      );
/**********************************************************************************************************************
| NAME:             PduR_CanTpTxConfirmation
| CALLED BY:        CAN Transport Protocol
| DESCRIPTION:      See PDUR359 for a complete API description
**********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation (PduIdType CanTpTxPduId, NotifResultType Result);


#endif

#endif /* !defined(PDUR_CANTP_H) */

/***************************************************** End *******************************************************/
