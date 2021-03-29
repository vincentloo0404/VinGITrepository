
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L3_ECAL.h"

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
static void DTC_L4_ClrDTCMgt(void);
static void DTC_L4_SnapShotMgt(uint8 index);
static void DTC_L4_CustomerDTCMgt(void);
static void DTC_L4_FaultMgt(void);

#define d_L4DTC_START_SEC_VAR 
#include "MemMap.h" 
/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
static uint8 L4_S_DTCEnable_Ct_G_a[e_DTC_HANDLE];
static uint8 L4_S_DTCError_CTR_Ct_G_a[e_DTC_HANDLE];
static uint8 gIndex_u08;

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/

#define d_L4DTC_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4DTC_START_SEC_CODE
#include "MemMap.h" 
/*****************************************************************************
*
*   Function:     void DTC_L4_vInit(void)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void DTC_L4_vInit(void)
{
    uint8 tmpIndex;
    
    gIndex_u08 = 0;
    
	/* Customer DTC */
    for(tmpIndex=0;tmpIndex<e_DTC_HANDLE;tmpIndex++)
    {
        DTC_L4_Enable(tmpIndex);
        /* read from external EEPROM */
        L4_S_DTCSta_G_Str[tmpIndex].bits.TestFailed_b = FALSE;
        
        L4_S_DTCSta_G_Str[tmpIndex].bits.TestFailedThisOperation_b = FALSE;
        
        if(L4_S_DTCSta_G_Str[tmpIndex].bits.ConfirmedDTC_b == TRUE)
        {
            L4_S_DTCAGING_Ct_G_a[tmpIndex]++;
            
            if(d_PENDINGDTC_THRESHOLD <= L4_S_DTCAGING_Ct_G_a[tmpIndex])
            {
                L4_S_DTCSta_G_Str[tmpIndex].bits.PendingDTC_b\
                                                            = FALSE;
            }
            
            if(L4_S_DTCCfg_G_Str[tmpIndex].AgeingCnt_u08 <= \
                                    L4_S_DTCAGING_Ct_G_a[tmpIndex])
            {
                L4_S_DTCAGING_Ct_G_a[tmpIndex] = 0;
                L4_S_DTCSta_G_Str[tmpIndex].bits.ConfirmedDTC_b\
															= FALSE;
            }            
        }
        else
        {
        	L4_S_DTCAGING_Ct_G_a[tmpIndex] = 0;
        }
        /* Bit TestNotCompletedSinceLastClear and testFailedSinceLastClear
           not supported */
        L4_S_DTCSta_G_Str[tmpIndex].bits.TestNotCompletedLastClear_b\
                                                                   = FALSE;
        L4_S_DTCSta_G_Str[tmpIndex].bits.TestFailedSinceLastClear_b\
                                                                   = FALSE;
                                                                   
        L4_S_DTCSta_G_Str[tmpIndex].bits.TestNotCompletedThisCycle_b\
																   = TRUE;
        
        L4_S_DTCSta_G_Str[tmpIndex].bits.WarningIndicatorReq_b = FALSE;
        
        L4_S_DTCError_CTR_Ct_G_a[tmpIndex] = 0;
	}
    
	/* Ht-Saae FaultCode */
    for(tmpIndex=0;tmpIndex<e_FAULT_HANDLE;tmpIndex++)
    {
        /* read from external EEPROM */
        L4_S_FaultSta_G_Str[tmpIndex].bits.TestFailed_b = FALSE;
        
		L4_S_FaultSta_G_Str[tmpIndex].bits.TestFailedThisOperation_b\
																   = FALSE;

		if(L4_S_FaultSta_G_Str[tmpIndex].bits.ConfirmedDTC_b == TRUE)
        {
            L4_S_FaultAGING_Ct_G_a[tmpIndex]++;
        }
        else
        {
        	L4_S_FaultAGING_Ct_G_a[tmpIndex] = 0;
        }
        
        if(L4_S_FaultAGING_Ct_G_a[tmpIndex] >= d_PENDINGDTC_THRESHOLD)
        {
        	L4_S_FaultSta_G_Str[tmpIndex].bits.PendingDTC_b = FALSE;
        }
        
        if(L4_S_FaultAGING_Ct_G_a[tmpIndex] >= d_FAULT_AGING_THRESHOLD)
        {
        	L4_S_FaultSta_G_Str[tmpIndex].bits.ConfirmedDTC_b = FALSE;
        	
        	L4_S_FaultSta_G_Str[tmpIndex].bits.SnapShotCompleted_b\
        	                                                      = FALSE;
        	L4_S_FaultAGING_Ct_G_a[gIndex_u08] = 0;
        }
        /* Bit TestNotCompletedSinceLastClear and testFailedSinceLastClear
           not supported */
        L4_S_FaultSta_G_Str[tmpIndex].bits.TestNotCompletedLastClear_b = FALSE;
        L4_S_FaultSta_G_Str[tmpIndex].bits.TestFailedSinceLastClear_b = FALSE;
        
		L4_S_FaultSta_G_Str[tmpIndex].bits.TestNotCompletedThisCycle_b\
																   = TRUE;
																   
    }
}
/*****************************************************************************
*
*   Function:     void DTC_L4_SetError(uint8 index)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void DTC_L4_SetError(uint8 index)
{
    uint8 tmpDTCindex_u08;

    if(L4_S_FaultSta_G_Str[index].bits.TestFailed_b==FALSE)
    {
       /* Find the DTC index for customer */
       tmpDTCindex_u08 = L4_S_FaultCode_G_Str[index].DTCIndex; 

       if(tmpDTCindex_u08 < e_DTC_HANDLE)
       {
      	  if(TRUE == L4_S_DTCEnable_Ct_G_a[tmpDTCindex_u08])
      	  {
      	  	 /* Set DTC status bit */
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestFailed_b = TRUE;
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestFailedThisOperation_b\
      	  	                                                           = TRUE;
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.PendingDTC_b = TRUE;
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.ConfirmedDTC_b = TRUE;
            /* Bit TestNotCompletedSinceLastClear and testFailedSinceLastClear
               not supported */
             /*
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestNotCompletedLastClear_b\
      	  	                                                             = FALSE;
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestFailedSinceLastClear_b\
      	  	                                                           = TRUE;
      	  	 */                                                          
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestNotCompletedThisCycle_b\
      	  	 															   = FALSE;
      	  	 /* clear the aging counter */
      	  	 L4_S_DTCAGING_Ct_G_a[tmpDTCindex_u08] = 0;
      	  	
      	  	 /* Set the Error Ctr */
      	  	 if(L4_S_DTCError_CTR_Ct_G_a[tmpDTCindex_u08]<255)
      	  	 {
      	  	     L4_S_DTCError_CTR_Ct_G_a[tmpDTCindex_u08]++;
      	  	 }
      	  }
      	  else
      	  {
      	  	 L4_S_DTCSta_G_Str[tmpDTCindex_u08].DTC_Sta_u08 = 0x00;
      	  }
       }
       /* Set Fault Code  */
       L4_S_FaultSta_G_Str[index].bits.TestFailed_b = TRUE;
       L4_S_FaultSta_G_Str[index].bits.TestFailedThisOperation_b = TRUE;
       L4_S_FaultSta_G_Str[index].bits.PendingDTC_b = TRUE;
       L4_S_FaultSta_G_Str[index].bits.ConfirmedDTC_b = TRUE;

       /* Bit TestNotCompletedSinceLastClear and testFailedSinceLastClear
          not supported */
       /*
       L4_S_FaultSta_G_Str[index].bits.TestNotCompletedLastClear_b = FALSE;
       L4_S_FaultSta_G_Str[index].bits.TestFailedSinceLastClear_b = TRUE;
       */
       L4_S_FaultSta_G_Str[index].bits.TestNotCompletedThisCycle_b = FALSE;
       /*Clear Aging Counter*/
       L4_S_FaultAGING_Ct_G_a[index] = 0;
    }
}
/*****************************************************************************
*
*   Function:     void DTC_L4_ClrError(uint8 index)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void DTC_L4_ClrError(uint8 index)
{
    uint8 tmpDTCindex_u08;
   
    //Find the DTC index for customer
    tmpDTCindex_u08 = L4_S_FaultCode_G_Str[index].DTCIndex;
    //Set DTC status bit
	//L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestFailed_b = FALSE;
    L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestNotCompletedThisCycle_b\
    															   = FALSE;
    /*
    L4_S_DTCSta_G_Str[tmpDTCindex_u08].bits.TestNotCompletedLastClear_b\
                                                                   = FALSE;
    */
    //Clr the Error Ctr
    if(L4_S_FaultSta_G_Str[index].bits.TestFailed_b==TRUE)
    {
        if(L4_S_DTCError_CTR_Ct_G_a[tmpDTCindex_u08]>0)
        {
            L4_S_DTCError_CTR_Ct_G_a[tmpDTCindex_u08]--;
        }
    }
	
    //Set Fault Code 
    L4_S_FaultSta_G_Str[index].bits.TestFailed_b = FALSE;
    L4_S_FaultSta_G_Str[index].bits.TestNotCompletedThisCycle_b = FALSE;
    //L4_S_FaultSta_G_Str[index].bits.TestNotCompletedLastClear_b = FALSE;
}
/*****************************************************************************
*
*   Function:     uint8 DTC_L4_GetErrorSta(uint8 index)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
****************************************************************************/
uint8 DTC_L4_GetErrorSta(uint8 index)
{
    uint8 tmpRet_u08;
    
    if(index<e_FAULT_HANDLE)
    {
        tmpRet_u08 = L4_S_FaultSta_G_Str[index].Fault_Sta_u08;
    }
	else
    {
        tmpRet_u08 = 0;
    }

    return(tmpRet_u08);
}
/*****************************************************************************
*
*   Function:     uint8 DTC_L4_GetErrorSta(uint8 index)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
****************************************************************************/
uint8 DTC_L4_GetErrorStaB0(uint8 index)
{
    uint8 tmpRet_u08;
    
    if(index<e_FAULT_HANDLE)
    {
        tmpRet_u08 = L4_S_FaultSta_G_Str[index].bits.TestFailed_b;
    }
	else
    {
        tmpRet_u08 = 0;
    }

    return(tmpRet_u08);
}
/*****************************************************************************
*
*   Function:     uint8 DTC_L4_GetErrorSta(uint8 index)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
****************************************************************************/
uint8 DTC_L4_GetErrorStaB1(uint8 index)
{
    uint8 tmpRet_u08;
    
    if(index<e_FAULT_HANDLE)
    {
        tmpRet_u08 =\
        		L4_S_FaultSta_G_Str[index].bits.TestFailedThisOperation_b;
    }
	else
    {
        tmpRet_u08 = 0;
    }

    return(tmpRet_u08);
}
/*****************************************************************************
*
*   Function:     void DTC_L4_Enable(uint8 index)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*****************************************************************************/
void DTC_L4_Enable(uint8 index)
{
    L4_S_DTCEnable_Ct_G_a[index] = TRUE;
}
/*****************************************************************************
*
*   Function:     void DTC_L4_Disable(uint8 index)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*****************************************************************************/
void DTC_L4_Disable(uint8 index)
{
	L4_S_DTCEnable_Ct_G_a[index] = FALSE;
}
/*****************************************************************************
*
*   Function:    uint8 DTC_L4_GetStatus(uint8 index)
*
*   Description:  This fucntion is for getting the dtc status
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
******************************************************************************/
uint8 DTC_L4_GetSta(uint8 index)
{
    uint8 tmpSta_u08;

    if(index<e_DTC_HANDLE)
    {
        tmpSta_u08 = L4_S_DTCSta_G_Str[index].DTC_Sta_u08;
    }
	else
	{
        tmpSta_u08 = 0;
    }

    return(tmpSta_u08);
}
/*****************************************************************************
*
*   Function:     void DTC_L4_ClrSta(void)
*
*   Description:  This fucntion is for clearing the dtc status
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
****************************************************************************/
void DTC_L4_ClrSta(void)
{
    uint8 tmpIndex;
    
	/*Clear the Customer DTC*/
    for(tmpIndex=0;tmpIndex<e_DTC_HANDLE;tmpIndex++)
    {
        L4_S_DTCSta_G_Str[tmpIndex].DTC_Sta_u08 = 0x00;
    }
    /*Clear the Ht-saae Fault*/
    for(tmpIndex=0;tmpIndex<e_FAULT_HANDLE;tmpIndex++)
    {
        L4_S_FaultSta_G_Str[tmpIndex].Fault_Sta_u08 = 0x00;
    }
    /*Clear the Snapshot Index*/
    for(tmpIndex=0;tmpIndex<d_SNAPSHOT_FIFO_LENGTH;tmpIndex++)
    {
        d_SNAPSHOT_INDEX(tmpIndex) = 0U;
    }
}
/*****************************************************************************
*
*   Function:     void DTC_L4_ClrDTCMgt(void)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void DTC_L4_ClrDTCMgt(void)
{

    uint8 tempIndex;
    
    for(tempIndex = 0;tempIndex < e_DTC_HANDLE;tempIndex++)
    {
	    if(L4_S_DTCError_CTR_Ct_G_a[tempIndex] == 0)
	    {
	        L4_S_DTCSta_G_Str[tempIndex].bits.TestFailed_b = FALSE;
	    }
    }


#if 0

    /* ECU Is Faulted */
    if(L4_S_DTCError_CTR_Ct_G_a[e_DTC_ECU_ERROR] == 0)
    {
        L4_S_DTCSta_G_Str[e_DTC_ECU_ERROR].bits.TestFailed_b = FALSE;
    }
    /* Flash Programming Malfunction */
    if(L4_S_DTCError_CTR_Ct_G_a[e_DTC_FLASH_ERROR] == 0)
    {
        L4_S_DTCSta_G_Str[e_DTC_FLASH_ERROR].bits.TestFailed_b = FALSE;
    }
    /* Bus Off Fault */
    if(L4_S_FaultSta_G_Str[e_FAULT_CANOFF_RUN].bits.TestFailed_b == FALSE)
    {
        L4_S_DTCSta_G_Str[e_DTC_CAN_BUSOFF].bits.TestFailed_b = FALSE;
    }
    /* Battery Voltage High */
    if(L4_S_FaultSta_G_Str[e_FAULT_BATVOLT_HIGH].bits.TestFailed_b==FALSE)
    {
        L4_S_DTCSta_G_Str[e_DTC_BATTERY_VOLTAGE_HIGH].bits.TestFailed_b \
																	= FALSE; 
    }
	/* Battery Voltage Low */
    if(L4_S_FaultSta_G_Str[e_FAULT_BATVOLT_LOW].bits.TestFailed_b==FALSE)
    {
        L4_S_DTCSta_G_Str[e_DTC_BATTERY_VOLTAGE_LOW].bits.TestFailed_b \
																	= FALSE;  
    }
    /* Steering Shaft Torque Sensor Malfunction */
    if(L4_S_DTCError_CTR_Ct_G_a[e_DTC_TORQUE_SENSOR_ERROR] == 0)
    {
        L4_S_DTCSta_G_Str[e_DTC_TORQUE_SENSOR_ERROR].bits.TestFailed_b \
																	= FALSE;
    }
    /* Missing ECU Message */
    if(L4_S_DTCError_CTR_Ct_G_a[e_DTC_CAN_MESSAGE_LOST] == 0)
    {
        L4_S_DTCSta_G_Str[e_DTC_CAN_MESSAGE_LOST].bits.TestFailed_b = FALSE;
    }
    /* Electronic Power Steering Motor Malfunction */
    if(L4_S_DTCError_CTR_Ct_G_a[e_DTC_MOTOR_ERROR] == 0)
    {
        L4_S_DTCSta_G_Str[e_DTC_MOTOR_ERROR].bits.TestFailed_b = FALSE;
    }
#endif    
}
/*****************************************************************************
*
*   Function:    void DTC_L4_SnapShotMgt(void)
*
*   Description:  This function is to record the SnapShot data
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
***************************************************************************/
static void DTC_L4_SnapShotMgt(uint8 index)
{ 

#if 0

    /*When reach boundary the first time,clear this value*/
    if(L4_N_SnapShotCurrentPoint_F_u8 >= d_SNAPSHOT_FIFO_LENGTH)
    {
        L4_N_SnapShotCurrentPoint_F_u8 = 0;
    }
    /*Snap the data*/
    d_SNAPSHOT_BAT(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_Battery_Voltage_Vt_G_u16p08;    
    d_SNAPSHOT_VSPD(L4_N_SnapShotCurrentPoint_F_u8) =\
    		                          L3_S_VehicleSpeed_Kph_G_u16p01;
    d_SNAPSHOT_TOR_A(L4_N_SnapShotCurrentPoint_F_u8) =\
    		            TorqueAndAngle_Y.L3_S_TrqDTorqVal_HwNm_G_s16p07;
    d_SNAPSHOT_TOR_B(L4_N_SnapShotCurrentPoint_F_u8) = 0;
                                      //L3_S_HandWheelTorque_A_Nm_G_s16;
    d_SNAPSHOT_MCUR_U(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_MotorCurrent_A_G_s16[0];
    d_SNAPSHOT_MCUR_V(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_MotorCurrent_A_G_s16[1];
    d_SNAPSHOT_PWM_A(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_PWM_CompareValue_A_G_u16[0];
    d_SNAPSHOT_PWM_B(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_PWM_CompareValue_A_G_u16[1];
    d_SNAPSHOT_PWM_C(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_PWM_CompareValue_A_G_u16[2];
    d_SNAPSHOT_MSPD(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_MotorSpeed_rpm_G_u16;
    d_SNAPSHOT_MFPWR(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_Mosfet_Voltage_Vt_G_u16p11;
    d_SNAPSHOT_SNPWR(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_Sensor_Voltage_Vt_G_u16p08;
    d_SNAPSHOT_MFTMP(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_MosfetTemp_DegC_G_s16p01;
    d_SNAPSHOT_MPT_HALL(L4_N_SnapShotCurrentPoint_F_u8) = 0;
                                      //(uint8)(d_PresentHallState);
    d_SNAPSHOT_MPT_AB(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      (uint8)L3_S_EncoderValue_Ct_G_u16;
    d_SNAPSHOT_ENG(L4_N_SnapShotCurrentPoint_F_u8) =\
                                      L3_S_EngineRunningStatus_Ct_G_u08;
    d_SNAPSHOT_INDEX(L4_N_SnapShotCurrentPoint_F_u8) = index;
    
    if(L4_N_SnapShotCurrentPoint_F_u8 < (d_SNAPSHOT_FIFO_LENGTH - 1))
    {
        L4_N_SnapShotCurrentPoint_F_u8++;
    }
    else
    {
        L4_N_SnapShotCurrentPoint_F_u8 = 0;
    }
    
#endif    
}
/*****************************************************************************
*
*   Function:     void DTC_L4_CustomerDTCMgt(void)
*
*   Description:  This function is to management the customer DTC
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
***************************************************************************/
static void DTC_L4_CustomerDTCMgt(void)
{
   
	DTC_L4_ClrDTCMgt();
                        
}
/*****************************************************************************
*
*   Function:     void DTC_L4_FaultMgt(void)
*
*   Description:  This function is to management the ht-saae DTC
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
***************************************************************************/
static void DTC_L4_FaultMgt(void)
{
    uint8 tmpFaultIndex_u08;
    uint8 tmpLoophandle_u08;
    
    if((gIndex_u08 + d_MAX_LOOP_LENGHT) >= e_FAULT_HANDLE)
    {
        tmpLoophandle_u08 = e_FAULT_HANDLE;
    }
    else
    {
        tmpLoophandle_u08 = gIndex_u08 + d_MAX_LOOP_LENGHT;
    }
    
    for(;gIndex_u08<tmpLoophandle_u08;gIndex_u08++)
    {
        if(L4_S_FaultSta_G_Str[gIndex_u08].bits.TestFailed_b == TRUE)
        {
            if(L4_S_FaultSta_G_Str[gIndex_u08].bits.SnapShotCompleted_b\
                                                                ==FALSE)
            {
                L4_S_FaultSta_G_Str[gIndex_u08].bits.SnapShotCompleted_b\
																=TRUE;
                //SnapShot
                tmpFaultIndex_u08 = \
                        L4_S_FaultCode_G_Str[gIndex_u08].FaultIndex;
                DTC_L4_SnapShotMgt(tmpFaultIndex_u08);
            }
        }
        else
        {   

		}
    }
    
	if(tmpLoophandle_u08 == e_FAULT_HANDLE)
    {
        gIndex_u08 = 0;
    }
}
/*****************************************************************************
*
*   Function:     void DTC_L4_POLLING_2ms(void)
*
*   Description:  
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
***************************************************************************/
void DTC_L4_POLLING_2ms(void)
{
    static uint8 testIndex  = 0;
    static uint8 testEnable = 0;
    
    if(testEnable == 1)
    {
    	DTC_L4_SetError(testIndex);
    }
    else if(testEnable == 2)
    {
    	DTC_L4_ClrError(testIndex);
    }
    else
    {
    	
    }
    /* Customer DTC */
    DTC_L4_CustomerDTCMgt();
    
    /* FaultCode    */
    DTC_L4_FaultMgt();   
}
#define d_L4DTC_STOP_SEC_CODE
#include "MemMap.h" 

/*End of L4_DTC.c file*/