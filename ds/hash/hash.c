/**********************************************
 * HASH - Source File                         *
 * Developer: Tanya			                  *
 *          Feb 01, 2022                      *
 *                                            *
 * Reviewer: Ori    	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* memset */

#include "../include/hash.h" /* programs header*/
#include "dll.h"


typedef enum status
{
    SUCCESS,
    FAIL = -1
}status_e;


struct hash
{
    hash_cmp_func_t cmp_func;
    hash_func_t hash_func;
    hash_get_key_func_t get_key;
    size_t size;
    dlist_t **table;
};

typedef struct keva
{
    const void *key;
    void *value;

}keva_t;


hash_t *HashCreate(size_t size, hash_get_key_func_t get_key, 
            hash_cmp_func_t cmp_func, hash_func_t hash_func)
{
    hash_t *hash = NULL;

    assert(0 != size);
    assert(NULL != get_key);
    assert(NULL != cmp_func);
    assert(NULL != hash_func);

    hash = (hash_t *)malloc(sizeof(hash_t));
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
    hash->cmp_func = cmp_func;
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

int HashInsert(hash_t *hash, void *data)
{
   
    const void *new_key = hash->get_key(data);
    
    size_t level = 0;
    dlist_iter_t noob;
   

    level = hash->hash_func(new_key);

    assert(level <= hash->size);

    if(NULL == hash->table[level])
    {
       hash->table[level] = DListCreate();
       if(NULL == hash->table[level])
       {
            return FAIL;
       }
       
    }
    assert(HashFind(hash, new_key) != data);
   

    noob = DListPushBack(hash->table[level], data);
    assert(!DListIsEqual(DListBegin(hash->table[level]),DListEnd(hash->table[level]) ));

    return (DListIsEqual(noob, DListEnd(hash->table[level])));

}


void *HashFind(const hash_t *hash, const void *key)
{
    dlist_t *level = NULL;
    dlist_iter_t runner = NULL;
    void *data = NULL;

    assert(NULL != hash);
    assert(NULL != key);

    level = hash->table[hash->hash_func(key)];

    if(NULL != level)
    {
        
        dlist_iter_t end = DListEnd(level);
        runner = DListBegin(level);
        
        while (!DListIsEqual(runner, end) && 
            (0 != hash->cmp_func(hash->get_key(DListGetData(runner)), key)))
        {
              runner = DListNext(runner);  
        }
      
      data = DListGetData(runner);
        
    }
    
    return (DListIsEqual(runner, DListEnd(level))? NULL : data );
    
}


void HashRemove(hash_t *hash, const void *key)
{
    dlist_t *level = NULL;

    assert(NULL != hash);
    assert(NULL != key);

    level = hash->table[hash->hash_func(key)];
    
    if(level != NULL)
    {
        dlist_iter_t runner = DListBegin(level);
        dlist_iter_t end = DListEnd(level);

        dlist_iter_t found = DListFind(runner, end, hash->cmp_func, key);

       if (!DListIsEqual(found, end))
       {
            DListRemove(found);
       } 
    }  
}


size_t HashSize(const hash_t *hash)
{
    size_t occupance = 0;
    size_t rooms = 0;
    
    if(NULL != hash)
    {
        for(rooms = 0; rooms < hash->size; ++rooms)
        {
            if(hash->table[rooms] != NULL)
                occupance += DListSize(hash->table[rooms]);
        }
        
    }
    return occupance;
}


int HashIsEmpty(const hash_t *hash)
{
    assert(NULL != hash);
    return (!HashSize(hash));
}


int HashForEach(const hash_t *hash, hash_action_func_t action_func, void *param)
{
    status_e stat = SUCCESS;
    size_t room = 0;

    assert(NULL != hash);
    assert(NULL != action_func);

    for (room = 0; room < hash->size && (SUCCESS == stat); ++room)
    {
        dlist_t *level = hash->table[room];
         
        if (NULL != level)
        {
            dlist_iter_t runner = DListBegin(level);
            dlist_iter_t end = DListEnd(level);
            
            stat = DListForEach(runner, end, action_func, param);
        }
    }

    return stat;
}





