/******************************************************************************
*
* ChuangQu NewEnergy .
* (c) Copyright 2014 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*
*
* @file     
*
* @brief    
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2014/12/20      ----    	   	N/A          Original
************************************************************************************************/
#ifndef L4_SCHEDULEMANAGEMENT_H
#define L4_SCHEDULEMANAGEMENT_H  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Std_Types.h"

#include "L4_ScheduleManagement_Cfg.h"

#include "L4_WarmTask.h"
#include "L4_RunTask.h"
#include "L4_StopTask.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
/*Type for Task management*/
typedef struct
{
    /*time slice counter of Task*/
    uint16 Task_ExecuteCounter_u16;
    /*Period for Task execution*/
    uint16 Task_ExecutePeriod_u16;
    /*function call*/
    void (*TaskFunction)(void);
}TaskType_Str;

typedef void (*PFCN_VOID_VOID)(void); /* pointer to function,no parameter and no output */

/*****************************************************************************
*   Global Macros Definitions
*****************************************************************************/

/*****************************************************************************
*   Global Data Declarations
*****************************************************************************/
extern uint16 L4_S_Loop_Ct_u16;
extern TaskType_Str L4_S_Task_G_Str[d_MaxTaskNumber_u16];

/*****************************************************************************
*   Global Function Declarations
*****************************************************************************/
extern void ScheduleManagement_L4_ColdInit(void);
extern void ScheduleManagement_L4_WarmInit(void);
extern void ScheduleManagement_L4_RunInit(void);
extern void ScheduleManagement_L4_StopInit(void);
extern void ScheduleManagement_L4_Per(void);

#endif
/*End of L4_ScheduleManagement.h file*/
