/******************************************************************************
*
* Beijing Hualong Tech Inc.
* (c) Copyright 2013 Beijing Hualong Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dtc_Types.h  
*
* @brief  this file defines the Marcos and datatypes used by the DTC Moudle..
*
********************************************************************************
*    Revision History:
*                                         
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     draft      2013/05/10    CODER1     N/A           Original
*     
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/

#ifndef _DTC_TYPES_H_
#define _DTC_TYPES_H_

#include "Platform_Types.h"

/******************************************************************************                          
 *                           Global Macros           
 ******************************************************************************/ 
#define DTC_RESTABLE                   1U
#define DTC_PARTIALRESTABLE            2U
#define DTC_UNRESTABLE                 3U

#define DETECT_CYCLIC                  1U
#define DETECT_ON_DEMAND               2U 
#define DETECT_IN_INITIALIZATION       3U

#define DTC_WITH_SNAPSHOT              1U
#define DTC_NO_SNAPSHOT                0U
#define DTC_WITH_EXTENDDATA            1U
#define DTC_NO_EXTENDDATA              0U

#define DATA_BE_FROZEN                 1u
#define DATA_NO_FROZEN                 0u

#define DTC_WITH_WARNING_INDICATOR     1U
#define DTC_NO_WARNING_INDICATOR       0U


#define SAFETY_D_LEVLE             1U
#define SAFETY_C_LEVEL             2U      
#define SAFETY_B_LEVEL             3U
#define SAFETY_A_LEVEL             4U /*unrestable*/
#define SAFETY_S_LEVEL             5U /*unrestable*/



#define IMMEDIATE                      1u
#define NON_IMMEDIATE                  0u

#define IN_FAULT                  (uint8)1u
#define NO_FAULT                  (uint8)0u



#endif