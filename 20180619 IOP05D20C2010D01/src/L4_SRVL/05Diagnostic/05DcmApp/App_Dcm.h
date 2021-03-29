/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file   App_Dcm.h  
*
* @brief  Main header file of appplication diagnostic callback function.
*
********************************************************************************
*    Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0      2013/03/20    CODER1     N/A           Original
*     
*******************************************************************************/


#ifndef _APP_DCM_H_
#define _APP_DCM_H_

/******************************************************************************
 -----------------------------------------------------------------------------
 Include files
 -----------------------------------------------------------------------------
*******************************************************************************/
#include "DtcStatusManage.h"
//#include "pStateMachine.h"
//#include "hClbDataPri.h"
#include "Dcm.h"
#include "dDiagDec.h"


/*****************************************************************************************                           
 *                                  DID INFO Def              
 *****************************************************************************************/
/*-----------------------------------------------------------------------------
    &&~ DID Lenth Def
 -----------------------------------------------------------------------------*/
#define DID_F187_LEN                 (16u)
#define DID_F18A_LEN                 (10u)
#define DID_F18B_LEN                 (4u)
#define DID_F18C_LEN                 (14u)
#define DID_F190_LEN                 (17u)
#define DID_F193_LEN                 (18u)
#define DID_F195_LEN                 (20u)
#define DID_0100_LEN                 (16u)
#define DID_F010_LEN                 (35u)

#if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
	#define DID_F197_LEN                 (10u)
	#define DID_1C00_LEN                 (2u)
	#define DID_1C01_LEN                 (2u)
	#define DID_1C02_LEN                 (2u)
	#define DID_1C03_LEN                 (2u)
	#define DID_1C04_LEN                 (2u)
	#define DID_1C05_LEN                 (1u)
#endif



/*-----------------------------------------------------------------------------
    &&~  DID Storage Address 
 -----------------------------------------------------------------------------*/
/*
#define DID_ROM_START_ADDR            PRIVATE_DATA_ROM_START_ADDR
#define DID_RAM_START_ADDR            PRIVATE_DATA_START_ADDR

#define DID_F187_ADDR                (DID_RAM_START_ADDR)
#define DID_F18A_ADDR                (DID_F187_ADDR+DID_F187_LEN)
#define DID_F18B_ADDR                (DID_F18A_ADDR+DID_F18A_LEN)
#define DID_F18C_ADDR                (DID_F18B_ADDR+DID_F18B_LEN)
#define DID_F190_ADDR                (DID_F18C_ADDR+DID_F18C_LEN)
#define DID_F193_ADDR                (DID_F190_ADDR+DID_F190_LEN)
#define DID_F195_ADDR                (DID_F193_ADDR+DID_F193_LEN)
#define DID_0100_ADDR                (DID_F195_ADDR+DID_F195_LEN)
#define DID_F010_ADDR                (DID_0100_ADDR+DID_0100_LEN)


#if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
	#define DID_F197_ADDR                (DID_F010_ADDR+DID_F010_LEN)
	#define DID_1C00_ADDR                (DID_F197_ADDR+DID_F197_LEN)
	#define DID_1C01_ADDR                (DID_1C00_ADDR+DID_1C00_LEN)
	#define DID_1C02_ADDR                (DID_1C01_ADDR+DID_1C01_LEN)
	#define DID_1C03_ADDR                (DID_1C02_ADDR+DID_1C02_LEN)
	#define DID_1C04_ADDR                (DID_1C03_ADDR+DID_1C03_LEN)
	#define DID_1C05_ADDR                (DID_1C04_ADDR+DID_1C04_LEN)
#endif
// DID Pointer 
#define DID_F187                     ((uint8*)DID_F187_ADDR)
#define DID_F18A                     ((uint8*)(DID_F187_ADDR + DID_F187_LEN))
#define DID_F18B                     ((uint8*)(DID_F18A_ADDR + DID_F18A_LEN))
#define DID_F18C                     ((uint8*)(DID_F18B_ADDR + DID_F18B_LEN))
#define DID_F190                     ((uint8*)(DID_F18C_ADDR + DID_F18C_LEN))
#define DID_F193                     ((uint8*)(DID_F190_ADDR + DID_F190_LEN))
#define DID_F195                     ((uint8*)(DID_F193_ADDR + DID_F193_LEN))
#define DID_0100                     ((uint8*)(DID_F195_ADDR + DID_F195_LEN))
#define DID_F010                     ((uint8*)(DID_0100_ADDR + DID_0100_LEN))
#if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
	#define DID_F197                     ((uint8*)(DID_F010_ADDR + DID_F010_LEN))
	#define DID_1C00                (DID_F197_ADDR+DID_F197_LEN)
	#define DID_1C01                (DID_1C00_ADDR+DID_1C00_LEN)
	#define DID_1C02                (DID_1C01_ADDR+DID_1C01_LEN)
	#define DID_1C03                (DID_1C02_ADDR+DID_1C02_LEN)
	#define DID_1C04                (DID_1C03_ADDR+DID_1C03_LEN)
	#define DID_1C05                (DID_1C04_ADDR+DID_1C04_LEN)
#endif

*/
/*-----------------------------------------------------------------------------
    &&~  read handle for 22 
 -----------------------------------------------------------------------------*/
#define ReadHandle_F187              0u
#define ReadHandle_F18A              1u
#define ReadHandle_F18B              2u
#define ReadHandle_F18C              3u
#define ReadHandle_F190              4u
#define ReadHandle_F193              5u
#define ReadHandle_F195              6u
#define ReadHandle_100               7u
#define ReadHandle_F010              8u
#if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
	#define ReadHandle_F197              9u
	#define ReadHandle_1C00              10u
	#define ReadHandle_1C01              11u
	#define ReadHandle_1C02              12u
	#define ReadHandle_1C03              13u
	#define ReadHandle_1C04              14u
	#define ReadHandle_1C05              15u
#endif

#if(DCM_SERVICE_2A_ENABLED==STD_ON)
#define ReadHandle_F301              21u
#endif

/*-----------------------------------------------------------------------------
    &&~  for 27 
 -----------------------------------------------------------------------------*/
#define SecurityLevel1_Hanle         0u
#define SecurityLevel2_Hanle         1u
#define SecurityLevel3_Hanle         2u

//#define SECURITY_SEED_SIZE           2u
#define SECURITY_SEED_SIZE           4u
#if(SECURITY_SEED_SIZE == 2)
#define SECURITY_MASK_CODE_FIRST       0xE5
#define SECURITY_MASK_CODE_SECOND      0x31
#endif

#if(SECURITY_SEED_SIZE == 3)
#define SECURITY_MASK_CODE_FIRST       0xE5
#define SECURITY_MASK_CODE_SECOND      0x31
#define SECURITY_MASK_CODE_THIRD       0xF2
#endif

#if(SECURITY_SEED_SIZE == 4)
#define SECURITY_MASK_CODE_FIRST       0xE5
#define SECURITY_MASK_CODE_SECOND      0x31
#define SECURITY_MASK_CODE_THIRD       0xF2
#define SECURITY_MASK_CODE_FOURTH      0x69
#endif 

/*-----------------------------------------------------------------------------
    &&~  for 2E 
 -----------------------------------------------------------------------------*/
#define WriteHandle_F187             0u
#define WriteHandle_F18A             1u
#define WriteHandle_F18B             2u
#define WriteHandle_F18C             3u
#define WriteHandle_F190             4u
#define WriteHandle_F193             5u
#define WriteHandle_F195             6u
#define WriteHandle_100              7u
#define WriteHandle_F010             8u
#if(OBC_DCM_SERVICE_22_ENABLED==STD_ON)
	#define WriteHandle_F197             9u
	#define WriteHandle_1C00              10u
	#define WriteHandle_1C01              11u
	#define WriteHandle_1C02              12u
	#define WriteHandle_1C03              13u
	#define WriteHandle_1C04              14u
	#define WriteHandle_1C05              15u
#endif
/*-----------------------------------------------------------------------------
    &&~  Negative Code Def 
 -----------------------------------------------------------------------------*/
#define   DCM_NUM_POSITIVERESPONSE     0u
#define   DCM_NUM_GENERALREJECT        1u
#define   DCM_NUM_CONDITIONSNOTCORRECT 2u
#define   DCM_NUM_REQUESTOUTOFRANGE    3u

/* DTC mask */
#define DTCStatusAvailabilityMask      DTC_STATUS_MASK

#define ENABLE_OPERATION                    1u
#define DISABLE_OPERATION                   0u                  

/**************************************************************************************************
 * Global Variables
 **************************************************************************************************/
extern  uint32  gClrGroupOfDTC;
extern  uint8   u8EnCanRxAndTx;
extern  uint8   u8MsgType;
extern  uint32  u32FreRunCntrForRand;
/**************************************************************************************************
 * Application Callback Function Prototye
 **************************************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL==STD_ON)

extern Std_ReturnType App_DiagnosticActive(void);

#endif

#if(DCM_COSTOMIZED_SERVCIE_SUPPORTED==STD_ON)

extern void App_CustomizedServcie(Dcm_MsgContextType* pMsgContext);

#endif

#if(DCM_INTERNALTEST_SERVCIE_SUPPORTED==STD_ON)

extern void App_InternalTestServcie(uint8 subpara);

#endif

/* 10 */ 
extern void App_DefaultSession(Dcm_MsgContextType* pMsgContext);
extern void App_ProgramSession(Dcm_MsgContextType* pMsgContext);
extern void App_ExtendedSession(Dcm_MsgContextType* pMsgContext);
extern void App_DefaultSessionPost(Std_ReturnType Result);
extern void App_ProgramSessionPost(Std_ReturnType Result);
extern void App_ExtendedSessionPost(Std_ReturnType Result);

/* 11 */
extern void App_HardReset(Dcm_MsgContextType* pMsgContext);
extern void App_HardResetPost(Std_ReturnType Result);
extern void App_SoftReset(Dcm_MsgContextType* pMsgContext);
extern void App_SoftResetPost(Std_ReturnType Result);

/* 14 */
extern uint8 App_ClearDiagnosticInformation(Dcm_MsgContextType* pMsgContext);

/* 19 */ 
extern uint8 App_ReportNumberOfDTCByStatusMask(Dcm_MsgContextType* pMsgContext); /*0x01*/
extern uint8 App_ReportDTCByStatusMask(Dcm_MsgContextType* pMsgContext);         /*0x02*/
extern uint8 App_ReportSupportedDTC(Dcm_MsgContextType* pMsgContext);   /*0x0A*/

extern uint8 App_ReportDTCSnapshotIdentification(Dcm_MsgContextType* pMsgContext); /* 03 */
extern uint8 App_ReportDTCSnapshotRecordByDTCNumber(Dcm_MsgContextType* pMsgContext); /* 04 */
extern uint8 App_ReportDTCSnapshotRecordByRecordNumber(Dcm_MsgContextType* pMsgContext); /* 05 */
extern uint8 App_ReportDTCExtendedDataRecordByDTCNumber(Dcm_MsgContextType* pMsgContext);/* 06 */


/* 22 */
extern void App_ReadF187(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF18A(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF18B(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF18C(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF190(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF193(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF195(Dcm_MsgContextType* pMsgContext);
extern void App_Read0100(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF010(Dcm_MsgContextType* pMsgContext);
extern void App_ReadF197(Dcm_MsgContextType* pMsgContext);
extern void App_Read1C00(Dcm_MsgContextType* pMsgContext);
extern void App_Read1C01(Dcm_MsgContextType* pMsgContext);
extern void App_Read1C02(Dcm_MsgContextType* pMsgContext);
extern void App_Read1C03(Dcm_MsgContextType* pMsgContext);
extern void App_Read1C04(Dcm_MsgContextType* pMsgContext);
extern void App_Read1C05(Dcm_MsgContextType* pMsgContext);
/* 27 */
#if(DCM_SERVICE_27_ENABLED==STD_ON)
extern void App_GetSeed_L1(Dcm_MsgContextType* pMsgContext);
extern uint8 App_CompareKey_L1(Dcm_MsgContextType* pMsgContext);
#endif
/* 28 */
extern void App_EnableRxAndTx(Dcm_MsgContextType* pMsgContext);
extern void App_DisableRxAndTx(Dcm_MsgContextType* pMsgContext);

/* 2E */  
extern uint8 App_WriteF190(Dcm_MsgContextType* pMsgContext);
extern uint8 App_Write0100(Dcm_MsgContextType* pMsgContext);


extern uint8 App_WriteF187(Dcm_MsgContextType* pMsgContext);/*20130313 add for debug*/
extern uint8 App_WriteF18A(Dcm_MsgContextType* pMsgContext);
extern uint8 App_WriteF18B(Dcm_MsgContextType* pMsgContext);
extern uint8 App_WriteF18C(Dcm_MsgContextType* pMsgContext);
extern uint8 App_WriteF193(Dcm_MsgContextType* pMsgContext);
extern uint8 App_WriteF195(Dcm_MsgContextType* pMsgContext);
extern uint8 App_WriteF010(Dcm_MsgContextType* pMsgContext);
extern uint8 App_WriteF197(Dcm_MsgContextType* pMsgContext);
extern uint8 App_Write1C00(Dcm_MsgContextType* pMsgContext);
extern uint8 App_Write1C01(Dcm_MsgContextType* pMsgContext);
extern uint8 App_Write1C02(Dcm_MsgContextType* pMsgContext);
extern uint8 App_Write1C03(Dcm_MsgContextType* pMsgContext);
extern uint8 App_Write1C04(Dcm_MsgContextType* pMsgContext);
extern uint8 App_Write1C05(Dcm_MsgContextType* pMsgContext);

/* 2F */  
extern uint8 	App_2F_4C00_ReturnControlToEcuFnc(Dcm_MsgContextType* pMsgContext);
extern uint8 	App_2F_4C00_ResetToDefaultFnc(Dcm_MsgContextType* pMsgContext);
extern uint8 	App_2F_4C00_FreezeCurrentStateFnc(Dcm_MsgContextType* pMsgContext);
extern uint8 	App_2F_4C00_ShortTermAdjustmentFnc(Dcm_MsgContextType* pMsgContext);

/* 31 */  
extern uint8 App_31_startRoutine(Dcm_MsgContextType* pMsgContext);
/* 85 */
extern void App_DTCRecordOn(Dcm_MsgContextType* pMsgContext);
extern void App_DTCRecordOff(Dcm_MsgContextType* pMsgContext);

/* B0 */
extern void App_EchoRequest(Dcm_MsgContextType* pMsgContext);/*reserved*/

extern void SetDiagCondition(uint8 u8DiagCondition);
extern void SetIgnStatus(uint8 aIgnStatus);

#endif


/******************************************************* End  ******************************************************/