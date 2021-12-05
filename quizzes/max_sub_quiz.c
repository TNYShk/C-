#include <stdio.h>

int FindMaxSub(const int *arr, size_t ar_len)
{
	size_t start =0;
	size_t end = 0;
	int untillnow = *arr;
	int global_max=*arr;
	for(end=1;end<ar_len; ++end)
	{
		untillnow= *(arr+end) + untillnow * (untillnow>0);
		if (untillnow == *(arr+end)){
			start=end;
		}
		printf("what is >0 %d\n",(untillnow>0));
	if (global_max < untillnow){
		global_max= untillnow;
		printf("start is %d\n", start);
		printf("end is %d\n", end);
		}
	}
	return global_max;
}



int maxLocalSum(int *ar, int length)
{
	int *start=ar;
	int *run=ar+1;
	int max_sum,cur_sum = *start;
	
	while(run<ar+length)
	{
		cur_sum = *start + *run ;
		
		if(cur_sum > max_sum)
		{
			max_sum=cur_sum;
			cur_sum= *start;
			printf("start is %ld\n",start-ar);
			
			if(*start < *run)
			{
			start=run;
			}
			
		}
	run++;
	}
	
	return max_sum;
}


int main(){

	int arr[]={-2,1,-3,4,-1,2,3,-5,4};
	int arr1[]={-1,2,4,0};
	int len= sizeof(arr)/sizeof(int);
	/*int len1= sizeof(arr1)/sizeof(int);*/
	
	/*printf("arr: max sum is %d\n",maxLocalSum(arr,len));*/
	
	/*printf("max sum is %d\n",FindMaxSub(arr,len));*/
	printf("max sum is %d\n",maxLocalSum(arr1,4));
	/*printf("arr1 max sum is %d\n",FindMaxSub(arr1,4));*/
	
	
	return 0;
}
