/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_GPIO.c
*
* @brief    SIUL module function, GPIO port Init and Output
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/05/25      ----       N/A          Original
*     1.1        2017/01/6       ych       N/A          Original     
*******************************************************************************/

#ifndef M_GPIO_C
#define M_GPIO_C
#endif

/* *****************************************************************************
   External Includes
   ***************************************************************************** */
#include 	"m_GPIO.h"
#include 	"m_GPIO_Cfg.h"

/* *****************************************************************************
   Function:        mGPIO_PinOut_Low
   Description:     Set Pin Output Low level
   Parameters:      Input:    uint8	PadName PadDefinition as"A1"
                    Output:   None
   Notes:           Hardware pullup needed
                   
   ***************************************************************************** */
void 	PORT_L2_Init(void)
{
	int testCnt = 0;
	/* TES1 */
	//modify by ych 20170705 
	
	A6_OUT = LOW;
	PCR_CFG(A6,PCR_PIN_OUT_WPE);
	//TES2
	A5_OUT = LOW;
	PCR_CFG(A5,PCR_PIN_OUT_WPE);
	
	D2_OUT = HIGH;
	PCR_CFG(D2,PCR_PIN_OUT_WPE);

//	O_OCP_RSET拢卢O_OVP_RSET,O_PFC_OVP_RSET,O_PFC_OCP_RSET拢卢O_GLB_RSET


	/* resolver squire pulse pin *///remove by ych at 20170705 not use
	/*
	D1_OUT = LOW;	
	SIU.PCR[D1].R = (ALT3|B_OBE);	//output
	*/
	
    /* Test2 8pin */
    /*
    A5_OUT = LOW;
	PCR_CFG(A5,PCR_PIN_OUT_WPE);
	*/
	
	
	
//************************** INPUT  PIN ****************************************//
    /* I_GLB_EN */
	PCR_CFG(C13,PCR_PIN_IN);
	
	/* PG_SENSE */
	PCR_CFG(D5,PCR_PIN_IN);
	
	/* AC_WAKEUP */
	PCR_CFG(D6,PCR_PIN_IN);
	
	/* I_AD_LocalWake */
	PCR_CFG(D7,PCR_PIN_IN);
	
	/* EN_POWER_UC_SBC */
	PCR_CFG(A2,PCR_PIN_IN);
	
    /* I_DCDC_OCP */
	PCR_CFG(D12,PCR_PIN_IN);

    /* I_PFC_OCP */
	PCR_CFG(C10,PCR_PIN_IN);

    /* I_PFC_OVP */
	PCR_CFG(B2,PCR_PIN_IN);

    /* I_DCDC_OVP */
	PCR_CFG(B3,PCR_PIN_IN);


    /* OVER_CUR_TRIG */
	PCR_CFG(A9,PCR_PIN_IN);

    /* LIMP_OUT */
	PCR_CFG(A13,PCR_PIN_IN);
	
	/* I_SBC_INTN */
	PCR_CFG(B6,PCR_PIN_IN);
	
	
	
	//************************** OUTPUT  PIN ****************************************//
	
	
	

	 /* O_PFC_DRV_EN */
	 /*
    //A8_OUT = HIGH;
    A8_OUT = LOW;
	PCR_CFG(A8,PCR_PIN_OUT_WPE);
	*/
	
	/*O_PFC_EN*/
	//A0_OUT = HIGH;
	C4_OUT = LOW;//default HIGH pfc normal work
	PCR_CFG(C4,PCR_PIN_OUT_WPE);

	/*S2_CTR*/
	A8_OUT = LOW;
	PCR_CFG(A8,PCR_PIN_OUT_WPE);
	
	/*CAN_MODE*/
	C11_OUT = LOW; //Normal LOW;Standby HIGH
	PCR_CFG(C11,PCR_PIN_OUT_WPE);
	
	/*O_PG*/
	D8_OUT = LOW;//default HIGH WORK
	PCR_CFG(D8,PCR_PIN_OUT_WPE);
	
	/*O_DEN*/
	C3_OUT = LOW;
	PCR_CFG(C3,PCR_PIN_OUT_WPE);

    /* O_S_RlyCTL1 */
    A12_OUT = LOW;
    //A12_OUT = HIGH;
	PCR_CFG(A12,PCR_PIN_OUT_WPE);

	/* O_S_RlyCTL2 */
    C9_OUT = LOW;
    //C9_OUT = HIGH;
	PCR_CFG(C9,PCR_PIN_OUT_WPE);



	//NEED 	rest signal
	
	//   	O_MCU_FAT
   	//D9_OUT = LOW;
   	//D9_OUT = HIGH;
	//PCR_CFG(D9,PCR_PIN_OUT_WPE);
	
    /* O_OVP_RSET */
    A7_OUT = HIGH;
//	A7_OUT = LOW;
	PCR_CFG(A7,PCR_PIN_OUT_WPE);
        
    // O_OCP_RSET 
	A0_OUT = HIGH;
    //C4_OUT = LOW;
	PCR_CFG(A0,PCR_PIN_OUT_WPE);


		// delay 10ms，再拉低的reset信号
	 //*
	 while(testCnt++ < 71430)
	  {
	  	asm 
	  	{
	  	  nop	
	  	  nop
	  	  nop
	  	  nop
	  	}
	  }
	 // O_OVP_RSET 
    A7_OUT = LOW;
//	PCR_CFG(A7,PCR_PIN_OUT_WPE);
        
    // O_OCP_RSET 
	A0_OUT = LOW;
	//PCR_CFG(C4,PCR_PIN_OUT_WPE);
	
	//delay 10ms
	testCnt = 0;
	while(testCnt++ < 71430)
	  {
	  	asm 
	  	{
	  	  nop	
	  	  nop
	  	  nop
	  	  nop
	  	}
	  }
	
	
		//O_GLB_RSET
	C14_OUT = HIGH;
	PCR_CFG(C14,PCR_PIN_OUT_WPE);
		//delay 10ms
		testCnt = 0;
	while(testCnt++ < 71430)
	  {
	  	asm 
	  	{
	  	  nop	
	  	  nop
	  	  nop
	  	  nop
	  	}
	  }
	  
	  	//O_GLB_RSET
	C14_OUT = LOW;
//	PCR_CFG(D8,PCR_PIN_OUT_WPE);
	  
	  
	  

	//O_PFC_OVP_RSET 
	C5_OUT = HIGH;
	PCR_CFG(C5,PCR_PIN_OUT_WPE);
	
	/* O_PFC_OCP_RSET */
	C7_OUT = HIGH;
//    C7_OUT = LOW;
	PCR_CFG(C7,PCR_PIN_OUT_WPE);
	

	//delay 10ms
	 //*
	 while(testCnt++ < 71430)
	  {
	  	asm 
	  	{
	  	  nop	
	  	  nop
	  	  nop
	  	  nop
	  	}
	  }


	//O_PFC_OVP_RSET
	C5_OUT = LOW;
//	PCR_CFG(C5,PCR_PIN_OUT_WPE);
	

    // O_PFC_OCP_RSET 
    C7_OUT = LOW;
//	PCR_CFG(C7,PCR_PIN_OUT_WPE);

//*/
	
}

void 	PORT_L2_MCU_FATInit(void)
{
	//O_MCU_FAT
   	D9_OUT = LOW;
   	//D9_OUT = HIGH;
	PCR_CFG(D9,PCR_PIN_OUT_WPE);
}