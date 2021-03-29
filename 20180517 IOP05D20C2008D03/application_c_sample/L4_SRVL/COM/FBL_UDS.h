/******************************************************************************
*
* ChuangQu Tech Inc.
* (c) Copyright 2016 ChuangQu Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     FBL_UDS.h
*
* @brief    Hardware-specific module
*           Provides the CAN-Interface and timer operations
*
************************************************************************************************
*   Revision History:
* 
*    Version       Date          Author         CR#      Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2016/08/26       	YCH         N/A         Original
*     
************************************************************************************************/


#ifndef FBL_UDS_H
#define FBL_UDS_H
#include 	"Common.h"
#include "MPC560xP.h"
#include "m_CAN_Drv.h"
#include "m_CAN_Cfg.h"

/* Special return codes */
#define S_DSM_RC_OK               (0x0100u) /*process ok */   
#define S_DSM_RC_PENDING          (0x0200u) /*The application initiates
                                              a pending response */
#define S_DSM_RC_SNS              (0x0011u) /*serviceNotSupported */
#define S_DSM_RC_SFNS             (0x0012u) /*subFunctionNotSupported */
/*incorrectMessageLengthOrInvalidFormat */
#define S_DSM_RC_IMLOIF           (0x0013u) /*incorrectMessageLength */

#define S_DSM_RC_CNC              (0x0022u) /*conditionsNotCorrect */
#define S_DSM_RC_ROOR             (0x0031u) /*requestOutOfRange */

#define S_DSM_RC_SFNS             (0x0012u) /*subFunctionNotSupported */


#define UPGRADE_RAM_ADDR 0x40000000u
#define UPGRADE_PATTERN 0x12344321u

void s_dsmco_PHYS_service(uint8* data);
void s_dsmco_FUNC_service(uint8* data);
uint16 s_dsmco_dsc_handler (uint8 diagmode);
uint16 s_dsmco_RC_handler (void);
uint16 s_dsmco_CommControl_handler (void);
uint16 s_dsmco_DTCSetting_handler (uint8 diagmode);

void  send_negative_response(uint16 respid);
uint8 send_UDS_CAN(uint8 msg_length, uint8 buffer_length,volatile uint8 *buffer );
                      
void send_positive_response(const uint8 msglen);

void EcuSoftRst(void);
extern void CAN_L3_TxUdsMsg(uint8* data);

#endif	