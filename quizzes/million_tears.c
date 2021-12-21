#include <stdio.h>
#include <string.h>

#define SIZE_OF_TYPE(a) ((size_t)(1+(a*)0))


#define OFFSET2(S,f) (SIZE_OF_TYPE(S)- SIZE_OF_TYPE(f))

#define OFFSET(S, f) ((size_t)&(((S *)0)->f) )

#define ASCII (256)

typedef struct Str
{
	int x;
	float f;
	double d;
}str_t;



void ResetLut(size_t *arr);
void AMillionChars(char c);
size_t CharCounter(size_t *arr);
size_t CountBitLoopAsOn(long num);




void ResetLut(size_t *arr)
{
	*arr = 0;
}

void AMillionChars(char c)
{
	static size_t Lut[ASCII] = {0};

	if ('0' == c)
	{
		printf("char was inserted %ld times!\n", CharCounter(Lut));
	}
	else
	{
		Lut[c] += 1;
	}
}




size_t CharCounter(size_t *arr)
{
	size_t i_max = 0 , index = 0;
	
	
	int i = 0;
		
		for(i = 0; i < ASCII; ++i)
		{
			index = arr[i];
			if(index > i_max)
			{
				i_max = index;
			}

		ResetLut(&arr[i]);
		}	
	return i_max;
}
	

/*
void OneMill(char c)
{
	
	static size_t Lut[ASCII] = {0};
	size_t i;
	
	if ('0' != c)
	{
		Lut[c] += 1; 
	}
	else
	{
		size_t i_max = Lut[0];
		size_t i_index = 0;
		
		for(i=1; i<256; ++i)
		{
			if (i_max < Lut[i])
			{
				i_max = Lut[i];
				i_index = i;
			}
		}
	while(i_max)
	{
		printf("%c",i_index);
		--i_max;
	}	
	ResetLut(Lut);

	}
	
return;
}
*/

size_t CountBitLoopAsOn(long num)
{
	long temp = 0;
	size_t count = 0;

	while(num)
	{
		temp = num - 1;
		num &= temp;
		++count;
	}
	return count;
}



int main()
{
	int i = 0;

	for (i = 1; i < 10; ++i)
	{
		AMillionChars('a');
	}
	AMillionChars('0');
	for (i = 0; i < 20; ++i)
	{
		AMillionChars('t');
	}
	AMillionChars('0');
	for (i = 0; i < 40; ++i)
	{
		AMillionChars('t');
	}
	AMillionChars('0');
	
	
/*

printf("\nbits on are %ld\n",CountBitLoopAsOn(7));
printf("size of struct is %ld\n",sizeof(str_t));
printf("size of struct is %ld\n",SIZE_OF_TYPE(struct Str));
printf("OFFSET of struct is %ld\n",OFFSET(struct Str,f));

*/
	
	
	return 0;
}


