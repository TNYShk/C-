/***********************************
 * 100k threads - Source File      *
 * Developer: Tanya                *
 *          Feb 23, 2022           *
 *                                 *
 * Reviewer: Zohar                 *
************************************/
#include <stdio.h> /* printf*/
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <time.h> /* time*/
#include <stdlib.h> /* error macro */
#include <omp.h> /* pragma openMP */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define STOP (32700)
#define TH_ARR_SIZE (100000)
#define NEW_STOP (10000)
#define HUGE_NUM (1111111111UL)
#define SUCCESS (0)

/* ex 1-3*/ 
int counter_g = 0;
size_t thread_arr[TH_ARR_SIZE] = {0};
static pthread_mutex_t mutexi = PTHREAD_MUTEX_INITIALIZER;

/* ex 5*/
const size_t huge_g = 1111111;
size_t range_g = 0; 


void Ex1_2(void);
void Ex3(void);
void Ex4(void);
void Ex5(size_t max_threads);
static void *InitArr(void *idx);
static void *ThreadDivFunc(void *);
static void *ThreadFunc(void *);
static void *ThreadDivFunc5(void *val);
void CheckArr(size_t);
void SumOfDivs(void);

/* 
compile: gd *.c  -pthread -fopenmp
run:     time ./a.out
*/

int main(void)
{
    /*size_t ex5 =3;
     Ex4();
    Ex3();
    Ex1_2();
   
  
    Ex3();*/
    
     Ex1_2(); 
    /*for(;ex5 < 16; ++ex5)
    {
        Ex5(ex5);
    }
    SumOfDivs();
*/

    return 0;
}



static void *ThreadFunc(void *dummyPtr)
{
    pthread_mutex_lock(&mutexi);
    thread_arr[counter_g] = counter_g;
    ++counter_g;
    pthread_mutex_unlock(&mutexi);
    
    return dummyPtr;
}


void Ex1_2(void)
{
    pthread_t thread_id[STOP] = {0};
    time_t start = time(0);
    size_t idx = 0;
    pthread_attr_t attr = {0};
    counter_g = 0;

    if(SUCCESS != pthread_attr_init(&attr))
    {
        errExit("attr_t init fails");
    }

    if(SUCCESS != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE))
    {
        errExit("attr_t set detach state ");
    }
    for (idx = 0; idx < STOP; ++idx)
    {
        while(SUCCESS != pthread_create(&thread_id[idx], &attr, &ThreadFunc, &idx ));  
    }
    
    pthread_attr_destroy(&attr);

    printf("ex1_2 final counter value: %d\n", counter_g);
    printf("The process took %ld clocks\n", (time(0) - start));
    pthread_mutex_destroy(&mutexi);
    CheckArr(STOP);
    
}


static void *InitArr(void *idx)
{
    thread_arr[(size_t)idx] = (size_t)idx; 
    
    return NULL; 
}


void Ex3(void)
{
    size_t idx = 0;
    time_t start = time(0);
    pthread_attr_t attr = {0};
    
    if(SUCCESS != pthread_attr_init(&attr))
    {
        errExit("attr_t_init");
    }

    if(SUCCESS != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
    {
        errExit("attr_t_setdetachstate");
    }

    for (;idx < TH_ARR_SIZE; ++idx)
    {
        pthread_t id = 0;
        while(SUCCESS != pthread_create(&id, &attr, &InitArr, (void *)idx ));
    }

    printf("\nex3: final counter value: %ld\n", idx);
    printf("The process took %ld clocks\n", (time(0) - start));

    pthread_attr_destroy(&attr);
    
    CheckArr(TH_ARR_SIZE); 
}


static void *ThreadDivFunc(void *val)
{
    size_t num = (size_t)val;
    size_t idx = 0;
    size_t range = HUGE_NUM / NEW_STOP;
    size_t sum_of_divs = 0;

    for (idx = num; idx < (num + range); ++idx)
    {   
        if (0 == (HUGE_NUM % idx))
        {
            sum_of_divs += idx;
            printf("divisor of %ld is %ld\n",HUGE_NUM, idx);
        }

    }
    pthread_exit((void *)sum_of_divs);
}


void Ex4(void)
{
    size_t idx = 0;
    time_t start = time(0);
    size_t num = 1;
    size_t sum_of_divisors = 0;
    pthread_t thread_id[NEW_STOP] = {0};
    size_t range = HUGE_NUM / NEW_STOP + 1; 

    for (idx = 0; idx < NEW_STOP; ++idx)
    {
        while(SUCCESS != pthread_create(&thread_id[idx], NULL, &ThreadDivFunc, (void *)num));
        num += range;
    }

    for (idx = 0; idx < NEW_STOP; ++idx)
    {
        pthread_join(thread_id[idx], (void *)&num);
        sum_of_divisors += num;
    }
   
    printf("\nex4, sum of divisors: %ld\n", sum_of_divisors);
    printf("The process took %ld clocks\n", (time(0) - start));

    
}

void Ex5(size_t max_threads)
{
    size_t idx = 0;
    clock_t start = clock();
    size_t num = 1;
    size_t sum_of_divisors = 0;
    pthread_t thread_ids[15] = {0};
    
    range_g = huge_g / max_threads + 1; 

    for (idx = 0; idx < max_threads; ++idx)
    {
        while(SUCCESS != pthread_create(&thread_ids[idx], NULL, &ThreadDivFunc5, (void *)num));
        num += range_g;
    }

    for (idx = 0; idx < max_threads; ++idx)
    {
        pthread_join(thread_ids[idx], (void *)&num);
        sum_of_divisors += num;
    }
   
    printf("\nex5, sum of divisors: %ld\n", sum_of_divisors);

    printf("sum of divisors of %ld with %ld threads took %f sec\n",
            huge_g, max_threads, (double)(clock() - start)/CLOCKS_PER_SEC);

}

static void *ThreadDivFunc5(void *val)
{
    size_t num = (size_t)val;
    size_t idx = 0;
    
    size_t sum_of_divs = 0;
    
    for (idx = num; idx < (num + range_g); ++idx)
    {   
        if (0 == (huge_g % idx))
        {
            sum_of_divs += idx;
            /*printf("divisor of %ld is %ld\n",huge_g, idx);*/
        }

    }
    pthread_exit((void *)sum_of_divs);
}





/*single thread sum of all dividors */
void SumOfDivs(void)
{
    time_t start = time(0);
    size_t idx = 0;
    size_t sum_of_divs = 0;
#pragma omp parallel for num_threads (4)
    for (idx = 1; idx <= HUGE_NUM; ++idx)
    {
        if(0 == HUGE_NUM % idx)
        {
            sum_of_divs += idx;
            /*printf("divisor of %ld is %ld\n",HUGE_NUM, idx);*/
        }
    }
    
    printf("\nex4 single thread: %ld \n", sum_of_divs);
    printf("The process took %ld clocks\n", (time(0) - start));
}





void CheckArr(size_t length)
{
    size_t i = 0;
    for(; i < length; ++i)
    {
        assert(thread_arr[i] == i);
    }
}

