#include <stdio.h>
#include <stdlib.h> /* size_t */
#include <limits.h> /* CHAR_BIT */
#include <assert.h>
#include <string.h> 
#include "bit_array.h"


#define LONG_LEN (CHAR_BIT * (sizeof(unsigned long)))



int main(){

	static unsigned long bitty;
	size_t ans,ans1;

	
	char *str = NULL;
	char *str1 = NULL;
	

	str = calloc(CHAR_BIT,sizeof(long));
	str1 = calloc(CHAR_BIT,sizeof(long));
	assert(NULL != str);
	assert(NULL != str1);
	

	bitty = BitArraySetAll(bitty);
	printf("bitty is %lu\n",bitty);
	
	bitty = BitArrayResetAll(bitty);
	printf("reset all bitty is %ld\n",bitty);
	bitty = BitArraySetOn(bitty,1);
	printf("bitty set on,value is:  %ld\n",bitty);
	bitty = BitArraySetOn(bitty,2);
	printf("bitty set on value is:  %ld\n",bitty);
	str = BitArrayToString(bitty,str);
	printf("%s\n",str);

	ans = BitArrayCountOff(bitty);
	printf("%ld bits off \n",ans);
	bitty = BitArrayMirror(bitty);
	str1 = BitArrayToString(bitty,str1);
	printf("%s\n",str1);
	/*
	bitty = BitArrayResetAll(bitty);
	printf("reset all bitty is %ld\n",bitty);
	
	bitty = BitArraySetOn(bitty,0);
	printf("bitty set on 0:  %ld\n",bitty);
	bitty = BitArraySetOn(bitty,1);
	printf("bitty set on 1:  %ld\n",bitty);
	bitty = BitArraySetOn(bitty,2);
	printf("bitty set on 2:  %ld\n",bitty);
	str1 = BitArrayToString(bitty,str1);	

	ans1 = BitArrayCountOn(bitty);
	printf("%ld bits on \n",ans1);
	*/


	free(str);
	str = NULL;
	free(str1);
	str1= NULL;
	/*
	ans = BitArrayGetVal(bitty,63);
	printf("value of bit in location is %ld\n",ans);
	ans = BitArrayGetVal(bitty,62);
	printf("value of bit in location is %ld\n",ans);
	bitty = BitArrayMirror(bitty);
	printf("1 mirrored is %ld\n",bitty);
	
	bitty = BitArrayMirror(bitty);
	printf("bitty mirrored is %ld\n",bitty);

	bitty = BitArrayRotateRight(bitty,1);
	printf("rotate right %ld\n",bitty);
	
	bitty = BitArrayRotateLeft(bitty,2);
	printf("rotate left %ld\n",bitty);
	





	
	ans = BitArrayGetVal(bitty,9);
	printf("value of bit in location is %d\n",ans);

	ans1 = BitArrayCountOn(bitty);
	printf("%ld bits on \n",ans1);

	ans1 = BitArrayCountOff(39u);
	printf("%ld bits off \n",ans1);
	s
	ans = BitArrayCountOn(bitty);
	printf("onbits %d\n",ans);
	bitty = BitArraySetOn(bitty,8);
	printf("bitty is %ld\n",bitty);
	bitty= BitArrayFlip(bitty,2);
	printf("bitty is %ld\n",bitty);
	*/
	
	return 0;
}