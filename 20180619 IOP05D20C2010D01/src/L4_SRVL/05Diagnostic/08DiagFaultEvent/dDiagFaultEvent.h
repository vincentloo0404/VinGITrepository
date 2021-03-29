/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @Filename:  dDiagFaultEvent.h     
*
* @brief      This file masks all the fault flags of fault detecting moudle.    
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2013/8/20     CODER1      N/A            Original
*     
************************************************************************************************/

#ifndef _D_DIAG_FAULT_EVENT_H
#define _D_DIAG_FAULT_EVENT_H

#ifdef 	D_DIAG_FAULT_EVENT_C
#define D_DIAG_FAULT_EVENT_EXT
#else
#define D_DIAG_FAULT_EVENT_EXT 	extern
#endif

/*********************************************************************************************
 *********************************************************************************************
 Include files
 *********************************************************************************************
 *********************************************************************************************/
#include "Dtc_Cfg.h"
//#include "hClbData.h"
//#include "hMDIAG.h"
//#include "hCanSig.h"
//#include "hASDrv.h"
//#include "hTASDrv.h"
//#include "hTSDrv.h"
//#include "hTLE7189.h"
//#include "hTemp.h"
//#include "hVoltageMonitor.h"
//#include "h_AD2S1210.h"
//#include "hSBC_UJA1076A.h"
//#include "hPower.h"
#include "m_EEPROM_Drv.h"

#include "dDiagDec.h"

#include "dDiagScheduEntry.h"
//#include "m_Flash_Drv.h"
//#include "m_Clock_Drv.h"
//#include "pStateMachine.h"
//#include "hAngCal.h"

//#include "types.h"


/*********************************************************************************************
 *********************************************************************************************
 Typedef definition
 *********************************************************************************************
 *********************************************************************************************/
   
/*-------------------------------------------------------------------------------------------*\
                     All fault events are defined by these data-structures
        and DTC codes sequence must be accordance with the events and point to point  
\* ------------------------------------------------------------------------------------------*/                    
                

/*-----------------------------------------------------------------------------
    &&~    for Motor fault  
 -----------------------------------------------------------------------------*/
typedef  struct
{
    INT8U   MotCtrlErrFlg;
    INT8U   PreDrvErrFlg; 
    INT8U   MotPosErrFlg;
    INT8U   MotCurrErrFlg;
    INT8U   ReslvVoltErrFlg;
} MotorFault;


/*-----------------------------------------------------------------------------
    &&~   for TAS fault 
 -----------------------------------------------------------------------------*/
typedef  struct
{
    INT8U   TSSigLostFlg;
    INT8U   TSSigCharacterErrFlg;
    INT8U   ASSigLostFlg;
    INT8U   ASSigCharacterErrFlg;
    INT8U   ASMechanicalErrFlg;
    INT8U   TASVoltErrFlg;  /*5V*/
    
} TASFault;


/*-----------------------------------------------------------------------------
    &&~   for Network fault 
 -----------------------------------------------------------------------------*/
typedef  struct
{
    INT8U   BusOffFlg;
    INT8U   EMSMsgErrFlg;
    INT8U   ESPMsgErrFlg;
    INT8U   BMSMsgErrFlg;
} NetworkFault;


/*-----------------------------------------------------------------------------
    &&~   for Volt supply  fault 
 -----------------------------------------------------------------------------*/
typedef  struct
{
    INT8U   LowVoltFlg;
    INT8U   HighVoltFlg;
    INT8U   ReduceVoltFlg;
    
} VoltFault;


/*-----------------------------------------------------------------------------
    &&~   for Genernal fault 
 -----------------------------------------------------------------------------*/
typedef  struct
{
    INT8U   ChargeErrFlg;
    INT8U   ClbDataErrFlg;
    INT8U   TempAbnormlErrFlg;
    INT8U   TempOverHighErrFlg;
    INT8U   IGSignalErrFlg;
    INT8U   AglValueErrFlg;    //not calibrated or overturn//
} GenernalFault;

typedef  struct
{
    INT8U   bLV12UnderErrFlg;
    INT8U   bLV12OverErrFlg;
    INT8U   bLV13UnderErrFlg;
    INT8U   bLV13OverErrFlg;
    INT8U   bINPUT_RelayErrFlg;
    INT8U   boutputCurrentSenErrorFlg;  
    INT8U   bPG_SENSErrorFlg;  
    INT8U   bOverPFCUoutVoltErrFlg;  
    INT8U   bHWDCDC_OCPErrFlg;  
    INT8U   bOverDCUoutVoltErrFlg;  
    INT8U   bDCDCPrechargeTimeoutErrFlg;  
    INT8U   bPFCBoostFailErrFlg;  
    INT8U   bOverPFCUoutIErrFlg;  
    INT8U   bOverUinVoltErrFlg;  
    INT8U   bUnderUinVoltErrFlg;  
    INT8U   bUinVoltOpenErrFlg;
    INT8U   bUnderDCUoutVoltErrFlg;  
    INT8U   bTempWarinOutOffErrFlg;  
    INT8U   bOverTempCoolErrFlg;  
	INT8U   bCANBUSOFFErrFlg;  
	INT8U   bCANMissingErrFlg;    
} OBCGenernalFault;
/*-----------------------------------------------------------------------------
    &&~   for MCU fault 
 -----------------------------------------------------------------------------*/
typedef  struct
{
    INT8U   McuMalfuntionFlg;/*clock err; abnormal reset*/
    INT8U   EepromChkErrFlg;
    INT8U   FlshRamChkErrFlg;
    
} McuFault;



/*-----------------------------------------------------------------------------
    &&~   for all faults 
 -----------------------------------------------------------------------------*/ 
typedef union 
{
   INT8U FaultFlagArray[DTC_NUMBER_SIZE];  
   
   struct
   {
   	  //MotorFault    dtcMotFault;
   	  //TASFault      dtcTASFault;
   	  //NetworkFault  dtcNetworkFault;
   	  //VoltFault     dtcVoltFault;
   	  OBCGenernalFault dtcGenerlFault;
   	  //McuFault      dtcMcuFault;   	  
   }FaultFlgAll;  /*the flag variables and DTC codes must be point to point and the sequence also must be consistent.*/ 
   	
}FaultFlagUnion_TYPE;  


/*********************************************************************************************
 *********************************************************************************************
 Global variable definition
 *********************************************************************************************
 *********************************************************************************************/
D_DIAG_FAULT_EVENT_EXT FaultFlagUnion_TYPE  stc_dDiag_FaultFlg;

/*---- global variable which indicate fault_information used in App layer -----*/
D_DIAG_FAULT_EVENT_EXT INT8U u8ClockErr;     
D_DIAG_FAULT_EVENT_EXT INT8U u8AbnormalReset;
D_DIAG_FAULT_EVENT_EXT INT8U u8ClbDataErr;
D_DIAG_FAULT_EVENT_EXT INT8U u8ChargeSt;
/*---- global variable which indicate fault_information used in App layer -----*/

 /********************************************************************************************
  *   Variable Marcos definition
 *********************************************************************************************/
/*------------------------ Marcos for all fault event -------------------------*/
#define  gbLV12UnderErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bLV12UnderErrFlg
#define  gbLV12OverErrEvt      			stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bLV12OverErrFlg
#define  gbLV13UnderErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bLV13UnderErrFlg
#define  gbLV13OverErrEvt      			stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bLV13OverErrFlg
#define  gbINPUT_RelayErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bINPUT_RelayErrFlg
#define  gboutputCurrentSenErrorEvt     stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.boutputCurrentSenErrorFlg
#define  gbPG_SENSErrorEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bPG_SENSErrorFlg
#define  gbOverPFCUoutVoltErrEvt      	stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bOverPFCUoutVoltErrFlg
#define  gbHWDCDC_OCPErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bHWDCDC_OCPErrFlg
#define  gbOverDCUoutVoltErrEvt      	stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bOverDCUoutVoltErrFlg
#define  gbDCDCPrechargeTimeoutErrEvt   stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bDCDCPrechargeTimeoutErrFlg
#define  gbPFCBoostFailErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bPFCBoostFailErrFlg
#define  gbOverPFCUoutIErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bOverPFCUoutIErrFlg
#define  gbOverUinVoltErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bOverUinVoltErrFlg
#define  gbUnderUinVoltErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bUnderUinVoltErrFlg
#define  gbUinVoltOpenErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bUinVoltOpenErrFlg
#define  gbUnderDCUoutVoltErrEvt      	stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bUnderDCUoutVoltErrFlg
#define  gbTempWarinOutOffErrEvt      	stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bTempWarinOutOffErrFlg
#define  gbOverTempCoolErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bOverTempCoolErrFlg
#define  gbCANBUSOFFErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bCANBUSOFFErrFlg
#define  gbCANMissingErrEvt      		stc_dDiag_FaultFlg.FaultFlgAll.dtcGenerlFault.bCANMissingErrFlg


#define  IGN_ERR_DEBOUNCE_TIME    (1000u/DIAG_DECISION_SCAHEDULE)/*Igntion key signal err debounce time*/

/*********************************************************************************************
 *********************************************************************************************
 External function definition
 *********************************************************************************************
 *********************************************************************************************/
D_DIAG_FAULT_EVENT_EXT void dDiag_vFaultFlagInit(void);
D_DIAG_FAULT_EVENT_EXT void dDiag_vGetInitErrInfo(void);
D_DIAG_FAULT_EVENT_EXT void dDiag_vGetRuntimeErrInfo(void);
D_DIAG_FAULT_EVENT_EXT void dDiag_vFaultClear(void);


#endif

/********************************************* end ****************************************************/