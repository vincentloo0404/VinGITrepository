/******************************************************************************
*
* ChuangQu Inc.
* (c) Copyright 2012 ChuangQu, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     V_CCP.H
*
* @brief    ccp header file
*
********************************************************************************
*   Revision History:
* 
*    Version      Date          Author        CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2013/01/14      ----       N/A          delete debug code
*     1.1        2013/04/07      ----       N/A          change can tx interface
*     
*******************************************************************************/

#ifndef __CCP_H_
#define __CCP_H_

#include "m_CAN_Drv.h"
#include "m_CAN_Cfg.h"

#ifdef V_CCP_C
#define CCP_EXT 
#else
#define CCP_EXT extern
#endif

#ifndef C_DISABLE_CCP

#define CCP_CRO_CAN_ID  0x635 /*  0x64C*/
#define CCP_DTO_CAN_ID  0x636 /*  0x64D*/

/*----------------------------------------------------------------------------*/
/* Platform independant types */

/*
#define CCP_MOTOROLA  or #define CCP_INTEL
#define CCP_BYTE    unsigned char
#define CCP_WORD    UINT16
#define CCP_DWORD   uint32
#define CCP_BYTEPTR unsigned char*
#define CCP_ROM
#define CCP_RAM
#define CCP_DAQBYTEPTR CCP_BYTEPTR
#define CCP_MTABYTEPTR CCP_BYTEPTR
*/

/*----------------------------------------------------------------------------*/
/* Disable/Enable Interrupts */

/* Has to be defined if ccpSendCallBack may interrupt ccpDaq */
#define CCP_DISABLE_INTERRUPT  IRQ_DISABLE()
#define CCP_ENABLE_INTERRUPT   IRQ_ENABLE() 

/*----------------------------------------------------------------------------*/
/* CCP parameters */

/* CCP Identifiers and Address */
#define CCP_STATION_ADDR  0x0023      /* Define CCP_STATION_ADDR in Intel Format */
                                      /* High/Low byte swapped on motorola machines !!! (0x3900) */

#define CCP_STATION_ID    "ECU00001"  /* Plug&Play station identification */

#define CCP_DTO_ID        1           /* CAN identifier ECU -> Master */
#define CCP_CRO_ID        2           /* CAN identifier Master -> ECU */


/*----------------------------------------------------------------------------*/
/* CCP Data Acuisition Parameters */

#define CCP_DAQ                   /* Enable synchronous data aquisition in ccpDaq() */
#define CCP_MAX_ODT 20             /* Number of ODTs in each DAQ lists */
#define CCP_MAX_DAQ 2             /* Number of DAQ lists */


/*----------------------------------------------------------------------------*/
/* CCP Options */

#define CCP_SET_SESSION_STATUS
#define CCP_CPUTYPE_32BIT

/* Use the transmit queue in CCP.C */
/* Complete sampling is done in ccpDaq(x) and the messages are written into the queue */
#define CCP_SEND_QUEUE

/* Indicate queue overruns in the msb of pid */
/* Will be displayed in CANape's status bar if CANAPE.INI: [asap1a] check_overflow=1 */
#define CCP_SEND_QUEUE_OVERRUN_INDICATION

/* Transmit only one message in one call to ccpDaq() */
/* #define CCP_SEND_SINGLE */

/* Allow an ODT entry size >1 */
/* Not recommended for CANape, this will only need additional RAM space */
 #define CCP_ODT_ENTRY_SIZE 

/* Use GET_SEED and UNLOCK */
/* This is usually user dependant, just a skeleton here */
/* #define CCP_SEED_KEY*/

/* Implement the flash programming feature in the ECU*/
/* This is usually user dependant, just a skeleton here */
//#define CCP_PROGRAM
#define CCP_CALPAGE


/* Activate the flash programming kernel download feature */
/* This is a CCP extension for CANape */
/* #define CCP_BOOTLOADER_DOWNLOAD */

/* Implement the memory checksum feature */
/* The checksum will be calculated in ccpBackground() */
/* This may be implementation specific */
#define CCP_CHECKSUM
#define CCP_CHECKSUM_TYPE CCP_WORD

/* Use a 16 bit CRC algorithm */
/* Note:
   This will need additional 512 byte of ROM
   CCP_CHECKSUM_TYPE has to be WORD !
*/
/* #define CCP_CHECKSUM_CCITT*/

/* Check for pending CCP commands in ccpBackground() */
/* #ifdef CCP_CMD_NOT_IN_INTERRUPT */

/* Enable Memory Write Protection */
/* #define CCP_WRITE_PROTECTION*/

/* Enable EEPROM Read/Write Access */
/* #define CCP_WRITE_EEPROM */
/* #define CCP_READ_EEPROM */


/* Declare CCP-protocol version */
#define CCP_VERSION_MAJOR   0x02
#define CCP_VERSION_MINOR   0x01


/* Declare module implementation version number */
#define CCP_DRIVER_VERSION 142
#define CCP_DRIVER_BUGFIX_VERSION 0

#define kCanTxOk TRUE

/* Basic */
#define CC_CONNECT           0x01
#define CC_SET_MTA           0x02
#define CC_DNLOAD            0x03
#define CC_UPLOAD            0x04
#define CC_TEST              0x05 /* V2.1 */
#define CC_START_STOP        0x06
#define CC_DISCONNECT        0x07
#define CC_START_STOP_ALL    0x08 /* V2.1 */
#define CC_SHORT_UPLOAD      0x0F
#define CC_GET_DAQ_SIZE      0x14
#define CC_SET_DAQ_PTR       0x15
#define CC_WRITE_DAQ         0x16
#define CC_EXCHANGE_ID       0x17
#define CC_GET_CCP_VERSION   0x1B /* V2.1 */
#define CC_DNLOAD6           0x23

/* Optional */
#define CC_GET_CAL_PAGE      0x09
#define CC_SET_S_STATUS      0x0C
#define CC_GET_S_STATUS      0x0D
#define CC_BUILD_CHKSUM      0x0E
#define CC_CLEAR_MEMORY      0x10
#define CC_SET_CAL_PAGE      0x11
#define CC_GET_SEED          0x12
#define CC_UNLOCK            0x13
#define CC_PROGRAM           0x18
#define CC_MOVE_MEMORY       0x19
#define CC_DIAG_SERVICE      0x20
#define CC_ACTION_SERVICE    0x21
#define CC_PROGRAM6          0x22 

/* Vector extensions */
#define CC_PROGRAM_PREPARE   0x1E   /* Prepare for flash kernel download */
#define CC_PROGRAM_START     0x1F   /* Start flash kernel at MTA[0] */

/* Returncodes */
#define CRC_OK                 0x00

/* C1 */
#define CRC_CMD_BUSY           0x10
#define CRC_DAQ_BUSY           0x11
#define CRC_KEY_REQUEST        0x18
#define CRC_STATUS_REQUEST     0x19

/* C2 */
#define CRC_COLD_START_REQUEST 0x20
#define CRC_CAL_INIT_REQUEST   0x21
#define CRC_DAQ_INIT_REQUEST   0x22
#define CRC_CODE_REQUEST       0x23

/* C3 (Errors) */
#define CRC_CMD_UNKNOWN        0x30
#define CRC_CMD_SYNTAX         0x31
#define CRC_OUT_OF_RANGE       0x32
#define CRC_ACCESS_DENIED      0x33
#define CRC_OVERLOAD           0x34
#define CRC_ACCESS_LOCKED      0x35


/* Session Status */
#define SS_CAL                0x01
#define SS_DAQ                0x02
#define SS_RESUME             0x04
#define SS_TMP_DISCONNECTED   0x10
#define SS_CONNECTED          0x20
#define SS_STORE              0x40
#define SS_RUN                0x80

/* Priviledge Level */
#define PL_CAL 0x01
#define PL_DAQ 0x02
#define PL_PGM 0x40

/* Broadcast Station Address */
#define CCP_BROADCAST_STATION_ADDR 0

/*--------------------------------------------------------------------------*/
/* Datatypes */
/*--------------------------------------------------------------------------*/
#define CCP_BYTE            uint8
#define CCP_WORD            uint16
#define CCP_DWORD           uint32
#define CCP_BYTEPTR         uint8 *
#define CCP_MTABYTEPTR CCP_BYTE CCP_MEM_ROM *
#define CCP_DAQBYTEPTR CCP_BYTE CCP_MEM_ROM *
#define CCP_RAM
#define CCP_ROM   const//to be defined
#define CCP_MEM_ROM //to be defined
#define CCP_MEM_RAM //to be defined

/*--------------------------------------------------------------------------*/
/* DAQ Lists, Type Definition */
/*--------------------------------------------------------------------------*/

/* Note:
   - Adressextensions are not used in this example
   - Object size > 1 are not used in this example and must be handled in
     the calibration system
*/

/* The maximum number of ODTs is restricted
   PID=0xFE,0xFF is reserved
*/
#ifdef CCP_DAQ
#ifndef CCP_SEND_QUEUE_OVERRUN_INDICATION
  #if CCP_MAX_DAQ*CCP_MAX_ODT>254
  #error Too many ODTs, maximum is CCP_MAX_DAQ*CCP_MAX_ODT = 254
  #endif
#else
  #if CCP_MAX_DAQ*CCP_MAX_ODT>126
  #error Too many ODTs, maximum is CCP_MAX_DAQ*CCP_MAX_ODT = 126
  #endif
#endif
#endif


#ifdef CCP_DAQ

/* ODT entry */
typedef struct ccpOdtEntry 
{
  CCP_DAQBYTEPTR ptr;
  #ifdef CCP_ODT_ENTRY_SIZE
    CCP_BYTE       siz;
  #endif
} ccpOdtEntry_t;

/* ODT */
typedef ccpOdtEntry_t ccpODT_t[7];

/* DAQ list */
#define DAQ_FLAG_START    0x01
#define DAQ_FLAG_SEND     0x02
#define DAQ_FLAG_PREPARED 0x04
#define DAQ_FLAG_OVERRUN  0x80

typedef struct ccpDaqList 
{
  ccpODT_t    odt[CCP_MAX_ODT];
  CCP_WORD        prescaler;
  CCP_WORD        cycle;
  CCP_BYTE        eventChannel;
  CCP_BYTE        last;
  CCP_BYTE        flags;
} ccpDaqList_t;

#else
  #undef CCP_SEND_QUEUE
  #undef CCP_SEND_SINGLE
#endif

/*--------------------------------------------------------------------------*/
/* Transmit Queue, Type Definition */
/*--------------------------------------------------------------------------*/
#ifdef CCP_SEND_QUEUE

/* Checks */

#ifndef CCP_SEND_QUEUE_SIZE
  #define CCP_SEND_QUEUE_SIZE (CCP_MAX_ODT*CCP_MAX_DAQ)
#endif

#ifdef CCP_SEND_SINGLE
  #error Do not use CCP_SEND_SINGLE together with CCP_SEND_QUEUE
#endif

#if CCP_MAX_ODT > CCP_SEND_QUEUE_SIZE
  #error CCP_SEND_QUEUE_SIZE is too small
#endif


typedef struct 
{
  CCP_BYTE b[8];
} ccpMsg_t;

typedef struct 
{
  CCP_BYTE     len;
  CCP_BYTE     rp;
  ccpMsg_t msg[CCP_SEND_QUEUE_SIZE];
} ccpQueue_t;

#endif

/*--------------------------------------------------------------------------*/
/* CCP Driver Variables, Type Definition */
/*--------------------------------------------------------------------------*/

#define CCP_MAX_MTA 2
#define CCP_INTERNAL_MTA (CCP_MAX_MTA-1)

/* Return values for ccpWriteMTA and ccpCheckWriteEEPROM */
#define CCP_WRITE_DENIED  0
#define CCP_WRITE_OK      1
#define CCP_WRITE_PENDING 2
#define CCP_WRITE_ERROR   3

/* Bitmasks for ccp.SendStatus */
#define CCP_CRM_REQUEST  0x01
#define CCP_DTM_REQUEST  0x02
#define CCP_USR_REQUEST  0x04
#define CCP_CMD_PENDING  0x08
#define CCP_CRM_PENDING  0x10
#define CCP_DTM_PENDING  0x20
#define CCP_USR_PENDING  0x40
#define CCP_TX_PENDING   0x80
#define CCP_SEND_PENDING (CCP_DTM_PENDING|CCP_CRM_PENDING|CCP_USR_PENDING)

struct _ccp {

  CCP_BYTE Crm[8];                           /* CRM Command Return Message buffer */

  CCP_BYTE SessionStatus;
  CCP_BYTE SendStatus;

  CCP_MTABYTEPTR MTA[CCP_MAX_MTA];           /* Memory Transfer Address */

  #ifdef CCP_DAQ

    #ifdef CCP_SEND_QUEUE
      ccpQueue_t Queue;
    #else
      CCP_BYTE Dtm[8];                       /* DTM Data Transmission Message buffer */
    #endif

    #ifdef CCP_SEND_SINGLE
      CCP_BYTE CurrentDaq;
      CCP_BYTE CurrentOdt;
    #endif


    ccpOdtEntry_t *DaqListPtr;               /* Pointer for SET_DAQ_PTR, make it near to save RAM  */

    ccpDaqList_t   DaqList[CCP_MAX_DAQ];     /* DAQ list */

  #endif

  CCP_BYTE UserSessionStatus;                /* Used for GET/SET_SESSION_STATUS */

  #ifdef CCP_SEED_KEY
    CCP_BYTE ProtectionStatus;               /* Resource Protection Status */
  #endif

  #ifdef CCP_CHECKSUM
    #if defined( CCP_CPUTYPE_32BIT )
      CCP_DWORD CheckSumSize;                /* Counter for checksum calculation */
    #else
      CCP_WORD CheckSumSize;                 /* Counter for checksum calculation */
    #endif
  #endif

#if defined ( CCP_CALPAGE )
  CCP_DWORD ccpCalPage; // ¦Ì??¡¤3¡è?¨¨?a32bit¡ê???¨®?DWORD
#endif

};

extern CCP_RAM struct _ccp ccp;

#define CCP_CAN_ADAPTER_VERSION  0x0103
#define CCP_CAN_ADAPTER_BUGFIX_VERSION 0x03

#ifdef CCP_CALPAGE

#define CCP_CAL_PAGE_WORK 0
#define CCP_CAL_PAGE_REF  1

//#define CCP_CAL_PAGE_REF_ADDR  0x00804000
//#define CCP_CAL_PAGE_WORK_ADDR 0x40000000

// ¨¢¨´¨º¡À¨¬¨ª?¨®¦Ì?WPo¨ªRP¦Ì??¡¤¡ê?RP?¡§¨°??¨²RAM?D¡ê???¦Ì?¨º??a¨¢??¨¹?¨²RAM?D¨º¦Ì??¡À¨º?¡§1|?¨¹
#define CCP_WORKING_PAGE_ADDR_TEMP	0x800000UL
#define CCP_REFERENCE_PAGE_ADDR_TEMP	0x40002000UL



#endif

#define mCAN_Send_MessageForCCP mCAN_MB_12_15_Send_Message

/*--------------------------------------------------------------------------*/
/* Prototypes */

/* Functions provided externally */
/*-------------------------------*/

/* Transmit a message */
/* Returns 1 (TRUE) when successfull */
extern void ccpSend( CCP_BYTEPTR msg );

/* Background calculation */
#ifndef ccpUserBackground
  extern void ccpUserBackground( void );
#endif

/* Generate a pointer from addr_ext and addr */
#if !defined(ccpGetPointer) || defined(__BOOT_H__) /* Not defined as macro */
  extern CCP_MTABYTEPTR ccpGetPointer( CCP_BYTE addr_ext, CCP_DWORD addr );
#endif

#ifdef CCP_DAQ_BASE_ADDR
  extern CCP_DAQBYTEPTR ccpGetDaqPointer( CCP_BYTE addr_ext, CCP_DWORD addr );
#endif

#ifdef CCP_STANDARD
  extern void ccpGetMTA0( CCP_BYTE *e, CCP_DWORD *a);
#endif

/* Check addresses for valid write access */
/* Returns 0 (false) if access denied */
/* Used only, if write protection of memory areas is required */
#ifdef CCP_WRITE_PROTECTION
  #ifndef ccpCheckWriteAccess /* Not defined as macro */
    extern CCP_BYTE ccpCheckWriteAccess( CCP_MTABYTEPTR a, CCP_BYTE size );
  #endif
#endif

/* Flash Kernel Download */
/* Used only of Download of the Flash Kernel is required */  
#ifdef CCP_BOOTLOADER_DOWNLOAD

  extern CCP_BYTE ccpDisableNormalOperation( CCP_MTABYTEPTR a, CCP_WORD size );
  typedef void (*ccpBootLoader_t)(struct _ccp *, CCP_BYTEPTR);

#endif

/* Flash Programming */
/* Used only if Flash Programming is required */
#ifdef CCP_PROGRAM

  /* If Flash Programming is performed by a special loader, */
  /* the following function will be called on CLEAR_MEMORY command */
  #ifdef CCP_BOOTLOADER

    extern void ccpBootLoaderStartup( struct _ccp *ccp, CCP_BYTEPTR com );

  #else

    extern void ccpFlashClear( CCP_MTABYTEPTR a, CCP_DWORD size );
    extern CCP_BYTE ccpFlashProgramm( CCP_BYTEPTR data, CCP_MTABYTEPTR a, CCP_BYTE size );
    /* Returns:
       CCP_WRITE_OK      - FLASH written
       CCP_WRITE_PENDING - FLASH write in progress, call ccpSendCrm when done
    */

  #endif

#endif


/* RAM/ROM Switching */
#ifdef CCP_CALPAGE
  extern void ccpInitCalPage( void );
  extern CCP_DWORD ccpGetCalPage( void );
  extern void ccpSetCalPage( CCP_DWORD a );
#endif


/* Seed&Key*/
#ifdef CCP_SEED_KEY
  extern CCP_DWORD ccpGetSeed( CCP_BYTE resourceMask );
  extern CCP_BYTE ccpUnlock( CCP_BYTE *key );
#endif


/* EEPROM Programing */
#ifdef CCP_WRITE_EEPROM
  /* Return values for ccpCheckWriteEEPROM:
     CCP_WRITE_OK     - EEPROM written
     CCP_WRITE_DENIED - This is not EEPROM
     CCP_WRITE_PENDING - EEPROM write in progress, call ccpSendCrm when done
  */
  CCP_BYTE ccpCheckWriteEEPROM( CCP_MTABYTEPTR addr, CCP_BYTE size, CCP_BYTEPTR data );
#endif
#ifdef CCP_READ_EEPROM
  /* Return values for ccpCheckReadEEPROM:
     0 (FALSE)    - This is not EEPROM
     1 (TRUE)     - EEPROM read
  */
  CCP_BYTE ccpCheckReadEEPROM( CCP_MTABYTEPTR addr, CCP_BYTE size, CCP_BYTEPTR data );
#endif


/*--------------------------------------------------------------------------*/
/* Special Features */
/* Please contact Vector for details */
/*--------------------------------------------------------------------------*/

/* ECU Timestamping */
#ifdef CCP_TIMESTAMPING
  #ifndef ccpGetTimestamp /* Not defined as macro */
    CCP_WORD ccpGetTimestamp( void );
  #endif
  #ifndef ccpClearTimestamp /* Not defined as macro */
    void ccpClearTimestamp( void );
  #endif
#endif

#endif

/*--------------------------------------------------------------------------*/

/* Functions from ccp.c */
/*----------------------*/

/* Initialize */
CCP_EXT void ccpInit( void );

/* DAQ processor */
CCP_EXT void ccpDaq( CCP_BYTE eventChannel );

/* Command processor */
CCP_EXT void ccpCommand( CCP_BYTEPTR msg );

/* Transmit Notification */
/* Returns 0 when the CCP driver is idle */
CCP_EXT CCP_BYTE ccpSendCallBack( void );

/* Send a pending CRM */
CCP_EXT void ccpSendCrm( void );

/* Background Loop */
/* Return 1 (TRUE) when still pending */
/* Used only if Checksum Calculation or EEPROM Programming is required */
CCP_EXT CCP_BYTE ccpBackground( void );

CCP_EXT void CCP_CRO_Indication(CCP_BYTEPTR rxData);

extern void CCP_Per(void);


#endif
