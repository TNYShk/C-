#include <stdio.h>

void DivideFiveThree(int);
void PrintReverse(int, char *);

const int aA ='a' - 'A';




void PrintReverse(int length, char *string)
{
	char *str_end = length + string;
	
		while (string <= str_end && (--str_end))
		{
			if((*str_end <= 'Z') && (*str_end >= 'A'))
			{
				printf("%c",*str_end + aA);
			}
			
			else 
			{
			printf("%c", *str_end);
			}
		}	
		
}




/*divide by 3,5 */

void DivideFiveThree(int number)
{
	int i = 0;
	for(i = 1; i <= number; ++i)
	{
		if ((i % 3 == 0) && (i % 5 == 0))
		{
		
			printf("TF ");
		}	
		
		else if (i % 3 == 0)
		{
			printf("T ");
		}
		
		else if (i % 5 == 0)
		{
		
			printf("F ");
		}
		
		else
		{
			printf("%d ",i);
			
		}
	}

}
/* less if's*/
void DivideFiveThre(int number)
{
	int i = 0;

	for(i = 1; i <= number; ++i)
	{
		if ((i % 3 == 0) || (i % 5 == 0))
		{
			if (i % 5 == 0)
			{
				printf("F");
			}

			printf("T ");
		}
	  	else
			{
				printf(" %d ",i);
			}	
		
	}

}







int main ()
{
	DivideFiveThree(15);
	printf("\n");
	DivideFiveThre(15);
	printf("\n");
	PrintReverse(11,"HeLLO WoRlD");
	printf("\n");

return 0;
}

