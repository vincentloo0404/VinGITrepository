#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H  1

/*****************************************************************************
*   Global Type Definitions
*****************************************************************************/
/*The platform types for freescale mpc560xp MicroController */
typedef unsigned char                BOOL;          /*!< basic boolean type */
typedef unsigned char                boolean;             /*!< basic boolean type */
typedef unsigned char                uint8;            /*!< unsigned 8-bit integer type */
typedef signed char                  sint8;            /*!< signed 8-bit integer type */
typedef unsigned short               uint16;           /*!< unsigned 16-bit integer type */
typedef signed short                 sint16;           /*!< signed 16-bit integer type */
typedef unsigned int                 uint32;           /*!< unsigned 32-bit integer type */
typedef volatile unsigned int        vuint32;           /*!< unsigned 32-bit integer type */
typedef signed int                   sint32;           /*!< signed 32-bit integer type */
typedef unsigned long long           uint64;           /*!< unsigned 64-bit integer type */
typedef volatile unsigned long long  vuint64;           /*!< unsigned 64-bit integer type */
typedef signed long long             sint64;           /*!< signed 64-bit integer type */

#endif  /* PLATFORM_TYPES_H */
