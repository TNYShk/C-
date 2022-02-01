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

#include "../include/hash.h" /* programs header*/
#include "dll.h"
/*
typedef int (*hash_cmp_func_t)(const void *key1, const void *key2);

typedef const void *(*hash_get_key_func_t)(const void *data);
typedef size_t (*hash_func_t)(const void *key);

typedef int (*hash_action_func_t)(void *value, void *param);
typedef struct hash hash_t;
*/

struct hash
{
    hash_cmp_func_t cmp_func;
    hash_func_t hash_func;
    hash_get_key_func_t get_key;
    size_t size;
    dlist_t **table;
};

typedef struct kv
{
    const void *key;
    const void *data;
    
}kv_t;



hash_t *HashCreate(size_t size, hash_get_key_func_t get_key, 
            hash_cmp_func_t cmp_func, hash_func_t hash_func)
{
    hash_t *hash = NULL;

    assert(0 != size);
    assert(NULL != get_key);
    assert(NULL != cmp_func);
    assert(NULL != hash_func);

    hash = (hash_t *)calloc(size, sizeof(hash_t));
    if (NULL == hash)
    {
        return NULL;
    }

    hash->table = (dlist_t **)calloc(size, sizeof(dlist_t *));
    if(NULL == hash->table)
    {
       free(hash);

        return NULL;
    }
    
    hash->size = size;
    hash->hash_func = hash_func;
    hash->get_key = get_key;

    return hash;
}

void HashDestroy(hash_t *hash)
{
    if(NULL != hash)
    {
        size_t clear_rooms = 0;

        for(clear_rooms = 0; clear_rooms < hash->size; ++clear_rooms)
        {
            DListDestroy(hash->table[clear_rooms]);
        }
        free(hash->table);
        
        memset(hash,0, sizeof(hash_t));
        free(hash);
        hash = NULL;

    }
    
}



