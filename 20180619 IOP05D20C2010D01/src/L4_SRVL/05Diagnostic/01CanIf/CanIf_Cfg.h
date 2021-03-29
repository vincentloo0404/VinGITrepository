
/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanIf_Cfg.h  
*
* @brief  Head file,Config file for CanIf moudule.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26    CODER1       N/A            Original
*     
*******************************************************************************/
/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/
#if !defined(CANIF_CFG_H)
#define CANIF_CFG_H
#define ACCESS_CANDRV_MODULE
#define ACCESS_ALL_MODULE
#include 	"m_CAN_Cfg.h"
#undef ACCESS_ALL_MODULE
#undef ACCESS_CANDRV_MODULE

/*-----------------------------------------------------------------------------
 && Config Items
 -----------------------------------------------------------------------------*/
#define CANIF_TRANSMIT_CANCELLATION    STD_ON  /*means can cancel the transmission for requesting*/
#define CANIF_MAX_RXPDUHANDLE          2       /*max number request CANID handle*/
#define CANIF_MAX_TXPDUHANDLE          1       /*max number response CANID handle*/
#define CANTP_CAN_CHANNELS             1       /*must 1, CanTp only supportted one CAN channel at the same time*/

#endif                                 /* CANIF_CFG_H */


/***************************************************** End ********************************************************/