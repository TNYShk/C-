/**********************************************
 * HASH - Source File                         *
 * Developer: Tanya			                  *
 *          Jan 31, 2022                      *
 *                                            *
 * Reviewer:        	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* memset */
#include <math.h> /* abs */
#include <stdio.h>

#include "hash.h" /* programs header*/

static const void *GetKey(const void *data);
static size_t hash_func(const void *key);
static int CompareData(const void *key1, const void *key2);
static int CompareData(const void *key1, const void *key2);


int main(void)
{
    
    hash_t *hashy = NULL;
   
    const void *key = GetKey("tanya");
    const void *Fey = GetKey("Fanya");
    const void *test_key;
    printf("key is %ld\n", (*(size_t **)&key));
    printf("Fey is %ld\n", (*(size_t **)&Fey));
    printf("hash key is %ld\n", hash_func(key));
    printf("hash key is %ld\n", hash_func(Fey));
    hashy = HashCreate(99, &GetKey, &CompareData, &hash_func);
    
    (1 == HashIsEmpty(hashy))? printf("Empty Hash\n") : printf("NOT empty Hash\n");
    HashInsert(hashy, "tanya");

    HashInsert(hashy, "Fanya");
    printf("hash size is: %ld\n", HashSize(hashy));
     (1 == HashIsEmpty(hashy))? printf("Empty Hash\n") : printf("NOT empty Hash\n");
   /*HashRemove(hashy, key);*/
    printf("hash size is: %ld\n", HashSize(hashy));
   

    HashDestroy(hashy);

    
    return 0;
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

    hash_index = ((*(size_t *)&key) % 100);
    
    return hash_index;
}

static int CompareData(const void *key1, const void *key2)
{
    return (*(size_t *)key1 - *(size_t *)key2);
}