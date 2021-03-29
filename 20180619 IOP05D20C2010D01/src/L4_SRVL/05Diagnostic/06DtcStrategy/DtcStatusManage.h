/******************************************************************************
*
* Beijing Hualong Tech Inc.
* (c) Copyright 2013 Beijing Hualong Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   DtcStatusManage.h  
*
* @brief  this file is a header file.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/05/10    CODER1     N/A           Original
*     
*******************************************************************************/

#ifndef DTC_STATUS_MANAGE_H
#define DTC_STATUS_MANAGE_H

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "Dcm.h"
#include "Dtc_Cfg.h"
#include "dDiagFaultEvent.h"
#include "m_EEPROM_Drv.h"


#ifdef DTC_STATUS_MANAGE_C
#define DTC_STATUS_MANAGE_EXT
#else
#define DTC_STATUS_MANAGE_EXT            extern
#endif

/*******************************************************************************
*                            General Macros Def
********************************************************************************/
#define EXD_DATA_INITIAL                  0x00000000u /*extend data init value*/
#define FREEZE_DATA_INITIAL               0xFFFFFFFFu /*Freeze data init value*/
#define DTC_RAM_START_ADDR                0x40001C00  /*Start address (RAM) for DTC*/
#define gDtcInfoData                      ((DtcInfoBufType*)DTC_RAM_START_ADDR) /*Global pointer to DTC storage space*/


/*******************************************************************************
*                       Macros for Fault Monitor Logic
********************************************************************************/
#define DTC_TEST_FAILED                     (uint8)1U
#define DTC_TEST_PASSED                     (uint8)0U

#define DTC_CONFIRMED                       (uint8)1U
#define DTC_NOT_CONFIRMED                   (uint8)0U

#define DTC_TEST_FAILED_COUNTER_CLEAR      (sint16)0U
#define DTC_TEST_FAILED_COUNTER_START      (sint16)1U

#define DTC_CONFIRM_COUNTER_CLEAR          (uint16)0U
#define DTC_CONFIRM_COUNTER_START          (uint16)1U

#define DTC_AGING_COUNTER_CLEAR            (uint16)0U
#define DTC_AGING_COUNTER_START            (uint16)1U

#define DTC_HAS_CLEAR                       (uint8)1U  /*for 14 request*/
#define DTC_NOT_CLEAR                       (uint8)0U

#define MONITOR_CYCLE_NOTCOMPLETE           (uint8)0U/*this Macro must be zero*/
#define MONITOR_CYCLE_END_IN_PASS           (uint8)1U 
#define MONITOR_CYCLE_END_IN_FAIL           (uint8)2U
  

#define DTC_TRUE                  (uint8)1U
#define DTC_FALSE                 (uint8)0U


#define DTC_ENABLE                   1U  /* DTC detect enable, counter should be normally count and DTC codes will be normally stored.*/
#define DTC_DISABLE                  0U  /* DTC detect disable,counter will be disable and DTC codes will not be recorded.*/ 



/*******************************************************************************
*                        Macros for DTC bit operation 
********************************************************************************/

#define DTC_BIT_SUPPORT                    (uint8)1U
#define DTC_BIT_NOTSUPPORT                 (uint8)0U   

/*-----------------------------------------------------------------------------
    &&~   Bit masks 
 -----------------------------------------------------------------------------*/ 
#define DTC_BIT0                        0x01
#define DTC_BIT1                        0x02
#define DTC_BIT2                        0x04
#define DTC_BIT3                        0x08
#define DTC_BIT4                        0x10
#define DTC_BIT5                        0x20
#define DTC_BIT6                        0x40
#define DTC_BIT7                        0x80
#define DTC_NOT_BIT0                    0xfe       
#define DTC_NOT_BIT1                    0xfd
#define DTC_NOT_BIT2                    0xfb
#define DTC_NOT_BIT3                    0xf7
#define DTC_NOT_BIT4                    0xef
#define DTC_NOT_BIT5                    0xdf
#define DTC_NOT_BIT6                    0xbf
#define DTC_NOT_BIT7                    0x7f

/*-----------------------------------------------------------------------------
    &&~  judge if some bit is supported
 -----------------------------------------------------------------------------*/ 
#define DTC_BIT0_SUPPORT                (DTC_STATUS_MASK & DTC_BIT0)
#define DTC_BIT1_SUPPORT                (DTC_STATUS_MASK & DTC_BIT1)
#define DTC_BIT2_SUPPORT                (DTC_STATUS_MASK & DTC_BIT2)
#define DTC_BIT3_SUPPORT                (DTC_STATUS_MASK & DTC_BIT3)
#define DTC_BIT4_SUPPORT                (DTC_STATUS_MASK & DTC_BIT4)
#define DTC_BIT5_SUPPORT                (DTC_STATUS_MASK & DTC_BIT5)
#define DTC_BIT6_SUPPORT                (DTC_STATUS_MASK & DTC_BIT6)
#define DTC_BIT7_SUPPORT                (DTC_STATUS_MASK & DTC_BIT7)

/*-----------------------------------------------------------------------------
    &&~  bit set operrand
 -----------------------------------------------------------------------------*/ 
#define BIT0_SET_OPERRAND             ((uint32)1U << 0)
#define BIT1_SET_OPERRAND             ((uint32)1U << 1)
#define BIT2_SET_OPERRAND             ((uint32)1U << 2)
#define BIT3_SET_OPERRAND             ((uint32)1U << 3)
#define BIT4_SET_OPERRAND             ~((uint32)1U << 4)
#define BIT5_SET_OPERRAND             ((uint32)1U << 5)
#define BIT6_SET_OPERRAND             ~((uint32)1U << 6)
#define BIT7_SET_OPERRAND             ((uint32)1U << 7)

/*-----------------------------------------------------------------------------
    &&~  bit reset operrand
 -----------------------------------------------------------------------------*/ 
#define BIT0_RESET_OPERRAND             ~((uint32)1U << 0)
#define BIT1_RESET_OPERRAND             ~((uint32)1U << 1)
#define BIT2_RESET_OPERRAND             ~((uint32)1U << 2)
#define BIT3_RESET_OPERRAND             ~((uint32)1U << 3)
#define BIT4_RESET_OPERRAND              ((uint32)1U << 4)
#define BIT5_RESET_OPERRAND             ~((uint32)1U << 5)
#define BIT6_RESET_OPERRAND              ((uint32)1U << 6)
#define BIT7_RESET_OPERRAND             ~((uint32)1U << 7)


/*-----------------------------------------------------------------------------
    &&~  bit set operation
 -----------------------------------------------------------------------------*/ 
#define BIT0_SET(dtc)                 dtc |= BIT0_SET_OPERRAND
#define BIT1_SET(dtc)                 dtc |= BIT1_SET_OPERRAND
#define BIT2_SET(dtc)                 dtc |= BIT2_SET_OPERRAND
#define BIT3_SET(dtc)                 dtc |= BIT3_SET_OPERRAND
#define BIT4_SET(dtc)                 dtc &= BIT4_SET_OPERRAND
#define BIT5_SET(dtc)                 dtc |= BIT5_SET_OPERRAND
#define BIT6_SET(dtc)                 dtc &= BIT6_SET_OPERRAND
#define BIT7_SET(dtc)                 dtc |= BIT7_SET_OPERRAND

/*-----------------------------------------------------------------------------
    &&~  bit reset operation
 -----------------------------------------------------------------------------*/ 
#define BIT0_RESET(dtc)                 dtc &= BIT0_RESET_OPERRAND
#define BIT1_RESET(dtc)                 dtc &= BIT1_RESET_OPERRAND
#define BIT2_RESET(dtc)                 dtc &= BIT2_RESET_OPERRAND
#define BIT3_RESET(dtc)                 dtc &= BIT3_RESET_OPERRAND
#define BIT4_RESET(dtc)                 dtc |= BIT4_RESET_OPERRAND
#define BIT5_RESET(dtc)                 dtc &= BIT5_RESET_OPERRAND
#define BIT6_RESET(dtc)                 dtc |= BIT6_RESET_OPERRAND
#define BIT7_RESET(dtc)                 dtc &= BIT7_RESET_OPERRAND

/*-----------------------------------------------------------------------------
    &&~  bit assignment
 -----------------------------------------------------------------------------*/ 
#define BIT_SET_ONE                        0x1
#define BIT_SET_ZERO                       0x0
                                                                          
   
/*******************************************************************************
*                        Macros for DTC data struct 
********************************************************************************/   

/*-----------------------------------------------------------------------------
    &&~  DTC code
 -----------------------------------------------------------------------------*/ 
#define      DTC_CODE(x)              gDtcInfoData->dtcCode[x].DtcCode
#define      DTC_STATUS_BYTE(x)       gDtcInfoData->dtcCode[x].dtcBytes.DtcStatusByte 
#define      DTC_STATUS_BIT0(x)       gDtcInfoData->dtcCode[x].dtcBits.bit0_state  
#define      DTC_STATUS_BIT1(x)       gDtcInfoData->dtcCode[x].dtcBits.bit1_state  
#define      DTC_STATUS_BIT2(x)       gDtcInfoData->dtcCode[x].dtcBits.bit2_state  
#define      DTC_STATUS_BIT3(x)       gDtcInfoData->dtcCode[x].dtcBits.bit3_state  
#define      DTC_STATUS_BIT4(x)       gDtcInfoData->dtcCode[x].dtcBits.bit4_state  
#define      DTC_STATUS_BIT5(x)       gDtcInfoData->dtcCode[x].dtcBits.bit5_state 
#define      DTC_STATUS_BIT6(x)       gDtcInfoData->dtcCode[x].dtcBits.bit6_state  
#define      DTC_STATUS_BIT7(x)       gDtcInfoData->dtcCode[x].dtcBits.bit7_state 

#define      DTC_HIGH_BYTE(x)         gDtcInfoData->dtcCode[x].dtcBytes.DtcHighByte 
#define      DTC_MIDDLE_BYTE(x)       gDtcInfoData->dtcCode[x].dtcBytes.DtcMiddleByte 
#define      DTC_LOW_BYTE(x)          gDtcInfoData->dtcCode[x].dtcBytes.DtcLowByte 


/*-----------------------------------------------------------------------------
    &&~  Extend data
 -----------------------------------------------------------------------------*/
#define      DTC_EXT_DATA(x)                     gDtcInfoData->dtcExtendData[x].aDtcExtendData
#define      DTC_EXT_DATA_BYTE(x)                gDtcInfoData->dtcExtendData[x].cDtcExtendData
#define      DTC_EXT_AGING_COUNTER_DATA(x)       gDtcInfoData->dtcExtendData[x].ExtD.extAgingCounterValue
#define      DTC_EXT_NUM_FAILED_CYCLE_DATA(x)    gDtcInfoData->dtcExtendData[x].ExtD.extNumOfFailedIgnCycle


/*-----------------------------------------------------------------------------
    &&~  Freezeframe
 -----------------------------------------------------------------------------*/
#ifdef USE_SNAPSHOT_DATA
#define      DTC_SNAPSHOT_DATA(x)               gDtcInfoData->dtcSnapshotFrame[x].aDtcSnapshotData 
#define      DTC_SNAPSHOT_DATA_16BIT(x)         gDtcInfoData->dtcSnapshotFrame[x].bDtcSnapshotData
#define      DTC_SNAPSHOT_DATA_BYTE(x)          gDtcInfoData->dtcSnapshotFrame[x].cDtcSnapshotData
#define      DTC_SNAPSHOT_FREEZE_FLAG(x)        gDtcInfoData->dtcSnapshotFrame[x].SnapshotData.freezeflag 

#endif


/*******************************************************************************
*                         Typedef for DTC Data Store 
********************************************************************************/ 
 
/*Dtc code struct type*/
typedef union 
{
   uint32 DtcCode; 
   
   struct
   {     	  
   	  uint8  DtcHighByte;
   	  uint8  DtcMiddleByte;
   	  uint8  DtcLowByte;
   	  
   	  uint8  DtcStatusByte;   
   	  	  
   }dtcBytes;
   
   struct
   {
      uint8  DtcBytes[3];
      
      uint8  bit7_state        :1;  
      uint8  bit6_state        :1;
      uint8  bit5_state        :1; 
      uint8  bit4_state        :1;
      uint8  bit3_state        :1; 
      uint8  bit2_state        :1;  
      uint8  bit1_state        :1;                                    
      uint8  bit0_state        :1;
               
   }dtcBits;
   	
}DtcCodeType;  


/*Dtc extenddata struct type*/
typedef union 
{
   uint32 aDtcExtendData[1]; 
   uint16 bDtcExtendData[2];
   uint8  cDtcExtendData[4];
   
   struct
   {   
   	  uint16  extAgingCounterValue;     /*Extendrecord Number: 01hex*/ 
   	  uint16  extNumOfFailedIgnCycle;   /*Extendrecord Number: 01hex*/  
   	  # if(DEM_USER_DEFINE_EXTDATA_RECORD_SIZE>0u)
      uint8 UserDefineData[DEM_USER_DEFINE_EXTDATA_RECORD_SIZE];/*Extendrecord Number: 01hex.this will be internal data and not open for customer*/
      # endif 
       
   }ExtD;
   	
}ExtDataType; 


/*Dtc freeze frame struct*/
typedef union 
{  
   uint32  aDtcSnapshotData[3];
   uint16  bDtcSnapshotData[6]; 
   uint8   cDtcSnapshotData[12]; 
      
   struct
   {   
	    uint32 areserved[2];
        uint8  breserved[3];
        uint8  freezeflag;
   }SnapshotData;
   	
}SnapshotDataType;


/*Dtc buffer struct*/
typedef struct
{
   DtcCodeType           dtcCode[DTC_NUMBER_SIZE];
   
   ExtDataType           dtcExtendData[DTC_NUMBER_SIZE];
   
   #ifdef USE_SNAPSHOT_DATA
   SnapshotDataType      dtcSnapshotFrame[DTC_NUMBER_SIZE];	/*Moule supply all DTCs the freezedata buffer but actually only the DTCs which has freezedata will store into E2.*/
   #endif
   
   uint32                dtcNumber;
   
}DtcInfoBufType;
  


/*******************************************************************************
*                         Global Function Declaration
********************************************************************************/ 

#ifdef ROLLING_MODE
void Dtc_StatusUpdate(void);
#else
DTC_STATUS_MANAGE_EXT void Dtc_StatusUpdate(uint32 aDTCNumber, uint8 testResult);
#endif


DTC_STATUS_MANAGE_EXT void  Dtc_Status_14Service_Hook(uint32 groupofDTC);
DTC_STATUS_MANAGE_EXT void  Dtc_Status_PowerOn_Init(void);
DTC_STATUS_MANAGE_EXT uint8 Dtc_Save(void);
DTC_STATUS_MANAGE_EXT void  Dtc_MainTask(void);

DTC_STATUS_MANAGE_EXT void Dtc_Init(void);
DTC_STATUS_MANAGE_EXT void Dtc_PreInit(void);
DTC_STATUS_MANAGE_EXT void InitializationFault_DTCStatusUpdate(void);
DTC_STATUS_MANAGE_EXT void Dtc_DataCopy( uint8* Dest,const uint8* Src,uint16 Cnt); 

#endif
