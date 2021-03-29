/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @Filename:  dDiagScheduEntry.c     
*
* @brief      This file defines the entry of DiagnosticTask.             
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2013/8/30     CODER1       N/A            Original
*     
************************************************************************************************/

#ifndef D_DIAG_SCAHEDU_ENTRY_C
#define D_DIAG_SCAHEDU_ENTRY_C
#endif

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include   	"dDiagScheduEntry.h"

/* *****************************************************************************
   *****************************************************************************
   static variable declaration
   *****************************************************************************
   *****************************************************************************/
//static INT8U u8_ems1msg_err;
//static INT8U u8_esp3msg_err;
static INT8U u8_BMS04msg_err;
static INT8U u8_LastIgnState;
static INT8U u8_DelayCnt;

static INT8U u8_StackScheCnt;
static INT8U u8_DtcScheCnt;
static INT8U u8_DecScheCnt;
/*******************************************************************************
* Prototypes of internal functions
********************************************************************************/
static void dDiag_vDiscardNwkErrInfo(void);
static void dDiag_vRecoverNwkErrInfo(void);

/* *****************************************************************************
   Function:        dDiag_vDiscardNwkErrInfo
   Description:     discard the network error
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void dDiag_vDiscardNwkErrInfo(void) 
{  
    //u8_ems1msg_err = gEMSErrEvt;
    //u8_esp3msg_err = gESPErrEvt;
    //gEMSErrEvt = 0u;
    //gESPErrEvt = 0u;
    u8_BMS04msg_err = gbCANMissingErrEvt;
    gbCANMissingErrEvt = 0;
}

/* *****************************************************************************
   Function:        dDiag_vRecoverNwkErrInfo
   Description:     recover monitoring network error.
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
__inline static void dDiag_vRecoverNwkErrInfo(void) 
{  
	//gEMSErrEvt = u8_ems1msg_err;
	//gESPErrEvt = u8_esp3msg_err;
	gbCANMissingErrEvt = u8_BMS04msg_err;
}

/* *****************************************************************************
   Function:        dDiag_vCommStackTask_Entry
   Description:     Entry for diag-protocol stack
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
   
void dDiag_vCommStackTask_Entry(void)
{
    u8_StackScheCnt ++;
    
	if(u8_StackScheCnt >= DIAG_COMSTACK_SCAHEDULE)
    {
    	u8_StackScheCnt = 0u;             
       
        SetIgnStatus(SYS_IGN_STATE);
   
    #if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL==STD_ON)

        /*process timer such as S3\P2\P2*\27service delay*/
        DslInternal_Timer_CallbackTask();//test by ych

        if(E_OK == App_DiagnosticActive())
        {
           CanTp_MainFunction();
           Dcm_MainFunction();        
        }
        else
        {
        	
        }

    #endif      
        
    }
    else
    {
    	
    }

}

/* *****************************************************************************
   Function:        dDiag_vDtcStrategyTask_Entry
   Description:     Entry for Dtc management
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
   
void dDiag_vDtcStrategyTask_Entry(void)
{
    u8_DtcScheCnt ++;
    
	if(u8_DtcScheCnt >= DIAG_DTCUPDATE_SCAHEDULE)
    {
        u8_DtcScheCnt = 0u;
        
    	if(IGN_OFF == SYS_IGN_STATE)
        {
            dDiag_vDiscardNwkErrInfo();  
            u8_LastIgnState = IGN_OFF;     
        }
        else if((IGN_ON == SYS_IGN_STATE)&&(IGN_OFF == u8_LastIgnState))/*when IGN OFF and then set to ON at once,this need ignore the initial err state*/
        {
            dDiag_vDiscardNwkErrInfo(); 
            
            u8_DelayCnt ++;            
            if(u8_DelayCnt >= DELAY_DETECT_MSG_ERR/DIAG_DTCUPDATE_SCAHEDULE) /*wait until CanSig module has cleared the error info from IGN OFF state*/
            {
	            u8_LastIgnState = IGN_ON;  
	            u8_DelayCnt = 0u;           	
            }
            else
            {
            	
            }
 
        }
        else
        {
        	
        }

        /** DTC Main Logic **/
        Dtc_MainTask();
        
        /*recovery the actual fault state*/
        if(IGN_OFF == SYS_IGN_STATE)
        {
            dDiag_vRecoverNwkErrInfo();        
        } 
        else if((IGN_ON == SYS_IGN_STATE)&&(IGN_OFF == u8_LastIgnState))
        {
            dDiag_vRecoverNwkErrInfo();    
        }  
        else
        {
        	
        }
    }
    else
    {
    	
    }
}

/* *****************************************************************************
   Function:        dDiag_vRuntimeDecisionTask_Entry
   Description:     Entry for diag-decision task
   Parameters:      Input:    None
                    Output:   None
   Notes:           None
                   
   *****************************************************************************/
   
void dDiag_vRuntimeDecisionTask_Entry(void)
{
    u8_DecScheCnt ++;
    
	if(u8_DecScheCnt >= DIAG_DECISION_SCAHEDULE)
    {
        u8_DecScheCnt = 0u;
        
       /* Get diag info */
        dDiag_vGetRuntimeErrInfo();
    
       /* set diagnostic status */
        dDiagDec_vGatherFaultInfo();
       
       /* signal diagnostic */
        dDiagDec_vMainTask();                
    }
    else
    {
    	
    }
}

/* *****************************************************************************
   Function:        dDiag_vInitDecisionTask_Entry
   Description:     Entry for init-process diag-decison task
   Parameters:      Input:    None
                    Output:   None
   Notes:           only be called once in the end of system init.
                   
   *****************************************************************************/
   
void dDiag_vInitDecisionTask_Entry(void)
{
    /*init the variables*/
    //u8_ems1msg_err = 0u;
    //u8_esp3msg_err = 0u;
    u8_BMS04msg_err = 0;
    u8_LastIgnState = 0u;
    u8_DelayCnt = 0u;                            

	u8_StackScheCnt = 0u;
	u8_DtcScheCnt = 0u;
	u8_DecScheCnt = 0u;

   /* Get Init_Process diag info */
    dDiag_vGetInitErrInfo();

   /* set diagnostic status */
    dDiagDec_vGatherFaultInfo();
   
   /* signal diagnostic */
    dDiagDec_vMainTask();        
        
}

/*********************************************** End ************************************************/
