#include <stdio.h>
#include <stdlib.h>


typedef struct stock
{
	int *p_buy;
	int *p_sell;
	int max_profit;
}stock_t;



int Stock(int *arr, size_t length, int *p_sell, int *p_buy);

stock_t MaxProfitStock(int *, size_t);



int main(void)
{
	
	int stock[8]={6,12,3,5,1,4,9,2};
	size_t length= sizeof(stock)/sizeof(int);
 	int bursa[] = {5, 2, 30, 23, 1, 80};
 	

 	int *buy = NULL;
 	int *sell = NULL;

 	stock_t profit_t = MaxProfitStock(stock, length);
 	printf("stock max profit is %d\n", profit_t.max_profit);
 	printf("buy max at idx %d, value is %d\n", profit_t.p_buy - stock, *profit_t.p_buy);
 	printf("sell max at idx %d value is %d\n\n", profit_t.p_sell - stock, *profit_t.p_sell);
 	

	printf("\nmax profit idx %d\n",Stock(stock,length,sell,buy));
	printf("\nmax profit idx %d\n",Stock(bursa,6,sell,buy));




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

 			int delta = *runner - *p_buy;
 			p_sell = runner;
 		
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
 	printf("index of p_buy is %ld and p_sell is %ld\n",p_buy-arr,p_sell-arr);
 	return max_profit;
 }


stock_t MaxProfitStock(int *stock, size_t length)
{
	stock_t stocky = {0,0,0};
	int *runner = NULL;

	int *buy = NULL;
	int *sell = NULL;

	buy = stock;
 	sell = stock + 1;
 	stocky.max_profit = *sell - *buy;
 	runner = sell;

		

	while(runner < stock + length)
 	{
 		if(*runner > *sell)
 		{

 			int delta = *runner - *buy;
 			
 			sell = runner;
 		
 			if(delta > stocky.max_profit)
 			{
 				stocky.max_profit = delta;
 			}
 		}
 		else if(*runner < *buy)
 		{
 			buy = sell = runner;
 		}
 		++runner;
 	}
 	stocky.p_buy = buy;
 	stocky.p_sell = sell;

 	return stocky;
}
