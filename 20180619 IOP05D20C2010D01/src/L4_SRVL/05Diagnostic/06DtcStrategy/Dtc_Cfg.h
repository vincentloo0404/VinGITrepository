/******************************************************************************
*
* Beijing Hualong Tech Inc.
* (c) Copyright 2013 Beijing Hualong Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dtc_Cfg.h  
*
* @brief  this file provide the config interfaces of DTC Moudle
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/05/10    CODER1     N/A           Original
*     
*******************************************************************************/

#ifndef _DTC_CFG_H_
#define _DTC_CFG_H_

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "Dtc_Types.h"
#include "Compiler.h"
//#include "Defines.h"

/******************************************************************************                          
 *                           Config-Macros for DTC            
 ******************************************************************************/ 

/*DTC module working mode */
#define ROLLING_MODE

#ifdef  ROLLING_MODE

#undef  REALTIME_CALL_MODE
#else
#define REALTIME_CALL_MODE

#endif

#ifdef ROLLING_MODE

#define DTC_TASK_TIME                   5u /*task schedule cycle*/
#define DTC_DELAY_ON_BOOT               0u /*delaytime before called after poweron*/

#endif


#define DTC_STATUS_MASK                 0xFF /*statusbits mask*/  


/*-------------------------------------------------------------------------------------------------------------------------
    &&~                                                  DTC INFO SIZE
 --------------------------------------------------------------------------------------------------------------------------*/ 
#define USE_SNAPSHOT_DATA                    /*if using freezeframe then define the macro*/

#define DTC_NUMBER_SIZE                 21u//26u  /*amount of DTCs*/

#define DTC_CODE_STORE_SIZE             (DTC_NUMBER_SIZE * 4) /*DTC code total size,must be divisible by 4*/

#define DEM_DEFAULT_EXTDATA_RECORD_SIZE        4u             /*default extend data size,must be divisible by 4*/

#define DEM_USER_DEFINE_EXTDATA_RECORD_SIZE    0u             /*user defined extend data size,must be divisible by 4*/

#define DTC_EXD_DATA_TYPE_SIZE          (DEM_USER_DEFINE_EXTDATA_RECORD_SIZE + DEM_DEFAULT_EXTDATA_RECORD_SIZE)  /*each extend data size,must be divisible by 4*/

#define DTC_EXD_STORE_SIZE              (DTC_NUMBER_SIZE * DTC_EXD_DATA_TYPE_SIZE) /*extend data total size,must be divisible by 4*/


#ifdef  USE_SNAPSHOT_DATA
//#define DTC_FREEZEFRAME_AMOUNT          3u                    /*this version not used*/

#define DTC_SNAPSHOT_TYPE_SIZE          12u                   /*freezeframe struct size,must be divisible by 4*/

#define DTC_SNAPSHOT_STORE_SIZE         (DTC_NUMBER_SIZE * DTC_SNAPSHOT_TYPE_SIZE) /*freeze data total size,must be divisible by 4*/      
#else
#define DTC_SNAPSHOT_STORE_SIZE         0u
#endif

#define NONE_DTC_DATA_SIZE              4u/*record DTC number*/

/*real store size*/
#define DTC_ALL_INFO_STORE_SIZE         (((DTC_CODE_STORE_SIZE + DTC_EXD_STORE_SIZE) + DTC_SNAPSHOT_STORE_SIZE)+ NONE_DTC_DATA_SIZE) /*must be multiple of 4*/
/*size based on 8bytes align*/
#define DTC_ALL_INFO_WRITE_SIZE         (((DTC_ALL_INFO_STORE_SIZE % 8u == 0)?DTC_ALL_INFO_STORE_SIZE: \
                                        (DTC_ALL_INFO_STORE_SIZE + (8u-(DTC_ALL_INFO_STORE_SIZE % 8u)))) ) 

/*Macros for FreezeFrame index*/
#define DTC_NUMBER_OF_DYNAMIC_DATA_DID    6u/*amount of dynamic DIDs,its amount due to how many paramaters need to concerned*/
#define DTC_MAX_NUMBER_FF_RECORDS         2u/*a min value which can satisfy all DTCs(which has freezeframe) requirements*/
#define DTC_MAX_NUMBER_DID_IN_FF_RECORDS  4u/*each FreezeFrame maybe contain different amount of DIDs,so this array size is base on the MAX one*/ 


/*------------------------------------------------------------------------------------
    &&~                           DTC detect Timer
 ------------------------------------------------------------------------------------*/ 
/*general Macros*/
#define ALL_DTCS_USE_SAME_MATURE_STEP         STD_ON /*default STD_ON*/
#define ALL_DTCS_USE_SAME_MATURE_THRESHOLD    STD_ON /*default STD_ON*/ 

#define ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD   STD_ON /*default STD_ON*/
#define ALL_DTCS_USE_SAME_AGING_THRESHOLD     STD_ON/*default STD_ON*/


#if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_ON)    

#define DTC_FAIL_MATURE_STEP           1U
#define DTC_PASS_DEMATURE_STEP         1U

#endif

#if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_ON)   

#define DTC_FAIL_MATURE_THRESHOLD           3U
#define DTC_PASS_DEMATURE_THRESHOLD         -3u

#endif

#if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_ON)    

#define DTC_FAIL_CONFIRM_THRESHOLD          100U

#endif

#if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_ON)    

#define DTC_AGING_THRESHOLD                 2U

#endif

 
   
   
/**************************************************************************************                          
 *                Struct Types for DTC info\freezeframe config table            
 **************************************************************************************/ 

/*------------------------------------------------------------------------------------
    &&~         DTC Attribute Typedef
 ------------------------------------------------------------------------------------*/ 
typedef struct
{
  uint32   DtcHexCode;
  
  #ifdef USE_SNAPSHOT_DATA
  uint8    WithFreezeFrameFlag;  
  uint8    FreezeFrameNumber;
  #endif
  
  uint8    FaultSafetyLevel; 
  uint8    WithWaringIndicator;   
  uint8    RestableFlag;
  uint8    DtcMonitorType;
  uint8    IsImmediateType;           
  
  /*-------- ususlly not used -------- */
  #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)
  uint8    MatureFailCountStep;        
  uint8    MaturePassCountStep;       
  #endif
  #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)
  uint16   TestFailedMatureThreshold; 
  sint16   TestPassedDematureThreshold;
  #endif 
  #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
  uint16   ConfirmMatureThreshold;     
  #endif
  #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
  uint16   AgingThreshold;             
  #endif  
  /*------- ususlly not used --------- */
  
}Dtc_AttributeType;

/*------------------------------------------------------------------------------------
    &&~         Structure describing one Freeze Frame Record
 ------------------------------------------------------------------------------------*/ 

typedef struct 
{
  uint8  DataSize;/*size of data bytes of a FreezeFrame*/
  uint8  NumOfDid;/*indicate how many dids in this FreezeFrame*/
  uint8  DidRefTable[DTC_MAX_NUMBER_DID_IN_FF_RECORDS];/*the DIDs of each DTC*/
         
} Dtc_FreezeFrameRecDataType;

/*------------------------------------------------------------------------------------
    &&~         Structure describing one DID Record 
 ------------------------------------------------------------------------------------*/ 
     
typedef struct                                          
{
  uint16        Did;/*did code*/
  uint8         DataSize; /*1 .. 255,Defines the size of the data element in bytes.*/ /*Did data size*/
  const uint8   *DataBuf;/*data buffer*/
} Dtc_DidClassType;



/**************************************************************************************                          
 *                               Global Variables           
 **************************************************************************************/ 
 
extern ROM_CONST Dtc_AttributeType* const gDtc_Attribute_Table;

extern ROM_CONST uint32 DTC_InitValue[DTC_NUMBER_SIZE];

extern ROM_CONST Dtc_FreezeFrameRecDataType Dtc_FFRecCfgTable[DTC_MAX_NUMBER_FF_RECORDS];

extern ROM_CONST Dtc_DidClassType  Dtc_DidCfgTable[DTC_NUMBER_OF_DYNAMIC_DATA_DID];

extern uint8  u8DidParameter[10];
extern uint16 u16DidParameter[10];


#endif

/********************************************** END ******************************************************/
