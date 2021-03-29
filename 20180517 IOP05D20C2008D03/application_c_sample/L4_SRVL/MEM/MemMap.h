/*****************************************************************************
*   Copyright 2010 - 2011 Shanghai Aerospace Automobile Electromechanical 
*   Co., Ltd., all rights reserved.
*
*   Filename:    MemMap.h
*
*   Description: This file is the C header file for the Memory Map
*
*   Revision History:
*
*   Date            Author          Description
*   ----------      ----------      -----------------------------------------
*   2012-09-20      xuefeng.fan     Initial created
*
*****************************************************************************/

/*****************************************************************************
*   Include Files
*****************************************************************************/

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/
/*********************************************************
 *           变量绝对地址分配
 *********************************************************/
/* 绝对地址分配START_ABSOLUTE_ADDRESS_VAR */
#if 0

#if defined(d_L2RAM_START_ABSOLUTE_ADDRESS_VAR)
    #undef d_L2RAM_START_ABSOLUTE_ADDRESS_VAR
    #define RAMTEST_StoreAddress1               0xB0C0U
    #define RAMTEST_StoreAddress2               0xB0C4U
#elif (defined(d_L3MOTORSIGNAL_START_ABSOLUTE_ADDRESS_VAR)||\
      (defined(d_L2IRQ_START_ABSOLUTE_ADDRESS_VAR)))
    #undef d_L3MOTORSIGNAL_START_ABSOLUTE_ADDRESS_VAR
    #undef d_L2IRQ_START_ABSOLUTE_ADDRESS_VAR
    /*Encode Value store address*/
    #define EncoderValue_StoreAddress           0xB9C0U
   /*Encode Offset Value store address*/
    #define EncoderOffsetValue_StoreAddress     0xB9C2U
    /*Rotation Direction Value store address*/
    #define RotationDirection_StoreAddress      0xB9C4U
    /*Motor Current Value store address*/
    #define MotroCurrent_StroeAddress           0xB9C6U
#elif defined(d_L4EEPROMMANAGEMENT_START_ABSOLUTE_ADDRESS_VAR)
    #undef d_L4EEPROMMANAGEMENT_START_ABSOLUTE_ADDRESS_VAR
    /*Rotation Direction Value store address*/
    #define EEPROM_RAW_StartAddress           	0xBE00U
    /*Rotation Direction Value store address*/
    #define EEPROM_Shadow_StartAddress        	0xBA00U

#endif

/*********************************************************
 *           单个模块的Code区域分配
 *********************************************************/
/* 单个模块的START_SEC_CODE */
#if defined(d_CSTART_START_SEC_CODE)
    #undef d_CSTART_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2USIC_START_SEC_CODE)
    #undef d_L2USIC_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2SBRAM_START_SEC_CODE)
    #undef d_L2SBRAM_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2PORT_START_SEC_CODE)
    #undef d_L2PORT_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2MCAL_START_SEC_CODE)
    #undef d_L2MCAL_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2RAM_START_SEC_CODE)
    #undef d_L2RAM_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2ALU_START_SEC_CODE)
    #undef d_L2ALU_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2RTC_START_SEC_CODE)
    #undef d_L2RTC_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2WDT_START_SEC_CODE)
    #undef d_L2WDT_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2GPT_START_SEC_CODE)
    #undef d_L2GPT_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2CC2_START_SEC_CODE)
    #undef d_L2CC2_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2ADC_START_SEC_CODE)
    #undef d_L2ADC_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2CCU6_START_SEC_CODE)
    #undef d_L2CCU6_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2PORT_START_SEC_CODE)
    #undef d_L2PORT_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2IRQ_START_SEC_CODE)
    #undef d_L2IRQ_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2MCUDIAGNOSIS_START_SEC_CODE)
    #undef d_L2MCUDIAGNOSIS_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2MPU_START_SEC_CODE)
    #undef d_L2MPU_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2SCU_START_SEC_CODE)
    #undef d_L2SCU_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L2CAN_START_SEC_CODE)
    #undef d_L2CAN_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE
    
#elif defined(d_L2FLASH_START_SEC_CODE)
    #undef d_L2FLASH_START_SEC_CODE
    #define d_L2_MCAL_START_SEC_CODE

#elif defined(d_L3ECAL_START_SEC_CODE)
    #undef d_L3ECAL_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3STDLIB_START_SEC_CODE)
    #undef d_L3STDLIB_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3ECUDIAGNOSIS_START_SEC_CODE)
    #undef d_L3ECUDIAGNOSIS_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3ECALFAILSAFE_START_SEC_CODE)
    #undef d_L3ECALFAILSAFE_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3ECUDIAG_START_SEC_CODE)
    #undef d_L3ECUDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3BATTVOLTDIAG_START_SEC_CODE)
    #undef d_L3BATTVOLTDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3SENSORVOLTDIAG_START_SEC_CODE)
    #undef d_L3SENSORVOLTDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3TORQUESENSORDIAG_START_SEC_CODE)
    #undef d_L3TORQUESENSORDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3STRANGLESENSORDIAG_START_SEC_CODE)
    #undef d_L3STRANGLESENSORDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3ENGINESTATUSDIAG_START_SEC_CODE)
    #undef d_L3ENGINESTATUSDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3VEHICLESPEEDDIAG_START_SEC_CODE)
    #undef d_L3VEHICLESPEEDDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3PRECHARGEDIAG_START_SEC_CODE)
    #undef d_L3PRECHARGEDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3POWRELAYDIAG_START_SEC_CODE)
    #undef d_L3POWRELAYDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3PREDRIVERDIAG_START_SEC_CODE)
    #undef d_L3PREDRIVERDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3HBRIDGEDIAG_START_SEC_CODE)
    #undef d_L3HBRIDGEDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3TEMPERATUREDIAG_START_SEC_CODE)
    #undef d_L3TEMPERATUREDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3TEMPDIAGMT_START_SEC_CODE)
    #undef d_L3TEMPDIAGMT_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3MOTORCURRDIAG_START_SEC_CODE)
    #undef d_L3MOTORCURRDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3CURRDIAGMT_START_SEC_CODE)
    #undef d_L3CURRDIAGMT_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3MOTORVOLTDIAG_START_SEC_CODE)
    #undef d_L3MOTORVOLTDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3PHASEDIAGMT_START_SEC_CODE)
    #undef d_L3PHASEDIAGMT_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3MOTORPOSDIAG_START_SEC_CODE)
    #undef d_L3MOTORPOSDIAG_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3HALLDIAGMT_START_SEC_CODE)
    #undef d_L3HALLDIAGMT_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE


#elif defined(d_L3HANDWHEELSIGNAL_START_SEC_CODE)
    #undef d_L3HANDWHEELSIGNAL_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_BIPST_START_SEC_CODE)
    #undef d_BIPST_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3MOTORSIGNAL_START_SEC_CODE)
    #undef d_L3MOTORSIGNAL_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3EEPROM_START_SEC_CODE)
    #undef d_L3EEPROM_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3POWERCIRCUITSIGNAL_START_SEC_CODE)
    #undef d_L3POWERCIRCUITSIGNAL_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3PREDRIVERSIGNAL_START_SEC_CODE)
    #undef d_L3PREDRIVERSIGNAL_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3MONITOR_START_SEC_CODE)
    #undef d_L3MONITOR_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3CAN_START_SEC_CODE)
    #undef d_L3CAN_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L3EEP_START_SEC_CODE)
    #undef d_L3EEP_START_SEC_CODE
    #define d_L3_ECAL_START_SEC_CODE

#elif defined(d_L4ECUSTATEMANAGEMENT_START_SEC_CODE)
    #undef d_L4ECUSTATEMANAGEMENT_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4FAULTMANAGER_START_SEC_CODE)
    #undef d_L4FAULTMANAGER_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4EEPROMMANAGEMENT_START_SEC_CODE)
    #undef d_L4EEPROMMANAGEMENT_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4NVMAPPDATA_START_SEC_CODE)
    #undef d_L4NVMAPPDATA_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4SCHEDULEMANAGEMENT_START_SEC_CODE)
    #undef d_L4SCHEDULEMANAGEMENT_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4MAIN_START_SEC_CODE)
    #undef d_L4MAIN_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4SRVL_START_SEC_CODE)
    #undef d_L4SRVL_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4MONITORSRV_START_SEC_CODE)
    #undef d_L4MONITORSRV_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4TP_START_SEC_CODE)
    #undef d_L4TP_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4UDS_START_SEC_CODE)
    #undef d_L4UDS_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4DTC_START_SEC_CODE)
    #undef d_L4DTC_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4CCP_START_SEC_CODE)
    #undef d_L4CCP_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L4SYSTEMTEST_START_SEC_CODE)
    #undef d_L4SYSTEMTEST_START_SEC_CODE
    #define d_L4_SRVL_START_SEC_CODE

#elif defined(d_L5APPL_START_SEC_CODE)
    #undef d_L5APPL_START_SEC_CODE
    #define d_L5_APPL_START_SEC_CODE

#elif defined(d_L5APPLFAILSAFE_START_SEC_CODE)
    #undef d_L5APPLFAILSAFE_START_SEC_CODE
    #define d_L5_APPL_START_SEC_CODE

#elif defined(d_L5MOTORCTRL_START_SEC_CODE)
    #undef d_L5MOTORCTRL_START_SEC_CODE
    #define d_L5_APPL_START_SEC_CODE

#elif defined(d_L5POWERSTEERINGCTRL_START_SEC_CODE)
    #undef d_L5POWERSTEERINGCTRL_START_SEC_CODE
    #define d_L5_APPL_START_SEC_CODE

#else
    /* Nothing is defined */

#endif


/* 单个模块的STOP_SEC_CODE */
#if defined(d_CSTART_STOP_SEC_CODE)
    #undef d_CSTART_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2USIC_STOP_SEC_CODE)
    #undef d_L2USIC_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2SBRAM_STOP_SEC_CODE)
    #undef d_L2SBRAM_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2PORT_STOP_SEC_CODE)
    #undef d_L2PORT_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2MCAL_STOP_SEC_CODE)
    #undef d_L2MCAL_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2RAM_STOP_SEC_CODE)
    #undef d_L2RAM_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2ALU_STOP_SEC_CODE)
    #undef d_L2ALU_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2RTC_STOP_SEC_CODE)
    #undef d_L2RTC_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2WDT_STOP_SEC_CODE)
    #undef d_L2WDT_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2GPT_STOP_SEC_CODE)
    #undef d_L2GPT_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2CC2_STOP_SEC_CODE)
    #undef d_L2CC2_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2ADC_STOP_SEC_CODE)
    #undef d_L2ADC_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2CCU6_STOP_SEC_CODE)
    #undef d_L2CCU6_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2PORT_STOP_SEC_CODE)
    #undef d_L2PORT_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2IRQ_STOP_SEC_CODE)
    #undef d_L2IRQ_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2MCUDIAGNOSIS_STOP_SEC_CODE)
    #undef d_L2MCUDIAGNOSIS_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2MPU_STOP_SEC_CODE)
    #undef d_L2MPU_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2SCU_STOP_SEC_CODE)
    #undef d_L2SCU_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2CAN_STOP_SEC_CODE)
    #undef d_L2CAN_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L2FLASH_STOP_SEC_CODE)
    #undef d_L2FLASH_STOP_SEC_CODE
    #define d_L2_MCAL_STOP_SEC_CODE

#elif defined(d_L3ECAL_STOP_SEC_CODE)
    #undef d_L3ECAL_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3STDLIB_STOP_SEC_CODE)
    #undef d_L3STDLIB_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3ECUDIAGNOSIS_STOP_SEC_CODE)
    #undef d_L3ECUDIAGNOSIS_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3ECALFAILSAFE_STOP_SEC_CODE)
    #undef d_L3ECALFAILSAFE_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3ECUDIAG_STOP_SEC_CODE)
    #undef d_L3ECUDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3BATTVOLTDIAG_STOP_SEC_CODE)
    #undef d_L3BATTVOLTDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3SENSORVOLTDIAG_STOP_SEC_CODE)
    #undef d_L3SENSORVOLTDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3TORQUESENSORDIAG_STOP_SEC_CODE)
    #undef d_L3TORQUESENSORDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3STRANGLESENSORDIAG_STOP_SEC_CODE)
    #undef d_L3STRANGLESENSORDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3ENGINESTATUSDIAG_STOP_SEC_CODE)
    #undef d_L3ENGINESTATUSDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3VEHICLESPEEDDIAG_STOP_SEC_CODE)
    #undef d_L3VEHICLESPEEDDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3PRECHARGEDIAG_STOP_SEC_CODE)
    #undef d_L3PRECHARGEDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3POWRELAYDIAG_STOP_SEC_CODE)
    #undef d_L3POWRELAYDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3PREDRIVERDIAG_STOP_SEC_CODE)
    #undef d_L3PREDRIVERDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3HBRIDGEDIAG_STOP_SEC_CODE)
    #undef d_L3HBRIDGEDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3TEMPERATUREDIAG_STOP_SEC_CODE)
    #undef d_L3TEMPERATUREDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3TEMPDIAGMT_STOP_SEC_CODE)
    #undef d_L3TEMPDIAGMT_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3MOTORCURRDIAG_STOP_SEC_CODE)
    #undef d_L3MOTORCURRDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3CURRDIAGMT_STOP_SEC_CODE)
    #undef d_L3CURRDIAGMT_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3MOTORVOLTDIAG_STOP_SEC_CODE)
    #undef d_L3MOTORVOLTDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3PHASEDIAGMT_STOP_SEC_CODE)
    #undef d_L3PHASEDIAGMT_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3MOTORPOSDIAG_STOP_SEC_CODE)
    #undef d_L3MOTORPOSDIAG_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3HALLDIAGMT_STOP_SEC_CODE)
    #undef d_L3HALLDIAGMT_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE


#elif defined(d_L3HANDWHEELSIGNAL_STOP_SEC_CODE)
    #undef d_L3HANDWHEELSIGNAL_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_BIPST_STOP_SEC_CODE)
    #undef d_BIPST_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3MOTORSIGNAL_STOP_SEC_CODE)
    #undef d_L3MOTORSIGNAL_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3EEPROM_STOP_SEC_CODE)
    #undef d_L3EEPROM_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3POWERCIRCUITSIGNAL_STOP_SEC_CODE)
    #undef d_L3POWERCIRCUITSIGNAL_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3PREDRIVERSIGNAL_STOP_SEC_CODE)
    #undef d_L3PREDRIVERSIGNAL_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3MONITOR_STOP_SEC_CODE)
    #undef d_L3MONITOR_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3CAN_STOP_SEC_CODE)
    #undef d_L3CAN_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L3EEP_STOP_SEC_CODE)
    #undef d_L3EEP_STOP_SEC_CODE
    #define d_L3_ECAL_STOP_SEC_CODE

#elif defined(d_L4ECUSTATEMANAGEMENT_STOP_SEC_CODE)
    #undef d_L4ECUSTATEMANAGEMENT_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4FAULTMANAGER_STOP_SEC_CODE)
    #undef d_L4FAULTMANAGER_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4EEPROMMANAGEMENT_STOP_SEC_CODE)
    #undef d_L4EEPROMMANAGEMENT_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4NVMAPPDATA_STOP_SEC_CODE)
    #undef d_L4NVMAPPDATA_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4SCHEDULEMANAGEMENT_STOP_SEC_CODE)
    #undef d_L4SCHEDULEMANAGEMENT_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4MAIN_STOP_SEC_CODE)
    #undef d_L4MAIN_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4SRVL_STOP_SEC_CODE)
    #undef d_L4SRVL_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4MONITORSRV_STOP_SEC_CODE)
    #undef d_L4MONITORSRV_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4TP_STOP_SEC_CODE)
    #undef d_L4TP_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4UDS_STOP_SEC_CODE)
    #undef d_L4UDS_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4DTC_STOP_SEC_CODE)
    #undef d_L4DTC_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4CCP_STOP_SEC_CODE)
    #undef d_L4CCP_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L4SYSTEMTEST_STOP_SEC_CODE)
    #undef d_L4SYSTEMTEST_STOP_SEC_CODE
    #define d_L4_SRVL_STOP_SEC_CODE

#elif defined(d_L5APPL_STOP_SEC_CODE)
    #undef d_L5APPL_STOP_SEC_CODE
    #define d_L5_APPL_STOP_SEC_CODE

#elif defined(d_L5APPLFAILSAFE_STOP_SEC_CODE)
    #undef d_L5APPLFAILSAFE_STOP_SEC_CODE
    #define d_L5_APPL_STOP_SEC_CODE

#elif defined(d_L5MOTORCTRL_STOP_SEC_CODE)
    #undef d_L5MOTORCTRL_STOP_SEC_CODE
    #define d_L5_APPL_STOP_SEC_CODE

#elif defined(d_L5POWERSTEERINGCTRL_STOP_SEC_CODE)
    #undef d_L5POWERSTEERINGCTRL_STOP_SEC_CODE
    #define d_L5_APPL_STOP_SEC_CODE

#else
    /* Nothing is defined */

#endif

/*********************************************************
 *           单个模块的FastCode区域分配
 *********************************************************/
/* 单个模块的START_SEC_FAST_CODE */
#if defined(d_L2GPT_START_SEC_FAST_CODE)
    #undef d_L2GPT_START_SEC_FAST_CODE
    #define d_L2_MCAL_START_SEC_FAST_CODE

#elif defined(d_L2IRQ_START_SEC_FAST_CODE)
    #undef d_L2IRQ_START_SEC_FAST_CODE
    #define d_L2_MCAL_START_SEC_FAST_CODE

#elif defined(d_L2CCU6_START_SEC_FAST_CODE)
    #undef d_L2CCU6_START_SEC_FAST_CODE
    #define d_L2_MCAL_START_SEC_FAST_CODE

#elif defined(d_L2MPU_START_SEC_FAST_CODE)
    #undef d_L2MPU_START_SEC_FAST_CODE
    #define d_L2_MCAL_START_SEC_FAST_CODE

#elif defined(d_L3ECAL_START_SEC_FAST_CODE)
    #undef d_L3ECAL_START_SEC_FAST_CODE
    #define d_L3_ECAL_START_SEC_FAST_CODE

#elif defined(d_L3HANDWHEELSIGNAL_START_SEC_FAST_CODE)
    #undef d_L3HANDWHEELSIGNAL_START_SEC_FAST_CODE
    #define d_L3_ECAL_START_SEC_FAST_CODE

#elif defined(d_L3MOTORSIGNAL_START_SEC_FAST_CODE)
    #undef d_L3MOTORSIGNAL_START_SEC_FAST_CODE
    #define d_L3_ECAL_START_SEC_FAST_CODE

#elif defined(d_L3PREDRIVERSIGNAL_START_SEC_FAST_CODE)
    #undef d_L3PREDRIVERSIGNAL_START_SEC_FAST_CODE
    #define d_L3_ECAL_START_SEC_FAST_CODE



#elif defined(d_L4SCHEDULEMANAGEMENT_START_SEC_FAST_CODE)
    #undef d_L4SCHEDULEMANAGEMENT_START_SEC_FAST_CODE
    #define d_L4_SRVL_START_SEC_FAST_CODE

#elif defined(d_L4SRVL_START_SEC_FAST_CODE)
    #undef d_L4SRVL_START_SEC_FAST_CODE
    #define d_L4_SRVL_START_SEC_FAST_CODE

#elif defined(d_L5APPL_START_SEC_FAST_CODE)
    #undef d_L5APPL_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_APPSCL5ASSISTANCE_START_SEC_FAST_CODE)
    #undef d_APPSCL5ASSISTANCE_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_APPSCL5CALCASSTQLIMIT_START_SEC_FAST_CODE)
    #undef d_APPSCL5CALCASSTQLIMIT_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_APPSCL5DAMPINGCTRL_START_SEC_FAST_CODE)
    #undef d_APPSCL5DAMPINGCTRL_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_APPSCL5RETURNCTRL_START_SEC_FAST_CODE)
    #undef d_APPSCL5RETURNCTRL_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_APPSCL5THERMMANAGE_START_SEC_FAST_CODE)
    #undef d_APPSCL5THERMMANAGE_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_STEERINGCONTROL_START_SEC_FAST_CODE)
    #undef d_STEERINGCONTROL_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_MOTORCONTROL_START_SEC_FAST_CODE)
    #undef d_MOTORCONTROL_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_L5MOTORCTRL_START_SEC_FAST_CODE)
    #undef d_L5MOTORCTRL_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#elif defined(d_L5POWERSTEERINGCTRL_START_SEC_FAST_CODE)
    #undef d_L5POWERSTEERINGCTRL_START_SEC_FAST_CODE
    #define d_L5_APPL_START_SEC_FAST_CODE

#else
    /* Nothing is defined */

#endif


/* 单个模块的STOP_SEC_FAST_CODE */
#if defined(d_L2GPT_STOP_SEC_FAST_CODE)
    #undef d_L2GPT_STOP_SEC_FAST_CODE
    #define d_L2_MCAL_STOP_SEC_FAST_CODE

#elif defined(d_L2IRQ_STOP_SEC_FAST_CODE)
    #undef d_L2IRQ_STOP_SEC_FAST_CODE
    #define d_L2_MCAL_STOP_SEC_FAST_CODE

#elif defined(d_L2CCU6_STOP_SEC_FAST_CODE)
    #undef d_L2CCU6_STOP_SEC_FAST_CODE
    #define d_L2_MCAL_STOP_SEC_FAST_CODE

#elif defined(d_L2MPU_STOP_SEC_FAST_CODE)
    #undef d_L2MPU_STOP_SEC_FAST_CODE
    #define d_L2_MCAL_STOP_SEC_FAST_CODE

#elif defined(d_L3ECAL_STOP_SEC_FAST_CODE)
    #undef d_L3ECAL_STOP_SEC_FAST_CODE
    #define d_L3_ECAL_STOP_SEC_FAST_CODE

#elif defined(d_L3HANDWHEELSIGNAL_STOP_SEC_FAST_CODE)
    #undef d_L3HANDWHEELSIGNAL_STOP_SEC_FAST_CODE
    #define d_L3_ECAL_STOP_SEC_FAST_CODE

#elif defined(d_L3MOTORSIGNAL_STOP_SEC_FAST_CODE)
    #undef d_L3MOTORSIGNAL_STOP_SEC_FAST_CODE
    #define d_L3_ECAL_STOP_SEC_FAST_CODE

#elif defined(d_L3PREDRIVERSIGNAL_STOP_SEC_FAST_CODE)
    #undef d_L3PREDRIVERSIGNAL_STOP_SEC_FAST_CODE
    #define d_L3_ECAL_STOP_SEC_FAST_CODE


#elif defined(d_L4SCHEDULEMANAGEMENT_STOP_SEC_FAST_CODE)
    #undef d_L4SCHEDULEMANAGEMENT_STOP_SEC_FAST_CODE
    #define d_L4_SRVL_STOP_SEC_FAST_CODE

#elif defined(d_L4SRVL_STOP_SEC_FAST_CODE)
    #undef d_L4SRVL_STOP_SEC_FAST_CODE
    #define d_L4_SRVL_STOP_SEC_FAST_CODE

#elif defined(d_L5APPL_STOP_SEC_CFAST_ODE)
    #undef d_L5APPL_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_APPSCL5ASSISTANCE_STOP_SEC_FAST_CODE)
    #undef d_APPSCL5ASSISTANCE_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_APPSCL5CALCASSTQLIMIT_STOP_SEC_FAST_CODE)
    #undef d_APPSCL5CALCASSTQLIMIT_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_APPSCL5DAMPINGCTRL_STOP_SEC_FAST_CODE)
    #undef d_APPSCL5DAMPINGCTRL_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_APPSCL5RETURNCTRL_STOP_SEC_FAST_CODE)
    #undef d_APPSCL5RETURNCTRL_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_APPSCL5THERMMANAGE_STOP_SEC_FAST_CODE)
    #undef d_APPSCL5THERMMANAGE_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_STEERINGCONTROL_STOP_SEC_FAST_CODE)
    #undef d_STEERINGCONTROL_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_MOTORCONTROL_STOP_SEC_FAST_CODE)
    #undef d_MOTORCONTROL_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_L5MOTORCTRL_STOP_SEC_FAST_CODE)
    #undef d_L5MOTORCTRL_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#elif defined(d_L5POWERSTEERINGCTRL_STOP_SEC_FAST_CODE)
    #undef d_L5POWERSTEERINGCTRL_STOP_SEC_FAST_CODE
    #define d_L5_APPL_STOP_SEC_FAST_CODE

#else
    /* Nothing is defined */

#endif

/*********************************************************
 *           单个模块的Variable区域分配
 *********************************************************/
/* 单个模块的START_SEC_VAR */
#if defined(d_L2MCUDIAGNOSIS_START_SEC_VAR)
    #undef d_L2MCUDIAGNOSIS_START_SEC_VAR
    #define d_L2_MCAL_START_SEC_VAR
    
#elif defined(d_L2CAN_START_SEC_VAR)
    #undef d_L2CAN_START_SEC_VAR
    #define d_L2_MCAL_START_SEC_VAR
    
#elif defined(d_L2FLASH_START_SEC_VAR)
    #undef d_L2FLASH_START_SEC_VAR
    #define d_L2_MCAL_START_SEC_VAR

#elif defined(d_L3ECAL_START_SEC_VAR)
    #undef d_L3ECAL_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3ECUDIAGNOSIS_START_SEC_VAR)
    #undef d_L3ECUDIAGNOSIS_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3ECUDIAG_START_SEC_VAR)
    #undef d_L3ECUDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3BATTVOLTDIAG_START_SEC_VAR)
    #undef d_L3BATTVOLTDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3SENSORVOLTDIAG_START_SEC_VAR)
    #undef d_L3SENSORVOLTDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3TORQUESENSORDIAG_START_SEC_VAR)
    #undef d_L3TORQUESENSORDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3STRANGLESENSORDIAG_START_SEC_VAR)
    #undef d_L3STRANGLESENSORDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3ENGINESTATUSDIAG_START_SEC_VAR)
    #undef d_L3ENGINESTATUSDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3VEHICLESPEEDDIAG_START_SEC_VAR)
    #undef d_L3VEHICLESPEEDDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3PRECHARGEDIAG_START_SEC_VAR)
    #undef d_L3PRECHARGEDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3POWRELAYDIAG_START_SEC_VAR)
    #undef d_L3POWRELAYDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3PREDRIVERDIAG_START_SEC_VAR)
    #undef d_L3PREDRIVERDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3HBRIDGEDIAG_START_SEC_VAR)
    #undef d_L3HBRIDGEDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3TEMPERATUREDIAG_START_SEC_VAR)
    #undef d_L3TEMPERATUREDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3TEMPDIAGMT_START_SEC_VAR)
    #undef d_L3TEMPDIAGMT_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3MOTORCURRDIAG_START_SEC_VAR)
    #undef d_L3MOTORCURRDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3CURRDIAGMT_START_SEC_VAR)
    #undef d_L3CURRDIAGMT_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3MOTORVOLTDIAG_START_SEC_VAR)
    #undef d_L3MOTORVOLTDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3PHASEDIAGMT_START_SEC_VAR)
    #undef d_L3PHASEDIAGMT_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3MOTORPOSDIAG_START_SEC_VAR)
    #undef d_L3MOTORPOSDIAG_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3HALLDIAGMT_START_SEC_VAR)
    #undef d_L3HALLDIAGMT_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR


#elif defined(d_L3HANDWHEELSIGNAL_START_SEC_VAR)
    #undef d_L3HANDWHEELSIGNAL_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_BIPST_START_SEC_VAR)
    #undef d_BIPST_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3MOTORSIGNAL_START_SEC_VAR)
    #undef d_L3MOTORSIGNAL_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3PREDRIVERSIGNAL_START_SEC_VAR)
    #undef d_L3PREDRIVERSIGNAL_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3POWERCIRCUITSIGNAL_START_SEC_VAR)
    #undef d_L3POWERCIRCUITSIGNAL_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3CAN_START_SEC_VAR)
    #undef d_L3CAN_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L3EEP_START_SEC_VAR)
    #undef d_L3EEP_START_SEC_VAR
    #define d_L3_ECAL_START_SEC_VAR

#elif defined(d_L4ECUSTATEMANAGEMENT_START_SEC_VAR)
    #undef d_L4ECUSTATEMANAGEMENT_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4FAULTMANAGER_START_SEC_VAR)
    #undef d_L4FAULTMANAGER_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4EEPROMMANAGEMENT_START_SEC_VAR)
    #undef d_L4EEPROMMANAGEMENT_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4NVMAPPDATA_START_SEC_VAR)
    #undef d_L4NVMAPPDATA_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4SCHEDULEMANAGEMENT_START_SEC_VAR)
    #undef d_L4SCHEDULEMANAGEMENT_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4SRVL_START_SEC_VAR)
    #undef d_L4SRVL_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4TP_START_SEC_VAR)
    #undef d_L4TP_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4UDS_START_SEC_VAR)
    #undef d_L4UDS_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4DTC_START_SEC_VAR)
    #undef d_L4DTC_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR
    
#elif defined(d_L4CCP_START_SEC_VAR)
    #undef d_L4CCP_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4SYSTEMTEST_START_SEC_VAR)
    #undef d_L4SYSTEMTEST_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L4MONITORSRV_START_SEC_VAR)
    #undef d_L4MONITORSRV_START_SEC_VAR
    #define d_L4_SRVL_START_SEC_VAR

#elif defined(d_L5APPL_START_SEC_VAR)
    #undef d_L5APPL_START_SEC_VAR
    #define d_L5_APPL_START_SEC_VAR

#elif defined(d_L5APPLFAILSAFE_START_SEC_VAR)
    #undef d_L5APPLFAILSAFE_START_SEC_VAR
    #define d_L5_APPL_START_SEC_VAR

#elif defined(d_STEERINGCONTROLDATA_START_SEC_VAR)
    #undef d_STEERINGCONTROLDATA_START_SEC_VAR
    #define d_L5_APPL_START_SEC_VAR

#elif defined(d_STEERINGCONTROL_START_SEC_VAR)
    #undef d_STEERINGCONTROL_START_SEC_VAR
    #define d_L5_APPL_START_SEC_VAR

#elif defined(d_MOTORCONTROL_START_SEC_VAR)
    #undef d_MOTORCONTROL_START_SEC_VAR
    #define d_L5_APPL_START_SEC_VAR

#elif defined(d_L5POWERSTEERINGCTRL_START_SEC_VAR)
    #undef d_L5POWERSTEERINGCTRL_START_SEC_VAR
    #define d_L5_APPL_START_SEC_VAR

#elif defined(d_L5MOTORCTRL_START_SEC_VAR)
    #undef d_L5MOTORCTRL_START_SEC_VAR
    #define d_L5_APPL_START_SEC_VAR

#else
    /* Nothing is defined */

#endif


/* 单个模块的STOP_SEC_VAR */
#if defined(d_L2MCUDIAGNOSIS_STOP_SEC_VAR)
    #undef d_L2MCUDIAGNOSIS_STOP_SEC_VAR
    #define d_L2_MCAL_STOP_SEC_VAR

#elif defined(d_L2CAN_STOP_SEC_VAR)
    #undef d_L2CAN_STOP_SEC_VAR
    #define d_L2_MCAL_STOP_SEC_VAR

#elif defined(d_L2FLASH_STOP_SEC_VAR)
    #undef d_L2FLASH_STOP_SEC_VAR
    #define d_L2_MCAL_STOP_SEC_VAR

#elif defined(d_L3ECAL_STOP_SEC_VAR)
    #undef d_L3ECAL_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3ECUDIAGNOSIS_STOP_SEC_VAR)
    #undef d_L3ECUDIAGNOSIS_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3ECUDIAG_STOP_SEC_VAR)
    #undef d_L3ECUDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3BATTVOLTDIAG_STOP_SEC_VAR)
    #undef d_L3BATTVOLTDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3SENSORVOLTDIAG_STOP_SEC_VAR)
    #undef d_L3SENSORVOLTDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3TORQUESENSORDIAG_STOP_SEC_VAR)
    #undef d_L3TORQUESENSORDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3STRANGLESENSORDIAG_STOP_SEC_VAR)
    #undef d_L3STRANGLESENSORDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3ENGINESTATUSDIAG_STOP_SEC_VAR)
    #undef d_L3ENGINESTATUSDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3VEHICLESPEEDDIAG_STOP_SEC_VAR)
    #undef d_L3VEHICLESPEEDDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3PRECHARGEDIAG_STOP_SEC_VAR)
    #undef d_L3PRECHARGEDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3POWRELAYDIAG_STOP_SEC_VAR)
    #undef d_L3POWRELAYDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3PREDRIVERDIAG_STOP_SEC_VAR)
    #undef d_L3PREDRIVERDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3HBRIDGEDIAG_STOP_SEC_VAR)
    #undef d_L3HBRIDGEDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3TEMPERATUREDIAG_STOP_SEC_VAR)
    #undef d_L3TEMPERATUREDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3TEMPDIAGMT_STOP_SEC_VAR)
    #undef d_L3TEMPDIAGMT_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3MOTORCURRDIAG_STOP_SEC_VAR)
    #undef d_L3MOTORCURRDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3CURRDIAGMT_STOP_SEC_VAR)
    #undef d_L3CURRDIAGMT_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3MOTORVOLTDIAG_STOP_SEC_VAR)
    #undef d_L3MOTORVOLTDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3PHASEDIAGMT_STOP_SEC_VAR)
    #undef d_L3PHASEDIAGMT_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3MOTORPOSDIAG_STOP_SEC_VAR)
    #undef d_L3MOTORPOSDIAG_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3HALLDIAGMT_STOP_SEC_VAR)
    #undef d_L3HALLDIAGMT_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR


#elif defined(d_L3HANDWHEELSIGNAL_STOP_SEC_VAR)
    #undef d_L3HANDWHEELSIGNAL_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_BIPST_STOP_SEC_VAR)
    #undef d_BIPST_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3MOTORSIGNAL_STOP_SEC_VAR)
    #undef d_L3MOTORSIGNAL_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3PREDRIVERSIGNAL_STOP_SEC_VAR)
    #undef d_L3PREDRIVERSIGNAL_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3POWERCIRCUITSIGNAL_STOP_SEC_VAR)
    #undef d_L3POWERCIRCUITSIGNAL_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3CAN_STOP_SEC_VAR)
    #undef d_L3CAN_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L3EEP_STOP_SEC_VAR)
    #undef d_L3EEP_STOP_SEC_VAR
    #define d_L3_ECAL_STOP_SEC_VAR

#elif defined(d_L4ECUSTATEMANAGEMENT_STOP_SEC_VAR)
    #undef d_L4ECUSTATEMANAGEMENT_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4FAULTMANAGER_STOP_SEC_VAR)
    #undef d_L4FAULTMANAGER_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4EEPROMMANAGEMENT_STOP_SEC_VAR)
    #undef d_L4EEPROMMANAGEMENT_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4NVMAPPDATA_STOP_SEC_VAR)
    #undef d_L4NVMAPPDATA_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4SCHEDULEMANAGEMENT_STOP_SEC_VAR)
    #undef d_L4SCHEDULEMANAGEMENT_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4SRVL_STOP_SEC_VAR)
    #undef d_L4SRVL_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4TP_STOP_SEC_VAR)
    #undef d_L4TP_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4UDS_STOP_SEC_VAR)
    #undef d_L4UDS_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4DTC_STOP_SEC_VAR)
    #undef d_L4DTC_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4CCP_STOP_SEC_VAR)
    #undef d_L4CCP_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4SYSTEMTEST_STOP_SEC_VAR)
    #undef d_L4SYSTEMTEST_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L4MONITORSRV_STOP_SEC_VAR)
    #undef d_L4MONITORSRV_STOP_SEC_VAR
    #define d_L4_SRVL_STOP_SEC_VAR

#elif defined(d_L5APPL_STOP_SEC_VAR)
    #undef d_L5APPL_STOP_SEC_VAR
    #define d_L5_APPL_STOP_SEC_VAR

#elif defined(d_L5APPLFAILSAFE_STOP_SEC_VAR)
    #undef d_L5APPLFAILSAFE_STOP_SEC_VAR
    #define d_L5_APPL_STOP_SEC_VAR

#elif defined(d_STEERINGCONTROLDATA_STOP_SEC_VAR)
    #undef d_STEERINGCONTROLDATA_STOP_SEC_VAR
    #define d_L5_APPL_STOP_SEC_VAR

#elif defined(d_STEERINGCONTROL_STOP_SEC_VAR)
    #undef d_STEERINGCONTROL_STOP_SEC_VAR
    #define d_L5_APPL_STOP_SEC_VAR

#elif defined(d_MOTORCONTROL_STOP_SEC_VAR)
    #undef d_MOTORCONTROL_STOP_SEC_VAR
    #define d_L5_APPL_STOP_SEC_VAR

#elif defined(d_L5POWERSTEERINGCTRL_STOP_SEC_VAR)
    #undef d_L5POWERSTEERINGCTRL_STOP_SEC_VAR
    #define d_L5_APPL_STOP_SEC_VAR

#elif defined(d_L5MOTORCTRL_STOP_SEC_VAR)
    #undef d_L5MOTORCTRL_STOP_SEC_VAR
    #define d_L5_APPL_STOP_SEC_VAR

#else
    /* Nothing is defined */

#endif

/*********************************************************
 *           单个模块的Calibration Variable区域分配
 *********************************************************/
/* 单个模块的START_SEC_CALIB_VAR */
#if defined(d_BIPST_START_SEC_CALIB_VAR)
    #undef d_BIPST_START_SEC_CALIB_VAR
    #define d_L3_ECAL_START_SEC_CALIB_VAR

#elif defined(d_L3TEMPDIAGMTCALIBDATA_START_SEC_CALIB_VAR)
    #undef d_L3TEMPDIAGMTCALIBDATA_START_SEC_CALIB_VAR
    #define d_L3_ECAL_START_SEC_CALIB_VAR

#elif defined(d_L3CURRDIAGMTCALIBDATA_START_SEC_CALIB_VAR)
    #undef d_L3CURRDIAGMTCALIBDATA_START_SEC_CALIB_VAR
    #define d_L3_ECAL_START_SEC_CALIB_VAR

#elif defined(d_L3PHASEDIAGMTCALIBDATA_START_SEC_CALIB_VAR)
    #undef d_L3PHASEDIAGMTCALIBDATA_START_SEC_CALIB_VAR
    #define d_L3_ECAL_START_SEC_CALIB_VAR

#elif defined(d_L3HALLDIAGMTCALIBDATA_START_SEC_CALIB_VAR)
    #undef d_L3HALLDIAGMTCALIBDATA_START_SEC_CALIB_VAR
    #define d_L3_ECAL_START_SEC_CALIB_VAR


#elif defined(d_L3ECUSIGNALCALIBDATA_START_SEC_CALIB_VAR)
    #undef d_L3ECUSIGNALCALIBDATA_START_SEC_CALIB_VAR
    #define d_L3_ECAL_START_SEC_CALIB_VAR

#elif defined(d_L3ECALFAILSAFECALDATA_START_SEC_CALIB_VAR)
    #undef d_L3ECALFAILSAFECALDATA_START_SEC_CALIB_VAR
    #define d_L3_ECAL_START_SEC_CALIB_VAR

#elif defined(d_L4SRVLFAILSAFECALDATA_START_SEC_CALIB_VAR)
    #undef d_L4SRVLFAILSAFECALDATA_START_SEC_CALIB_VAR
    #define d_L4_SRVL_START_SEC_CALIB_VAR

#elif defined(d_L5APPLFAILSAFECALDATA_START_SEC_CALIB_VAR)
    #undef d_L5APPLFAILSAFECALDATA_START_SEC_CALIB_VAR
    #define d_L5_APPL_START_SEC_CALIB_VAR

#elif defined(d_STEERINGCONTROLDATA_START_SEC_CALIB_VAR)
    #undef d_STEERINGCONTROLDATA_START_SEC_CALIB_VAR
    #define d_L5_APPL_START_SEC_CALIB_VAR

#elif defined(d_MOTORCONTROLGLOBAL_START_SEC_CALIB_VAR)
    #undef d_MOTORCONTROLGLOBAL_START_SEC_CALIB_VAR
    #define d_L5_APPL_START_SEC_CALIB_VAR

#elif defined(d_L5POWERSTEERINGCTRLCALIBDATA_START_SEC_CALIB_VAR)
    #undef d_L5POWERSTEERINGCTRLCALIBDATA_START_SEC_CALIB_VAR
    #define d_L5_APPL_START_SEC_CALIB_VAR

#else
    /* Nothing is defined */

#endif

/* 单个模块的STOP_SEC_CALIB_VAR */
#if defined(d_BIPST_STOP_SEC_CALIB_VAR)
    #undef d_BIPST_STOP_SEC_CALIB_VAR
    #define d_L3_ECAL_STOP_SEC_CALIB_VAR

#elif defined(d_L3TEMPDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR)
    #undef d_L3TEMPDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR
    #define d_L3_ECAL_STOP_SEC_CALIB_VAR

#elif defined(d_L3CURRDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR)
    #undef d_L3CURRDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR
    #define d_L3_ECAL_STOP_SEC_CALIB_VAR

#elif defined(d_L3PHASEDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR)
    #undef d_L3PHASEDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR
    #define d_L3_ECAL_STOP_SEC_CALIB_VAR

#elif defined(d_L3HALLDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR)
    #undef d_L3HALLDIAGMTCALIBDATA_STOP_SEC_CALIB_VAR
    #define d_L3_ECAL_STOP_SEC_CALIB_VAR


#elif defined(d_L3ECUSIGNALCALIBDATA_STOP_SEC_CALIB_VAR)
    #undef d_L3ECUSIGNALCALIBDATA_STOP_SEC_CALIB_VAR
    #define d_L3_ECAL_STOP_SEC_CALIB_VAR

#elif defined(d_L3ECALFAILSAFECALDATA_STOP_SEC_CALIB_VAR)
    #undef d_L3ECALFAILSAFECALDATA_STOP_SEC_CALIB_VAR
    #define d_L3_ECAL_STOP_SEC_CALIB_VAR

#elif defined(d_L4SRVLFAILSAFECALDATA_STOP_SEC_CALIB_VAR)
    #undef d_L4SRVLFAILSAFECALDATA_STOP_SEC_CALIB_VAR
    #define d_L3_SRVL_STOP_SEC_CALIB_VAR

#elif defined(d_L5APPLFAILSAFECALDATA_STOP_SEC_CALIB_VAR)
    #undef d_L5APPLFAILSAFECALDATA_STOP_SEC_CALIB_VAR
    #define d_L5_APPL_STOP_SEC_CALIB_VAR

#elif defined(d_STEERINGCONTROLDATA_STOP_SEC_CALIB_VAR)
    #undef d_STEERINGCONTROLDATA_STOP_SEC_CALIB_VAR
    #define d_L5_APPL_STOP_SEC_CALIB_VAR

#elif defined(d_MOTORCONTROLGLOBAL_STOP_SEC_CALIB_VAR)
    #undef d_MOTORCONTROLGLOBAL_STOP_SEC_CALIB_VAR
    #define d_L5_APPL_STOP_SEC_CALIB_VAR

#elif defined(d_L5POWERSTEERINGCTRLCALIBDATA_STOP_SEC_CALIB_VAR)
    #undef d_L5POWERSTEERINGCTRLCALIBDATA_STOP_SEC_CALIB_VAR
    #define d_L5_APPL_STOP_SEC_CALIB_VAR

#else
    /* Nothing is defined */

#endif

/*********************************************************
 *           单个模块的安全变量区域分配
 *********************************************************/
/* 单个模块的START_SEC_SAFETYREDUNDANT_VAR */
#if defined(d_UDS_START_SEC_SAFETYREDUNDANT_VAR)
    #undef d_UDS_START_SEC_SAFETYREDUNDANT_VAR
    #define d_START_SEC_SAFETYREDUNDANT_VAR
#else
    /* Nothing is defined */
#endif



/* 单个模块的STOP_SEC_SAFETYREDUNDANT_VAR */
#if defined(d_UDS_STOP_SEC_SAFETYREDUNDANT_VAR)
    #undef d_UDS_STOP_SEC_SAFETYREDUNDANT_VAR
    #define d_STOP_SEC_SAFETYREDUNDANT_VAR
#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           单个模块的Constants区域分配
 *********************************************************/
/* 单个模块的START_SEC_CONST */
#if defined(d_L2MPUDATA_START_SEC_CONST)
    #undef d_L2MPUDATA_START_SEC_CONST
    #define d_START_SEC_CONST
  
#elif defined(d_L2CAN_START_SEC_CONST)
    #undef d_L2CAN_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_L3MOTORSIGNALDATA_START_SEC_CONST)
    #undef d_L3MOTORSIGNALDATA_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_L3POWERCIRCUITDATA_START_SEC_CONST)
    #undef d_L3POWERCIRCUITDATA_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_L3EEP_START_SEC_CONST)
    #undef d_L3EEP_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_L4TP_START_SEC_CONST)
    #undef d_L4TP_START_SEC_CONST
    #define d_START_SEC_CONST
    
#elif defined(d_L4DTC_START_SEC_CONST)
    #undef d_L4DTC_START_SEC_CONST
    #define d_START_SEC_CONST
    
#elif defined(d_L4CCP_START_SEC_CONST)
    #undef d_L4CCP_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_L4MAIN_START_SEC_CONST)
    #undef d_L4MAIN_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_L4SRVL_START_SEC_CONST)
    #undef d_L4SRVL_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_L5APPL_START_SEC_CONST)
    #undef d_L5APPL_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_STEERINGCONTROLDATA_START_SEC_CONST)
    #undef d_STEERINGCONTROLDATA_START_SEC_CONST
    #define d_START_SEC_CONST

#elif defined(d_MOTORCONTROL_START_SEC_CONST)
    #undef d_MOTORCONTROL_START_SEC_CONST
    #define d_START_SEC_CONST
    
#elif defined(d_BIPSTDATA_START_SEC_CONST)
    #undef d_BIPSTDATA_START_SEC_CONST
    #define d_START_SEC_CONST

#else
    /* Nothing is defined */

#endif

/* 单个模块的STOP_SEC_CONST */
#if defined(d_L2MPUDATA_STOP_SEC_CONST)
    #undef d_L2MPUDATA_STOP_SEC_CONST
    #define d_STOP_SEC_CONST
    
#elif defined(d_L2CAN_STOP_SEC_CONST)
    #undef d_L2CAN_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L3MOTORSIGNALDATA_STOP_SEC_CONST)
    #undef d_L3MOTORSIGNALDATA_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L3POWERCIRCUITDATA_STOP_SEC_CONST)
    #undef d_L3POWERCIRCUITDATA_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L3EEP_STOP_SEC_CONST)
    #undef d_L3EEP_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L4TP_STOP_SEC_CONST)
    #undef d_L4TP_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L4DTC_STOP_SEC_CONST)
    #undef d_L4DTC_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L4CCP_STOP_SEC_CONST)
    #undef d_L4CCP_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L4MAIN_STOP_SEC_CONST)
    #undef d_L4MAIN_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L4SRVL_STOP_SEC_CONST)
    #undef d_L4SRVL_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_L5APPL_STOP_SEC_CONST)
    #undef d_L5APPL_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_STEERINGCONTROLDATA_STOP_SEC_CONST)
    #undef d_STEERINGCONTROLDATA_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_MOTORCONTROL_STOP_SEC_CONST)
    #undef d_MOTORCONTROL_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#elif defined(d_BIPSTDATA_STOP_SEC_CONST)
    #undef d_BIPSTDATA_STOP_SEC_CONST
    #define d_STOP_SEC_CONST

#else
    /* Nothing is defined */

#endif

/*********************************************************
 *           各层的Code区域分配
 *********************************************************/
/* 各层的START_SEC_CODE */
#if defined(d_L5_APPL_START_SEC_CODE)
    #pragma section code = code_L5APPL
    #undef d_L5_APPL_START_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_START_SEC_CODE)
    #pragma section code = code_L4SRVL
    #undef d_L4_SRVL_START_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_START_SEC_CODE)
    #pragma section code = code_L3ECAL
    #undef d_L3_ECAL_START_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_START_SEC_CODE)
    #pragma section code = code_L2MCAL
    #undef d_L2_MCAL_START_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_START_SEC_CODE)
    #pragma section code = code_LIB
    #undef d_LIB_START_SEC_CODE
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/* 各层的STOP_SEC_CODE */
#if defined(d_L5_APPL_STOP_SEC_CODE)
    #pragma section code = code_Default
    #undef d_L5_APPL_STOP_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_STOP_SEC_CODE)
    #pragma section code = code_Default
    #undef d_L4_SRVL_STOP_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_STOP_SEC_CODE)
    #pragma section code = code_Default
    #undef d_L3_ECAL_STOP_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_STOP_SEC_CODE)
    #pragma section code = code_Default
    #undef d_L2_MCAL_STOP_SEC_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_STOP_SEC_CODE)
    #pragma section code = code_Default
    #undef d_LIB_STOP_SEC_CODE
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           各层的FastCode区域分配
 *********************************************************/
/* 各层的START_SEC_FAST_CODE */
#if defined(d_L5_APPL_START_SEC_FAST_CODE)
    #pragma section code = code_psram_L5APPL
    #undef d_L5_APPL_START_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_START_SEC_FAST_CODE)
    #pragma section code = code_psram_L4SRVL
    #undef d_L4_SRVL_START_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_START_SEC_FAST_CODE)
    #pragma section code = code_psram_L3ECAL
    #undef d_L3_ECAL_START_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_START_SEC_FAST_CODE)
    #pragma section code = code_psram_L2MCAL
    #undef d_L2_MCAL_START_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_START_SEC_FAST_CODE)
    #pragma section code = code_psram_LIB
    #undef d_LIB_START_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/* 各层的STOP_SEC_FAST_CODE */
#if defined(d_L5_APPL_STOP_SEC_FAST_CODE)
    #pragma endsection
    #undef d_L5_APPL_STOP_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_STOP_SEC_FAST_CODE)
    #pragma endsection
    #undef d_L4_SRVL_STOP_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_STOP_SEC_FAST_CODE)
    #pragma endsection
    #undef d_L3_ECAL_STOP_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_STOP_SEC_FAST_CODE)
    #pragma endsection
    #undef d_L2_MCAL_STOP_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_STOP_SEC_FAST_CODE)
    #pragma endsection
    #undef d_LIB_STOP_SEC_FAST_CODE
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           各层的Variable区域分配
 *********************************************************/
/* 各层的START_SEC_VAR */
#if defined(d_L5_APPL_START_SEC_VAR)
    #pragma section near = data_L5APPL
    #undef d_L5_APPL_START_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_START_SEC_VAR)
    #pragma section near = data_L4SRVL
    #undef d_L4_SRVL_START_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_START_SEC_VAR)
    #pragma section near = data_L3ECAL
    #undef d_L3_ECAL_START_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_START_SEC_VAR)
    #pragma section near = data_L2MCAL
    #undef d_L2_MCAL_START_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_START_SEC_VAR)
    #pragma section near = data_LIB
    #undef d_LIB_START_SEC_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/* 各层的STOP_SEC_VAR */
#if defined(d_L5_APPL_STOP_SEC_VAR)
    #pragma endsection
    #undef d_L5_APPL_STOP_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_STOP_SEC_VAR)
    #pragma endsection
    #undef d_L4_SRVL_STOP_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_STOP_SEC_VAR)
    #pragma endsection
    #undef d_L3_ECAL_STOP_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_STOP_SEC_VAR)
    #pragma endsection
    #undef d_L2_MCAL_STOP_SEC_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_STOP_SEC_VAR)
    #pragma endsection
    #undef d_LIB_STOP_SEC_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           整体的安全备份数据区域分配
 *********************************************************/
/* 整体的START_SEC_SAFETYREDUNDANT_VAR */
#ifdef d_START_SEC_SAFETYREDUNDANT_VAR
    #pragma section near = data_BackupVar
    #undef d_START_SEC_SAFETYREDUNDANT_VAR
    #undef d_MEMMAP_ERROR
#else
    /* Nothing is defined */
#endif

/* 整体的STOP_SEC_SAFETYREDUNDANT_VAR */
#ifdef d_STOP_SEC_SAFETYREDUNDANT_VAR
    #pragma endsection
    #undef d_STOP_SEC_SAFETYREDUNDANT_VAR
    #undef d_MEMMAP_ERROR
#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           各层的Calibration Variable区域分配
 *********************************************************/
/* 各层的START_SEC_CALIB_VAR */
#if defined(d_L5_APPL_START_SEC_CALIB_VAR)
    #pragma section near = data_CalibData_L5APPL
    #undef d_L5_APPL_START_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_START_SEC_CALIB_VAR)
    #pragma section near = data_CalibData_L4SRVL
    #undef d_L4_SRVL_START_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_START_SEC_CALIB_VAR)
    #pragma section near = data_CalibData_L3ECAL
    #undef d_L3_ECAL_START_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_START_SEC_CALIB_VAR)
    #pragma section near = data_CalibData_L2MCAL
    #undef d_L2_MCAL_START_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_START_SEC_CALIB_VAR)
    #pragma section near = data_CalibData_LIB
    #undef d_LIB_START_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/* 各层的STOP_SEC_CALIB_VAR */
#if defined(d_L5_APPL_STOP_SEC_CALIB_VAR)
    #pragma endsection
    #undef d_L5_APPL_STOP_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L4_SRVL_STOP_SEC_CALIB_VAR)
    #pragma endsection
    #undef d_L4_SRVL_STOP_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L3_ECAL_STOP_SEC_CALIB_VAR)
    #pragma endsection
    #undef d_L3_ECAL_STOP_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_L2_MCAL_STOP_SEC_CALIB_VAR)
    #pragma endsection
    #undef d_L2_MCAL_STOP_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#elif defined(d_LIB_STOP_SEC_CALIB_VAR)
    #pragma endsection
    #undef d_LIB_STOP_SEC_CALIB_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           各层的EEPROM RAM Raw Data区域分配
 *********************************************************/
/* 各层的START_SEC_EE_RAW_VAR */
#if defined(d_L4_SRVL_START_SEC_EE_RAW_VAR)
    #pragma section near = data_EERaw_L4SRVL
    #undef d_L4_SRVL_START_SEC_EE_RAW_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/* 各层的STOP_SEC_EE_RAW_VAR */
#if defined(d_L4_SRVL_STOP_SEC_EE_RAW_VAR)
    #pragma endsection
    #undef d_L4_SRVL_STOP_SEC_EE_RAW_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           各层的EEPROM RAM Shadow Data区域分配
 *********************************************************/
/* 各层的START_SEC_EE_SHADOW_VAR */
#if defined(d_L4_SRVL_START_SEC_EE_SHADOW_VAR)
    #pragma section near = data_EEShadow_L4SRVL
    #undef d_L4_SRVL_START_SEC_EE_SHADOW_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/* 各层的STOP_SEC_EE_SHADOW_VAR */
#if defined(d_L4_SRVL_STOP_SEC_EE_SHADOW_VAR)
    #pragma endsection
    #undef d_L4_SRVL_STOP_SEC_EE_SHADOW_VAR
    #undef d_MEMMAP_ERROR

#else
    /* Nothing is defined */
#endif

/*********************************************************
 *           整体的Constants区域分配
 *********************************************************/
/* 整体的START_SEC_CONST */
#ifdef d_START_SEC_CONST
    #pragma section huge = const_NormalConst
    #undef d_START_SEC_CONST
    #undef d_MEMMAP_ERROR
#endif

/* 整体的STOP_SEC_CONST */
#ifdef d_STOP_SEC_CONST
    #pragma endsection
    #undef d_STOP_SEC_CONST
    #undef d_MEMMAP_ERROR
#endif

#ifdef d_MEMMAP_ERROR
    #error "MemMap.h, wrong pragma command"
#endif

#endif

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/

/* End of MemMap.h  File*/
