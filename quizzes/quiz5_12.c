#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



void PrintMissingLut(int *arr, int size)
{
	int i = size + 2;
	int *new_ar = (int*)calloc((size+2),sizeof(size_t));
	if(NULL != new_ar){

	for(i = 0; i<size; ++i)
	{
		new_ar[arr[i]] = arr[i];
	}
	printf("LUT: missing numbers are: ");
	for (i=1;i<=size+2; ++i)
	{
		if (new_ar[i] == 0)
			printf("%d ",i);
	}
	free(new_ar);
	new_ar = NULL;
	}
}

void PrintMissingMat(int *arr, size_t length)
{
	size_t org_sum = 0;
	size_t missing1 = 0, missing2 = 0, diff = 0;
	float  avg = 0.0;
	size_t i = 0;
	
	
	avg = (1 + length+2) / 2.0;

	org_sum = avg * (length+2);
	diff = org_sum;
	
	for(i = 0; i<length ; ++i)
	{
		diff -= arr[i];
	}
	
	
	for (i = 1; i <= length; ++i) /*up to len */
	{
		if((size_t)arr[i-1] != i)
		{
			missing1 = i;
			break;
		}
	}
	
	missing2 = diff - missing1; 
	printf("\nMATH: missing nums are %ld and %ld\n", missing1, missing2);

}



void PrintMissXOR(int arr[], int arr_size)
{
    int xor_arr_size = arr[0];
    int xor_all = 1;
    int xor_combined = 0;
    int i = 0;
    int leastsig = 1;
    int notset_x = 0;
    int set_y = 0;
    int found = 0;

    for(i = 1; i < arr_size; ++i)
    {
        xor_arr_size ^= arr[i];
    }

    for(i = 2; i <= arr_size + 2; ++i)
    {
        xor_all ^= i;
    }

    xor_combined = xor_all ^ xor_arr_size;


    while(0 == found)
    {
        if((xor_combined & leastsig) == leastsig)
        {    
            found = 1;
        }
        else
        {
            leastsig <<= 1;
        }
    }
    
    for(i = 1; i <= arr_size +2; ++i)
    {
        if((i & leastsig) > 0)
        {
            set_y ^= i;
        }
        
        else
        {
            notset_x ^= i;
        }
    }

    for(i = 0; i < arr_size; ++i)
    {    
        if((arr[i] & leastsig) > 0)
        {
            set_y ^= arr[i];
        }
        
        else
        {
            notset_x ^= arr[i];
        }
    }


    printf("XOR: the 2 missing numbers are %d and %d\n", set_y, notset_x);
}






int main()
{
	int ar[] = {1,6,3,5};
	int ar2[]= {3,5,2};
	int lenfth = sizeof(ar)/sizeof(ar[0]);
	
	PrintMissingLut(ar,lenfth);
	PrintMissingMat(ar,lenfth);
	PrintMissXOR(ar,lenfth);
	printf("\n");
	PrintMissingLut(ar2,3);
	PrintMissingMat(ar2,3);
	PrintMissXOR(ar2,3);



	return 0;
}






