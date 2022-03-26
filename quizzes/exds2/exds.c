
#include <stdio.h> /*print */
#include <assert.h> /* assert*/
#include <stdlib.h> /*memory allocation & free */
#include <string.h> /* testing strlen, strcmp, strstr*/
#include <assert.h>
#include <errno.h>       /* errno */

#include "stack.h"
#include "bst.h"
#include "avl.h"
#include "hash.h"
#define ESC (27)
#define WORDLENMAX (32)
#define WORDSDICT (102401)
#define FAILURE (1)
#define SUCCESS (0)

#define DICT_PATH ("/usr/share/dict/words")

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct dict
{
    const void *key;
    char data[WORDLENMAX];
}dict_t;


typedef struct sll_node
{
    void *data;
    struct sll_node *next;
}sll_node_t;


static char sorted[][WORDLENMAX] = {{'\0', '\0'}};
static char sort[WORDSDICT] = {'\0'};

static void SLLFlipTest(void);
static void MinSubArrTest(void);
static void RevStrTest(void);
static void Test2Stacks(void);

sll_node_t *Flip(sll_node_t *toflip);
static sll_node_t *InitNode(sll_node_t *new_node, void *data);
sll_node_t *RecFlipList(sll_node_t *head);
void FlipList(sll_node_t **head);
static void PrintSll(sll_node_t *head);

int FindMinSubArray(const int *arr, size_t ar_len);
int FindMaxSub(const int *arr, size_t ar_len);
static void PrintArr(int *arr, size_t len);

static void Swap(char *a, char *b);
void ReverseStr(char *string);
void RecReverseStr(char *string, size_t start, size_t end);

static void SpellCheck(void);
static size_t hash_func99(const void *key);
static const void *GetKey(const void *data);
void ValidPermutation(hash_t *hash, char *string, size_t idx);
int CompareData(const void *key1, const void *key2);

int CompareChar(const void *key1, const void *key2);
void SortWordsFile(const char *filename);
void SortCharsFile(void);
static void PrintWords(size_t len);

int CompareChars(const void *key1, const void *key2);

void RecSort(stack_t *stack);
void SortStacks(stack_t *stack, stack_t *temp);
void InSortedStack(stack_t *stack, int number);
static void PrintStack(stack_t *stack);

int CountONBits(int number);
int RecCountONBits(int number);


int main(void)
{
  
   /* 
   
    MinSubArrTest();
  
    SpellCheck(); 
 
    RevStrTest(); 
   
    Test2Stacks();
     
    SortWordsFile("filesort");
    SortCharsFile();
   
    */
SLLFlipTest();

printf("on bits of 76 is %d\n", CountONBits(75));
printf("REC on bits of 76 is %d\n", RecCountONBits(75));

    
    return 0;
}



/*sort chars from a file */
void SortCharsFile(void)
{
    FILE *fp = NULL;
    size_t length = 0;
    int copy = 0;
    int newcopy = 0;
    char *rem_newline = NULL;
    
    if (NULL == (fp = fopen(DICT_PATH, "r")))
    {
        errExit("failed fopen");
    }

    fread(sort, 1,WORDSDICT,fp);
    fclose(fp);
 /*    printf("read from file:\n%s",sort);  
    length = strlen(sort); */
    
    for(copy = 0; copy < WORDSDICT -1; ++copy)
    {
        for(newcopy = copy +1; newcopy < WORDSDICT; ++newcopy)
        {
            if(sort[copy] > sort[newcopy])
            {
                Swap(sort + copy, sort + newcopy);
            }
        }
    }
    rem_newline = strchr(sort,'a');
    printf("after: %s\n",rem_newline); 
}




/* sort words? in a given file*/
void SortWordsFile(const char *filename)
{
    FILE *fp = NULL;
    size_t idx = 0;
    if (NULL == (fp = fopen(filename, "r")))
    {
        errExit("failed fopen");
    }
    while(fgets(sorted[idx], WORDLENMAX, fp))
    {
        sorted[idx][strlen(sorted[idx])-1] = '\0';
        idx++;
         
    }
    qsort(*sorted,idx, WORDLENMAX, &CompareChar); 
    fclose(fp);
   
    PrintWords(idx);
}

static void PrintWords(size_t len)
{
    size_t idx = 0;
    while (idx < len)
    {
        printf("%s \n", sorted[idx]);
        ++idx;
    }
}

int CompareChar(const void *key1, const void *key2)
{
    return strcmp(key1,key2);
}
int CompareChars(const void *key1, const void *key2)
{
    return (*(char **)&key1 - *(char **)&key2);
}

int CompareData(const void *key1, const void *key2)
{
    return (*(size_t **)&key1 - *(size_t **)&key2);
}


/* sll flip & recursive*/
static void SLLFlipTest(void)
{
    int filler[] = { 1, 15,-7,8,23};
    sll_node_t *head = NULL;
     sll_node_t *next = NULL;
      sll_node_t *next1 = NULL;
         sll_node_t *next2 = NULL;
         sll_node_t *tail = NULL;
         sll_node_t *flipped = NULL;

    head = InitNode(head, (void *)(filler));
    next = InitNode(next, (void *)(filler + 1) );
    next1 = InitNode(next1, (void*)(filler + 2) ); 
    next2 = InitNode(next2, (void*)(filler + 3) ); 
    tail = InitNode(tail, (void*)(filler + 4) ); 
 
    head->next = next;
    next->next = next1;
    next1->next = next2;
    next2->next = tail;
    printf("original sll: \n");
    PrintSll(head); 
    flipped = Flip(head);
     printf("post flip sll: \n");
    PrintSll(flipped); 
     printf("flipped post rec flip sll: \n");
    head = RecFlipList(flipped);
    PrintSll(head);
    printf("void flip **head: \n");
    flipped = head;
    FlipList(&flipped);
    PrintSll(flipped);
    
    free(head);
    free(next);
    free(next1);
    free(next2);
    free(tail);
}

sll_node_t *Flip(sll_node_t *toflip)
{
    sll_node_t *runner = NULL;
    sll_node_t *new_head = NULL;
    sll_node_t *next_node = NULL;
    sll_node_t *holder = NULL;

    assert(NULL != toflip);

    runner = toflip;

    while(NULL != runner->next)
    {
       next_node = runner->next;
       runner->next = holder;
       holder = runner;
       runner = next_node;
    }

    new_head = runner;
    runner->next = holder;

    return new_head;
}

void FlipList(sll_node_t **head)
{
    sll_node_t *prev = NULL;
    sll_node_t *runner = *head;
    sll_node_t *next = NULL;

    while(NULL != runner)
    {
        next = runner->next;
        runner->next = prev;

        prev = runner;
        runner = next;
    }
    *head = prev;
}

sll_node_t *RecFlipList(sll_node_t *head)
{

	if(NULL == head->next)
	{
		return head;
	}
	else
	{
		sll_node_t *new = RecFlipList(head->next);
		head->next->next = head;
		head->next = NULL;

		return new;
	}
}

static sll_node_t *InitNode(sll_node_t *new_node, void *data)
{
	new_node = (struct sll_node *)malloc(sizeof(struct sll_node));

	if(new_node != NULL)
	{
		new_node->data = data;
		new_node->next = NULL;

		return new_node;
	}
	
	return NULL;
}

static void PrintArr(int *arr, size_t len)
{
    printf("%d ", *arr);
    if(1 < len)
    {
        PrintArr(++arr, --len);
    }
    return;
}

static void PrintSll(sll_node_t *head)
{ 
    printf("%d ", *(int *)head->data);
    
    if (NULL != head->next)
    {
        PrintSll(head->next);
    }
    printf("\n");
    return;
}

/*Reverse String & Recursive */
void ReverseStr(char *string)
{
    size_t len = strlen(string);
    size_t idx = 0;

    for(; idx < (len >> 1); ++idx)
    {
        Swap((string + idx), (string + (len - idx -1)));
    }
}   

void RecReverseStr(char *string, size_t start, size_t end)
{
    if(start < end)
    {
        Swap((string + start), (string + end -1));
        RecReverseStr(string, start + 1, end - 1); 
    }
    return;
} 




/* dictionary, permutation - WORDLE*/
static void SpellCheck()
{
    size_t i = 0;
    hash_t *hashy = NULL;
    dict_t *dictionary = NULL;
    char string[WORDLENMAX] = {0};
    void *spell = NULL;
    
    FILE *pFile = fopen("words", "r"); 
    hashy = HashCreate(1000, &GetKey, &CompareData, &hash_func99);
    
    dictionary = (dict_t *)calloc(WORDSDICT, sizeof(dict_t));
    if(dictionary == NULL)
    {
        HashDestroy(hashy);
        fclose(pFile);
    }
    else
    {
        for( ;i< WORDSDICT ; ++i)
        {
            fgets(dictionary[i].data, WORDLENMAX, pFile);
            HashInsert(hashy, &(dictionary[i].data));
        }
        printf("Loaded dictionary! good luck\n");
        printf("\nEnter a word to search in linux dict, or ESC Enter :\n");
            
        while (*(char *)string != ESC)
        {
            fgets(string, WORDLENMAX, stdin);
            spell = HashFind(hashy, GetKey(string));
                
            if(strlen(string) == 6)
            {
                ValidPermutation(hashy,string, 0);
            }

            (spell == NULL)? printf("\nbad spelling: %s \n", string): 
                printf("\n %s\nGOOD SPELLING!!\n", (char *)spell);
        }
         
        fclose(pFile);
        free(dictionary);
        HashDestroy(hashy);
    }
}

static size_t hash_func99(const void *key)
{
    size_t hash_index = 0; /* number of rooms*/
    hash_index = ((*(size_t *)&key) % 1000);
    
    return hash_index;
}

static const void *GetKey(const void *data)
{
    size_t hash = 5381;
    int cc = 0;
    char *str = (char *)data;

    while ('\0' != *str)
    {
        cc = *str;
        hash = ((hash << 5) + (hash)) + cc;
        ++str;
    }

    return *(void**)&hash;
}

void ValidPermutation(hash_t *hashy, char *string, size_t idx)
{
    size_t i = 0;
    char *spell = NULL;

    if (idx == strlen(string))
    {
        if (NULL != (spell = HashFind(hashy, GetKey(string))))
        {
            printf("%s \n",(char *)spell);
        }
        
        return;
    }

    for(i = idx; i < strlen(string); ++i)
    {
        Swap(string + idx, string + i);
        ValidPermutation(hashy, string, idx + 1);
        Swap(string + idx, string + i);
    }
  

}


static void Swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}



static void RevStrTest(void)
{
    char test[] = "Data Structs exam part two";
    printf("before reverse: %s\n", test);

    ReverseStr(test);
    printf("after reverse: %s\n", test);

    RecReverseStr(test,0,strlen(test));
    printf("after Rec reverse: %s\n", test);
}



/* find min | max sub array sum */
static void MinSubArrTest(void)
{
    int filler[] = { 1, 0,-7,8,23};
    size_t five = 5;
    PrintArr(filler,five);

    printf("\nfind MIN sum: %d\n", FindMinSubArray(filler,5));
    printf("find MAX sum: %d\n", FindMaxSub(filler,5));
}

int FindMinSubArray(const int *arr, size_t ar_len)
{
	size_t end = 0;
	int untillnow = *arr;
	int global_min = *arr;

	for(end = 1; end < ar_len; ++end)
	{
		untillnow = *(arr + end) + untillnow * (untillnow < 0);
		
		if (global_min > untillnow)
		{
			global_min = untillnow;
		}
	}
	return global_min;
}

int FindMaxSub(const int *arr, size_t ar_len)
{
	size_t end = 0;
	int untillnow = *arr;
	int global_max = *arr;

	for(end = 1; end < ar_len; ++end)
	{
		untillnow = *(arr + end) + untillnow * (untillnow > 0);
		
		if (global_max < untillnow)
		{
			global_max = untillnow;
		}
	}
	return global_max;
}


/* sort stack*/
static void Test2Stacks(void)
{
	stack_t *tosort = StackCreate(6, sizeof(int));
	stack_t *another = StackCreate(6, sizeof(int));
	int num1 = 100;
    int num2 = 1;
    int num3 = 2;
    int num4 = -5;
    int num5 = 4;
	int num6 = 101;

	StackPush(tosort, &num1);
    StackPush(tosort, &num2);
    StackPush(tosort, &num3);
    StackPush(tosort, &num4);
    StackPush(tosort, &num5);
    StackPush(tosort, &num6);
    StackIsEmpty(tosort) == 1? printf("stack is empty\n"): printf("stack NOT empty\n") ;

	printf("stack numbers: %d, %d, %d, %d, %d, %d\n", num6,num5,num4,num3,num2,num1);
    /* PrintStack(tosort); */

	SortStacks(tosort, another);
	printf("\nSort Stack with 2 stacks,  after:\n");
    PrintStack(another);

    StackPush(another, &num6);
    StackPush(another, &num2);
    StackPush(another, &num3);
    StackPush(another, &num1);
    StackPush(another, &num5);
    StackPush(another, &num4);
    
    printf("\nrecursive vesion with 1 stack:\n");
    RecSort(another);
    PrintStack(another);

	StackDestroy(tosort);
    StackDestroy(another);

}

void RecSort(stack_t *stack)
{
	int peek = 0;

	assert(NULL != stack);
	
	if (StackIsEmpty(stack))
	{
		return;
	}

	peek = *(int *)StackPeek(stack);
	StackPop(stack);

	RecSort(stack);

	InSortedStack(stack, peek);

}


void SortStacks(stack_t *stack, stack_t *temp)
{
	int peek = 0;
	
	assert(NULL != temp);
	assert(NULL != stack);


	while(!StackIsEmpty(stack))
	{
		peek = *(int *)StackPeek(stack);
		
		StackPop(stack);

		while(!StackIsEmpty(temp) && (peek > *(int *)StackPeek(temp)))
		{
			StackPush(stack, StackPeek(temp));
			StackPop(temp);
		}
		
		StackPush(temp, &peek);
	}
}



void InSortedStack(stack_t *stack, int number)
{
	if (!(StackIsEmpty(stack)) && (number > (*(int *)StackPeek(stack))))
	{
		int peek = *(int *)StackPeek(stack);
		StackPop(stack);
		
		InSortedStack(stack, number);
		
		StackPush(stack, &peek);
		
		return;
	}

	StackPush(stack, &number);
}

static void PrintStack(stack_t *stack)
{
	while(!StackIsEmpty(stack))
	{
		int peek = *(int *)StackPeek(stack);
		printf("%d ", peek);
		StackPop(stack);
	}
	printf("\n");
}




void MergeSort(int *arr, size_t length){

    int *helper = (int *)calloc(length,sizeof(int));
    assert(NULL != helper);

    memcpy(helper,arr,sizeof(int) * length);
    
}

int CountONBits(int number)
{
    int temp = 0;
    int counter = 0;

    while(number)
    {
        temp = number -1;
        number &= temp;
        ++counter;
    }
    return counter;
}

int RecCountONBits(int number)
{
    int temp = 0;
    
    if(number == 0)
    {
        return 0;
    }
    
    temp = number -1;
    return (1 + RecCountONBits(number&temp));
    
} 