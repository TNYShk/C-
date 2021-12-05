#include <stdio.h>
#include <stdlib.h> /* size_t */
#include <limits.h> /*for LONG_MAX */
#include <string.h> /* strncat*/
#include <assert.h>
#include "bit_array.h"

#define LONG_LEN (CHAR_BIT * (sizeof(unsigned long)))

#define m1 (0x5555555555555555)
#define m2 (0x3333333333333333)
#define m4 (0x0f0f0f0f0f0f0f0f)
#define m8 (0x00ff00ff00ff00ff)
#define m16 (0x0000ffff0000ffff)
#define h01 (0x0101010101010101)

static unsigned long lut_arr[] = {m1,m2,m4,m8,m16,h01};

static unsigned int lut_ar[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

bits_arr64_t BitArraySetAll(bits_arr64_t bit_array)
{
	bit_array = OFF - ON;
	return bit_array;

}

bits_arr64_t BitArrayResetAll(bits_arr64_t bit_array)
{
	bit_array = OFF;
	return bit_array;
}

char *BitArrayToString(bits_arr64_t bit_array, char *str)
{
	size_t index;
	char tmp[LONG_LEN] = {0};
	
	
	for (index = 0; index<LONG_LEN; ++index)
	{
		sprintf(tmp, "%d" ,BitArrayGetVal(bit_array, (LONG_LEN - 1) - index));
		strcat(str,tmp);
	}
	
	return str;
}

bits_arr64_t BitArraySetOn(bits_arr64_t bit_array, unsigned int index)
{
	
	bit_array |= (ON << (index));                                                                        
	return bit_array;
}

bits_arr64_t BitArraySetOff(bits_arr64_t bit_array, unsigned int index)
{
	bit_array &= ~(1ul << (index));                                                                        
	return bit_array;
}

bits_arr64_t BitArraySetBit(bits_arr64_t bit_array, unsigned int index, bit_t value)
{
	switch(value)
	{
		
		case (ON):
			return BitArraySetOn(bit_array,index);
		case (OFF):	
			return BitArraySetOff(bit_array,index);
	}
	return bit_array;
}	

bit_t BitArrayGetVal(bits_arr64_t bit_array, unsigned int index)
{
	
	return ((bit_array >> index) & ON);
}

bits_arr64_t BitArrayFlip(bits_arr64_t bit_array, unsigned int index)
{
	bit_array ^= (ON << (index % LONG_LEN)); 
	return bit_array;
}




size_t BitArrayCountOn(bits_arr64_t var)
{
	int set_nibble = 15;
	size_t answer;
	
	answer = lut_ar[var & set_nibble];
	answer += lut_ar[(var >> 4) & set_nibble];
	answer += lut_ar[(var >> 8) & set_nibble];
	answer += lut_ar[(var >> 12) & set_nibble];
	answer += lut_ar[(var >> 16) & set_nibble];
	answer += lut_ar[(var >> 20) & set_nibble];
	answer += lut_ar[(var >> 24) & set_nibble];
	answer += lut_ar[(var >> 28) & set_nibble];
	answer += lut_ar[(var >> 32) & set_nibble];
	answer += lut_ar[(var >> 36) & set_nibble];
	answer += lut_ar[(var >> 40) & set_nibble];
	answer += lut_ar[(var >> 44) & set_nibble];
	answer += lut_ar[(var >> 48) & set_nibble];
	answer += lut_ar[(var >> 52) & set_nibble];
	answer += lut_ar[(var >> 56) & set_nibble];
	answer += lut_ar[(var >> 60) & set_nibble];
	
	return answer;
}



size_t BitArrayCountOff(bits_arr64_t var)
{
	return (LONG_LEN - BitArrayCountOn(var));
}

bits_arr64_t BitArrayMirror(bits_arr64_t num)
{
	
	num = (num  >> 32) | (num << 32);
	num = ((num >> 16) & 0x0000ffff0000ffff) |((num << 16) & 0xffff0000ffff0000);
    num = ((num >> 8) & 0x00ff00ff00ff00ff) | ((num << 8) & 0xFF00FF00FF00FF00);
    num = ((num >> 4) & 0x0f0f0f0f0f0f0f0f) | ((num << 4) & 0xF0F0F0F0F0F0F0F0);
    num = ((num >> 2) & 0x3333333333333333) | ((num << 2) & 0xCCCCCCCCCCCCCCCC);
    num = ((num >> 1) & 0x5555555555555555) | ((num << 1) & 0xAAAAAAAAAAAAAAAA);

    return num;
}

bits_arr64_t BitArrayRotateRight(bits_arr64_t bit_array, unsigned int rotation)
{
	size_t temp = (bit_array >> rotation) | (bit_array << (LONG_LEN - rotation));
	
	return temp;
}


bits_arr64_t BitArrayRotateLeft(bits_arr64_t bit_array, unsigned int rotation)
{
	size_t temp = (bit_array << rotation) | (bit_array >> (LONG_LEN - rotation));
	return temp;
}

/*
bits_arr64_t BitArrayRotateLeft(bits_arr64_t bit_array, unsigned int rotation)
{
	int i=1;
	size_t bitArLut[64];
	size_t temp;
	bitArLut[0] = 1ul;
	for(i=1;i<64;++i)
	{
		bitArLut[i] = bitArLut[i-1] * 2ul;
		
	}
	temp = bit_array * bitArLut[rotation];
	return temp;
}
*/

/*
size_t BitArrayCountOn(bits_arr64_t var)
{
	
	long temp = 0;
	size_t count = 0;
	
	while (var != 0)
	{
		temp = var-1;
		var = var & temp;
		++count;
	}
	
	return count;
}
*/