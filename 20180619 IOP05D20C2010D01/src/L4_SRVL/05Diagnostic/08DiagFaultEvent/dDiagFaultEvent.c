/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @Filename:  dDiagFaultEvent.c     
*
* @brief      This file masks all the fault flags of fault detecting moudle.    
*            
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2013/8/20     CODER1       N/A            Original
*     1.1       2013/10/16    CODER1       N/A            1)Add IGN signal err detect logic
*                                                            2)Add Reslv Volt detect logic
*     1.2       2013/10/23    CODER1       N/A            Add Anlge Calibrated err logic
*     1.3       2013/11/06    CODER1       N/A            Add Watchdog reset event detect logic
************************************************************************************************/

#ifndef D_DIAG_FAULT_EVENT_C
#define D_DIAG_FAULT_EVENT_C
#endif

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   *****************************************************************************/
#include   	"dDiagFaultEvent.h"
#include "diag.h"
/* *****************************************************************************
   *****************************************************************************
   Global variable declaration
   *****************************************************************************
   *****************************************************************************/
static INT8U u8_IGNSigErrdebounce; 
FaultFlagUnion_TYPE stc_dDiag_FaultFlg; 

/* *****************************************************************************
   Function:        GetAnglSenorErrInfo
   Description:     Get angle sensor err infomation
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/

__inline static void GetAnglSenorErrInfo(void)
{
   
   /*
    INT8U SteerAngleErr = 0u;
      
    SteerAngleErr = hASDrv_u8GetErrCode();     
         
	if((SteerAngleErr & (AS_AP_SIG_LOST_MSK|AS_AS_SIG_LOST_MSK)) != 0u)
	{
    	gAsSigLostEvt = IN_FAULT;
	}
	else
	{
    	gAsSigLostEvt = NO_FAULT;
	}	
	
	
	if((SteerAngleErr & (AS_AP_PWM_ERR_MSK|AS_AS_PWM_ERR_MSK)) != 0u)
	{
    	gAsSigCharacErrEvt = IN_FAULT;
	}
	else
	{
    	gAsSigCharacErrEvt = NO_FAULT;
	}	
*/
}	
/* *****************************************************************************
   Function:        GetTqSenorErrInfo
   Description:     Get TQ sensor err infomation
   Parameters:      Input:    None
                    Output:   None
   Notes:           
                   
   *****************************************************************************/
__inline static void GetTqSenorErrInfo(void)
{
    /*
    INT8U TqErr = 0u;
    TqErr = hTSDrv_u8GetErrCode();
    
	if((TqErr & (TS_TP_SIG_LOST_MSK|TS_TS_SIG_LOST_MSK)) != 0u)
	{
       gTsSigLostEvt = IN_FAULT;
	}
	else
	{
       gTsSigLostEvt = NO_FAULT;
	}	
	
	if((TqErr & (TS_TX_CHK_FREQ_MSK|TS_TX_CHK_DUTY_MSK|TS_TX_CHK_SYNC_MSK)) != 0u)
	{
       gTsSigCharacErrEvt	= IN_FAULT;
	}
	else
	{
       gTsSigCharacErrEvt	= NO_FAULT;
	}
	*/
}

/* *****************************************************************************
   Function:        GetMcuMalFncInfo
   Description:     Get MCU error information
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetMcuMalFncInfo(void)
{
	/*
   if((0 == u8ClockErr)||(SBC_EPS_WDT_OVT_RST == hSBC_vGetResetEvents()))
   {
   	   gMcuMalfunErrEvt = IN_FAULT;
   }
   else
   {
   	   gMcuMalfunErrEvt = NO_FAULT;
   }
   */
}

/* *****************************************************************************
   Function:        GetEEPROMErrInfo
   Description:     Get E2 error information
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetEEPROMErrInfo(void)
{
   /*gEEPROMErrEvt = ;*/
}

/* *****************************************************************************
   Function:        GetFlhRamErrInfo
   Description:     Get Flash Error information
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetFlhRamErrInfo(void)
{
   /*gFlhRamErrEvt = ;*/
}

/* *****************************************************************************
   Function:        GetClbErrInfo
   Description:     Ger calibration data error information	
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetClbErrInfo(void)
{
   //gClbDataErrEvt = u8ClbDataErr;
}
/* *****************************************************************************
   Function:        GetChargeErrInfo
   Description:     Get Charge error information
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetChargeErrInfo(void)
{
	/*
   if((u8ChargeSt == _HPOWER_FLAG_CHARGE_FAIL) || (u8ChargeSt == _HPOWER_FLAG_RELAY_FAIL))
   {  
       gChargeErrEvt = IN_FAULT;
   }   
   else
   {
       gChargeErrEvt = NO_FAULT;   	
   }
   */
}

/* *****************************************************************************
   Function:        GetVoltErrInfo
   Description:     Get Volt error infomation
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetVoltErrInfo(void)
{
	/*
   switch(hVoltageMonitor_vGetBatSt())
   {
   	case BAT_HIGH   :
   	{
   	    gLowVoltErrEvt    = NO_FAULT;
   	    gHighVoltErrEvt   = IN_FAULT;
   	    gReduceVoltErrEvt = NO_FAULT;
   	    
   		break;
   	}
   	case BAT_NORMAL :
   	{
   	    gLowVoltErrEvt    = NO_FAULT;
   	    gHighVoltErrEvt   = NO_FAULT;
   		gReduceVoltErrEvt = NO_FAULT;
   		
   		break;
   	}
   	case BAT_RD_PWR :
   	{
   	    gLowVoltErrEvt    = NO_FAULT;
   	    gHighVoltErrEvt   = NO_FAULT;
   	    gReduceVoltErrEvt = IN_FAULT;
   	
   		break;
   	}
   	case BAT_LOW    :
   	{
   	
   	    gLowVoltErrEvt    = IN_FAULT;
   	    gHighVoltErrEvt   = NO_FAULT;
   	    gReduceVoltErrEvt = NO_FAULT;
   	
   		break;
   	}
   	default:
   	{
   		
   	}
   	
   	
   }
   
   // TAS power supply status //
   if(hVoltageMonitor_vGetSensor5vSt() == SENSOR_5V_NORMAL)
   {
   	  gTasPowerErrEvt = NO_FAULT;
   }
   else
   {
   	  gTasPowerErrEvt = IN_FAULT;
   }

   // ReslvVolt power supply status //
   if(hVoltageMonitor_vGetRslvPowerSt() == RSLV_POWER_NORMAL)
   {
   	  gMotReslvErrEvt = NO_FAULT;
   }
   else
   {
   	  gMotReslvErrEvt = IN_FAULT;
   }
   
   */
}

/* *****************************************************************************
   Function:        GetTempErrInfo
   Description:     Ger Tempurature error Information
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetTempErrInfo(void)
{
	/*
	if(TEMP_NORMAL == hTemp_vGetTempDiagState())
	{
		gReduceTempErrEvt =  NO_FAULT; 
    	gOverTempErrEvt =  NO_FAULT;  	
	}
	else if(TEMP_HIGH_1 == hTemp_vGetTempDiagState())
	{
		gReduceTempErrEvt =  IN_FAULT; 
    	gOverTempErrEvt =  NO_FAULT;  
   	}
	else if(TEMP_HIGH_2 == hTemp_vGetTempDiagState())
	{
		gReduceTempErrEvt =  NO_FAULT; 
    	gOverTempErrEvt =  IN_FAULT;  		
	}
	else
	{
		
	}
	*/
}
/* *****************************************************************************
   Function:        GetIGNSignalErrInfo
   Description:     Get Ignition key error information
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetIGNSignalErrInfo(void)
{
    /*
    if( SYS_IGN_STATE == IGN_OFF )
    {
       if(0u == gEMSErrEvt)
       {
       	   u8_IGNSigErrdebounce++;
       }
       else
       {
       	   u8_IGNSigErrdebounce = 0u; 
       	   gIgnSigErrEvt = 0u;       	   
       }
       
       if(IGN_ERR_DEBOUNCE_TIME <= u8_IGNSigErrdebounce)
       {
       	   gIgnSigErrEvt = 1u;
       	   u8_IGNSigErrdebounce = 0u; 
       }
       else
       {
       	   ;
       }
    }
    else
    {
    	gIgnSigErrEvt = 0u;
    }
      */
}

/* *****************************************************************************
   Function:        GetAngleCalibrErrInfo
   Description:     Get Angle Calibrate Error information
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void GetAngleCalibrErrInfo(void)
{  
/*
    if((ANGLE_CAL_OK == hAngCal_vGetAngleCalSt())&&(ANGLE_MECH_OK == hAngCal_vGetAngleMechSt()))
    {
        gAglValueErrEvt = NO_FAULT;
    }
    else
    {
    	gAglValueErrEvt = IN_FAULT;
    }
    */
}


/* *****************************************************************************
   Function:        dDiag_vGetInitErrInfo
   Description:     Get init process error information	
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   *****************************************************************************/
void dDiag_vGetInitErrInfo(void) 
{
	GetMcuMalFncInfo();
	GetClbErrInfo();
}
/* *****************************************************************************
   Function:        dDiag_vGetRuntimeErrInfo
   Description:     Get all the runtime error information
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   *****************************************************************************/
void dDiag_vGetRuntimeErrInfo(void) 
{
	

	gbLV12UnderErrEvt   = faultCodeMoreTag.bit.bLV12VUnderFault;
	gbLV12OverErrEvt    = faultCodeMoreTag.bit.bLV12VOverFault ;  		
	gbLV13UnderErrEvt   = faultCodeMoreTag.bit.bLV13VUnderFault;	
	gbLV13OverErrEvt    = faultCodeMoreTag.bit.bLV13VOverFault;  		
	gbINPUT_RelayErrEvt = faultCodeTag.bit.	bINPUT_Relay;
	gboutputCurrentSenErrorEvt  = faultCodeTag.bit.	boutputCurrentSenError;
	gbPG_SENSErrorEvt      	= faultCodeTag.bit.	bPG_SENS;
	gbOverPFCUoutVoltErrEvt = faultCodeTag.bit.	bOverPFCUoutVolt; 
	gbHWDCDC_OCPErrEvt     = faultCodeTag.bit.	bHWDCDC_OCP;  	
	gbOverDCUoutVoltErrEvt  = faultCodeTag.bit.	bOverDCUoutVolt;  	    
	gbDCDCPrechargeTimeoutErrEvt = faultCodeMoreTag.bit.bDCDCPrechargeTimeout;  	    
	gbPFCBoostFailErrEvt  = faultCodeTag.bit.bPFCBoostFail ;  	       	
	gbOverPFCUoutIErrEvt =     faultCodeTag.bit.bOverPFCUoutI ; 	
	gbOverUinVoltErrEvt     = faultCodeTag.bit.bOverUinVolt ; 	 	
	gbUnderUinVoltErrEvt = faultCodeTag.bit.bUnderUinVolt ; 	 	     	
	//gbUinVoltOpenErrEvt  = faultCodeTag.bit.bUinVoltOpen;    
	gbUinVoltOpenErrEvt  = FALSE;//¶Ïµç¹ÊÕÏ½ûÖ¹    	
	gbUnderDCUoutVoltErrEvt = faultCodeTag.bit.bUnderDCUoutVolt;      	
	gbTempWarinOutOffErrEvt = faultCodeTag.bit.bTempWarinOutOff;     
	gbOverTempCoolErrEvt = faultCodeTag.bit.bOverTempCool;      	
	gbCANBUSOFFErrEvt    = faultCodeTag.bit.bCANBUSOFF;   	
	gbCANMissingErrEvt    = faultCodeTag.bit.bCANMissing;   	




/*
	gMotCtrlErrEvt = hMDIAG_u8GetMotoSt();
	gMotPosErrEvt =  hMDIAG_u8GetPosSensSt();
	gMotPreDrvErrEvt = hMDIAG_u8GetGateDrvSt();
	gMotCurrErrEvt =   hMDIAG_u8GetCurrSensSt();
	
	gEMSErrEvt = hCanSig_u8GetDiag_RxEMS1_Flg();
	gESPErrEvt =(hCanSig_u8GetDiag_RxESP3_Flg() | hCanSig_u8GetVehicleSpeedFlag());
	gBusOffEvt = hCanBus_u8GetBusOffState();

    GetAnglSenorErrInfo();
    GetTqSenorErrInfo();  
    GetAngleCalibrErrInfo();
	GetChargeErrInfo();
	GetVoltErrInfo();
	GetTempErrInfo();
	GetIGNSignalErrInfo();
	
	GetEEPROMErrInfo();
	GetFlhRamErrInfo();
*/
}

/* *****************************************************************************
   Function:        dDiag_vFaultFlagInit
   Description:     init all the fault flags
   Parameters:      Input:    None
                    Output:   None
   Notes:           called when initilization,
                    it should be called before initilization-detect task.
                  
   *****************************************************************************/

void dDiag_vFaultFlagInit(void) 
{
    INT16U i = 0;
  
	for(i=0;i<DTC_NUMBER_SIZE;i++)
	{	
       stc_dDiag_FaultFlg.FaultFlagArray[i] = 0u;	   
	} 
	
    u8ClockErr = 1u;    
    u8ClbDataErr = E_OK;     
    u8AbnormalReset = E_OK;
    u8ChargeSt = E_OK;
    
    u8_IGNSigErrdebounce = 0u; /*used in IgnSigErr detect function,not an err flag*/

}




/* *****************************************************************************
   Function:        dDiag_vFaultClear
   Description:     clear all the fault and timer
   Parameters:      Input:    None
                    Output:   None
   Notes:           called when 14 hex sevice ,
                    it should be called Dtc_Status_14Service_Hook.
                  
   *****************************************************************************/

void dDiag_vFaultClear(void) 
{
	L3_S_BMSMsgTimeOut_Uls_G_u08 = FALSE;
	L3_CanBusOff_error_Ct_u8 = FALSE;
    (void) memset((void *)&faultCodeTag, 0,sizeof(faultCodeTag));
	(void) memset((void *)&faultCodeMoreTag, 0,sizeof(faultCodeMoreTag));
	(void) memset((void *)&diagCtrlTag, 0,sizeof(diagCtrlTag));
	(void) memset((void *)&diagRecoverTag, 0,sizeof(diagRecoverTag));
  

}
/*********************************************** End ************************************************/

