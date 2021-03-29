
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_Temperature_Diag.h"

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
static void FS_L3_TempSenShGnd(void);
static void FS_L3_TempSenShVc(void);
static void FS_L3_TempSenHigh(void);
static void FS_L3_TempSenLow(void);

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
#define d_L3TEMPERATUREDIAG_START_SEC_VAR
#include "MemMap.h"

static uint16 L3_N_TempSenShGndErrCnt_Ct_u16;

static uint16 L3_N_TempSenShVcErrCnt_Ct_u16;

static uint16 L3_N_TempSenHighErrCnt_Ct_u16;

static uint16 L3_N_TempSenLowErrCnt_Ct_u16;

static uint8  L3_N_TempSenDiagLoopCt_Ct_u08;

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/

FS_TempSenDiagType_Str L3_S_TempSenDiagResult_Uls_G_Str;

#define d_L3TEMPERATUREDIAG_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L3TEMPERATUREDIAG_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     FS_L3_TemperatureDiagPer
*
*   Description:  Mosfet Temperature Diagnosis Per 20ms
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FS_L3_TemperatureDiagInit(void)
{
	L3_S_TempSenDiagResult_Uls_G_Str.TempSenShGnd_lgc = FALSE;
	L3_S_TempSenDiagResult_Uls_G_Str.TempSenShVc_lgc = FALSE;
	L3_S_TempSenDiagResult_Uls_G_Str.TempSenHigh_lgc = FALSE;
	L3_S_TempSenDiagResult_Uls_G_Str.TempSenLow_lgc = FALSE;

	L3_N_TempSenShGndErrCnt_Ct_u16 = 0;
	L3_N_TempSenShVcErrCnt_Ct_u16 = 0;
	L3_N_TempSenHighErrCnt_Ct_u16 = 0;
	L3_N_TempSenLowErrCnt_Ct_u16 = 0;
	
	L3_N_TempSenDiagLoopCt_Ct_u08 = 0;
}
/*****************************************************************************
*
*   Function:     FS_L3_TemperatureDiagPer
*
*   Description:  Mosfet Temperature Diagnosis Per 20ms
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FS_L3_TemperatureDiagPer(void)
{
	if (k_S_TempSenDiagENbFlg_Uls_u16 == 0)
	{
		L3_N_TempSenShGndErrCnt_Ct_u16 = 0;
		L3_N_TempSenShVcErrCnt_Ct_u16 = 0;
		L3_N_TempSenHighErrCnt_Ct_u16 = 0;
		L3_N_TempSenLowErrCnt_Ct_u16 = 0;
		
		DTC_L4_ClrError(e_FAULT_TEMP_EXDLIM_ERR);
		DTC_L4_ClrError(e_FAULT_TEMP_SEN_ERR);
	}
	else
	{
		if(L3_N_TempSenDiagLoopCt_Ct_u08 >= 8)
		{
			FS_L3_TempSenShGnd();
			FS_L3_TempSenShVc();
			FS_L3_TempSenHigh();
			FS_L3_TempSenLow();

			if((L3_S_TempSenDiagResult_Uls_G_Str.TempSenHigh_lgc == FALSE)\
			&& (L3_S_TempSenDiagResult_Uls_G_Str.TempSenLow_lgc == FALSE))
			{
				DTC_L4_ClrError(e_FAULT_TEMP_EXDLIM_ERR);
			}
			else
			{
				DTC_L4_SetError(e_FAULT_TEMP_EXDLIM_ERR);
			}

			if((L3_S_TempSenDiagResult_Uls_G_Str.TempSenShGnd_lgc == FALSE)\
			&& (L3_S_TempSenDiagResult_Uls_G_Str.TempSenShVc_lgc == FALSE))
			{
				DTC_L4_ClrError(e_FAULT_TEMP_SEN_ERR);
			}
			else
			{
				DTC_L4_SetError(e_FAULT_TEMP_SEN_ERR);
			}
			
			L3_N_TempSenDiagLoopCt_Ct_u08 = 0;
		}
		
		L3_N_TempSenDiagLoopCt_Ct_u08++;
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
static void FS_L3_TempSenShGnd(void)
{
    if (L3_S_PcbTemp_Ct_G_u16 <= k_S_TempSenShGndLmt_Cnt_u16)
    {
        if (L3_N_TempSenShGndErrCnt_Ct_u16
           < k_S_TempSenShGndConfirmCntTh_Ct_u16)
        {
            if (L3_N_TempSenShGndErrCnt_Ct_u16
            <= (MAX_UINT16 - (uint16)k_S_TempSenShGndCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
            	L3_N_TempSenShGndErrCnt_Ct_u16 +=\
                        (uint16)k_S_TempSenShGndCntIncStep_Ct_u8;

                if (L3_N_TempSenShGndErrCnt_Ct_u16
                   > k_S_TempSenShGndConfirmCntTh_Ct_u16)
                {
                	L3_N_TempSenShGndErrCnt_Ct_u16 =\
                			k_S_TempSenShGndConfirmCntTh_Ct_u16;
                }
            }
            else
            {
            	L3_N_TempSenShGndErrCnt_Ct_u16 =\
            			k_S_TempSenShGndConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_PcbTemp_Ct_G_u16 >=
    		 (k_S_TempSenShGndLmt_Cnt_u16+5U))
    {
        if (L3_N_TempSenShGndErrCnt_Ct_u16
           > k_S_TempSenShGndCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
        	L3_N_TempSenShGndErrCnt_Ct_u16 -=\
                    (uint16)k_S_TempSenShGndCntDecStep_Ct_u8;
        }
        else
        {
        	L3_N_TempSenShGndErrCnt_Ct_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_N_TempSenShGndErrCnt_Ct_u16
            >= k_S_TempSenShGndConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenShGnd_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_N_TempSenShGndErrCnt_Ct_u16 == 0)
    {
        /* Clear Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenShGnd_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
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
static void FS_L3_TempSenShVc(void)
{
    if (L3_S_PcbTemp_Ct_G_u16 >= k_S_TempSenShVcLmt_Cnt_u16)
    {
        if (L3_N_TempSenShVcErrCnt_Ct_u16
           < k_S_TempSenShVcConfirmCntTh_Ct_u16)
        {
            if (L3_N_TempSenShVcErrCnt_Ct_u16
            <= (MAX_UINT16 - (uint16)k_S_TempSenShVcCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
            	L3_N_TempSenShVcErrCnt_Ct_u16 +=\
                        (uint16)k_S_TempSenShVcCntIncStep_Ct_u8;

                if (L3_N_TempSenShVcErrCnt_Ct_u16
                   > k_S_TempSenShVcConfirmCntTh_Ct_u16)
                {
                	L3_N_TempSenShVcErrCnt_Ct_u16 =\
                			k_S_TempSenShVcConfirmCntTh_Ct_u16;
                }
            }
            else
            {
            	L3_N_TempSenShVcErrCnt_Ct_u16 =\
            			k_S_TempSenShVcConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_PcbTemp_Ct_G_u16 <=
    		 (k_S_TempSenShVcLmt_Cnt_u16-5U))
    {
        if (L3_N_TempSenShVcErrCnt_Ct_u16
           > k_S_TempSenShVcCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
        	L3_N_TempSenShVcErrCnt_Ct_u16 -=\
                    (uint16)k_S_TempSenShVcCntDecStep_Ct_u8;
        }
        else
        {
        	L3_N_TempSenShVcErrCnt_Ct_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_N_TempSenShVcErrCnt_Ct_u16
            >= k_S_TempSenShVcConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenShVc_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_N_TempSenShVcErrCnt_Ct_u16 == 0)
    {
        /* Clear Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenShVc_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
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
static void FS_L3_TempSenHigh(void)
{
    if (L3_S_MosfetTemp_DegC_G_s16p01 >= k_S_TempSenHighUpLmt_Deg_s16p01)
    {
        if (L3_N_TempSenHighErrCnt_Ct_u16
           < k_S_TempSenHighConfirmCntTh_Ct_u16)
        {
            if (L3_N_TempSenHighErrCnt_Ct_u16
            <= (MAX_UINT16 - (uint16)k_S_TempSenHighCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
            	L3_N_TempSenHighErrCnt_Ct_u16 +=\
                        (uint16)k_S_TempSenHighCntIncStep_Ct_u8;

                if (L3_N_TempSenHighErrCnt_Ct_u16
                   > k_S_TempSenHighConfirmCntTh_Ct_u16)
                {
                	L3_N_TempSenHighErrCnt_Ct_u16 =\
                			k_S_TempSenHighConfirmCntTh_Ct_u16;
                }
            }
            else
            {
            	L3_N_TempSenHighErrCnt_Ct_u16 =\
            			k_S_TempSenHighConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_MosfetTemp_DegC_G_s16p01 <=\
    		  k_S_TempSenHighDnLmt_Deg_s16p01)
    {
        if (L3_N_TempSenHighErrCnt_Ct_u16
           > k_S_TempSenHighCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
        	L3_N_TempSenHighErrCnt_Ct_u16 -=\
                    (uint16)k_S_TempSenHighCntDecStep_Ct_u8;
        }
        else
        {
        	L3_N_TempSenHighErrCnt_Ct_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_N_TempSenHighErrCnt_Ct_u16
            >= k_S_TempSenHighConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenHigh_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_N_TempSenHighErrCnt_Ct_u16 == 0)
    {
        /* Clear Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenHigh_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
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
static void FS_L3_TempSenLow(void)
{
    if (L3_S_MosfetTemp_DegC_G_s16p01 <= k_S_TempSenLowLmt_Deg_s16p01)
    {
        if (L3_N_TempSenLowErrCnt_Ct_u16
           < k_S_TempSenLowConfirmCntTh_Ct_u16)
        {
            if (L3_N_TempSenLowErrCnt_Ct_u16
            <= (MAX_UINT16 - (uint16)k_S_TempSenLowCntIncStep_Ct_u8))
            {
                /* 错误计数器累加 */
            	L3_N_TempSenLowErrCnt_Ct_u16 +=\
                        (uint16)k_S_TempSenLowCntIncStep_Ct_u8;

                if (L3_N_TempSenLowErrCnt_Ct_u16
                   > k_S_TempSenLowConfirmCntTh_Ct_u16)
                {
                	L3_N_TempSenLowErrCnt_Ct_u16 =\
                			k_S_TempSenLowConfirmCntTh_Ct_u16;
                }
            }
            else
            {
            	L3_N_TempSenLowErrCnt_Ct_u16 =\
            			k_S_TempSenLowConfirmCntTh_Ct_u16;
            }
        }
    }
    else if (L3_S_MosfetTemp_DegC_G_s16p01 >=
    		 (k_S_TempSenLowLmt_Deg_s16p01+10))
    {
        if (L3_N_TempSenLowErrCnt_Ct_u16
           > k_S_TempSenLowCntDecStep_Ct_u8)
        {
            /* 错误计数器递减 */
        	L3_N_TempSenLowErrCnt_Ct_u16 -=\
                    (uint16)k_S_TempSenLowCntDecStep_Ct_u8;
        }
        else
        {
        	L3_N_TempSenLowErrCnt_Ct_u16 = 0;
        }
    }
    else
    {
    	/* Do nothing */
    }

    /* 如果错误计数器达到上限 */
    if (L3_N_TempSenLowErrCnt_Ct_u16
            >= k_S_TempSenLowConfirmCntTh_Ct_u16)
    {
        /* Set Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenLow_lgc = TRUE;
    }
    /* 如果错误计数器已清零 */
    else if (L3_N_TempSenLowErrCnt_Ct_u16 == 0)
    {
        /* Clear Fault */
    	L3_S_TempSenDiagResult_Uls_G_Str.TempSenLow_lgc = FALSE;
    }
    else
    {
    	/* Do nothing */
    }
}
#define d_L3TEMPERATUREDIAG_STOP_SEC_CODE
#include "MemMap.h"

/*End of L3_Temperature_Diag.c file*/

