
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_SensorVolt_Diag.h"

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
static void FS_L3_SensorVoltLow(void);
static void FS_L3_SensorVoltHigh(void);
static void FS_L3_RslvVccLow(void);
static void FS_L3_RslvVccHigh(void);

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
#define d_L3SENSORVOLTDIAG_START_SEC_VAR
#include "MemMap.h"

/* 传感器供电电压欠压故障的计数器 */
static uint16 L3_N_SenVoltLowErrCnt_Ct_F_u16;
/* 传感器供电电压过压故障的计数器 */
static uint16 L3_N_SenVoltHighErrCnt_Ct_F_u16;

/* Resolver Power Supply */
static uint16 L3_S_RslvVccLowErrCnt_Ct_F_u16;
static uint16 L3_S_RslvVccHighErrCnt_Ct_F_u16;

#define d_L3SENSORVOLTDIAG_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L3SENSORVOLTDIAG_START_SEC_VAR
#include "MemMap.h"

FS_SenorVoltDiagType_Str L3_S_SenorVoltDiagResult_Uls_G_Str;
FS_SenorVoltDiagType_Str L3_S_RslvVccDiagResult_Uls_G_Str;

#define d_L3SENSORVOLTDIAG_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3SENSORVOLTDIAG_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     FS_L4_VehSpeedDiagInit
*
*   Description:  扭矩传感器供电电压诊断初始化函数
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FS_L3_SensorVoltDiagInit(void)
{
    /* torque sensor vcc */
	L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltLow_lgc = FALSE;
	L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltHigh_lgc = FALSE;

	L3_N_SenVoltLowErrCnt_Ct_F_u16 = 0;
    L3_N_SenVoltHighErrCnt_Ct_F_u16 = 0;
    
    /* Resolver power supply */
	L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltLow_lgc = FALSE;
	L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltHigh_lgc = FALSE;
    
    L3_S_RslvVccLowErrCnt_Ct_F_u16  = 0;
    L3_S_RslvVccHighErrCnt_Ct_F_u16 = 0;
}
/*****************************************************************************
*
*   Function:     FS_L3_SensorVoltDiagPer
*
*   Description:  扭矩传感器供电电压诊断主函数
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FS_L3_SensorVoltDiagPer(void)
{
    /* torque sensor power supply diag */
    if (k_S_EnSenVoltDiag_Uls_u16 == 0)
    {
        L3_N_SenVoltLowErrCnt_Ct_F_u16 = 0;
        L3_N_SenVoltHighErrCnt_Ct_F_u16 = 0;
        
        L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltLow_lgc = FALSE;
    	L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltHigh_lgc = FALSE;
        
        DTC_L4_ClrError(e_FAULT_SENSOR_BAT_ERR);
    }
    else
    {
    	FS_L3_SensorVoltLow();
        FS_L3_SensorVoltHigh();

        if ((L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltLow_lgc==FALSE)
         && (L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltHigh_lgc==FALSE))
        {
            DTC_L4_ClrError(e_FAULT_SENSOR_BAT_ERR);
        }
        else
        {
        	DTC_L4_SetError(e_FAULT_SENSOR_BAT_ERR);
        }
    }
   
    /* resolver power supply diag */
    if (k_S_EnRslvVccDiag_Uls_u16 == 0)
    {
        /* Resolver power supply */
        L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltLow_lgc = FALSE;
        L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltHigh_lgc = FALSE;
        
        L3_S_RslvVccLowErrCnt_Ct_F_u16  = 0;
        L3_S_RslvVccHighErrCnt_Ct_F_u16 = 0;
        
        DTC_L4_ClrError(e_FAULT_RSLV_VCC_ERR);
    }
    else
    {
    	FS_L3_RslvVccLow();
        FS_L3_RslvVccHigh();

        if ((L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltLow_lgc==FALSE)
         && (L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltHigh_lgc==FALSE))
        {
            DTC_L4_ClrError(e_FAULT_RSLV_VCC_ERR);
        }
        else
        {
        	DTC_L4_SetError(e_FAULT_RSLV_VCC_ERR);
        }
    }    
}
/*****************************************************************************
*
*   Function:     FS_L3_SensorVoltLow
*
*   Description:  扭矩传感器供电电压低电压检测
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_SensorVoltLow(void)
{
    if (L3_S_Sensor5V_Volt_G_u16p08 <= k_S_SenVoltLowTh_V_u16p08)
    {
        if (L3_N_SenVoltLowErrCnt_Ct_F_u16
           < k_S_SenVoltLowConfirmCntTh_Ct_u16)
        {
            if (L3_N_SenVoltLowErrCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_SenVoltLowCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_SenVoltLowErrCnt_Ct_F_u16 +=\
                        (uint16)k_S_SenVoltLowCntIncStep_Ct_u8;

                if (L3_N_SenVoltLowErrCnt_Ct_F_u16
                   > k_S_SenVoltLowConfirmCntTh_Ct_u16)
                {
                    L3_N_SenVoltLowErrCnt_Ct_F_u16 =\
                            k_S_SenVoltLowConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_SenVoltLowErrCnt_Ct_F_u16 =\
                        k_S_SenVoltLowConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_Sensor5V_Volt_G_u16p08 >=
    		 (k_S_SenVoltLowTh_V_u16p08+5U))
    {
        if (L3_N_SenVoltLowErrCnt_Ct_F_u16
           > k_S_SenVoltLowCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_SenVoltLowErrCnt_Ct_F_u16 -=\
                            (uint16)k_S_SenVoltLowCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_SenVoltLowErrCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_N_SenVoltLowErrCnt_Ct_F_u16
            >= k_S_SenVoltLowConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
        L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltLow_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_N_SenVoltLowErrCnt_Ct_F_u16 == 0)
    {
        /* Clear Fault */
        L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltLow_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_SensorVoltHigh
*
*   Description:  扭矩传感器供电电压过压检测
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_SensorVoltHigh(void)
{
    if (L3_S_Sensor5V_Volt_G_u16p08 >= k_S_SenVoltHighTh_V_u16p08)
    {
        if (L3_N_SenVoltHighErrCnt_Ct_F_u16
           < k_S_SenVoltHighConfirmCntTh_Ct_u16)
        {
            if (L3_N_SenVoltHighErrCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_SenVoltHighCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_N_SenVoltHighErrCnt_Ct_F_u16 +=\
                        (uint16)k_S_SenVoltHighCntIncStep_Ct_u8;

                if (L3_N_SenVoltHighErrCnt_Ct_F_u16
                  > k_S_SenVoltHighConfirmCntTh_Ct_u16)
                {
                    L3_N_SenVoltHighErrCnt_Ct_F_u16 =\
                            k_S_SenVoltHighConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_N_SenVoltHighErrCnt_Ct_F_u16 =\
                        k_S_SenVoltHighConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_Sensor5V_Volt_G_u16p08 <=
    		 (k_S_SenVoltHighTh_V_u16p08-5U))
    {
        if (L3_N_SenVoltHighErrCnt_Ct_F_u16
           > k_S_SenVoltHighCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_N_SenVoltHighErrCnt_Ct_F_u16 -=\
                            (uint16)k_S_SenVoltHighCntDecStep_Ct_u8;
        }
        else
        {
            L3_N_SenVoltHighErrCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_N_SenVoltHighErrCnt_Ct_F_u16
            >= k_S_SenVoltHighConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
        L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltHigh_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_N_SenVoltHighErrCnt_Ct_F_u16 == 0)
    {
        /* Clear Fault */
        L3_S_SenorVoltDiagResult_Uls_G_Str.SenVoltHigh_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_RslvVccLow
*
*   Description:  resolver power supply under limit
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_RslvVccLow(void)
{
    if (L3_S_RslvVcc_Volt_G_u16p08 <= k_S_RslvVccLowTh_V_u16p08)
    {
        if (L3_S_RslvVccLowErrCnt_Ct_F_u16
           < k_S_RslvVccLowConfirmCntTh_Ct_u16)
        {
            if (L3_S_RslvVccLowErrCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_RslvVccLowConfirmCntTh_Ct_u16))
            {
                /* 错误计数器累加 */
                L3_S_RslvVccLowErrCnt_Ct_F_u16 +=\
                        (uint16)k_S_RslvVccLowConfirmCntTh_Ct_u16;

                if (L3_S_RslvVccLowErrCnt_Ct_F_u16
                   > k_S_RslvVccLowConfirmCntTh_Ct_u16)
                {
                    L3_S_RslvVccLowErrCnt_Ct_F_u16 =\
                            k_S_RslvVccLowConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_S_RslvVccLowErrCnt_Ct_F_u16 =\
                        k_S_RslvVccLowConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_RslvVcc_Volt_G_u16p08 >=
    		 (k_S_RslvVccLowTh_V_u16p08+5U))
    {
        if (L3_S_RslvVccLowErrCnt_Ct_F_u16
           > k_S_RslvVccLowCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_S_RslvVccLowErrCnt_Ct_F_u16 -=\
                            (uint16)k_S_RslvVccLowCntDecStep_Ct_u8;
        }
        else
        {
            L3_S_RslvVccLowErrCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_S_RslvVccLowErrCnt_Ct_F_u16
            >= k_S_RslvVccLowConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
        L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltLow_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_S_RslvVccLowErrCnt_Ct_F_u16 == 0)
    {
        /* Clear Fault */
        L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltLow_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
    }
}
/*****************************************************************************
*
*   Function:     FS_L3_RslvVccHigh
*
*   Description:  resolver power supply over limit
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FS_L3_RslvVccHigh(void)
{
    if (L3_S_RslvVcc_Volt_G_u16p08 >= k_S_RslvVccHighTh_V_u16p08)
    {
        if (L3_S_RslvVccHighErrCnt_Ct_F_u16
           < k_S_RslvVccHighConfirmCntTh_Ct_u16)
        {
            if (L3_S_RslvVccHighErrCnt_Ct_F_u16
            <= (MAX_UINT16 - (uint16)k_S_RslvVccHighCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
                L3_S_RslvVccHighErrCnt_Ct_F_u16 +=\
                        (uint16)k_S_RslvVccHighCntIncStep_Ct_u8;

                if (L3_S_RslvVccHighErrCnt_Ct_F_u16
                  > k_S_RslvVccHighConfirmCntTh_Ct_u16)
                {
                    L3_S_RslvVccHighErrCnt_Ct_F_u16 =\
                            k_S_RslvVccHighConfirmCntTh_Ct_u16;
                }
            }
            else
            {
                L3_S_RslvVccHighErrCnt_Ct_F_u16 =\
                        k_S_RslvVccHighConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_RslvVcc_Volt_G_u16p08 <=
    		 (k_S_RslvVccHighTh_V_u16p08-5U))
    {
        if (L3_S_RslvVccHighErrCnt_Ct_F_u16
           > k_S_RslvVccHighCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
            L3_S_RslvVccHighErrCnt_Ct_F_u16 -=\
                            (uint16)k_S_RslvVccHighCntDecStep_Ct_u8;
        }
        else
        {
            L3_S_RslvVccHighErrCnt_Ct_F_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_S_RslvVccHighErrCnt_Ct_F_u16
            >= k_S_RslvVccHighConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
        L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltHigh_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_S_RslvVccHighErrCnt_Ct_F_u16 == 0)
    {
        /* Clear Fault */
        L3_S_RslvVccDiagResult_Uls_G_Str.SenVoltHigh_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
    }
}
#define d_L3SENSORVOLTDIAG_STOP_SEC_CODE
#include "MemMap.h"

/*End of L3_SensorVolt_Diag.c file */

