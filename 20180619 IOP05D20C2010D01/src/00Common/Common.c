/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     Common.c
*
* @brief    this file contains some common functions, which other source files may use.
*			such as Soft Delay function like "mDalay_Nms"
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        	CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2016/09/24     ----			N/A          Original
*******************************************************************************/
#ifndef COMMON_C
#define COMMON_C
#endif
/* *****************************************************************************
   *****************************************************************************
   External Includes
   *****************************************************************************
   ***************************************************************************** */
#include 	"Common.h"
/* *****************************************************************************
   *****************************************************************************
   static variable declaration
   *****************************************************************************
   ***************************************************************************** */   
static uint16  mComm_u16TickCnt;

/* *****************************************************************************
   *****************************************************************************
   public function declaration
   *****************************************************************************
   ***************************************************************************** */
/* *****************************************************************************
   Function:        mDalay_Nms
   Description:     software delay for n ms
   Parameters:      Input:	delay:	Delay time (uint: ms)
                    Output:	None
   Notes:           
                   
   ***************************************************************************** */
void mDalay_Nms(uint32 delay)
{
	uint32 	i;
	while(delay--)
	{
		for(i=0; i<0x3E5C; i++) { }
	}
}
/* *****************************************************************************
   Function:        OverTimeCheckLong
   Description:     Check change of some Bit of Register (32Bit) in certain Count decided by DelayTime
   Parameters:      Input:	*pModuleSR:		Register (32bit)
   							checkMask:		Mask used for checking Bit
   							checkResult:	expect Result for checking
                    Output:	TRUE,			success
                    		FALSE,			failed
   Notes:           
                   
   ***************************************************************************** */
uint8 OverTimeCheckLong(volatile uint32 *pModuleSR, uint32 checkMask, uint32 checkResult, uint32 delayTime)
{
	uint8	StateRet;
	uint32	TimeOutCnt;
	
	StateRet = TRUE;
	TimeOutCnt = 0;

	while((*pModuleSR & checkMask) != checkResult)
	{
		TimeOutCnt++;
		if(TimeOutCnt > delayTime)
		{
			StateRet = FALSE;
			break;
		}
		else
		{
		}
	}
	
	return(StateRet);
}
/* *****************************************************************************
   Function:        OverTimeCheckLong_16U
   Description:     Check change of some Bit of Register (16Bit) in certain Count decided by DelayTime
   Parameters:      Input:	*pModuleSR:		Register (16bit)
   							checkMask:		Mask used for checking Bit
   							checkResult:	expect Result for checking
                    Output:	TRUE,			success
                    		FALSE,			failed
   Notes:           
                   
   ***************************************************************************** */
uint8 OverTimeCheckLong_16U(volatile uint16 *pModuleSR, uint32 checkMask, uint32 checkResult, uint32 delayTime)
{
	uint8	StateRet;
	uint32	TimeOutCnt;
	
	StateRet = TRUE;
	TimeOutCnt = 0;

	while((*pModuleSR & checkMask) != checkResult)
	{
		TimeOutCnt++;
		if(TimeOutCnt > delayTime)
		{
			StateRet = FALSE;
			break;
		}
		else
		{ }
	}
	
	return(StateRet);
}
/* *****************************************************************************
   Function:        Memory_Copy_Src_to_Dest
   Description:     Copy Data from Source to Dest
   Parameters:      Input:	*dest:		destination Array
   							*source:	Source Array
   							u16Len:		Size of Char
                    Output:	None
   Notes:           this Function Ref from memcpy(void *dest, const void *source, size_t n)
                   
   ***************************************************************************** */
void Memory_Copy_Src_to_Dest(uint8 *dest, uint8 *source, uint16 u16Len)
{
	while(u16Len>0)	
	{
		*dest = *source;
		dest++;
		source++;
		u16Len -- ;
	}
}
/* *****************************************************************************
   Function:        Memory_Set_Dest
   Description:     Set Value of dest to be Char_Val (uint8).
   Parameters:      Input:	*dest:		destination Array
   							Char_Val:	Char to be set in destination Array
   							u16Len:		Size of Char
                    Output:	None
   Notes:	uint8 Char_Val, if uint32 array used, *dest will be uint32.
   			for example, Char_Val = 0x01; dest[0] = 0x01010101; 
   			this Function Ref from memset(void *dest, int c, size_t n);                   
   ***************************************************************************** */
void Memory_Set_Dest(uint8 *dest, uint8 Char_Val, uint16 u16Len)
{
	while(u16Len>0)
	{
		*(uint8 *) dest = Char_Val;
		((uint8 *) dest)++;
		u16Len -- ;
	}
}
/* *****************************************************************************
   Function:    	mComm_vTimeInit      
   Description: 	get current tick counter   
   Parameters:      Input:    None
                    Output:   uint16 : timer counter now
   Notes:          

   ***************************************************************************** */
void mComm_vTimeInit(void)
{
    mComm_u16TickCnt = 0;
}
/* *****************************************************************************
   Function:    	mComm_vTimeTick      
   Description: 	get current tick counter   
   Parameters:      Input:    None
                    Output:   uint16 : timer counter now
   Notes:          

   ***************************************************************************** */
void mComm_vTimeTick(void)
{
    mComm_u16TickCnt++;
}
/* *****************************************************************************
   Function:    	mComm_u16GetCurrCnt      
   Description: 	get current tick counter   
   Parameters:      Input:    
                           startTimer: start timer
                           nowTimer  : timer counter now
                           timerOut  : timer out counter limit
                    Output:  
                           0:no timer out
                           1:timer out
   Notes: 

   ***************************************************************************** */
uint16 mComm_u16GetCurrCnt(void)
{
	return(mComm_u16TickCnt);
}
/* *****************************************************************************
   Function:		mComm_u8CheckTimeOut      
   Description:		get current tick counter   
   Parameters:      Input:    
                           startTimer: start timer
                           nowTimer  : timer counter now
                           timerOut  : timer out counter limit
                    Output:  
                           0:no timer out
                           1:timer out
   Notes:           
                   
   ***************************************************************************** */
uint8 mComm_u8CheckTimeOut(uint16 startTimer, uint16 nowTimer, uint16 timeOut)
{
	uint8	Ret = TIMER_TIME_IN;

	#define u16RegCnt  ((uint16) (startTimer+timeOut))

	if (u16RegCnt > startTimer)
	{
		if ((nowTimer >= u16RegCnt) || (nowTimer < startTimer))
		{
			Ret = TIMER_TIME_OUT;
		}
		else
		{
			/**/
		}
	}
	else if ((nowTimer >= u16RegCnt) && (nowTimer < startTimer))
	{
		Ret = TIMER_TIME_OUT;
	}
	else
	{
		/**/
	}
	#undef u16RegCnt

	return(Ret);
}
/* End of file */