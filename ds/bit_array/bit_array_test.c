#include <stdio.h>
#include <stdlib.h> /* size_t */
#include <limits.h> /* CHAR_BIT */
#include <assert.h>
#include <string.h> 
#include "bit_array.h"


#define LONG_LEN (CHAR_BIT * (sizeof(unsigned long)))

void TestOne();
void TestTwo();


static void PrintBits(unsigned char byte)
{
	int string[1] = {0};
	unsigned char bit_mask = 1u;
	
	while(byte)
	{
		
		*string = byte&bit_mask;
		byte >>= 1;
		printf("%d",*string);
	}
	printf("\n");
	
}


int main(void)
{

	TestOne();
	TestTwo();
	
	return 0;
}

void TestOne()
{
static unsigned long bitty;
	size_t ans;

	
	char *str = NULL;
	char *str1 = NULL;
	

	str = calloc(CHAR_BIT,sizeof(long));
	str1 = calloc(CHAR_BIT,sizeof(long));
	assert(NULL != str);
	assert(NULL != str1);
	
	
	printf("\n\t***********************-Test-1-*********************************\n\n");
	bitty = BitArraySetAll(bitty);
	printf("bitty is %lu\n",bitty);
	
	bitty = BitArrayResetAll(bitty);
	printf("reset all bitty is %ld\n",bitty);
	bitty = BitArraySetOn(bitty,1);
	printf("bitty set on,value is:  %ld\n",bitty);
	bitty = BitArraySetBit(bitty,2,1);
	/* bitty = BitArraySetOn(bitty,2);  */
	printf("bitty set on value is:  %ld\n",bitty);
	str = BitArrayToString(bitty,str);
	printf("%s\n",str);
	bitty = BitArrayFlip(bitty,2);
	printf("flipped idx2: %ld\n",bitty);
	PrintBits(BitArrayFlip(bitty,2));

	bitty = BitArrayFlip(bitty,2);
	printf("flipped again idx2: %ld\n",bitty);

	ans = BitArrayGetVal(bitty,63);
	printf("value of bit in location 63 is %ld\n",ans);
	ans = BitArrayGetVal(bitty,2);
	printf("value of bit in location 2 is %ld\n",ans);
	ans = BitArrayCountOff(bitty);
	printf("%ld bits off \n",ans);
	ans = BitArrayCountOn(bitty);
	printf("%ld bits ON \n",ans);
	
	bitty = BitArrayRotateLeft(bitty,2);
	
	printf("post 2 left rotations\n%s\n",BitArrayToString(bitty,str1));

	free(str);
	str = NULL;
	free(str1);
	str1 = NULL;

}

void TestTwo()
{
	static unsigned long bitty;
	size_t ans = 0, ans1 = 0;

	char *str = NULL;
	char *str1 = NULL;
	

	str = calloc(CHAR_BIT,sizeof(long));
	str1 = calloc(CHAR_BIT,sizeof(long));
	assert(NULL != str);
	assert(NULL != str1);
	printf("\n\t***********************-Test-2-*********************************\n\n");
	
	bitty = BitArraySetOn(bitty,5);
	bitty = BitArraySetOn(bitty,7);
	PrintBits(bitty);
	ans = BitArrayGetVal(bitty,62);
	printf("value of bit in location 62 is %ld\n",ans);
	bitty = BitArrayMirror(bitty);
	printf("1 mirrored is %ld\n",bitty);
	
	bitty = BitArrayMirror(bitty);
	printf("bitty mirrored is %ld\n",bitty);

	bitty = BitArrayRotateRight(bitty,1);
	printf("rotate right %ld\n",bitty);
	PrintBits(bitty);
	printf("bitty\n\t%s\n",BitArrayToString(bitty,str));
	
	bitty = BitArrayRotateLeft(bitty,2);
	printf("rotate left %ld\n",bitty);

	ans = BitArrayGetVal(bitty,6);
	printf("value of bit in index 7 is %ld\n",ans);

	ans1 = BitArrayCountOn(bitty);
	printf("%ld bits on \n",ans1);

	ans1 = BitArrayCountOff(39u);
	printf("%ld bits off \n",ans1);
	ans = BitArrayCountOn(bitty);
	printf("onbits %ld\n",ans);
	bitty = BitArraySetOn(bitty,8);
	printf("bitty is %ld\n",bitty);
	bitty= BitArrayFlip(bitty,2);
	printf("Flipped bitty is %ld\n",bitty);
	printf("FLipped bitty\n\t%s\n",BitArrayToString(bitty,str1));

	free(str);
	str = NULL;
	free(str1);
	str1= NULL;
	
	
}