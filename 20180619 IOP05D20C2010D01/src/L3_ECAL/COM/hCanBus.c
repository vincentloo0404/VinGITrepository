/***********************************************************************************************
*
* Beijing Hualong Tech Inc.
* (c) Copyright 2012 Beijing Hualong Tech, Inc.
* ALL RIGHTS RESERVED.
*
************************************************************************************************
*
* @file   hCanBus.c  
*
* @brief  EPS Can Bus Diagnostic and Bus-Off Recovery Module  
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*      1.0      2013/10/31      IsstaGao      N/A          Original
*      1.1      2013/11/11     gaobaoquan     N/A        Optimize the format of the code    
************************************************************************************************/


/*-------------------------------------------------------------------------*/
/***                       External Includes                             ***/
/*-------------------------------------------------------------------------*/
#include 	"hCanBus.h"

#include 	"Common.h"
#include 	"m_CAN_Drv.h"
#include 	"m_CAN_Cfg.h"

/*-------------------------------------------------------------------------*/
/**                Can-Bus diagnostic structure definition                **/
/*-------------------------------------------------------------------------*/
typedef struct _CAN_ISR_OBJ 
{
    /*4 bytes*/
    INT16U u16_mBusRecFreq;
    INT16U u16_mBusRecCtrl;
    
    /*4 bytes*/
    INT16U u16_mBusRecTime;
    INT16U u16_mMsgSendCnt;
    INT16U u16_mMsgCntRec;

    /*2 bytes*/
    INT8U u8_mBusOffFlg;
    INT8U u8_mCanDigFlg; 

}CAN_BUS_ISR_TYPE,*P_CAN_BUS_ISR_TYPE;


/*-------------------------------------------------------------------------*/
/**        Local static variables declaration                              **/
/*-------------------------------------------------------------------------*/
static CAN_BUS_ISR_TYPE  STC_hCanBusState;
static INT16U            hCanBus_u16BusStDigTick;

/*-------------------------------------------------------------------------*/
/**        Local static function declaration                              **/
/*-------------------------------------------------------------------------*/
static INT8U hCanBus_u8BusFaultConfineSt(void);
static void hCanBus_vBusDiagAndHandle(void);
static void hCanBus_vBusOffErrCheck(void);
static void hCanBus_vBusOffRecover(void);

/* *****************************************************************************
Function:     hCanBus_u8BusFaultConfineSt   
Description:  indicates the Confinement State of the FlexCAN module
              
Parameters:      Input:    none
                 Output:   Can Bus srror State :
                 
                         CAN_BUS_ERR_ACTIVE 
                         CAN_BUS_ERR_PASSIVE
                         CAN_BUS_ERR_BUS_OFF
Notes:     
               
                   
***************************************************************************** */

INT8U hCanBus_u8BusFaultConfineSt(void)
{
    INT8U CanFaultState = CAN_BUS_ERR_ACTIVE;

    if(CAN_BUS_ERR_BUS_OFF == (mCAN_Get_Fault_Conf_State() & CAN_ERR_BUS_OFF_MSK))
    {
        CanFaultState = CAN_ERR_BUS_OFF_MSK;
    }
    else
    {
        CanFaultState = mCAN_Get_Fault_Conf_State();
    }
    
    return(CanFaultState);
} 

/* *****************************************************************************
Function:     hCanBus_vBusDiagModuleInit   
Description:  Bus Diag Module Init
              
Parameters:      Input:    none
                 Output:   none
Notes:     
               
                   
***************************************************************************** */
void hCanBus_vBusDiagModuleInit(void)
{
    STC_hCanBusState.u16_mBusRecFreq = CAN_BUSY_BUS_REC_TICK;
    STC_hCanBusState.u16_mBusRecCtrl = mComm_u16GetCurrCnt();
    
    STC_hCanBusState.u8_mCanDigFlg   = CAN_BUS_NORMAL_MODE;
    
    STC_hCanBusState.u8_mBusOffFlg   = CAN_BUS_OFF_FALSE;   
    
    STC_hCanBusState.u16_mBusRecTime = CAN_BUS_RECOVER_TIME_INIT;
    STC_hCanBusState.u16_mMsgSendCnt = CAN_ISR_MSG_COUNTER_RESET;
    STC_hCanBusState.u16_mMsgCntRec  = CAN_ISR_MSG_COUNTER_RESET;

    hCanBus_u16BusStDigTick          = CAN_BUS_ERR_DIG_THRE_CLR;
}


/* *****************************************************************************
Function:     hCanBus_vBusOffErrSwCheck   
Description:  
              
Parameters:      Input:    none
                 Output:   none
Notes:     
               must running under can-bus-normal mode
                   
***************************************************************************** */
void hCanBus_vBusOffErrCheck(void)
{
    if(CAN_BUS_ERR_BUS_OFF == hCanBus_u8BusFaultConfineSt())
    {
        STC_hCanBusState.u8_mCanDigFlg = CAN_BUS_RECOVER_MODE;  /*start bus-off recovery*/
        STC_hCanBusState.u8_mBusOffFlg = CAN_BUS_OFF_TRUE;      /*Set Bus-Off DTC Code*/
        
        mCAN_MB_All_Send_Clear();    /*Clear Can Message Send-buffer :HW-Buf or SW-Buf*/
        //hCanSig_BusRecoveryInit();   /*Clear Local Message Send-buffer*/ 
        
    	STC_hCanBusState.u16_mMsgSendCnt = CAN_ISR_MSG_COUNTER_RESET;

    	CAN_BOFF_AutoRec_En;         /*Enable automatic recovering from Bus Off state */
    
        STC_hCanBusState.u16_mBusRecFreq = CAN_BUSY_BUS_REC_TICK;
        STC_hCanBusState.u16_mBusRecCtrl = mComm_u16GetCurrCnt();     /*for over-time checking*/
        
        STC_hCanBusState.u16_mBusRecTime = CAN_BUS_RECOVER_TIME_INIT;     
    }
    else
    {
        /*Do Nothing*/
    }  
}

/* *****************************************************************************
Function:     hCanBus_vBusOffRecover   
Description:  
              
Parameters:      Input:    none
                 Output:   none
Notes:     
               
                   
***************************************************************************** */
void hCanBus_vBusOffRecover(void)
{
    if(STC_hCanBusState.u16_mBusRecFreq <= ((INT16U)(mComm_u16GetCurrCnt() - STC_hCanBusState.u16_mBusRecCtrl)))
    {
        STC_hCanBusState.u16_mBusRecCtrl = mComm_u16GetCurrCnt();     /*for over-time checking*/

        if(CAN_BUS_BUSY_REC_TIME > STC_hCanBusState.u16_mBusRecTime)
        {
            STC_hCanBusState.u16_mBusRecTime ++;
        }
        else
        {
            STC_hCanBusState.u16_mBusRecFreq = CAN_LAZY_BUS_REC_TICK; /*If fail, Retry Send Can-Message every 1000ms until successfully recover*/
        }

        //hCanSig_u8ImmeTxMsg_EPS_STE_1();   /*Retry Send Can-Message every 100ms or 1000ms*/
        //hCanSig_u8ImmeTxMsg_EPS_STE_2();   /*Retry Send Can-Message every 100ms or 1000ms*/

        if((CAN_BUS_ERR_BUS_OFF != hCanBus_u8BusFaultConfineSt()) && (CAN_ISR_BUS_OFF_REC_THRES <= STC_hCanBusState.u16_mMsgSendCnt))
        {
            STC_hCanBusState.u16_mBusRecTime = CAN_BUS_RECOVER_TIME_INIT; /*clear total recovery times*/
            STC_hCanBusState.u16_mBusRecFreq = CAN_BUSY_BUS_REC_TICK;     /*back to every-100ms-recovery mode*/
            
            CAN_BOFF_AutoRec_Dis;         /*Disable automatic recovering from Bus Off state*/
            
            STC_hCanBusState.u8_mBusOffFlg = CAN_BUS_OFF_FALSE;        /*Clear DTC code*/
            STC_hCanBusState.u8_mCanDigFlg = CAN_BUS_NORMAL_MODE;      /*Back to normal mode*/               
        }
        else
        {
	        mCAN_MB_All_Send_Clear();    /*Clear Can Message Send-buffer :HW-Buf or SW-Buf*/
	        //hCanSig_BusRecoveryInit();  
        }          
    }
    else
    {
        /*Do Nothing*/
    }
}
/* *****************************************************************************
Function:     hCanBus_vBusDiagAndHandle   
Description:  Can Bus Diag And Handle
              
Parameters:      Input:    none
                 Output:   none
Notes:     
               
                   
***************************************************************************** */
void hCanBus_vBusDiagAndHandle(void)
{
    if(CAN_BUS_RECOVER_MODE != STC_hCanBusState.u8_mCanDigFlg)
    {
        hCanBus_vBusOffErrCheck();     /*Bus-Off Error software check and handle */ 
    }  
    else
    {
        hCanBus_vBusOffRecover();
    }
}


/* *****************************************************************************
Function:     hCanBus_vBusStateMonitor   
Description:  Bus-Off Error Monitor and Handle
              
Parameters:      Input:    none
                 Output:   none
Notes:     
             Function calling period Must Not bigger than 65536ms
                   
***************************************************************************** */
void hCanBus_vBusStateMonitor(void)
{
    if(CAN_BUS_ST_DIG_SCHE_TICK <= hCanBus_u16BusStDigTick)
    {
        hCanBus_vBusDiagAndHandle(); /*Bus-Off Error Monitor and Handle*/

        hCanBus_u16BusStDigTick = CAN_BUS_ERR_DIG_THRE_CLR;
    }
    else
    {
        /*Do Nothing*/
    }
    
    hCanBus_u16BusStDigTick ++;    /*Do Not change position of this code*/  

} 

/* *****************************************************************************
Function:     hCanBus_u8UpdateBusOKCnt   
Description:  For ISR, to indicate can msg successfully sent once 
              
Parameters:      Input:    none
                 Output:   none :

Notes:     
               
                   
***************************************************************************** */
void hCanBus_u8UpdateBusOKCnt(void)
{
    STC_hCanBusState.u16_mMsgSendCnt += CAN_ISR_MSG_INCREASE_STEP;
}


/* *****************************************************************************
Function:     hCanBus_u8GetBusOffState   
Description:  return current can bus-off state
              
Parameters:      Input:    none
                 Output:   Can Bus State :
                 
                         CAN_BUS_OFF_TRUE 
                         CAN_BUS_OFF_FALSE
Notes:     
               
                   
***************************************************************************** */

INT8U hCanBus_u8GetBusOffState(void)
{
    return(STC_hCanBusState.u8_mBusOffFlg);
}


/*****************************************End Line**********************************************/