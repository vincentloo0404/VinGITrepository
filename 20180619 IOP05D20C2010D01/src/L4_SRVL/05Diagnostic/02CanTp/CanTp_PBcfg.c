/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanTp_PBcfg.h  (AUTOSAR)
*
* @brief  config file for link.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26     CODER1       N/A           Original
*     
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "CanTp.h"
#include "CanTp_Cfg.h"


/* -----------------------------------------------------------------------------
    &&~ CanTp Overall (ROM)
 ----------------------------------------------------------------------------- */
/* Struct to hold the complete CanTp-configuration */

ROM_CONST CanTp_RxNsduCfgType CanTp_RxNsduCfg[];
ROM_CONST CanTp_TxNsduCfgType CanTp_TxNsduCfg[];
ROM_CONST CanTp_RxPduMapType CanTp_RxPduMap[];
ROM_CONST CanTp_CfgType CanTp_Cfg = 
{
    CanTp_RxNsduCfg /* Pointer to RxNsdu-cfg-table */, 
    CanTp_TxNsduCfg /* Pointer to TxNsdu-cfg-table */, 
    CanTp_RxPduMap /* Extended SDU indirection table */,  
    2 /*  NumCanTpRxSduId */,
    1 /*  NumCanTpTxSduId */,   
};



/* -----------------------------------------------------------------------------
    &&~ RxNsdu (ROM)
 ----------------------------------------------------------------------------- */

ROM_CONST CanTp_RxNsduCfgType CanTp_RxNsduCfg[] = 
{
  /*Channel 0:Functional & Standars addressing*/
    {
        0 /* CANTP_RXNSDU_ID; to    PduR */, 
        0 /* CANTP_RXNPDU_ID; from  CanIf */, 
        0  /* CANTP_TXFC_NPDU_ID; to CanIf */, 
        1 /* CANTP_DL */, 
        70 /* CANTP_NAR */, 
        60 /* CANTP_NBR (N_Br+N_Ar) < 0.9*N_Bs*/, 
        150 /* CANTP_NCR */, 
        CANTP_ON /* CANTP_PADDING_ACTIVATION */, 
        CANTP_PHYSICAL /* CANTP_TA_TYPE */, 
        CANTP_STANDARD /* CANTP_ADDRESSING_FORMAT */,  
        0 /* CANTP_BS */, 
        10 /* CANTP_STMIN */, 
        0 /* CANTP_WFTMAX */, 
        CANTP_UNUSED /* CANTP_RX_NAE */,
        CANTP_UNUSED /* CANTP_RX_NSA */, 
        CANTP_UNUSED /* CANTP_RX_NTA */, 
    } /* Channel 0 */, 
  /*Channel 1:Phsical & Standars addressing*/
    { 
        1 /* CANTP_RXNSDU_ID; to    PduR */, 
        1 /* CANTP_RXNPDU_ID; from  CanIf */, 
        CANTP_UNUSED /* CANTP_TXFC_NPDU_ID; to CanIf */, 
        1 /* CANTP_DL */, 
        70 /* CANTP_NAR */, 
        60 /* CANTP_NBR */, 
        150 /* CANTP_NCR */,    
        CANTP_ON /* CANTP_PADDING_ACTIVATION */, 
        CANTP_FUNCTIONAL /* CANTP_TA_TYPE */, 
        CANTP_STANDARD /* CANTP_ADDRESSING_FORMAT */, 
        0 /* CANTP_BS */, 
        10 /* CANTP_STMIN */, 
        0 /* CANTP_WFTMAX */, 
        CANTP_UNUSED /* CANTP_RX_NAE */,
        CANTP_UNUSED /* CANTP_RX_NSA */, 
        CANTP_UNUSED /* CANTP_RX_NTA */, 
    }, /* Channel 1 */
};




/* -----------------------------------------------------------------------------
    &&~ TxNsdu (ROM)
 ----------------------------------------------------------------------------- */

ROM_CONST CanTp_TxNsduCfgType CanTp_TxNsduCfg[] = 
{
  /*Channel 0:Phsical & Standars addressing,maped Rx channel:0&1*/
    {
        0 /* CANTP_TXNSDU_ID;  from PduR */, 
        0 /* CANTP_TXNPDU_ID; to CanIf */, 
        0 /* CANTP_RXFC_NPDU_ID; from CanIf */,
        1 /* CANTP_DL */, 
        25 /* CANTP_NAS */, 
        75 /* CANTP_NBS */, 
        10 /* CANTP_NCS */,  
        CANTP_ON /* CANTP_PADDING_ACTIVATION */, 
        CANTP_PHYSICAL /* CANTP_TA_TYPE */, 
        CANTP_STANDARD /* CANTP_ADDRESSING_FORMAT */,  
        CANTP_UNUSED /* CANTP_TX_NAE */,
        CANTP_UNUSED /* CANTP_TX_NSA */, 
        CANTP_UNUSED /* CANTP_TX_NTA */, 
    }, /* Channel 0 */
};




/* -----------------------------------------------------------------------------
    &&~ RxPdu mapping table
 ----------------------------------------------------------------------------- */

ROM_CONST CanTp_RxPduMapType CanTp_RxPduMap[] = 
{
    {
        0,  /*RxSduIdx*/
        0   /*TxSduIdx*/
    }, 
  
    {
        1,  /*RxSduIdx*/
        0   /*TxSduIdx*/
    },
};

/***************************************************** End *******************************************************/
