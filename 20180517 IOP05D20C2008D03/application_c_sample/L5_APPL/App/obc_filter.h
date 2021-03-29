/*
 * obc_filter.h
 *
 *  Created on: 2017Äê8ÔÂ25ÈÕ
 *      Author: YCH
 */

#ifndef APP_CONTROL_INCLUDE_OBC_FILTER_H_
#define APP_CONTROL_INCLUDE_OBC_FILTER_H_
#include "my_all.h"

#define CP_FILTER_Tau  40
#define CP_FILTER_Dt   2


extern volatile uint16 L3_I_AD_Curr_Input_filter;
#define Curr_Input_Tau  10
#define Curr_Input_Dt   5

extern volatile uint32 cp_pwm_width_percent_filter;
#define CP_FILTER_CNT   10

extern volatile uint8 cp_pwm_width_percent_filter_cnt;
extern volatile uint32 cpPwmWidthPFilterOffset;

extern volatile uint32 cpPwmWidthPFilterOffset_last;

#endif /* APP_CONTROL_INCLUDE_OBC_FILTER_H_ */
