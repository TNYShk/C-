#include <stdio.h>
#include "ws1.h"

int main()
{
   	int x=2;
   	int y=5;
	
	
	HelloHexa();
	
	printf("10^-3 is %f\n",PowerofTen(-3));	
	printf("10^3 is %.f\n",PowerofTen(3)); /* for n>0, no floating point needed */
	
	PrintReverseNum(123456);
	
	printf("Reverse of 1023 is %d\n",ReverseInt(1023));
	printf("Reverse of -1023 is %d\n",ReverseInt(-1023));
	printf("before swap: x=%d, y=%d\n",x,y);
	Swap(&x,&y);
	printf("post swap: x=%d, y=%d\n",x,y);

	return 0;
}

