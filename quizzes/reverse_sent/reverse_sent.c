#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "stack.h"


typedef struct stackw
{
	stack_t *stack;

}stackw_t; 

void ReverseSentance(stackw_t *stackword, char *sentence, char *rev);
static void InitSTack(stackw_t *stackword, size_t len);
void Destroy(stackw_t *stackword);





int main(void)
{
	stackw_t *words = NULL;
	char sent[] = "corona? sick am i";

	char *rev = NULL;
	
	words = (stackw_t *)calloc(strlen(sent),sizeof(stackw_t));
	rev = (char *)calloc(strlen(sent),100);
	
	InitSTack(words,strlen(sent));
	ReverseSentance(words,sent, rev);

	printf("reveresed: \t%s\n", rev);
	
	Destroy(words);
	free(rev);
	rev = NULL;

	return 0;
}

void Destroy(stackw_t *stackword)
{
	StackDestroy(stackword->stack);
	

	free(stackword);
	stackword = NULL;
}


void ReverseSentance(stackw_t *stackword, char *sentence, char *rev)
{
	char *token = NULL;
	char *reversed = NULL;

	reversed = (char *)malloc(strlen(sentence));
	
	printf("before: %s\n",sentence );
	token = strtok(sentence, " ");

	while( token != NULL ) 
	{
      StackPush(stackword->stack, token);
      StackPush(stackword->stack, " ");
      token = strtok(NULL, " ");
   	}
   
   
   	do{
   		strcat(reversed, StackPeek(stackword->stack));
   		StackPop(stackword->stack);

   	} while(!StackIsEmpty(stackword->stack));
  	
  	memcpy(rev, reversed, strlen(reversed));

   	free(reversed);
   	reversed = NULL;
   
}

static void InitSTack(stackw_t *stackword, size_t len)
{
	assert(stackword != NULL);

	stackword->stack = StackCreate(len,sizeof(char *));
}