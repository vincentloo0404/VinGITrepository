/*
 * mathlib.c
 *
 *  Created on: 2016年4月22日
 *      Author: YCH
 */


#include "mathlib.h"

/**
 *
 *TODO sqrt a number
 * @param input
 * @return output
 */
unsigned int LIB_Sqrt(unsigned int input)
{
	unsigned int i, c;
	unsigned int output = 0;
	for (i = 0x4000; i != 0; i >>= 2)
	{
		c = i + output;
		output >>= 1;
		if (c <= input)
		{
			input -= c;
			output += i;
		}
	}
	return (unsigned int) output;
}



/****************************************/
/*Function: 开根号处理                  */
/*入口参数：被开方数，长整型            */
/*出口参数：开方结果，整型              */
/****************************************/
unsigned int sqrt_16(unsigned long M)
{
    unsigned int N, i;
    unsigned long tmp, ttp;   // 结果、循环计数
    if (M == 0)               // 被开方数，开方结果也为0
        return 0;
    N = 0;
    tmp = (M >> 30);          // 获取最高位：B[m-1]
    M <<= 2;
    if (tmp > 1)              // 最高位为1
    {
        N ++;                 // 结果当前位为1，否则为默认的0
        tmp -= N;
    }
    for (i=15; i>0; i--)      // 求剩余的15位
    {
        N <<= 1;              // 左移一位
        tmp <<= 2;
        tmp += (M >> 30);     // 假设
        ttp = N;
        ttp = (ttp<<1)+1;
        M <<= 2;
        if (tmp >= ttp)       // 假设成立
        {
            tmp -= ttp;
            N ++;
        }
    }
    return N;
}

int Interpolate_16_To_16 (unsigned short x, unsigned short n_points,  const unsigned short x_table[],  const int y_table[])
{
   ldiv_t result;
   int y;
   long y1;
   long y2;
   long y3;
   long x1;
   long x2;
   long x3;
   unsigned short i = 0;

   while ( (x_table[i] < x) && (i < n_points) )
   {
   	++i;
   }

   if (n_points > i)
   {
      if (0 == i)
      {
         y = y_table[0];
	   }
      else
      {
         y1 = (y_table[i] - y_table[i-1]);
         y2 = y_table[i-1];
         x1 = (x - x_table[i-1]);
         x2 = (x_table[i] - x_table[i-1]);
         x3 = y1 * x1;

         result = ldiv(x3, x2);
         y3 = result.quot;

         y  = (int) (y3 + y2);
      }
   }
   else
   {
   	y = (int)y_table[n_points-1];
   }
   return (y);
}


/**
 *
 *TODO 查找一维线值
 * @param input
 * @param pTable1D 要查数组
 * @param length 要查数组长度
 * @return ret 线性查找的值
 */
signed short LIB_geTable1D(signed short input, const TABLE1D *  pTable1D, signed short length)
{
	signed short low = 0, mid = 0, high, find_flag = 0;
	signed short ret = 0;
	length = length - 1;
	high = length;
	if (length <= 0)
	{
		ret = -999; //只有一位-999返回
	}
	else
	{
		if (pTable1D[0].x < pTable1D[1].x)
		{
			//线性递增
			if (input < pTable1D[0].x)
			{
				ret = pTable1D[0].y;

			}
			else
			{
				if (input > pTable1D[length].x)
				{
					ret = pTable1D[length].y;
				}
				else
				{

					while (low <= high)
					{
						mid = (low + high) / 2;
						if (input < pTable1D[mid].x)
							(high = mid - 1);
						else if (input > pTable1D[mid].x)
							(low = mid + 1);
						else
						//return pTable1D[mid].y;
						{
							ret = pTable1D[mid].y;
							find_flag = 1; //找到值
							break;
						}

					}
					//没有找到值
					if (find_flag != 1)
					{
						if (pTable1D[mid].x > input)
						{
							TABLE1D table1D1 = (mid == 0) ? pTable1D[0] : pTable1D[mid - 1];
							TABLE1D table1D2 = pTable1D[mid];
							ret = (sint16) ((sint32) table1D1.y
									+ (sint32) (input - table1D1.x) * (sint32) (table1D2.y - table1D1.y)
											/ (sint32) (table1D2.x - table1D1.x));
						}
						else
						{
							TABLE1D table1D1 = pTable1D[mid];
							TABLE1D table1D2 = (mid == length) ? pTable1D[length] : pTable1D[mid + 1];
							ret = (sint16) ((sint32) table1D1.y
									+ (sint32) (input - table1D1.x) * (sint32) (table1D2.y - table1D1.y)
											/ (sint32) (table1D2.x - table1D1.x));
						}
					}

				}
			}

		}
		else
		{
			//线性递减
			if (input > pTable1D[0].x)
			{
				ret = pTable1D[0].y;

			}
			else
			{
				if (input < pTable1D[length].x)
				{
					ret = pTable1D[length].y;
				}
				else
				{
					//线性递减
					while (low <= high)
					{
						mid = (low + high) / 2;
						if (input > pTable1D[mid].x)
							(high = mid - 1);
						else if (input < pTable1D[mid].x)
							(low = mid + 1);
						else
						//return pTable1D[mid].y;
						{
							ret = pTable1D[mid].y;
							find_flag = 1; //找到值
							break;
						}
					}
					//没有找到值
					if (find_flag != 1)
					{
						if (pTable1D[mid].x < input)
						{
							TABLE1D table1D1 = (mid == 0) ? pTable1D[0] : pTable1D[mid - 1];
							TABLE1D table1D2 = pTable1D[mid];
							ret = (sint16) ((sint32) table1D1.y
									+ (sint32) (input - table1D1.x) * (sint32) (table1D2.y - table1D1.y)
											/ (sint32) (table1D2.x - table1D1.x));
						}
						else
						{
							TABLE1D table1D1 = pTable1D[mid];
							TABLE1D table1D2 = (mid == length) ? pTable1D[length] : pTable1D[mid + 1];
							ret = (sint16) ((sint32) table1D1.y
									+ (sint32) (input - table1D1.x) * (sint32) (table1D2.y - table1D1.y)
											/ (sint32) (table1D2.x - table1D1.x));
						}
					}
				}

			}
		}
	}
	return ret;
}



void quckly_sort_2(short unsigned int* a,int begin ,int end)
{
	short unsigned int start = a[begin];
	int pos;
	int left = begin;
	int right = end;

	while(left < right)
	{
		while(left <right && a[right] <= start)
		right--;
		a[left] = a[right];
		while(left <right && a[left] >= start)
		left++;
		a[right] = a[left];
	}
	a[left] = start;
	pos = right;

	if(begin < end)//递归调用
	{
		quckly_sort_2(a, begin , pos-1);
		quckly_sort_2(a, pos+1 , end);
	}
	return;
}


uint32 LPF(uint32 x,uint32 xFlt,uint16 dt,uint16 tau)
{

	sint32 xSuby =0 ;
	sint32 yAdd =0 ;
	xSuby = x - xFlt;
	yAdd = xSuby*dt/tau;
	xFlt = (uint32)(xFlt + yAdd);

	return xFlt;
}
