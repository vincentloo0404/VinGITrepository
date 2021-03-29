#ifndef STD_TYPES_H
#define STD_TYPES_H  1

/*****************************************************************************
*   Include Files
*****************************************************************************/
#include "Compiler.h"
#include "Platform_Types.h"

/*****************************************************************************
*   Global Define Definitions
*****************************************************************************/
#define E_OK        0x00U
#define E_NOT_OK    0x01U

#define STD_ON      0x01U
#define STD_OFF     0x00U

typedef uint8       Std_ReturnType;

#define MAX_SINT8   ((sint8)(127))
#define MIN_SINT8   ((sint8)(-128))
#define MAX_UINT8   ((uint8)(255U))
#define MIN_UINT8   ((uint8)(0U))
#define MAX_SINT16  ((sint16)(32767))
#define MIN_SINT16  ((sint16)(-32768))
#define MAX_UINT16  ((uint16)(65535U))
#define MIN_UINT16  ((uint16)(0U))
#define MAX_SINT32  ((sint32)(2147483647))
#define MIN_SINT32  ((sint32)(-2147483647-1))
#define MAX_UINT32  ((uint32)(0xFFFFFFFFU))
#define MIN_UINT32  ((uint32)(0U))

/*---------------------------------------------------------------------------*/
/***	BOOL Defination Macro                                              ***/
/*---------------------------------------------------------------------------*/
#ifndef   		FALSE
#define   		FALSE               0         /* Bit-Field Is False */
#endif
#ifndef   		TRUE
#define   		TRUE                1         /* Bit-Field Is True */
#endif

#ifndef   		OFF
#define   		OFF                 0         /* Bit-Field Is Off */
#endif
#ifndef   		ON
#define   		ON                  1         /* Bit-Field Is On */
#endif

#ifndef   		DISABLE
#define   		DISABLE             0         /* Bit-Field Is Disabled */
#endif
#ifndef   		ENABLE
#define   		ENABLE              1         /* Bit-Field Is Enabled */
#endif

#ifndef   		LOW
#define   		LOW                 0         /* Bit-Field Is Low */
#endif
#ifndef   		HIGH
#define   		HIGH                1         /* Bit-Field Is High */
#endif

#define			PTR_NULL			0x00
/*---------------------------------------------------------------------------*/
/***	Byte Mask Macro                                                    ***/
/*---------------------------------------------------------------------------*/
#define 		BYTE_MASK				(uint8)0xFFu
#define 		LOW_BYTE_MASK			(uint8)0x0Fu
#define 		HIGH_BYTE_MASK			(uint8)0xF0u

#endif  /* STD_TYPES_H */
