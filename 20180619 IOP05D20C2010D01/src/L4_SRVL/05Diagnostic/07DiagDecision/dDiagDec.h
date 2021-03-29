/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     dDiagDec.h
*
* @brief    Head file for diag-decision module
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/06/24     ----        N/A          Original
*     1.1	     2013/07/25		CODER1	  N/A		   Recoding according to requirements disscussion
*     
************************************************************************************************/
#ifndef _D_DIAGDEC_H
#define _D_DIAGDEC_H

#ifdef 	D_DIAGDEC_C
#define D_DIAGDEC_EXT
#else
#define D_DIAGDEC_EXT 	extern
#endif

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
//#include	"types.h"
#include    "SysConfig.h"
#include    "Dtc_Types.h"
//#include    "hCanSig.h"
//#include    "hIGN.h"
//#include 	"hKF.h"
//#include    "hMDRV.h"
#include    "dDiagDecCfg.h"
#include   	"dDiagFaultEvent.h"
//#include 	"hFailSafe.h"
//#include 	"hAngCal.h"
#include    "App_Dcm.h"

/*******************************************************************************
 *******************************************************************************
   Genernal Macros
 *******************************************************************************
 *******************************************************************************/

/* fault level definition */

#define FAULT_LEVEL_OK     (INT8U)0
#define FAULT_LEVEL_C      (INT8U)1
#define FAULT_LEVEL_B      (INT8U)2
#define FAULT_LEVEL_A      (INT8U)3


/* fault lamp */
#define FAULT_LAMP_ON   1u
#define FAULT_LAMP_OFF  0u

/* Assit state */
#define EPS_ENABLE    1u
#define EPS_DISABLE   0u

/* Sleep state */
#define SLEEP_ENABLE    1u
#define SLEEP_DISABLE   0u

/* send state */
#define SEND_ENABLE     1u
#define SEND_DISABLE    0u

/* Rec state */
#define RECIVE_ENABLE   1u
#define RECIVE_DISABLE    0u


#define IGN_ON        1u
#define IGN_OFF       0u

#define VALUE_INVALID  0u
#define VALUE_VALID    1u

#define CLEAR_STEERING_ANGLE_ZERO_POS_CMD  0x05
#define SET_STEERING_ANGLE_ZERO_POS_CMD    0x03

/*******************************************************************************
 *******************************************************************************
 structure for all Inputs & Outputs varibales
 *******************************************************************************
 *******************************************************************************/
typedef struct      
{
   /*----- fault level (output)-----*/
   INT8U  FaultLevel; 
   /*----- fault lamp  (output)-----*/
   INT8U  FaultLampFlg;

   /*----------------- error flag (input mask)-----------------*/  
    
    INT8U   bLV12UnderErr;
    INT8U   bLV12OverErr;
    INT8U   bLV13UnderErr;
    INT8U   bLV13OverErr;
    INT8U   bINPUT_RelayErr;
    INT8U   boutputCurrentSenError;  
    INT8U   bPG_SENSError;  
    INT8U   bOverPFCUoutVoltErr;  
    INT8U   bHWDCDC_OCPErr;  
    INT8U   bOverDCUoutVoltErr;  
    INT8U   bDCDCPrechargeTimeoutErr;  
    INT8U   bPFCBoostFailErr;  
    INT8U   bOverPFCUoutIErr;  
    INT8U   bOverUinVoltErr;  
    INT8U   bUnderUinVoltErr;  
    INT8U   bUinVoltOpenErr;
    INT8U   bUnderDCUoutVoltErr;  
    INT8U   bTempWarinOutOffErr;  
    INT8U   bOverTempCoolErr; 
   /*---- Network Fault----*/
   INT8U  BUSOFFErr; 
   INT8U  bms04MsgErr;
   
  
      
   /*----- IGN signal abnormal----*/
   INT8U  IgnSigErr;
   
   /*input*/
  
   
   INT8U  IgnState;
   
   INT16U INPUTVoltage;
   INT16U INPUTCurrent;
   INT16U CPDUTY;
   
   /* output */
   /* signal filtered */
   
   
   INT16U OUTVoltage;   
   INT16U OUTCurrent;
   INT8U OBCTemp;

   
   
   /* Assit flag */
   INT8U  AssitIndicationFlg;  
   
   /* Send Message flag*/
   INT8U  MessageSendFlag;
   
   /* Receive Message flag*/
   INT8U  MessageRecFlag;
   
   
   
   
  
   
   
   
   
   
   
   
   
   
}DiagSig_TYPE;


/*Gloabl variable Definition*/
D_DIAGDEC_EXT  DiagSig_TYPE  stc_dDiagDec_Sig;

/*******************************************************************************
 *******************************************************************************
 Macros for Module Input & Output
 *******************************************************************************
 *******************************************************************************/
 
#define   SYS_FAULT_LEVEL         stc_dDiagDec_Sig.FaultLevel   /*Output Fault Level*/
#define   SYS_FAULT_LAMP_FLG      stc_dDiagDec_Sig.FaultLampFlg /*Output FaultLamp indication*/
         
/*-----------------------------------------------------------------------------
    &&~  Input  All the Fault Flags
 -----------------------------------------------------------------------------*/ 	


#define	  SYS_bLV12UnderErr   				stc_dDiagDec_Sig.bLV12UnderErr
#define	  SYS_bLV12OverErr   				stc_dDiagDec_Sig.bLV12OverErr
#define	  SYS_bLV13UnderErr   				stc_dDiagDec_Sig.bLV13UnderErr
#define	  SYS_bLV13OverErr  				stc_dDiagDec_Sig.bLV13OverErr
#define	  SYS_bINPUT_RelayErr   			stc_dDiagDec_Sig.bINPUT_RelayErr
#define	  SYS_boutputCurrentSenError   		stc_dDiagDec_Sig.boutputCurrentSenError 
#define	  SYS_bPG_SENSError   				stc_dDiagDec_Sig.bPG_SENSError
#define	  SYS_bOverPFCUoutVoltErr  			stc_dDiagDec_Sig.bOverPFCUoutVoltErr
#define	  SYS_bHWDCDC_OCPErr  				stc_dDiagDec_Sig.bHWDCDC_OCPErr 
#define	  SYS_bOverDCUoutVoltErr   			stc_dDiagDec_Sig.bOverDCUoutVoltErr 
#define	  SYS_bDCDCPrechargeTimeoutErr   	stc_dDiagDec_Sig.bDCDCPrechargeTimeoutErr
#define	  SYS_bPFCBoostFailErr  			stc_dDiagDec_Sig.bPFCBoostFailErr
#define	  SYS_bOverPFCUoutIErr   			stc_dDiagDec_Sig.bOverPFCUoutIErr 
#define	  SYS_bOverUinVoltErr   			stc_dDiagDec_Sig.bOverUinVoltErr 
#define	  SYS_bUnderUinVoltErr   			stc_dDiagDec_Sig.bUnderUinVoltErr  
#define	  SYS_bUinVoltOpenErr   			stc_dDiagDec_Sig.bUinVoltOpenErr
#define	  SYS_bUnderDCUoutVoltErr   		stc_dDiagDec_Sig.bUnderDCUoutVoltErr
#define	  SYS_bTempWarinOutOffErr   		stc_dDiagDec_Sig.bTempWarinOutOffErr 
#define	  SYS_bOverTempCoolErr   			stc_dDiagDec_Sig.bOverTempCoolErr
#define	  SYS_BUSOFF_ERR        			stc_dDiagDec_Sig.BUSOFFErr
#define	  SYS_BMS04MSG_ERR      			stc_dDiagDec_Sig.bms04MsgErr



 
/*-----------------------------------------------------------------------------
    &&~  Input  Raw Signal value
 -----------------------------------------------------------------------------*/           	


#define	  OBC_INPUTVoltage         stc_dDiagDec_Sig.INPUTVoltage
#define	  OBC_INPUTCurrent         stc_dDiagDec_Sig.INPUTCurrent
#define	  OBC_CPDUTY               stc_dDiagDec_Sig.CPDUTY

/*-----------------------------------------------------------------------------
    &&~  Output Filter Signal value
 -----------------------------------------------------------------------------*/  	

#define   SYS_MSG_SND_FLG         stc_dDiagDec_Sig.MessageSendFlag

#define   SYS_MSG_REC_FLG         stc_dDiagDec_Sig.MessageRecFlag


#define	  SYS_IGN_STATE           stc_dDiagDec_Sig.IgnState //obc 12V LV POWER.


#define	  SYS_ASSIT_FLG           stc_dDiagDec_Sig.AssitIndicationFlg/*Output Assit Indication*/


#define	  SYS_SLEEP_FLG           stc_dDiagDec_Sig.SleepFlg /*Output PreSleep Indication*/

#define	  OBC_OUTVoltage           stc_dDiagDec_Sig.OUTVoltage /*dcdc ouput volt*/
#define	  OBC_OUTCurrent           stc_dDiagDec_Sig.OUTCurrent /*dcdc ouput current*/
#define	  OBC_OBCTemp           stc_dDiagDec_Sig.OBCTemp /*OBC temp*/


/*******************************************************************************
 *******************************************************************************
 Macros for Signals Process
 *******************************************************************************
 *******************************************************************************/

#define  SetSysFaultLevel(x)               stc_dDiagDec_Sig.FaultLevel = x



#define  SetOBC_OUTVoltagerValue(x)        	stc_dDiagDec_Sig.OUTVoltage = x
#define  SetOBC_OUTCurrentValue(x) 			stc_dDiagDec_Sig.OUTCurrent = x
#define  SetOBC_OBCTempValue(x)       		stc_dDiagDec_Sig.OBCTemp = x
#define  SetOBC_INPUTVoltageValue(x)    	stc_dDiagDec_Sig.INPUTVoltage = x
#define  SetOBC_INPUTCurrentValue(x)      	stc_dDiagDec_Sig.INPUTCurrent = x
#define  SetOBC_OBC_CPDUTYValue(x)      	stc_dDiagDec_Sig.CPDUTY = x

/*******************************************************************************
 *******************************************************************************
 External Function
 *******************************************************************************
 *******************************************************************************/
D_DIAGDEC_EXT void dDiagDec_vInit(void);
D_DIAGDEC_EXT void dDiagDec_vGatherFaultInfo(void);
D_DIAGDEC_EXT void dDiagDec_vMainTask(void);


#endif					

/*********************************************** End ************************************************/
