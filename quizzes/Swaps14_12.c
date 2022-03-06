#include <stdio.h>
#include <stdio.h>
#include <assert.h>

void SwapInts(int *a, int *b);
void StupidSwap(int *a, int *b);
void SwapVP(void **p1, void **p2);

#define SIZE_OF_TYPE(a) ((size_t)(1 + (a *)0))


void SwapInts(int *a, int *b)
{
	int temp = *a;
	assert (a != b);
	*a = *b;
	*b = temp;
}


void SwapVP(void **p1, void **p2){
	
	void *temp = *p1;
	
	*p1 = *p2;
	*p2 = temp;
}

void StupidSwap(int *a, int *b)
{
    int *tmp = a;
    *a = *b;
    *b = *tmp;
}

int main()
{
	void *p1 = NULL;
	void *p2 = NULL;
	size_t z = 5;
	int x = 3,y = 7;
	

	p1=(void*)&x;
	p2=(void*)&z;

	/*StupidSwap(&x, &y);*/

	printf("x is: %d, z is: %ld", x, z);

	printf("p1 is %x\n",p1);

	printf("p2 is %x\n",p2);

	SwapVP(&p1,&p2);
	printf("\npost p1 is %x\n",p1);

	printf("post p2 is %x\n",p2);
	printf("x is: %d, z is: %ld", x, z);
	return 0;
}