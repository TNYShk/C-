#include <stdio.h> /* standard library, printf */
#include <stdlib.h> /* size_t*/

#include "bitwise.h"
#define UCHAR (256)
#define B3_5_ON (20)


int main()
{
	char c = 5;
	
	unsigned int ar[]={19,71,15,11,111};
	
	int size=sizeof(ar)/sizeof(ar[0]);

	PrintThreeBitsOnElements(ar,size);
	Pow2(1,7);
	printf("IsBothIdxOn %d\n", IsBothIdxOn(c));
	c = 100;
	printf("char %c IsBothIdxOn %d\n",c, IsBothIdxOn(c));
	printf("char %c either 2nd or 6th bit on %d\n",c, IsOneOfIdxOn(c));;
	c = 3;
	printf("3 BitSwapByIdx %d\n", BitSwapByIdx(c));;
	c = 48;
	printf("BitSwapByIdx %d\n", BitSwapByIdx(c));;
	printf("ClosestDividedByHex %u\n", ClosestDividedByHex(22));
	
	MirrorByte(18);
	printf("\n");

	printf("in #54, ON bits are: %lu\n",CounterBits(54));
	printf("Print Float bits:\n");
	FloatPrintBits(18.2);

	MirrorByte(20);
	
	
	return 0;
}
