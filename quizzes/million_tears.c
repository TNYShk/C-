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

void PrintChar(char c)
{
	size_t i_max, index;
	static size_t Lut[ASCII] = {0};
	
	Lut[c] +=1; 
	
	
	if ('0'== c)
	{
		int i_max = Lut[0];
		int i,index = 0;
		
		for(i=1; i<128; ++i)
		{
			if (i_max < Lut[i])
			{
				i_max = Lut[i];
				index = i;
			}
		}
	
		while(i_max)
		{
			printf("%c",index);
			--i_max;
		}	
	
	memset(Lut,'0',ASCII);
	}
	return;
}

void OneMill(char c)
{
	
	static size_t Lut[128] = {0};
	size_t i;
	
	if ('0' != c)
	{
		Lut[c] +=1; 
	}
	else
	{
		int i_max = Lut[0];
		int i_index = 0;
		
		for(i=1; i<128; ++i)
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
	memset(Lut,'0',ASCII);

	}
	
return;
}

size_t CountBitLoopAsOn(long num)
{
	long temp = 0;
	size_t count = 0;

	while(num){
		temp = num -1;
		num = num&temp;
		++count;
	}
	return count;
}



int main()
{
	PrintChar('1');
	PrintChar('1');
	PrintChar('1');
	PrintChar('0');
	PrintChar('2');
	PrintChar('2');
	PrintChar('2');
	PrintChar('2');

	PrintChar('0');

	/*
	OneMill('1');
	OneMill('1');
	OneMill('1');
	OneMill('0');

	OneMill('2');
	OneMill('2');
	OneMill('1');
	OneMill('0');
	*/
	return 0;
}

/*
PrintChar('1');
	PrintChar('1');
	PrintChar('1');
	PrintChar('0');
printf("\nbits on are %ld\n",CountBitLoopAsOn(7));
printf("size of struct is %ld\n",sizeof(str_t));
printf("size of struct is %ld\n",SIZE_OF_TYPE(struct Str));
printf("OFFSET of struct is %ld\n",OFFSET(struct Str,f));

 */
