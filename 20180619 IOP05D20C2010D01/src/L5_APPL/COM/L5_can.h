/*
 * L5_can.h
 *
 *  Created on: 2016年4月21日
 *      Author: YCH
 */

#ifndef APP_COMM_INCLUDE_L5_CAN_H_
#define APP_COMM_INCLUDE_L5_CAN_H_

#include "my_all.h"

#include "Common.h"
#include "MPC560xP.h"
#include "m_CAN_Drv.h"
#include "m_CAN_Cfg.h"
#include "L3_CAN.h"
#include "L3_CAN_Cfg.h"
#include "obc_app.h"


#define DCDC_VOLT_PHY_DBC_CONVERT(CAN_DATA) (float)((CAN_DATA)>>1)
#define DCDC_VOLT_AD_DBC_CONVERT(CAN_DATA) (uint16)((uint32)(CAN_DATA)*1024*10.5115/5000/2)
#define DCDC_CURRENT_AD_DBC_CONVERT(CAN_DATA) (uint16)(((CAN_DATA) + 2.5*16)*(49.152/16))
//#define DCDC_CURRENT_AD_DBC_CONVERT(CAN_DATA) (uint16)(((CAN_DATA) + 40)*(71.68/16))
//#include "L3_safetyPortCAN.h"
//#include "L3_safetyPortCAN_Cfg.h"

#define CCSTATE_NULL (0)
#define CCSTATE_A (1)
#define CCSTATE_B (2)
#define CCSTATE_C (3)
#define CCSTATE_C1 (4)
#define CCSTATE_D (5)
#define CCSTATE_D1 (6)
#define CCSTATE_E (7)
#define CCSTATE_E1 (8)
#define CCSTATE_F (9)
#define CCSTATE_F1 (0xA)

/*
enum CCSTATE
{
      CCSTATE_NULL=0,CCSTATE_A=1, CCSTATE_B, CCSTATE_C, CCSTATE_C1, CCSTATE_D, CCSTATE_D1, CCSTATE_E,CCSTATE_E1,CCSTATE_F,CCSTATE_F1
};
*/
typedef union
{
	volatile uint8_t ucDara[8];
	struct
	{
		uint8_t BMS04_CCState:4;
		uint8_t Byte0Reserve:4;
		uint8_t Byte1Reserve:2;
		uint8_t BMS04_FastCharMode:4;
		uint8_t BMS04_OBCModeH:2;
		uint8_t BMS04_OBCModeL:2;
		uint8_t BMS04_DCChrRlySt:2;
		uint8_t Byte2Reserve:2;
		uint8_t BMS04_EnCharger:1;
		uint8_t Byte2Reserve1:1;
		uint8_t BMS04_ACChrRlySt:2;
		uint8_t BMS04_ChrTimeRemainH:6;
		uint8_t BMS04_ChrTimeRemainL:4;
		uint8_t BMS04_ChrCurrentSpH:4;
		uint8_t BMS04_ChrCurrentSpL:6;
		uint8_t BMS04_ChrVoltSpH:2;
		uint8_t BMS04_ChrVoltSpL:8;
		uint8_t BMS04_DcChrCntSt:2;
		uint8_t BMS04_AcChrCntSt:2;
		uint8_t BMS04_Counter:4;
	}bit;
}CanRxFrameTag;

extern CanRxFrameTag mCanRxFrameTag;

typedef union
{
	volatile uint8_t ucDara[8];
	struct
	{
		uint8_t CHR01_bFaultHW:1;
		uint8_t CHR01_bFaultAC:1;
		uint8_t CHR01_bErrorCOM:1;
		uint8_t CHR01_bFaultDC:1;
		uint8_t CHR01_bOverTempCool:1;
		uint8_t CHR01_bFaultCable:1;
		uint8_t CHR01_bWakeUp:1;
		uint8_t CHR01_ReqCloseRly:1;
		uint8_t Byte1Reserve:3;
		uint8_t CHR01_PowerLimit:1;
		uint8_t CHR01_SWVersionH:4;
		uint8_t CHR01_SWVersionL:4;
		uint8_t CHR01_actChrCurrentH:4;
		uint8_t CHR01_actChrCurrentL:6;
		uint8_t CHR01_actChrVoltH:2;
		uint8_t CHR01_actChrVoltL;
		uint8_t CHR01_ChrTemp;
		uint8_t CHR01_FaultID;
		uint8_t CHR01_ChrOpMode:3;
		uint8_t Byte7Reserve:1;
		uint8_t CHR01_Counter:4;
	}bit;
}CanTxFrameTag;

extern CanTxFrameTag mCanTxFrameTag;




typedef union
{
	volatile uint8_t ucDara[8];
	struct
	{
		uint8_t CHR02_CCState:4;
		uint8_t Byte1Reserve:2;
		uint8_t CHR02_UINVoltH:2;
		uint8_t CHR02_UINVoltL:8;
		uint8_t CHR02_CPState:3;
		uint8_t Byte3Reserve:3;
		uint8_t CHR02_PFCVoltH:2;
		uint8_t CHR02_PFCVoltL:8;
		uint8_t Byte5Reserve;
		uint8_t Byte6Reserve;
		uint8_t Byte7Reserve;
		uint8_t Byte8Reserve;
		
	}bit;
}CanTxFrameTag1;

extern CanTxFrameTag1 mCanTxFrameTag1;




typedef union
{
	volatile uint8_t ucDara[8];
	struct
	{
		uint8_t bHWDCDC_OVP			:1;// HWDCDC_OVP
    	uint8_t bOverDCUoutI		:1;// OverUoutI

    	uint8_t bOverUinVolt		:1;// Overvoltage  220v过压
    	uint8_t bUnderUinVolt		:1;// Undervoltage     220v欠压

    	uint8_t bOverDCUoutVolt		:1;//
    	uint8_t bUnderDCUoutVolt	:1;//

    	uint8_t bHWDCDC_OCP			:1;//
    	uint8_t bOverTempCool		:1;

    	uint8_t bloadDump				:1;
    	uint8_t bDriver13VFault		:1;
    	uint8_t bLV12VFault			:1;

    	uint8_t bHWPFC_OVP			:1;
    	uint8_t bHWPFC_OCP			:1;
    	uint8_t bOverPFCUoutVolt	:1;
    	uint8_t bUnderPFCUoutVolt	:1;
    	uint8_t bOverPFCUoutI		:1;
		uint8_t Byte2Reserve;
		uint8_t Byte3Reserve;
		uint8_t Byte4Reserve;
		uint8_t Byte5Reserve;
		uint8_t Byte6Reserve;
		uint8_t Byte7Reserve;

	}bit;
}DebugCanTxFrameTag;

extern DebugCanTxFrameTag mDebugCanTxFrameTag;



typedef struct
{
	uint8_t ucCanLiveCntr;
	uint8_t ucBusoffCntr;
	uint8_t	ucBusRecoveryCntr;
	uint8_t ucCanRecvBuff[8];
}CanCtrlParaTag;
extern CanCtrlParaTag	stCanCrtlPara;		// Can控制参数



typedef struct
{
	uint8_t index;
	uint16_t RC;
	uint16_t R4;
	uint8_t S3;
	uint8_t IMax;
}CC_STATE_TAG;
extern CC_STATE_TAG	CC_STATE_Tag[];		// CC控制参数


extern uint8_t	CC_STATE_ARR[];		// CC控制参数



#define CanSendTest_THREAD_CYCLE_TIME 100  //单位都是ms
#define CanSendInfo_THREAD_CYCLE_TIME 100  //单位都是ms



#define HARDWARE_VERSION_INTEGER    0xc	// 硬件版本号
#define HARDWARE_VERSION_DECIMAL    1	// 硬件版本号
#define SOFTWARE_VERSION_INTEGER    20	// 软件版本号
#define SOFTWARE_VERSION_DECIMAL    15	// 软件版本号
#define SOFTWARE_DATA_VERSION    	01	// 数据版本号


#define DBC_VERSION_H    	1	//dbc协议中显示的版本 高位
#define DBC_VERSION_L    	15//dbc协议中显示的版本 低位


extern uint8_t k_hardware_version_integer;
extern uint8_t k_hardware_version_decimal;
extern uint8_t k_software_version_integer;
extern uint8_t k_software_version_decimal;
extern uint8_t k_software_data_version;

#define  CLOSE_RLY 1
#define  OPEN_RLY  0

#define  BMS_EN_CHARGER 1
#define  BMS_DIS_CHARGER 0

extern void CanTxFramePack(void);
void DebugCanTxFramePack(void);
extern void CanTxFrameUnpack(uint8 * data);
extern void CanDBCModeCov(uint8_t mode);
extern void SAFEPORT_CAN_L5_TxMsg(void);
extern void CAN_L5_TxMsg(void);

extern volatile uint16 k_Dcdc_Vref_Ct_u16;
extern volatile uint16 k_Dcdc_Iref_Ct_u16;

extern volatile uint16 k_Dcdc_SetpInitIref_Ct_u16;
extern volatile uint16 k_Dcdc_SetpIref_Ct_u16;

extern volatile uint16 k_Dcdc_startOnVref_Ct_u16;




#endif
