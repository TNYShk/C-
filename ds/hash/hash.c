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
    const void *value;
    
}keva_t;

int MatchNum(const void *data, void *param);
int CmpNodeD(const void *key1, void *key2);

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
    keva_t pair = {0};
    size_t room = 0;
    dlist_iter_t noob;

    pair.key = new_key;
    pair.value = data;
    room = hash->hash_func(new_key);
    
    assert(room <= hash->size);

    if(NULL == hash->table[room])
    {
       hash->table[room] = DListCreate();
       
    }
    assert(data != HashFind(hash, new_key));

    noob = DListPushBack(hash->table[room], data);
    assert(!DListIsEqual(DListBegin(hash->table[room]),DListEnd(hash->table[room]) ));
    return (DListIsEqual(noob, DListEnd(hash->table[room])));

}


void *HashFind(const hash_t *hash, const void *key)
{
    size_t room = 0;
    dlist_t *level = NULL;
    dlist_iter_t found;

    assert(NULL != hash);
    assert(NULL != key);

    level = hash->table[hash->hash_func(key)];

    if(NULL != level)
    {
        found = DListFind(DListBegin(level), DListEnd(level), hash->cmp_func, key);

        return (DListIsEqual(found, DListEnd(level))? NULL : DListGetData(found) );
    }
    return level;
}

void HashRemove(hash_t *hash, const void *key)
{
    size_t room = 0;
    dlist_iter_t runner = NULL;
    dlist_iter_t end = NULL;


    assert(NULL != hash);
    assert(NULL != key);

    room = hash->hash_func(key);
    assert(room <= hash->size);

    if(hash->table[room] != NULL)
    {
        runner = DListBegin(hash->table[room]);
        end = DListEnd(hash->table[room]);

        runner = DListFind(runner,end, hash->cmp_func, key);

       if (!DListIsEqual(runner, end))
       {
            DListRemove(runner);
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
            if(hash->table[rooms]!= NULL)
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

    for (room = 0; room < hash->size && SUCCESS == stat; ++room)
    {
        dlist_t *level = hash->table[room];
        if (NULL != level)
        {
            stat = DListForEach(
                DListBegin(level), DListEnd(level), action_func, param);
        }
        else
        {
            stat = FAIL;
        }
    }

    return stat;
}






int MatchNum(const void *data, void *param)
{   
    assert(NULL != param);

    return (*(size_t *)data == *(size_t *)param);
}

int CmpNodeD(const void *key1, void *key2)
{   
   
    return (*(int *)key1 - *(int *)key2);
}
