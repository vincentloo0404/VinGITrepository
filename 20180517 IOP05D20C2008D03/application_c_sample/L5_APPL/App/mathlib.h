/*
 * mathlib.h
 *
 *  Created on: 2016年4月22日
 *      Author: YCH
 */

#ifndef APP_COMM_INCLUDE_MATHLIB_H_
#define APP_COMM_INCLUDE_MATHLIB_H_

#include "stdlib.h"
#include "my_all.h"
//#ifndef uint8
//typedef unsigned char       uint8;
//#endif
//#ifndef int8
//typedef signed char int8;
//#endif
//#ifndef sint16
//typedef signed short sint16;
//#endif
//#ifndef uint16
//typedef unsigned short uint16;
//#endif
//#ifndef sint32
//typedef signed int sint32;
//#endif
//#ifndef uint32
//typedef unsigned int uint32;
//#endif
//#ifndef uint64
//typedef unsigned long uint64;
//#endif
//
//#ifndef int16_t
//typedef signed short int16_t;
//#endif
//
//#ifndef uint16_t
//typedef unsigned short uint16_t;
//#endif

typedef struct Table1D{
	int16_t x;
	int16_t y;
}TABLE1D;

void quckly_sort_2(short unsigned int* a,int begin ,int end);
unsigned int LIB_Sqrt(unsigned int);
unsigned int sqrt_16(unsigned long M);
extern int Interpolate_16_To_16 (unsigned short x, unsigned short n_points,
                                                   const unsigned short x_table[],  const int y_table[]);
//extern int Interpolate_16_To_16 (unsigned short x, unsigned short n_points,const unsigned short x_table[], const int y_table[]);
signed short LIB_geTable1D(signed short input, const TABLE1D *  pTable1D, signed short length);
#define No_Elems(arr)   (sizeof(arr) / sizeof(arr[0])) //温度查表
#define ABS(x) ((x)>0?(x):-(x))

extern uint32 LPF(uint32 x,uint32 xFlt,uint16 dt,uint16 tau);

#endif /* APP_COMM_INCLUDE_MATHLIB_H_ */
