#include <stdio.h>

void TF(int);

void PrintReverse(int, char *);


void PrintReverse(int length, char *string){
	
	char *str_end= length + string;
	
	
	
		while (string <= str_end && str_end--)
		{
			if((*str_end<=90) && (*str_end >=65))
			{
				printf("%c",*str_end+32);
			}
			
			else 
			{
			printf("%c", *str_end);
			}
		}	
		
}





void TF(int number)
{
	int i;
	for(i=1;i<=number;i++)
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

int main ()
{
TF(15);
printf("\n");
PrintReverse(11,"HellO WoRlD");


return 0;
}
