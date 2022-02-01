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

#include "hash.h" /* programs header*/

static const void *GetKey(const void *data);
static size_t hash_func(const void *key);
static int CompareData(const void *key1, const void *key2);

typedef struct kv
{
    void *key;
    void *data;
    
}kv_t;


int main(void)
{
    
    hash_t *hashy = NULL;

    hashy = HashCreate(16, &GetKey, &CompareData, &hash_func);
    HashDestroy(hashy);
    return 0;
}







static const void *GetKey(const void *data)
{
    size_t key = 5381;
    int cc = 0;
    kv_t pair;

    while (cc = (++(*(char *)&data)))
    {
        key = ((key << 5) + key) + cc;
       
    }

    pair.key = (*(void **)&key);
    pair.data = (*(void **)&data);

    return pair.key;
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