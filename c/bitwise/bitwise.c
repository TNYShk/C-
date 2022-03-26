#include <stdio.h>  /* standard library, printf */
#include <stdlib.h> /* size_t*/

/***** Reviewed by Erez *****/

#include "bitwise.h"


#define UCHAR (256)
#define B3_5_ON (20)
#define INTBIT (32)




/*******exercise.1*********/
long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);
}
/*******exercise.2a*********/
int IsPowOf2(unsigned int n)
{
	unsigned int ans = n >> 1;
	
	return (0 == n % ans);
}
/*******exercise.2*********/
int IsPow2Loop(unsigned int n)
{
	unsigned int ans = n;
	
	while(0 == ans % 2)
	{
		ans /= 2;
	}
	
	return (1 == ans);
}


/*******exercise.3*********/
int AddOne(int n)
{
	int one = 1;
	
	while(n & one)
	{
		n ^= one;
		one <<=  1;	
	}
	
	n ^= one;
	
	return n;
}


static void Swap(int *start, int *end)
{
	while(start < end)
	{
		int t = *start;
		*start = *end;
		*end = t;
		++start;
		--end;
	}
}
/* private func for printing mirrored binary numbers */
static void MirrorBytes(unsigned int n,int swap)
{
	int bin[INTBIT] = {0};
	int i = 0;
	unsigned int k = 1<<31;
	unsigned int ans = 0;
	int m = INTBIT;
	int *ptr = NULL;
	int *start = NULL;
	
	ptr = bin;
	
	for(i = 0; i < m; ++i)
	{
		bin[INTBIT - 1 - i] = n % 2;
		n /= 2;
		printf("%d",bin[i]);
		ans += bin[INTBIT - 1 - i] * k;
		k = k >> 1;
		
	}
	printf("\nwhich is %u mirrored\n",ans);
	start = bin + m - 1;
	
	if (swap)
	{
		Swap(ptr,start);
	
	while(m)
	{
		printf("%d",*ptr);
		--m;
		ptr++;
	}
	}
	printf("\n");
}

static int CountBits(unsigned int n)
{
	int i;
	int x = 0;
	
	for(i = 0; n > 0; ++i)
	{
		if(1 == n%2)
		{
			++x;
		}
		n /= 2;
	}
	
	return x;
}

/*exercise 9a */
size_t CounterBits(unsigned int n)
{
	size_t ans = CountBits(n);
	
	return ans;
}
/********exercise 9b *************/
size_t CountSetBitsNoLoop(unsigned int i)
{
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	i = (i + (i >> 4)) & 0x0F0F0F0F; 
	i = (i & 0x33333333) + ((i >> 8) & 0x33333333);
	i = (i + (i >> 16)) & 0x0F0F0F0F; 
	return (i * 0x0101010101010101) >> 32;
}


/*********exercise 10*********/
void FloatPrintBits(float ff)
{
	unsigned int *ip = 0;
	float *fp = &ff;
	ip = (unsigned int *)fp;

	MirrorBytes(*ip,0);
}

void PrintThreeBitsOnElements(unsigned int *ar, size_t size)
{
	size_t i;
	for(i = 0; i < size; ++i)
	{
		unsigned int x = CountBits(ar[i]);
		
		if(x==3)
		{
			printf("-%d- ",ar[i]);
			MirrorBytes(ar[i],0);
		}
	}
}

/******** exercise 6 *********/
int IsBothIdxOn(unsigned char c)
{
	return (34 == (c & 34));
}

/******** exercise 6a, 
checks if 2nd bit OR 6th bit are on */
int IsOneOfIdxOn(unsigned char c)
{
	return !!(34 & c);
	/*return ( (2 == (c & 2)) || (32 == (c & 32)) );*/
}

unsigned int BitSwapByIdx(unsigned char c)
{
	char d = (c & B3_5_ON);
	switch(d)
	{
		case(B3_5_ON):
			return c;
		case(4):
		case(16):
			return (c^B3_5_ON);
	}
	return (c);
}

/*exercise 7 */
unsigned int ClosestDividedByHex(unsigned int num)
{
	unsigned int ans = num >> 4;
	return (ans * 16);
}

/* exercise 8, wont work with zero */
void BitwiseSwap(int *x, int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}


void MirrorByte(unsigned int n)
{
	printf("%d  is ",n);
	MirrorBytes(n,1);
}

unsigned int ByteMirrorWithoutLoop(unsigned int num)
{
 	num = (num  >> 16) | (num << 16);
    num = ((num >> 8) & 0x00FF00FF) | ((num << 8) & 0xFF00FF00);
    num = ((num >> 4) & 0x0F0F0F0F) | ((num << 4) & 0xF0F0F0F0);
    num = ((num >> 2) & 0x33333333) | ((num << 2) & 0xCCCCCCCC);
    num = ((num >> 1) & 0x55555555) | ((num << 1) & 0xAAAAAAAA);

    return num;
}


