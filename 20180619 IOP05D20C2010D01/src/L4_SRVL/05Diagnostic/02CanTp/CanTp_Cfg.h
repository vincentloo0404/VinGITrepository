/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanTp_Cfg.h  
*
* @brief  config file.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26     CODER1       N/A           Original
*     
*******************************************************************************/

#if !defined(CANTP_CFG_H)
#define CANTP_CFG_H

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "PduR_CanTp.h"
#include "CanIf.h"


/**************************************************************************************************
 * Global defines
 **************************************************************************************************/
/*-----------------------------------------------------------------------------
   && CanTpGeneral{CanTpConfiguration}
 -----------------------------------------------------------------------------*/
#define CANTP_VERSION_INFO_API         STD_ON
#define CANTP_DEV_ERROR_DETECT         STD_OFF
#define CANTP_PROD_ERROR_DETECT        STD_OFF
#define CANTP_TC                       STD_ON
#define CANTP_MAIN_FUNCTION_PERIOD     5      /* tp call cycle: 5ms */


/*-----------------------------------------------------------------------------
   && CanTpChannel
----------------------------------------------------------------------------- */
#define CANTP_CHANNEL_MODE             CANTP_MODE_HALF_DUPLEX    /*CANTP_MODE_FULL_DUPLEX*/
//#define CANTP_CHANNEL_MODE             CANTP_MODE_FULL_DUPLEX    /*CANTP_MODE_FULL_DUPLEX*/ // modify by ych at 20180621 for test
#define CANTP_FILLPATTERN              0x55u


/*-----------------------------------------------------------------------------
   && Maximum number of SDUs supported by the CanTp on this ECU
----------------------------------------------------------------------------- */
#define CANTP_NUM_RX_CHANNELS          2
#define CANTP_NUM_TX_CHANNELS          1
#define CANTP_CAN_CHANNELS             1
#define CanTp_CanInterruptDisable()                             
#define CanTp_CanInterruptRestore()                             

/**************************************************************************************************
 * Global Marco Functions
 **************************************************************************************************/
 
#define CanTp_CanTransmit(txSduIdx,pduInfo) CanIf_Transmit(txSduIdx,pduInfo)

/*
 * Description : The network layer use  the service function that is provided by the lower layer to transmit N-PDU.
 *******************************************************************************/
 
 
 
#define CanTp_CanCancelTransmit(txSduIdx) CanIf_CancelTransmit(txSduIdx)

/*
 * Description : The network layer use  the service function that is provided by the lower layer to cancle transmit N-PDU.
 *******************************************************************************/
 
 
#define CanTp_NUSDataIndication(rxSduIdx,canTpErrorCode) PduR_CanTpRxIndication(rxSduIdx,canTpErrorCode)/* -- Not used -- */

/*
 * Description : This service is used by the network layer to pass status information and received data to
   upper communication layers or the application;
 *******************************************************************************/
 
 
#define CanTp_NUSDataConfirm(txSduIdx,canTpErrorCode) PduR_CanTpTxConfirmation(txSduIdx,canTpErrorCode)/* -- -*/

/*
 * Description : This service is used by the network layer to pass status information to higher
   communication layers or the application.
 *******************************************************************************/
 
 
#define CanTp_NUSDataFFIndication(rxSduIdx,length,bufferSizePtr) PduR_CanTpStartOfReception(rxSduIdx,length,bufferSizePtr)

/*
 * Description : This service is used to signal the beginning of a segmented message reception to the upper layer.
 *******************************************************************************/
 
 
#define CanTp_NUSDataSFIndication(rxSduIdx,length,bufferSizePtr) PduR_CanTpStartOfReception(rxSduIdx,length,bufferSizePtr)

/*
 * Description : This service is used to signal the beginning of a segmented message reception to the upper layer.
 *******************************************************************************/
 
 
#define CanTp_CopyRxData(rxSduIdx,pduInfo,bufferSizePtr) PduR_CanTpCopyRxData(rxSduIdx,pduInfo,bufferSizePtr)

/*
 * Description : The network layer use  the  function that is provided by the upper layer
   to copy data of received N-PDU to buffer provided by the upper layer .
 *******************************************************************************/
 
 
#define CanTp_CopyTxData(txSduIdx,pduInfo,NULL_PTR,bufferSizePtr) PduR_CanTpCopyTxData(txSduIdx,pduInfo,NULL_PTR,bufferSizePtr)

/*
 * Description : The network layer use  the  function that is provided by the upper layer
   to copy data of transmitted N-PDU from buffer provided by the upper layer  to network layer.
 *******************************************************************************/
 
/**************************************************************************************************
 * Global data types and structures
 **************************************************************************************************/
/**************************************************************************************************
 * Gloable Data definitions
 **************************************************************************************************/
#endif                                 /* CANTP_CFG_H */

/************************************************************ End ***************************************************************/
