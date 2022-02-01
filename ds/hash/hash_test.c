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



int main(void)
{
    
    hash_t *hashy = NULL;
   
    const void *key = GetKey("tanya");
    printf("key is %ld\n", (*(size_t **)&key));
    hashy = HashCreate(100, &GetKey, &CompareData, &hash_func);
    
    

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
    size_t hash_index = 16; /* number of rooms*/
    int cc = 0;

    hash_index = ((*(size_t*)&key)%hash_index);
    
    return hash_index;
}

static int CompareData(const void *key1, const void *key2)
{
    return (*(size_t *)key1 - *(size_t *)key2);
}