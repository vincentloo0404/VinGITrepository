/*****************************************************************************
*   Copyright 2010 - 2011  
*   Co., Ltd., all rights reserved.
*
*   Filename:    L3_Data.h
*
*   Description: calibration data address defination
*
*   Revision History:
*
*   Date            Author          Description
*   ----------      ----------      -----------------------------------------
*   2016-10-27      Jiao Yu          Initial created
*
*****************************************************************************/
#ifndef L3_DATA_H
#define L3_DATA_H  1

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/
/* ignition */ 
#define k_S_IgnOnTimeOut_Ct_u08                  (*((uint8*)(0x40000100)))
#define k_S_IgnOffTimeOut_Ct_u08                 (*((uint8*)(0x40000101)))
#define k_S_IgnOnVoltThre_Volt_u16p10           (*((uint16*)(0x40000102)))  /* 4v */
#define k_S_IgnOffVoltThre_Volt_u16p10          (*((uint16*)(0x40000104)))  /* 1.5v */
										     
/* over write */						     
#define k_N_VehSpdOvrEn_Uls_u08                   (*(uint8*)(0x4000010D)) 
#define k_N_VehSpdOvrVal_kph_u16p01	             (*(uint16*)(0x4000010E))
#define k_N_EngSpdOvrVal_rpm_u16	             (*(uint16*)(0x40000110))
#define k_N_EngSpdOvrEn_Uls_u08		              (*(uint8*)(0x40000112))
#define k_N_IgnOvrEn_Uls_u08		              (*(uint8*)(0x40000113))
#define k_N_IgnOvrVal_Uls_u08		              (*(uint8*)(0x40000114))

/* Resolver Power Supply diag */						       
#define k_S_EnRslvVccDiag_Uls_u16               (*((uint16*)(0x40000132)))
#define k_S_RslvVccLowTh_V_u16p08               (*((uint16*)(0x40000134)))
#define k_S_RslvVccHighTh_V_u16p08              (*((uint16*)(0x40000136)))
#define k_S_RslvVccLowCntIncStep_Ct_u8           (*((uint8*)(0x40000138)))
#define k_S_RslvVccLowCntDecStep_Ct_u8           (*((uint8*)(0x40000139)))
#define k_S_RslvVccLowConfirmCntTh_Ct_u16       (*((uint16*)(0x4000013A)))
#define k_S_RslvVccHighCntIncStep_Ct_u8          (*((uint8*)(0x4000013C)))
#define k_S_RslvVccHighCntDecStep_Ct_u8          (*((uint8*)(0x4000013D)))
#define k_S_RslvVccHighConfirmCntTh_Ct_u16      (*((uint16*)(0x4000013E)))
										       
/* sensor5v diag */						       
#define k_S_EnSenVoltDiag_Uls_u16               (*((uint16*)(0x40000140)))
#define k_S_SenVoltLowTh_V_u16p08               (*((uint16*)(0x40000142)))
#define k_S_SenVoltHighTh_V_u16p08              (*((uint16*)(0x40000144)))
#define k_S_SenVoltLowCntIncStep_Ct_u8           (*((uint8*)(0x40000146)))
#define k_S_SenVoltLowCntDecStep_Ct_u8           (*((uint8*)(0x40000147)))
#define k_S_SenVoltLowConfirmCntTh_Ct_u16       (*((uint16*)(0x40000148)))
#define k_S_SenVoltHighCntIncStep_Ct_u8          (*((uint8*)(0x4000014A)))
#define k_S_SenVoltHighCntDecStep_Ct_u8          (*((uint8*)(0x4000014B)))
#define k_S_SenVoltHighConfirmCntTh_Ct_u16      (*((uint16*)(0x4000014C)))
										       
/* battery voltage diag */				      
#define k_S_EnBatVoltDiag_Uls_u16               (*((uint16*)(0x4000014E)))
#define k_S_BatOffStateEnterLimit_V_u16p08      (*((uint16*)(0x40000150)))
#define k_S_BatOffStateExitLimit_V_u16p08       (*((uint16*)(0x40000152)))
#define k_S_BatLowStateEnterLimit_V_u16p08      (*((uint16*)(0x40000154)))
#define k_S_BatLowStateExitLimit_V_u16p08       (*((uint16*)(0x40000156)))
#define k_S_BatNormal1StateEnterLimit_V_u16p08  (*((uint16*)(0x40000158)))
#define k_S_BatNormal1StateExitLimit_V_u16p08   (*((uint16*)(0x4000015A)))
#define k_S_BatOver1StateEnterLimit_V_u16p08    (*((uint16*)(0x4000015C)))
#define k_S_BatOver1StateExitLimit_V_u16p08     (*((uint16*)(0x4000015E)))
#define k_S_BatOver2StateEnterLimit_V_u16p08    (*((uint16*)(0x40000160)))
#define k_S_BatOver2StateExitLimit_V_u16p08     (*((uint16*)(0x40000162)))
#define k_S_BatErrCntIncStep_Ct_u8              (*((uint16*)(0x40000164)))
#define k_S_BatErrCntDecStep_Ct_u8              (*((uint16*)(0x40000165)))
#define k_S_BatOffConfirmCntTh_Ct_u16           (*((uint16*)(0x40000166)))
#define k_S_BatOffClearCntTh_Ct_u16             (*((uint16*)(0x40000168)))
#define k_S_BatLowConfirmCntTh_Ct_u16           (*((uint16*)(0x4000016A)))
#define k_S_BatLowClearCntTh_Ct_u16             (*((uint16*)(0x4000016C)))
#define k_S_BatNormal1ConfirmCntTh_Ct_u16       (*((uint16*)(0x4000016E)))
#define k_S_BatNormal1ClearCntTh_Ct_u16         (*((uint16*)(0x40000170)))
#define k_S_BatOver1ConfirmCntTh_Ct_u16         (*((uint16*)(0x40000172)))
#define k_S_BatOver1ClearCntTh_Ct_u16           (*((uint16*)(0x40000174)))
#define k_S_BatOver2ConfirmCntTh_Ct_u16         (*((uint16*)(0x40000176)))
#define k_S_BatOver2ClearCntTh_Ct_u16           (*((uint16*)(0x40000178)))

/* Temperature Sensor Diag */
#define k_S_TempSenDiagENbFlg_Uls_u16           (*((uint16*)(0x4000017A)))
#define k_S_TempSenShGndLmt_Cnt_u16			    (*((uint16*)(0x4000017C)))
#define k_S_TempSenShVcLmt_Cnt_u16			    (*((uint16*)(0x4000017E)))
#define k_S_TempSenHighUpLmt_Deg_s16p01		    (*((sint16*)(0x40000180)))
#define k_S_TempSenHighDnLmt_Deg_s16p01		    (*((sint16*)(0x40000182)))
#define k_S_TempSenLowLmt_Deg_s16p01		    (*((sint16*)(0x40000184)))
#define k_S_TempSenShGndCntIncStep_Ct_u8	     (*((uint8*)(0x40000186)))
#define k_S_TempSenShGndCntDecStep_Ct_u8	     (*((uint8*)(0x40000187)))
#define k_S_TempSenShGndConfirmCntTh_Ct_u16	    (*((uint16*)(0x40000188)))
#define k_S_TempSenShVcCntIncStep_Ct_u8		     (*((uint8*)(0x4000018A)))
#define k_S_TempSenShVcCntDecStep_Ct_u8		     (*((uint8*)(0x4000018B)))
#define k_S_TempSenShVcConfirmCntTh_Ct_u16	    (*((uint16*)(0x4000018C)))
#define k_S_TempSenHighCntIncStep_Ct_u8		     (*((uint8*)(0x4000018E)))
#define k_S_TempSenHighCntDecStep_Ct_u8		     (*((uint8*)(0x4000018F)))
#define k_S_TempSenHighConfirmCntTh_Ct_u16	    (*((uint16*)(0x40000190)))
#define k_S_TempSenLowCntIncStep_Ct_u8		     (*((uint8*)(0x40000192)))
#define k_S_TempSenLowCntDecStep_Ct_u8		     (*((uint8*)(0x40000193)))
#define k_S_TempSenLowConfirmCntTh_Ct_u16	    (*((uint16*)(0x40000194)))

/* motor terminal volt diag */
#define k_S_EnMtrPhaseVoltDiag_Uls_u16          (*((uint16*)(0x400001DA)))
#define k_S_MtrVoltDiffLim_Uls_u16p10           (*((uint16*)(0x400001DC)))
#define k_S_MtrVoltErrCntIncStep_Ct_u8           (*((uint8*)(0x400001DE)))
#define k_S_MtrVoltErrCntDecStep_Ct_u8           (*((uint8*)(0x400001DF)))
#define k_S_MtrVoltErrConfirmCntTh_Ct_u16       (*((uint16*)(0x400001E0)))
#define k_S_MtrVoltErrMotSpdThr_rpm_u16         (*((uint16*)(0x400001E2)))
										      
/* ignition diag */						      
#define k_S_EnIgnVoltDiag_Uls_u16               (*((uint16*)(0x400001E4)))
#define k_S_IgnVoltErrConfirmCntTh_Ct_u16       (*((uint16*)(0x400001E6)))
#define k_S_IgnVoltErrCntIncStep_Ct_u8           (*((uint8*)(0x400001E8)))
#define k_S_IgnVoltErrCntDecStep_Ct_u8           (*((uint8*)(0x400001E9)))

/* PreDriver Diag */
#define k_S_EnPreDrvDiag_Uls_u16                   (*((uint16*)(0x400001EA)))
#define k_S_PreDrvUnderVoltCntIncStep_Ct_u8		    (*((uint8*)(0x400001EC)))
#define k_S_PreDrvUnderVoltCntDecStep_Ct_u8		    (*((uint8*)(0x400001ED)))
#define k_S_PreDrvUnderVoltConfirmCntTh_Ct_u16	   (*((uint16*)(0x400001EE)))
#define k_S_PreDrvShortCircuitCntIncStep_Ct_u8	    (*((uint8*)(0x400001F0)))
#define k_S_PreDrvShortCircuitCntDecStep_Ct_u8	    (*((uint8*)(0x400001F1)))
#define k_S_PreDrvShortCircuitConfirmCntTh_Ct_u16  (*((uint16*)(0x400001F2)))
#define k_S_PreDrvOverVoltTempCntIncStep_Ct_u8	    (*((uint8*)(0x400001F4)))
#define k_S_PreDrvOverVoltTempCntDecStep_Ct_u8	    (*((uint8*)(0x400001F5)))
#define k_S_PreDrvOverVoltTempConfirmCntTh_Ct_u16  (*((uint16*)(0x400001F6)))
										       
/* resolver diag */						       
#define k_S_Rslv_DiagEn_Ct_u8                      (*(uint8*)(0x400001F8))
#define k_S_RslvAmpErrConfirmCntTh_Ct_u16         (*(uint16*)(0x400001FC))
#define k_S_RslvAmpErrCnDecStep_Ct_u8	           (*(uint8*)(0x400001FE))
#define k_S_RslvAmpCnIncStep_Ct_u8		           (*(uint8*)(0x400001FF))
#define k_S_RslvSynErrConfirmCntTh_Ct_u16         (*(uint16*)(0x40000200))
#define k_S_RslvSynErrCnDecStep_Ct_u8	           (*(uint8*)(0x40000202))
#define k_S_RslvSynErrCnIncStep_Ct_u8	           (*(uint8*)(0x40000203))
#define k_S_RslvVoltErrConfirmCntTh_Ct_u16        (*(uint16*)(0x40000204))
#define k_S_RslvVoltErrCnDecStep_Ct_u8	           (*(uint8*)(0x40000206))
#define k_S_RslvVoltErrCnIncStep_Ct_u8		       (*(uint8*)(0x40000207))

/* Tas T1&2 Diag */
#define k_S_TAS_DiagEn_Ct_u8                       (*(uint8*)(0x400002D4))
#define k_S_TAS_T12_TimeOut_Ct_u16		          (*(uint16*)(0x400002D6))
#define k_S_T12FreqErrConfirmCntTh_Ct_u16         (*(uint16*)(0x400002D8))
#define k_S_T12FreqErrCnDecStep_Ct_u8	           (*(uint8*)(0x400002DA))
#define k_S_T12FreqErrCnIncStep_Ct_u8	           (*(uint8*)(0x400002DB))
#define k_S_T12DutyErrConfirmCntTh_Ct_u16         (*(uint16*)(0x400002DC))
#define k_S_T12DutyErrCnDecStep_Ct_u8	           (*(uint8*)(0x400002DE))
#define k_S_T12DutyErrCnIncStep_Ct_u8	           (*(uint8*)(0x400002DF))
#define k_S_T12SynErrConfirmCntTh_Ct_u16          (*(uint16*)(0x400002E0))
#define k_S_T12SynErrCnDecStep_Ct_u8	           (*(uint8*)(0x400002E2))
#define k_S_T12SynErrCnIncStep_Ct_u8	           (*(uint8*)(0x400002E3))
										        
#endif									        
/* End of L3_Data.h file*/				        
										        
										        
