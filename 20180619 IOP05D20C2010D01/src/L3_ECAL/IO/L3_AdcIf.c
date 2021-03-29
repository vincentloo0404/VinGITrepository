/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     AdcIf
* 
* @brief    adc interface between MCAL and HAL
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/10/23      JiaoYu       N/A          Original
*     
*******************************************************************************/

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"L3_AdcIf.h"
#include 	"obc_app.h"

uint32	RxDataRam0[SYS_CTU_THRESH_0+1];
uint32	RxDataRam1[SYS_CTU_THRESH_1+1];

/* ad value count */
uint16 L3_S_Sensor5V_Ct_G_u16;
uint16 L3_S_Ref25V_Ct_G_u16;

uint16 L3_S_RslvR1_Ct_G_u16;
uint16 L3_S_RslvR2_Ct_G_u16;

uint16 L3_S_RslvS1_Ct_G_u16;
uint16 L3_S_RslvS2_Ct_G_u16;

uint16 L3_S_RslvS1Buf_Ct_G_u16[6];
uint16 L3_S_RslvS2Buf_Ct_G_u16[6];

uint16 L3_S_RslvR1Buf_Ct_G_u16[6];
uint16 L3_S_RslvR2Buf_Ct_G_u16[6];

uint16 L3_S_RslvVcc_Ct_G_u16;

uint16 L3_S_BatCmmVolt_Ct_G_u16;
uint16 L3_S_BatMosVolt_Ct_G_u16;

uint16 L3_S_IgnVolt_Ct_G_u16;

uint16 L3_S_PcbTemp_Ct_G_u16;

uint16 L3_S_MotorCurrentU_Ct_G_u16;
uint16 L3_S_MotorCurrentV_Ct_G_u16;
uint16 L3_S_MotorCurrentW_Ct_G_u16;

uint16 L3_S_PhaseU_Ct_G_u16;
uint16 L3_S_RlyCoil_Ct_G_u16;



uint16 L3_Dcdc_Vout_Ct_u16;
uint16 L3_Dcdc_Iout_Ct_u16;

uint16 L3_Dcdc_IoutFilter_Ct_u16;
uint16 L3_Dcdc_IoutFilter_Tau_Ct_u16 = 3000;

uint16 L3_I_AD_CP_Filter_Ct_u16;
uint16 L3_I_AD_CP_Filter_Tau_Ct_u16 = 300;



//uint16 L5_AC_Volt_fast_max_buffFilter;
//uint16 L5_AC_Volt_fast_max_buffFilter = 30;

uint16 L3_PriCurHigh_Ct_u16;
uint16 L3_PriCurLow_Ct_u16;

uint16 L3_AD0_AC_Volt_fast_Ct_u16;
uint16 L3_AD0_AC_Volt_fast_max_Ct_u16;

//uint16 L3_AD0_AC_Volt_fast_finshmax_Ct_u16;



uint16 L3_I_AD_PFC_slow_Ct_u16;
uint16 L3_I_AD_Curr_Input;
uint16 L3_I_AD_Curr_InputMax_Ct_u16 = 0;
uint16 L3_I_AD_Driver13V;
uint16 L3_I_AD_12V_CMM;
uint16 L3_I_AD_PG;
uint16 L3_I_AD_CP;
uint16 L3_I_AD_CP_max_Ct_u16;
uint16 L3_I_AD_CP_max_buff_Ct_u16;
uint16 L3_I_AD_RelayCoil1;



uint16 L3_I_AD_PCB_TEM;
uint16 L3_I_AD_FB_TEM;

uint16 L3_I_AD_CC;
uint16 L3_I_AD_Driver13V;

/* *****************************************************************************
   Function:        hAdcIf_u16GetBatVoltVal
   Description:     init
   Parameters:      Input:    None
                    Output:   battery voltage sample value
   Notes:           
                   
   ***************************************************************************** */
void AdcSigSample_L3_Init(void)
{
   /* ad value count */
   L3_Dcdc_Vout_Ct_u16 = 0;
   L3_Dcdc_Iout_Ct_u16 = 0;

}
/* *****************************************************************************
   Function:        AdcSigSample_L3_Per
   Description:     init
   Parameters:      Input:    None
                    Output:   battery voltage sample value
   Notes:           
                   
   ***************************************************************************** */
void AdcSigSample_L3_Per(void)
{
    uint8 adChn,i;
   
	for(i=0; i<=SYS_CTU_THRESH_0;i++)
	{
	   adChn = (uint8)( ( RxDataRam0[i]>>16) & 0x1F );

	   switch(adChn)
	   {
	   	 case DCDC_VOUT_AD:          /* I_AD_Vout*/
	   	 {
              L3_Dcdc_Vout_Ct_u16 =  ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;	   	 	
	   	 }
	   	 break;

	   	 case DCDC_IOUT_AD:          /* AD0_Sec_Curr_fast*/
	   	 {
              L3_Dcdc_Iout_Ct_u16 = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;   	 	
	   	 }
	   	 break;
	   	 
	   	 case PRI_CUR_AD_HIGH:          /* AD0_Sec_Curr_fast*/
	   	 {
              L3_PriCurHigh_Ct_u16 = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;   	 	
	   	 }
	   	 break;

	   	 case PRI_CUR_AD_LOW:          /* AD0_Sec_Curr_fast*/
	   	 {
              L3_PriCurLow_Ct_u16 = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;   	 	
	   	 }
	   	 break;	   	 

	   	 case ADC1_CH3:     //I_AD_PFC_slow
	   	 {
			   L3_I_AD_PFC_slow_Ct_u16 = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;   
	   	 }
	   	 break;	   	 

	   	 case ADC0_CH11:   //AD0_AC_Volt_fast       
	   	 {
			  L3_AD0_AC_Volt_fast_Ct_u16 = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;
			  if(L3_AD0_AC_Volt_fast_Ct_u16 > L3_AD0_AC_Volt_fast_max_Ct_u16)
			  {
			  	L3_AD0_AC_Volt_fast_max_Ct_u16 = L3_AD0_AC_Volt_fast_Ct_u16;
			  }
		     if(stSysFSMCtrl.ucCurrentState  == STATE_PFC_RUN)
		     {
		   		if(mStateCntrTag.PFC_RUNCntr > mStateTimerTag.PFC_RUNTime)
				{
					if(L3_AD0_AC_Volt_fast_zeroN_Ct_u16 <= L3_AD0_AC_Volt_fast_Ct_u16 && L3_AD0_AC_Volt_fast_Ct_u16 <= L3_AD0_AC_Volt_fast_zeroP_Ct_u16)
				   {
				  	  pfcEnAtACzeroState = TRUE;
				  	  //TEST1 = HIGH;
				  	  O_PFC_EN = HIGH;
				  	  HW_O_PFC_EN = O_PFC_EN;
				   }
				}
				else
				{
					pfcEnAtACzeroState = FALSE;
					//TEST1 = LOW;
				}
		   	  
		     }
		     /*
		     if(L3_AD0_AC_Volt_fast_Ct_u16 > L3_AD0_AC_Volt_fast_finshmax_Ct_u16)
		     {
		     	L3_AD0_AC_Volt_fast_finshmax_Ct_u16 = L3_AD0_AC_Volt_fast_Ct_u16;
		     }
		     */
			  
			  
			  

	   	 }
	   	 break;	   	 
	   	 
 		 case ADC0_CH3:     //I_AD_CP
	   	 {
			  L3_I_AD_CP = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;
			  if(L3_I_AD_CP >= L3_I_AD_CP_max_Ct_u16)
			  {
			  	L3_I_AD_CP_max_Ct_u16 = L3_I_AD_CP;
			  }
	   	 }
	   	 break;	   	 

	   	 case ADC1_CH0:   //I_AD_Curr_Input       
	   	 {
			  L3_I_AD_Curr_Input = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;
			  if(L3_I_AD_Curr_InputMax_Ct_u16 <= L3_I_AD_Curr_Input)
			  {
			  	L3_I_AD_Curr_InputMax_Ct_u16 = L3_I_AD_Curr_Input;
			  }
			  //L3_I_AD_Curr_Input_filter = LPF(L3_I_AD_Curr_Input,L3_I_AD_Curr_Input_filter,Curr_Input_Tau,Curr_Input_Dt);

	   	 }
	   	 break;
	   	
	   	 
	   
	   	 
	   	 default:
	   	 {
	   	 	
	   	 }
	   	 break;
	   }
	}
}
/* *****************************************************************************
   Function:        AdcSigSample_L3_Per
   Description:     init
   Parameters:      Input:    None
                    Output:   battery voltage sample value
   Notes:           
                   
   ***************************************************************************** */
  
void AdcSigSample_L3_Per1(void)
{
    uint8 adChn,i,r1Index = 0,r2Index =0;

	for(i=0; i<=SYS_CTU_THRESH_1;i++)
	{
	   adChn = (uint8)( ( RxDataRam1[i]>>16) & 0x1F );
	
	   switch(adChn)
	   {
	   	
	     case ADC0_CH2:   //I_AD_Driver13V
	   	 {
			 L3_I_AD_Driver13V = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;
			  
	   	 }
	   	 break;
	   	 
	   	 
	   	 case ADC1_CH4:   //I_AD_CC
	   	 {
			 L3_I_AD_CC = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;
			  
	   	 }
	   	 break;
	   	 
	   	  case ADC0_CH4:     //I_AD_FB_TEM
	   	 {
			  L3_I_AD_FB_TEM = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;
			  //L3_I_AD_FB_TEM = 0 ;
	   	 }
	   	 break;	 
	   	 /*  	 
	   	 case ADC1_CH14:   //I_AD_PFC_TEM       
	   	 {
			 L3_I_AD_PCB_TEM = ((uint16)RxDataRam0[i]) & (0x3FF<<0) ;
			  
	   	 }
	   	 break;
	   	 */
	   	 case ADC1_CH1:   //I_AD_PCB_TEM  ====     L3_I_AD_PCB_TEM   
	   	 {
			 L3_I_AD_PCB_TEM = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;
			  
	   	 }
	   	 break;
	   	 /*
	   	 case ADC0_CH3:     //I_AD_CP
	   	 {
			  L3_I_AD_CP = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;
			  if(L3_I_AD_CP >= L3_I_AD_CP_max_Ct_u16)
			  {
			  	L3_I_AD_CP_max_Ct_u16 = L3_I_AD_CP;
			  }
	   	 }
	   	 break;	   	 

	   	 case ADC1_CH0:   //I_AD_Curr_Input       
	   	 {
			  L3_I_AD_Curr_Input = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;
			  if(L3_I_AD_Curr_InputMax_Ct_u16 <= L3_I_AD_Curr_Input)
			  {
			  	L3_I_AD_Curr_InputMax_Ct_u16 = L3_I_AD_Curr_Input;
			  }
			  //L3_I_AD_Curr_Input_filter = LPF(L3_I_AD_Curr_Input,L3_I_AD_Curr_Input_filter,Curr_Input_Tau,Curr_Input_Dt);

	   	 }
	   	 break;
	   	 */
	   	 
	   	 case ADC0_CH13:     //I_AD_RelayCoil1
	   	 {
			  L3_I_AD_RelayCoil1 = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;
	   	 }
	   	 break;	   	 

	   	 case ADC1_CH2:   //I_AD_12V_CMM       
	   	 {
			  L3_I_AD_12V_CMM = ((uint16)RxDataRam1[i]) & (0x3FF<<0) ;

	   	 }
	   	 break;
	   	 	   	 	   	 
	   	 default:
	   	 break;
	   }
	}
}
/* End of file */