/********************************************************************************************
*
* Beijing Hualong Tech Inc.
* (c) Copyright 2013 Beijing Hualong Tech, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************************//*!
*
* @file   DtcStatusManage.c  
*
* @brief  this file implements the DTC manage logic.
*
**********************************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/05/10    CODER1     N/A             Original
*     1.1      2013/10/16    CODER1	    N/A             use firmed RAM space 
                                                            and update init and save process
**********************************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#ifndef DTC_STATUS_MANAGE_C
#define DTC_STATUS_MANAGE_C
#endif

#include "DtcStatusManage.h"

/* *****************************************************************************
   *****************************************************************************
   variable declaration
   *****************************************************************************
   *****************************************************************************/

/*******************************************************************************
* declaration of internal variables
********************************************************************************/
static uint16 DTC_DelayOnBoot;
static sint16 DTC_TestFailedCounter[DTC_NUMBER_SIZE];
static uint16 DTC_ConfirmedCounter[DTC_NUMBER_SIZE];
static uint8  DTC_This_Cycle_Failed_Flag[DTC_NUMBER_SIZE];      
static uint8  DTC_Last_Cycle_Failed_Flag[DTC_NUMBER_SIZE];
static uint8  Ext_failedcycle_cnt_updt[DTC_NUMBER_SIZE];
static uint8  LastMonitorState[DTC_NUMBER_SIZE];

/*******************************************************************************
* Prototypes of internal functions
********************************************************************************/
static uint8  Dtc_MatureCounterState(uint16 aInedx,uint8 testresult);
static uint8  Dtc_ConfirmedCounterState(uint16 aIndex, uint8 testResult);
static void   Dtc_StatusBitsUpdate(uint16 aIndex,uint8 monitorState,uint8 confirmState);

static void   Dtc_ExtDataUpdate(uint16 aIndex);
static void   Dtc_FFDataUpdate(uint16 aIndex);

/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : Dtc_PreInit
 *
 * Description   : init the fault flags before Systeminit
 *
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : must be called before all "Initialization-fault-detecting moudles"
 *
 ************************************************************************************************
 END_FUNCTION_HDR */
void Dtc_PreInit(void)
{
    dDiag_vFaultFlagInit();
}

/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : Dtc_Init
 *
 * Description   : read last fault record from E2 and init the current DTC buffer
 *
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : must be called after all "Initialization-fault-detecting moudles"
 *
 ************************************************************************************************
 END_FUNCTION_HDR */

void Dtc_Init(void)
{
   uint16 i = 0u;
   uint16 j = 0u;
   uint16 k = 0u;
   uint16 r = 0u;
   uint8  Eeprom_Flag = EEPROM_OK;
   
   DTC_DelayOnBoot = 0;
   
   for(k=0;k<10;k++)
   {
   	  u8DidParameter[k] = 0x0;
   	  u16DidParameter[k] = 0x0;
   }

   Eeprom_Flag = mEEPROM_Read_Flash((INT32U *)DTC_RAM_START_ADDR);
   
   if((EEPROM_OK == Eeprom_Flag)&&(DTC_NUMBER_SIZE == gDtcInfoData->dtcNumber))
   {         
	   for(i=0u; i<DTC_NUMBER_SIZE; i++)
	   {
	   
	       DTC_HIGH_BYTE(i) =  (uint8)(DTC_InitValue[i]>>24);    
           DTC_MIDDLE_BYTE(i) = (uint8)(DTC_InitValue[i]>>16);     
           DTC_LOW_BYTE(i) = (uint8)(DTC_InitValue[i]>>8);   	  
	       	  
	       DTC_Last_Cycle_Failed_Flag[i] = gDtcInfoData->dtcCode[i].dtcBits.bit1_state;   	      
	   }
	  
   }
   else
   {
   	   for(i=0u; i<DTC_NUMBER_SIZE; i++)
	   {  
	      DTC_CODE(i) = DTC_InitValue[i];/*DTC code and status initial*/
	      
	      for(r=0u; r<DTC_EXD_DATA_TYPE_SIZE/4u; r++)
	      {
		      DTC_EXT_DATA(i)[r] = EXD_DATA_INITIAL; /*Extend data initial*/	      	
	      }	
	      
	     
	      #ifdef USE_SNAPSHOT_DATA	
	      
	      if(DTC_NO_SNAPSHOT != gDtc_Attribute_Table[i].WithFreezeFrameFlag)/*freezeframe data*/
	      {
		      for(j=0; j<DTC_SNAPSHOT_TYPE_SIZE/4u; j++)
			  {
			  	  DTC_SNAPSHOT_DATA(i)[j] = FREEZE_DATA_INITIAL;
			  }	      	
	      } 
	      else
	      {
	      	
	      }
	      
	      #endif   
	      
	      DTC_Last_Cycle_Failed_Flag[i] = gDtcInfoData->dtcCode[i].dtcBits.bit1_state; 
	      	      	        	   
	   }	  	   	  
   }

   gDtcInfoData->dtcNumber = DTC_NUMBER_SIZE;
   Dtc_Status_PowerOn_Init();
   
   #ifdef ROLLING_MODE    
   InitializationFault_DTCStatusUpdate(); /* must be called after calling DTC_Status_PowerOn_Init()*/
   #endif
   
}

/* BEGIN_FUNCTION_HDR
 ************************************************************************************************************
 * Function Name : DTC_MainTask
 *
 * Description   : when power on, ECUs usually need some prepare time during which they cant give
                   correct information and ECU should not do the fault-checking except Initialization Type.
 *                 So for some faults ECU may need a delay and then start the fault monitor.
 
                   DTC_DELAY_ON_BOOT: delay time;
                   DTC_TASK_TIME:     DTC task schedule time.
                   
                   if it due to the App module when start detecting Faul, the delay time here dont need any more.
                   For this, DTC_DELAY_ON_BOOT can be set 0;
                   
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : this function only be appropriate for ROLLING MODE but not for REALTIME_CALL_MODE
 *
 *************************************************************************************************************
   END_FUNCTION_HDR */

void Dtc_MainTask(void)
{
	if (DTC_DelayOnBoot < (DTC_DELAY_ON_BOOT/DTC_TASK_TIME)) 
	{
		DTC_DelayOnBoot++;
	} 
	else 
	{
		if(gDTCSwitch == DTC_ENABLE)
		{
			Dtc_StatusUpdate();     	
		}
		else
		{

		}

	}
}

/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : DTC_Status_PowerOn_Init
 *
 * Description   : Init all the DTC status when IGN switch into ON state.
 *
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
void Dtc_Status_PowerOn_Init(void)
{
  uint16 i = 0u;

  for (i = 0u;i < DTC_NUMBER_SIZE;i++) 
  { 
      DTC_This_Cycle_Failed_Flag[i] = DTC_FALSE; 
      
      DTC_STATUS_BIT0(i)  = BIT_SET_ZERO;
      
      DTC_STATUS_BIT1(i)  = BIT_SET_ZERO; 
      
      #if (DTC_BIT2_SUPPORT) 
      
      if (DTC_Last_Cycle_Failed_Flag[i] == DTC_FALSE) 
      {
         DTC_STATUS_BIT2(i) = BIT_SET_ZERO;
      }
      else
      {
      	
      }
      
      #else
      
      DTC_STATUS_BIT2(i) = BIT_SET_ZERO;
      
      #endif

      /*--------------- bit3 reset & Aging process ----------------*/
      if(DTC_TRUE == DTC_STATUS_BIT3(i))
      {                                                
        if(DTC_FALSE == DTC_Last_Cycle_Failed_Flag[i])
        {
           DTC_EXT_AGING_COUNTER_DATA(i)++;
        }
        else
        {
           DTC_EXT_AGING_COUNTER_DATA(i) = DTC_AGING_COUNTER_CLEAR;
        }

        #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_ON) 
        if (DTC_EXT_AGING_COUNTER_DATA(i) > DTC_AGING_THRESHOLD) 
        #else
        if (DTC_EXT_AGING_COUNTER_DATA(i) > gDtc_Attribute_Table[i].AgingThreshold) 
        #endif        
        {
           DTC_STATUS_BIT3(i) = BIT_SET_ZERO;
           DTC_EXT_AGING_COUNTER_DATA(i) = DTC_AGING_COUNTER_CLEAR;
        } 
        else
        {
        	
        }
      }
      else
      {
         DTC_STATUS_BIT3(i) = BIT_SET_ZERO;
      }

     /*-- bit4 & bit5 can not be initial here. 
      the two value only read from E2 first and then update in running time and reset only when 14 request. --*/
      
      
      DTC_STATUS_BIT6(i) = BIT_SET_ONE;

      DTC_STATUS_BIT7(i) = BIT_SET_ZERO;

      DTC_TestFailedCounter[i] = DTC_TEST_FAILED_COUNTER_CLEAR;
      DTC_ConfirmedCounter[i] = DTC_CONFIRM_COUNTER_CLEAR;
      Ext_failedcycle_cnt_updt[i] = DTC_FALSE;
      LastMonitorState[i] = MONITOR_CYCLE_NOTCOMPLETE;
          
   }
   
}

/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : DTC_Status_14Service_Hook
 *
 * Description   : The diagnose 14 service  hook function.
 *
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
void Dtc_Status_14Service_Hook(uint32 groupofDTC)
{
  uint16 i = 0u;
  uint16 j = 0u;
  uint16 r = 0u;

  for (i = 0u;i < DTC_NUMBER_SIZE;i++) 
  {
      //if ((groupofDTC == 0xFFFFFF00U) || ((DTC_CODE(i) & 0xF0000000U) == groupofDTC)) /* DTC group can be defined */
      if (1) //Dtc_Status_14Service_Hook call after chek groupofDTC
      { 
          if(gDtc_Attribute_Table[i].RestableFlag == DTC_RESTABLE)
          {
             DTC_CODE(i) &= 0xFFFFFF00U; 
                                
          }
          else
          {
             DTC_CODE(i) &= 0xFFFFFF80U;  /*keep the bit7 state */
          }
                  
          DTC_CODE(i) |= 0x00000050U;
            
	      /*Clear Extend data*/
	      for(r=0u; r<DTC_EXD_DATA_TYPE_SIZE/4u; r++)
	      {
		      DTC_EXT_DATA(i)[r] = EXD_DATA_INITIAL; 	      	
	      }	
	      Ext_failedcycle_cnt_updt[i] = DTC_FALSE;    
	      
	      #ifdef USE_SNAPSHOT_DATA
	      
	      /*Clear freezeframe data*/	
	      if(DTC_NO_SNAPSHOT != gDtc_Attribute_Table[i].WithFreezeFrameFlag)
	      {
		      for(j=0u; j<DTC_SNAPSHOT_TYPE_SIZE/4u; j++)
			  {
			  	  DTC_SNAPSHOT_DATA(i)[j] = FREEZE_DATA_INITIAL;
			  }	      	
	      } 
	      else
	      {
	      	
	      }
	      
	      #endif
          
          DTC_TestFailedCounter[i] = DTC_TEST_FAILED_COUNTER_CLEAR;
          DTC_ConfirmedCounter[i] = DTC_CONFIRM_COUNTER_CLEAR;
          DTC_This_Cycle_Failed_Flag[i] = DTC_FALSE;
          LastMonitorState[i] = MONITOR_CYCLE_NOTCOMPLETE;
          
          #ifdef Sevice14ClearAllFaultAndRecov
          dDiag_vFaultClear();
          #endif
          
      } 
      else 
      {
         ;/*do nothing*/
      }

  }
  
}

/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : DTC_StatusUpdate
 *
 * Description   : update all the DTC timer and DTC status bit value.
 *
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
   
#ifdef ROLLING_MODE    

void Dtc_StatusUpdate(void) 
{
	uint16 i = 0u;
	uint8 MatureTestResult = DTC_FALSE;
	uint8 ConfirmTestResult = DTC_FALSE;
		
	for(i=0u;i<DTC_NUMBER_SIZE;i++)
	{	
		if(gDtc_Attribute_Table[i].DtcMonitorType != DETECT_IN_INITIALIZATION) 
	    { 	   		   
	  	   MatureTestResult = Dtc_MatureCounterState(i,stc_dDiag_FaultFlg.FaultFlagArray[i]);
	       ConfirmTestResult = Dtc_ConfirmedCounterState(i, MatureTestResult);
	       Dtc_StatusBitsUpdate(i,MatureTestResult,ConfirmTestResult);
	    }
	    else 
		{
		   ;
		}
	      
	}
	
}

#else /*REALTIME_CALL_MODE*/

void Dtc_StatusUpdate(uint32 aDTCNumber, uint8 testResult)/*extern type, called by FaultDetect Moudle*/
{
	uint16 i = 0u;
	uint8 MatureTestResult = DTC_FALSE;

	if ((DTC_DelayOnBoot >= (DTC_DELAY_ON_BOOT/DTC_TASK_TIME)) && (gDTCSwitch == DTC_ENABLE))
	{
		for (i = 0u;i < DTC_NUMBER_SIZE; i++) 
		{
			if ((gDtc_Attribute_Table[i].DtcHexCode & 0xFFFFFF00) == (aDTCNumber & 0xFFFFFF00)) 
			{
				MatureTestResult = Dtc_MatureCounterState(i,testResult);
				ConfirmTestResult = Dtc_ConfirmedCounterState(i, MatureTestResult);
				Dtc_StatusBitsUpdate(i,MatureTestResult,ConfirmTestResult);
			} 
			else
			{
				
			}
		}
	} 
	else 
	{
	 ;
	}
}

#endif   
  


/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : DTC_Save
 *
 * Description   : save the DTC data into EEPROM.
 *
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
uint8 Dtc_Save(void)
{ 
  uint8 flag = EEPROM_OK;
  
  flag = mEEPROM_Write_Flash((INT32U *)DTC_RAM_START_ADDR); 
 
  return flag;
  
}


/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : Dtc_MatureCounterState
 *
 * Description   : process the MonitorCycle and give its state
 *
 * Inputs        : uint8 aIndex, uint8 testResult
 *
 * Outputs       : Dtc_MonitorState
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
   
static uint8 Dtc_MatureCounterState(uint16 aIndex, uint8 testResult) 
{
    uint8 Dtc_MonitorState = MONITOR_CYCLE_NOTCOMPLETE;

    /*------------------------  test failed mature count begin  ---------------------------*/
    
    if (testResult == DTC_TEST_FAILED) 
    { 
        if(DTC_UNRESTABLE == gDtc_Attribute_Table[aIndex].RestableFlag)  
        {                                                           
           Dtc_MonitorState = MONITOR_CYCLE_END_IN_FAIL;
        }   
        else if(IMMEDIATE == gDtc_Attribute_Table[aIndex].IsImmediateType)   
        {
           Dtc_MonitorState = MONITOR_CYCLE_END_IN_FAIL;
           
           #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_ON)     
             DTC_TestFailedCounter[aIndex] = DTC_FAIL_MATURE_THRESHOLD; 
           #else
             DTC_TestFailedCounter[aIndex] = gDtc_Attribute_Table[aIndex].TestFailedMatureThreshold;
           #endif
        }        
        else   
        {   
            /*---if testfailed and current counter value is below zero, 
                  the counter must be set a positive value which ususlly is a step value---*/
            if (DTC_TestFailedCounter[aIndex] <= DTC_TEST_FAILED_COUNTER_CLEAR) 
            {  
               Dtc_MonitorState = MONITOR_CYCLE_NOTCOMPLETE; 
                              
               #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_ON)  
                 DTC_TestFailedCounter[aIndex] = DTC_FAIL_MATURE_STEP; 
               #else      
                 DTC_TestFailedCounter[aIndex] = gDtc_Attribute_Table[aIndex].MatureFailCountStep;                                        
               #endif           
            } 
            #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_ON)     
            else  if(DTC_TestFailedCounter[aIndex] < DTC_FAIL_MATURE_THRESHOLD) 
            #else
            else  if(DTC_TestFailedCounter[aIndex] < gDtc_Attribute_Table[aIndex].TestFailedMatureThreshold)
            #endif
            {
               Dtc_MonitorState = MONITOR_CYCLE_NOTCOMPLETE; 
               
               #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_ON)  
                 DTC_TestFailedCounter[aIndex] += DTC_FAIL_MATURE_STEP; 
               #else      
                 DTC_TestFailedCounter[aIndex] += gDtc_Attribute_Table[aIndex].MatureFailCountStep;
               #endif 

            }      
            else 
            {    
               Dtc_MonitorState = MONITOR_CYCLE_END_IN_FAIL;                
            }       
        }                    
  }
  /*-----------------------------------test failed end--------------------------------------*/

  /*-----------------------------------test passed begin------------------------------------*/
  else 
  {
       /*for unrestable DTC, if it has no fault occurs, the counter will decrease until to PASS state*/
       
      #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_ON)     
      if (DTC_TestFailedCounter[aIndex] > DTC_PASS_DEMATURE_THRESHOLD) 
      #else
      if (DTC_TestFailedCounter[aIndex] > -gDtc_Attribute_Table[aIndex].TestPassedDematureThreshold) 
      #endif        
      {            
         Dtc_MonitorState = MONITOR_CYCLE_NOTCOMPLETE; 
             
         #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_ON)  
           DTC_TestFailedCounter[aIndex] -= DTC_PASS_DEMATURE_STEP; 
         #else      
           DTC_TestFailedCounter[aIndex] -= gDtc_Attribute_Table[aIndex].MaturePassCountStep;
         #endif 
                     
      }   
      else
      {
         Dtc_MonitorState = MONITOR_CYCLE_END_IN_PASS;
      }

  }
  /*-----------------------------------test passed end--------------------------------------*/
  return Dtc_MonitorState;
  
}
/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : DTC_ConfirmedCounterState
 *
 * Description   : Confirm DTC Counter Logic
 *
 * Inputs        : aIndex: index of DTC code;
                   monitorResult: result of fault detect;
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
static uint8 Dtc_ConfirmedCounterState(uint16 aIndex, uint8 monitorResult) 
{
    uint8 Dtc_ConfirmState = DTC_NOT_CONFIRMED;
    /*this time test failed, for bit0*/
    if (monitorResult == MONITOR_CYCLE_END_IN_FAIL) 
    {
        #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_ON) 
        if (DTC_ConfirmedCounter[aIndex] >= DTC_FAIL_CONFIRM_THRESHOLD) /*if the threshold is 0,it means bit3  keeps pace with bit0*/
        #else
        if (DTC_ConfirmedCounter[aIndex] >= gDtc_Attribute_Table[aIndex].ConfirmMatureThreshold) 
        #endif
        {
            DTC_ConfirmedCounter[aIndex] = DTC_CONFIRM_COUNTER_CLEAR;
            
            Dtc_ConfirmState = DTC_CONFIRMED;
           
        }
        else
        {
            DTC_ConfirmedCounter[aIndex]++;
        }
    } 
    else
    {
        DTC_ConfirmedCounter[aIndex] = DTC_CONFIRM_COUNTER_CLEAR;  
    }
    
    return Dtc_ConfirmState; 
        
}

/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : Dtc_StatusBitsUpdate
 *
 * Description   : update DTC status bits
 *
 * Inputs        : uint8 bInedx,  uint8 monitorState
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
   
static void Dtc_StatusBitsUpdate(uint16 aIndex,uint8 monitorState,uint8 confirmState)     
{    
    if(DTC_UNRESTABLE == gDtc_Attribute_Table[aIndex].RestableFlag)
    {
        if(MONITOR_CYCLE_END_IN_FAIL == monitorState)/*first time monitor in fail or after 14request and then failed again*/
        { 
            if(DTC_TRUE != DTC_This_Cycle_Failed_Flag[aIndex])
            { 
                DTC_This_Cycle_Failed_Flag[aIndex] = DTC_TRUE;
                
                /*set the bit0*/
                #if (DTC_BIT0_SUPPORT)                    

                DTC_STATUS_BIT0(aIndex) = BIT_SET_ONE;
                                        
                #endif
                
                /*set the bit1*/
                #if (DTC_BIT1_SUPPORT)                       

                DTC_STATUS_BIT1(aIndex) = BIT_SET_ONE;
                
                #endif
                
                /*set the bit2*/
                #if (DTC_BIT2_SUPPORT) 

                DTC_STATUS_BIT2(aIndex) = BIT_SET_ONE;
                
                #endif


                /*clear bit 4,and then only when received 14 request it canbe set to 1 again*/
                #if (DTC_BIT4_SUPPORT) 

                DTC_STATUS_BIT4(aIndex) = BIT_SET_ZERO;
                #endif

                /*set bit5*/
                #if (DTC_BIT5_SUPPORT) 
                
                DTC_STATUS_BIT5(aIndex) = BIT_SET_ONE;

                #endif


                /*clear bit6, set 1 when received 14 request or being start a new operation cycle.*/
                #if (DTC_BIT6_SUPPORT) 
 
                DTC_STATUS_BIT6(aIndex) = BIT_SET_ZERO;
                #endif
                
                
            }
            else
            {
               ;
            }
        }
        else if(MONITOR_CYCLE_END_IN_PASS == monitorState) 
        {
            if(DTC_TRUE == DTC_STATUS_BIT6(aIndex))
            {
                /*reset the bit0*/
                #if (DTC_BIT0_SUPPORT)                    

                DTC_STATUS_BIT0(aIndex) = BIT_SET_ZERO;
                                        
                #endif
                
                
                #if (DTC_BIT6_SUPPORT) 

                DTC_STATUS_BIT6(aIndex) = BIT_SET_ZERO;

                #endif          
            }
            else
            {
               ;
            }         
            

            /*clear bit 4,and then only when received 14 request it canbe set to 1 again*/
            #if (DTC_BIT4_SUPPORT)

           
            DTC_STATUS_BIT4(aIndex) = BIT_SET_ZERO;
           
            #endif

        }
        else
        {
           ;
        }
    }
    else /* for restable DTC */
    {  
        if((monitorState == MONITOR_CYCLE_END_IN_FAIL)&&(LastMonitorState[aIndex] != MONITOR_CYCLE_END_IN_FAIL)) 
        { 
            /*set the bit0*/
            
            #if (DTC_BIT0_SUPPORT)                    

            DTC_STATUS_BIT0(aIndex) = BIT_SET_ONE;
                                    
            #endif              
                                                                       
            if(DTC_This_Cycle_Failed_Flag[aIndex] != DTC_TRUE) /*cleared  in 14 hook*/
            {
                /*set the bit1*/
                #if (DTC_BIT1_SUPPORT)                      
                
                DTC_STATUS_BIT1(aIndex) = BIT_SET_ONE;
                
                #endif
                
                /*set the bit2*/
                #if (DTC_BIT2_SUPPORT)

                DTC_STATUS_BIT2(aIndex) = BIT_SET_ONE;

                #endif


                /*clear bit 4,and then only when received 14 request it canbe set to 1 again*/
                
                #if (DTC_BIT4_SUPPORT)

                DTC_STATUS_BIT4(aIndex) = BIT_SET_ZERO;

                #endif                    
                

                /*set bit5*/
                #if (DTC_BIT5_SUPPORT)

                DTC_STATUS_BIT5(aIndex) = BIT_SET_ONE;

                #endif

                
                /*clear bit6, set 1 when received 14 request or being start a new operation cycle.*/
                #if (DTC_BIT6_SUPPORT)

                DTC_STATUS_BIT6(aIndex) = BIT_SET_ZERO;

                #endif            
            }
            else
            {
            	
            }
            
            DTC_This_Cycle_Failed_Flag[aIndex] = DTC_TRUE;
   
                     
        }
        else if((monitorState == MONITOR_CYCLE_END_IN_PASS)&&(LastMonitorState[aIndex] != MONITOR_CYCLE_END_IN_PASS))/*init state is middlestate(NOTCOMPLETE state). failcounter value=0. so not pass state.*/
        {            
            /*clear the bit0*/
            
            #if (DTC_BIT0_SUPPORT)                    

            DTC_STATUS_BIT0(aIndex) = BIT_SET_ZERO;
                                    
            #endif
    

            /*clear bit 4,and then only when received 14 request it canbe set to 1 again*/
            #if (DTC_BIT4_SUPPORT)                    
 
            DTC_STATUS_BIT4(aIndex) = BIT_SET_ZERO;
                                   
            #endif


            
            if(DTC_TRUE == DTC_STATUS_BIT6(aIndex))
            {
                #if (DTC_BIT6_SUPPORT)                    

                DTC_STATUS_BIT6(aIndex) = BIT_SET_ZERO;
                                       
                #endif
            }
            else
            {
            	
            }
                    
        }
        else 
        {
            ;
        }

    }   
    
    if(confirmState == DTC_CONFIRMED)
    {
        
        #if (DTC_BIT3_SUPPORT)

        DTC_STATUS_BIT3(aIndex) = BIT_SET_ONE;

        #endif

        #if (DTC_BIT7_SUPPORT) 
         
        if(DTC_WITH_WARNING_INDICATOR == gDtc_Attribute_Table[aIndex].WithWaringIndicator)
        {
           DTC_STATUS_BIT7(aIndex) = BIT_SET_ONE;
        }  
        else
        {
        	;
        } 
        #endif    
    }
    else
    {
    	
    }
       
    Dtc_ExtDataUpdate(aIndex); 
    
    #ifdef USE_SNAPSHOT_DATA
    /*assign the freezedata */
    Dtc_FFDataUpdate(aIndex);
    #endif

    /*part ExtData update logic may add here*/

    LastMonitorState[aIndex] = monitorState;   
    
}



/* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : InitializationFault_DTCStatusUpdate()
 *
 * Description   : only used to detect the init-process fault and update the relvant DTC info
 *
 * Inputs        : None 
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
 void InitializationFault_DTCStatusUpdate(void) 
 {
    /*If detect type is INITIALIZATION, its process type must be IMMEDIATE. */
    uint16 i = 0u;
    uint8 Temp_MatureTestResult = DTC_FALSE;
    uint8 Temp_ConfirmTestResult = DTC_FALSE;

    
    for(i=0u;i<DTC_NUMBER_SIZE;i++)
  	{	
		if(gDtc_Attribute_Table[i].DtcMonitorType == DETECT_IN_INITIALIZATION) 
		{ 	   		   
			Temp_MatureTestResult = Dtc_MatureCounterState(i,stc_dDiag_FaultFlg.FaultFlagArray[i]);
			Temp_ConfirmTestResult = Dtc_ConfirmedCounterState(i, Temp_MatureTestResult);
			Dtc_StatusBitsUpdate(i,Temp_MatureTestResult,Temp_ConfirmTestResult);
		}
		else 
		{
		 ;
		}
  	}  
  	
 }
 #ifdef  USE_SNAPSHOT_DATA
 /* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : Dtc_ExtDataUpdate()
 *
 * Description   : Update the extenddata of DTC according to state of DTC status detecting.
 *
 * Inputs        : None
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
static void  Dtc_ExtDataUpdate(uint16 aIndex)
{
    /*number of failed IGN cycles*/
	if((DTC_TRUE == DTC_This_Cycle_Failed_Flag[aIndex])&&(DTC_TRUE != Ext_failedcycle_cnt_updt[aIndex]))
	{
	    Ext_failedcycle_cnt_updt[aIndex] = DTC_TRUE;
		DTC_EXT_NUM_FAILED_CYCLE_DATA(aIndex)++;
	}
	else
	{
		;
	}
	/*other extend data canbe add here*/    	
	
}

 /* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : Dtc_FFDataUpdate()
 *
 * Description   : capture the freezedata
 *
 * Inputs        : uint16 aIndex
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
static void  Dtc_FFDataUpdate(uint16 aIndex)
{
    uint16 j;
    uint8  FFDNumber;
    uint16 didcode;
    uint8  didsize;
    uint8  didIndex;
    
    uint8  dataoffset = 0u;
    
    if(DTC_NO_SNAPSHOT != gDtc_Attribute_Table[aIndex].WithFreezeFrameFlag)
    {
        
	    if((1U == DTC_EXT_NUM_FAILED_CYCLE_DATA(aIndex)) && (DTC_TRUE == DTC_This_Cycle_Failed_Flag[aIndex]))
	    {
	    	/*get the freezedata here*/
	    	
	    	FFDNumber = gDtc_Attribute_Table[aIndex].FreezeFrameNumber;	
	    	
	    	for(j=0u; j< Dtc_FFRecCfgTable[FFDNumber-1u].NumOfDid;j++)
	    	{
	    	    didIndex = Dtc_FFRecCfgTable[FFDNumber-1u].DidRefTable[j];
	    		didcode = Dtc_DidCfgTable[didIndex].Did;
	    		didsize = Dtc_DidCfgTable[didIndex].DataSize;
	    		
	    		Dtc_DataCopy(&DTC_SNAPSHOT_DATA_BYTE(aIndex)[dataoffset],Dtc_DidCfgTable[didIndex].DataBuf,didsize);
	    		dataoffset += didsize;
	    	}
	    	
	    }   
	    else
	    {
	    	;
	    } 	
    }	
}
#endif
 /* BEGIN_FUNCTION_HDR
 ************************************************************************************************
 * Function Name : Dtc_DataCopy()
 *
 * Description   : copy data from one buffer into another buffer.
 *
 * Inputs        : uint8* Dest,const uint8* Src,uint16 Cnt
 *
 * Outputs       : None
 *
 * Limitations   : None
 *
 ************************************************************************************************
   END_FUNCTION_HDR */
  
void Dtc_DataCopy( uint8* Dest,const uint8* Src,uint16 Cnt)
{
    uint16 i;
    
    for(i=0u;i<Cnt;i++)
    {
       Dest[i]=Src[i];
    }
}


/********************************************** END ******************************************************/
