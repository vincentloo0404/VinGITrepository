
#ifndef UDS_STD_TYPES_H
#define UDS_STD_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "UDS_Platform_Types.h"
#include "UDS_Compiler.h"
#include "Platform_Types.h"


//#include "Defines.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define STDTYPES_VENDOR_ID               (0xFFFFu)
/* AUTOSAR Software Specification Version Information */
#define STD_TYPES_AR_MAJOR_VERSION       (0x04u)
#define STD_TYPES_AR_MINOR_VERSION       (0x00u)
#define STD_TYPES_AR_PATCH_VERSION       (0x00u)

/* Component Version Information */
#define STD_TYPES_SW_MAJOR_VERSION       (0x01u)
#define STD_TYPES_SW_MINOR_VERSION       (0x00u)
#define STD_TYPES_SW_PATCH_VERSION       (0x00u)

#define STD_HIGH     1u /* Physical state 5V or 3.3V */
#define STD_LOW      0u /* Physical state 0V */

#define STD_ACTIVE   1u /* Logical state active */
#define STD_IDLE     0u /* Logical state idle */

/* This typedef has been addedf or OSEK compliance */


typedef uint8 Std_ReturnType;
typedef unsigned char StatusType; /* OSEK compliance */
typedef struct
{
   uint16 vendorID;
   uint16 moduleID;
   uint8  instanceID;
   uint8  sw_major_version;
   uint8  sw_minor_version;
   uint8  sw_patch_version;
} Std_VersionInfoType;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


#endif  /* UDS_STD_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
