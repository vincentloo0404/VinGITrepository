/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dcm_Types.h  
*
* @brief  Types definition for DCM module.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/20    CODER1     N/A           Original
*     
*******************************************************************************/

#ifndef _DCM_TYPES_H_
#define _DCM_TYPES_H_

/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/  
#include "Platform_Types.h"

/**************************************************************************************************
* Macros and Tyedef
**************************************************************************************************/
typedef uint8 Dcm_StatusType;
typedef uint8 Dcm_SecLevelType;
typedef uint8 Dcm_SesCtrlType;
typedef uint8 Dcm_ProtocolType;
typedef uint8 Dcm_NegativeResponseCodeType;
typedef uint8 Dcm_CommunicationModeType;
typedef struct
{
    Dcm_ProtocolType protocolType;
}Dcm_ConfigType;  /* Need change */
typedef uint8 Dcm_ConfirmationStatusType;
typedef uint8 Dcm_OpStatusType;
typedef uint8 Dcm_ReturnReadMemoryType;
typedef uint8 Dcm_ReturnWriteMemoryType;
typedef uint8 Dcm_RoeStateType;
typedef uint8 Dcm_EcuStartModeType;
typedef struct
{
    uint8 ProtocolId; 
    uint8 TesterSourceAddr;
    uint8 Sid;
    uint8 SubFncId;
    Dcm_EcuStartModeType EcuStartMode;
}Dcm_ProgConditionsType;

typedef uint8 Dcm_MsgItemType;
typedef Dcm_MsgItemType *Dcm_MsgType;
typedef uint32 Dcm_MsgLenType;
typedef struct
{
    uint8 reqType; /* 0=physical request; 1=functional request */
    uint8 suppressPosResponse;/* 0=no; 1=yes;*/ /*0 non-disable positive response;1 disable positive response;*/
    uint8 cancelOperation;/* 0=no;1=cancel pending operation */
}Dcm_MsgAddInfoType;


typedef uint8 Dcm_IdContextType;


typedef struct 
{
    Dcm_MsgType reqData;  /*request data*/
    Dcm_MsgLenType reqDataLen;
    Dcm_MsgType resData;  /*response data*/
    Dcm_MsgLenType resDataLen;
    Dcm_MsgAddInfoType msgAddInfo; /*addressing mode*/
    Dcm_MsgLenType resMaxDataLen;
    Dcm_IdContextType idContext; /*request or response service-ID, reserved.*/
    PduIdType dcmRxPduId;   /*Msg ID*/
}Dcm_MsgContextType;


typedef uint8 Dcm_ResetModeType;

/* Dcm_StatusType */
#define DCM_E_OK                             0x00
#define DCM_E_COMPARE_KEY_FAILED             0x01
#define DCM_E_TI_PREPARE_LIMITS              0x02
#define DCM_E_TI_PREPARE_INCONSTENT          0x03
#define DCM_E_SESSION_NOT_ALLOWED            0x04
#define DCM_E_PROTOCOL_NOT_ALLOWED           0x05
#define DCM_E_ROE_NOT_ACCEPTED               0x06
#define DCM_E_PERIODICID_NOT_ACCEPTED        0x07
#define DCM_E_REQUEST_NOT_ACCEPTED           0x08
#define DCM_E_REQUEST_ENV_NOK                0x09
/* Dcm_ProtocolType */
#define DCM_OBD_ON_CAN                       0x00
#define DCM_OBD_ON_FLEXRAY                   0x01
#define DCM_OBD_ON_IP                        0x02
#define DCM_UDS_ON_CAN                       0x03
#define DCM_UDS_ON_FLEXRAY                   0x04
#define DCM_UDS_ON_IP                        0x05
#define DCM_ROE_ON_CAN                       0x06 
#define DCM_ROE_ON_FLEXRAY                   0x07
#define DCM_ROE_ON_IP                        0x08
#define DCM_PERIODICTRANS_ON_CAN             0x09
#define DCM_PERIODICTRANS_ON_FLEXRAY         0x0A
#define DCM_PERIODICTRANS_ON_IP              0x0B
/* Dcm_SesCtrlType */
#define DCM_DEFAULT_SESSION                  0x01
#define DCM_PROGRAMMING_SESSION              0x02
#define DCM_EXTENDED_DIAGNOSTIC_SESSION      0x03
#define DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION 0x04
/* Dcm_SecLevelType */
#define DCM_SEC_LEV_LOCK 0x00 /*do not need security access*/
#define DCM_SEC_LEV_L1   0x01 /*usually used*/
#define DCM_SEC_LEV_L2   0x02 
#define DCM_SEC_LEV_L3   0x03 
#define DCM_SEC_LEV_ALL  0xff
/* Dcm_NegativeResponseCodeType */
#define DCM_E_POSITIVERESPONSE                         0x00
#define DCM_E_GENERALREJECT                            0x10
#define DCM_E_SERVICENOTSUPPORTED                      0x11
#define DCM_E_SUBFUNCTIONNOTSUPPORTED                  0x12
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT    0x13
#define DCM_E_BUSYREPEATREQUEST                        0x21
#define DCM_E_CONDITIONSNOTCORRECT                     0x22
#define DCM_E_REQUESTSEQUENCEERROR                     0x24
#define DCM_E_REQUESTOUTOFRANGE                        0x31
#define DCM_E_SECURITYACCESSDENIED                     0x33
#define DCM_E_INVALIDKEY                               0x35
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                   0x36
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED              0x37
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED                0x70
#define DCM_E_TRANSFERDATASUSPENDED                    0x71
#define DCM_E_GENERALPROGRAMMINGFAILURE                0x72
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER                0x73
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING 0x78
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION   0x7E
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION       0x7F
#define DCM_E_RPMTOOHIGH                               0x81
#define DCM_E_RPMTOOLOW                                0x82
#define DCM_E_ENGINEISRUNNING                          0x83
#define DCM_E_ENGINEISNOTRUNNING                       0x84
#define DCM_E_ENGINERUNTIMETOOLOW                      0x85
#define DCM_E_TEMPERATURETOOHIGH                       0x86
#define DCM_E_TEMPERATURETOOLOW                        0x87
#define DCM_E_VEHICLESPEEDTOOHIGH                      0x88
#define DCM_E_VEHICLESPEEDTOOLOW                       0x89
#define DCM_E_THROTTLE_PEDALTOOHIGH                    0x8A
#define DCM_E_THROTTLE_PEDALTOOLOW                     0x8B
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL            0x8C
#define DCM_E_TRANSMISSIONRANGENOTINGEAR               0x8D
#define DCM_E_BRAKESWITCH_NOTCLOSED                    0x8F
#define DCM_E_SHIFTERLEVERNOTINPARK                    0x90
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED              0x91
#define DCM_E_VOLTAGETOOHIGH                           0x92
#define DCM_E_VOLTAGETOOLOW                            0x93
/* Dcm_CommunicationModeType */
#define DCM_ENABLE_RX_TX_NORM            0x00
#define DCM_ENABLE_RX_DISABLE_TX_NORM    0x01
#define DCM_DISABLE_RX_ENABLE_TX_NORM    0x02
#define DCM_DISABLE_RX_TX_NORMAL         0x03
#define DCM_ENABLE_RX_TX_NM              0x04
#define DCM_ENABLE_RX_DISABLE_TX_NM      0x05
#define DCM_DISABLE_RX_ENABLE_TX_NM      0x06
#define DCM_DISABLE_RX_TX_NM             0x07
#define DCM_ENABLE_RX_TX_NORM_NM         0x08
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM 0x09
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM 0x0A
#define DCM_DISABLE_RX_TX_NORM_NM        0x0B
/* Dcm_ConfirmationStatusType */
#define DCM_RES_POS_OK     0x00
#define DCM_RES_POS_NOT_OK 0x01
#define DCM_RES_NEG_OK     0x02
#define DCM_RES_NEG_NOT_OK 0x03
/* Dcm_OpStatusType */
#define DCM_INITIAL        0x00
#define DCM_PENDING        0x01
#define DCM_CANCEL         0x02
#define DCM_FORCE_RCRRP_OK 0x03
/* Dcm_ReturnReadMemoryType */
#define DCM_READ_OK        0x00
#define DCM_READ_PENDIN    0x01
#define DCM_READ_FAILED    0x02
/* Dcm_ReturnWriteMemoryType */
#define DCM_WRITE_OK       0x00
#define DCM_WRITE_PENDIN   0x01
#define DCM_WRITE_FAILED   0x02
/* Dcm_RoeStateType */
#define DCM_ROE_ACTIVE     0x00
#define DCM_ROE_UNACTIV    0x01
/* Dcm_EcuStartModeType */
#define DCM_COLD_START     0x00
#define DCM_WARM_START     0x01
/* Dcm_ResetModeType */
#define DCM_NO_RESET                            0x00
#define DCM_HARD_RESET                          0x01
#define DCM_KEY_ON_OFF_RESET                    0x02
#define DCM_SOFT_RESET                          0x03
#define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET   0x04
#define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET  0x05
#define DCM_BOOTLOADER_RESET                    0x06
#define DCM_SS_BOOTLOADER_RESET                 0x07
#define DCM_RESET_EXECUTION                     0x08


#endif

/******************************************************* End  ******************************************************/
