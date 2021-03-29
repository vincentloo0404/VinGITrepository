
/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   CanIf_Lcfg.c  
*s
* @brief  config file for link.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/26    CODER1       N/A            Original
*     
*******************************************************************************/

#define CANIF_LCFG_SOURCE
/******************************************************************************
 -----------------------------------------------------------------------------
 External Includes
 -----------------------------------------------------------------------------
*******************************************************************************/

#include "CanIf.h"

/*-----------------------------------------------------------------------------
   && config itmes--requesting format and frametype config. 
 ----------------------------------------------------------------------------*/
ROM_CONST CanIf_RxPduConfigType CanIf_RxPduIdConfig[CANIF_MAX_RXPDUHANDLE] = 
{
  {
	  0x7A5u,                              /* CanId (Index: 0) */
	  
	  STANDARD_CAN
  },    
  {
	  0x7DFu, 
	  	                                   /* CanId (Index: 1) */  	
	  STANDARD_CAN
  }
                     
};

/*-----------------------------------------------------------------------------
   && config itmes--response format and frametype config. 
 -----------------------------------------------------------------------------*/
ROM_CONST CanIf_TxPduConfigType CanIf_TxPduConfig[CANIF_MAX_TXPDUHANDLE] = 
{
  {
    0x7E5u,                            /* CanId(PduId/Index: 0) */

    STANDARD_CAN,                      /* CanIdType */

    0,                                 /* Controller physical CAN channel*/
    0,                                 /* Hardware Transmit Handle */
    8,                                 /* Data Length Code */
    (uint8)0                           /* PduR_CanIfTxConfirmation */
  }
};

/* end Fileversion check */

/***************************************************** End ********************************************************/