/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     L3_GPIO.h
*
* @brief    
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2017/02/20      YCH       		N/A          Original
*     
************************************************************************************************/
#ifndef L3_GPIO_H
#define L3_GPIO_H 1

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include	"Std_Types.h"
//1-5
#define O_DCDC_DRV_EN 
//#define O_DCDC_DRV_EN A6_OUT
#define TEST1  A6_OUT//2pin
#define O_OVP_RSET A7_OUT

//#define O_PFC_DRV_EN A8_OUT //modify to O_PFC_EN
#define O_PFC_EN C4_OUT

//6-10

#define S2_CTR A8_OUT
#define O_PFC_OVP_RSET C5_OUT
#define TEST2  //8pin
#define O_PFC_OCP_RSET C7_OUT

#define O_DEN  C3_OUT

//11-15

#define O_MCU_FAT D9_OUT


//21-25

#define O_PG D8_OUT
#define PG_SENSE D5_IN
#define AC_WAKEUP D6_IN

//26-30
#define I_AD_LocalWake D7_IN


//51-55
#define O_OCP_RSET A0_OUT
#define CAN_MODE C11_OUT


//56-60
#define EN_POWER_UC_SBC A2_IN


//60-65



//65-70
#define I_DCDC_OCP  D12_IN


//71-75
#define I_GLB_EN C13_IN
#define O_GLB_RSET C14_OUT

//76-80
#define I_PFC_OCP  C10_IN //53->78 PIN  D10_IN->C10_IN
#define I_PFC_OVP  B2_IN//54->79 PIN   D11_IN->B2_IN
#define I_DCDC_OVP  B3_IN //67->80    D13_IN->B3_IN

//81-85

//#define O_S_RlyCTL A12_OUT
#define O_S_RlyCTL1 A12_OUT
#define O_S_RlyCTL2 C9_OUT

//86-90


//91-95
#define OVER_CUR_TRIG A9_IN
#define LIMP_OUT A13_IN




//96-100
#define I_SBC_INTN B6_IN

#define EN_POWER_FLYBACK D2_OUT

















#endif					
