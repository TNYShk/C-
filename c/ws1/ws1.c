#include <stdio.h>

/* ***Declaration*** */
void HelloHexa();
double PowerofTen(int);
void PrintReverseNum(int);
void Swap(int*,int*);


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
	
	/*if(n==0)
	{
	   return 1.0;
	 }*/
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

/* ***Main*** */ 
int main()
{
   	int x=2;
   	int y=5;
	
	HelloHexa();
	
	printf("10^-3 is %f\n",PowerofTen(-3));	
	printf("10^3 is %.f\n",PowerofTen(3)); /* for n>0, no floating point needed */
	
	PrintReverseNum(123456);
	
	printf("before swap: x=%d, y=%d\n",x,y);
	Swap(&x,&y);
	printf("post swap: x=%d, y=%d\n",x,y);

	return 0;
}

