#include <stdio.h>
#include "ws1.h"


/* ***Definition*** */

/* **Exercise** 4 */
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

/* **Exercise** 5 */
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

/* **Exercise** 6 */
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

/* **Ex 6-Vers 2 */
int ReverseInt(int num)
{
   int modul;
   int ans=0;
   
   while(num)
   {
	modul=num%10;
	ans=ans * 10 + modul;
	num/=10;
   }
  return ans;	
}

/* **Exercise** 7 */
void Swap(int*a, int*b)
{
   int holder=*a;
   *a=*b;
   *b=holder;
}



