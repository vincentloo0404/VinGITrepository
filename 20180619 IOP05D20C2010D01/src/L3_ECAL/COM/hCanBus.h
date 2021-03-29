/***********************************************************************************************
*
* Beijing Hualong Tech Inc.
* (c) Copyright 2012 Beijing Hualong Tech, Inc.
* ALL RIGHTS RESERVED.
*
************************************************************************************************
*
* @file   hCanBus.h   
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
#ifndef _H_CAN_BUS_H_
#define _H_CAN_BUS_H_


/*-------------------------------------------------------------------------*/
/**                              Include files                            **/
/*-------------------------------------------------------------------------*/  
#include	"Platform_Types.h"


/*-------------------------------------------------------------------------*/
/**               Bus-Off Error Monitor and Handle Rate                   **/
/*-------------------------------------------------------------------------*/
#define CAN_BUS_ST_DIG_SCHE_TICK        0x000A      /*10ms */

/*-------------------------------------------------------------------------*/
/**                 Bus-Off Error Recover Rate                            **/
/*-------------------------------------------------------------------------*/
#define CAN_LAZY_BUS_REC_TICK     1000U  /*1000ms:Slow Bus-Off recover time*/
#define CAN_BUSY_BUS_REC_TICK     100U   /*100ms :Fast Bus-Off recover time*/

#define CAN_BUS_BUSY_REC_TIME     5U     /*Fast Bus-Off recover retry times*/


/*-------------------------------------------------------------------------*/
/**                               User Cfg.                               **/
/*-------------------------------------------------------------------------*/
#define CAN_ISR_MSG_INCREASE_STEP  0x0001   /*Number added after Msg-Tx OK*/
#define CAN_ISR_BUS_OFF_REC_THRES  0x0002   /*Judge Bus-Rec-Succ threshold*/


/*-------------------------------------------------------------------------*/
/**                Internal Can-Bus State                                 **/
/*-------------------------------------------------------------------------*/
#define CAN_BUS_RECOVER_MODE    0x01
#define CAN_BUS_NORMAL_MODE     0x00

/*-------------------------------------------------------------------------*/
/**             Internal Standard Can-Bus Status check Mask               **/
/*-------------------------------------------------------------------------*/
#define CAN_ERR_BUS_OFF_MSK     0x02


/*-------------------------------------------------------------------------*/
#define CAN_BUS_OFF_RECOVER_BUSY     0x01
#define CAN_BUS_OFF_RECOVER_IDLE     0x00

/*-------------------------------------------------------------------------*/
/**                External Can-Bus State                                 **/
/*-------------------------------------------------------------------------*/
#define CAN_BUS_OFF_TRUE     0x01
#define CAN_BUS_OFF_FALSE    0x00

/*-------------------------------------------------------------------------*/
/**                External Can-Bus Error Status                          **/
/*-------------------------------------------------------------------------*/
#define CAN_BUS_ERR_ACTIVE      0x00
#define CAN_BUS_ERR_PASSIVE     0x01
#define CAN_BUS_ERR_BUS_OFF     0x02

/*-------------------------------------------------------------------------*/
/**                 Normal Macro Defination                               **/
/*-------------------------------------------------------------------------*/
#define CAN_BUS_RECOVER_TIME_INIT  0x0001
#define CAN_BUS_ERR_DIG_THRE_CLR   0x0000
#define CAN_ISR_MSG_COUNTER_RESET  0x0000

/*-------------------------------------------------------------------------*/
/***                Extern function declaration                          ***/
/*-------------------------------------------------------------------------*/
extern void hCanBus_vBusDiagModuleInit(void);
extern void hCanBus_u8UpdateBusOKCnt(void);


extern void hCanBus_vBusStateMonitor(void);
extern INT8U hCanBus_u8GetBusOffState(void); 

#endif					

/*****************************************End Line**********************************************/