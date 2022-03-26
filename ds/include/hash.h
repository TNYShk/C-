#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h> /* size_t */


typedef struct hash hash_t;


typedef int (*hash_cmp_func_t)(const void *key1, const void *key2);

typedef const void *(*hash_get_key_func_t)(const void *data);
typedef size_t (*hash_func_t)(const void *key);

typedef int (*hash_action_func_t)(void *value, void *param);
/* hash_action_func_t cannot change the data! */


/*
 * DESCRIPTION: 
 * Creates Hash table based on user's given params and funcs
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: SUCCESS is 0 , FAIL (-1) if malloc failed
 * Complexity: time O(1) or O(m) (your choice), space O(m)*/
hash_t *HashCreate(size_t size, hash_get_key_func_t get_key, 
			hash_cmp_func_t cmp_func, hash_func_t hash_func);

/*
 * DESCRIPTION: 
 * Destroy Hash
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 * Complexity: time O(n) space O(1)*/
void HashDestroy(hash_t *hash);

/*
 * DESCRIPTION: 
 * Insert data (dll node) into hash table
 * BUT, duplicates are not welcomed! since result in same key
 *
 * PARAMS: 
 * ptr to the hash table
 * void *data to insert
 * 
 * RETURN: 0 for SUCCESS
 * Complexity: time O(n) (amortized), space O(1)*/
int HashInsert(hash_t *hash, void *data);

/*
 * DESCRIPTION: 
 * Remove element from the hash table, based on given element's key
 * 
 * PARAMS: 
 * ptr to the hash table
 * key of the element to remove
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 * Complexity: time O(1) (amortized), space O(1)*/
void HashRemove(hash_t *hash, const void *key);

/*
 * DESCRIPTION: 
 * find a matching element in the hash table, based on the provided key
 * 
 * PARAMS: 
 * ptr to the hash table
 * key of the element
 * 
 * RETURN: if element exist in the hash, its data is returned. otherwise NULL
 * Complexity: time O(1) (amortized), space O(1)*/
void *HashFind(const hash_t *hash, const void *key);

/*
 * DESCRIPTION: 
 * get the size of the hash table = number of elements
 * 
 * PARAMS: 
 * ptr to the hash table
 * 
 * RETURN: total amount of elements cuurenly residing in the hash
 * Complexity: time O(n) space O(1)*/
size_t HashSize(const hash_t *hash);

 /*
 * DESCRIPTION:
 *  Checks wether hash table is empty.
 *  
 * PARAMS:
 *  ptr to the hash table.
 * 
 * RETURN:
 *  Boolean. 1 if empty, otherwise 0.
 * 
 * Complexity: O(size) time, O(1) space*/
int HashIsEmpty(const hash_t *hash);

 /* Complexity: time O(n) space O(1)*/ /* it cannot change the data! */
int HashForEach(const hash_t *hash, hash_action_func_t action_func, void *param);

#endif /* __HASH_H__*/
