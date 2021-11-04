#include <stdio.h>
#include "ws1.h"


/* ***Definition*** */
void HelloHexa()
{
	char phrase[]={"\"Hello World!\""};

	char *ptr = phrase;
	printf("%s\n",phrase);
	
	while (*ptr)
	{
		printf("0x%x ",*ptr);
		ptr++;
	}
	printf("\n");
}

double PowerofTen(int n)
{
	double base=10;
	double ans=1.0;
	
	if (n<0)
	{
	   n=-n;
	   base=0.1;
	}
	
	while(n)
	{
	   ans*=base;
	   n--;
	}
	return ans;
}

void PrintReverseNum(int number)
{
   printf("%d shall revese! to: ",number);
   
   while(number!=0)
   {
	printf("%d",number%10);
	number/=10;
   }
   
   printf("\n");
}

void Swap(int*a, int*b)
{
   int holder=*a;
   *a=*b;
   *b=holder;
}



