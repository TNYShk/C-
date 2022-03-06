#ifndef __SEMAPHORE_POSIX_H__
#define __SEMAPHORE_POSIX_H__




/* DESCRIPTION: 
 * Create new POSIX semaphore or update existing one for undo-ability
 *

 * PARAMS: 
 * const char *name - named semaphore
 * init_num - value of the created semapthore
 * Dou - flag for undo-able semaphore (0 - not, 1- yes)
 * 
 * RETURN:
 * newly created semaphore/ existing semaphore
 * 
 */
sem_t *InitSemaphore(const char *name, int init_num, int DoU);

/* DESCRIPTION: 
 * perform sem_wait in the given semaphore val - amount of times
 *

 * PARAMS: 
 * *sem - named semaphore
 * val - amout to decrease 
 * 
 * 
 * RETURN:
 * 0 SUCCESS, otherwise exit error
 * 
 */
int DoDecrement(sem_t *sem, unsigned int val);

/* DESCRIPTION: 
 * perform sem_post in the given semaphore val - amount of times
 *

 * PARAMS: 
 * *sem - named semaphore
 * val - amout to increase 
 * 
 * 
 * RETURN:
 * 0 SUCCESS, otherwise exit error
 * 
 */
int DoIncrement(sem_t *sem, unsigned int val);

/* DESCRIPTION: 
 * Remove and Close named semaphore, perform sem_unlink 
 *

 * PARAMS: 
 * *sem - named semaphore to remove
 * 
 * 
 * 
 * RETURN:
 * 0 SUCCESS, otherwise exit error
 * 
 */
int DoUnlink(sem_t *sem);

/* DESCRIPTION: 
 * Get current names semaphore's value
 *

 * PARAMS: 
 * *sem - named semaphore 
 * 
 * 
 * 
 * RETURN:
 * the value
 * 
 */
int DoView(sem_t *sem);


/* DESCRIPTION: 
 *  Close named semaphore, perform sem_close, frees resources
 *

 * PARAMS: 
 * *sem - named semaphore to close
 * 
 * 
 * 
 * RETURN:
 * 0 SUCCESS, otherwise exit error
 * 
 */
int DoExit(sem_t *sem);


#endif /* __SEMAPHORE_POSIX_H__ */
