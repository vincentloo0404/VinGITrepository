/******************************************************************************
*
* Lingtong Tech Inc.
* (c) Copyright 2012 Lingtong Tech, Inc.
* ALL RIGHTS RESERVED.
*
*******************************************************************************
*
* @file     m_Flash_Drv.h
*
* @brief    Drive Header file for "m_Flash_Drv.c"
*
************************************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2012/11/15      CODER21983       N/A          Original
************************************************************************************************/
#ifndef _M_FLASH_DRV_H_
#define _M_FLASH_DRV_H_


#ifdef 	M_FLASH_DRV_C
#define M_FLASH_DRV_EXT
#else
#define M_FLASH_DRV_EXT 	extern
#endif


/* *****************************************************************************
   *****************************************************************************
   Include files
   *****************************************************************************
   ***************************************************************************** */
#include 	"Common.h"


/* *****************************************************************************
   *****************************************************************************
   Drive Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	register Address define											   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_BASE_ADDRESS				0xFFE8C000ul
#define 	FLASH_MCR_OFFSET				0x0ul
#define 	FLASH_LML_OFFSET				0x4ul
#define 	FLASH_SLL_OFFSET				0xCul
#define 	FLASH_LMS_OFFSET				0x10ul
#define 	FLASH_ADR_OFFSET				0x18ul
#define 	FLASH_PFCR0_OFFSET				0x1Cul
#define 	FLASH_PFCR1_OFFSET				0x20ul
#define 	FLASH_PFAPR_OFFSET				0x24ul
#define 	FLASH_UT0_OFFSET				0x3Cul
#define 	FLASH_UT1_OFFSET				0x40ul
#define 	FLASH_UT2_OFFSET				0x44ul
#define 	FLASH_UMISR_OFFSET(x)			(0x48ul+(x)*0x4)
#define 	FLASH_NVLML_OFFSET				0x403DE8ul	/* CodeFlash Only, TestFlash */
#define 	FLASH_NVSLL_OFFSET				0x403DF8ul	/* CodeFlash Only, TestFlash */
#define 	FLASH_NVPWD0_ADDRESS			0x203DD8ul	/* CodeFlash Only, ShadowFlash */
#define 	FLASH_NVPWD1_ADDRESS			0x203DDCul	/* CodeFlash Only, ShadowFlash */
#define 	FLASH_NVSCI0_ADDRESS			0x203DE0ul	/* CodeFlash Only, ShadowFlash */
#define 	FLASH_NVSCI1_ADDRESS			0x203DE4ul	/* CodeFlash Only, ShadowFlash */
#define 	FLASH_NVUSRO_ADDRESS			0x203E18ul	/* CodeFlash Only, ShadowFlash */

/*---------------------------------------------------------------------------*/
/***	Data Flash Block 0--3 Base Address								   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_D_ARRAY_BASE0_ADDRESS		0x00800000ul
#define 	FLASH_D_ARRAY_BASE1_ADDRESS		0x00804000ul
#define 	FLASH_D_ARRAY_BASE2_ADDRESS		0x00808000ul
#define 	FLASH_D_ARRAY_BASE3_ADDRESS		0x0080C000ul

/*---------------------------------------------------------------------------*/
/***	Data Flash Block Size : 64KB									   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_DF_ALL_SIZE				(0x1<<16)
#define 	FLASH_DF_EVERY_SIZE				(0x1<<14)

/*---------------------------------------------------------------------------*/
/***	Module Configuration Register (MCR)								   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_MCR						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_MCR_OFFSET))
#define 	FLASH_MCR_EHV_MASK				(1<<0)
#define 	FLASH_MCR_ESUS_MASK				(1<<1)
#define 	FLASH_MCR_ERS_MASK				(1<<2)
#define 	FLASH_MCR_PSUS_MASK				(1<<3)
#define 	FLASH_MCR_PGM_MASK				(1<<4)
#define 	FLASH_MCR_PEG_MASK				(1<<9)
#define 	FLASH_MCR_DONE_MASK				(1<<10)
#define 	FLASH_MCR_PEAS_MASK				(1<<11)
#define 	FLASH_MCR_RWE_MASK				(1<<14)
#define 	FLASH_MCR_EER_MASK				(1<<15)
#define 	FLASH_MCR_MAS_MASK				(1<<16)
#define 	FLASH_MCR_LAS_MASK				(0x7<<20)
#define 	FLASH_MCR_SIZE_MASK				(0x7<<24)
#define 	FLASH_MCR_EDC_MASK				(1<<31)

/*---------------------------------------------------------------------------*/
/***	Low/Mid Address Space Block Locking register (LML)				   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_LML						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_LML_OFFSET))
#define 	FLASH_LML_LLK_MASK				(0xFFFF<<0)
#define 	FLASH_LML_MLK_MASK				(0x03<<16)
#define 	FLASH_LML_TSLK_MASK				(1<<20)
#define 	FLASH_LML_LME_MASK				(1<<31)
#define 	FLASH_LML_PASSWORD				0xA1A11111
#define 	FLASH_LML_LLK_D_MASK			(0x0F<<0)

/*---------------------------------------------------------------------------*/
/***	Non-Volatile Low/Mid Address Space Block Locking register (NVLML)  ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NVLML						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_NVLML_OFFSET))
#define 	FLASH_NVLML_LLK_MASK			(0xFFFF<<0)
#define 	FLASH_NVLML_MLK_MASK			(1<<16)
#define 	FLASH_NVLML_TSLK_MASK			(1<<20)

/*---------------------------------------------------------------------------*/
/***	Secondary Low/Mid Address Space Block Locking register (SLL)	   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_SLL						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_SLL_OFFSET))
#define 	FLASH_SLL_SLK_MASK				(0xFFFF<<0)
#define 	FLASH_SLL_SMK_MASK				(0x03<<16)
#define 	FLASH_SLL_STSLK_MASK			(1<<20)
#define 	FLASH_SLL_SLE_MASK				(1<<31)
#define 	FLASH_SLL_PASSWORD				0xC3C33333

/*---------------------------------------------------------------------------*/
/***	Non-Volatile Secondary Low/Mid Address Space Block Locking register (NVSLL)   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NVSLL						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_NVSLL_OFFSET))
#define 	FLASH_NVSLL_LLK_MASK			(0xFFFF<<0)
#define 	FLASH_NVSLL_SMK_MASK			(1<<16)
#define 	FLASH_NVSLL_STSLK_MASK			(1<<20)

/*---------------------------------------------------------------------------*/
/***	Low/Mid Address Space Block Select register (LMS)				   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_LMS						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_LMS_OFFSET))
#define 	FLASH_LMS_DF_SEL_MASK			(0x0F<<0)
#define 	FLASH_LMS_LSL_MASK				(0xFFFF<<0)
#define 	FLASH_LMS_MSL_MASK				(0x03<<16)

/*---------------------------------------------------------------------------*/
/***	Address Register (ADR)											   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_ADR						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_ADR_OFFSET))
#define 	FLASH_ADR_MASK					0x007FFFF8

/*---------------------------------------------------------------------------*/
/***	Platform Flash Configuration Register 0 (PFCR0)					   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_PFCR0						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_PFCR0_OFFSET))
#define 	FLASH_PFCR0_B0_P0_BFE_MASK		(1<<0)
#define 	FLASH_PFCR0_B0_P0_PFLM_MASK		(0x03<<1)
#define 	FLASH_PFCR0_B0_P0_IPFE_MASK		(1<<3)
#define 	FLASH_PFCR0_B0_P0_DPFE_MASK		(1<<4)
#define 	FLASH_PFCR0_B0_P0_BCFG_MASK		(0x03<<5)
#define 	FLASH_PFCR0_BK0_RWWC0_MASK		(1<<7)
#define 	FLASH_PFCR0_BK0_RWWC1_MASK		(1<<15)
#define 	FLASH_PFCR0_BK0_RWWC2_MASK		(1<<16)
#define 	FLASH_PFCR0_BK0_RWSC_MASK		(0x1F<<17)
#define 	FLASH_PFCR0_BK0_WWSC_MASK		(0x1F<<22)
#define 	FLASH_PFCR0_BK0_APC_MASK		(0x1F<<27)

/*---------------------------------------------------------------------------*/
/***	Platform Flash Configuration Register 1 (PFCR1)					   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_PFCR1						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_PFCR1_OFFSET))
#define 	FLASH_PFCR1_B1_P0_BFE_MASK		(1<<0)
#define 	FLASH_PFCR1_BK1_RWWC0_MASK		(1<<7)
#define 	FLASH_PFCR1_B1_P1_BFE_MASK		(1<<8)
#define 	FLASH_PFCR1_BK1_RWWC1_MASK		(1<<15)
#define 	FLASH_PFCR1_BK1_RWWC2_MASK		(1<<16)
#define 	FLASH_PFCR1_BK1_RWSC_MASK		(0x1F<<17)
#define 	FLASH_PFCR1_BK1_WWSC_MASK		(0x1F<<22)
#define 	FLASH_PFCR1_BK1_APC_MASK		(0x1F<<27)

/*---------------------------------------------------------------------------*/
/***	Platform Flash Access Protection Register (PFAPR)				   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_PFAPR						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_PFAPR_OFFSET))
#define 	FLASH_PFAPR_ARBM_MASK			(0x03<<24)

/*---------------------------------------------------------------------------*/
/***	User Test 0 register (UT0)										   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_UT0						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_UT0_OFFSET))
#define 	FLASH_UT0_AID_MASK				(1<<0)
#define 	FLASH_UT0_AIE_MASK				(1<<1)
#define 	FLASH_UT0_AIS_MASK				(1<<2)
#define 	FLASH_UT0_EIE_MASK				(1<<3)
#define 	FLASH_UT0_MRV_MASK				(1<<4)
#define 	FLASH_UT0_MRE_MASK				(1<<5)
#define 	FLASH_UT0_X_MASK				(1<<6)
#define 	FLASH_UT0_UTE_MASK				(1<<31)
#define 	FLASH_UT1_DSI_MASK				(0xFF<<16)
#define 	FLASH_UT0_PASSWORD				0xF9F99999	/* Password to enable User Test Mode */

/*---------------------------------------------------------------------------*/
/***	User Test 1 register (UT1)										   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_UT1						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_UT1_OFFSET))

/*---------------------------------------------------------------------------*/
/***	User Test 2 register (UT2)										   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_UT2						(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_UT2_OFFSET))

/*---------------------------------------------------------------------------*/
/***	User Multiple Input Signature Register 0						   ***/
/***	(UMISR0)(UMISR1)(UMISR2)(UMISR3)(UMISR4)						   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_UMISR(x)					(*(volatile INT32U *)(FLASH_BASE_ADDRESS+FLASH_UMISR_OFFSET(x)))

/*---------------------------------------------------------------------------*/
/***	Non-Volatile Private Censorship Password 0 register (NVPWD0)	   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NVPWD0					(*(volatile INT32U *)(FLASH_NVPWD0_ADDRESS))

/*---------------------------------------------------------------------------*/
/***	Non-Volatile Private Censorship Password 1 register (NVPWD1)	   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NVPWD1					(*(volatile INT32U *)(FLASH_NVPWD1_ADDRESS))

/*---------------------------------------------------------------------------*/
/***	Non-Volatile System Censoring Information 0 register (NVSCI0)	   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NVSCI0					(*(volatile INT32U *)(FLASH_NVSCI0_ADDRESS))

/*---------------------------------------------------------------------------*/
/***	Non-Volatile System Censoring Information 1 register (NVSCI1)	   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NVSCI1					(*(volatile INT32U *)(FLASH_NVSCI1_ADDRESS))
#define 	FLASH_NVSCI_SC_MASK				(0xFFFF<<16)
#define 	FLASH_NVSCI_CW_MASK				(0xFFFF<<0)

/*---------------------------------------------------------------------------*/
/***	Non-Volatile User Options register (NVUSRO)						   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NVUSRO					(*(volatile INT32U *)(FLASH_NVUSRO_ADDRESS))
#define 	FLASH_NVUSRO_PAD3V5V_MASK		(1<<29)
#define 	FLASH_NVUSRO_MARGIN_MASK		(1<<30)
#define 	FLASH_NVUSRO_WTG_EN_MASK		(1<<31)
#define 	FLASH_NVUSRO_UO_MASK			0x1FFFFFFF


/* *****************************************************************************
   *****************************************************************************
   App Macro definition
   *****************************************************************************
   ***************************************************************************** */
/*---------------------------------------------------------------------------*/
/***	Return Code for Flash Functions									   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_OK						0x0
#define		FLASH_INFO_RWE					0x1		/* There is read-while-write error for previous reads */
#define		FLASH_INFO_EER					0x2		/* There is ECC error for previous reads */
#define		FLASH_INFO_EPE					0x3		/* The program/erase for all blocks including shadow row and excluding the boot block is disabled */
#define		FLASH_INFO_BBEPE				0x4		/* The program/erase for boot block is disabled */
#define		FLASH_ERR_PARTID				0x5		/* The SSD cannot operate on this part */
#define		FLASH_ERR_STOP					0x6		/* The flash is in STOP mode and no operation is allowed */
#define		FLASH_ERR_ALIGN					0x7		/* Alignment error */
#define		FLASH_ERR_RANGE					0x8		/* Address range error */
#define		FLASH_ERR_BUSY					0x9		/* New program/erase cannot be preformed while previous high voltage operation in progress */
#define		FLASH_ERR_PGOOD					0x0A	/* The program operation is unsuccessful */
#define		FLASH_ERR_EGOOD					0x0B	/* The erase operation is unsuccessful */
#define		FLASH_ERR_NOT_BLANK				0x0C	/* There is non-blank location in the checked flash memory */
#define		FLASH_ERR_VERIFY				0x0D	/* There is a mismatch between the source data and content in the checked flash memory */
#define		FLASH_ERR_LOCK_INDR				0x0E	/* Invalid block lock indicator */
#define		FLASH_ERR_RWE					0x0F	/* Read while write error on the previous reads */
#define		FLASH_ERR_PASSWORD				0x10	/* The password provided cannot unlock the block lock register for register writes */
#define		FLASH_ERR_AIC_MISMATCH			0x11	/* The MISR generated by the AIC hardware doesnot match the MISR passed by the user */
#define		FLASH_ERR_AIC_NO_BLOCK			0x12	/* No blocks have been enabled for Array Integrity check */
#define		FLASH_ERR_FMR_MISMATCH			0x13	/* The MISR generated by the FMR hardware doesnot match the MISR passed by the user */
#define		FLASH_ERR_FMR_NO_BLOCK			0x14	/* No blocks have been enabled for Factory Margin Read check */
#define		FLASH_ERR_ECC_LOGIC				0x15	/* The ECC Logic check has failed */
#define		FLASH_ERR_SUSP					0x16	/* Ongoing operation cannot be suspended */

/*---------------------------------------------------------------------------*/
/***	Size of Double Word												   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_DWORD_SIZE				8
#define		FLASH_WORD_SIZE					4
#define		FLASH_DWORD_MASK				0xFFFFFFFF

/*---------------------------------------------------------------------------*/
/***	Flash Page Size													   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_PAGE_SIZE_8				(INT32U)8
#define		FLASH_PAGE_SIZE_16				(INT32U)16
#define		FLASH_PAGE_SIZE_32				(INT32U)32

/*---------------------------------------------------------------------------*/
/***	Indication for setting/getting block lock state					   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_LOCK_SHADOW_PRIMARY      	0   /* Primary Block lock protection of shadow address space */
#define 	FLASH_LOCK_SHADOW_SECONDARY    	1   /* Secondary Block lock protection of shadow address space */
#define 	FLASH_LOCK_LOW_PRIMARY         	2   /* Primary block lock protection of low address space */
#define 	FLASH_LOCK_LOW_SECONDARY       	3   /* Secondary block lock protection of low address space */
#define 	FLASH_LOCK_MID_PRIMARY         	4   /* Primary block lock protection of mid address space */
#define 	FLASH_LOCK_MID_SECONDARY       	5   /* Secondary block lock protection of mid address space */

/*---------------------------------------------------------------------------*/
/***	Macros for flash suspend operation								   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_NO_OPERATION             	0   /* no program/erase operation */
#define 	FLASH_PGM_WRITE                	1   /* A program sequence in interlock write stage. */
#define 	FLASH_ERS_WRITE                	2   /* An erase sequence in interlock write stage. */
#define 	FLASH_ERS_SUS_PGM_WRITE        	3   /* A erase-suspend program sequence in interlock write stage. */
#define 	FLASH_PGM_SUS                  	4   /* The program operation is in suspend state */
#define 	FLASH_ERS_SUS                  	5   /* The erase operation on main array is in suspend state */
#define 	FLASH_SHADOW_ERS_SUS           	6   /* The erase operation on shadow row is in suspend state. */
#define 	FLASH_ERS_SUS_PGM_SUS          	7   /* The erase-suspended program operation is in suspend state */
#define 	FLASH_NO_SUS                   	8   /* No operation has been suspended  */

/*---------------------------------------------------------------------------*/
/***	Suspend Operation Function StateFlag							   ***/
/*---------------------------------------------------------------------------*/
#define 	SUSP_NORMAL                   	0
#define 	SUSP_WAIT                   	1
#define 	SUSP_RETURN                   	2

/*---------------------------------------------------------------------------*/
/***	Macros for flash resume operation								   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_RES_NOTHING               0   /* No suspended program/erase operation */
#define 	FLASH_RES_PGM                   1   /* The program operation is resumed */
#define 	FLASH_RES_ERS                   2   /* The erase operation is resumed */
#define 	FLASH_RES_ERS_PGM				3   /* The erase-suspended program operation is resumed */

/*---------------------------------------------------------------------------*/
/***	Cycles counter used in FlashResume								   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_RESUME_WAIT   			15

/*---------------------------------------------------------------------------*/
/***	Array Integrity Sequence Mode									   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_AIS_SEQL       			0x1 /* Logically sequential. Array integrity sequence is */
#define		FLASH_AIS_PROP       			0x0 /* Proprietary sequence. */

/*---------------------------------------------------------------------------*/
/***	MAcros used in ECC logic check									   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_ECC_ERR_BIT_SET_ZERO		0x0
#define		FLASH_ECC_ERR_BIT_SET_ONE		0x1
#define		FLASH_ECC_ERR_BIT_SET_TWO		0x2

/*---------------------------------------------------------------------------*/
/***	Data Array Input Count											   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_UT_DAI_CNT				64

/*---------------------------------------------------------------------------*/
/***	Ecc Error Mask													   ***/
/*---------------------------------------------------------------------------*/
#define 	FLASH_ECC_ERR_MASK				0xFF00FF00

/*---------------------------------------------------------------------------*/
/***	Margin Check Level												   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_FMR_ERASED_LEVEL       	0x01 /* Margin checked to an erased level (MRV=1) */
#define		FLASH_FMR_PROGRAMMED_LEVEL   	0x00 /* Margin checked to an programmed level (MRV=0) */

/*---------------------------------------------------------------------------*/
/***	Nest and UnNest IRQ												   ***/
/*---------------------------------------------------------------------------*/
#define		FLASH_IRQ_DISABLE()				asm("wrteei 0")	/* (void)0 */
#define		FLASH_IRQ_ENABLE()				asm("wrteei 1")	/* (void)0 */

/*---------------------------------------------------------------------------*/
/***	User Multiple Input Signature Register Struct					   ***/
/*---------------------------------------------------------------------------*/
typedef struct _stc_Flash_MISR_
{
    INT32U W0;
    INT32U W1;
    INT32U W2;
    INT32U W3;
    INT32U W4;
} stc_Flash_MISR;



/* *****************************************************************************
   *****************************************************************************
   function declaration
   *****************************************************************************
   ***************************************************************************** */
M_FLASH_DRV_EXT	INT8U	mFlash_BlankCheck(INT32U dest, INT32U size);
M_FLASH_DRV_EXT	INT8U	mFlash_CheckSum(INT32U dest, INT32U size, INT32U *pSum);
M_FLASH_DRV_EXT	INT8U	mFlash_DFlashErase(INT32U EraseAddrBase, INT32U lowEnabledBlocks);
M_FLASH_DRV_EXT	INT8U	mFlash_Init(void);
M_FLASH_DRV_EXT	INT8U	mFlash_DFlashProgram(INT32U dest, INT32U size, INT32U source);
M_FLASH_DRV_EXT	INT8U	mFlash_DFlashVerify(INT32U dest, INT32U size, INT32U source);
M_FLASH_DRV_EXT	INT8U	mFlash_SetLock(INT8U blkLockIndicator, INT32U blkLockState, INT32U password);
M_FLASH_DRV_EXT	INT8U	mFlash_GetLock(INT8U blkLockIndicator, INT8U *blkLockEnAddr, INT32U *blkLockStateAddr);
M_FLASH_DRV_EXT	INT8U	mFlash_Suspend(INT8U *SuspendStateAddr, INT8U *SuspendFlagAddr);
M_FLASH_DRV_EXT	INT8U	mFlash_Resume(INT8U *ResumeStateAddr);
M_FLASH_DRV_EXT	INT8U	mFlash_ArrayIntergrityCheck(INT32U LowEnBlock, INT32U MidEnBlock, INT8U ArrSeqMode, stc_Flash_MISR MisrValue);
M_FLASH_DRV_EXT	INT8U	mFlash_ECCLogicCheck(INT64U DataVal, INT64U ErrBits, INT8U EccVal);
M_FLASH_DRV_EXT	INT8U	mFlash_FactoryMarginReadCheck(INT32U LowEnBlock, INT32U MidEnBlock, INT8U MarginLevel, stc_Flash_MISR MisrValue);



#endif	
