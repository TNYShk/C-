#include <stdio.h>
#include "ws1.h"


/* ***Definition*** */

/* **Exercise** 4 */
void HelloHexa()
{
	char phrase[] = {"\"Hello World!\""};

	char *ptr = phrase;
	printf("%s\n", phrase);
	
	while (*ptr)
	{
		printf("0x%x ",*ptr);
		++ptr;
	}
	printf("\n");
}

/* **Exercise** 5 */
double PowerofTen(int exponent)
{
	double base = 10.0;
	double ans = 1.0;
	
	if (0 > exponent)
	{
	   exponent = -exponent;
	   base = 1.0 / base;
	}
	
	while(exponent)
	{
	   ans *= base;
	   --exponent;
	}
	return ans;
}

/* **Exercise** 6 */
void PrintReverseNum(int number)
{
   printf("%d shall revese! to: ",number);
   
   while(number != 0)
   {
	printf("%d",number % 10);
	number /= 10;
   }
   
   printf("\n");
}

/* **Ex 6-Vers 2 */
int ReverseInt(int num)
{
   int sign = 1;
   int ans = 0;
   if (0 > num)
   {
     num *= -1;
     sign = -1;
   }
   
   while(num)
   {
	
	ans = ans * 10 + (num%10);
	num /= 10;
   }
  return ans*sign;	
}

/* **Exercise** 7 */
void Swap(int *a, int *b)
{
   int holder = *a;
   *a = *b;
   *b = holder;
}



