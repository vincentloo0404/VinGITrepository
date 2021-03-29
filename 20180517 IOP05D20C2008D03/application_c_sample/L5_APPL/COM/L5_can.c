/*
 * L5_can.c
 *
 *  Created on: 2016年4月21日
 *      Author: YCH
 */
#include "L5_can.h"
CanTxFrameTag mCanTxFrameTag = {0};

CanTxFrameTag1 mCanTxFrameTag1 = {0};

DebugCanTxFrameTag mDebugCanTxFrameTag = {0};
CanCtrlParaTag	stCanCrtlPara = {0};

CC_STATE_TAG	CC_STATE_Tag[10] =
{
	//{0x1,0,0,0,0},
	{0x1,0,0,0,8},//兼容无 cc的枪，8A
	{0x2,0,0,0,0},
	{0x3,1500,0,1,10},
	{0x4,1500,1800,0,0},
	{0x5,680,0,1,16},
	{0x6,680,2700,0,0},
	{0x7,220,0,1,32},
	{0x8,220,3300,0,0},
	{0x9,100,0,1,63},
	{0xa,100,3300,0,0}

};

uint8_t CC_STATE_ARR[10] = 
{
	0,//兼容无 cc的枪，10A,20171227去除 不符合国标都不充电
	0,
	10,
	0,
	16,
	0,
	32,
	0,
	63,
	0
};

uint8_t k_hardware_version_integer = HARDWARE_VERSION_INTEGER;
uint8_t k_hardware_version_decimal = HARDWARE_VERSION_DECIMAL;
uint8_t k_software_version_integer = SOFTWARE_VERSION_INTEGER;
uint8_t k_software_version_decimal = SOFTWARE_VERSION_DECIMAL;
uint8_t k_software_data_version = 	SOFTWARE_DATA_VERSION;




void updateOBCTagAPI(void)
{
//	uint16	actChrCurrentTemp = 0;

	//OBCTag.actChrCurrent = (uint32)(L3_Dcdc_Iout_Ct_u16*500*2)>>10;
	//actChrCurrentTemp =(uint16)((uint32)L3_Dcdc_Iout_Ct_u16*25/112);
	//OBCTag.actChrCurrent = actChrCurrentTemp>40?actChrCurrentTemp-40:0;//电流计算。
	
	
	OBCTag.actChrCurrent =(uint16)((DCDC_AD_CONVERT_100doubleCURRENT(L3_Dcdc_Iout_Ct_u16)<<4)/100);//电流计算。
	
	//OBCTag.actChrVolt = (uint16)(((uint32)L3_Dcdc_Vout_Ct_u16*1000)>>10);//电压计算
	//OBCTag.actChrVolt = DCDC_AD_CONVERT_VOLT(L3_Dcdc_Vout_Ct_u16)*2;//电压计算
	OBCTag.actChrVolt = (uint16)((DCDC_AD_CONVERT_100doubleVOLT(L3_Dcdc_Vout_Ct_u16)<<1)/100);//电压计算
	
	OBCTag.ChrOpMode = stSysFSMCtrl.ucCurrentState;
	//OBCTag.ChrTemp 
	//OBCTag.FaultID
	if(bms_can_available)
	{
		OBCTag.bErrorCOM = L3_S_BMSMsgTimeOut_Uls_G_u08;//BMS帧通信是否正常
	}
	else
	{
		OBCTag.bErrorCOM = FALSE;//BMS帧通信是否正常
	}
	
	OBCTag.bOverTempCool = faultCodeTag.bit.bOverTempCool || faultCodeTag.bit.bTempWarinOutOff;
	OBCTag.bFaultHW = faultCodeTag.bit.bHWDCDC_OVP || faultCodeTag.bit.bHWDCDC_OCP || faultCodeTag.bit.bHWPFC_OVP || faultCodeTag.bit.bHWPFC_OCP;
	
	OBCTag.bFaultAC = faultCodeTag.bit.bOverUinVolt || faultCodeTag.bit.bUnderUinVolt;
	
	OBCTag.bFaultDC = faultCodeTag.bit.bOverDCUoutI || faultCodeTag.bit.bOverDCUoutVolt || faultCodeTag.bit.bUnderDCUoutVolt;
	
	//OBCTag.bWakeUp = O_PG;
	OBCTag.bWakeUp = PG_SENSE;
	//OBCTag.PowerLimit 

}



void CanTxFramePack(void)
{


	updateOBCTagAPI();

	//生命信号变化
	stCanCrtlPara.ucCanLiveCntr++;
	stCanCrtlPara.ucCanLiveCntr %= 0x0F;
	//mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_CURRENTMODE;
	CanDBCModeCov(OBCTag.ChrOpMode);

	if((OBCTag.chrFB_TEM+40) <= 0)
	{
		OBCTag.ChrTemp = 0;
	}
	else
	{
		OBCTag.ChrTemp = OBCTag.chrFB_TEM + 40 ;
	}
	
	mCanTxFrameTag.bit.CHR01_ChrTemp = (uint8)(OBCTag.ChrTemp);
	//mCanTxFrameTag.bit.CHR01_ChrTemp = (uint8)(OBCTag.ChrTemp+40+10);
	//mCanTxFrameTag.bit.CHR01_ChrTemp =  TEMP_DBC+40;
	mCanTxFrameTag.bit.CHR01_FaultID = (uint8)OBCTag.FaultID;
	//mCanTxFrameTag.bit.CHR01_FaultID = CONNECT_BMS_OK;
	//mCanTxFrameTag.bit.CHR01_FaultID =  BMSTag.EnCharger;
	
	mCanTxFrameTag.bit.CHR01_PowerLimit = (uint8)OBCTag.PowerLimit;
	mCanTxFrameTag.bit.CHR01_SWVersionH = (uint8)DBC_VERSION_H;
	mCanTxFrameTag.bit.CHR01_SWVersionL = (uint8)DBC_VERSION_L;
	mCanTxFrameTag.bit.CHR01_ReqCloseRly = (uint8)OBCTag.ReqCloseRly;
	mCanTxFrameTag.bit.CHR01_actChrCurrentH = (uint8)(OBCTag.actChrCurrent>>6);
	mCanTxFrameTag.bit.CHR01_actChrCurrentL = (uint8)(OBCTag.actChrCurrent&0x003F);
	mCanTxFrameTag.bit.CHR01_actChrVoltH = (uint8)(OBCTag.actChrVolt >> 8);
	mCanTxFrameTag.bit.CHR01_actChrVoltL = (uint8)(OBCTag.actChrVolt & 0x00FF);
	mCanTxFrameTag.bit.CHR01_bErrorCOM = (uint8)OBCTag.bErrorCOM;
	mCanTxFrameTag.bit.CHR01_bFaultAC = (uint8)OBCTag.bFaultAC;
	mCanTxFrameTag.bit.CHR01_bFaultCable = (uint8)OBCTag.bFaultCable;
	/*
	if(OBCTag.ChrOpMode == STATE_PREFAILURE)
	{
		mCanTxFrameTag.bit.CHR01_bFaultDC = FALSE;
		mCanTxFrameTag.bit.CHR01_bFaultHW = FALSE;
		mCanTxFrameTag.bit.CHR01_bOverTempCool = FALSE;
	}
	else
	*/
	{
		mCanTxFrameTag.bit.CHR01_bFaultDC = (uint8)OBCTag.bFaultDC;
		mCanTxFrameTag.bit.CHR01_bFaultHW = (uint8)OBCTag.bFaultHW;
		mCanTxFrameTag.bit.CHR01_bOverTempCool = (uint8)OBCTag.bOverTempCool;
	}
	
	
	mCanTxFrameTag.bit.CHR01_bWakeUp = (uint8)OBCTag.bWakeUp;
	//CAN生命信号、系统状态、校验和
	mCanTxFrameTag.bit.CHR01_Counter = (uint8)stCanCrtlPara.ucCanLiveCntr;
	
	

}


void CanTxFramePack1(void)
{


	//OBCTag.ACRMSVolt  = (uint16)(((float)AC_AD_CONVERT_VOLT(L5_AC_Volt_fast_max_buff))*2*0.707);//AC有效电压计算
	//OBCTag.ACRMSVolt  = (uint16)(((float)AC_AD_CONVERT_VOLT(L5_AC_Volt_fast_max_buff))*0.707);//AC有效电压计算
	OBCTag.ACRMSVolt  = (uint16)(707*(AC_AD_CONVERT_VOLT(L5_AC_Volt_fast_maxBuffCPS))/1000);//AC有效电压计算

	//OBCTag.ACRMSVolt  = (uint16)(((float)AC_AD_CONVERT_VOLT(829))*2*0.707);//AC有效电压计算

	//OBCTag.ACRMSVolt  = 220*2;//AC有效电压计算
	//mCanTxFrameTag1.bit.CHR02_CCState = 0;


	//OBCTag.ACRMSVolt  = (uint16)(((float)AC_AD_CONVERT_VOLT(L3_AD0_AC_Volt_fast_Ct_u16))*2);//AC实际值
	
	OBCTag.PFCVolt = (uint16)((PFC_AD_CONVERT_1000double_VOLT(L3_I_AD_PFC_slow_Ct_u16)<<1)/100);//电压计算
	
	if( CC_STATE_D_VALUE_MIN<=L3_I_AD_CC && L3_I_AD_CC<= CC_STATE_D_VALUE_MAX)
	{
		mCanTxFrameTag1.bit.CHR02_CCState = CCSTATE_D;
	}
	else if( CC_STATE_D1_VALUE_MIN<=L3_I_AD_CC && L3_I_AD_CC<= CC_STATE_D1_VALUE_MAX)
	{
			mCanTxFrameTag1.bit.CHR02_CCState = CCSTATE_D1;
	}
	else
	{
		mCanTxFrameTag1.bit.CHR02_CCState = CCSTATE_A;
	}

	mCanTxFrameTag1.bit.CHR02_UINVoltH = (uint8)((OBCTag.ACRMSVolt*2) >> 8);
	mCanTxFrameTag1.bit.CHR02_UINVoltL = (uint8)((OBCTag.ACRMSVolt*2) & 0x00FF);
	
	
	mCanTxFrameTag1.bit.CHR02_PFCVoltH = (uint8)(OBCTag.PFCVolt >> 8);
	mCanTxFrameTag1.bit.CHR02_PFCVoltL = (uint8)(OBCTag.PFCVolt & 0x00FF);
	
	

	
}

void CanDBCModeCov(uint8_t mode)
{
	switch(mode)
	   {
	   	 case STATE_INIT:
	   	 {
              mCanTxFrameTag.bit.CHR01_ChrOpMode  =  DBC_STATE_INIT;	   	 	
	   	 }
	   	 break;
		 case STATE_STANDBY:
	   	 {
              mCanTxFrameTag.bit.CHR01_ChrOpMode =  DBC_STATE_STANDBY;	   	 	
	   	 }
	   	 break;
	   	 case STATE_PRECHARGE1:
	   	 {
              mCanTxFrameTag.bit.CHR01_ChrOpMode =  DBC_STATE_PRECHARGE;	   	 	
	   	 }
	   	 break;
	   	 case STATE_PRECHARGE2:
	   	 {
              mCanTxFrameTag.bit.CHR01_ChrOpMode =  DBC_STATE_PRECHARGE;	   	 	
	   	 }
	   	 break;
	   	 case STATE_PFC_RUN:
	   	 {
              mCanTxFrameTag.bit.CHR01_ChrOpMode =  DBC_STATE_PRECHARGE;	   	 	
	   	 }
	   	 break;
	   	 case STATE_OPETRATION:
	   	 {
			if(OBC_Y.VLOOPbIT)
			{
				mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_VOLTMODE;
				/*
				if(AC_Volt_fast_limtLow_Ct_u16 > L5_AC_Volt_fast_max_buff || L5_AC_Volt_fast_max_buff > AC_Volt_fast_maxHigh_Ct_u16)
				{
					mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_STANDBY;
				}
				else
				{
					mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_VOLTMODE;
				}
				*/
			}else
			{
				mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_CURRENTMODE;
			}	 	
			//mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_CURRENTMODE;	 	
	   	 }
	   	 break;
	   	 case STATE_PREFAILURE:
	   	 {
	   	 	//mCanTxFrameTag.bit.CHR01_ChrOpMode = mCanTxFrameTag.bit.CHR01_ChrOpMode;
	   	 	/*
			if(stSysFSMCtrl.ucLastSysState != STATE_PREFAILURE)
			{
				mCanTxFrameTag.bit.CHR01_ChrOpMode = CanDBCModeCov(stSysFSMCtrl.ucLastSysState);
			}
			else
			{
				//mCanTxFrameTag.bit.CHR01_ChrOpMode = mCanTxFrameTag.bit.CHR01_ChrOpMode;
			}	   	 	
			*/
			
			mCanTxFrameTag.bit.CHR01_ChrOpMode =  DBC_STATE_PREFAILURE;	  
	   	 }
	   	 break;
	   	 case STATE_FAILURE:
	   	 {
	   	 	mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_FAILURE;
	   	 }
	   	 break;
	   	 case STATE_AFTER_RUN:
	   	 {
	   	 	mCanTxFrameTag.bit.CHR01_ChrOpMode = DBC_STATE_AFTER_RUN;
	   	 }
	   	 break;
	   	 case STATE_SLEEP:
	   	 {
	   	 	mCanTxFrameTag.bit.CHR01_ChrOpMode = STATE_AFTER_RUN;
	   	 }
	   	 break;
	   	 default:
	   	 {
	   	 
	   	 }
	   	 break;
	   }
}
void DebugCanTxFramePack(void)
{

	mDebugCanTxFrameTag.bit.bDriver13VFault = faultCodeTag.bit.bDriver13VFault;
	mDebugCanTxFrameTag.bit.bHWDCDC_OCP = faultCodeTag.bit.bHWDCDC_OCP;
	mDebugCanTxFrameTag.bit.bHWDCDC_OVP = faultCodeTag.bit.bHWDCDC_OVP;
	mDebugCanTxFrameTag.bit.bHWPFC_OCP = faultCodeTag.bit.bHWPFC_OCP;
	mDebugCanTxFrameTag.bit.bHWPFC_OVP = faultCodeTag.bit.bHWPFC_OVP;
	mDebugCanTxFrameTag.bit.bLV12VFault = faultCodeTag.bit.bLV12VFault;
	mDebugCanTxFrameTag.bit.bOverDCUoutI = faultCodeTag.bit.bOverDCUoutI;
	mDebugCanTxFrameTag.bit.bOverDCUoutVolt = faultCodeTag.bit.bOverDCUoutVolt;
	mDebugCanTxFrameTag.bit.bOverPFCUoutI = faultCodeTag.bit.bOverPFCUoutI;
	mDebugCanTxFrameTag.bit.bOverPFCUoutVolt = faultCodeTag.bit.bOverPFCUoutVolt;
	mDebugCanTxFrameTag.bit.bOverTempCool = faultCodeTag.bit.bOverTempCool;
	mDebugCanTxFrameTag.bit.bOverUinVolt = faultCodeTag.bit.bOverUinVolt;
	mDebugCanTxFrameTag.bit.bUnderDCUoutVolt = faultCodeTag.bit.bUnderDCUoutVolt;
	mDebugCanTxFrameTag.bit.bUnderPFCUoutVolt = faultCodeTag.bit.bUnderPFCUoutVolt;
	mDebugCanTxFrameTag.bit.bUnderUinVolt = faultCodeTag.bit.bUnderUinVolt;
	mDebugCanTxFrameTag.bit.bloadDump = faultCodeTag.bit.bloadDump;


}



void CanRxFrameUnpack(uint8 * data)
{


	
	/*
	uint8 data0,data1,data2,data3,data4,data5,data6,data7;
	
	data0 = data[0];
	data1 = data[1];
	data2 = data[2];
	data3 = data[3];
	data4 = data[4];
	data5 = data[5];
	data6 = data[6];
	data7 = data[7];
	*/
//	uint8 CC_IMax = 0;
//	uint8 CCState = 0;
	BMSTag.CCState = (data[0]&0xF0) >> 4;
	//BMSTag.EnCharger = (data[1] & 0x3F)>>2;
	BMSTag.EnCharger = (data[2] & 0x02)>>1;
	//BMSTag.EnCharger = (data[2] & 0x03)>>1;
	//BMSTag.ACChrRlySt = (data[7] & 0x3F)>>4;
	BMSTag.ACChrRlySt = (data[3] & 0xC0)>>6;
	
	BMSTag.ChrTimeRemain = (((uint16)data[3] & 0x3F)<<4)+(((uint16)data[4]&0xF0)>>4);
	BMSTag.ChrCurrentSp = (((uint16)data[4] & 0x0F)<<6)+((data[5]&0xFC)>>2);
	BMSTag.ChrVoltSp = (((uint16)data[5] & 0x03)<<8)+data[6];


}


void CanRxFrameUnpack1(uint8 * data)
{
	static uint8 runCnt = 0;
	
	if(runCnt>20)
	{
		
		
		BMSTag.PosRlySt = (data[4] & 0x0C)>>2;
		BMSTag.actVoltage = ((((uint16)data[1] & 0x0F)<<8)+data[2])>>2;//  /4
		L3_PRECHARGE2_BMS_MIN = DCDC_VOLT_AD_CONVERT(BMSTag.actVoltage-PRECHARGE2_BMS_OFFSET);
		L3_PRECHARGE2_BMS_MAX = DCDC_VOLT_AD_CONVERT(BMSTag.actVoltage+PRECHARGE2_BMS_OFFSET);

		BMSTag.actVoltageADRow = DCDC_VOLT_AD_CONVERT(BMSTag.actVoltage);
		L5_precharge2_CMD_FLAG = TRUE;
		
	
		runCnt = 0;
	}
	
	else
	{
		runCnt++;
	}
	

}

static stc_CAN_MB L5_ObcTxMsgBuf_Str;
//static SAFEPORT_stc_CAN_MB  L5_ObcSAFEPORT_TxMsgBuf_Str;
void CAN_L5_TxMsg()
{

	L5_ObcTxMsgBuf_Str.CS.Bits.SRR = CAN_CS_SRR;
	L5_ObcTxMsgBuf_Str.CS.Bits.IDE = CAN_CS_IDE;
	L5_ObcTxMsgBuf_Str.CS.Bits.RTR = CAN_CS_RTR;
	L5_ObcTxMsgBuf_Str.CS.Bits.LENGTH = 8;
	L5_ObcTxMsgBuf_Str.ID.Bits.PRIO = CAN_ID_APP_PRIO;
	L5_ObcTxMsgBuf_Str.ID.Bits.STD_ID = MSG_Tx_CAN_ID;
	L5_ObcTxMsgBuf_Str.ID.Bits.EXT_ID = 0;

	CanTxFramePack();

   	 /* put response data here */

    L5_ObcTxMsgBuf_Str.DATA.Bytes[0] = mCanTxFrameTag.ucDara[0];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[1] = mCanTxFrameTag.ucDara[1];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[2] = mCanTxFrameTag.ucDara[2];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[3] = mCanTxFrameTag.ucDara[3];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[4] = mCanTxFrameTag.ucDara[4];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[5] = mCanTxFrameTag.ucDara[5];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[6] = mCanTxFrameTag.ucDara[6];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[7] = mCanTxFrameTag.ucDara[7];


    (void)mCAN_MB_08_11_Send_Message(&L5_ObcTxMsgBuf_Str);
}

void CAN_L5_TxMsg1()
{

	L5_ObcTxMsgBuf_Str.CS.Bits.SRR = CAN_CS_SRR;
	L5_ObcTxMsgBuf_Str.CS.Bits.IDE = CAN_CS_IDE;
	L5_ObcTxMsgBuf_Str.CS.Bits.RTR = CAN_CS_RTR;
	L5_ObcTxMsgBuf_Str.CS.Bits.LENGTH = 8;
	L5_ObcTxMsgBuf_Str.ID.Bits.PRIO = CAN_ID_APP_PRIO;
	//L5_ObcTxMsgBuf_Str.ID.Bits.PRIO = CAN_ID_BOOT_PRIO;
	
	L5_ObcTxMsgBuf_Str.ID.Bits.STD_ID = MSG_Tx_CAN_ID1;
	L5_ObcTxMsgBuf_Str.ID.Bits.EXT_ID = 0;

	CanTxFramePack1();
   	 /* put response data here */

    L5_ObcTxMsgBuf_Str.DATA.Bytes[0] = mCanTxFrameTag1.ucDara[0];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[1] = mCanTxFrameTag1.ucDara[1];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[2] = mCanTxFrameTag1.ucDara[2];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[3] = mCanTxFrameTag1.ucDara[3];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[4] = mCanTxFrameTag1.ucDara[4];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[5] = mCanTxFrameTag1.ucDara[5];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[6] = mCanTxFrameTag1.ucDara[6];
    L5_ObcTxMsgBuf_Str.DATA.Bytes[7] = mCanTxFrameTag1.ucDara[7];


    (void)mCAN_MB_08_11_Send_Message(&L5_ObcTxMsgBuf_Str);
}


/*
void SAFEPORT_CAN_L5_TxMsg()
{

	L5_ObcSAFEPORT_TxMsgBuf_Str.CS.Bits.SRR = SAFEPORT_CAN_CS_SRR;
	L5_ObcSAFEPORT_TxMsgBuf_Str.CS.Bits.IDE = SAFEPORT_CAN_CS_IDE;
	L5_ObcSAFEPORT_TxMsgBuf_Str.CS.Bits.RTR = SAFEPORT_CAN_CS_RTR;
	L5_ObcSAFEPORT_TxMsgBuf_Str.CS.Bits.LENGTH = 8;
	L5_ObcSAFEPORT_TxMsgBuf_Str.ID.Bits.PRIO = SAFEPORT_CAN_ID_APP_PRIO;
	L5_ObcSAFEPORT_TxMsgBuf_Str.ID.Bits.STD_ID = SAFEPORT_MSG_Tx_CAN_ID;
	L5_ObcSAFEPORT_TxMsgBuf_Str.ID.Bits.EXT_ID = 0;

	DebugCanTxFramePack();

   	 // put response data here 

    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[0] = mDebugCanTxFrameTag.ucDara[0];
    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[1] = mDebugCanTxFrameTag.ucDara[1];
    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[2] = mDebugCanTxFrameTag.ucDara[2];
    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[3] = mDebugCanTxFrameTag.ucDara[3];
    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[4] = mDebugCanTxFrameTag.ucDara[4];
    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[5] = mDebugCanTxFrameTag.ucDara[5];
    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[6] = mDebugCanTxFrameTag.ucDara[6];
    L5_ObcSAFEPORT_TxMsgBuf_Str.DATA.Bytes[7] = mDebugCanTxFrameTag.ucDara[7];


    (void)mSAFEPORT_CAN_MB_08_11_Send_Message(&L5_ObcSAFEPORT_TxMsgBuf_Str);
}
*/