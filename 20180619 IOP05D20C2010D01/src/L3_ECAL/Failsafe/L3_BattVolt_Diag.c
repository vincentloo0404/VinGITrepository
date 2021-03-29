/*****************************************************************************
*   Copyright 2010 - 2011 Shanghai 
*   Co., Ltd., all rights reserved.
*
*   Filename:    L3_BattVolt_Diag.c
*
*   Description: This file is Battery Voltage Diagnostic C source module
*
*   Revision History:
*
*   Date            Author          Description
*   ----------      ----------      -----------------------------------------
*   2016-11-12      Jerry           Initial created.
*****************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_BattVolt_Diag.h"
      
/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/
static void FS_L3_EnterBatoffState(void);
static void FS_L3_ExitBatoffState(void);
static void FS_L3_EnterBatLowState(void);
static void FS_L3_ExitBatLowState(void);
static void FS_L3_EnterBatNormal1State(void);
static void FS_L3_ExitBatNormal1State(void);
static void FS_L3_EnterBatOver1State(void);
static void FS_L3_ExitBatOver1State(void);
static void FS_L3_EnterBatOver2State(void);
static void FS_L3_ExitBatOver2State(void);

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
#define d_L3BATTVOLTDIAG_START_SEC_VAR
#include "MemMap.h"

static uint16 L3_N_BatOffErrConfirmCnt_Ct_F_u16;
static uint16 L3_N_BatOffErrClearCnt_Ct_F_u16;

static uint16 L3_N_BatLowErrConfirmCnt_Ct_F_u16;
static uint16 L3_N_BatLowErrClearCnt_Ct_F_u16;

static uint16 L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16;
static uint16 L3_N_BatNormal1ErrClearCnt_Ct_F_u16;

static uint16 L3_N_BatOver1ErrConfirmCnt_Ct_F_u16;
static uint16 L3_N_BatOver1ErrClearCnt_Ct_F_u16;

static uint16 L3_N_BatOver2ErrConfirmCnt_Ct_F_u16;
static uint16 L3_N_BatOver2ErrClearCnt_Ct_F_u16;

#define d_L3BATTVOLTDIAG_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3BATTVOLTDIAG_START_SEC_VAR
#include "MemMap.h"

/* 电池电压等级 */
BattDiag_BattLevel_Enu L3_S_BatLevel_Uls_G_Enu;
/* 电池管理状态 */
BattDiag_BattState_Enu L3_S_BatState_Uls_G_Enu;

#define d_L3BATTVOLTDIAG_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3BATTVOLTDIAG_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     FS_L3_BattVoltDiagInit
*
*   Description:  电池电压诊断初始化函数
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FS_L3_BatVoltDiagInit(void)
{
    L3_S_BatState_Uls_G_Enu = e_BAT_STATE_NORMAL2;
    L3_S_BatLevel_Uls_G_Enu = e_BAT_NORMAL_2;

    L3_N_BatOffErrConfirmCnt_Ct_F_u16 = 0;
    L3_N_BatOffErrClearCnt_Ct_F_u16 = 0;
    L3_N_BatLowErrConfirmCnt_Ct_F_u16 = 0;
    L3_N_BatLowErrClearCnt_Ct_F_u16 = 0;
    L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 = 0;
    L3_N_BatNormal1ErrClearCnt_Ct_F_u16 = 0;
    L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 = 0;
    L3_N_BatOver1ErrClearCnt_Ct_F_u16 = 0;
    L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 = 0;
    L3_N_BatOver2ErrClearCnt_Ct_F_u16 = 0;
}
/*****************************************************************************
*
*   Function:     FS_L3_BattVoltDiagPer
*
*   Description:  电池电压诊断主函数
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FS_L3_BatVoltDiagPer(void)
{
    if(k_S_EnBatVoltDiag_Uls_u16 == 0)
    {
    	L3_S_BatState_Uls_G_Enu = e_BAT_STATE_NORMAL2;
		L3_S_BatLevel_Uls_G_Enu = e_BAT_NORMAL_2;

		L3_N_BatOffErrConfirmCnt_Ct_F_u16 = 0;
		L3_N_BatOffErrClearCnt_Ct_F_u16 = 0;
		L3_N_BatLowErrConfirmCnt_Ct_F_u16 = 0;
		L3_N_BatLowErrClearCnt_Ct_F_u16 = 0;
		L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 = 0;
		L3_N_BatNormal1ErrClearCnt_Ct_F_u16 = 0;
		L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 = 0;
		L3_N_BatOver1ErrClearCnt_Ct_F_u16 = 0;
		L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 = 0;
		L3_N_BatOver2ErrClearCnt_Ct_F_u16 = 0;
    }
    else
    {
		switch (L3_S_BatState_Uls_G_Enu)
		{
			/* 0V <= Batt Volt < 6.5V */
			case e_BAT_STATE_OFF:
			{
				FS_L3_ExitBatoffState();

				if (L3_N_BatOffErrClearCnt_Ct_F_u16
				  >= k_S_BatOffClearCntTh_Ct_u16)
				{
					/* 清空'进入'计数器 */
					L3_N_BatOffErrConfirmCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_LOW;

					/* 确认错误 */
					DTC_L4_SetError(e_FAULT_BATVOLT_LOW_ERR);
					/* 清除错误 */
					DTC_L4_ClrError(e_FAULT_BATVOLT_OFF_ERR);
				}
				break;
			}
			/* 7.0V <= Batt Volt < 9.0V */
			case e_BAT_STATE_LOW:
			{
				FS_L3_EnterBatoffState();
				FS_L3_ExitBatLowState();

				if (L3_N_BatOffErrConfirmCnt_Ct_F_u16
				  >= k_S_BatOffConfirmCntTh_Ct_u16)
				{
					/* 清空'退出'计数器 */
					L3_N_BatOffErrClearCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_OFF;

					/* 确认错误 */
					DTC_L4_SetError(e_FAULT_BATVOLT_LOW_ERR);
					/* 确认错误 */
					DTC_L4_SetError(e_FAULT_BATVOLT_OFF_ERR);
				}
				else if (L3_N_BatLowErrClearCnt_Ct_F_u16
					   >= k_S_BatLowClearCntTh_Ct_u16)
				{
					/* 清空'进入'计数器 */
					L3_N_BatLowErrConfirmCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_NORMAL1;

					/* 清除错误 */
					DTC_L4_ClrError(e_FAULT_BATVOLT_LOW_ERR);
					/* 清除错误 */
					DTC_L4_ClrError(e_FAULT_BATVOLT_OFF_ERR);
				}
				break;
			}
			/* 9.5V <= Batt Volt < 10.0V */
			case e_BAT_STATE_NORMAL1:
			{
				FS_L3_EnterBatLowState();
				FS_L3_ExitBatNormal1State();

				if (L3_N_BatLowErrConfirmCnt_Ct_F_u16
				  >= k_S_BatLowConfirmCntTh_Ct_u16)
				{
					/* 清空'退出'计数器 */
					L3_N_BatLowErrClearCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_LOW;

					/* 确认错误 */
					DTC_L4_SetError(e_FAULT_BATVOLT_LOW_ERR);
				}
				else if (L3_N_BatNormal1ErrClearCnt_Ct_F_u16
					   >= k_S_BatNormal1ClearCntTh_Ct_u16)
				{
					/* 清空'进入'计数器 */
					L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_NORMAL2;
				}
				break;
			}
			/* 10.5V <= Batt Volt < 16.0V */
			case e_BAT_STATE_NORMAL2:
			{
				FS_L3_EnterBatNormal1State();
				FS_L3_EnterBatOver1State();

				if (L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16
				  >= k_S_BatNormal1ConfirmCntTh_Ct_u16)
				{
					/* 清空'退出'计数器 */
					L3_N_BatNormal1ErrClearCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_NORMAL1;
				}
				else if (L3_N_BatOver1ErrConfirmCnt_Ct_F_u16
					   >= k_S_BatOver1ConfirmCntTh_Ct_u16)
				{
					/* 清空'退出'计数器 */
					L3_N_BatOver1ErrClearCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_OVER1;

					/* 确认错误 */
					DTC_L4_SetError(e_FAULT_BATVOLT_HIGH_ERR);
				}
				break;
			}
			/* 16.5V <= Batt Volt < 18.0V */
			case e_BAT_STATE_OVER1:
			{
				FS_L3_EnterBatOver2State();
				FS_L3_ExitBatOver1State();

				if (L3_N_BatOver2ErrConfirmCnt_Ct_F_u16
				  >= k_S_BatOver2ConfirmCntTh_Ct_u16)
				{
					/* 清空'退出'计数器 */
					L3_N_BatOver2ErrClearCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_OVER2;

					/* 确认错误 */
					DTC_L4_SetError(e_FAULT_BATVOLT_HIGH_ERR);
				}
				else if (L3_N_BatOver1ErrClearCnt_Ct_F_u16
					   >= k_S_BatOver1ClearCntTh_Ct_u16)
				{
					/* 清空'进入'计数器 */
					L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_NORMAL2;

					/* 清除错误 */
					DTC_L4_ClrError(e_FAULT_BATVOLT_HIGH_ERR);
				}
				break;
			}
			/* 18.5V <= Batt Volt < 20.0V */
			case e_BAT_STATE_OVER2:
			{
				FS_L3_ExitBatOver2State();

				if (L3_N_BatOver2ErrClearCnt_Ct_F_u16
				  >= k_S_BatOver2ClearCntTh_Ct_u16)
				{
					/* 清空'进入'计数器 */
					L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 = 0;

					L3_S_BatState_Uls_G_Enu = e_BAT_STATE_OVER1;
				}
				break;
			}
			default:
			{
				break;
			}
		}
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_EnterBatDropState
*
*   Description:  检测是否进入电池电压跌落状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_EnterBatoffState(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08<=k_S_BatOffStateEnterLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_OFF;

    	if (L3_N_BatOffErrConfirmCnt_Ct_F_u16
           < k_S_BatOffConfirmCntTh_Ct_u16)
        {
            if (L3_N_BatOffErrConfirmCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatOffErrConfirmCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatOffErrConfirmCnt_Ct_F_u16
                   > k_S_BatOffConfirmCntTh_Ct_u16)
                {
                    L3_N_BatOffErrConfirmCnt_Ct_F_u16 =\
                            k_S_BatOffConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatOffErrConfirmCnt_Ct_F_u16 =\
                        k_S_BatOffConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08>=
    		 (k_S_BatOffStateEnterLimit_V_u16p08+5U))
    {
        if (L3_N_BatOffErrConfirmCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatOffErrConfirmCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatOffErrConfirmCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_ExitBatDropState
*
*   Description:  检测是否退出电池电压跌落状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_ExitBatoffState(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08>=k_S_BatOffStateExitLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_LOW;

    	if (L3_N_BatOffErrClearCnt_Ct_F_u16
           < k_S_BatOffClearCntTh_Ct_u16)
        {
            if (L3_N_BatOffErrClearCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatOffErrClearCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatOffErrClearCnt_Ct_F_u16
                   > k_S_BatOffClearCntTh_Ct_u16)
                {
                    L3_N_BatOffErrClearCnt_Ct_F_u16 =\
                            k_S_BatOffClearCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatOffErrClearCnt_Ct_F_u16 =\
                        k_S_BatOffClearCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08<=
    		 (k_S_BatOffStateExitLimit_V_u16p08-5U))
    {
        if (L3_N_BatOffErrClearCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatOffErrClearCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatOffErrClearCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_EnterBatLowState
*
*   Description:  检测是否进入电池过低状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_EnterBatLowState(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08<=k_S_BatLowStateEnterLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_LOW;

    	if (L3_N_BatLowErrConfirmCnt_Ct_F_u16
           < k_S_BatLowConfirmCntTh_Ct_u16)
        {
            if (L3_N_BatLowErrConfirmCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatLowErrConfirmCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatLowErrConfirmCnt_Ct_F_u16
                   > k_S_BatLowConfirmCntTh_Ct_u16)
                {
                    L3_N_BatLowErrConfirmCnt_Ct_F_u16 =\
                            k_S_BatLowConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatLowErrConfirmCnt_Ct_F_u16 =\
                        k_S_BatLowConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08>=
    		 (k_S_BatLowStateEnterLimit_V_u16p08+5U))
    {
        if (L3_N_BatLowErrConfirmCnt_Ct_F_u16
          > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatLowErrConfirmCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatLowErrConfirmCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_ExitBatLowState
*
*   Description:  检测是否退出电池过低状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_ExitBatLowState(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08>=k_S_BatLowStateExitLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_NORMAL_1;

    	if (L3_N_BatLowErrClearCnt_Ct_F_u16
           < k_S_BatLowClearCntTh_Ct_u16)
        {
            if (L3_N_BatLowErrClearCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatLowErrClearCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatLowErrClearCnt_Ct_F_u16
                   > k_S_BatLowClearCntTh_Ct_u16)
                {
                    L3_N_BatLowErrClearCnt_Ct_F_u16 =\
                            k_S_BatLowClearCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatLowErrClearCnt_Ct_F_u16 =\
                        k_S_BatLowClearCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08<=
    		 (k_S_BatLowStateExitLimit_V_u16p08-5U))
    {
        if (L3_N_BatLowErrClearCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatLowErrClearCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatLowErrClearCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_EnterBatLowState
*
*   Description:  检测是否进入电池过低状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_EnterBatNormal1State(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08<=k_S_BatNormal1StateEnterLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_NORMAL_1;

    	if (L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16
           < k_S_BatNormal1ConfirmCntTh_Ct_u16)
        {
            if (L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16
                   > k_S_BatNormal1ConfirmCntTh_Ct_u16)
                {
                    L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 =\
                            k_S_BatNormal1ConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 =\
                        k_S_BatNormal1ConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08>=
    		 (k_S_BatNormal1StateEnterLimit_V_u16p08+5U))
    {
        if (L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatNormal1ErrConfirmCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_ExitBatLowState
*
*   Description:  检测是否退出电池过低状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_ExitBatNormal1State(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08>=k_S_BatNormal1StateExitLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_NORMAL_2;

    	if (L3_N_BatNormal1ErrClearCnt_Ct_F_u16
           < k_S_BatNormal1ClearCntTh_Ct_u16)
        {
            if (L3_N_BatNormal1ErrClearCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatNormal1ErrClearCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatNormal1ErrClearCnt_Ct_F_u16
                   > k_S_BatNormal1ClearCntTh_Ct_u16)
                {
                    L3_N_BatNormal1ErrClearCnt_Ct_F_u16 =\
                            k_S_BatNormal1ClearCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatNormal1ErrClearCnt_Ct_F_u16 =\
                        k_S_BatNormal1ClearCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08<=
    		 (k_S_BatNormal1StateExitLimit_V_u16p08-5U))
    {
        if (L3_N_BatNormal1ErrClearCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatNormal1ErrClearCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatNormal1ErrClearCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_EnterBattOverState
*
*   Description:  检测是否进入电池过压状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_EnterBatOver1State(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08>=k_S_BatOver1StateEnterLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_OVER_1;

    	if (L3_N_BatOver1ErrConfirmCnt_Ct_F_u16
           < k_S_BatOver1ConfirmCntTh_Ct_u16)
        {
            if (L3_N_BatOver1ErrConfirmCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatOver1ErrConfirmCnt_Ct_F_u16
                   > k_S_BatOver1ConfirmCntTh_Ct_u16)
                {
                    L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 =\
                            k_S_BatOver1ConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 =\
                        k_S_BatOver1ConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08<=
    		(k_S_BatOver1StateEnterLimit_V_u16p08-5U))
    {
        if (L3_N_BatOver1ErrConfirmCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatOver1ErrConfirmCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_ExitBatOverState
*
*   Description:  检测是否退出电池过压状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_ExitBatOver1State(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08<=k_S_BatOver1StateExitLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_NORMAL_2;

    	if (L3_N_BatOver1ErrClearCnt_Ct_F_u16
           < k_S_BatOver1ClearCntTh_Ct_u16)
        {
            if (L3_N_BatOver1ErrClearCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatOver1ErrClearCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatOver1ErrClearCnt_Ct_F_u16
                   > k_S_BatOver1ClearCntTh_Ct_u16)
                {
                    L3_N_BatOver1ErrClearCnt_Ct_F_u16 =\
                            k_S_BatOver1ClearCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatOver1ErrClearCnt_Ct_F_u16 =\
                        k_S_BatOver1ClearCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08>=
    		 (k_S_BatOver1StateExitLimit_V_u16p08+5U))
    {
        if (L3_N_BatOver1ErrClearCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatOver1ErrClearCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatOver1ErrClearCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_EnterBattOverState
*
*   Description:  检测是否进入电池过压状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_EnterBatOver2State(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08>=k_S_BatOver2StateEnterLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_OVER_2;

    	if (L3_N_BatOver2ErrConfirmCnt_Ct_F_u16
           < k_S_BatOver2ConfirmCntTh_Ct_u16)
        {
            if (L3_N_BatOver2ErrConfirmCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatOver2ErrConfirmCnt_Ct_F_u16
                   > k_S_BatOver2ConfirmCntTh_Ct_u16)
                {
                    L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 =\
                            k_S_BatOver2ConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 =\
                        k_S_BatOver2ConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08<=
    		(k_S_BatOver2StateEnterLimit_V_u16p08-5U))
    {
        if (L3_N_BatOver2ErrConfirmCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatOver2ErrConfirmCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_ExitBatOverState
*
*   Description:  检测是否退出电池过压状态
*
*   Inputs:       全局变量：L3_S_Battery_Voltage_Vt_G_u16
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_ExitBatOver2State(void)
{
    if (L3_S_BatCmmVolt_Volt_G_u16p08<=k_S_BatOver2StateExitLimit_V_u16p08)
    {
    	L3_S_BatLevel_Uls_G_Enu = e_BAT_OVER_1;

    	if (L3_N_BatOver2ErrClearCnt_Ct_F_u16
           < k_S_BatOver2ClearCntTh_Ct_u16)
        {
            if (L3_N_BatOver2ErrClearCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_BatErrCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_BatOver2ErrClearCnt_Ct_F_u16 +=\
                        (uint16)k_S_BatErrCntIncStep_Ct_u8;

                if (L3_N_BatOver2ErrClearCnt_Ct_F_u16
                   > k_S_BatOver2ClearCntTh_Ct_u16)
                {
                    L3_N_BatOver2ErrClearCnt_Ct_F_u16 =\
                            k_S_BatOver2ClearCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_BatOver2ErrClearCnt_Ct_F_u16 =\
                        k_S_BatOver2ClearCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_BatCmmVolt_Volt_G_u16p08>=
    		 (k_S_BatOver2StateExitLimit_V_u16p08+5U))
    {
        if (L3_N_BatOver2ErrClearCnt_Ct_F_u16
           > k_S_BatErrCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_BatOver2ErrClearCnt_Ct_F_u16 -=\
            		(uint16)k_S_BatErrCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_BatOver2ErrClearCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }
}
#define d_L3BATTVOLTDIAG_STOP_SEC_CODE
#include "MemMap.h"
