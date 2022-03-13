#include <stdio.h>

void SwapP(int **a, int **b);



int main(void)
{
	int *p1;
	int *p2;
	int x,y;
	x = 3;
	y = 4;
	p1 = x;
	p2 = y;

	printf("p1 & %p\n",p1);
	printf("p1 * %d\n",*p1);
	printf("p2 & %p\n",p2);
	printf("p2 * %d\n",*p2);

	SwapP(&p1, &p2);

	printf("p1 & %p\n",p1);
	printf("p1 * %d\n",*p1);
	printf("p2 & %p\n",p2);
	printf("p2 * %d\n",*p2);
	return 0;
}

void SwapP(int **p1, int **p2){
	
	int *temp = *p1;
	
	*p1 = *p2;
	*p2 = temp;
}