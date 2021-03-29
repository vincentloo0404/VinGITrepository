/******************************************************************************
*
* Beijing Hualong Tech Inc.
* (c) Copyright 2013 Beijing Hualong Tech, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   Dtc_Cfg.c  
*
* @brief  this file provide the config interfaces of DTC Moudle
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/05/10    CODER1       N/A           Original
*     1.1      2013/10/16    CODER1       N/A           Change const type into ROM_CONST
*******************************************************************************/

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/

#include "Dtc_Cfg.h"
#include "Compiler.h"

/******************************************************************************                          
 *                           FF data container def             
 ******************************************************************************/
uint8  u8DidParameter[10];

uint16 u16DidParameter[10];

/******************************************************************************                          
 *                           DTC code init value             
 ******************************************************************************/
ROM_CONST uint32 DTC_InitValue[DTC_NUMBER_SIZE]= 
{
	/*
    //Motor Code//
	0xC0011050, //Motor Ctrl/
	0xC0011150, //PreDrv/
	0xC0011250, //Motor Pos/
	0xC0011350, //Motor Curr/
	0xC0011450, //Resolver Volt/
	
    //TAS Code/
	0xC1011550, //TS signal lost/
	0xC1011650, //TS signal character/
	0xC1011750, //AS signal lost/
	0xC1011850, //AS signal character/
	0xC1011950, //AS Mechnical/
	0xC1012050, //TAS Volt/
    	 
    //NWK Code/	
	0xC2012150, //BUSOFF/
	0xC2012250,	//EMS msg/
	0xC2012350,//	ESP Msg/
	
    //Volt Code/
    0xC3012450, //Low volt/
	0xC3012550,	//High volt/
	0xC3012650,	//Reduce Volt/
	
	//Genernal Code/
	0xC4012750, //Charge/
	0xC4012850, //Calb data/
	0xC4012950, //Temp abnormal/
	0xC4013050, //Temp overhigh/	
	0xC4013150,	//Ignition signal/
    0xC4013250,	//Angle offset err/
	
	//Mcu Code/
	0xC5013350, //Malfunction/
	0xC5013450,	//EEPROM/
	0xC5013550,	//FlashRam/
	*/
	
	0xB2001650,//低压输入欠压（诊断）

	0xB2011750,//低压输入过压（诊断）

	0xB2021650,//内部13.5V欠压保护

	0xB2031750,//内部13.5V过压保护

	0xE2000050,//输入继电器诊断

	0xE2010050,//输出电流传感器诊断

	0xE2020050,//PG信号诊断

	0xB2041750,//"PFC DC-link 过压保护ChgDCOVP"

	0xB2051950,//"DCDC硬件过流保护ChgLlcHWOCP"

	0xB2061750,//"高压输出过压保护ChgHVOVP"

	0xB2071750,//DCDC 预充 timeout 

	0xE2030050,//"PFC Boost Fail保护ChgPFCStartFail"

	0xB2081950,//"AC输入过流保护ChgVinOCP"

	0xB2091750,//"AC输入过压保护ChgVinOVP"

	0xB20A1650,//"AC输入欠压保护ChgVinUVP"

	0xB20B1350,//"AC输入断开ChgACLoss"

	0xB20C1650,//"高压输出欠压保护ChgHVUVP"

	0xB20D4B50,//"FB过温保护ChgCoolantPlateOTP"

	0xB20E4B50,//"PCB过温保护"

	0xC0730050,//"CAB总线关闭CAN BUS OFF"

	0xC1110050//"BMS CAN通讯丢失ChgCANMissing"

	
		
};


/**********************************************************************************************                          
 *                            Freeze Frame Data Record Configure
 **********************************************************************************************/
                               
/*------------------------------------------- ------------------------------------------------*
                                    FreezeFrame Info config Table
                          FreezeFrame data size, number of Dids, Did's index
 *------------------------------------------- ------------------------------------------------*/
ROM_CONST Dtc_FreezeFrameRecDataType Dtc_FFRecCfgTable[DTC_MAX_NUMBER_FF_RECORDS]=
{
    {
        5,3,{0,1,2},  /*FF 01 DID :0001,0002,0003*/        //20180625  FreezeFrame data size没有使用到？？？ 
    },
    {
        8,4,{3,4,1,0},/*FF 02 DID: 0004,0005,0002,0001*/
    },
    
};

/*------------------------------------------- ------------------------------------------------*
                                    Dynamic DIDs Info config Table
                               DID number, DID size, DID data buffer
 *------------------------------------------- ------------------------------------------------*/
ROM_CONST Dtc_DidClassType  Dtc_DidCfgTable[DTC_NUMBER_OF_DYNAMIC_DATA_DID]=
{
    {
        0x0001,2,(uint8*)&u16DidParameter[0]   /*	0 Vechile speed*/	      
    },	
    {
        0x0002,2,(uint8*)&u16DidParameter[1]   /*	1 engine speed*/	
    },	
    {
        0x0003,1,(uint8*)&u8DidParameter[6]    /*	2 PCB temputure*/	
    },	
    {
        0x0004,2,(uint8*)&u16DidParameter[3]   /*   3 system volt*/	
    },	
    {
        0x0005,2,(uint8*)&u16DidParameter[4]   /*	4 current*/	
    },	
    {
        0x0006,2,(uint8*)&u16DidParameter[5]   /*	5 ...*/ 	
    },
};


/*------------------------------------------- ------------------------------------------------*
                                    DTC INFOMATION TABLE
                                Absolute value can only be used
   1)If detect type is INITIALIZATION, its process type must be IMMEDIATE.
   2)If restable type is DTC_UNRESTABLE, its process type must be IMMEDIATE.
 *------------------------------------------- ------------------------------------------------*/

/*usually only immediate type DTC has the snapshotdata.*/

ROM_CONST static Dtc_AttributeType Dtc_Attribute_Table[DTC_NUMBER_SIZE]= 
{   


  {  
     /*DTC Code*/
     0xB2001650,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_A_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 1
  \*----------------------------------------- ### ----------------------------------------*/


  {  
     /*DTC Code*/
     0xB2011750,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_A_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 2
  \*----------------------------------------- ### ----------------------------------------*/


  {  
     /*DTC Code*/
     0xB2021650,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_A_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 3
  \*----------------------------------------- ### ----------------------------------------*/

  {  
     /*DTC Code*/
     0xB2031750,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_A_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 4
  \*----------------------------------------- ### ----------------------------------------*/

{  
     /*DTC Code*/
     0xE2000050,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_A_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 5
  \*----------------------------------------- ### ----------------------------------------*/


{  
     /*DTC Code*/
     0xE2010050,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_A_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 6
  \*----------------------------------------- ### ----------------------------------------*/
  
{  
     /*DTC Code*/
     0xE2020050,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_A_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 7
  \*----------------------------------------- ### ----------------------------------------*/
{  
     /*DTC Code*/
     0xB2041750,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 8
  \*----------------------------------------- ### ----------------------------------------*/
  
  {  
     /*DTC Code*/
     0xB2051950,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 9
  \*----------------------------------------- ### ----------------------------------------*/
  
  
    {  
     /*DTC Code*/
     0xB2061750,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 10
  \*----------------------------------------- ### ----------------------------------------*/
  
  
    
    {  
     /*DTC Code*/
     0xB2071750,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 11
  \*----------------------------------------- ### ----------------------------------------*/
  
    
    
    {  
     /*DTC Code*/
     0xE2030050,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 12
  \*----------------------------------------- ### ----------------------------------------*/
  
  
  
      
    
    {  
     /*DTC Code*/
     0xB2081950,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 13
  \*----------------------------------------- ### ----------------------------------------*/
    
      
    
    {  
     /*DTC Code*/
     0xB2091750,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 14
  \*----------------------------------------- ### ----------------------------------------*/
  
      {  
     /*DTC Code*/
     0xB20A1650,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 15
  \*----------------------------------------- ### ----------------------------------------*/
        {  
     /*DTC Code*/
     0xB20B1350,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_C_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 16
  \*----------------------------------------- ### ----------------------------------------*/
    
      {  
     /*DTC Code*/
     0xB20C1650,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_B_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 17
  \*----------------------------------------- ### ----------------------------------------*/
  
      
      {  
     /*DTC Code*/
     0xB20D4B50,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_C_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 18
  \*----------------------------------------- ### ----------------------------------------*/
  
    
      
      {  
     /*DTC Code*/
     0xB20E4B50,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_C_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 19
  \*----------------------------------------- ### ----------------------------------------*/
  
  
      
      
      {  
     /*DTC Code*/
     0xC0730050,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_C_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 20
  \*----------------------------------------- ### ----------------------------------------*/
  
    
      
      
      {  
     /*DTC Code*/
     0xC1110050,   
     
     #ifdef USE_SNAPSHOT_DATA
     /*snapshot record support*/      /*snapshot record number*/
     DTC_NO_SNAPSHOT,               2u,
     #endif
     
     /*safety level*/        /*waring indicator*/
     SAFETY_C_LEVEL,         DTC_WITH_WARNING_INDICATOR,
       
     /*restable*/            /*detect type*/           /*process type*/   
     DTC_RESTABLE,         DETECT_CYCLIC,            IMMEDIATE,
     
     
     /*----------------------------    ---------------------------------*\
       (Default)Ususlly the following items are disabled.                     
       Only when the Marcros are opened these items need to be set value.         
     \*---------------------------------------    ----------------------*/
     
     #if(ALL_DTCS_USE_SAME_MATURE_STEP == STD_OFF)     
     /*testfail mature step*/      /*testpass demature step*/     
     2u,                            1u,                                   
     #endif
     
     #if(ALL_DTCS_USE_SAME_MATURE_THRESHOLD == STD_OFF)   
     /*testfail mature threshold*/ /*testpass demature threshold*/
     100u,                          100u,
     #endif 
      
     #if(ALL_DTCS_USE_SAME_CONFIRM_THRESHOLD == STD_OFF)
     /*Confirm threshold*/         
     0u,                          
     #endif
     
     #if(ALL_DTCS_USE_SAME_AGING_THRESHOLD == STD_OFF)
     /*Aging threshold*/
     2u,  
     #endif    
                                
  },    
  /*----------------------------------------- ### ----------------------------------------*\
                                         parting line 21
  \*----------------------------------------- ### ----------------------------------------*/
  
                                       /** All End **/
};   


/* Global Const Variable (ROM) */
ROM_CONST  Dtc_AttributeType* const gDtc_Attribute_Table = Dtc_Attribute_Table;

/******************************************************* End  ******************************************************/