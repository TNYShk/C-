#include <stdio.h>  /*     standard library printf and what not  */
#include <stdlib.h> /*     malloc                                */
#include <assert.h> /*     test assertions made                  */
#include <string.h> /*     strlen strcopy                        */
#include <ctype.h>  /*     tolower                               */
#include <math.h>   /*     power of Josephus's choice            */

#include "arrays_ptrs.h"

#define COL 3
#define ROW 3
#define MAXLEN 150
#define MAXP 12

void MatrixSum(int matrix[][COL],int ans[ROW])
{
	int line,col,sum=0;

	for(line=0;line<ROW;line++)
	{
		for(col=0;col<COL;col++)
		{
			sum+=matrix[line][col];
				
		}
	printf("sum is %d",sum);
	ans[line]=sum;
	sum=0;
	printf("\n");
	}

}

void PrintMatrix(int mat[][COL])
{
	int line,col;
	for(line=0;line<ROW;line++)
	{
		for(col=0;col<COL;col++)
		{
			printf("%d ",mat[line][col]);
		}
	printf("\n");
	}
}



void PrintTypes()
{
	char   ch = ' ';
	int    int_num = 0;
	float  flt_num = 0.0f;
	double dbl_num = 0.0;
	printf("\n\tThe sizeof the following:\n");
	printf("\tThe size of char is: %ld-byte\n", sizeof(char));
	printf("\t\tThe size of ch is: %ld-byte\n", sizeof ch );
	printf("\t\tThe size of int is: %ld-byte\n", sizeof(int));
	printf("\tThe size of int_num is: %ld-byte\n", sizeof int_num);
	printf("\tThe size of float is: %ld-byte\n", sizeof(float));
	printf("\t\tThe size of flt_num is: %ld-byte\n", sizeof flt_num);
	printf("\t\tThe size of double is: %ld-byte\n", sizeof(double));
	printf("\tThe size of dbl_num is: %ld-byte\n", sizeof dbl_num);
	printf("\tThe size of size_t is: %ld-byte\n\n", sizeof(size_t));

 }
 
/*this works only if # of soldiers is less than 2^MAXP */
int JosephusChoice(int soldiers)
{
	int ans=1;
	int index=0;
	int *win=(int*)malloc(soldiers*sizeof(int));
	assert (NULL != win);
	
	while(++index<MAXP){
		win[index]=(int)pow(2.0, index);
		
		if(soldiers<win[index])
		{
			ans=(((soldiers-win[index-1])*2)+1);
			free(win);
			win= NULL;
			return ans;
		}
	}
	return -1;
}
/* coppied version */
int Josephus(int *circle, size_t soldiers)
{
	int index = 0;
	int next2die = 0;

	assert(NULL != circle);

	for(index=0; index<(int)soldiers; index++)
	{
		circle[index] = (index +1) % soldiers;
	}

	index = 0;
	while ( index != circle[index])
	{
		next2die = circle[circle[index]];
		circle[circle[index]] = 0;
		circle[index] = next2die;
		index = next2die;

	}
return index;
}

char * StrnCpy2Lower(char *dest, const char *src, size_t n)
{
	char * ptr_dest= dest+n;
	char * ptr_s= dest;
	while (dest < ptr_dest) 
	{
		if ('=' != *src)
		{
			*dest = tolower(*src);
			++dest;
			++src;
		}
		else
		{
			*dest = '\0';
			++dest;
		}
	}
	return ptr_s;
}
/* creates a truncated version array, later prints up to = */
char* StrDup(const char *s)
{
	/*size_t length = strlen(s)+1;*/
	size_t length = 0;
	char *dup=NULL;
	length=MAXLEN;
	dup=(char*)calloc(length,sizeof(char)+1);
	if (NULL == dup)
	{
		return NULL;
	}
	/*length= *s - *strchr(s,'=');*/
	dup= StrnCpy2Lower(dup,s,length);

	return dup;
}

void CopyEnvP(char **buf, char **envp)
{
	char *temp_b=NULL;
	
	while(*envp)
	{
		*buf=StrDup(*envp);
		printf("*buffer: %s\n", *buf);
		temp_b = *buf;
		buf++;
		envp++;
		free(temp_b);
	}
	
}

