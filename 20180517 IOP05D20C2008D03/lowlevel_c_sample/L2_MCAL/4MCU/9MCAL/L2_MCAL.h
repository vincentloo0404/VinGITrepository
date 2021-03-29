/******************************************************************************
*
* ChuangQu NewEnergy .
* (c) Copyright 2014 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     
*
* @brief    
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2014/12/20      JiaoYu    	   	N/A          Original
************************************************************************************************/
#ifndef L2_MCAL_H
#define L2_MCAL_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "MPC560xP.h"
#include "Std_Types.h"
#include "m_Clock_Drv.h"
#include "m_GPIO.h"
#include "m_Intc_Drv.h"
#include "m_CAN_Drv.h"
#include "m_CAN_Cfg.h"
#include "m_EDMA_Drv.h"
#include "m_ETimer_Drv.h"
#include "m_DSPI_Drv.h"
#include "L2_Ecc.h"

#include "V_ccp.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void MCU_L2_Init(void);
#endif 
 /* End of L2_MCAL.h file */
