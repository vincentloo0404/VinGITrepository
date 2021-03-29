/******************************************************************************
*
* ChuangQu NewEnergy .
* (c) Copyright 2014 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     
*
* @brief    
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2014/12/20      JiaoYu    	   	N/A          Original
************************************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L4_Main.h"
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

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L4MAIN_START_SEC_CONST
#include "MemMap.h"

/* Software Version (ASCIIÂë) */
//const uint8 c_N_SWVersion_Uls_au08[6] = {'Z','2','.','0','.','2'};

#define d_L4MAIN_STOP_SEC_CONST
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4MAIN_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************/

static stc_CAN_MB L3_UdsTxMsgBuf_Str1; 

void CAN_L3_TxTestMsg(void)
{

	L3_UdsTxMsgBuf_Str1.CS.Bits.SRR = CAN_CS_SRR;
	L3_UdsTxMsgBuf_Str1.CS.Bits.IDE = CAN_CS_IDE;
	L3_UdsTxMsgBuf_Str1.CS.Bits.RTR = CAN_CS_RTR;
	L3_UdsTxMsgBuf_Str1.CS.Bits.LENGTH = 8;
	L3_UdsTxMsgBuf_Str1.ID.Bits.PRIO = CAN_ID_APP_PRIO;
	L3_UdsTxMsgBuf_Str1.ID.Bits.STD_ID = 0x456;
	L3_UdsTxMsgBuf_Str1.ID.Bits.EXT_ID = 0;


    /* put response data here */

    L3_UdsTxMsgBuf_Str1.DATA.Bytes[0] = 0;
    L3_UdsTxMsgBuf_Str1.DATA.Bytes[1] = 1;
    L3_UdsTxMsgBuf_Str1.DATA.Bytes[2] = 2;
    L3_UdsTxMsgBuf_Str1.DATA.Bytes[3] = 3;
    L3_UdsTxMsgBuf_Str1.DATA.Bytes[4] = 4;
    L3_UdsTxMsgBuf_Str1.DATA.Bytes[5] = 5;
    L3_UdsTxMsgBuf_Str1.DATA.Bytes[6] = 6;
    L3_UdsTxMsgBuf_Str1.DATA.Bytes[7] = 7;


    
    (void)mCAN_MB_08_11_Send_Message(&L3_UdsTxMsgBuf_Str1);
}


/*****************************************************************************
*
*   Function:     Main
*
*   Description:  This is the main function
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void main(void)
{
    /*ECU system start up*/
    ECUStartUp_L4_Ctrl();
    
    /* for ecc test */
   // EccTest();
   
   CAN_L3_TxTestMsg();
   
    /*system schedule management*/
    ScheduleManagement_L4_Per();
}

#define d_L4MAIN_STOP_SEC_CODE
#include "MemMap.h"

/*End of L4_Main.c file*/