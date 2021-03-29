/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanIf_Cbk.h  
*
* @brief  Head file, callback function file.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26    CODER1       N/A            Original
*     
*******************************************************************************/
#ifndef CANIF_CBK_H
#define CANIF_CBK_H

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "UDS_ComStack_Types.h"
#include "CanIf.h"


/* Tx Confirmation */
extern void CanIf_TxConfirmation(PduIdType CanTxPduId); 
/* Rx Indication  */
extern void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc,const uint8* CanSduPtr); 

/* Cancel notification */
# if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
extern Std_ReturnType CanIf_CancelTransmit(PduIdType CanTxPduId);
# endif


#endif

/***************************************************** End ********************************************************/
