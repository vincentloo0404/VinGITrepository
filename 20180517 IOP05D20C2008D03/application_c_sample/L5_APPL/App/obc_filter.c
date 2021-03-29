/*
 * obc_filter.c
 *
 *  Created on: 2017Äê8ÔÂ25ÈÕ
 *      Author: YCH
 */
#include "obc_filter.h"

volatile uint32 cp_pwm_width_percent_filter =0;

volatile uint32 cp_pwm_width_percent_average =0;

volatile uint8 cp_pwm_width_percent_filter_cnt = 0;

volatile uint32 cpPwmWidthPFilterOffset =0;

volatile uint32 cpPwmWidthPFilterOffset_last =0;

volatile uint16 L3_I_AD_Curr_Input_filter =0;
