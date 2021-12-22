/***********************************
 * Sorted Linked List WS		   *
 *           	                   *
 * by Tanya					       *
 *   		Dec 10, 2021	       *
 *                                 *
 * Reviewer:                  	   *
 ***********************************/

#include <stdio.h>	/*sprintf */
#include <stdlib.h> /* size_t */
#include <limits.h> /*for LONG_MAX */
#include <string.h> /* strncat*/
#include <assert.h> /* assert */
#include "bit_array.h"

#define LONG_LEN (CHAR_BIT * (sizeof(unsigned long))) /* 64*/
#define LONE (1ul)

#define m1 (0x5555555555555555)
#define m2 (0x3333333333333333)
#define m4 (0x0f0f0f0f0f0f0f0f)
#define m8 (0x00ff00ff00ff00ff)
#define m16 (0x0000ffff0000ffff)
#define h01 (0x0101010101010101)

static const unsigned int lut_ar[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};


bits_arr64_t BitArraySetAll(bits_arr64_t bit_array)
{
	return (bit_array = OFF - ON);
}

bits_arr64_t BitArrayResetAll(bits_arr64_t bit_array)
{
	return (bit_array = OFF);
}

char *BitArrayToString(bits_arr64_t bit_array, char *str)
{
	size_t index = 0;
	char tmp[LONG_LEN] = {0};
	assert (NULL != str);
	
	for (index = LONE; index < LONG_LEN; ++index)
	{
		sprintf(tmp, "%d" ,BitArrayGetVal(bit_array, (LONG_LEN - LONE) - index));
		strcat(str,tmp);
	}
	
	return str;
}

bits_arr64_t BitArraySetOn(bits_arr64_t bit_array, unsigned int index)
{
	assert (LONG_LEN > index);                                                               
	return (bit_array |= (LONE << (index)));   
}

bits_arr64_t BitArraySetOff(bits_arr64_t bit_array, unsigned int index)
{
	assert (LONG_LEN > index);                                                                      
	return (bit_array &= ~(LONE << (index)));
}

bits_arr64_t BitArraySetBit(bits_arr64_t bit_array, unsigned int index, bit_t value)
{
	assert (LONG_LEN > index);
	return (BitArraySetOff(bit_array, index) | ((bits_arr64_t)value << index));
	
}	

bit_t BitArrayGetVal(bits_arr64_t bit_array, unsigned int index)
{
	assert (LONG_LEN > index);
	return ((bit_array >> index) & LONE);
}

bits_arr64_t BitArrayFlip(bits_arr64_t bit_array, unsigned int index)
{
	assert (LONG_LEN > index);
	return (bit_array ^= (LONE << index ));
}


size_t BitArrayCountOn(bits_arr64_t var)
{
	int set_nibble = 0xFul;
	size_t answer = 0;
	
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
	num = ((num >> 16) & m16) |((num << 16) & 0xffff0000ffff0000);
    num = ((num >> 8) & m8) | ((num << 8) & 0xFF00FF00FF00FF00);
    num = ((num >> 4) & m4) | ((num << 4) & 0xF0F0F0F0F0F0F0F0);
    num = ((num >> 2) & m2) | ((num << 2) & 0xCCCCCCCCCCCCCCCC);
    num = ((num >> LONE) & m1) | ((num << LONE) & 0xAAAAAAAAAAAAAAAA);

    return num;
}

bits_arr64_t BitArrayRotateRight(bits_arr64_t bit_array, unsigned int rotation)
{
	return bit_array >> (rotation & (LONG_LEN - LONE)) | bit_array << (LONG_LEN - (rotation & (LONG_LEN - LONE)));
}

bits_arr64_t BitArrayRotateLeft(bits_arr64_t bit_array, unsigned int rotation)
{
	return bit_array << (rotation & (LONG_LEN - LONE)) | bit_array >> (LONG_LEN - (rotation & (LONG_LEN - LONE)));
}


/* other options


int CountOnBots(bits_arr64_t var)
{
    var -= (var >> 1) & m1;             //put count of each 2 bits into those 2 bits
    var = (var & m2) + ((var >> 2) & m2); //put count of each 4 bits into those 4 bits 
    var = (var + (var >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    return (var * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}
*/




/*
bits_arr64_t BitArrayRotateLeft(bits_arr64_t bit_array, unsigned int rotation)
{
	int i=1;
	size_t bitArLut[64];
	size_t temp;
	bitArLut[0] = 1ul;
	for(i=1;i<32;++i)
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
