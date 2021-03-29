#ifndef L3_DTC_CFG_H
#define L3_DTC_CFG_H  
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"

/*****************************************************************************
*   DTC Status variable definitions
*****************************************************************************/
#define L4_S_DTCSta_G_Str      ((DTC_STATUS_Str*)(DTC_DATA_RAM_START_ADDR + 0))
#define L4_S_DTCAGING_Ct_G_a   ((uint8*)(DTC_DATA_RAM_START_ADDR + 40))

#define L4_S_FaultSta_G_Str    ((FAULT_STATUS_Str*)(DTC_DATA_RAM_START_ADDR + 80))
#define L4_S_FaultAGING_Ct_G_a ((uint8*)(DTC_DATA_RAM_START_ADDR + 160))

#define L4_N_SnapShotCurrentPoint_F_u8 (*((uint8*)(DTC_DATA_RAM_START_ADDR + 240)))
#define L4_S_SnapShotData_G_Str        ((SNAPSHOT_FAULTCONDITION_Str*)(DTC_DATA_RAM_START_ADDR + 242))

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/
#define d_FAULT_AGING_THRESHOLD                 40u
#define d_PENDINGDTC_THRESHOLD                  2u
#define d_SNAPSHOT_FIFO_LENGTH                  10u
#define d_MAX_LOOP_LENGHT               		5u
/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
typedef enum
{
    e_DTC_ECU_ERROR,
    
    e_DTC_TORQUE_SENSOR_ERROR,
    e_DTC_ANGLE_SENSOR_ERROR,
    e_DTC_HW_POS_NOTTRIM_ERROR,
    
    e_DTC_MOTOR_ERROR,
    e_DTC_MOTOR_POS_ERROR,
    
    e_DTC_BATTERY_VOLTAGE_HIGH,
    e_DTC_BATTERY_VOLTAGE_LOW,
    
    e_DTC_IGN_VOLT_ERROR,
    
    e_DTC_ENG_MESSAGE_LOST,
    e_DTC_ENG_MESSAGE_ERROR,
    e_DTC_VEHSPD_MESSAGE_LOST,
    e_DTC_VEHSPD_MESSAGE_ERROR,
    e_DTC_CAN_BUSOFF,
    
    e_DTC_HANDLE

}DTC_INDEX_Enu;

typedef enum
{
    e_FAULT_UNEXP_EVENT_ERR,
    e_FAULT_CLOCK_ERR,
	e_FAULT_STKFLOW_ERR,
    e_FAULT_RAM_ERR,
    e_FAULT_FLASH_ERR,
    e_FAULT_TASKLOOP_ERR,
    e_FAULT_TASKFREQ_ERR,
	e_FAULT_ADC_ERR,
	e_FAULT_SPI1_ERR,
    e_FAULT_SPI2_ERR,
    e_FAULT_EEPROM_OPR_ERR,
    e_FAULT_MONITOR_ERR,
	e_FAULT_POWEROFF_ERR,
	e_FAULT_RELAYON_ERR,
    e_FAULT_RELAYOFF_ERR,
    e_FAULT_PRECHARGEON_ERR,
    e_FAULT_PREDRV_UNDERVOLT_ERR,
    e_FAULT_PREDRV_SHORTCIR_ERR,
    e_FAULT_PREDRV_OVERVTEMP,
    e_FAULT_HBRIDGE_CUTOFF_ERR,
    e_FAULT_TEMP_EXDLIM_ERR,
    e_FAULT_TEMP_SEN_ERR,
    e_FAULT_SENSOR_BAT_ERR,
    e_FAULT_T1_OPEN_ERR,
    e_FAULT_T1FRE_OUTRANGE_ERR,
    e_FAULT_T1DUTY_OUTRANGE_ERR,
    e_FAULT_T2_OPEN_ERR,
    e_FAULT_T2FRE_OUTRANGE_ERR,
    e_FAULT_T2DUTY_OUTRANGE_ERR,
    e_FAULT_T1T2_SYNC_ERR,
    e_FAULT_AP_OPEN_ERR,
    e_FAULT_APFRE_OUTRANGE_ERR,
    e_FAULT_APDUTY_OUTRANGE_ERR,
    e_FAULT_AS_OPEN_ERR,
    e_FAULT_ASFRE_OUTRANGE_ERR,
    e_FAULT_ASDUTY_OUTRANGE_ERR,
	e_FAULT_TRQ_NOTTRIM_ERR,
	e_FAULT_HWPOS_NOTTRIM_ERR,
	e_FAULT_BATVOLT_OFF_ERR,
	e_FAULT_BATVOLT_LOW_ERR,
	e_FAULT_BATVOLT_HIGH_ERR,
	e_FAULT_ENGSTS_LOST_ERR,
	e_FAULT_ENGSTS_INVALID_ERR,
	e_FAULT_VEHSPD_LOST_ERR,
	e_FAULT_VEHSPD_INVALID_ERR,
	e_FAULT_CAN_BUSOFF_ERR,
	e_FAULT_MOTCUR_SEN_TRIM_ERR,
    e_FAULT_MTRVOLT_CUTOFF_ERR,
    e_FAULT_MOTCUR_UNREASONABLE_ERR,
    e_FAULT_MOTCUR_NOBALANCE_ERR,
    e_FAULT_MOTCUR_OVER_ERR,
    e_FAULT_MOTCUR_OPEN_ERR,
    e_FAULT_HALL_EXDLIM_ERR,
    e_FAULT_RSLV_AMP_ERR,
    e_FAULT_HALL_OPEN_ERR,
    e_FAULT_RSLV_VCC_ERR,
    e_FAULT_IGN_VOLT_ERR,
    e_FAULT_HANDLE

}FAULT_CODE_Enu;


typedef union 
{
    uint8 DTC_Sta_u08;
    struct  
    {
        unsigned char WarningIndicatorReq_b:1;       //bit7
        unsigned char TestNotCompletedThisCycle_b:1; //bit6
        unsigned char TestFailedSinceLastClear_b:1;  //bit5
        unsigned char TestNotCompletedLastClear_b:1; //bit4
        unsigned char ConfirmedDTC_b:1;              //bit3
        unsigned char PendingDTC_b:1;                //bit2
        unsigned char TestFailedThisOperation_b:1;   //bit1  
        unsigned char TestFailed_b:1;                //bit0
    }bits;
}DTC_STATUS_Str;

typedef union 
{
    uint8 Fault_Sta_u08;
    struct 
    {
        unsigned char SnapShotCompleted_b:1;          //bit7
        unsigned char TestNotCompletedThisCycle_b:1;  //bit6
        unsigned char TestFailedSinceLastClear_b:1;   //bit5
        unsigned char TestNotCompletedLastClear_b:1;  //bit4
        unsigned char ConfirmedDTC_b:1;               //bit3
        unsigned char PendingDTC_b:1;                 //bit2
        unsigned char TestFailedThisOperation_b:1;    //bit1
        unsigned char TestFailed_b:1;                 //bit0
    }bits;
}FAULT_STATUS_Str;

typedef struct
{
    const uint8 DTC_ID_a3[2];
    const uint8 CfmCnt_u08;
    const uint8 AgeingCnt_u08;
}DTC_DATA_Str;

typedef struct
{
    const uint8 FaultIndex;
	const uint8 FaultLevel;
    const uint8 DTCIndex;
}FAULT_INFOR_Str;

typedef struct 
{   
    uint16 BatteryVolt_u16;
    uint16 VehicleSpeed_u16;
    uint16 Torque_u16[2];
    uint16 MotorCurrent_u16[2];
    uint16 PWMCmpValue_u16[3];
    uint16 MotorSpeed_u16;
    uint16 MosfetPower_u16;
    uint16 SensorPower_u16;
    sint16 MosfetTemp_s16;
    uint8 MotorPosition_u08[2];
    uint8 EngineState_u08;
    uint8 FaultIndex_u08;
}SNAPSHOT_FAULTCONDITION_Str;

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/
#define L_DTCSTATUS_MASK(x)         L4_S_DTCSta_G_Str[x].DTC_Sta_u08
#define L_DTC_ID_HIGH(x)            L4_S_DTCCfg_G_Str[x].DTC_ID_a3[0]
#define L_DTC_ID_MIDDLE(x)          L4_S_DTCCfg_G_Str[x].DTC_ID_a3[1]
#define L_DTC_ID_LOW(x)             L4_S_DTCCfg_G_Str[x].DTC_ID_a3[2]

#define d_FAULT_CODE_INDEX(x)		L4_S_FaultCode_G_Str[x].FaultIndex
#define d_FAULT_CODE_STA(x)         L4_S_FaultSta_G_Str[x].Fault_Sta_u08

#define d_SNAPSHOT_LENGTH       	sizeof(SNAPSHOT_FAULTCONDITION_Str)

#define d_SNAPSHOT_BAT(x)       L4_S_SnapShotData_G_Str[x].BatteryVolt_u16
#define d_SNAPSHOT_VSPD(x)      L4_S_SnapShotData_G_Str[x].VehicleSpeed_u16
#define d_SNAPSHOT_TOR_A(x)     L4_S_SnapShotData_G_Str[x].Torque_u16[0]
#define d_SNAPSHOT_TOR_B(x)     L4_S_SnapShotData_G_Str[x].Torque_u16[1]
#define d_SNAPSHOT_MCUR_U(x)    L4_S_SnapShotData_G_Str[x].MotorCurrent_u16[0]
#define d_SNAPSHOT_MCUR_V(x)    L4_S_SnapShotData_G_Str[x].MotorCurrent_u16[1]
#define d_SNAPSHOT_PWM_A(x)     L4_S_SnapShotData_G_Str[x].PWMCmpValue_u16[0]
#define d_SNAPSHOT_PWM_B(x)     L4_S_SnapShotData_G_Str[x].PWMCmpValue_u16[1]
#define d_SNAPSHOT_PWM_C(x)     L4_S_SnapShotData_G_Str[x].PWMCmpValue_u16[2]
#define d_SNAPSHOT_MSPD(x)      L4_S_SnapShotData_G_Str[x].MotorSpeed_u16
#define d_SNAPSHOT_MFPWR(x)     L4_S_SnapShotData_G_Str[x].MosfetPower_u16
#define d_SNAPSHOT_SNPWR(x)     L4_S_SnapShotData_G_Str[x].SensorPower_u16
#define d_SNAPSHOT_MFTMP(x)     L4_S_SnapShotData_G_Str[x].MosfetTemp_s16
#define d_SNAPSHOT_MPT_HALL(x)  L4_S_SnapShotData_G_Str[x].MotorPosition_u08[0]
#define d_SNAPSHOT_MPT_AB(x)    L4_S_SnapShotData_G_Str[x].MotorPosition_u08[1]
#define d_SNAPSHOT_ENG(x)       L4_S_SnapShotData_G_Str[x].EngineState_u08
#define d_SNAPSHOT_INDEX(x)   	L4_S_SnapShotData_G_Str[x].FaultIndex_u08

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern const DTC_DATA_Str L4_S_DTCCfg_G_Str[e_DTC_HANDLE];
extern const FAULT_INFOR_Str L4_S_FaultCode_G_Str[e_FAULT_HANDLE];

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
#endif  

/*End of L4_DTC_CFG.h file */

