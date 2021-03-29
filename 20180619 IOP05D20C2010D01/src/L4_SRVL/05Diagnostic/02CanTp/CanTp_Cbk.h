/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanTp_Cbk.h  (AUTOSAR)
*
* @brief  callback function definition.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26     CODER1       N/A           Original
*     
*******************************************************************************/
#ifndef _CANTP_CBK_H_
#define _CANTP_CBK_H_


/*************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
extern void CanTp_RxIndication(PduIdType CanTpRxPduId, const PduInfoType* pCanTpRxPduPtr);
extern void CanTp_TxConfirmation(PduIdType CanIfTxPduId);


#endif
/* ifndef _CANTP_CBK_H_ */

/********************************************** End ************************************************/
