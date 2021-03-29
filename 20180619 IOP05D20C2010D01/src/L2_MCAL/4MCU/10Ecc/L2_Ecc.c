/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2012 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     main.c
*
* @author   
* 
* @version  
* 
* @date     
* 
* @brief    Main file used for evaluation of MPC5643L on EVB boards 
*
*******************************************************************************/
#ifndef L2_ECC_C_
#define L2_ECC_C_
#endif

#include "L2_Ecc.h"



extern SSD_CONFIG ssdConfig;
extern SSD_CONFIG ssdDataConfig;


/* Pointer to Flash intialization function entry code */
extern pFLASHINIT                  pFlashInit                 ;
/* Pointer to Flash erase function entry code */
extern pFLASHERASE                 pFlashErase                ;
/* Pointer to Flash program function entry code */
extern pFLASHPROGRAM               pFlashProgram              ;
/* Pointer to Flash get lock function entry code */
extern pGETLOCK                    pGetLock                   ;
/* Pointer to Flash set lock function entry code */
extern pSETLOCK                    pSetLock                   ;


/* Block start addresses of CFlash */
const uint32 BLOCK_START_CF[] = 
{
    /* LOW */
    0x00000000, 0x00008000, 
    0x0000C000, 0x00010000, 
    0x00018000, 0x00020000, 
    /* MID */
    0x00040000, 0x00060000
};
const uint32 BLOCK_SIZE_CF[] = 
{
    /* LOW */
    0x00008000, 0x00004000, 
    0x00004000, 0x00008000, 
    0x00008000, 0x00020000, 
    /* MID */
    0x00020000, 0x00020000,
};

/* Block start addresses of DFlash */
const uint32 BLOCK_START_DF[] = 
{
    /* LOW */
    0x00800000, 
    0x00804000, 
    0x00808000, 
    0x0080C000
};
const uint32 BLOCK_SIZE_DF[] = 
{
    /* LOW */
    0x00004000, 
    0x00004000, 
    0x00004000, 
    0x00004000
};

#define ENABLE_ME                              0x00001000 
#define ENABLE_EE                              0x00008000 

/******************************************************************************
* Defines and macros
******************************************************************************/
#define DISABLE_IRQ()    asm("wrteei 0")
#define ENABLE_IRQ()     asm("wrteei 1")

static void cRestoreEei(uint32 value)
{
    /*$ Write MSR */
    asm("mtmsr r3\n    ");
}

static void cRestoreMCSR(uint32 value)
{
    /*$ Write MSR */
    asm("mtmcsr r3\n    ");
}

/* function to simulate EER */
uint32 CreateEER_CF(uint8 SectorNum)
{
    uint32 ret;
    uint32 data;


    uint32 lowEnabledBlocks = 0;
    uint32 midEnabledBlocks = 0;

 lowEnabledBlocks = 0x00000000 ;
 midEnabledBlocks = 0x00000001 << (SectorNum-6);
 
 if (C90FL_OK == pFlashErase(&ssdConfig, FALSE, lowEnabledBlocks, midEnabledBlocks, 0x00000000, NULL_CALLBACK))
 {
     ret = E_OK;
 }

    
    /* program */
    data = 0x12345678;
    ret = pFlashProgram(&ssdConfig, BLOCK_START_CF[SectorNum], 0x4, (uint32)&data, NULL_CALLBACK);
    /* over program to cause ECC*/
    data = 0x87654321;
    ret = pFlashProgram(&ssdConfig, BLOCK_START_CF[SectorNum], 0x4, (uint32)&data, NULL_CALLBACK);
    data = ((uint32)(*(vuint32*)((BLOCK_START_CF[SectorNum]))));
    
    /* after reading to this location, EER must turnon. And it enter exception handler.
    Then EER is cleared within exception handler*/
    /* verify that EER is cleared properly */
    if (C90FL_REG_BIT_TEST(ssdConfig.c90flRegBase + C90FL_MCR, C90FL_MCR_EER) == C90FL_MCR_EER)
    {
        ret = C90FL_INFO_EER;
    }
    else
    {
        ret = C90FL_OK;
    }
    return (ret);
}

/* function to simulate EER */
static uint32 CreateEER_DF(PSSD_CONFIG pSSDConfig)
{
    uint32 ret;
    uint32 dest;
    uint32 data = 0;
    
    uint8 tempIndex = 0;// pSSDConfig->lowBlockNum - 1;
    
    
    ret = pFlashErase(pSSDConfig, 0x0,(0x1<<tempIndex), 0x0, 0x0, NULL_CALLBACK);
    if (ret != C90FL_OK)
    {
        //ErrorTrap(ret);
        
        return(ret);
    }
    /* program */
    data = 0x12345678;
    ret = pFlashProgram(pSSDConfig, BLOCK_START_DF[tempIndex], 0x4, (uint32)&data, NULL_CALLBACK);
    /* over program to cause ECC*/
    data = 0x87654321;
    ret = pFlashProgram(pSSDConfig, BLOCK_START_DF[tempIndex], 0x4, (uint32)&data, NULL_CALLBACK);
    data = READ32(BLOCK_START_DF[tempIndex]);
    /* after reading to this location, EER must turnon. And it enter exception handler.
    Then EER is cleared within exception handler*/
    /* verify that EER is cleared properly */
    if (C90FL_REG_BIT_TEST(pSSDConfig->c90flRegBase + C90FL_MCR, C90FL_MCR_EER) == C90FL_MCR_EER)
    {
        ret = C90FL_INFO_EER;
    }
    else
    {
        ret = C90FL_OK;
    }
    return (ret);
}


void EccTest (void)
{
   // DISABLE_IRQ();

    // ***************************************************************************************
    // ************************************* NOTE !!! ****************************************
    // ***************************************************************************************
    // Non-Volatile User Options register (NVUSRO) addr:0x203E18,
    // change PAD3V5V to 0, if High Voltage supply is 5.0 V
    
    // bit #2: PAD3V5V: 0 High Voltage supply is 5.0 V; 1 High Voltage supply is 3.3 V
    //                  Default manufacturing value before Flash initialization is '1' (3.3 V), 
    //                  which should ensure correct minimum slope for boundary scan. 
    //                  Customers should modify the bit to "0" if High Voltage supply is 5.0 V.         
    // bit #0: WATCHDOG_EN: 1: Enable after reset; 0: Disable after reset
    //                  Default manufacturing value before Flash initialization is '1'
    // ***************************************************************************************
    //nNVUSRO = *((uint32_t*)0x203E18);
    
    
    (void)pFlashInit(&ssdConfig);
    (void)pFlashInit(&ssdDataConfig);

    (void)pSetLock(&ssdConfig, LOCK_SHADOW_PRIMARY,   1, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_SHADOW_SECONDARY, 1, FLASH_SLMLR_PASSWORD);
   
    (void)pSetLock(&ssdConfig, LOCK_LOW_PRIMARY,   0, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_LOW_SECONDARY, 0, FLASH_SLMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_MID_PRIMARY,   0, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_MID_SECONDARY, 0, FLASH_SLMLR_PASSWORD);
    (void)pSetLock(&ssdConfig, LOCK_HIGH,          0, FLASH_HLR_PASSWORD);
    
    (void)pSetLock(&ssdDataConfig, LOCK_LOW_PRIMARY,   0, FLASH_LMLR_PASSWORD);
    (void)pSetLock(&ssdDataConfig, LOCK_LOW_SECONDARY, 0, FLASH_SLMLR_PASSWORD);
  
    // Trigger ECC error for testing the ECC error handle 

    // MSR[ME] == 0 and MSR[EE] == 0, thus checkstop will be triggered 
    
   // CreateEER_CF(6);
    
    //CreateEER(&ssdConfig);
    CreateEER_DF(&ssdDataConfig);
    
    for(;;)
    {
    	
    }
}

/***********************************************************************************************************
 ========================= MPC5604P reactions to ECC double bit error ======================================
************************************************************************************************************
1) If ECC error occurs when MSR[EE]=1 an ECC error will lead to IVOR2(data) or IVOR3 (Instruction) exception,  
2) If MSR[EE]=0 but MSR[ME]=1 the ECC error will result in Machine Check IVOR1 exception 
3) If MSR[EE]=0 and MSR[ME]=0 the ECC error will result in checkstop state. If RGM_FERD[D_CHKSTOP]==0(default),
   RESET will be triggered immediately. 
4) For case 1) and 2), if MCM.ECR.B.EFNCR == 1, ECSM interrupt will be triggered after exception.    
   This is given by priority. IVOR1/2/3 has higher priority than IVOR4 (external interrupts). 
************************************************************************************************************/
extern void EcuSoftRst(void);

void IVOR1_Isr()
{
    uint32 EccErrAddr = 0;

    /* flash ecc error */
    if(MCM.ESR.B.FNCE == 1)
    {
    	EccErrAddr = MCM.FEAR.R;
    	
    	if(EccErrAddr >= 0x800000)
    	{
    		(void)Fls_Erase(EccErrAddr,0x00004000ul,NULL_CALLBACK);
    		
    		/* reset MCU */
    		
    	//	EcuSoftRst();
    	}
    }

    /* ram ecc error */
    if(MCM.ESR.B.RNCE == 1)
    {
    	/* reset MCU */
    	
    	//EcuSoftRst();
    }    
}

void IVOR2_Isr()
{
    IVOR1_Isr();
    
    asm
    {
    	nop;
    }
}

/***********************************************************************************************************
 ========================= MPC5604P reactions to ECC double bit error ======================================
************************************************************************************************************
1) If ECC error occurs when MSR[EE]=1 an ECC error will lead to IVOR2(data) or IVOR3 (Instruction) exception,  
2) If MSR[EE]=0 but MSR[ME]=1 the ECC error will result in Machine Check IVOR1 exception 
3) If MSR[EE]=0 and MSR[ME]=0 the ECC error will result in checkstop state. If RGM_FERD[D_CHKSTOP]==0(default),
   RESET will be triggered immediately. 
4) For case 1) and 2), if MCM.ECR.B.EFNCR == 1, ECSM interrupt will be triggered after exception.    
   This is given by priority. IVOR1/2/3 has higher priority than IVOR4 (external interrupts). 
************************************************************************************************************/
void ECC_DBD_Isr (void)
{
    MCM.ESR.B.RNCE =1;
    MCM.ESR.B.FNCE =1;
}
/*******************************************************************************
Function Name : ECSM_Init
Engineer      : b08110
Date          : Jan-21-2010
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : initialization of the ECSM module
Issues        : NONE
*******************************************************************************/
void ECSM_Init(void)
{
    cRestoreEei(ENABLE_ME);
   /* enable non-correctable ECC error reporting for internal FLASH */
    MCM.ECR.B.EFNCR = 1;      
}
