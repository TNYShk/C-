#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "wboai.h"

#define NUM_CHAR (12)
#define DECIM (10)
#define ASCIICHAR (48)

#define IS_LITTLE_ENDIAN (*(int *)&("1") != 0) 

#define MAX2(a,b) ((a)>(b)?(a):(b))
#define MIN2(a,b) ((a)<(b)?(a):(b))







void PrintFromArrays(char *a, char *b, char *c, size_t a_arr, size_t b_arr, size_t c_arr)
{

	int i = 0;
	size_t shorter = MIN2(a_arr, b_arr);
	size_t bigger = a_arr + b_arr - shorter;
	
	char *temp = NULL; 
	char *a1= NULL;
	char *a2 = NULL;
	char *a3 = NULL;
	
	temp = (char*)calloc(shorter,sizeof(char*));
	a1= (char*)calloc(a_arr+1,sizeof(char*));
	a2 = (char*)calloc(b_arr+1,sizeof(char*));
	a3 = (char*)calloc(c_arr+1,sizeof(char*));
	
	strncpy(a1,a,a_arr);
	strncpy(a2,b,b_arr);
	strncpy(a3,c,c_arr);
	
	assert (NULL != temp);
	assert (NULL != a1);
	assert (NULL != a2);
	assert (NULL != a3);

	while(bigger)
	{
		if (NULL != strchr(a1,*(a2+i)))
		{
			*(temp +i) = *(strchr(a1,*(a2+i)));
		}
			++i;
			--bigger;
	}
	i=0;
	
	while (shorter)
	{
		if (NULL == strchr(a3,*(temp+i)))
		{
			printf("%c ", temp[i]);
		}
		--shorter;
		++i;
	}
	
	
	free(temp);
	free(a1);
	free(a2);
	free(a3);
	a1 = NULL;
	a2 = NULL;
	a3 = NULL;
	temp = NULL;
	
}




static void Reverse(char *str, size_t length)
{
	char *start = str;
	char *end = str + length - 1;
		
	while (start < end)
	{
		char t = *start;
		*start = *end; 
			*end = t;
			++start;
			--end;
	}
}


char *ItoaIntToStrBase(int value, char *str, unsigned int base)
{
	char *ptr = str;
	int i = 0;
	size_t len = 0;
	char flag = '\0';
	if(0 > value)
	{
		value= -value;
		flag = '-';
	}
	
	while(value)
	{
		char leftover = value % base;

		if (leftover > 9)
		{
			leftover -= DECIM;
			leftover += 'A';
			*(ptr+i) = leftover;
		}
		
		else
		{
			leftover += '0';
			*(ptr+i) = leftover;
		}

	value /= base;
	++i;
	*(ptr + i) = flag;
	}
	
	len = strlen(str);

	Reverse(str,len);
	
	return str;
}

int AtoiStrToIntBase(const char *nptr, unsigned int base)
{
	int num = 0;
	int i = 0;
	int sign = 1;

	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t')
	{
		++i;
	}
	if ( *nptr == '-')
	{
		sign = -1;
		++nptr;
	}

	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
		{
			num *=  base;
			num += (nptr[i] - '0');
		}
		if ((nptr[i] >= 'A') && (nptr[i] <= 'F'))
		{
			num *=  base;
			num += (nptr[i] - 'A' + 10);
		}

	++i;
	} 
	
	return sign * num;	
		
	}
	




int AtoiStrToInt(const char *nptr)
{
	int num = 0;
	int sign = 1;
	

	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' )
	{
		++nptr;
	}

	if ( *nptr == '-')
	{
		sign = -1;
		++nptr;
	}
	while (nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		num *=  10;
		num += (*nptr - '0');
		
		++nptr;
	}
	
	return sign*num;
}



char *ItoaIntToStr(int value, char *str)
{
	int i = 0;
	size_t len = 0;
	char *ptr = str;
	char flag = '\0';
	
	if(value < 0)
	{
		value = -value;
		 flag = '-';
	}
	
	while(value)
	{
		char temp = value % DECIM;
		temp += '0';
		value /= DECIM;
		*(ptr+i) = temp;
		++i;
		*(ptr+i) = flag;
	}
	
	len = strlen(str);

	Reverse(str,len);
	return str;
}

int IsLittleEndian(void)
{
		int n = 1;
		char *indian = (char *)&n;

        return (indian[0] == 1);
}

