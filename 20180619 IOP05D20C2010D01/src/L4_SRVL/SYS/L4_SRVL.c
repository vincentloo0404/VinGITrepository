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
*     1.0        2014/12/20      ----    	   	N/A          Original
************************************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L4_SRVL.h"
//#include "L4_EOLData.h"
//#include "L4_NvmAppData.h"
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

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define d_L4SRVL_START_SEC_CODE
#include "MemMap.h"
/*****************************************************************************
*
*   Function:     SRVL_L4_Init
*
*   Description:  This function is use to Initial the Service Layer
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void SRVL_L4_Init(void)
{

    /* calibration init */
    //ccpInit();/* ccp stack init */	       

    /*Initial UDS service*/
    DTC_L4_vInit();

    /*Initial fail management*/
    FM_L4_ColdInit();
    
    /* calibration data */
    //(void)ClbData_L4_Init();

    /* Copy Calibration data from NVM to RAM */
//    EOL_L4_Init();

#if 0
    /*Initial CCP service*/
    Serv_L4_CANCalInit();
    L4_TP_APPL_CAN_INIT();
    L4_NL_RX_Init();
    L4_TP_Sender_CAN_INIT();
    /*Initial the Monitor Service*/
    MonitorSrv_L4_Init();
    /*Initial the EEPROM data*/
    EepromManagement_L4_Init();
    /*Initial UDS service*/
    DTC_L4_vInit();
    /* Copy App data from NVM to RAM */
    Nvm_L4_ReadAppData();
    /* Copy Calibration data from NVM to RAM */
    EOL_L4_Init();
    /*Initial fail management*/
    FM_L4_ColdInit();
    
#endif    
}
#define d_L4SRVL_STOP_SEC_CODE
#include "MemMap.h"

/*End of L4_SRVL.c file*/
