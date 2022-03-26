#include <stdio.h>
#include <stdlib.h>


int IsSumFound(int *, int, int);



int IsSumFound(int *sorted_ar, int target, int size)
{
	int *left = sorted_ar;
	int *right = &sorted_ar[size-1];
	
	while(left<right)
	{
		int sum = *left + *right;
		if(sum == target)
		{
			printf("found target %d at\nlocation a: %p\nlocation b: %p\n",target,left,right);
			
			return 1;
		}
		if(sum > target)
			--right;
		else
		{
			++left;
		}
	}

	return 0;
}

int main (void)
{
	int ar[5]= {2,4,7,12,14};
	int x = IsSumFound(ar,21,5);
	printf("ar[0] location %p\n",&ar[0]);
	printf("ar[1] location %p\n",&ar[1]);
	printf("ar[2] location %p\n",&ar[2]);




	return 0;
}