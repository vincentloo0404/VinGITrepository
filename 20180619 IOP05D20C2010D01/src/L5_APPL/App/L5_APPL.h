/*****************************************************************************
*   Copyright 2010 - 2011 Shanghai Aerospace Automobile Electromechanical 
*   Co., Ltd., all rights reserved.
*
*   Filename:    L5_APPL.h
*
*   Description: This file is C header file for Application Layer
*
*   Revision History:
*
*   Date            Author          Description
*   ----------      ----------      -----------------------------------------
*   2016-1-31      	  YCH		     Initial created
*
*****************************************************************************/
#ifndef L5_APPL_H
#define L5_APPL_H  1
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "L5_APPL_Cfg.h"
#include "OBC.h"
/* L5_APPL */
//#include "L5_ApplFailSafe.h"
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
extern void APPL_L5_Init(void);
extern void APPL_1ms_task(void);
extern void APPL_softwareRest(void);
extern uint16 UDS_TimeOutCnt; 
extern uint8 UDS_TimeOutFlag; 
extern void APPL_100us_task(void);
#endif 
 /* End of L5_APPL.h file */
