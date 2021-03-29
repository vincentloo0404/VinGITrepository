/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
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
*     1.0        2012/10/23      ----       N/A          Original
*     
************************************************************************************************/
#ifndef L3_SBCDRV_H
#define L3_SBCDRV_H 1

/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include	"Std_Types.h"
#include    "m_DSPI_Drv.h"


/*---------------------------------------------------------------------------*/
/***  SPI Interface configuration                                          ***/
/*---------------------------------------------------------------------------*/
#define SBC_SPI_MODULE        DSPI3
#define SBC_SPI_MODULE_CHN    DSPI_CS0
#define SBC_SPI_CTAR          CTAR0

/*---------------------------------------------------------------------------*/
/***  Enable or Disable the protection process while SBC_Cfg_Error occurs  ***/
/*---------------------------------------------------------------------------*/
/*#define SBC_CFG_FAIL_PROTECT_EN*/


/*---------------------------------------------------------------------------*/
/***   Define the Operation Period of Feeding WDT    Unit: ms              ***/
/*---------------------------------------------------------------------------*/
#define SBC_WDT_FEED_TICK_CN   64U   /*64 ms*/

/*---------------------------------------------------------------------------*/
/***    Normal Macro Defination                                            ***/
/*---------------------------------------------------------------------------*/
#define SBC_REGISTER_CLEAR   0x0000   /*register clear value*/
#define SBC_SPI_READ_FAULT   0xFFFF   /*diagnostic error value, No not Change*/

#define SBC_SPI_SW_DLAY_CN   0x000F   /*software delay counter of 'nop'*/
#define SBC_GLB_VARI_RESET   0x0000   /*variable reset value*/

#define SBC_RESET_FLAG_CLR   0x00

/*--------------------------------------------------------------------------*/
#ifndef SBC_SYS_EVENT_DIAG_BY_FBL
#define SBC_SYS_EVENT_DIAG_BY_SBC
#endif

/*--------------------------------------------------------------------------*/
#define SBC_REG_INIT_CFG_FAIL   0x01
#define SBC_REG_INIT_CFG_SUCC   0x00

#define SBC_DEVICE_RUN_UN_DEF   0x00
#define SBC_DEVICE_RUN_NORMAL   0x01


#define SBC_WDT_OVT_FLG_CLR   0x00
#define SBC_WDT_OVT_FLG_SET   0x01
#define SBC_WDT_OVT_FLG_UDF   0x02

#define SBC_WI_INT_FLG_CLR   0x00
#define SBC_WI_INT_FLG_SET   0x01
#define SBC_WI_INT_FLG_UDF   0x02


/*---------------------------------------------------------------------------*/
/***    bit15--------------------------------------bit11-------------bit0  ***/
/***    -15--14--13--12-------------------------------11-----------0-      ***/
/***    -0---0---0---[0 = read/write, 1 = read only]--WD_and_Status--      ***/
/***    -0---0---1---[0 = read/write, 1 = read only]--Mode_Control---      ***/
/***    -0---1---0---[0 = read/write, 1 = read only]--Int_Control----      ***/
/***    -0---1---1---[0 = read/write, 1 = read only]--Int_Status-----      ***/ 
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/***                 WD/MC/IC/IS  Register Operation Mask                  ***/
/*---------------------------------------------------------------------------*/
#define SBC_WD_ADD_MSK    0x0000  /*Watchdog and Status Register address*/
#define SBC_MC_ADD_MSK    0x2000  /*Mode Control Register address       */
#define SBC_IC_ADD_MSK    0x4000  /*Interrupt Control Register address  */
#define SBC_IS_ADD_MSK    0x6000  /*Interrupt Status Register address   */

#define SBC_WD_READ_MSK   0x1000  /*Watchdog and Status Register read mask*/
#define SBC_MC_READ_MSK   0x3000  /*Mode Control Register read mask       */
#define SBC_IC_READ_MSK   0x5000  /*Interrupt Control Register read mask  */
#define SBC_IS_READ_MSK   0x7000  /*Interrupt Status Register read mask   */

#define SBC_WD_WRITE_MSK  0xEFFF  /*Watchdog and Status Register write mask*/
#define SBC_MC_WRITE_MSK  0xEFFF  /*Mode Control Register write mask       */
#define SBC_IC_WRITE_MSK  0xEFFF  /*Interrupt Control Register write mask  */
#define SBC_IS_WRITE_MSK  0xEFFF  /*Interrupt Status Register write mask   */


/*---------------------------------------------------------------------------*/
/***                 WD_and_Status register                                ***/
/*---------------------------------------------------------------------------*/
#define SBC_WD_WMC_MSK    0x0800  /*Watchdog Mode Control*/ 
#define SBC_WD_NWP_MSK    0x0700  /*Nominal Watchdog Period*/


/*---------------------------------------------------------------------------*/
/***                 WD_and_Status register:watchdog period                ***/
/*---------------------------------------------------------------------------*/
#define SBC_WD_NWP_016    0x0100  /*016ms*/
#define SBC_WD_NWP_032    0x0200  /*032ms*/
#define SBC_WD_NWP_064    0x0300  /*064ms*/
#define SBC_WD_NWP_128    0x0400  /*128ms*/
#define SBC_WD_NWP_256    0x0500  /*256ms*/

#define SBC_WD_WOS_MSK    0x0080  /*Watchdog Off Status*/

#define SBC_WD_SWR_MSK    0x0080  /*Software Reset*/

#define SBC_WD_V1S_MSK    0x0040  /*V1 Status*/
#define SBC_WD_V2S_MSK    0x0020  /*V2 Status; not available for UJA1079A*/
#define SBC_WD_WLS1_MSK   0x0010  /*Wake-Up Status 1*/
#define SBC_WD_WLS2_MSK   0x0008  /*Wake-Up Status 2*/


/*---------------------------------------------------------------------------*/
/***                 Mode_Control register                                 ***/
/*---------------------------------------------------------------------------*/
#define SBC_MC_MC_MSK      0x0C00  /*Mode Control*/


/*---------------------------------------------------------------------------*/
/***                 Mode_Control register  :SBC Mode Control              ***/
/*---------------------------------------------------------------------------*/
#define SBC_MC_MC_STANDBY   0x0000  /*Mode Control mask for Standby Mode (MC = 0)*/
#define SBC_MC_MC_SLEEP     0x0400  /*Mode Control mask for Sleep   Mode (MC = 1)*/
#define SBC_MC_MC_V2OFF     0x0800  /*Mode Control mask for Normal Mode with disabled V2 (MC = 2)*/
#define SBC_MC_MC_NORMAL    0x0c00  /*Mode Control mask for Normal Mode with enabled  V2 (MC = 3)*/

#define SBC_MC_LHWC_MSK    0x0200  /*Limp Home Warning Control*/
#define SBC_MC_LHC_MSK     0x0100  /*Limp Home Control*/
#define SBC_MC_ENC_MSK     0x0080  /*Enable Control*/

#define SBC_MC_WBC_MSK     0x0020  /* Wake Bias Control*/
#define SBC_MC_PDC_MSK     0x0010  /* Power Distribution Control*/


/*---------------------------------------------------------------------------*/
/***                 Int_Control register                                  ***/
/*---------------------------------------------------------------------------*/
#define SBC_IC_V1UIE_MSK   0x0800   /*V1 Undervoltage Interrupt Enable*/
#define SBC_IC_V2UIE_MSK   0x0400   /* V2 Undervoltage Interrupt Enable*/


/*Wake-Up Interrupt 1 Control*/
#define SBC_IC_WIC1_MSK           0x00C0  
#define SBC_IC_WIC1_DISANLE       0xFF3F
#define SBC_IC_WIC1_RISING_EDGE   0x0040
#define SBC_IC_WIC1_FALLING_EDGE  0x0080
#define SBC_IC_WIC1_BOTH_EDGE     0x00C0   /*wake-up interrupt 1 on both edges*/

/*Wake-Up Interrupt 2 Control*/
#define SBC_IC_WIC2_MSK           0x0030
#define SBC_IC_WIC2_DISANLE       0xFFCF
#define SBC_IC_WIC2_RISING_EDGE   0x0010
#define SBC_IC_WIC2_FALLING_EDGE  0x0020
#define SBC_IC_WIC2_BOTH_EDGE     0x0030   /*wake-up interrupt 1 on both edges*/


#define SBC_IC_STBCC_MSK 0x0008    /* CAN Standby Control; not available for UJA1079A*/
#define SBC_IC_RTHC_MSK  0x0004    /* Reset Threshold Control*/
#define SBC_IC_WSE1_MSK  0x0002    /* WAKE1 Sample Enable*/
#define SBC_IC_WSE2_MSK  0x0001    /*WAKE2 Sample Enable*/


/*---------------------------------------------------------------------------*/
/***                  Int_Status register                                  ***/
/*---------------------------------------------------------------------------*/
#define SBC_IS_V1UI_MSK    0x0800    /*V1 Undervoltage Interrupt*/
#define SBC_IS_V2UI_MSK    0x0400    /*V2 Undervoltage Interrupt*/

#define SBC_IS_CI_MSK      0x0080    /*cyclic interrupt*/
#define SBC_IS_WI1_MSK     0x0040    /*wake-up interrupt 1*/
#define SBC_IS_POSI_MSK    0x0020    /*power-on status interrupt*/
#define SBC_IS_WI2_MSK     0x0010    /*wake-up interrupt 2*/
#define SBC_IS_CWI_MSK     0x0008    /*CAN wake-up interrupt*/


/*---------------------------------------------------------------------------*/
/***             Normal Macro Defination                                   ***/
/*---------------------------------------------------------------------------*/
#define  SBC_IS_V_BIT_SHIFT   6U
#define  SBC_IS_E_BIT_SHIFT   4U
#define  SBC_WD_V_BIT_SHIFT   3U

/*--------------------------------------------------------------------------*/
#define SBC_WD_REG_VXS_ST      SBC_WD_V2S_MSK


/*---------------------------------------------------------------------------*/
/***             UJA1076A  Config CMD-Prefix-Macro Defination              ***/
/*---------------------------------------------------------------------------*/
#define SBC_READ_WD_CMD_PREFIX  (SBC_WD_ADD_MSK | SBC_WD_READ_MSK) 
#define SBC_READ_MC_CMD_PREFIX  (SBC_MC_ADD_MSK | SBC_MC_READ_MSK)
#define SBC_READ_IC_CMD_PREFIX  (SBC_IC_ADD_MSK | SBC_IC_READ_MSK)
#define SBC_READ_IS_CMD_PREFIX  (SBC_IS_ADD_MSK | SBC_IS_READ_MSK)

/*--------------------------------------------------------------------------*/
#define SBC_WRITE_WD_CMD_PREFIX  (SBC_WD_ADD_MSK & SBC_WD_WRITE_MSK)
#define SBC_WRITE_MC_CMD_PREFIX  (SBC_MC_ADD_MSK & SBC_MC_WRITE_MSK)
#define SBC_WRITE_IC_CMD_PREFIX  (SBC_IC_ADD_MSK & SBC_IC_WRITE_MSK)
#define SBC_WRITE_IS_CMD_PREFIX  (SBC_IS_ADD_MSK & SBC_IS_WRITE_MSK)

/*---------------------------------------------------------------------------*/
/***                   UJA1076A  abridged Config-CMD                       ***/
/*---------------------------------------------------------------------------*/
#define SBC_READ_WD_REG_CMD     SBC_READ_WD_CMD_PREFIX 
#define SBC_READ_MC_REG_CMD     SBC_READ_MC_CMD_PREFIX
#define SBC_READ_IC_REG_CMD     SBC_READ_IC_CMD_PREFIX
#define SBC_READ_IS_REG_CMD     SBC_READ_IS_CMD_PREFIX


/*---------------------------------------------------------------------------*/
/***                   UJA1076A  Unabridged Config-CMD                     ***/
/*---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
WMC   = 1
NWP = 011
WOS   = 0
----------------------------------------------------------------------------*/
#define SBC_WRITE_WD_REG_CMD (SBC_WRITE_WD_CMD_PREFIX |\
                              SBC_WD_WMC_MSK |\
                              SBC_WD_NWP_256)
/*----------------------------------------------------------------------------
MC  = 11
LHWC = 0
LHC  = 0
ENC  = 1
WBC  = 0
PDC  = 1                              
----------------------------------------------------------------------------*/
#if 1
#define SBC_WRITE_MC_REG_CMD (SBC_WRITE_MC_CMD_PREFIX |\
                              SBC_MC_MC_NORMAL |\
                              SBC_MC_ENC_MSK  |\
                              SBC_MC_PDC_MSK)
#endif
/*
#define SBC_WRITE_MC_REG_CMD (SBC_WRITE_MC_CMD_PREFIX |\
                              SBC_MC_MC_NORMAL |\
                              SBC_MC_ENC_MSK  |\
                              0)
*/
/*----------------------------------------------------------------------------
V1UIE = 1
V2UIE = 1
WIC1 = 01
WIC2 = 01
STBCC = 0
RTHC  = 0
WSE1  = 0
WSE2  = 0
----------------------------------------------------------------------------*/
#define SBC_WRITE_IC_REG_CMD  (SBC_WRITE_IC_CMD_PREFIX |\
                               SBC_IC_V1UIE_MSK |\
                               SBC_IC_V2UIE_MSK |\
                               SBC_IC_WIC1_RISING_EDGE |\
                               SBC_IC_WIC2_RISING_EDGE)

/*----------------------------------------------------------------------------
V1UI = 1
V2UI = 1
CI   = 1
WI1  = 1
POSI = 1
WI2  = 1
CWI  = 1
----------------------------------------------------------------------------*/

#define SBC_WRITE_IS_REG_CMD  (SBC_WRITE_IS_CMD_PREFIX |\
                               SBC_IS_V1UI_MSK |\
                               SBC_IS_V2UI_MSK |\
                               SBC_IS_CI_MSK   |\
                               SBC_IS_WI1_MSK  |\
                               SBC_IS_POSI_MSK |\
                               SBC_IS_WI2_MSK  |\
                               SBC_IS_CWI_MSK)                              
/*----------------------------------------------------------------------------
V1UI = 0
V2UI = 0
CI   = 0
WI1  = 0
POSI = 0
WI2  = 0
CWI  = 0
----------------------------------------------------------------------------*/
#define SBC_WRITE_IS_REG_CHK  (SBC_WRITE_IS_CMD_PREFIX)


/*---------------------------------------------------------------------------*/
/***             SBC Register Write And Read Check CMD                     ***/
/*---------------------------------------------------------------------------*/
#define SBC_WD_WR_RE_CHECK_MSK  (SBC_WD_ADD_MSK |\
                                 SBC_WD_WMC_MSK |\
                                 SBC_WD_NWP_MSK |\
                                 SBC_WD_WOS_MSK)
/*--------------------------------------------------------------------------*/                                 
#define SBC_MC_WR_RE_CHECK_MSK  (SBC_MC_ADD_MSK  |\
                                 SBC_MC_MC_MSK   |\
                                 SBC_MC_LHWC_MSK |\
                                 SBC_MC_LHC_MSK  |\
                                 SBC_MC_ENC_MSK  |\
                                 SBC_MC_WBC_MSK  |\
                                 SBC_MC_PDC_MSK)
/*--------------------------------------------------------------------------*/                                 
#define SBC_IC_WR_RE_CHECK_MSK  (SBC_IC_ADD_MSK |\
                                 SBC_IC_V1UIE_MSK |\
                                 SBC_IC_V2UIE_MSK |\
                                 SBC_IC_WIC1_MSK  |\
                                 SBC_IC_WIC2_MSK  |\
                                 SBC_IC_STBCC_MSK |\
                                 SBC_IC_RTHC_MSK  |\
                                 SBC_IC_WSE1_MSK  |\
                                 SBC_IC_WSE2_MSK)
/*--------------------------------------------------------------------------*/                                
#define SBC_IS_WR_RE_CHECK_MSK  (SBC_IS_ADD_MSK  |\
                                 SBC_IS_V1UI_MSK |\
                                 SBC_IS_V2UI_MSK |\
                                 SBC_IS_CI_MSK   |\
                                 SBC_IS_WI1_MSK  |\
                                 SBC_IS_POSI_MSK |\
                                 SBC_IS_WI2_MSK  |\
                                 SBC_IS_CWI_MSK)

/*---------------------------------------------------------------------------*/
/***             Normal Macro Defination                                   ***/
/*---------------------------------------------------------------------------*/                                 
#define SBC_MC_CFG_COPY_MSK  (SBC_MC_LHWC_MSK |\
                              SBC_MC_LHC_MSK  |\
                              SBC_MC_ENC_MSK  |\
                              SBC_MC_WBC_MSK  |\
                              SBC_MC_PDC_MSK)
                                
/*--------------------------------------------------------------------------*/                                
#define SBC_INIT_MODE_CHECK_MSK  (SBC_MC_ADD_MSK | SBC_MC_MC_MSK)
#define SBC_POW_ON_DFL_MODE_MSK  (SBC_MC_ADD_MSK | SBC_MC_MC_STANDBY)                 

/*--------------------------------------------------------------------------*/ 
#define SBC_SW_RESET_EPS_CMD  (SBC_WRITE_WD_CMD_PREFIX | SBC_WD_WMC_MSK | SBC_WD_SWR_MSK)

/*--------------------------------------------------------------------------*/
#define SBC_CLA_ISR_EVENT_CMD (SBC_WRITE_IS_CMD_PREFIX |\
                               SBC_IS_V1UI_MSK |\
                               SBC_IS_V2UI_MSK |\
                               SBC_IS_CI_MSK   |\
                               SBC_IS_WI1_MSK  |\
                               SBC_IS_POSI_MSK |\
                               SBC_IS_WI2_MSK  |\
                               SBC_IS_CWI_MSK )
 
/*--------------------------------------------------------------------------*/                              
#define SBC_ENTER_SLEEP_MD_CMD (SBC_WRITE_MC_CMD_PREFIX |\
                                SBC_MC_MC_SLEEP |\
                                SBC_MC_ENC_MSK  |\
                                SBC_MC_PDC_MSK)
/*--------------------------------------------------------------------------*/                                
#define SBC_WDT_EVENT_CLR_CMD  (SBC_WRITE_IS_CMD_PREFIX | SBC_IS_CI_MSK)

#define SBC_WI_EVENT_CLR_CMD   (SBC_WRITE_IS_CMD_PREFIX | SBC_IS_WI1_MSK | SBC_IS_WI2_MSK)
                                                                
/*--------------------------------------------------------------------------*/
#define SBC_SPI_RW_2REG_SUCC   (TRUE + TRUE)
#define SBC_SPI_RW_4REG_SUCC   (TRUE + TRUE + TRUE + TRUE)


/*---------------------------------------------------------------------------*/
/***          EPS Reset reason diagnostic mask                             ***/
/*---------------------------------------------------------------------------*/        
#define SBC_EPS_RESET_BY_POW_UP   0x02
#define SBC_EPS_RESET_BY_WDT_OVT  0x08
#define SBC_EPS_RESET_BY_BAT_LOW  0x20
#define SBC_EPS_RESET_BY_IGN_ON   0x05

/*---------------------------------------------------------------------------*/
/***          Diagnostic Code of SPI Communication and configuration       ***/
/*---------------------------------------------------------------------------*/
#define SBC_DIAG_READ_BEFOR_CFG_FAIL  0x01
#define SBC_DIAG_CUR_WORK_MODE_WRONG  0x02
#define SBC_DIAG_TARGET_MODE_CFG_ERR  0x04
#define SBC_DIAG_CURRENT_CFG_CHK_ERR  0x08

#define SBC_DIAG_REGISTER_WR_RE_FAIL  0x10
#define SBC_DIAG_CFG_CONDITION_WRONG  0x20
#define SBC_DIAG_WDT_OPT_NOT_SUPPORT  0x40
#define SBC_DIAG_WDT_FEED_MAY_WARONG  0x80



/*---------------------------------------------------------------------------*/
/***                 Reset reason for user                                 ***/
/*---------------------------------------------------------------------------*/
#define SBC_EPS_RST_DIG_FAIL 0x00   /*Reset events check fail*/

#define SBC_EPS_POW_UP_RST   0x01   /*Power on reset*/
#define SBC_EPS_BAT_LOW_RST  0x02   /*Battery Low power state*/
#define SBC_EPS_WDT_OVT_RST  0x03   /*Watchdog overflow*/
#define SBC_EPS_USER_SW_RST  0x04   /*User software reset*/
#define SBC_EPS_IGN_ON_RST   0x05   /*Wakeup after Sleep*/

#define SBC_EPS_UN_DEF_RST   0x06   /*Reset Caused by unknown reason*/


/* macro definition */  

#define SbcTxRx(x,y) mDSPI_Data_TxRx16_CTAS(SBC_SPI_MODULE, SBC_SPI_MODULE_CHN, SBC_SPI_CTAR, (x), (y))



/* AD sample value */

/* ad value count */


/* signal */


/* function */
extern void SBC_L3_Init(void);
extern void SBC_L3_Per(void);
extern void SBC_L3_CfgSleepMode(void);
extern uint8 SBC_L3_CheckWakeupIntEvent(void);

#endif					
