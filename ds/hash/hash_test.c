/**********************************************
 * HASH - Source File                         *
 * Developer: Tanya			                  *
 *          Feb 01, 2022                      *
 *                                            *
 * Reviewer: Ori    	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdio.h> /* printf*/
#include <stdlib.h> /*  fgets, fopen, fclose*/
#include <string.h> /* strlen */
#include "hash.h" /* programs header*/

#define WORDSDICT (102401)
#define WORDLENMAX (30)
#define ESC (27)


void CreateDestroy();
void OccupyHotel();
static const void *GetKey(const void *data);
static size_t hash_func(const void *key);
int CompareData(const void *key1, const void *key2);
int PrintForEachString(void *value, void *param);
static void SpellCheck();
static size_t hash_func99(const void *key);

typedef struct dict
{
    const void *key;
    char data[WORDLENMAX];
}dict_t;

int main(void)
{
    
    CreateDestroy();
    OccupyHotel();
    
    printf("\n\tSpell Check Test:\n");

    SpellCheck();
    
    return 0;
}



static void SpellCheck(void *word)
{

    size_t i = 0;
    hash_t *hashy = NULL;
    dict_t *dictionary = NULL;
    char string[WORDLENMAX] = {0};
    void *spell = NULL;
    int x = 0;

    FILE *fp1 = fopen("words", "r"); 
    
    hashy = HashCreate(1000, &GetKey, &CompareData, &hash_func99);
    
    dictionary = (dict_t *)calloc(WORDSDICT,sizeof(dict_t));
    if(dictionary == NULL)
    {
        HashDestroy(hashy);
        fclose(fp1);
    }
    else
    {
        for( ;i< WORDSDICT ; ++i)
        {
            fgets(dictionary[i].data, WORDLENMAX, fp1);
            HashInsert(hashy, &(dictionary[i].data));
            
        }
            printf("\nEnter a word to search in linux dict, 2 tries:\n");
            fgets(string, WORDLENMAX, stdin);
            spell = HashFind(hashy, GetKey(string));
            (spell == NULL)? printf("word: %s not found\n", (char *)word): printf("GOOD SPELLING!! %s\n", (char *)spell);
        
            printf("\nEnter a word to spell check!\n");
            fgets(string, WORDLENMAX, stdin);
            spell = HashFind(hashy, GetKey(string));
            (spell == NULL)? printf("word: %s not found\n", string): printf("GOOD SPELLING!! %s\n", string);
        printf("\nTest Complete GoodBye\n");
        
        
        
        fclose(fp1);
        free(dictionary);
        HashDestroy(hashy);
    }
   
    
}





void CreateDestroy()
{

    hash_t *hashy = NULL;
    hashy = HashCreate(10, &GetKey, &CompareData, &hash_func);
    assert(1 == HashIsEmpty(hashy));
    assert(0 == HashSize(hashy));
    HashDestroy(hashy);

}

void OccupyHotel()
{
    hash_t *hashy = NULL;
    void *param = NULL;
    int x = 0;

    hashy = HashCreate(99, &GetKey, &CompareData, &hash_func);
    (1 == HashIsEmpty(hashy))? printf("Empty Hash Hotel\n") : printf("NOT empty Hotel\n");
    
    assert(0 == HashInsert(hashy, "tanya"));
    HashInsert(hashy, "Anya");
    HashInsert(hashy, "Fanya");
    HashInsert(hashy, "Aanya");
    HashInsert(hashy, "Banya");
    HashInsert(hashy, "Tatyanna");
    printf(" currently %ld rooms taken\n", HashSize(hashy));
    assert(HashSize(hashy) == 6);

    printf("\nCurrent Hotel Occupants:\n");
    HashForEach(hashy, &PrintForEachString, &x );
    printf("\n");

    printf("\nCheckout, 2 guests leaving\n");
    HashRemove(hashy, GetKey("tanya"));
    HashRemove(hashy, GetKey("Banya"));
    assert(HashSize(hashy) == 4);

    printf("\nCurrent Hotel Occupants:\n");
    HashForEach(hashy, &PrintForEachString, &x );
    printf("\n\nCalling Guests to Lobby:\n");
    param = HashFind(hashy, GetKey("Anya"));
    printf("found! %s\n", *(char **)&param);
    assert(param != NULL);

    param = HashFind(hashy, GetKey("tanya"));
    assert(param == NULL);
    printf("guest tanya not found -  left the building \n");
    

    HashDestroy(hashy);

}




static const void *GetKey(const void *data)
{
    size_t hash = 5381;
    int cc = 0;

    while (cc = (*(char *)data))
    {
        hash = ((hash << 5) + (hash)) + cc;
        ++(*(char **)&data);
    }

    return *(void**)&hash;
}

static size_t hash_func(const void *key)
{
    size_t hash_index = 0; /* number of rooms*/
    int cc = 0;

    hash_index = ((*(size_t *)&key) % 10);
    
    return hash_index;
}

static size_t hash_func99(const void *key)
{
    size_t hash_index = 0; /* number of rooms*/
    int cc = 0;

    hash_index = ((*(size_t *)&key) % 1000);
    
    return hash_index;
}

int CompareData(const void *key1, const void *key2)
{
    return (*(size_t *)&key1 - *(size_t *)&key2);
}

int PrintForEachString(void *value, void *param)
{
    (void)param;

    printf("%s ", (char *)value);

    return 0;
}