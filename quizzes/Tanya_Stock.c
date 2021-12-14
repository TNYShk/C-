#include <stdio.h>
#include <stdlib.h>




int Stock(int *arr, size_t length, int *p_sell, int *p_buy);

int main(int argc, char const *argv[])
{
	int stock[8]={6,12,3,5,1,4,9,2};
	size_t length= sizeof(stock)/sizeof(int);
 	int bursa[] = {5, 2, 30, 23, 1, 80};
 	
 	int *buy = NULL;
 	int *sell = NULL;

	printf("max profit is %d\n",Stock(stock,length,sell,buy));
	return 0;
}


 int Stock(int *arr, size_t length, int *p_sell, int *p_buy)
 {
 	int max_profit = 1;
 	int *runner = NULL;
 	
 	p_buy = arr;
 	p_sell = arr + 1;
 	max_profit = *p_sell - *p_buy;
 	runner = p_sell;
 	
 	while(runner < arr + length)
 	{
 		if(*runner > *p_sell)
 		{
 			p_sell = runner;
 			int delta = *p_sell - *p_buy;
 		
 			if(delta > max_profit)
 			{
 				max_profit = delta;
 			}
 		}
 		else if(*runner < *p_buy)
 		{
 			p_buy = p_sell = runner;
 		}
 		++runner;
 	}
 	printf("index of p_buy is %d and p_sell is %d\n",p_buy-arr,p_sell-arr);
 	return max_profit;
 }


