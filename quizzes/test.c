#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct s
{
	unsigned int i : 2;
	unsigned c : 1;
	unsigned short s : 3;
	int *j;
	unsigned char x : 2;
}s_t;

static const unsigned int lut_ar[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};


/* Q6 */
size_t CountSetBits(unsigned char ch)
{
	char mask = 0xFu;
	int iter = 0;
	size_t counter = 0;

	while(ch)
	{
		counter += lut_ar[ch & mask];
		ch >>= 4;
		++iter;
	}

	return counter;
}

/* Q4 */
unsigned MirrorBitsInByte(unsigned char ch)
{
	int index = 0;
	unsigned char result = 0;

	for(index =0; index<CHAR_BIT; ++index)
	{
		result <<= 1;
		result |= ch & 1;
		ch >>=1;
	}
	return result;
}
/* Q4 v.2 */
unsigned char ByteMirror(unsigned char cc)
{
	cc = (cc >> 4u) | (cc<<4u);
	cc = ((cc >> 2u) & 0x33) | ((cc << 2u) & 0xCC);
	cc = ((cc >> 1u) & 0x55) | ((cc << 1u) & 0xAA);
	return cc;
}

/* Q5 */
int FlipBit(int val, unsigned int n)
{
	
	unsigned int mask = 1u;
	assert (n < 32);
	mask <<= n;
	return (val^mask);
}

/* Q6 */
size_t CountOnBitsByte(char byte)
{
	size_t count = 0;
	while(byte)
	{
		byte &= (byte-1);
		++count;
	}
	return count;
}

/* Q6 ver 2.1 */
size_t CountOnBB(unsigned char cc)
{
	char max_nible = 15u;
	size_t counter = 0;
	counter = lut_ar[cc & max_nible];
	counter += lut_ar[(cc >> 4) & max_nible];
	
	return counter;
}

/* Q8 */
char RotateLeft(char byte, unsigned int nbits)
{
	assert(8 > nbits);
	return ( (byte << nbits) | ( byte >> (CHAR_BIT - nbits) ));
}
/* Q9 */
void SwapPtrs(int **p1, int **p2)
{
	int *temp = *p1;
	*p1 = *p2;
	*p2 = temp;
	
}
/* Q11.1 */
size_t Strlen(const char *str)
{
	size_t index = 0;
	assert(NULL != str);
	while( *str != '\0')
	{
		++str;
		++index;
	}
	return index;
}

int StrCmp(const char *s1, const char *s2)
{
	while (s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}


char *StrnCpy(char *dest, const char *src, size_t len)
{
	size_t index = 0;
	char *temp_dest = dest;
	
	while (len)
	{
		*(temp_dest + index) = *(src + index);
		++index;
		--len;
	}
	*(temp_dest + index + 1) = '\0';
	return dest;
}

char *StrCpy(char *dest, const char *src)
{
	size_t length = Strlen(src);
	char *temp = StrnCpy(dest, src, length);
	return temp;
}

char *StrCat(char *dest, const char *src)
{
	size_t dest_len = strlen(dest);
	size_t src_len = strlen(src);
	char * temp = dest + dest_len;

	dest = StrnCpy(temp, src, src_len);
	return dest;
}
/*end of Q11 */

/* Q12 */
unsigned long GetFibonacci(unsigned int n)
{
	int index = 2;
	int ans = 1;
	int *fibo = (int *)calloc(1+n,sizeof(size_t));
	assert (fibo != NULL);
	fibo[0] = 1;
	fibo[1] = 1;

	while(index <= n)
	{
		fibo[index] = fibo[index-1] + fibo[index-2];
		++index;
	
	}
	
	ans = fibo[n-1];

	free(fibo);
	fibo = NULL;
	return ans;
}

int anotherFibo(int nelement)
{
	int ans = 1, x1 = 1, x2 = 1;
	
	while(nelement > 2)
	{
		ans = x1 + x2;
		x1 = x2;
		x2 = ans;
		--nelement;
	}
	return ans;

}
/* Q13 */
void IntToString(int num, char *str)
{
	assert(NULL != str);
	sprintf(str, "%d",num);
}

/*Q15 */
void SwapIntVal(int *a, int *b)
{
	int tmp = *a;
	printf("a is  %d and b  %d\n",*a,*b);
	*a = *b;
	*b = tmp;
	printf("a is now %d and b  %d\n",*a,*b);
}
/*Q15 */
void SwapIntXOR(int *a, int *b)
{
	printf("a is  %d and b  %d\n",*a,*b);
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
	printf("a is now %d and b  %d\n",*a,*b);
}
/*Q15 */
void SwapInts(int *a, int *b)
{
	printf("a is  %d and b  %d\n",*a,*b);
	*b = *a * *b;
	*a = *b / *a;
	*b = *b / *a;
	printf("a is now %d and b  %d\n",*a,*b);
}


void foo()
{
	char *s1 = "hello";
	char s2[] = "hello";
	char *s3 = s1;
	printf("%lu %lu %lu %lu\n",sizeof(s1),sizeof(s2),strlen(s1),strlen(s2));

	s3[0] = 'H';
	printf("%s\n",s3);
}


int main()
{
	char strong[] = "Hell";
	char s2[] = "Help";
	char *s3 = NULL;
	int *p1;
	int *p2;
	int x = 5,y = 6;
	
	/*s_t sticky; */
	
	

	s3 = (char *)calloc(100, sizeof(char));
	p1= &x;
	p2 = &y;
	printf("a is now %x and b  %x\n",p1,p2);
	SwapPtrs(&p1,&p2);
	printf("a is now %x and b  %x\n",p1,p2);
	printf("\nlength of %s is %ld\n",strong, Strlen(strong));
	printf("\nanother fibo element 9 is %d\n", anotherFibo(9) );
	/*
	printf("fibo 9 is %ld\n",GetFibonacci(9));
	printf("size of sticky is: %ld\n", sizeof(s_t));
	printf("on bits in 251 is %ld\n", CountSetBits(251));
	printf("On bits in 255 is %ld\n", CountOnBitsByte(255));
	printf("On BB in 255 is %ld\n", CountOnBB(255));
	
	printf("mirrored 7 is %d\n", MirrorBitsInByte(7));
	printf("mirror mirror 7 is %d\n", ByteMirror(7));
	printf("flip bit 1 in 7 will be %d\n", FlipBit(7,1));
	printf("rotate left 4 1 time, will be %d\n", RotateLeft(7,2));
	printf("\n----------------string lib-------------------------");
	printf("\nlength of %s is %ld\n",strong, Strlen(strong));
	printf("\nstrcmp of %s&%s is %d\n",strong,s2, StrCmp(strong,s2));
	StrCpy(s3,s2);
	printf("\nstrcpy s3 is %s\n",s3);
	StrCat(s3, strong);
	printf("\nstrcat is %s\n", s3 );
	IntToString(5, s3);
	printf("\npost int to str is %s\n", s3 );
	SwapIntVal(&x, &y);
	SwapIntXOR(&x, &y);
	SwapInts(&x, &y);
	printf("sizeof short is %ld\n",sizeof(short));
	printf("sizeof unsigned int is %ld\n",sizeof(unsigned int));
	free(s3);
	s3 = NULL;
	/*foo();*/
		return 0;
}