/*
 * mathlib.c
 *
 *  Created on: 2016��4��22��
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
/*Function: �����Ŵ���                  */
/*��ڲ���������������������            */
/*���ڲ������������������              */
/****************************************/
unsigned int sqrt_16(unsigned long M)
{
    unsigned int N, i;
    unsigned long tmp, ttp;   // �����ѭ������
    if (M == 0)               // �����������������ҲΪ0
        return 0;
    N = 0;
    tmp = (M >> 30);          // ��ȡ���λ��B[m-1]
    M <<= 2;
    if (tmp > 1)              // ���λΪ1
    {
        N ++;                 // �����ǰλΪ1������ΪĬ�ϵ�0
        tmp -= N;
    }
    for (i=15; i>0; i--)      // ��ʣ���15λ
    {
        N <<= 1;              // ����һλ
        tmp <<= 2;
        tmp += (M >> 30);     // ����
        ttp = N;
        ttp = (ttp<<1)+1;
        M <<= 2;
        if (tmp >= ttp)       // �������
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
 *TODO ����һά��ֵ
 * @param input
 * @param pTable1D Ҫ������
 * @param length Ҫ�����鳤��
 * @return ret ���Բ��ҵ�ֵ
 */
signed short LIB_geTable1D(signed short input, const TABLE1D *  pTable1D, signed short length)
{
	signed short low = 0, mid = 0, high, find_flag = 0;
	signed short ret = 0;
	length = length - 1;
	high = length;
	if (length <= 0)
	{
		ret = -999; //ֻ��һλ-999����
	}
	else
	{
		if (pTable1D[0].x < pTable1D[1].x)
		{
			//���Ե���
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
							find_flag = 1; //�ҵ�ֵ
							break;
						}

					}
					//û���ҵ�ֵ
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
			//���Եݼ�
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
					//���Եݼ�
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
							find_flag = 1; //�ҵ�ֵ
							break;
						}
					}
					//û���ҵ�ֵ
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

	if(begin < end)//�ݹ����
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
