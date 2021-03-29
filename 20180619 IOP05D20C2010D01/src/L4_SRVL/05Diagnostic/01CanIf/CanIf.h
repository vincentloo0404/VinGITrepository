/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanIf.h  
*
* @brief  Head file,interface for CanDrv and CanTp.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date           Author         CR#          Descriptions
*   ---------   ----------    ------------  ----------    ---------------
*     1.0       2013/03/26      CODER1       N/A            Original
*     
*******************************************************************************/

#ifndef CANIF_H
#define CANIF_H

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/

#include "UDS_ComStack_Types.h"
#include "CanIf_Cfg.h"

/* Version of CAN Interface module */
#define CANIF_SW_MAJOR_VERSION            0x01
#define CANIF_SW_MINOR_VERSION            0x00
#define CANIF_SW_PATCH_VERSION            0x00

/* Autosar release version */
#define CANIF_AR_MAJOR_VERSION            0x04
#define CANIF_AR_MINOR_VERSION            0x00
#define CANIF_AR_PATCH_VERSION            0x00


/*******************************************************************************
* Global data types and structures
********************************************************************************/
/* -----------------------------------------------------------------------------
    &&&~Gloable Data types
 ----------------------------------------------------------------------------- */
typedef enum
{
    STANDARD_CAN=0,                                 /*STANDARD CAN Type*/
    EXTENDED_CAN=1                                  /*EXTENDED CAN Type*/
}CanIfTxPduCanIdType;


typedef struct sCanIf_RxPduConfigType
{
  Can_IdType                      CanId;             /*Can_IdType Pdu ID defined by upper layer */
  uint8                           CanIdType;         /*CANIF RX ID TYPE*/  
} CanIf_RxPduConfigType;


typedef struct sCanIf_TxPduConfigType
{
  Can_IdType                      CanId;           /* Can_IdType 16 bit / 32 bit */
  uint8                           CanIdType;       /* CANIF TXPDU ID TYPE      */
  uint8                           Controller;      /* Controller / Channel     */
  uint8                           Hth;             /* Hardware transmit handle */
  uint8                           Length;          /* DLC                      */
  uint8                           TxConfirmation;  /* confirmation function    */
} CanIf_TxPduConfigType;



/* -----------------------------------------------------------------------------
    &&&~Gloable Data definitions
 ----------------------------------------------------------------------------- */

extern ROM_CONST CanIf_RxPduConfigType CanIf_RxPduIdConfig[CANIF_MAX_RXPDUHANDLE]; 
extern ROM_CONST CanIf_TxPduConfigType CanIf_TxPduConfig[CANIF_MAX_TXPDUHANDLE];

/*******************************************************************************
** Prototypes of export functions
********************************************************************************/
/* AUTOSAR CanTp API */
extern void dDiag_vCanIfInit(void);
extern Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType* PduInfoPtr);

#if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
extern Std_ReturnType CanIf_CancelTransmit(PduIdType CanTxPduId);
#endif

#endif

/***************************************************** End ********************************************************/