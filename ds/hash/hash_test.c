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
#define HIDE (system("stty -icanon -echo"))
#define UNHIDE (system("stty icanon echo"))
#define ESC (27)


void CreateDestroy();
void OccupyHotel();
static void SpellCheck();
int CompareData(const void *key1, const void *key2);
int PrintForEachString(void *value, void *param);

/* hashing & indexing funcs */
static const void *GetKey(const void *data);
static size_t hash_func(const void *key);
static size_t hash_func99(const void *key);




typedef struct dict
{
    const void *key;
    char data[WORDLENMAX];
}dict_t;

int main(void)
{
    
    CreateDestroy();
    printf("\n------------CreateDestroy TEST COMPLETE---------------\n");
    OccupyHotel();
    printf("\n-------------Other funcs TESTS COMPLETE----------------\n");
    printf("\n\tSpell Check Test:\n");

    SpellCheck();
    printf("\n-------------");
    printf("\t\n------------Test Complete GoodBye----------------------\n");
    return 0;
}



static void SpellCheck()
{
    size_t i = 0;
    hash_t *hashy = NULL;
    dict_t *dictionary = NULL;
    char string[WORDLENMAX] = {0};
    void *spell = NULL;
    
    FILE *pFile = fopen("words", "r"); 
    hashy = HashCreate(1000, &GetKey, &CompareData, &hash_func99);
    
    dictionary = (dict_t *)calloc(WORDSDICT,sizeof(dict_t));
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
                (spell == NULL)? printf("\nbad spelling: %s \n", string): 
                    printf("\n %s\nGOOD SPELLING!!\n", (char *)spell);
            }
         
        fclose(pFile);
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
    HashInsert(hashy, "tatyana");
    HashInsert(hashy, "Banya");
    HashInsert(hashy, "Elvis");
    HashInsert(hashy, "Tatyanna");
    printf(" currently %ld rooms taken\n", HashSize(hashy));
    assert(HashSize(hashy) == 7);

    printf("\nCurrent Hotel Occupants:\n");
    HashForEach(hashy, &PrintForEachString, &x );
    printf("\n");

    printf("\nCheckout, 2 guests leaving\n");
    HashRemove(hashy, GetKey("tanya"));
    HashRemove(hashy, GetKey("Elvis"));
    assert(HashSize(hashy) == 5);

    printf("\nCurrent Hotel Occupants:\n");
    HashForEach(hashy, &PrintForEachString, &x );
    printf("\n\nCalling Guests to Lobby:\n");
    param = HashFind(hashy, GetKey("Tatyanna"));
    printf("found! %s\n", *(char **)&param);
    assert(param != NULL);

    param = HashFind(hashy, GetKey("tanya"));
    assert(param == NULL);
    printf("guest not found - Elvis has left the building \n");
    

    HashDestroy(hashy);

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

static size_t hash_func(const void *key)
{
    size_t hash_index = 0; /* number of rooms*/
    
    hash_index = ((*(size_t *)&key) % 10);
    
    return hash_index;
}

static size_t hash_func99(const void *key)
{
    size_t hash_index = 0; /* number of rooms*/
  
    hash_index = ((*(size_t *)&key) % 1000);
    
    return hash_index;
}

int CompareData(const void *key1, const void *key2)
{
    return (*(size_t **)&key1 - *(size_t **)&key2);
}

int PrintForEachString(void *value, void *param)
{
    (void)param;

    printf("%s ", (char *)value);

    return 0;
}