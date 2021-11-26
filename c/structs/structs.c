#include <stdio.h>			/*standard things print */
#include <stdlib.h> 		/* malloc(), realloc() */
#include <string.h>         /* strcpy,strcat  */

#define TYPES_NUM (3)
#define MUM2CHAR (11)

typedef int (*add_t)(int num, void *element);
typedef int (*print_t)(void *element);
typedef int (*clean_up_t)(void *element);

typedef struct operations
{
	add_t add_func;
	print_t print_func;
	clean_up_t clean_up_func;
} operations_t;



typedef struct gen_element
{
	void *element;
	operations_t *func_operations;
} gen_element_t;



enum exit_code {PRINT_ERROR = -1, SUCCESS, MEMORY_ALLOCATION_ERROR};

static int AddInt(int num, void *element)
{
	(*(int*)element)+=num;
	return SUCCESS;
}

static int AddFloat(int num, void *element)
{
	(*(float*)element)+=num;
	return SUCCESS;
}

static int AddString(int num, void *element){
	
	char * temp=(char *)malloc(sizeof(num)*MUM2CHAR);
	char *temp2=(*(char**)element);
	
	if (NULL ==temp)
	{
		return MEMORY_ALLOCATION_ERROR;
	}
	
	sprintf(temp,"%d ",num);
	strcat(temp2,temp);
	
	free(temp);
	temp=NULL;
	
	return SUCCESS;
}

static int PrintInt(void *element)
{
	if(NULL==(element))
	{
		printf("NULL==element");
		return PRINT_ERROR;
	}
	printf("Int element is %d\n",*(int*)&(element));
	return SUCCESS;
}

static int PrintFloat(void *element)
{
	if(NULL==(element))
	{
		printf("NULL==element");
		return PRINT_ERROR;
	}
	printf("Float element is %f\n",*(float*)&element);
	return SUCCESS;
}

static int PrintString(void *element)
{
	if(NULL==(element))
	{
		printf("NULL==element");
		return PRINT_ERROR;
	}
	printf("%s\n",(char*)element);
	return SUCCESS;
}

static int Nothing(void *element)
{	
	(void)element;
	printf("cleanup! doing nothing is nice\n");
	return SUCCESS;
}
static int CleanUpArray(void *element)
{
	free(*(char **)element);
	element=NULL;
    return SUCCESS;
	
}

static operations_t function_bank[TYPES_NUM] =						/* optional */
		{
			{&AddInt, 		&PrintInt,		&Nothing},			/* int */
			{&AddFloat, 	&PrintFloat, 	&Nothing},			/* float */	
			{&AddString,	&PrintString, 	&CleanUpArray}		/* string */
		};


static void  Initialize(gen_element_t*darth)
{
	
	int x=9;
	float pi=3.14;

	char * string= "Darth Voider";
	void * vp_i= (*(void**)&(x));
	void * vp_f=(*(void**)&(pi));
	
	void *vp_s=malloc(sizeof(char*)*(sizeof(string)));	
	
	if(NULL == vp_s)
	{
		printf("error initializing");
	}

	strcpy((char*)vp_s,string);
	darth[0].element=vp_i;
	darth[0].func_operations= &function_bank[0];

	darth[1].element=vp_f;
	darth[1].func_operations= &function_bank[1];
	
	darth[2].element= vp_s;
	darth[2].func_operations= &function_bank[2];

	
	
}




int main()
{
	int i=0;
	
	gen_element_t *darth=calloc(TYPES_NUM,sizeof(gen_element_t));
	if(NULL ==darth)
	{
		printf("error initializing");
		return MEMORY_ALLOCATION_ERROR;
	}

	Initialize(darth);

	for(i=0;i<TYPES_NUM;++i)
	{
		darth[i].func_operations->print_func(darth[i].element);
		darth[i].func_operations->add_func(10,&darth[i].element);
		darth[i].func_operations->print_func(darth[i].element);
	}
	
	for(i=0;i<TYPES_NUM;++i)
	{
		darth[i].func_operations->clean_up_func(&darth[i].element);

	}
	
	/*manual option:
	CleanUpArray(&darth[2].element);
	*/
	free(darth);
	darth=NULL;
	
	
	
	return (0);
}

