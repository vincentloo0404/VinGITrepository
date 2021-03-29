/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanTp.h  
*
* @brief  UDS transport layer protocol.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26    CODER1       N/A           Original
*     
*******************************************************************************/

#ifndef CANTP_H
#define CANTP_H

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/

#include "UDS_ComStack_Types.h"
#include "CanTp_Cfg.h"

/******************************************************************************
** Macros
*******************************************************************************/
#define CANTP_VENDOR_ID             (uint16)(0xFFFFu)  /*Supplier ID */
#define CANTP_MODULE_ID             (uint16)(0x0023u)  /*CanTp Moudle ID */

/*-------------------------------------------------------------------------*/
/**                  CanTp Component release Version                                                      
/*-------------------------------------------------------------------------*/
#define CANTP_SW_MAJOR_VERSION      (uint8)(0x01u)
#define CANTP_SW_MINOR_VERSION      (uint8)(0x00u)
#define CANTP_SW_PATCH_VERSION      (uint8)(0x00u)

/*-------------------------------------------------------------------------*/
/**                  Autosar release version                                                     
/*-------------------------------------------------------------------------*/
#define CANTP_AR_MAJOR_VERSION      (uint8)(0x04u)
#define CANTP_AR_MINOR_VERSION      (uint8)(0x00u)
#define CANTP_AR_PATCH_VERSION      (uint8)(0x00u)

/* Internal and iso 15765-2 compliant */
/*-------------------------------------------------------------------------*/
/**                        CanTp_FrameType                                                    
/*-------------------------------------------------------------------------*/
#define cCanTp_SF                   (uint8)0x00
#define cCanTp_FF                   (uint8)0x10
#define cCanTp_CF                   (uint8)0x20
#define cCanTp_FC                   (uint8)0x30
#define cCanTp_FC_FS_CTS            (uint8)0x00
#define cCanTp_FC_FS_Wait           (uint8)0x01
#define cCanTp_FC_FS_Overrun        (uint8)0x02

/*-------------------------------------------------------------------------*/
/**                      Masks for frame parsing                                                    
/*-------------------------------------------------------------------------*/
#define cCanTp_DLMaskSF             (uint8)0x0F
#define cCanTp_DLMaskFF             (uint8)0x0F
#define cCanTp_FrameTypeMask        (uint8)0xF0
#define cCanTp_FSMask               (uint8)0x0F
#define cCanTp_SNMask               (uint8)0x0F
#define cCanTpSNStartValue          (uint8)0x01/* Start value for sequence number counter*/


/******************************************************************************
* Transport protocol global status codes
*******************************************************************************/

/*-------------------------------------------------------------------------*/
/**                      CanTp_RxStateType                                                    
/*-------------------------------------------------------------------------*/
#define cCanTpRxState_Idle                     (uint8)0x00  /* must be zero due to optimization */
#define cCanTpRxState_WaitCF                   (uint8)0x01
#define cCanTpRxState_WaitForTxFC              (uint8)0x02
#define cCanTpRxState_WaitForTxFCOverrun       (uint8)0x03
#define cCanTpRxState_WaitForTxFCWait          (uint8)0x04
#define cCanTpRxState_WaitForRxBuffer          (uint8)0x05
#define cCanTpRxState_Error                    (uint8)0x08
#define cCanTpRxState_WaitForFCConf            (uint8)0x10
#define cCanTpRxState_WaitForFCWaitConf        (uint8)0x20
#define cCanTpRxState_WaitForFCOverConf        (uint8)0x40


/*-------------------------------------------------------------------------*/
/**                      CanTp_TxStateType                                                    
/*-------------------------------------------------------------------------*/
#define cCanTpTxState_Idle                     (uint8)0x00  /* must be zero due to optimization */
#define cCanTpTxState_WaitFC                   (uint8)0x01
#define cCanTpTxState_WaitForTpTxCF            (uint8)0x02
#define cCanTpTxState_Error                    (uint8)0x08
#define cCanTpTxState_WaitForSFConf            (uint8)0x10
#define cCanTpTxState_WaitForFFConf            (uint8)0x20
#define cCanTpTxState_WaitForCFConf            (uint8)0x30
#define cCanTpTxState_WaitForLastCFConf        (uint8)0x40
#define cCanTpState_Retransmit                 (uint8)0x80
#define cCanTpInternalStateMask                (uint8)0x0F
#define cCanTpCanTxStateMask                   (uint8)0x70



/*******************************************************************************
* TP ISO offsets in CAN-frame
*******************************************************************************/
#define TARGET_OFFSET                       (uint8)0
#define AE_OFFSET                           (uint8)0


/***************************************************************************************************
* TP ISO offsets in RX CAN-frame and protocol lengths
****************************************************************************************************/
#define RX_TPCI_OFFSET(CanTpSduId)              (uint8)RxFormatOffset[CanTpSduId]
#define RX_DL_OFFSET(CanTpSduId)                (uint8)(1+RxFormatOffset[CanTpSduId])
#define RX_FF_OFFSET(CanTpSduId)                (uint8)(2+RxFormatOffset[CanTpSduId])
#define RX_SF_OFFSET(CanTpSduId)                (uint8)(1+RxFormatOffset[CanTpSduId])
#define RX_CF_OFFSET(CanTpSduId)                (uint8)(1+RxFormatOffset[CanTpSduId])
#define RX_BS_OFFSET(CanTpSduId)                (uint8)(1+RxFormatOffset[CanTpSduId])
#define RX_STMIN_OFFSET(CanTpSduId)             (uint8)(2+RxFormatOffset[CanTpSduId])
#define RX_SF_DataLength(CanTpSduId)            (uint8)(7-RxFormatOffset[CanTpSduId])
#define RX_FF_DataLength(CanTpSduId)            (uint8)(6-RxFormatOffset[CanTpSduId])
#define RX_FC_DataLength(CanTpSduId)            (uint8)(3+RxFormatOffset[CanTpSduId])
#define RX_CF_DataLength(CanTpSduId)            (uint8)(7-RxFormatOffset[CanTpSduId])


/***************************************************************************************************
*TP ISO offsets in TX CAN-frame and protocol lengths
****************************************************************************************************/
#define TX_TPCI_OFFSET(CanTpSduId)              (uint8)TxFormatOffset[CanTpSduId]
#define TX_DL_OFFSET(CanTpSduId)                (uint8)(1+TxFormatOffset[CanTpSduId])
#define TX_FF_OFFSET(CanTpSduId)                (uint8)(2+TxFormatOffset[CanTpSduId])
#define TX_SF_OFFSET(CanTpSduId)                (uint8)(1+TxFormatOffset[CanTpSduId])
#define TX_CF_OFFSET(CanTpSduId)                (uint8)(1+TxFormatOffset[CanTpSduId])
#define TX_BS_OFFSET(CanTpSduId)                (uint8)(1+TxFormatOffset[CanTpSduId])
#define TX_STMIN_OFFSET(CanTpSduId)             (uint8)(2+TxFormatOffset[CanTpSduId])
#define TX_SF_DataLength(CanTpSduId)            (uint8)(7-TxFormatOffset[CanTpSduId])
#define TX_FF_DataLength(CanTpSduId)            (uint8)(6-TxFormatOffset[CanTpSduId])
#define TX_FC_DataLength(CanTpSduId)            (uint8)(3+TxFormatOffset[CanTpSduId])
#define TX_CF_DataLength(CanTpSduId)            (uint8)(7-TxFormatOffset[CanTpSduId])


/***************************************************************************************************
* CanTpRxNSdu{RxNsdu}
****************************************************************************************************/
#define CANTP_RXNSDU_ID(CanTpSduId)             CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxNSduId
#define CANTP_RXNPDU_ID(CanTpSduId)             CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxNPduId
#define CANTP_TXFC_NPDU_ID(CanTpSduId)          CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpTxFcNPduId
#define CANTP_RX_DL(CanTpSduId)                 CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxDl
#define CANTP_NAR(CanTpSduId)                   (uint16)(CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpNar/CANTP_MAIN_FUNCTION_PERIOD)
#define CANTP_NBR(CanTpSduId)                   (uint16)(CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpNbr/CANTP_MAIN_FUNCTION_PERIOD)
#define CANTP_NCR(CanTpSduId)                   (uint16)(CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpNcr/CANTP_MAIN_FUNCTION_PERIOD)
#define CANTP_RX_PADDING_ACTIVATION(CanTpSduId) CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxPaddingActive
#define CANTP_RX_TA_TYPE(CanTpSduId)            CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxTaType
#define CANTP_RX_ADDRESSING_FORMAT(CanTpSduId)  CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxAddrFormat
#define CANTP_BS(CanTpSduId)                    CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpBs
#define CANTP_STMIN(CanTpSduId)                 CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpSTmin
#define CANTP_WFTMAX(CanTpSduId)                CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxWftMax
#define CANTP_RX_NAE(CanTpSduId)                CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxNAe
#define CANTP_RX_NSA(CanTpSduId)                CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxNSa
#define CANTP_RX_NTA(CanTpSduId)                CanTp_Cfg.CanTp_RxNsduCfg[CanTpSduId].CanTpRxNTa


/****************************************************************************************************
* CanTpTxNSdu{TxNsdu}
*****************************************************************************************************/
#define CANTP_TXNSDU_ID(CanTpSduId)             CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxNSduId
#define CANTP_TXNPDU_ID(CanTpSduId)             CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxNPduId
#define CANTP_RXFC_NPDU_ID(CanTpSduId)          CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpRxFcNPduId
#define CANTP_TX_DL(CanTpSduId)                 CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxDl
#define CANTP_NAS(CanTpSduId)                   (uint16)(CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpNas/CANTP_MAIN_FUNCTION_PERIOD)
#define CANTP_NBS(CanTpSduId)                   (uint16)(CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpNbs/CANTP_MAIN_FUNCTION_PERIOD)
#define CANTP_NCS(CanTpSduId)                   (uint16)(CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpNcs/CANTP_MAIN_FUNCTION_PERIOD)
#define CANTP_TX_PADDING_ACTIVATION(CanTpSduId) CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxPaddingActive
#define CANTP_TX_TA_TYPE(CanTpSduId)            CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxTaType
#define CANTP_TX_ADDRESSING_FORMAT(CanTpSduId)  CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxAddrFormat
#define CANTP_TX_NAE(CanTpSduId)                CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxNAe
#define CANTP_TX_NSA(CanTpSduId)                CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxNSa
#define CANTP_TX_NTA(CanTpSduId)                CanTp_Cfg.CanTp_TxNsduCfg[CanTpSduId].CanTpTxNTa


/****************************************************************************************************
* RxPdu mapping
*****************************************************************************************************/
#define RX_TO_TX_CHANNEL(CanTpSduId)      CanTp_Cfg.CanTp_RxPduMap[CanTpSduId].TxSduIdx
#define TX_TO_RX_CHANNEL(CanTpSduId)      CanTp_Cfg.CanTp_RxPduMap[CanTpSduId].RxSduIdx


/**************************************************************************************************
* Global defines
**************************************************************************************************/
#define CANTP_MODE_HALF_DUPLEX      0x00
#define CANTP_MODE_FULL_DUPLEX      0x01
/*-------------------------------------------------------------------------*/
/**  Error notification codes specific for the communication system CAN                                              
/*-------------------------------------------------------------------------*/
#define NTFRSLT_E_CAN_WRONG_SFDL               0x1F /* Single frame data length error (DL > possible SF_DL */
#define NTFRSLT_E_CAN_WRONG_FFDL               0x20 /*FF_DL that is less than (eight) 8*/
#define NTFRSLT_E_CAN_WRONG_FFTATYPE           0x21

#define CANTP_MAX_FRAME_LENGTH      0x08u    /* CAN frame max length*/
#define CANTP_UNUSED                0xFFu


/****************************************************************************************************
* Global data types and structures
*****************************************************************************************************/
/* AUTOSAR compliant */
/*-------------------------------------------------------------------------*/
/**                            CanTpInternalState                                              
/*-------------------------------------------------------------------------*/
typedef enum /* CanTpInternalState */
{
  CANTP_OFF = 0,
  CANTP_ON
} CanTpInternalState;


/*-------------------------------------------------------------------------*/
/**                            CanTpChannelType                                              
/*-------------------------------------------------------------------------*/
typedef enum
{
  CANTP_RX_CHANNEL = 0,
  CANTP_TX_CHANNEL
} CanTpChannelType;


/*-------------------------------------------------------------------------*/
/**                            CanTpAddressingFormat                                              
/*-------------------------------------------------------------------------*/
typedef enum
{
  CANTP_STANDARD = 0,
  CANTP_EXTENDED,
  CANTP_MIXED
} CanTpAddressingFormat;


/*-------------------------------------------------------------------------*/
/**                            CanTpTaType                                              
/*-------------------------------------------------------------------------*/
typedef enum
{
  CANTP_PHYSICAL = 0,
  CANTP_FUNCTIONAL
} CanTpTaType;


/*-------------------------------------------------------------------------*/
/**                            CanTpParameterType                                              
/*-------------------------------------------------------------------------*/
typedef enum
{
  CANTP_BS_PARAMETER = 0,
  CANTP_STMIN_PARAMETER
} CanTpParameterType;


/**************************************************************************************
* Types for static-configuration (ROM/Flash)
***************************************************************************************/
/*************
* CanTp (ROM)
*************/

/*-------------------------------------------------------------------------*/
/**                            RxNsdu (ROM)                                              
/*-------------------------------------------------------------------------*/
typedef struct 
{
    PduIdType      CanTpRxNSduId;    /* to PduR  */
    PduIdType      CanTpRxNPduId;    /* from CanIf */
    PduIdType      CanTpTxFcNPduId;  /* to   CanIf */
    uint16         CanTpRxDl;
    uint16         CanTpNar;
    uint16         CanTpNbr;
    uint16         CanTpNcr;
    uint8          CanTpRxPaddingActive;
    uint8          CanTpRxTaType;
    uint8          CanTpRxAddrFormat;
    uint8          CanTpBs;
    uint8          CanTpSTmin;
    uint8          CanTpRxWftMax;
    uint8          CanTpRxNAe;
    uint8          CanTpRxNSa;
    uint8          CanTpRxNTa;
} CanTp_RxNsduCfgType;


/*-------------------------------------------------------------------------*/
/**                            TxNsdu (ROM)                                             
/*-------------------------------------------------------------------------*/
typedef struct 
{
    PduIdType      CanTpTxNSduId;    /* from PduR  */
    PduIdType      CanTpTxNPduId;    /* to   CanIf */
    PduIdType      CanTpRxFcNPduId;  /* from CanIf */
    uint16         CanTpTxDl;
    uint16         CanTpNas;
    uint16         CanTpNbs;
    uint16         CanTpNcs;
    uint8          CanTpTxPaddingActive;
    uint8          CanTpTxTaType;
    uint8          CanTpTxAddrFormat;
    uint8          CanTpTxNAe;
    uint8          CanTpTxNSa;
    uint8          CanTpTxNTa;
} CanTp_TxNsduCfgType;


/*-------------------------------------------------------------------------*/
/**                         RxPdu mapping table                                           
/*-------------------------------------------------------------------------*/
typedef struct 
{
	PduIdType RxSduIdx;
	PduIdType TxSduIdx;
} CanTp_RxPduMapType;


/* ************************************************************************** */
/* CanTp Overall (ROM)                                                        */
/* ************************************************************************** */
/*-------------------------------------------------------------------------*/
/**            Struct to hold the complete CanTp-configuration                                           
/*-------------------------------------------------------------------------*/
typedef struct 
{
    const CanTp_RxNsduCfgType* const CanTp_RxNsduCfg;
    const CanTp_TxNsduCfgType* const CanTp_TxNsduCfg;
    const CanTp_RxPduMapType* const CanTp_RxPduMap;
    PduIdType   NumCanTpRxSduId;  /* Overall maximum num of CanTp Rx Channel*/
    PduIdType   NumCanTpTxSduId;  /* Overall maximum num of CanTp Tx Channel*/
} CanTp_CfgType;


/* ************************************************************************** */
/* External administration data (RAM)                                         */                 
/* ************************************************************************** */
typedef struct
{
    const CanTp_CfgType*    CfgPtr;
    CanTpInternalState      InternalState; /* keep track of the initialization status */
} CanTp_AdminDataType;


/**************************************************************************************************
* Gloable Data definitions
**************************************************************************************************/
extern const CanTp_CfgType CanTp_Cfg;
extern CanTp_AdminDataType CanTp_AdminData;


/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
extern void           CanTp_Init(const void* const pCfgPtr);
extern void           CanTp_ChannelInit(CanTpChannelType tpChannelType,PduIdType tpChannel);
extern void           CanTp_Shutdown(void);
extern void           CanTp_MainFunction(void);
extern Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* pData);
#if (CANTP_TC == STD_ON)
extern Std_ReturnType CanTp_CancelTransmitRequest(PduIdType CanTpTxSduId);
#endif
extern Std_ReturnType CanTp_CancelReceiveRequest(PduIdType CanTpRxSduId);
extern Std_ReturnType CanTp_ChangeParameterRequest(PduIdType CanTpSduId,CanTpParameterType parameter,uint16 value);

#if (CANTP_VERSION_INFO_API == STD_ON)
extern void           CanTp_GetVersionInfo(Std_VersionInfoType* pVersionInfo);
#endif


#endif/* ifndef CANTP_H */

/****************************************************** End *********************************************************/