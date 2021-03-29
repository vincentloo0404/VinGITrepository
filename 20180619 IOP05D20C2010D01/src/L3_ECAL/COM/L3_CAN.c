
/*****************************************************************************
*   Include Files
*****************************************************************************/
/* LIB */
#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"

/* L2_MCAL */

/* L3_ECAL */
#include "L3_CAN.h"
#include "L3_CAN_Cfg.h"

/* L4_SRVL */

/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/


/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/

/* signal of can rx message */
#define VehSpdRawVal  ((((uint16)(L3_S_EspMsgBuf_F_u08[1] & 0x0F))<<8) + (uint16)(L3_S_EspMsgBuf_F_u08[0]))
#define VehSpdStatus  ((uint8)(L3_S_EspMsgBuf_F_u08[1] >> 7 ))

#define EngSpdRawVal  (((uint16)(L3_S_EmsMsgBuf_F_u08[1])<<8) + (uint16)L3_S_EmsMsgBuf_F_u08[0])
#define EngSpdStatus  ((uint8)(L3_S_EmsMsgBuf_F_u08[4]  & 0x10) >> 4 )

/* signal of can tx message */
#define SetEpsFaultWarnBit(x)   (L3_N_ObcTxMsgBuf_F_Str.DATA.Bytes[0] |= ((x)&0x03))


/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/


/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/
#define d_L3CAN_START_SEC_VAR 
#include "MemMap.h"


/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
CAN_STATUS_Enu L3_S_CANSta_Ct_M_Enu;

/*--------------Tx signal of Message 0x230 (EPS)----------------*/
uint8 L3_S_EPS_EPSFault_Ct_G_u08;

/* Rx message buffer */
uint8 L3_S_EspMsgBuf_F_u08[8];
uint8 L3_S_EmsMsgBuf_F_u08[8];

/* Tx message buffer */
static stc_CAN_MB L3_N_ObcTxMsgBuf_F_Str;

static uint16 L3_N_ObcTxMsgCnt_Ct_F_u16;
static uint16 L3_N_ObcTxMsg1Cnt_Ct_F_u16;

/* can message timeout flag */
uint8 L3_S_Ems1MsgTimeOut_Uls_G_u08;
uint8 L3_S_Esp3MsgTimeOut_Uls_G_u08;
uint16 L3_S_Ems1MsgTimeCnt_Uls_u16 = 0;
uint16 L3_S_VehSpdMsgTimeCnt_Uls_u16 = 0;

//obc
uint8 L3_S_BMSMsgTimeOut_Uls_G_u08 = FALSE;
uint16 L3_S_BMSMsgTimeCnt_Uls_u16 = 0;


/* engine speed signal
 * Received from Message 0x138 (EMS1) */
uint16 L3_S_CANEngineSpeed_rpm_G_u16;
uint8 L3_S_CANEngineSpeedValid_Ct_G_u08;
uint8 L3_S_CANEngineRunningSt_Uls_u08 = FALSE;

uint8 L3_S_CANEnAstSt_Uls_u08;
uint8 L3_N_EngineType_Uls_u08;

/* vehicle speed sigal
 * Received from Message 0x121 (EPS_3) */
uint16 L3_S_CANVehicleSpeed_Kph_G_u16p06;
uint8 L3_S_CANVehicleSpeedValid_Ct_G_u08;

/* can message timeout flag */
uint16 L3_CanBusOffRecCnt_Ct_u16;
uint16 L3_CanBusOffRecFastCnt_Ct_u16 = 0;
uint16 L3_CanBusOffRecSlowCnt_Ct_u16 = 0;
uint8  L3_CanBusOff_error_Ct_u8 = FALSE;
uint8  L3_inBusOffFastRecCnt = 0;

#define  d_L3CAN_STOP_SEC_VAR
#include "MemMap.h"

/*****************************************************************************
*   Function Definitions
*****************************************************************************/
#define    d_L3CAN_START_SEC_CODE
#include "MemMap.h"

/*****************************************************************************
*
*   Function:     uint8 CAN_L3_vINTRInit(void)
*
*   Description:  This function is use to initialize the CAN ECAL layer 
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void CAN_L3_Init(void)
{
    uint8 tempCnt;
    
	/* tx message init */
	L3_N_ObcTxMsgCnt_Ct_F_u16 = 0;
	L3_N_ObcTxMsg1Cnt_Ct_F_u16 = 0;
	L3_N_ObcTxMsgBuf_F_Str.CS.Bits.SRR = CAN_CS_SRR;
	L3_N_ObcTxMsgBuf_F_Str.CS.Bits.IDE = CAN_CS_IDE;
	L3_N_ObcTxMsgBuf_F_Str.CS.Bits.RTR = CAN_CS_RTR;
	L3_N_ObcTxMsgBuf_F_Str.CS.Bits.LENGTH = 8;
	L3_N_ObcTxMsgBuf_F_Str.ID.Bits.PRIO = CAN_ID_APP_PRIO;
	L3_N_ObcTxMsgBuf_F_Str.ID.Bits.STD_ID = MSG_Tx_CAN_ID;
	L3_N_ObcTxMsgBuf_F_Str.ID.Bits.EXT_ID = 0;

	for(tempCnt=0;tempCnt<8;tempCnt++)
	{
		L3_S_EspMsgBuf_F_u08[tempCnt]   = 0;
		L3_S_EmsMsgBuf_F_u08[tempCnt]   = 0;
		L3_N_ObcTxMsgBuf_F_Str.DATA.Bytes[tempCnt] = 0;
	}
    
    L3_S_Ems1MsgTimeOut_Uls_G_u08 = FALSE;
    L3_S_Esp3MsgTimeOut_Uls_G_u08 = FALSE;

    /* vehicle speed signal */
    L3_S_CANVehicleSpeed_Kph_G_u16p06 = 0;
    L3_S_CANVehicleSpeedValid_Ct_G_u08 = E_OK;

    /* engine speed signal */
    L3_S_CANEngineSpeed_rpm_G_u16 = 0;
    L3_S_CANEngineSpeedValid_Ct_G_u08 = E_OK;
    L3_S_CANEngineRunningSt_Uls_u08 = FALSE;
    
    L3_S_CANEnAstSt_Uls_u08 = FALSE;

    L3_S_CANSta_Ct_M_Enu = e_NOBUSOFF;
    
    /* EPS fault status */
    L3_S_EPS_EPSFault_Ct_G_u08 = STD_ON;
    
    L3_S_Ems1MsgTimeCnt_Uls_u16 = 0;
    L3_S_VehSpdMsgTimeCnt_Uls_u16 = 0;
    
    L3_S_BMSMsgTimeOut_Uls_G_u08 = FALSE;
    L3_S_BMSMsgTimeCnt_Uls_u16 = 0;


    L3_CanBusOffRecCnt_Ct_u16 = 0;
}
/*****************************************************************************
*
*   Function:     uint8 CAN_L3_vINTRInit(void)
*
*   Description:  This function is use to initialize the CAN ECAL layer 
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
#define		ABS_DSC_HSC_FrP00		0x16D    /* MG GT ABS_DSC_HSC_FrP00 vehSpd */
#define		ABS_DSC_HSC_FrP01		0x4CC    /* ABS_DSC_HSC_FrP01 WheelSpd */
#define		ABS_DSC_HSC_FrP02		0x512    /* ABS_DSC_HSC_FrP02 WheelRollingCount */
#define		BCM_HSC_FrP02			0x600    /* BCM_HSC_FrP02,KeySwitch */
#define		EMS_HSC_FrP00			0x05E    /* EMS_HSC_FrP00,EngineRunningST */
#define		EMS_HSC_FrP05			0x608    /* EMS_HSC_FrP05,EnASSStaHSC */
#define		EMS_HSC_FrP02			0x57E    /* EMS_HSC_FrP02,EngineType */

void pFUN_mCAN_MB_FIFO_Hook(stc_CAN_MB *tCanBuf)
{
	static uint8 runCnt = 0;
    switch (tCanBuf->ID.Bits.STD_ID)
    {
    	
        case CCP_CRO_CAN_ID:
        { 
           CCP_CRO_Indication((uint8*)(tCanBuf->DATA.Bytes));
           break;   
        }
        
        case Rx_BMS_CAN_ID:
        { 
           CanRxFrameUnpack((uint8*)(tCanBuf->DATA.Bytes));
           L3_S_BMSMsgTimeCnt_Uls_u16 = 0;
           break;   
        }
        
        case Rx_BMS_CAN_ID1:
        { 
      		CanRxFrameUnpack1((uint8*)(tCanBuf->DATA.Bytes));
        	
           break;   
        }
        
        /*
        case ABS_DSC_HSC_FrP00:
        { 
           // vehicle speed signal /
           if( tCanBuf->DATA.Bytes[4] & 0x04 )
           {
   	          L3_S_CANVehicleSpeedValid_Ct_G_u08 = E_OK;
           }
           else
           {
   	          L3_S_CANVehicleSpeedValid_Ct_G_u08 = E_NOT_OK;
           }
 
           L3_S_CANVehicleSpeed_Kph_G_u16p06 = (uint16)(tCanBuf->DATA.Bytes[6]<<8) +  
                                               (uint16)tCanBuf->DATA.Bytes[7];
           // 1LSB = 0.001 kph/
           L3_S_CANVehicleSpeed_Kph_G_u16p06 =  (uint16)((((uint32)L3_S_CANVehicleSpeed_Kph_G_u16p06)<<6) / 100) ;                         
           
           L3_S_VehSpdMsgTimeCnt_Uls_u16 = 0;
           
           break;   
        }
        case ABS_DSC_HSC_FrP01:
        { 
           break;   
        }
        case ABS_DSC_HSC_FrP02:
        {  
           break;   
        }

        case BCM_HSC_FrP02:
        {  
           break;   
        }

        case EMS_HSC_FrP00:
        {  
           
           if( (tCanBuf->DATA.Bytes[7] & 0x08) != 0 )
           {
   	          L3_S_CANEngineRunningSt_Uls_u08 = TRUE;
           }
           else
           {
   	          L3_S_CANEngineRunningSt_Uls_u08 = FALSE;
           }

           L3_S_CANEngineSpeed_rpm_G_u16 = (uint16)(tCanBuf->DATA.Bytes[4]<<8) + 
           								   (uint16)tCanBuf->DATA.Bytes[5];
           
          // 1LSB = 0.15625 rpm/
           L3_S_CANEngineSpeed_rpm_G_u16 = (uint16)(((uint32)L3_S_CANEngineSpeed_rpm_G_u16*10)>>6);
           
   	 	   L3_S_CANEngineSpeedValid_Ct_G_u08 = E_OK;
   	 	   
           L3_S_Ems1MsgTimeCnt_Uls_u16 = 0;
           
           break;   
        }

        case EMS_HSC_FrP05:
        {  
           L3_S_CANEnAstSt_Uls_u08 = tCanBuf->DATA.Bytes[0] >> 6;

           break;   
        }

        case EMS_HSC_FrP02:
        {  
           L3_N_EngineType_Uls_u08 = tCanBuf->DATA.Bytes[7];

           break;   
        }
        */
       ///////////////////////////////////////////////////////////
        case Rx_FBL_CAN_ID:
        { 
           
           // put uds response here //
        	s_dsmco_PHYS_service((uint8*)(tCanBuf->DATA.Bytes));
        
           break;   
        }
        case Rx_FBL_FUNC_CAN_ID:
        { 
          	s_dsmco_FUNC_service((uint8*)(tCanBuf->DATA.Bytes));
          break;   
        }
        
        ////////////////////////////////////////////////////////
        default :

        break; 
    }
}

/* *****************************************************************************
Function:     pFUN_mCAN_MB_08_11_Hook   
Description:   CAN MSG send ISR Hook  
Parameters:      Input:     pointer point to the Can Msg. Obj
                Output:   None
Notes:           
               
***************************************************************************** */
void pFUN_mCAN_MB_08_11_Hook(stc_CAN_MB *tCanBuf)
{
    tCanBuf;/**/
    //hCanBus_u8UpdateBusOKCnt();
}
/* *****************************************************************************
Function:     pFUN_mCAN_MB_12_15_Hook   
Description:    CCP Can Message  handle
Parameters:      Input:     pointer point to the Can Msg. Obj
                Output:   None
Notes:           
               
***************************************************************************** */
void pFUN_mCAN_MB_12_15_Hook(stc_CAN_MB *tCanBuf)
{
    if(tCanBuf->ID.Bits.STD_ID == CCP_DTO_CAN_ID)  /*tx success interrupt*/
    {
        CCP_DTO_Confirmation((uint8*)(tCanBuf->DATA.Bytes));	
    }
    else
    {
        /*do nothing*/
    }  
}
/* *****************************************************************************
Function:     CAN_L3_RxMsg   
Description:    CAN rx message
Parameters:      Input:   None
                Output:   None
Notes:           
               
***************************************************************************** */
static void CAN_L3_RxMsg(void)
{
   /* check can rx buffer */
   CanRx_L2_Per();
   L3_S_BMSMsgTimeCnt_Uls_u16++;
   if(L3_S_BMSMsgTimeCnt_Uls_u16 >= 1000)
  {
	   L3_S_BMSMsgTimeCnt_Uls_u16 = 0;
	   L3_S_BMSMsgTimeOut_Uls_G_u08 = TRUE;
  }
  else
  {
	  L3_S_BMSMsgTimeOut_Uls_G_u08 = FALSE;
  }
}
/*****************************************************************************
*
*   Function:     uint8 OBC_HSC_FrP00_Tx_Per(void)
*
*   Description:  100ms send can msg
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static uint8 OBC_HSC_FrP00_Tx_Per(void)
{
    uint8 Ret = TRUE;
    static uint8 beginFlag = 0;
    static uint8 spaceFlag = 0;
    
    L3_N_ObcTxMsgCnt_Ct_F_u16++;
    
    /* period = 50*2 ms */
    if(50 <= L3_N_ObcTxMsgCnt_Ct_F_u16)
    {
       // L3_N_ObcTxMsgBuf_F_Str.DATA.Bytes[0] = (0)<<6;
        //L3_N_ObcTxMsgBuf_F_Str.DATA.Bytes[7]++;
        //Ret = mCAN_MB_08_11_Send_Message(&L3_N_ObcTxMsgBuf_F_Str);
        CAN_L5_TxMsg();
        L3_N_ObcTxMsgCnt_Ct_F_u16 = 0;
        beginFlag = 1;
        
    }
    else
    {
        /*Do Nothing*/
      
    }
    
     if(beginFlag)
    {
    	if(spaceFlag <= 50)
    	{
    		spaceFlag ++;
    	}
    }
    
    if(spaceFlag >= 50)
    {
    	L3_N_ObcTxMsg1Cnt_Ct_F_u16++;
    
    }
    
    if(50 <= L3_N_ObcTxMsg1Cnt_Ct_F_u16)
    {
    	CAN_L5_TxMsg1();
        L3_N_ObcTxMsg1Cnt_Ct_F_u16 = 0;
        
    }
    
    
    
    
    return(Ret);
} 
/*****************************************************************************
*
*   Function:     static void CAN_L3_TxMsg(void)
*
*   Description:  This function is use to send can msg
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void CAN_L3_TxMsg(void)
{
   CanTx_L2_Confirm();

   if(L3_S_IgnitionState_G_u08 == STD_ON)
   {
		/* update can tx msg signal */

		/* CAN Msg tx */
		(void)OBC_HSC_FrP00_Tx_Per();
	}
	else
	{
		;
	}
}
/*****************************************************************************
*
*   Function:     uint8 CAN_L3_vINTRInit(void)
*
*   Description:  This function is use to initialize the CAN ECAL layer 
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
static void CAN_L3_BusOff(void)
{
   if(0x02 == (mCAN_Get_Fault_Conf_State() & 0x02))
   {
   		L3_CanBusOff_error_Ct_u8 = TRUE;
   	   
   	   if(L3_inBusOffFastRecCnt++ >=5 )
   	   {
   	   		if(L3_CanBusOffRecSlowCnt_Ct_u16++ > 100)
   	   		{
   	   			CAN_BOFF_AutoRec_En;	
   	   			L3_CanBusOffRecSlowCnt_Ct_u16 = 0;
   	   		}
   	   		
   	   }
   	   else
   	   {
   	   		if(L3_CanBusOffRecFastCnt_Ct_u16++ > 25)
   	   		{
   	   			CAN_BOFF_AutoRec_En;	
   	   			L3_CanBusOffRecFastCnt_Ct_u16 = 0;
   	   		}
   	   }
   	   
   	   
   }
   else
   {
   	   CAN_BOFF_AutoRec_Dis;
   	   //L3_CanBusOffRecCnt_Ct_u16 = 50;
   	   L3_CanBusOffRecFastCnt_Ct_u16 = 0;
   	   L3_CanBusOffRecSlowCnt_Ct_u16 = 0;
   	   L3_CanBusOff_error_Ct_u8 = FALSE;
   	   L3_inBusOffFastRecCnt = 0;
   }
}
/*****************************************************************************
*
*   Function:     uint8 CAN_L3_vCommunication_2ms(void)
*
*   Description:  The can main task
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
void CAN_L3_Per(void)
{
    /***************Message Receive************/
    CAN_L3_RxMsg();
    /***************Message Transmit***********/
    CAN_L3_TxMsg();
    /*BUSOFF detect*/
    CAN_L3_BusOff();
}
/*****************************************************************************
*
*   Function:     uint8 CAN_L3_TP_Transmit(void)
*
*   Description:  This function is use to transmit the diagnose message
*
*   Inputs:       None
*
*   Outputs:      None
*
*   Notes:
*
*****************************************************************************/
uint8 CAN_L3_TP_Transmit(void)
{
    return (0);
}

#define d_L3CAN_STOP_SEC_CODE
#include "MemMap.h"

/*End of L3_CAN.c file*/
