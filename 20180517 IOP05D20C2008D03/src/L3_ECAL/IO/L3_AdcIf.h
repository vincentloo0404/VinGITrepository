/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
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
*     1.0        2012/10/23      JiaoYu       N/A          Original
*     1.1        2017/1/23        YCH       N/A          Original     
************************************************************************************************/
#ifndef L3_ADCIF_H
#define L3_ADCIF_H 1

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include	"Std_Types.h"
#include    "m_ADC_Cfg.h"
#include    "m_CTU_Drv.h"

extern uint32	RxDataRam0[SYS_CTU_THRESH_0+1];
extern uint32	RxDataRam1[SYS_CTU_THRESH_1+1];


/* macro definition */  
#define ADC0_SAMPLE_SUC (ADC_ISR(ADC0) & ADC_ISR_ECH_MASK)
#define ADC1_SAMPLE_SUC (ADC_ISR(ADC1) & ADC_ISR_ECH_MASK)
 
#define ADC_SAMPLE_SUC ((ADC0_SAMPLE_SUC) && (ADC1_SAMPLE_SUC))

#define AdcSampleStart() 	mADC_Normal_Start(ADC0); mADC_Normal_Start(ADC1)
#define ClearAdcFlag() 	    ADC_ISR(ADC0) = 0x0000001F; ADC_ISR(ADC1) = 0x0000001F

/* AD sample value */
#define SENSOR5V_AD_VAL  ((uint16)(ADC_CDR(ADC0, ADC_CH2)  & ADC0_CDR_CDATA_MASK))   /* I_AD_Sensor5V_M */
#define REF25V_AD_VAL    ((uint16)(ADC_CDR(ADC0, ADC_CH3)  & ADC0_CDR_CDATA_MASK))   /* I_AD_Reference2.5V_M */
#define MOT_CUR_U_AD_VAL ((uint16)(ADC_CDR(ADC0, ADC_CH5)  & ADC0_CDR_CDATA_MASK))   /* AD1_Mot_CurrU */
#define IGN_AD_VAL       ((uint16)(ADC_CDR(ADC0, ADC_CH13) & ADC0_CDR_CDATA_MASK))   /* I_AD_IGN_M */
#define BAT_CMM_AD_VAL   ((uint16)(ADC_CDR(ADC1, ADC_CH2)  & ADC1_CDR_CDATA_MASK))   /* I_AD_12V&CMM_M */
#define BAT_MOS_AD_VAL   ((uint16)(ADC_CDR(ADC1, ADC_CH3)  & ADC1_CDR_CDATA_MASK))   /* I_AD_12V&MOS_M */
#define MOT_CUR_W_AD_VAL ((uint16)(ADC_CDR(ADC1, ADC_CH5)  & ADC1_CDR_CDATA_MASK))   /* AD0_Mot_CurrW */
#define PCB_TEMP_AD_VAL  ((uint16)(ADC_CDR(ADC1, ADC_CH14) & ADC1_CDR_CDATA_MASK))   /* I_AD_PCB&TEM_M */

/* ad value count */
extern uint16 L3_S_Sensor5V_Ct_G_u16;
extern uint16 L3_S_BatCmmVolt_Ct_G_u16;
extern uint16 L3_S_BatMosVolt_Ct_G_u16;

extern uint16 L3_S_IgnVolt_Ct_G_u16;

extern uint16 L3_S_Ref25V_Ct_G_u16;
extern uint16 L3_S_RslvS1_Ct_G_u16;
extern uint16 L3_S_RslvS2_Ct_G_u16;

extern uint16 L3_S_RslvVcc_Ct_G_u16;

extern uint16 L3_S_PcbTemp_Ct_G_u16;

extern uint16 L3_S_RlyCoil_Ct_G_u16;

extern uint16 L3_S_MotorCurrentU_Ct_G_u16;
extern uint16 L3_S_MotorCurrentV_Ct_G_u16;
extern uint16 L3_S_MotorCurrentW_Ct_G_u16;

/* signal */
extern uint16 L3_S_BatCmmVolt_Volt_G_u16p08;
extern uint16 L3_S_BatCmmVolt_Volt_G_u16p10;
extern uint16 L3_S_BatMosVolt_Volt_G_u16p10;

extern uint16 L3_S_RslvS1Buf_Ct_G_u16[6];
extern uint16 L3_S_RslvS2Buf_Ct_G_u16[6];

extern uint16 L3_S_RslvR1Buf_Ct_G_u16[6];
extern uint16 L3_S_RslvR2Buf_Ct_G_u16[6];


extern uint16 L3_Dcdc_Vout_Ct_u16;
extern uint16 L3_Dcdc_Iout_Ct_u16;
extern uint16 L3_Dcdc_IoutFilter_Ct_u16;
extern uint16 L3_Dcdc_IoutFilter_Tau_Ct_u16;


extern uint16 L3_I_AD_CP_Filter_Ct_u16;
extern uint16 L3_I_AD_CP_Filter_Tau_Ct_u16;

extern uint16 L5_AC_Volt_fast_max_buffFilter;
extern uint16 L5_AC_Volt_fast_max_buffFilter;

extern uint16 L3_PriCurHigh_Ct_u16;
extern uint16 L3_PriCurLow_Ct_u16;


extern uint16 L3_AD0_AC_Volt_fast_Ct_u16;
extern uint16 L3_AD0_AC_Volt_fast_max_Ct_u16;

extern uint8 pfcEnAtACzeroState;
extern uint16 L3_AD0_AC_Volt_fast_zeroP_Ct_u16;
extern uint16 L3_AD0_AC_Volt_fast_zeroN_Ct_u16;

extern uint16 L3_I_AD_PFC_slow_Ct_u16;

extern uint16 L3_I_AD_Curr_Input;
extern uint16 L3_I_AD_Curr_InputMax_Ct_u16;

extern uint16 L3_I_AD_Driver13V;
extern uint16 L3_I_AD_12V_CMM;
extern uint16 L3_I_AD_RelayCoil1;

extern uint16 L3_I_AD_PG;
extern uint16 L3_I_AD_CP;
extern uint16 L3_I_AD_CP_max_Ct_u16;
extern uint16 L3_I_AD_CP_max_buff_Ct_u16;


extern uint16 L3_I_AD_PCB_TEM;
extern uint16 L3_I_AD_FB_TEM;


extern uint16 L3_I_AD_CC;
extern uint16 L3_I_AD_Driver13V;
/* function */
extern void AdcSigSample_L3_Per(void);
extern void AdcSigSample_L3_Per1(void);

#endif					
