#ifndef L3_CAN_H
#define L3_CAN_H  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L4_DTC.h"
#include "L3_CAN_Cfg.h"
#include "m_CAN_Drv.h"
#include "m_CAN_Cfg.h"
#include "L3_IgnitionSignal.h"
#include "L4_FaultManager.h"
#include "V_ccp.h"
#include "L3_Data.h"


/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/


/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
typedef uint16* PU16;
typedef uint32* PU32;


typedef union
{
   uint8 byte;
   struct
   {
       unsigned char bit0:1;
       unsigned char bit1:1;
       unsigned char bit2:1;
       unsigned char bit3:1;
       unsigned char bit4:1;
       unsigned char bit5:1;
       unsigned char bit6:1;
       unsigned char bit7:1; 
   }bits;
}CAN_UNDATA;

typedef struct
{
    uint8 length;
    uint8 frame[8];
}CAN_MSSAGE_T;

typedef struct
{
    uint8 initdelay_u8;
    uint8 period_u8;  
    uint8 poweronct_u8;
    uint8 counter_u8;
}CAN_TXMSG_ST;

typedef enum
{
   e_NOBUSOFF,
   e_BUSOFFRCV,
   e_BUSOFFTEM,
   e_BUSOFFCRM,
   e_WAIT  
}CAN_STATUS_Enu;


#define ENGINE_STOPPING (3)
#define ENGINE_STARING  (2)
#define ENGINE_RUNNING  (1)
#define ENGINE_OFF      (0)


/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

#define CALC_CANTXMSG_PRD(period)     ((period)/CAN_TIMETABLE_TICK)
#define CALC_CANRXMSG_PRD(period)     ((period)/CAN_TIMETABLE_TICK)

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern CAN_STATUS_Enu L3_S_CANSta_Ct_M_Enu;


/*--------------TX Message 0x230 (EPS)----------------*/
extern uint8 L3_S_EPS_EPSFault_Ct_G_u08;

/* Rx Message Buffer */
extern uint8 L3_S_EspMsgBuf_F_u08[8];
extern uint8 L3_S_EmsMsgBuf_F_u08[8];

/* can message timeout flag */
extern uint8 L3_S_Ems1MsgTimeOut_Uls_G_u08;
extern uint8 L3_S_Esp3MsgTimeOut_Uls_G_u08;

/* 发动机转速信号
 * Received from Message 0x278 (EMS3) */
extern uint16 L3_S_CANEngineSpeed_rpm_G_u16;
extern uint8 L3_S_CANEngineSpeedValid_Ct_G_u08;

/* 车速信号
 * Received from Message 0x311 (ABS1) */
extern uint16 L3_S_CANVehicleSpeed_Kph_G_u16p06;
extern uint8 L3_S_CANVehicleSpeedValid_Ct_G_u08;

/*For CAN test*/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void CAN_L3_Init(void);
extern void CAN_L3_Per(void);
extern uint8 CAN_L3_TP_Transmit(void);

extern void CANRx_L3_Esp1Msg(uint8* pRxData);
extern void CANRx_L3_Ecm1Msg(uint8* pRxData);

extern uint8 L3_S_BMSMsgTimeOut_Uls_G_u08;
/*For CAN Test*/

#endif
/*End of L3_CAN.h file */
