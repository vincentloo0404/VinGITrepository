
/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "L4_DTC_CFG.h"
/*****************************************************************************
*   Local Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Local Macro Definitions
*****************************************************************************/
#define d_EEDTCDATA_RAMSTARTADDR_u16    0xBE00U

/*****************************************************************************
*   Local Function Declarations
*****************************************************************************/

/*****************************************************************************
*   Local Data Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Definitions
*****************************************************************************/
#define d_L4_SRVL_START_SEC_EE_RAW_VAR 
#include "MemMap.h" 

#if 0
DTC_STATUS_Str L4_S_DTCSta_G_Str[e_DTC_HANDLE];
uint8 L4_S_DTCAGING_Ct_G_a[e_DTC_HANDLE];

HT_SAAE_FAULT_STATUS_Str L4_S_FaultSta_G_Str[e_FAULT_HANDLE] ;
uint8 L4_S_FaultAGING_Ct_G_a[e_FAULT_HANDLE] ;
SNAPSHOT_FAULTCONDITION_Str L4_S_SnapShotData_G_Str[d_SNAPSHOT_FIFO_LENGTH];
uint8 L4_N_SnapShotCurrentPoint_F_u8;
#endif

#define d_L4_SRVL_STOP_SEC_EE_RAW_VAR
#include "MemMap.h" 

#define d_L4DTC_START_SEC_CONST     
#include "MemMap.h" 

const DTC_DATA_Str L4_S_DTCCfg_G_Str[e_DTC_HANDLE] =
{
      /*DTC ID*/  /*Confirm counter*/  /*Aging counter*/
    { {0x55,0x00},    5,                  40},
    { {0x55,0x01},    5,                  40},
    { {0x55,0x14},    5,                  40},
    { {0x55,0x17},    5,                  40},
    { {0x55,0x21},    5,                  40},
    { {0x55,0x22},    5,                  40},
    { {0x55,0x23},    5,                  40},
    { {0x55,0x44},    5,                  40},
    { {0x55,0x21},    5,                  40},
    { {0x55,0x22},    5,                  40},
    { {0x55,0x23},    5,                  40},
    { {0x55,0x44},    5,                  40},
    { {0x55,0x44},    5,                  40},
    { {0x55,0x44},    5,                  40},
};
#if 0
const HT_SAAE_FAULT_INFOR_Str L4_S_FaultCode_G_Str1[e_FAULT_HANDLE1] =
{
    {0x01, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_UNEXPECTED_EVENT    */
    {0x02, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_EXTOSC_INI          */
    {0x03, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_INTOSC_INI          */
    {0x04, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_OSCWDT_TRAP         */
    {0x05, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_VCOLCK_TRAP         */
    {0x06, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_STKFLOW_TRAP        */
    {0x07, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_SOFTBRK_TRAP        */
    {0x08, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_ACER_TRAP           */
    {0x09, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_ILLOPT_TRAP         */
    {0x0A, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_MPU_INI             */
    {0x0B, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_MPU_TRAP            */
    {0x0C, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_ALU_INI             */
    {0x0D, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_ALU_RUN             */
    {0x0E, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_SBRAM_INI           */
    {0x0F, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_RAM_INI             */
    {0x10, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_TASKLOOP_RUN        */
    {0x11, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_TASKFREQ_TRAP       */
    {0x12, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_ADC_RUN             */
    {0x13, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_U0C1_RUN            */
    {0x14, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_U1C0_RUN            */
    {0x15, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_MONITOR_RUN         */
    {0x16, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_EEPROM_SAVE_RUN     */
    {0x17, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_EEPROM_INTG_EXT     */
    {0x18, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_HOLDOFF_EXT         */
    {0x19, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_RELAYON_RUN         */
    {0x1A, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_RELAYOFF_EXT        */
    {0x1B, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_PRECHARGEON_INI     */
    {0x1C, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_PREDRV_UNDERVOLT    */
    {0x1D, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_PREDRV_SHORTCIR     */
    {0x1E, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_PREDRV_OVERVOLTTEMP */
    {0x1F, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_HBRIDGE_CUTOFF      */
    {0x20, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_SENVOLT_RUN         */
    {0x21, 5, e_DTC_ECU_ERROR},            /* -> e_FAULT_TEMP_EXDLIM_RUN     */
    {0x22, 2, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T1OUTRANGE_RUN      */
    {0x23, 2, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T2OUTRANGE_RUN      */
    {0x24, 2, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T1T2SUMERR_RUN      */
    {0x25, 5, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_P1P2SUMERR_RUN      */
    {0x26, 5, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_EPSPSTERR_RUN       */
    {0x27, 5, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_P3OUTRANGE_RUN      */
    {0x28, 5, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_TRQ_NOTTRIM_INI     */
    {0x29, 5, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_HWPOS_NOTTRIM_INI   */
    {0x2A, 3, e_DTC_BATTERY_VOLTAGE_LOW},  /* -> e_FAULT_BATVOLT_OFF         */
    {0x2B, 3, e_DTC_BATTERY_VOLTAGE_LOW},  /* -> e_FAULT_BATVOLT_LOW         */
    {0x2C, 3, e_DTC_BATTERY_VOLTAGE_HIGH}, /* -> e_FAULT_BATVOLT_HIGH        */
    {0x2D, 4, e_DTC_CAN_BUSOFF},  		   /* -> e_FAULT_CANOFF_RUN          */
    {0x2E, 4, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_ENGSTS_LOST         */
    {0x2F, 4, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_ENGSTS_INVALID      */
    {0x30, 5, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_VEHSPD_LOST         */
    {0x31, 5, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_VEHSPD_INVALID      */
    {0x32, 4, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_STRANG_LOST         */
    {0x33, 4, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_STRANG_INVALID      */
    {0x34, 4, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_STRANGSPD_LOST      */
    {0x35, 4, e_DTC_CAN_MESSAGE_LOST},     /* -> e_FAULT_STRANGSPD_INVALID   */
    {0x36, 1, e_DTC_FLASH_ERROR},     	   /* -> e_FAULT_FLASH_CKS_INI       */
    {0x37, 1, e_DTC_FLASH_ERROR},          /* -> e_FAULT_FLASH_OPT_EXT       */
    {0x38, 5, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTR_NOTTRIM_INI     */
    {0x39, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTRVOLT_CUTOFF      */
    {0x3A, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTRCURRUW_ZEROOFFSET*/
    {0x3B, 1, e_DTC_MOTOR_ERROR},  		   /* -> e_FAULT_MTRCURRUW_UNREASONABLE*/
    {0x3C, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTRCURRUW_NOBALANCE */
    {0x3D, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTRCURR_OVER        */
    {0x3E, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTRCURR_OPEN        */
	{0x3F, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_HALL_EXDLIM_RUN     */
	{0x40, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_HALL_SHORTCIR_RUN   */
	{0x41, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_ENCODER_EXDLIM_RUN  */
	{0x42, 1, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTRCURR_LOOP        */

};
#endif
const FAULT_INFOR_Str L4_S_FaultCode_G_Str[e_FAULT_HANDLE] =
{
    {0x01, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_UNEXP_EVENT_ERR,       */
    {0x02, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_CLOCK_ERR,				*/
    {0x03, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_STKFLOW_ERR,			*/
    {0x04, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_RAM_ERR,				*/
    {0x05, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_FLASH_ERR,				*/
    {0x06, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_TASKLOOP_ERR,			*/
    {0x07, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_TASKFREQ_ERR,			*/
    {0x08, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_ADC_ERR,				*/
    {0x09, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_SPI1_ERR,				*/
    {0x0A, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_SPI2_ERR,				*/
    {0x0B, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_EEPROM_OPR_ERR,		*/
    {0x0C, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_MONITOR_ERR,			*/
    {0x0D, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_POWEROFF_ERR,			*/
    {0x0E, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_RELAYON_ERR,			*/
    {0x0F, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_RELAYOFF_ERR,			*/
    {0x10, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_PRECHARGEON_ERR,		*/
    {0x11, 0, e_DTC_ECU_ERROR},            /* -> e_FAULT_PREDRV_UNDERVOLT_ERR,  */
    {0x12, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_PREDRV_SHORTCIR_ERR,   */
    {0x13, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_PREDRV_OVERVTEMP,		*/
    {0x14, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_HBRIDGE_CUTOFF_ERR,    */
    {0x15, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_TEMP_HIGH_ERR,			*/
    {0x16, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_TEMP_SEN_ERR,			*/
    {0x17, 1, e_DTC_ECU_ERROR},            /* -> e_FAULT_SENSOR_BAT_ERR,		*/
    {0x18, 1, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T1_OPEN_ERR,			*/
    {0x19, 1, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T1FRE_OUTRANGE_ERR,    */
    {0x1A, 1, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T1DUTY_OUTRANGE_ERR,   */
    {0x1B, 1, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T2_OPEN_ERR,			*/
    {0x1C, 1, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T2FRE_OUTRANGE_ERR,    */
    {0x1D, 1, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T2DUTY_OUTRANGE_ERR,   */
    {0x1E, 1, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_T1T2_SYNC_ERR,			*/
    {0x1F, 1, e_DTC_ANGLE_SENSOR_ERROR},   /* -> e_FAULT_AP_OPEN_ERR,			*/
    {0x20, 1, e_DTC_ANGLE_SENSOR_ERROR},   /* -> e_FAULT_APFRE_OUTRANGE_ERR,    */
    {0x21, 5, e_DTC_ANGLE_SENSOR_ERROR},   /* -> e_FAULT_APDUTY_OUTRANGE_ERR,   */
    {0x22, 2, e_DTC_ANGLE_SENSOR_ERROR},   /* -> e_FAULT_AS_OPEN_ERR,			*/
    {0x23, 2, e_DTC_ANGLE_SENSOR_ERROR},   /* -> e_FAULT_ASFRE_OUTRANGE_ERR,    */
    {0x24, 2, e_DTC_ANGLE_SENSOR_ERROR},   /* -> e_FAULT_ASDUTY_OUTRANGE_ERR,   */
    {0x25, 5, e_DTC_TORQUE_SENSOR_ERROR},  /* -> e_FAULT_TRQ_NOTTRIM_ERR,		*/
    {0x26, 5, e_DTC_HW_POS_NOTTRIM_ERROR}, /* -> e_FAULT_HWPOS_NOTTRIM_ERR,		*/
    {0x27, 5, e_DTC_BATTERY_VOLTAGE_LOW},  /* -> e_FAULT_BATVOLT_OFF_ERR,		*/
    {0x28, 5, e_DTC_BATTERY_VOLTAGE_LOW},  /* -> e_FAULT_BATVOLT_LOW_ERR,		*/
    {0x29, 5, e_DTC_BATTERY_VOLTAGE_HIGH}, /* -> e_FAULT_BATVOLT_HIGH_ERR,		*/
    {0x2A, 3, e_DTC_ENG_MESSAGE_LOST},     /* -> e_FAULT_ENGSTS_LOST_ERR,		*/
    {0x2B, 3, e_DTC_ENG_MESSAGE_ERROR},    /* -> e_FAULT_ENGSTS_INVALID_ERR,    */
    {0x2C, 3, e_DTC_VEHSPD_MESSAGE_LOST},  /* -> e_FAULT_VEHSPD_LOST_ERR,		*/
    {0x2D, 4, e_DTC_VEHSPD_MESSAGE_ERROR}, /* -> e_FAULT_VEHSPD_INVALID_ERR,    */
    {0x2E, 4, e_DTC_CAN_BUSOFF},           /* -> e_FAULT_CAN_BUSOFF_ERR,		*/
    {0x2F, 4, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MOTCUR_SEN_TRIM_ERR,   */
    {0x30, 5, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MTRVOLT_CUTOFF_ERR,    */
    {0x31, 5, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MOTCUR_UNREASONABLE_ERR*/
    {0x32, 4, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MOTCUR_NOBALANCE_ERR,  */
    {0x33, 4, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MOTCUR_OVER_ERR,		*/
    {0x34, 4, e_DTC_MOTOR_ERROR},          /* -> e_FAULT_MOTCUR_OPEN_ERR,		*/
    {0x35, 4, e_DTC_MOTOR_POS_ERROR},      /* -> e_FAULT_HALL_EXDLIM_ERR,		*/
    {0x36, 1, e_DTC_MOTOR_POS_ERROR},      /* -> e_FAULT_HALL_SHORTCIR_ERR,		*/
    {0x37, 1, e_DTC_MOTOR_POS_ERROR},      /* -> e_FAULT_HALL_OPEN_ERR,         */
    {0x38, 1, e_DTC_MOTOR_POS_ERROR},      /* -> e_FAULT_RSLV_VCC_ERR,    */
    {0x39, 1, e_DTC_IGN_VOLT_ERROR},       /* -> e_FAULT_IGN_VOLT_ERR,          */
};

#define d_L4DTC_STOP_SEC_CONST
#include "MemMap.h" 

/*End of L4_DTC_Data.c file*/

