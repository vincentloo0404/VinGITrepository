/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_ADC_Cfg.h
*
* @brief    Config Header file for "m_ADC_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/09/27      CODER2       	   	N/A          Original
*     1.1        2012/10/09      CODER2           	N/A          simplified
*     1.2        2012/11/02      CODER2			N/A          Add History Comment
*     1.3        2013/02/26      CODER2			N/A          Code Simplify, Delete Reg_Bit Functions
*     1.4        2014/07/21      CODER2			N/A          Modify ADC Config for WanDu Analog Sensor, V1.6 HW
*     1.5        2016/02/26      ych			N/A          OBC PIN ADC
************************************************************************************************/

#ifndef _M_ADC_CFG_H_
#define _M_ADC_CFG_H_


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"m_ADC_Drv.h"
#include	"SysConfig.h"


/* *****************************************************************************
   *****************************************************************************
   Config Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	ADC0 Pin Configration                                              ***/
/*---------------------------------------------------------------------------*/
#define		ADC_PCR				(B_APC)
#define		ADC0_CH0_PIN		B7      /* I_AD_Vout */
#define		ADC0_CH2_PIN		C1      /* I_AD_Driver13V */
#define		ADC0_CH3_PIN		C2      /* I_AD_CP */	  
#define		ADC0_CH4_PIN		E1      /* I_AD_FB_TEM */
#define		ADC0_CH5_PIN		E2      /* AD0_Pri_Curr_High */
#define		ADC0_CH13_PIN		B11     /* I_AD_RelayCoil1 */


#define		ADC0_CH11_PIN		B9     /*  */


/*---------------------------------------------------------------------------*/
/***	ADC1 Pin Configration                                              ***/
/*---------------------------------------------------------------------------*/
#define		ADC1_CH0_PIN		B13      /* I_AD_Curr_Input */
#define		ADC1_CH1_PIN		B14      /* I_AD_PCB_TEM */
#define		ADC1_CH2_PIN		B15      /* I_AD_12V_CMM */
#define		ADC1_CH3_PIN		C0       /*  */
#define		ADC1_CH4_PIN		D15      /* I_AD_CC */
#define		ADC1_CH5_PIN		E0       /* AD0_Pri_Curr_Low */
//#define		ADC1_CH11_PIN		B9       /*  */
#define		ADC1_CH12_PIN		B10      /* AD0_Sec_Curr_fast */
#define		ADC1_CH14_PIN		B12     /* I_AD_PFC_TEM */

/*---------------------------------------------------------------------------*/
/***	DCDC voltage and current out                                       ***/
/*---------------------------------------------------------------------------*/
#define     DCDC_VOUT_AD  (((ADC0<<4)^(1<<4))|AD_CH0)    /* I_AD_Vout */
#define     DCDC_IOUT_AD  (((ADC1<<4)^(1<<4))|AD_CH12)   /* AD0_Sec_Curr_fast*/

#define     PRI_CUR_AD_HIGH  (((ADC0<<4)^(1<<4))|AD_CH5)    /* AD0_Pri_Curr_High */
#define     PRI_CUR_AD_LOW   (((ADC1<<4)^(1<<4))|AD_CH5)    /* AD0_Pri_Curr_Low*/

//#define     ADC1_CH11      (((ADC1<<4)^(1<<4))|AD_CH11)  
//#define     ADC0_CH4       (((ADC0<<4)^(1<<4))|AD_CH4)
#define     ADC0_CH11      (((ADC0<<4)^(1<<4))|AD_CH11)  
#define     ADC1_CH3       (((ADC1<<4)^(1<<4))|AD_CH3)


#define     ADC0_CH3      (((ADC0<<4)^(1<<4))|AD_CH3)     //I_AD_CP
#define     ADC1_CH0       (((ADC1<<4)^(1<<4))|AD_CH0)   //I_AD_Curr_Input
  
#define     ADC0_CH4      (((ADC0<<4)^(1<<4))|AD_CH4)     //I_AD_FB_TEM
//#define     ADC1_CH14       (((ADC1<<4)^(1<<4))|AD_CH14)   //I_AD_PFC_TEM
#define     ADC1_CH1       (((ADC1<<4)^(1<<4))|AD_CH1)   //I_AD_PCB_TEM

#define     ADC0_CH2      (((ADC0<<4)^(1<<4))|AD_CH2)  //I_AD_Driver13V
#define     ADC1_CH4       (((ADC1<<4)^(1<<4))|AD_CH4) //I_AD_CC

#define     ADC0_CH13      (((ADC0<<4)^(1<<4))|AD_CH13)  //I_AD_RelayCoil1
#define     ADC1_CH2       (((ADC1<<4)^(1<<4))|AD_CH2) //I_AD_12V_CMM
/////////////////////////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------*/
/***	Motor Pin Configration                                             ***/
/*---------------------------------------------------------------------------*/
#define     MOTOR_PHASE_W_AD  (((ADC0<<4)^(1<<4))|AD_CH5)/* AD1_Mot_CurrU ->Phase W for Bsample */
#define     MOTOR_PHASE_U_AD  (((ADC1<<4)^(1<<4))|AD_CH5)/* AD0_Mot_CurrW ->Phase U for Bsample*/

/*---------------------------------------------------------------------------*/
/***	Resolver Pin Configration                                          ***/
/*---------------------------------------------------------------------------*/
#define     RSLV_SIN_AD       (((ADC0<<4)^(1<<4))|AD_CH0)     /* I_AD_ResolverSin */
#define     RSLV_COS_AD       (((ADC1<<4)^(1<<4))|AD_CH0)     /* I_AD_ResolverCos */
#define     REF_25_AD         (((ADC0<<4)^(1<<4))|AD_CH3)     /* I_AD_Reference2.5V_M */   
#define     RSLV_VCCR_AD      (((ADC1<<4)^(1<<4))|AD_CH4)     /* I_AD_VCCR */   

/*---------------------------------------------------------------------------*/
/***	Power Pin Configration                                             ***/
/*---------------------------------------------------------------------------*/
#define     BAT_POWER_AD      (((ADC1<<4)^(1<<4))|AD_CH2)    /* I_AD_12V&CMM_M  */
#define     BAT_OUT_AD        (((ADC1<<4)^(1<<4))|AD_CH3)    /* I_AD_12V&MOS_M */
#define     SENSOR_5V_AD      (((ADC0<<4)^(1<<4))|AD_CH2)    /* I_AD_Sensor5V_M */
#define     IGN_AD            (((ADC0<<4)^(1<<4))|AD_CH13)   /* I_AD_IGN_M */

/*---------------------------------------------------------------------------*/
/***	Temperature Pin Configration                                       ***/
/*---------------------------------------------------------------------------*/
#define     TEMP_AD           (((ADC0<<4)^(1<<4))|AD_CH14)    /* I_AD_PCB&TEM_M */

/*---------------------------------------------------------------------------*/
/***	others                                                             ***/
/*---------------------------------------------------------------------------*/
#define     RELAY_COIL_AD     (((ADC1<<4)^(1<<4))|AD_CH1)     /* I_AD_RelayCoil */

/*---------------------------------------------------------------------------*/
/***	CTU Used for ADC ,Initate CTU Used for ADC                         ***/
/*---------------------------------------------------------------------------*/
#define		ADC_CTU_INIT

#endif					
