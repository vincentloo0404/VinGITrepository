/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"
#include "L4_FaultManager.h"

/*
#include "L3_ECU_Diagnosis.h"
#include "L3_CAN.h"

#include "L4_SrvlFailSafe_CalData.h"
*/
#include "L4_DTC.h"
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
static void FM_L4_L2McalInit(void);
static void FM_L4_L3EcalInit(void);
static void FM_L4_L4SrvlInit(void);
static void FM_L4_L5ApplInit(void);
static inline void FM_L4_EPSFaultBitCfm(void);

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
#define d_L4FAULTMANAGER_START_SEC_VAR
#include "MemMap.h"

static uint16 L3_N_EPSFaultBitCnt_Ct_G_u16 = 0;

#define d_L4FAULTMANAGER_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L4FAULTMANAGER_START_SEC_VAR
#include "MemMap.h"

FM_SystemFault_Enu L4_S_SysFaultState_Uls_G_Enu;

#define d_L4FAULTMANAGER_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4FAULTMANAGER_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     void FailSafeCtrl_L5_Init(void)
*
*   Description:  This function is use to Initial the failsafe control module
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FM_L4_ColdInit(void)
{
    /* Failsafe fun disable */
    if (k_S_FailsafeEn_Uls_G_u8 == 0)
    {
    	L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
    }    
    else
    {
    	if ((DTC_L4_GetErrorStaB1(e_FAULT_UNEXP_EVENT_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_CLOCK_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_STKFLOW_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_RAM_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_FLASH_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKLOOP_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKFREQ_ERR) == TRUE)
    	 ||	(DTC_L4_GetErrorStaB1(e_FAULT_ADC_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_SPI1_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_SPI2_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_EEPROM_OPR_ERR) == TRUE))
    	{
    	    L4_S_SysFaultState_Uls_G_Enu = System_F1_Fault;
    	}
    	else
    	{
    		L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
    	}
    }
}
/*****************************************************************************
*
*   Function:     void FailSafeCtrl_L5_Init(void)
*
*   Description:  This function is use to Initial the failsafe control module
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FM_L4_WarmInit(void)
{
    /* Failsafe fun disable */
    if (k_S_FailsafeEn_Uls_G_u8 == 0)
    {
    	L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
    }    
    else
    {
    	if ((DTC_L4_GetErrorStaB1(e_FAULT_UNEXP_EVENT_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKLOOP_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKFREQ_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_ADC_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MONITOR_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_RELAYON_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_PRECHARGEON_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_UNDERVOLT_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_SHORTCIR_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_OVERVTEMP) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_HBRIDGE_CUTOFF_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TEMP_EXDLIM_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TEMP_SEN_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_SEN_TRIM_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_SENSOR_BAT_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_HALL_EXDLIM_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_RSLV_AMP_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_HALL_OPEN_ERR) == TRUE)
    	 )
    	{
    	    L4_S_SysFaultState_Uls_G_Enu = System_F1_Fault;
    	}
		else if ((DTC_L4_GetErrorStaB1(e_FAULT_T1_OPEN_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T1FRE_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T1DUTY_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T2_OPEN_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T2FRE_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T2DUTY_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T1T2_SYNC_ERR) == TRUE))
		      
    	{
    		L4_S_SysFaultState_Uls_G_Enu = System_F2_Fault;
    	}
        else if ((DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_OFF_ERR) == TRUE)
              || (DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_LOW_ERR) == TRUE)
              || (DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_HIGH_ERR) == TRUE))
        {
            L4_S_SysFaultState_Uls_G_Enu = System_F3_Fault;
        }
    	else
    	{
    		L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
    	}
    }
}
/*****************************************************************************
*
*   Function:     void FailSafeCtrl_L5_Per(void)
*
*   Description:  This function is use for the period failsafe control module 
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FM_L4_Per(void)
{
    /* Failsafe fun disable */
    if (k_S_FailsafeEn_Uls_G_u8 == 0)
    {
    	L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
    }    
    else
    {
    	if ((DTC_L4_GetErrorStaB1(e_FAULT_UNEXP_EVENT_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKLOOP_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKFREQ_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_ADC_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MONITOR_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_UNDERVOLT_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_SHORTCIR_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_OVERVTEMP) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_HBRIDGE_CUTOFF_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_SENSOR_BAT_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MTRVOLT_CUTOFF_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_UNREASONABLE_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_NOBALANCE_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_OVER_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_OPEN_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_HALL_EXDLIM_ERR) == TRUE)
    	 || (DTC_L4_GetErrorStaB1(e_FAULT_RSLV_AMP_ERR) == TRUE)
    	 )
    	{
    	    L4_S_SysFaultState_Uls_G_Enu = System_F1_Fault;
    	}
		else if ((DTC_L4_GetErrorStaB1(e_FAULT_T1_OPEN_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T1FRE_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T1DUTY_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T2_OPEN_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T2FRE_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T2DUTY_OUTRANGE_ERR) == TRUE)
		      || (DTC_L4_GetErrorStaB1(e_FAULT_T1T2_SYNC_ERR) == TRUE))
    	{
    		L4_S_SysFaultState_Uls_G_Enu = System_F2_Fault;
    	}
        else if ((DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_OFF_ERR) == TRUE)
              || (DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_LOW_ERR) == TRUE)
              || (DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_HIGH_ERR) == TRUE))
        {
            L4_S_SysFaultState_Uls_G_Enu = System_F3_Fault;
        }
		else if ((DTC_L4_GetErrorStaB0(e_FAULT_TEMP_EXDLIM_ERR) == TRUE)
			  || (DTC_L4_GetErrorStaB0(e_FAULT_CAN_BUSOFF_ERR) == TRUE)
			  )
        {
            L4_S_SysFaultState_Uls_G_Enu = System_F4_Fault;
        }
    	else
    	{
    		L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
    	}
    	
    	FM_L4_EPSFaultBitCfm();
    }
}
/*****************************************************************************
*
*   Function:     void FailSafeCtrl_L5_Init(void)
*
*   Description:  This function is use to Initial the failsafe control module
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void FM_L4_ShutDown(void)
{
    /* 如果Failsafe功能被使能 */
    if (k_S_FailsafeEn_Uls_G_u8 == 0)
    {
    	L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
    }
	else
	{
		if((L4_S_SysFaultState_Uls_G_Enu != System_F1_Fault)\
		&& (L4_S_SysFaultState_Uls_G_Enu != System_F2_Fault))
		{
			if ((DTC_L4_GetErrorStaB1(e_FAULT_UNEXP_EVENT_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKLOOP_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_TASKFREQ_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_ADC_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_MONITOR_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_UNDERVOLT_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_SHORTCIR_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_PREDRV_OVERVTEMP) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_HBRIDGE_CUTOFF_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_SENSOR_BAT_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_MTRVOLT_CUTOFF_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_UNREASONABLE_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_NOBALANCE_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_OVER_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_MOTCUR_OPEN_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_HALL_EXDLIM_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_RSLV_AMP_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_HALL_OPEN_ERR) == TRUE)
			 || (DTC_L4_GetErrorStaB1(e_FAULT_RSLV_VCC_ERR) == TRUE)
			 )
			{
			    L4_S_SysFaultState_Uls_G_Enu = System_F1_Fault;
			}
			else if ((DTC_L4_GetErrorStaB1(e_FAULT_T1_OPEN_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB1(e_FAULT_T1FRE_OUTRANGE_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB1(e_FAULT_T1DUTY_OUTRANGE_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB1(e_FAULT_T2_OPEN_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB1(e_FAULT_T2FRE_OUTRANGE_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB1(e_FAULT_T2DUTY_OUTRANGE_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB1(e_FAULT_T1T2_SYNC_ERR) == TRUE))
			{
				L4_S_SysFaultState_Uls_G_Enu = System_F2_Fault;
			}
			else if ((DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_OFF_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_LOW_ERR) == TRUE)
			      || (DTC_L4_GetErrorStaB0(e_FAULT_BATVOLT_HIGH_ERR) == TRUE))
			{
			    L4_S_SysFaultState_Uls_G_Enu = System_F3_Fault;
			}
			else if ((DTC_L4_GetErrorStaB0(e_FAULT_TEMP_EXDLIM_ERR) == TRUE)
				  || (DTC_L4_GetErrorStaB0(e_FAULT_CAN_BUSOFF_ERR) == TRUE)
				  )
			{
			    L4_S_SysFaultState_Uls_G_Enu = System_F4_Fault;
			}
			else
			{
				L4_S_SysFaultState_Uls_G_Enu = System_No_Fault;
			}
		}
	}

    FM_L4_EPSFaultBitCfm();
}
/*****************************************************************************
*
*   Function:     void FM_L4_L2McalInit(void)
*
*   Description:  该函数初始化Fault Manager中与L2层相关的内容
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FM_L4_L2McalInit(void)
{

    DTC_L4_ClrError(e_FAULT_UNEXP_EVENT_ERR);
    DTC_L4_ClrError(e_FAULT_CLOCK_ERR);
    DTC_L4_ClrError(e_FAULT_STKFLOW_ERR);
    DTC_L4_ClrError(e_FAULT_RAM_ERR);
    DTC_L4_ClrError(e_FAULT_FLASH_ERR);
    DTC_L4_ClrError(e_FAULT_TASKLOOP_ERR);
    DTC_L4_ClrError(e_FAULT_TASKFREQ_ERR);
    DTC_L4_ClrError(e_FAULT_ADC_ERR);
    DTC_L4_ClrError(e_FAULT_SPI1_ERR);
    DTC_L4_ClrError(e_FAULT_SPI2_ERR);
    DTC_L4_ClrError(e_FAULT_EEPROM_OPR_ERR);
    

#if 0
	DTC_L4_ClrError(e_FAULT_OSCWDT_TRAP);
	DTC_L4_ClrError(e_FAULT_VCOLCK_TRAP);

	DTC_L4_ClrError(e_FAULT_ALU_RUN);
	DTC_L4_ClrError(e_FAULT_ADC_RUN);

	DTC_L4_ClrError(e_FAULT_U0C1_RUN);
	DTC_L4_ClrError(e_FAULT_U1C0_RUN);

	/* unexpected event */
	if ((ECU_Diag_Str.MCUFaultCode.IllegalIRQFaultCode == Illegal_Irq_On)\
	|| ((ECU_Diag_Str.MCUFaultCode.ResetFaultCode == Unexpected_Reset)\
	 && (ECU_Diag_Str.MCUFaultCode.STKOF_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.STKUF_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.SOFTBRK_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.ACER_FAT_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.ACER_RAT_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.ACER_PET_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.ACER_ECCT_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.UNDOPC_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.PRTFLT_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.ILLOPA_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.MPR_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.MPW_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.MPX_Trap == Trap_Off)\
	 && (ECU_Diag_Str.MCUFaultCode.SystemFreqFaultCode == SystemFreq_No_Error)))
	{
	    DTC_L4_SetError(e_FAULT_UNEXPECTED_EVENT);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_UNEXPECTED_EVENT);
	}

	/* external oscillator */
	if (ECU_Diag_Str.MCUFaultCode.ExtOSCFaultCode != CGU_No_Error)
	{
	    DTC_L4_SetError(e_FAULT_EXTOSC_INI);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_EXTOSC_INI);
	}

	/* internal oscillator */
	if (ECU_Diag_Str.MCUFaultCode.IntOSCFaultCode != CGU_No_Error)
	{
	    DTC_L4_SetError(e_FAULT_INTOSC_INI);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_INTOSC_INI);
	}

	/* stack flow */
	if ((ECU_Diag_Str.MCUFaultCode.STKOF_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.STKUF_Trap == Trap_On))
	{
	    DTC_L4_SetError(e_FAULT_STKFLOW_TRAP);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_STKFLOW_TRAP);
	}

	/* software break */
	if (ECU_Diag_Str.MCUFaultCode.SOFTBRK_Trap == Trap_On)
	{
	    DTC_L4_SetError(e_FAULT_SOFTBRK_TRAP);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_SOFTBRK_TRAP);
	}

	/* access register */
	if ((ECU_Diag_Str.MCUFaultCode.ACER_FAT_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.ACER_RAT_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.ACER_PET_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.ACER_ECCT_Trap == Trap_On))
	{
	    DTC_L4_SetError(e_FAULT_ACER_TRAP);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_ACER_TRAP);
	}

	/* illegal operation */
	if ((ECU_Diag_Str.MCUFaultCode.UNDOPC_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.PRTFLT_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.ILLOPA_Trap == Trap_On))
	{
	    DTC_L4_SetError(e_FAULT_ILLOPT_TRAP);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_ILLOPT_TRAP);
	}

	/* MPU CFG */
	if (ECU_Diag_Str.MCUFaultCode.MPUFaultCode != MPU_No_Error)
	{
	    DTC_L4_SetError(e_FAULT_MPU_INI);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_MPU_INI);
	}

	/* MPU Trap */
	if ((ECU_Diag_Str.MCUFaultCode.MPR_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.MPW_Trap == Trap_On)\
	 || (ECU_Diag_Str.MCUFaultCode.MPX_Trap == Trap_On))
	{
	    DTC_L4_SetError(e_FAULT_MPU_TRAP);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_MPU_TRAP);
	}

	/* ALU CFG */
	if (ECU_Diag_Str.MCUFaultCode.ALUFaultCode != ALU_No_Error)
	{
	    DTC_L4_SetError(e_FAULT_ALU_INI);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_ALU_INI);
	}

	/* SBRAM CFG */
	if (ECU_Diag_Str.MCUFaultCode.SBRAMFaultCode != SBRAM_No_Error)
	{
	    DTC_L4_SetError(e_FAULT_SBRAM_INI);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_SBRAM_INI);
	}

	/* RAM CFG */
	if (ECU_Diag_Str.MCUFaultCode.RAMFaultCode != RAM_No_Error)
	{
	    DTC_L4_SetError(e_FAULT_RAM_INI);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_RAM_INI);
	}

	/* SYS FREQ */
	if (ECU_Diag_Str.MCUFaultCode.SystemFreqFaultCode != SystemFreq_No_Error)
	{
	    DTC_L4_SetError(e_FAULT_TASKFREQ_TRAP);
	}
	else
	{
	    DTC_L4_ClrError(e_FAULT_TASKFREQ_TRAP);
	}
	
	#endif
}
/*****************************************************************************
*
*   Function:     void FM_L4_L3EcalInit(void)
*
*   Description:  该函数初始化Fault Manager中与L3层相关的内容
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FM_L4_L3EcalInit(void)
{

    DTC_L4_ClrError(e_FAULT_MONITOR_ERR);
    DTC_L4_ClrError(e_FAULT_POWEROFF_ERR);
    DTC_L4_ClrError(e_FAULT_RELAYON_ERR);
    DTC_L4_ClrError(e_FAULT_RELAYOFF_ERR);
    DTC_L4_ClrError(e_FAULT_PRECHARGEON_ERR);
    DTC_L4_ClrError(e_FAULT_PREDRV_UNDERVOLT_ERR);
    DTC_L4_ClrError(e_FAULT_PREDRV_SHORTCIR_ERR);
    DTC_L4_ClrError(e_FAULT_PREDRV_OVERVTEMP);
    DTC_L4_ClrError(e_FAULT_HBRIDGE_CUTOFF_ERR);
    DTC_L4_ClrError(e_FAULT_TEMP_EXDLIM_ERR);
    DTC_L4_ClrError(e_FAULT_TEMP_SEN_ERR);
    DTC_L4_ClrError(e_FAULT_SENSOR_BAT_ERR);
    DTC_L4_ClrError(e_FAULT_T1_OPEN_ERR);
    DTC_L4_ClrError(e_FAULT_T1FRE_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_T1DUTY_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_T2_OPEN_ERR);
    DTC_L4_ClrError(e_FAULT_T2FRE_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_T2DUTY_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_T1T2_SYNC_ERR);
    DTC_L4_ClrError(e_FAULT_AP_OPEN_ERR);
    DTC_L4_ClrError(e_FAULT_APFRE_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_APDUTY_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_AS_OPEN_ERR);
    DTC_L4_ClrError(e_FAULT_ASFRE_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_ASDUTY_OUTRANGE_ERR);
    DTC_L4_ClrError(e_FAULT_TRQ_NOTTRIM_ERR);
    DTC_L4_ClrError(e_FAULT_HWPOS_NOTTRIM_ERR);
    DTC_L4_ClrError(e_FAULT_BATVOLT_OFF_ERR);
    DTC_L4_ClrError(e_FAULT_BATVOLT_LOW_ERR);
    DTC_L4_ClrError(e_FAULT_BATVOLT_HIGH_ERR);
    DTC_L4_ClrError(e_FAULT_ENGSTS_LOST_ERR);
    DTC_L4_ClrError(e_FAULT_ENGSTS_INVALID_ERR);
    DTC_L4_ClrError(e_FAULT_VEHSPD_LOST_ERR);
    DTC_L4_ClrError(e_FAULT_VEHSPD_INVALID_ERR);
    DTC_L4_ClrError(e_FAULT_CAN_BUSOFF_ERR);
    DTC_L4_ClrError(e_FAULT_MOTCUR_SEN_TRIM_ERR);
    DTC_L4_ClrError(e_FAULT_MTRVOLT_CUTOFF_ERR);
    DTC_L4_ClrError(e_FAULT_MOTCUR_UNREASONABLE_ERR);
    DTC_L4_ClrError(e_FAULT_MOTCUR_NOBALANCE_ERR);
    DTC_L4_ClrError(e_FAULT_MOTCUR_OVER_ERR);
    DTC_L4_ClrError(e_FAULT_MOTCUR_OPEN_ERR);
    DTC_L4_ClrError(e_FAULT_HALL_EXDLIM_ERR);
    DTC_L4_ClrError(e_FAULT_RSLV_AMP_ERR);
    DTC_L4_ClrError(e_FAULT_RSLV_VCC_ERR);

}
/*****************************************************************************
*
*   Function:     void FM_L4_L4SrvlInit(void)
*
*   Description:  该函数初始化Fault Manager中与L4层相关的内容
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FM_L4_L4SrvlInit(void)
{
#if 0

	DTC_L4_ClrError(e_FAULT_TASKLOOP_RUN);
	DTC_L4_ClrError(e_FAULT_MONITOR_RUN);

	DTC_L4_ClrError(e_FAULT_EEPROM_SAVE_RUN);

	/* EEPROM */
	if(ECU_Diag_Str.EEPROMFaultCode != EEPROM_No_Error)
	{
		DTC_L4_SetError(e_FAULT_EEPROM_INTG_EXT);
	}
	else
	{
		DTC_L4_ClrError(e_FAULT_EEPROM_INTG_EXT);
	}

	#endif
}
/*****************************************************************************
*
*   Function:     void FM_L4_L5ApplInit(void)
*
*   Description:  该函数初始化Fault Manager中与L5层相关的内容
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void FM_L4_L5ApplInit(void)
{

}
/*****************************************************************************
*
*   Function:     void FM_L4_L5ApplInit(void)
*
*   Description:  该函数初始化Fault Manager中与L5层相关的内容
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static inline void FM_L4_EPSFaultBitCfm(void)
{
	if((L4_S_SysFaultState_Uls_G_Enu == System_F1_Fault)
	|| (L4_S_SysFaultState_Uls_G_Enu == System_F2_Fault))
	{
		L3_S_EPS_EPSFault_Ct_G_u08 = STD_ON;
		L3_N_EPSFaultBitCnt_Ct_G_u16 = 0;
	}
	else
	{
		if(L4_S_SysFaultState_Uls_G_Enu == System_No_Fault)
		{
			L3_S_EPS_EPSFault_Ct_G_u08 = STD_OFF;
			L3_N_EPSFaultBitCnt_Ct_G_u16 = 0;
		}
		else
		{
			L3_N_EPSFaultBitCnt_Ct_G_u16++;
			if(L3_N_EPSFaultBitCnt_Ct_G_u16 >= 500U)
			{
				L3_S_EPS_EPSFault_Ct_G_u08 = STD_ON;
				L3_N_EPSFaultBitCnt_Ct_G_u16 = 0;
			}
		}
	}
}
#define d_L4FAULTMANAGER_STOP_SEC_CODE
#include "MemMap.h"

/* End of L4_FaultManager.c file */