#include <stdio.h> /* standard library, printf */
#include <stdlib.h> /* size_t*/

unsigned int CountCouples(unsigned int check);
unsigned int CountCouples1(unsigned int check);
int q3(long num);


unsigned int CountCouples(unsigned int check)
	{
	unsigned int m = 3;
	unsigned int k = 1<<31;
	int counter = 0;
	do
	{
		if((check & m)== m)
		{
			++counter;
		}

		m=m<<1;
	}while (m<k);

	return counter;
	}
	
unsigned int CountCouples1(unsigned int check)
{
	unsigned int m=3;

	int counter=0;
	do
	{
	if((check&m)==m)
	{
		++counter;
	}
	check= check>>1;
	
	}while (check);
	return counter;
}

int q3(long num)
{
	int x = 0;
	long temp = 0;
	int count = 0;
	
	while (num !=0)
	{
		temp=num-1;
		num= num&temp;
		++count;
		++x;
	}
	printf("loops %d\n",x);
	return count;
}


static size_t CountBits(unsigned long n)
{
	
	int i;
	size_t x=0;
	int loop=0;
	for(i=0;n>0;++i)
	{
		if(n%2==1)
			x++;

		n/=2;
		loop++;
	}
	printf("looped %d\n",loop);
	return x;
}

int main (void){
	unsigned int check=118;
	unsigned int check1=14;
	long num=96;
	printf("couple num is %u\n",CountCouples(check1));
	printf("couple1 num is %u\n",CountCouples1(check1));
	printf("countbitson num is %lu\n",CountBits(num));
	printf("q3 is %u\n",q3(num));
	return 0;
}

