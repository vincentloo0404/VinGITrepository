/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     dDiagDec
*
* @brief    Fault events diag decision.
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/06/24     ----        N/A          Original
*     1.1	     2013/07/25		CODER1	  N/A		   Recoding according to requirements disscussion
*     1.2        2013/08/15     CODER1	  N/A          Add the assit logic and Sleep logic according to MANDO
*     1.3        2013/08/27     CODER1     N/A          1).discard the VehSpd signal invalid detecting, the info will 
*                                                             be contained in ESPMSG Err info.
*                                                          2).Add function dDiagDec_vGetRawSignalValue();
*     1.4        2013/08/30     CODER1     N/A          Mask fault event info.
*     1.5        2013/09/02     CODER1     N/A          Add motor Acce spd signal, use kalman filter for motspd and Accspd
*     1.6        2013/09/09     CODER1	  N/A          1) Add function for process Can Comm logic;
*                                                          2) Add SetSleepIndication() function
*                                                          3) update PreShutDown & PreSleep logic;
*                                                          4) update FaultLamp Logic
*     1.7        2013/10/16     CODER1     N/A          Add Angle Calibration Err detect and update AngleValue get logic
*     1.8        2013/10/18     CODER1	  N/A          update CAN comm logic
*     1.9        2013/11/05     CODER1     N/A          1) Add limit-condition for some diag-service
*                                                          2) Update Angle Speed signal process logic
*******************************************************************************/
#ifndef D_DIAGDEC_C
#define D_DIAGDEC_C
#endif

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include 	"dDiagDec.h"
#include "my_all.h"

/*******************************************************************************
* declaration of internal variables
********************************************************************************/
static INT16U u16_EngineRunCnt;

//static GFLIB_RAMP_T EpsVehRepRamp;

//static KfParaType_32Bit stc_MotSpd_Sig;

static INT8U PreRunFlg; 

static INT8U  u8_StartAssitDelayCount;
static INT16U u16_AssitDelayCounter; 
static INT32U u32_SleepDelayCounter;
static INT16U RampEntryFlag;

/*******************************************************************************
* Prototypes of internal functions
********************************************************************************/
static void dDiagDec_vFaultLevelOutput(void);   
static void dDiagDec_vSignalFilterLogic(void);
static void dDiagDec_vEnableAssitLogic(void);
static void dDiagDec_vPreShutdownLogic(void);
static void dDiagDec_vCanCommLogic(void);
static void dDiagDec_vPreSleepLogic(void);
static void dDiagDec_vGetRawSignalValue(void);
static void dDiagDec_vSetSleepIndication(void);

static void dDiagDec_vGetSlaveState(void);
/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */
/* *****************************************************************************
   Function:        dDiagDec_vInit
   Description:     signal diagnostic init 
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   ***************************************************************************** */
void dDiagDec_vInit(void)
{


	SYS_IGN_STATE = IGN_ON;
	SYS_FAULT_LEVEL = FAULT_LEVEL_OK;
	
	SYS_FAULT_LAMP_FLG  = FAULT_LAMP_ON;
	
	SYS_MSG_SND_FLG = SEND_ENABLE;
	
	SYS_MSG_REC_FLG = RECIVE_ENABLE;
	RampEntryFlag = 0u;
	SYS_bLV12UnderErr   = NO_FAULT;		
	SYS_bLV12OverErr   	= NO_FAULT;	
	SYS_bLV13UnderErr   = NO_FAULT;		
	SYS_bLV13OverErr  	= NO_FAULT;	
	SYS_bINPUT_RelayErr   = NO_FAULT;	
	SYS_boutputCurrentSenError   = NO_FAULT;
	SYS_bPG_SENSError   = NO_FAULT;		
	SYS_bOverPFCUoutVoltErr  = NO_FAULT;	
	SYS_bHWDCDC_OCPErr  = NO_FAULT;		
	SYS_bOverDCUoutVoltErr   = NO_FAULT;	
	SYS_bDCDCPrechargeTimeoutErr = NO_FAULT;
	SYS_bPFCBoostFailErr  	= NO_FAULT;
	SYS_bOverPFCUoutIErr   	= NO_FAULT;
	SYS_bOverUinVoltErr   = NO_FAULT;	
	SYS_bUnderUinVoltErr   	= NO_FAULT;
	SYS_bUinVoltOpenErr   	= NO_FAULT;
	SYS_bUnderDCUoutVoltErr   = NO_FAULT;
	SYS_bTempWarinOutOffErr   = NO_FAULT;
	SYS_bOverTempCoolErr   	= NO_FAULT;
	SYS_BUSOFF_ERR       = NO_FAULT; 	
	SYS_BMS04MSG_ERR     = NO_FAULT; 	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	
     //error init 
	EPS_MCUMAL_ERR  = NO_FAULT;
	
	EPS_FLSHRAM_ERR = NO_FAULT;
	EPS_EEP_ERR = NO_FAULT;
	EPS_SYSVOLT_ERR = NO_FAULT;
	EPS_REDUCE_VOLT_ERR = NO_FAULT;
	
	SYS_BUSOFF_ERR = NO_FAULT;
	
	EPS_CLBDATA_ERR = NO_FAULT;
	
	EPS_ESP3MSG_ERR = NO_FAULT;
	EPS_EMS1MSG_ERR = NO_FAULT;

	EPS_MOTOR_POS_ERR = NO_FAULT;
	EPS_MOTOR_PREDRV_ERR = NO_FAULT;
	EPS_MOTOR_CTRL_ERR = NO_FAULT;
	EPS_MOTOR_CURR_ERR = NO_FAULT;
	EPS_RESLV_VOLT_ERR = NO_FAULT;
		 
	EPS_TQSENSOR_ERR = NO_FAULT;

	EPS_ANGLE_ERR = NO_FAULT;
	
	EPS_STEER_ANGLE_CAL_ERR = NO_FAULT;
	
	EPS_CHARG_ERR = NO_FAULT;
	
	EPS_REDUCE_TEMP_ERR = NO_FAULT;
    EPS_OVER_TEMP_ERR = NO_FAULT;
    
    EPS_IGN_ERR = NO_FAULT;
	// signal init //
	EPS_VEH_SPD_RAW = 0;
	EPS_ENG_SPD_RAW = 0;
	
	EPS_ANGLE_CMD_CODE = 0u;
	
	EPS_STEER_ANGLE_RAW = 0;
	EPS_STEER_ANGLE_SPD_RAW = 0;
	
	EPS_MOT_SPD_RAW = 0;		
	EPS_VEH_SPD_FLT = 0;
	EPS_ENG_SPD_FLT = 0;
	
	EPS_STEER_ANGLE_FLT = 0;
	EPS_STEER_ANGLE_SPD_FLT = 0;
	
	EPS_MOT_SPD_FLT = 0;
	
	SYS_IGN_STATE = IGN_ON;
	
	EPS_VEH_SPD_FLG = VALUE_INVALID;
	EPS_ENG_SPD_FLG = VALUE_INVALID;  
    EPS_STEER_ANGLE_FLG = VALUE_INVALID;    
    EPS_STEER_ANGLE_SPD_FLG = VALUE_INVALID;
    EPS_MOT_SPD_FLG = VALUE_INVALID;            	 

	SYS_ASSIT_FLG = EPS_DISABLE;
	
	SYS_SLEEP_FLG = SLEEP_DISABLE;
	
	SYS_MSG_SND_FLG = SEND_ENABLE;
	
	SYS_MSG_REC_FLG = RECIVE_ENABLE;
 
    PreRunFlg = 0u;
	u8_StartAssitDelayCount = 0u;
	u16_AssitDelayCounter = 0u; 
	u32_SleepDelayCounter = 0u;
	RampEntryFlag = 0u;

	u16_EngineRunCnt = 0;
	
	//EpsVehRepRamp.s32State = 0;
    //EpsVehRepRamp.s32RampUp   = VEH_SPD_RAMP_UP;
	//EpsVehRepRamp.s32RampDown = VEH_SPD_RAMP_DOWN;
	    
    //motor speed and accspd kalman filter init//
    //set input para initvalue //
    stc_MotSpd_Sig.kG1Sc = KF_G1_SC_32bit;
    stc_MotSpd_Sig.s8kG1Shift = KF_G1_SC_SHIFT_32bit;
    stc_MotSpd_Sig.kG2Sc = KF_G2_SC_32bit;
    stc_MotSpd_Sig.s8kG2Shift = KF_G2_SC_SHIFT_32bit;
    stc_MotSpd_Sig.kTsSc = KF_TS_SC_32bit;   
    stc_MotSpd_Sig.s8kTsShift = KF_TS_SC_SHIFT_32bit;
    
    //output value init//
    hKF_vInit32Bit(&stc_MotSpd_Sig);      
    */
}

/* *****************************************************************************
   Function:        dDiagDec_vGatherFaultInfo
   Description:     Get faults information
   Parameters:      Input:    None
                    Output:   None
   note             need mask faultinfo from faultevent flag(which point to DTC)
   ***************************************************************************** */
void dDiagDec_vGatherFaultInfo(void)
{

	
	SYS_BMS04MSG_ERR = gbCANMissingErrEvt;
		
    /* BUS status */
    SYS_BUSOFF_ERR = gbCANBUSOFFErrEvt;
    
    
}

/* *****************************************************************************
   Function:        dDiagDec_vMainTask
   Description:     main task
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   ***************************************************************************** */
void dDiagDec_vMainTask(void)
{
    dDiagDec_vFaultLevelOutput();  
    dDiagDec_vGetRawSignalValue();   
    dDiagDec_vSignalFilterLogic();
    //dDiagDec_vEnableAssitLogic();
    dDiagDec_vCanCommLogic();
    //dDiagDec_vPreShutdownLogic();
    //dDiagDec_vPreSleepLogic();
    //dDiagDec_vSetSleepIndication();
}


 /* *****************************************************************************
   Function:        dDiagDec_vFaultLevelOutput     
   Description:     Judge & output current Fault Level and Fault lamp state
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   ***************************************************************************** */
static void dDiagDec_vFaultLevelOutput(void)
{
   
   /*--------- Fault Level Judge Logic --------- */
   
	if(FAULT_LEVEL_A != SYS_FAULT_LEVEL)
    {
		/* A level, High level */
		if((SYS_bLV12UnderErr    == IN_FAULT) 
		 ||(SYS_bLV12OverErr     == IN_FAULT)
		 ||(SYS_bLV13UnderErr    == IN_FAULT) 
		 ||(SYS_bLV13OverErr   == IN_FAULT)		 
		 ||(SYS_bINPUT_RelayErr    == IN_FAULT)
		 ||(SYS_boutputCurrentSenError   == IN_FAULT)
		 ||(SYS_bPG_SENSError    == IN_FAULT)
		 )
		{
		    SetSysFaultLevel(FAULT_LEVEL_A);/**/
		}	
		/*B level, Middle Level*/
		else if((SYS_bOverPFCUoutVoltErr   == IN_FAULT)
		        ||(SYS_bHWDCDC_OCPErr   == IN_FAULT)
		        ||(SYS_bOverDCUoutVoltErr    == IN_FAULT)
		        ||(SYS_bDCDCPrechargeTimeoutErr    == IN_FAULT)
		        ||(SYS_bPFCBoostFailErr   == IN_FAULT)
		        ||(SYS_bOverPFCUoutIErr    == IN_FAULT)
		        ||(SYS_bOverUinVoltErr    == IN_FAULT)
		        ||(SYS_bUnderUinVoltErr    == IN_FAULT)
		        ||(SYS_bUnderDCUoutVoltErr    == IN_FAULT)
		        )
		{
			SetSysFaultLevel(FAULT_LEVEL_B);/* induce state judge into LimpHome state; */
		}
		/*C level, Low Level*/
		else if((SYS_BUSOFF_ERR == IN_FAULT)
				||(SYS_bUinVoltOpenErr    == IN_FAULT)
				||(SYS_bTempWarinOutOffErr    == IN_FAULT)
				||(SYS_bOverTempCoolErr    == IN_FAULT)
				||(SYS_BMS04MSG_ERR  == IN_FAULT)
				)
		{
		    SetSysFaultLevel(FAULT_LEVEL_C);/* not induce directly state judge but can set the AssitDisableFlg or SleepFlg */
		                                  	/* the operation for these faults will be realized in Decision Module */
		}
		/* No Fault */
		else
		{
			SetSysFaultLevel(FAULT_LEVEL_OK);
		}
    }
    else
    {
    	;
    }
    
	/* set failure lamp status */
	if((SYS_FAULT_LEVEL == FAULT_LEVEL_A) 
	   /*|| (CLEAR_STEERING_ANGLE_ZERO_POS_CMD == EPS_ANGLE_CMD_CODE)*/)
	{
		SYS_FAULT_LAMP_FLG  = FAULT_LAMP_ON;
	}
	else if((SYS_IGN_STATE == IGN_ON) 
	        &&(SYS_ASSIT_FLG == EPS_DISABLE))
	{
        if(0u == PreRunFlg)
        {
        	SYS_FAULT_LAMP_FLG  = FAULT_LAMP_ON;
            PreRunFlg++;
        }   
        else
        {
        	;
        }
	}
	else
	{
	    SYS_FAULT_LAMP_FLG  = FAULT_LAMP_OFF;
	}    
	
	
}

/* *****************************************************************************
   Function:        dDiagDec_vGetRawSignalValue
   Description:     Get raw signals from all signal sources
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   ***************************************************************************** */
__inline static void dDiagDec_vGetRawSignalValue(void)
{
	OBC_INPUTVoltage  = OBCTag.ACRMSVolt;
	OBC_INPUTCurrent = (uint16)((uint16)AC_AD_CONVERT_CURRENT(L5_AC_current_max_buff)<<4);
	OBC_CPDUTY = cpPwmWidthPFilterOffset;
	OBC_OUTVoltage = OBCTag.actChrVolt;
	OBC_OUTCurrent = OBCTag.actChrCurrent;
	OBC_OBCTemp = OBCTag.ChrTemp;

}

/* *****************************************************************************
   Functin:         dDiagDec_vSetSleepIndication
   Description:     logic for sleep flag;
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
static void dDiagDec_vSetSleepIndication(void)
{

	/*
	if(SLEEP_DISABLE == SYS_SLEEP_FLG)
	{
		if((SYS_FAULT_LEVEL == FAULT_LEVEL_A)
	      ||(EPS_DISABLE == SYS_ASSIT_FLG))
		{
			if(SYS_IGN_STATE == IGN_OFF)
			{
				SYS_SLEEP_FLG = SLEEP_ENABLE;
			}
			else
			{
				;
			}
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}
	*/
}

/* *****************************************************************************
   Functin:         dDiagDec_vEnableAssitLogic
   Description:     the logic of re-assit from non-assit.
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   *****************************************************************************/
static void dDiagDec_vEnableAssitLogic(void)
{
	/* Assit Indication Logic */
	/*
	if(SYS_ASSIT_FLG == EPS_DISABLE)     
	{
	    if(SYS_IGN_STATE == IGN_ON)
	    {
	        if(EPS_ENG_SPD_FLT > ENGINE_RUN_SPD_LMT) 
			{
			   	u16_EngineRunCnt++;
			   	
			   	if(u16_EngineRunCnt >= ENGINE_RUN_TIME_LMT) 
			   	{
			   		SYS_ASSIT_FLG = EPS_ENABLE; 
			   		
			   		u16_EngineRunCnt = 0u;	
			   	}
			   	else
			   	{
			   		;
			   	} 	
			}
			else
			{
				u16_EngineRunCnt = 0u;
			}	 
	    }
	    else
	    {
	    	;
	    }
	}	
	else
	{
		;
	}
*/
}

/* *****************************************************************************
   Function:        dDiagDec_vCanCommLogic
   Description:     logic for enable & disable send MSG;.
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
static void dDiagDec_vCanCommLogic()
{   
    if(SYS_IGN_STATE == IGN_ON)
    {
	    if(u8EnCanRxAndTx == 0x00)
	    {
	    	if((u8MsgType == 0x01) || (u8MsgType == 0x03))
	    	{
	    		SYS_MSG_SND_FLG = SEND_ENABLE;
	    		SYS_MSG_REC_FLG = RECIVE_ENABLE;
	    	}
	    	else if(u8MsgType == 0x02)
	    	{
	    		;
	    	}
	    	else
	    	{
	    		;
	    	}
	    }
	    else if(u8EnCanRxAndTx == 0x01)
	    {
	    	if((u8MsgType == 0x01) || (u8MsgType == 0x03))
	    	{
	    		SYS_MSG_SND_FLG = SEND_DISABLE;
	    		SYS_MSG_REC_FLG = RECIVE_ENABLE;
	    	}
	    	else if(u8MsgType == 0x02)
	    	{
	    		;
	    	}
	    	else
	    	{
	    		;
	    	}	
	    }
	    else if(u8EnCanRxAndTx == 0x02)
	    {
	    	if((u8MsgType == 0x01) || (u8MsgType == 0x03))
	    	{
	    		SYS_MSG_SND_FLG = SEND_ENABLE;
	    		SYS_MSG_REC_FLG = RECIVE_DISABLE;
	    	}
	    	else if(u8MsgType == 0x02)
	    	{
	    		;
	    	}
	    	else
	    	{
	    		;
	    	}
	    }
	    else if(u8EnCanRxAndTx == 0x03)
	    {
	    	if((u8MsgType == 0x01) || (u8MsgType == 0x03))
	    	{
	    		SYS_MSG_SND_FLG = SEND_DISABLE;
	    		SYS_MSG_REC_FLG = RECIVE_DISABLE;
	    	}
	    	else if(u8MsgType == 0x02)
	    	{
	    		;
	    	}
	    	else
	    	{
	    		;
	    	}	
	    }
	    else
	    {
	    	
	    }    	
    }
    else
    {
    	SYS_MSG_SND_FLG = SEND_DISABLE;
    }

}


/* *****************************************************************************
   Function:        dDiagDec_vPreShutdownLogic
   Description:     according the current condition provide assit indication.
   Parameters:      Input:    None
                    Output:   None
   Notes:           none
                   
   *****************************************************************************/
static void dDiagDec_vPreShutdownLogic(void)
{     

	/* 
    if(SYS_ASSIT_FLG == EPS_ENABLE)
	{
		if(EPS_ENG_SPD_FLT < ENGINE_RUN_SPD_LMT)// 30s disable Assit Delay Logic//
		{
			if(EPS_VEH_SPD_FLT <= VEHICLE_SPD_LMT)
			{
			    u8_StartAssitDelayCount = 1u;
			}
			else
			{
				;
			}
			
			if(u8_StartAssitDelayCount == 1u)
			{ 
			    u16_AssitDelayCounter ++;

				if(u16_AssitDelayCounter >= ASSIT_DELAY_COUNTER)
				{
				    u8_StartAssitDelayCount = 0u;
	                SYS_ASSIT_FLG = EPS_DISABLE;        //Output Assit Indication//
				}
				else
				{
					;
				}			    
			}
			else
			{
				;
			}

		}
		else
		{
		   u8_StartAssitDelayCount = 0u;
		   u16_AssitDelayCounter = 0u;
		}
				
	}	
	else
	{
		;
	}
	*/
}

/* *****************************************************************************
   Function:        dDiagDec_vPreSleepLogic  
   Description:     process the pre-sleep logic
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
static void dDiagDec_vPreSleepLogic(void)
{    
    /* 70s Delay Sleep Logic */		

	/*
	if(SYS_ASSIT_FLG == EPS_ENABLE)
	{
		if(SYS_IGN_STATE == IGN_OFF)
		{	    
			if(EPS_ENG_SPD_FLT < ENGINE_RUN_SPD_LMT)
			{			   
			    if(EPS_VEH_SPD_FLT > VEHICLE_SPD_LMT)
			    {
			        u32_SleepDelayCounter ++;
			        
					if(u32_SleepDelayCounter >= SLEEP_DELAY_COUNTER)
					{
					    u32_SleepDelayCounter = 0u;
					    SYS_ASSIT_FLG = EPS_DISABLE;
					}
					else
					{
						;
					}			        
				}
				else
				{
				    ;
				}
			}
			else 
			{
	            u32_SleepDelayCounter = 0u;
			}
			
		}
		else
		{
			u32_SleepDelayCounter = 0u;
		}		
	}
	else
	{
		;
	}
	*/

}

/* *****************************************************************************
   Function:        dDiagDec_vSignalFilterLogic
   Description:     process the raw signals and provide the filter signals.
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   ***************************************************************************** */
static void dDiagDec_vSignalFilterLogic(void)
{
    if(stSysFSMCtrl.ucCurrentState != STATE_OPETRATION)
    //非充电模式下可进入拓展模式
	{
		 SetDiagCondition(ENABLE);
	}
	else
	{
	     SetDiagCondition(DISABLE);
	}
}

/* *****************************************************************************
   Function:        dDiagDec_vGetSlaveState
   Description:     Get Slaver states.
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   ***************************************************************************** */
static void dDiagDec_vGetSlaveState(void)
{
	//stc_dDiagDec_Sig.SlaverState = hMaster_u8SlaverState();	
}



/*********************************************** End ************************************************/
	
	
