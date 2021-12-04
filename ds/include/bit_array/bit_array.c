#include <stdio.h>
#include <stdlib.h> /* size_t */
#include <limits.h> /*for LONG_MAX */
#include <string.h> /* strncat*/
#include <assert.h>
#include "bit_array.h"

#define LONG_LEN (8 * (sizeof(unsigned long)))

#define m1 (0x5555555555555555)
#define m2 (0x3333333333333333)
#define m4 (0x0f0f0f0f0f0f0f0f)


bits_arr64_t BitArraySetAll(bits_arr64_t bit_array)
{
	bit_array = ULONG_MAX;
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
	char *tmp = NULL;
	tmp = calloc(8,sizeof(unsigned long));
	
	for (index = 1; index<32; ++index)
	{
		sprintf(tmp, "%d" ,BitArrayGetVal(bit_array, 63 - index));
		strcat(str,tmp);
	}
	printf("%s\n",str);
	free(tmp);
	tmp = NULL;
	return str;
}

bits_arr64_t BitArraySetOn(bits_arr64_t bit_array, unsigned int index)
{
	
	bit_array |= (ON << (index % LONG_LEN));                                                                        
	return bit_array;
}

bits_arr64_t BitArraySetOff(bits_arr64_t bit_array, unsigned int index)
{
	bit_array &= ~(ON << (index % LONG_LEN));                                                                        
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
	return -1;
}	

bit_t BitArrayGetVal(bits_arr64_t bit_array, unsigned int index)
{
	long unsigned move2bit =  (ON << (index % LONG_LEN));
	long unsigned compare2bit = move2bit & bit_array;
	
	return (move2bit == compare2bit);
}

bits_arr64_t BitArrayFlip(bits_arr64_t bit_array, unsigned int index)
{
	bit_array ^= (ON << (index % LONG_LEN)); 
	return bit_array;
}

size_t BitArrayCountOn(bits_arr64_t var)
{
    var -= (var >> 1) & 0x5555555555555555;   							  /* binary 101010101010101010101010101010101010101010101010101010101010101 */          
    var = (var & 0x3333333333333333) + ((var >> 2) & 0x3333333333333333); /* binary 11001100110011001100110011001100110011001100110011001100110011 */
    var = (var + (var >> 4)) & 0x0f0f0f0f0f0f0f0f;       				  /* binary 111100001111000011110000111100001111000011110000111100001111 */
    
    return (var * 0x0101010101010101) >> 56;  							  /* binary 100000001000000010000000100000001000000010000000100000001 */

}



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

size_t BitArrayCountOff(bits_arr64_t var)
{
	return (64 - BitArrayCountOn(var));
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
	int i=1;
	size_t bitArLut[64];
	size_t temp;
	bitArLut[0] = 1;
	for(i=1;i<64;++i)
	{
		bitArLut[i] = bitArLut[i-1] * 2;
		
	}
	temp = bit_array * bitArLut[rotation];
	return temp;
}
/*
bits_arr64_t BitArrayRotateLeft(bits_arr64_t bit_array, unsigned int rotation)
{
	size_t temp = (bit_array << rotation) | (bit_array >> (63 - rotation));
	return temp;
}
*/