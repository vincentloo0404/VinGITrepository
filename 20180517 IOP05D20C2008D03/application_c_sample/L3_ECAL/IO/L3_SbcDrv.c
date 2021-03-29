/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     SbcDrv
* 
* @brief    adc interface between MCAL and HAL
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2016/10/23      JiaoYu       N/A          Original
*     
*******************************************************************************/

/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"L3_SbcDrv.h"

/* *****************************************************************************
   Function:        hAdcIf_u16GetBatVoltVal
   Description:     init
   Parameters:      Input:    None
                    Output:   battery voltage sample value
   Notes:           
                   
   ***************************************************************************** */
uint16 WdVal = 0;
uint16 IsVal = 0;
uint16 IcVal = 0;
uint16 McVal = 0;   
/* *****************************************************************************
   Function:        SBC_L3_Init
   Description:     init
   Parameters:      Input:    None
                    Output:   none
   Notes:           
                   
   ***************************************************************************** */
void SBC_L3_Init(void)
{
 	uint16 temp = 0;
 	
 	(void)SbcTxRx(SBC_READ_WD_REG_CMD,&temp);

    for(temp=0;temp<100;temp++)
    {
    }

    (void)SbcTxRx(SBC_WRITE_IS_REG_CMD,&temp);
    
    for(temp=0;temp<100;temp++)
    {
    }

    (void)SbcTxRx(SBC_WRITE_IC_REG_CMD,&temp);
    
    for(temp=0;temp<100;temp++)
    {
    }

    (void)SbcTxRx(SBC_WRITE_WD_REG_CMD,&temp);
    
    for(temp=0;temp<100;temp++)
    {
    }
 	
    (void)SbcTxRx(SBC_WRITE_MC_REG_CMD,&temp);
    
    for(temp=0;temp<100;temp++)
    {
    }

    (void)SbcTxRx(SBC_READ_WD_REG_CMD,&WdVal);
    
    for(temp=0;temp<100;temp++)
    {
    }
    
    (void)SbcTxRx(SBC_READ_WD_REG_CMD,&WdVal);
    
    for(temp=0;temp<100;temp++)
    {
    }
        
    (void)SbcTxRx(SBC_READ_MC_REG_CMD,&McVal);
    
    for(temp=0;temp<100;temp++)
    {
    }    

    (void)SbcTxRx(SBC_READ_IC_REG_CMD,&IcVal);
    
    for(temp=0;temp<100;temp++)
    {
    }    

    (void)SbcTxRx(SBC_READ_IS_REG_CMD,&IsVal);
    
    for(temp=0;temp<100;temp++)
    {
    }    
}
/* *****************************************************************************
   Function:        SBC_L3_Init
   Description:     init
   Parameters:      Input:    None
                    Output:   none
   Notes:           
                   
   ***************************************************************************** */
void SBC_L3_Per(void)
{
    static uint8 ReadSbcRegIndex = 0;
    
    uint16 temp;
 	
 	if(ReadSbcRegIndex > 4)
 	{
 		ReadSbcRegIndex = 0;
 	}
 	else
 	{
 	}
 	
 	switch(ReadSbcRegIndex)
 	{
 		case 0:
 		{
 			(void)SbcTxRx(SBC_READ_WD_REG_CMD,&WdVal);
 		}
 		break;
  		case 1:
 		{
 			(void)SbcTxRx(SBC_READ_MC_REG_CMD,&McVal);
 		}
 		break;
  		case 2:
 		{
 			(void)SbcTxRx(SBC_READ_IC_REG_CMD,&IcVal);
 		}
 		break;
  		case 3:
 		{
 			(void)SbcTxRx(SBC_READ_IS_REG_CMD,&IsVal);
 		}
 		break;	
 		
 		case 4:
 		{
 			(void)SbcTxRx(SBC_WRITE_WD_REG_CMD,&temp);
 		}
 		break; 		
 		
 		default:
 		
 		break;	
 	}
 	
 	ReadSbcRegIndex++;
}


/* *****************************************************************************
   Function:  hSBC_vCfgSleepMode      
   Description:     
   Parameters:      Input:    None
                    Output:  TRUE if succ, and FALSE if error occurs
   Notes:           
                   
   ***************************************************************************** */
void SBC_L3_CfgSleepMode(void)
{
    uint16 temp;
    
    /*clear wake-up events if any one pending */
    (void)SbcTxRx(SBC_CLA_ISR_EVENT_CMD,&temp);
    
    for(temp = 0; temp < 0xF; temp++)
    {
        asm
        {
   	    	nop
   	    }
    }
    
    (void)SbcTxRx(SBC_READ_IS_REG_CMD,&IsVal);
    
    
    if((SBC_WRITE_IS_REG_CHK & SBC_IS_WR_RE_CHECK_MSK) == (SBC_IS_WR_RE_CHECK_MSK & IsVal))
    {
       (void)SbcTxRx(SBC_ENTER_SLEEP_MD_CMD,&temp);
    }
}
/* *****************************************************************************
   Function:  hSBC_vCheckWakeupIntEvent      
   Description:  Check Wakeup Int Event
   
   Parameters:      Input:  None
    
                    Output:   
                            SBC_WI_INT_FLG_CLR
                            SBC_WI_INT_FLG_SET
                            SBC_WI_INT_FLG_UDF
   Notes:           
                   
   ***************************************************************************** */
uint8 SBC_L3_CheckWakeupIntEvent(void)
{
    uint8 SbcLocalOptSt = FALSE;
    
    (void)SbcTxRx(SBC_READ_IS_REG_CMD, &IsVal);
    
    if(SBC_GLB_VARI_RESET != (IsVal & (SBC_IS_WI1_MSK | SBC_IS_WI2_MSK)))
    {
        SbcLocalOptSt = SBC_WI_INT_FLG_SET;    
    }
    else
    {
        SbcLocalOptSt = SBC_WI_INT_FLG_CLR;
    }
    
    return(SbcLocalOptSt);
}
/* End of file */