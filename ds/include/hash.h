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
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 * Complexity: time O(1) or O(m) (your choice), space O(m)*/
hash_t *HashCreate(size_t size, hash_get_key_func_t get_key, 
			hash_cmp_func_t cmp_func, hash_func_t hash_func);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by counting instances of elements
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
 * Algorithm sorts given array, by counting instances of elements
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 * Complexity: time O(1) (amortized), space O(1)*/
int HashInsert(hash_t *hash, void *data);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by counting instances of elements
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 * Complexity: time O(1) (amortized), space O(1)*/
void HashRemove(hash_t *hash, const void *key);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by counting instances of elements
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 * Complexity: time O(1) (amortized), space O(1)*/
void *HashFind(const hash_t *hash, const void *key);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by counting instances of elements
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 * Complexity: time O(1) space O(1)*/
size_t HashSize(const hash_t *hash);

 /* Complexity: time O(m) space O(1)*/
int HashIsEmpty(const hash_t *hash);

 /* Complexity: time O(n) space O(1)*/ /* it cannot change the data! */
int HashForEach(const hash_t *hash, hash_action_func_t action_func, void *param);

#endif /* __HASH_H__*/
