#ifndef UDS_PLATFORM_TYPES_H
#define UDS_PLATFORM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PLATFORM_VENDOR_ID              (0xFFFFu)

/* AUTOSAR Software Specification Version Information */
#define PLATFORM_AR_MAJOR_VERSION       (0x01u)
#define PLATFORM_AR_MINOR_VERSION       (0x00u)
#define PLATFORM_AR_PATCH_VERSION       (0x00u)

/* Component Version Information */
#define PLATFORM_SW_MAJOR_VERSION       (1u)
#define PLATFORM_SW_MINOR_VERSION       (0x00u)
#define PLATFORM_SW_PATCH_VERSION       (0x00u)


#define CPU_TYPE_8       8
#define CPU_TYPE_16      16
#define CPU_TYPE_32      32

#define MSB_FIRST        0    /* big endian bit ordering */
#define LSB_FIRST        1    /* little endian bit ordering */

#define HIGH_BYTE_FIRST  0    /* big endian byte ordering */
#define LOW_BYTE_FIRST   1    /* little endian byte ordering */

#ifndef TRUE
   #define TRUE   1
#endif

#ifndef FALSE
   #define FALSE  0
#endif

#define CPU_TYPE         CPU_TYPE_16
#define CPU_BIT_ORDER    MSB_FIRST
#define CPU_BYTE_ORDER   HIGH_BYTE_FIRST

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

//typedef unsigned char         boolean; /*                 TRUE .. FALSE                */
//typedef signed char           sint8;   /*                 -128 .. +127                 *//
//typedef unsigned char         uint8;   /*                    0 .. 255                  */
//typedef signed short          sint16;  /*               -32768 .. +32767               */
//typedef unsigned short        uint16;  /*                    0 .. 65535                */

/*the following two types are changed into next two.*/
//typedef signed long int            sint32;  /*          -2147483648 .. +2147483647          */
//typedef unsigned long int          uint32;  /*                    0 .. 4294967295           */

//typedef signed  int            sint32;  /*          -2147483648 .. +2147483647          */
//typedef unsigned  int          uint32;  /*                    0 .. 4294967295           */


//typedef signed long long      sint64;  /* -9223372036854775808 .. 9223372036854775807  */
//typedef unsigned long long    uint64;  /*                    0 .. 18446744073709551615 */

typedef signed int      sint8_least;  /* At least 7 bit + 1 bit sign    */
typedef unsigned int    uint8_least;  /* At least 8 bit                 */
typedef signed int      sint16_least; /* At least 15 bit + 1 bit sign   */
typedef unsigned int    uint16_least; /* At least 16 bit                */
typedef signed int      sint32_least; /* At least 31 bit + 1 bit sign   */
typedef unsigned int    uint32_least; /* At least 32 bit                */

//typedef float  float32;
//typedef double float64;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif  /* UDS_PLATFORM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Platform_Types.h
 *********************************************************************************************************************/
