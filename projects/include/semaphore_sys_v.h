#ifndef __SEMAPHORE_SYS_V_H__
#define __SEMAPHORE_SYS_V_H__

int InitSem      (size_t init_val);
int SemDecrement (int sem_id, size_t dec_by);
int SemIncrement (int sem_id, size_t inc_by);
int SemGetVal    (int sem_id);
int SemRemove    (int sem_id);



#endif /* __SEMAPHORE_SYS_V_H__ */
