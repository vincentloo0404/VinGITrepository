/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm_Cbk.h  
*
* @brief  Head file
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

#ifndef _DCM_CBK_H_
#define _DCM_CBK_H_

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/ 
#include "Dcm.h"

/**************************************************************************************************
*                                    Global Function Prototype
**************************************************************************************************/
extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_StartOfReception
(
    PduIdType     DcmRxPduId,
    PduLengthType TpSduLength,
    PduLengthType *Length
);

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyRxData
(
    PduIdType      DcmRxPduId,
    P2VAR(PduInfoType,AUTOMATIC,DCM_APPL_DATA) PduInfoPointer,
    P2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA) RxBufferSizePtr
);

extern FUNC(void,DCM_CODE) Dcm_RxIndication
(
    PduIdType       DcmRxPduId,
    NotifResultType Result
);

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyTxData
(
    PduIdType      DcmTxPduId,
    P2VAR(PduInfoType,AUTOMATIC,DCM_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType,AUTOMATIC,DCM_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA) TxDataCntPtr
);

extern FUNC(void,DCM_CODE) Dcm_TxConfirmation
(
   PduIdType       DcmTxPduId,
   NotifResultType Result
);


#endif

/*******************************************************  End  ******************************************************/
