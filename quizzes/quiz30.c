

#include <stddef.h> /* size_t*/
#include <stdio.h> /*print */

#define ASCI (256)

int IsFound(char *arr, size_t len, char tofind);
static void EmptyLut(int *lut);
void CircularShift(char *arr, size_t len, int shift);
static void Reverse(char *arr,int from, int to);
static void Swap(char *a, char *b);

static int LUT[ASCI] = {0};



int main(void)
{
	char arr[5] = {'a', 'b', 'c','d','&'};
	char arrsy[5] = {'T', 'b', 'c','d','&'};
	printf("is T is arr? %d\n", IsFound(arr,5,'T'));
	printf("is a is arrsy? %d\n", IsFound(arrsy,5,'a'));
	printf("is T is arrsy? %d\n", IsFound(arrsy,5,'T'));
	printf("%s\n", arrsy);

	CircularShift(arrsy,5,3);
	printf("post shift by 3: %s\n", arrsy);

	return 0;
}

int IsFound(char *arr, size_t len, char tofind)
{
	size_t i = 0;
	EmptyLut(LUT);

	for(;i < len; ++i)
	{
		LUT[(int)arr[i]] = 1;
	}

	return LUT[(int)tofind];
}

static void EmptyLut(int *lut)
{
	int i = 0;
	for(i = 0; i<ASCI; ++i)
	{
		lut[i] = 0;
	}
}

void CircularShift(char *arr, size_t len, int shift)
{
	Reverse(arr, 0, len - 1);
	Reverse(arr,0, shift - 1);
	Reverse(arr, shift, len - 1);	
}

static void Reverse(char *arr, int from, int to)
{
	while(from < to)
	{
		Swap(&arr[from], &arr[to]);
		++from;
		--to;
	}
}

static void Swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}