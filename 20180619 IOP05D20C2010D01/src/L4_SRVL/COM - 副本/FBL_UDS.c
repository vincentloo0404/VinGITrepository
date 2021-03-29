/******************************************************************************
*
* ChuangQu Tech Inc.
* (c) Copyright 2016 ChuangQu Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     FBL_UDS.c
*
* @brief     hanlde UDS CAN 
*            
*
************************************************************************************************
*   Revision History:
* 
*    Version       Date          Author         CR#      Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0       2016/08/26       	YCH         N/A         Original
*     
************************************************************************************************/
#include "FBL_UDS.h"

#define RxBufferSizeIndex 0
#define RxBufferSeviceIndex 1
#define RxBufferSubSeviceIndex  2

#define CommControlDiagModeOFF  0
#define CommControlDiagModeON   1

#define DTCSettingDiagModeOFF  0
#define DTCSettingDiagModeON   1


uint8* fblUdsRxBuffer;
uint8 fblUdsTxBuffer[8] = {0};
volatile uint8        emergency_buffer[4];
uint8 lastDiagMode = 0xffu;
uint8 CommControlDiagMode = 0xffu;
uint8 DTCSettingDiagMode = 0xffu;
/*****************************************************************************
*
*   Function:     s_dsmco_PHYS_service
*
*   Description:  This function is use to UDS physical frame SERVICE
*
*   Inputs:       data  CAN Rx data
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void s_dsmco_PHYS_service(uint8* data)
{
	fblUdsRxBuffer = data;
	switch (fblUdsRxBuffer[RxBufferSeviceIndex])
    { 
        case 0x10: 
        {
            s_dsmco_dsc_handler(fblUdsRxBuffer[RxBufferSubSeviceIndex]);
            break;
        }
       	case 0x31: 
        {
            s_dsmco_RC_handler();
            break;
        }
        default:   
        {
            send_negative_response(S_DSM_RC_SNS);
            break;
        }
    }
	
}

/*****************************************************************************
*
*   Function:     s_dsmco_FUNC_service
*
*   Description:  This function is use to UDS functional frame SERVICE
*
*   Inputs:       data  CAN Rx data
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void s_dsmco_FUNC_service(uint8* data)
{
	fblUdsRxBuffer = data;
	switch (fblUdsRxBuffer[RxBufferSeviceIndex])
    { 
       
         case 0x85:
        {
           
            s_dsmco_DTCSetting_handler(fblUdsRxBuffer[RxBufferSubSeviceIndex]);
            break;
        }
        case 0x28:
        {
            s_dsmco_CommControl_handler ();
            break;
        }
        case 0x10: 
        {
            s_dsmco_dsc_handler(fblUdsRxBuffer[RxBufferSubSeviceIndex]);
            break;
        }
        default:  
        {
            break;
        }
    }
}
/*****************************************************************************
*
*   Function:     s_dsmco_dsc_handler
*
*   Description:  This function is use to dsc SERVICE  handler
*
*   Inputs:       diagmode  CAN Rx sub service
*
*   Outputs:      ret_value hanlder state
*
*   Notes:
*
*****************************************************************************/
uint16 s_dsmco_dsc_handler (uint8 diagmode)
{
    
    uint16 ret_value = S_DSM_RC_OK;
    switch (diagmode)
    { 
        case 0x01: 
        {
        	lastDiagMode = 0x01;
            send_positive_response(0x02);
            break;
        }
        case 0x03:
        {
            lastDiagMode = 0x03;
            send_positive_response(0x02);
            break;
        }
        default:   
        {
            
           send_negative_response(S_DSM_RC_SFNS);
            break;
        }
    }

    return ret_value;
}	


/*****************************************************************************
*
*   Function:     s_dsmco_RC_handler
*
*   Description:  This function is use to RC SERVICE  handler
*
*   Inputs:       diagmode  CAN Rx sub service
*
*   Outputs:      ret_value hanlder state
*
*   Notes:
*
*****************************************************************************/
uint16 s_dsmco_RC_handler (void)
{
    
    uint16 ret_value = S_DSM_RC_OK;
	uint16 diagmode = (uint16)(((*(fblUdsRxBuffer+RxBufferSubSeviceIndex+1)<<8)& 0xff00u)+(*(fblUdsRxBuffer+RxBufferSubSeviceIndex+2)));
    switch (diagmode)
    { 
        case 0x0203: 
        {
            send_positive_response(0x04);
            break;
        }
        default:    
        {
            
            send_negative_response(S_DSM_RC_SFNS);
            break;
        }
    }

    return ret_value;
}


/*****************************************************************************
*
*   Function:     s_dsmco_CommControl_handler
*
*   Description:  This function is use to CommControl SERVICE  handler
*
*   Inputs:       diagmode  CAN Rx sub service
*
*   Outputs:      ret_value hanlder state
*
*   Notes:
*
*****************************************************************************/
uint16 s_dsmco_CommControl_handler (void)
{
    
    uint16 ret_value = S_DSM_RC_OK;
    uint16 testCnt = 0;
	uint16 diagmode = (uint16)(((*(fblUdsRxBuffer+RxBufferSubSeviceIndex)<<8)& 0xff00)+(*(fblUdsRxBuffer+RxBufferSubSeviceIndex+1)));
    switch (diagmode)
    { 
        case 0x0301:
        {
            //请在这一些处理
             send_positive_response(0x02);
            CommControlDiagMode = CommControlDiagModeOFF;
            if(CommControlDiagMode == CommControlDiagModeOFF && DTCSettingDiagMode == DTCSettingDiagModeOFF)
        	{
        		lastDiagMode = 0x02;
	            send_positive_response(0x02);
	            //software rest
	             *((uint32 *)UPGRADE_RAM_ADDR) = UPGRADE_PATTERN;
	             while(testCnt++ < 10000)
				  {
				  	asm 
				  	{
				  	  nop	
				  	  nop
				  	  nop
				  	  nop
				  	}
				  }
	             EcuSoftRst();
        	}
        	else
        	{
        		send_negative_response(S_DSM_RC_CNC);
        		
        	}
            break;
        }
        case 0x0001:
        {
           	//请在这一些处理
            send_positive_response(0x02);
            CommControlDiagMode = CommControlDiagModeON;
           
            break;
        }
        default:    
        {
            
            send_negative_response(S_DSM_RC_SFNS);
            break;
        }
    }

    return ret_value;
}




/*****************************************************************************
*
*   Function:     s_dsmco_DTCSetting_handler
*
*   Description:  This function is use to DTCSetting SERVICE  handler
*
*   Inputs:       diagmode  CAN Rx sub service
*
*   Outputs:      ret_value hanlder state
*
*   Notes:
*
*****************************************************************************/
uint16 s_dsmco_DTCSetting_handler (uint8 diagmode)
{
    
    uint16 ret_value = S_DSM_RC_OK;

    switch (diagmode)
    { 
        case 0x01: 
        {
        	//请在这一些处理
             send_positive_response(0x02);
             DTCSettingDiagMode = DTCSettingDiagModeON;
        
            break;
        }
        case 0x02:
        {
        	//请在这一些处理
           send_positive_response(0x02);
           DTCSettingDiagMode = DTCSettingDiagModeOFF;
            break;
        }
        default:    
        {
            
            send_negative_response(S_DSM_RC_SFNS);
            break;
        }
    }

    return ret_value;
}


/*****************************************************************************
*
*   Function:     send_negative_response
*
*   Description:  This function is use to send negative response
*
*   Inputs:       respid  negative response value
*
*   Outputs:      none
*
*   Notes:
*
*****************************************************************************/
void  send_negative_response(uint16 respid)
{
	 	uint8 send_size = 3u;
	 	emergency_buffer[0] = 0x7fu;
        emergency_buffer[1] = fblUdsRxBuffer[RxBufferSeviceIndex];
        emergency_buffer[2] = (uint8)respid;
        
        if (respid == S_DSM_RC_CNC)
        {
           
            send_size = 3u;
        }
       
        send_UDS_CAN(send_size, send_size, emergency_buffer);
       
}



/*****************************************************************************
*
*   Function:     send_UDS_CAN
*
*   Description:  This function is use to UDS CAN datas
*
*   Inputs:       msg_length  need send CAN datas length
*                 buffer_length    CAN buffer datas length
*                 buffer           CAN buffer
*
*   Outputs:      none
*
*   Notes:
*
*****************************************************************************/
uint8 send_UDS_CAN(uint8 msg_length, uint8 buffer_length,volatile uint8 *buffer )
{
	uint8 i = 0;
	fblUdsTxBuffer[0] = msg_length;
	for(i=0;i<buffer_length;i++)
	{
		fblUdsTxBuffer[i+1] = buffer[i];
	
	}
	CAN_L3_TxUdsMsg(fblUdsTxBuffer);

}


/*****************************************************************************
*
*   Function:     send_positive_response
*
*   Description:  This function is use to send positive response
*
*   Inputs:       msglen   can datas length
*
*   Outputs:      none
*
*   Notes:
*
*****************************************************************************/
void send_positive_response(const uint8 msglen)
{    
   
    uint8 i = 0;
    fblUdsTxBuffer[0] = msglen;
	fblUdsTxBuffer[1] = fblUdsRxBuffer[RxBufferSeviceIndex]|0x40;
	for(i=0;i<msglen;i++)
	{
		fblUdsTxBuffer[i+2] = fblUdsRxBuffer[i+1];
	
	}
	CAN_L3_TxUdsMsg(fblUdsTxBuffer);
    
}


/*****************************************************************************
*
*   Function:     EcuSoftRst
*
*   Description:  This function is use to Ecu Software reset
*
*   Inputs:       none
*
*   Outputs:      none
*
*   Notes:
*
*****************************************************************************/
void EcuSoftRst(void)
{
    // Re-enter in DRUN mode to update the configuration
    ME.MCTL.R                       = 0x00005AF0;   // DRUN Mode & Key
    ME.MCTL.R                       = 0x0000A50F;   // DRUN Mode & Key
	
	//waiting for end of transaction
    //while(ME.GS.B.S_MTRANS == 1 || timer>0) {asm("nop");timer -=1;}
    while(ME.GS.B.S_MTRANS == 1)
    {
    	
    };
    
    while (1){};
}

/*****************************************************************************/

static stc_CAN_MB L3_UdsTxMsgBuf_Str; 

void CAN_L3_TxUdsMsg(uint8* data)
{

	L3_UdsTxMsgBuf_Str.CS.Bits.SRR = CAN_CS_SRR;
	L3_UdsTxMsgBuf_Str.CS.Bits.IDE = CAN_CS_IDE;
	L3_UdsTxMsgBuf_Str.CS.Bits.RTR = CAN_CS_RTR;
	L3_UdsTxMsgBuf_Str.CS.Bits.LENGTH = 8;
	L3_UdsTxMsgBuf_Str.ID.Bits.PRIO = CAN_ID_APP_PRIO;
	L3_UdsTxMsgBuf_Str.ID.Bits.STD_ID = 0x729;
	L3_UdsTxMsgBuf_Str.ID.Bits.EXT_ID = 0;


    /* put response data here */

    L3_UdsTxMsgBuf_Str.DATA.Bytes[0] = data[0];
    L3_UdsTxMsgBuf_Str.DATA.Bytes[1] = data[1];
    L3_UdsTxMsgBuf_Str.DATA.Bytes[2] = data[2];
    L3_UdsTxMsgBuf_Str.DATA.Bytes[3] = data[3];
    L3_UdsTxMsgBuf_Str.DATA.Bytes[4] = data[4];
    L3_UdsTxMsgBuf_Str.DATA.Bytes[5] = data[5];
    L3_UdsTxMsgBuf_Str.DATA.Bytes[6] = data[6];
    L3_UdsTxMsgBuf_Str.DATA.Bytes[7] = data[7];


    
    (void)mCAN_MB_08_11_Send_Message(&L3_UdsTxMsgBuf_Str);
}
