#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdlib.h> /* calloc, malloc, free*/
#include <string.h> /*memcpy */
#include <pthread.h> /* threads*/
#include <unistd.h> /* sleep, wait*/
#include <stdio.h> /*printf*/
#include <time.h>
#include <sys/time.h>
#include <math.h>



#define SUCCESS (0)
#define SIZE (100000)
#define BASE (10)
#define MIN(a,b) ((a)< (b)? (a) : (b))
#define MIN3(a,b,c) ( (MIN(a,b)) < (c) ? (MIN((a),(b))): (c) )
#define atomic_sub_and_fetch(destptr, decrement) __sync_sub_and_fetch(destptr, decrement)
#define atomic_add_and_fetch(destptr, increment) __sync_add_and_fetch(destptr, increment)

/*mutltithreaded qsort */
pthread_mutex_t qmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_attr_t attr = {0};

int max_threads_g = 0;
int n_threads_g = 0;
int data[SIZE] = {0};
int dataset[SIZE] = {0};

int arrtest_g[SIZE] = {0};

int arrdata[SIZE] = {0};
int left[SIZE /2] = {0};
int right[SIZE /2] = {0};
int part = 0;
void merge(int start, int mid, int end);
void merge_sort(int start, int end);
void Init_threads_merge_sort();

void count_sort(int radix);
void RadixTanya(void);
static int MaxDigits(int max);
static int FindMax(size_t len);


void Init_Array(int *data, int len);
void VerifySortTest(int *data, int len);
void PrintSome(int *data, int somelen);
double TimeTest(void);

void InitThreadSort(int *data, int len);
void QuickThreadSort(int *, int *);
void InsertSort(int *, int *);

static void *ThreadSortFunc(void *args);
static void Sort_3_Swap(int *a, int *b, int *c);
static void Partition(int *left0, int *right0, int **l1, int **r1, int **l2, int **r2);
static void PSwap(int *i , int *j);


typedef int (*cmp_func_t)(const void *, const void *);

void MergeSort(void *arr_to_sort, size_t num_elements,  unsigned int size_elem);
void RecMergeSort(void *arr, void *helper, size_t left, size_t right);
void Merge(void *arr, void *help, size_t low, size_t mid, size_t high);
void *ThreadMergeSortFunc(void *arg);
void InitThreadMergeSort(int *data);



int main(void) 
{
/*
  Init_Array(data, SIZE);
    printf("Sorting 50 Million numbers with Quicksort ...\n");
    TimeTest();
    InitThreadSort(data, SIZE);
    printf("took %.2fs\n", TimeTest());
    VerifySortTest(data, SIZE);
    
     printf("\n now merge sort threads..\n");
    Init_Array(arrdata, SIZE);
    printf("Sorting 50 Million numbers with MergeSort 4 threads ...\n");
    
    TimeTest();
    Init_threads_merge_sort();
     printf("took %.2fs\n", TimeTest());
*/

     printf("\n\n"); 
    Init_Array(arrtest_g, SIZE);
    printf("Radix sort\n");
    TimeTest();
    RadixTanya();
    printf("took %.2fs\n", TimeTest());
    VerifySortTest(arrtest_g, SIZE);
     
  
    
    return 0;
}

void VerifySortTest(int *data, int len) 
{
    int i = 0;
    for (i = 1; i < len; ++i) 
    {
        if (data[i] < data[i - 1]) 
        {
            printf("ERROR: ");
            printf("%d, %d \n", data[i - 1], data[i]);
           /*  break; */
        }
    }
}


double TimeTest(void) 
{
    double h = 0.0;
    static double t0 = 0.0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    h = t0;
    t0 = tv.tv_sec + tv.tv_usec / 1000000.0;
    
    return t0 - h;
}


void Init_Array(int *data, int len) 
{
    int i = 0;
    printf("\n\tInitialiing %d- sized array!\n", SIZE);
    
    for(; i < len; ++i) 
    {
        data[i] = rand() % SIZE;
    }
   
}

void PrintSome(int *data, int somelen)
{
    int i = 0;
    for(; i < somelen; ++i)
    {
        printf("%d ,", data[i]);
        if(i % 50 == 0)
            printf("\n");
    }
}


static void Sort_3_Swap(int *a, int *b, int *c)
{
    int holder =  MIN3(*a, *b, *c);
    if(*a != holder)
    {
        PSwap(a, &holder);
        if(*b == *a)
        {
            *b = MIN(holder, *c);
        }
        else
        {
            *b = MIN(holder, *b);
        }
        PSwap(&holder, c);
    }
    else
    {
        holder = *b;
        *b = MIN(*b, *c);
        if (*b != holder)
        {
            PSwap(&holder, c);
        }
    }   
}




static void PSwap(int *i , int *j)
{
	int holder = 0;

	assert (NULL != j);
	assert (NULL != i);
	
	holder = *j;
	*j = *i;
	*i =  holder;
}

void InsertSort(int *left, int *right)
{
    int *help = NULL;

    for(help = left + 1; help <= right; ++help)
    {
        if(*help < *left)
        {
            PSwap(help, left);
        }

    }
    for(help = left + 2; help <=right; ++help)
    {
        int holder = *help;
        int *help_holder = help - 1;

        while (holder < *help_holder)
        {
            *(help_holder + 1) = *help_holder;
            --help_holder; 
        }
         *(help_holder + 1) = holder;
    }
}

static void *ThreadSortFunc(void *args)
{
    int **param = (int **)args;
    QuickThreadSort(param[0], param[1]);
    free(args);

    pthread_mutex_lock(&qmutex);
        atomic_sub_and_fetch(&n_threads_g, 1);
    pthread_mutex_unlock(&qmutex);
    if(n_threads_g == 0)
    {
        pthread_cond_broadcast(&cond);
    }
    return NULL;
}


void QuickThreadSort(int *left, int *right)
{
    while (right - left >= 50) {
        int *n_left = NULL, *n_right = NULL;
        Partition(left, right, &n_left, &n_right, &left, &right);

        if (right - left > 100000 && n_threads_g < max_threads_g) 
        {
           /*start a new thread - max_threads is a soft limit*/
            pthread_t thread = 0;
            pthread_attr_t attr = {0};

            int **param = (int **)malloc(2 * sizeof(int *));
            if(NULL == param)
            {
                printf("malloc line %d failed!\n", __LINE__);
            }
            param[0] = left;
            param[1] = right;

            pthread_mutex_lock(&qmutex);
                atomic_add_and_fetch(&n_threads_g, 1);
            pthread_mutex_unlock(&qmutex);

            if(SUCCESS != pthread_attr_init(&attr))
            {
                printf("failed thread attr %d\n", __LINE__);
                return;
             }
            if(SUCCESS != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
            {
                printf("failed detached attr %d\n", __LINE__);
            }

            while(SUCCESS != pthread_create(&thread, &attr, &ThreadSortFunc, param));
            left = n_left;
            right = n_right;
        }
        else 
        {
            QuickThreadSort(n_left, n_right);
        }
    }
    InsertSort(left, right);
}

 
static void Partition(int *left0, int *right0, int **l1, int **r1, int **l2, int **r2) 
{
  
    int *left = left0 + 1;
    int *right = right0;
    int *mid = left0 + (right0 - left0) / 2;    
    int piv = *mid;
   
    *mid = *left;
   
    Sort_3_Swap(left0, &piv, right0);
    *left = piv;

    while (1) 
    {
        do 
        {
            left += 1; 
        } while(*left < piv);

        do 
        {
            right -= 1; 
        } while (*right > piv);

        if (left >= right) 
            break;

        PSwap(left, right);
    }
    *(left0 + 1) = *right;
    *right = piv;

    if (right < mid) 
    {
        *l1 = left0; *r1 = right - 1;
        *l2 = right + 1; *r2 = right0;
    }
    else 
    {
        *l1 = right + 1; *r1 = right0;
        *l2 = left0; *r2 = right - 1;
    }
}


void InitThreadSort(int *data, int len) 
{
    pthread_t thread = 0;
    pthread_attr_t attr = {0};
    int n_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    int **param = (int **)malloc(2 * sizeof(int *));
   
    if(SUCCESS != pthread_attr_init(&attr))
    {
        printf("failed thread attr %d\n", __LINE__);
        return;
    }
   
    if(NULL == param)
    {
        printf("malloc %d failed\n", __LINE__);
        return;
    }
    printf("num of cpu's %d\n", n_cpus);
    if (n_cpus > 0)
    {
        max_threads_g = n_cpus << 1;
    }
    else
    {
        max_threads_g = 8;
    } 
     printf("max threads then is: %d\n", max_threads_g);
    
    param[0] = data;
    param[1] = data + len - 1;
    n_threads_g = 1;

    if(SUCCESS != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
    {
        printf("failed detached attr %d\n", __LINE__);
    }

    while(SUCCESS != pthread_create(&thread, &attr, &ThreadSortFunc, param));

    pthread_mutex_lock(&qmutex);
        pthread_cond_wait(&cond, &qmutex);
    pthread_mutex_unlock(&qmutex);
}






void InitThreadMergeSort(int *data)
{
    pthread_t merged_th[8] = {0};
    size_t idx = 0;
   
    
    for(; idx < 8; ++idx)
    {
        while(SUCCESS != pthread_create(&merged_th[idx],NULL, &ThreadMergeSortFunc,(void *)data ));
    }
    for(idx = 0; idx < 8; ++idx)
    {
        pthread_join(merged_th[idx], NULL);
    }
}

void *ThreadMergeSortFunc(void *arg)
{
   void *holder = arg;
   MergeSort(holder, SIZE, sizeof(int));
 
    return NULL;
}



void MergeSort(void *arr_to_sort, size_t num_elements, unsigned int size_elem)
{
    void *helper = (void *)calloc(num_elements , size_elem);
    if(NULL == helper)
    {
        return;
    }
    assert(NULL != arr_to_sort);

    memcpy(helper, arr_to_sort, size_elem * SIZE);
   
    RecMergeSort(arr_to_sort, helper, 0, num_elements - 1);
      
    free(helper);
    helper = NULL;
}

void RecMergeSort(void *arr, void *helper, size_t left, size_t right)
{
    size_t mid = 0;

    if (right == left)
    {
        return;
    }

    mid = (left + ((right - left) >> 1));

    RecMergeSort(arr, helper, left, mid);
    RecMergeSort(arr, helper, mid + 1, right);

    Merge(arr, helper, left, mid, right);
}

void Merge(void *arr, void *help, size_t start, size_t mid, size_t end)
{
    
    size_t left_sub = start;
    size_t right_sub = mid + 1;
    size_t i = start;
    int *temp = (int *)arr;
    int *a_temp = (int *)help;
	
    while ((left_sub <= mid) && (right_sub <= end))
    {
       a_temp[i++] = (temp[left_sub] <= temp[right_sub]) ? (temp[left_sub++]) : 
    	                                               (temp[right_sub++]);
    }

    if(left_sub <= mid)
	{
		size_t remain = mid - left_sub + 1;
		memcpy(a_temp + i, temp + left_sub, sizeof(int) * remain);
		i += remain;
	}

	memcpy(temp + start, a_temp + start, sizeof(int) * (i - start));

}

void merge(int start, int mid, int end)
{
    int n1 = mid -start +1;
    int n2 = end - mid;
    int idx = 0, jdx = 0;
    int k = 0;

    for(;idx < n1; idx++)
    {
        left[idx] = arrdata[idx + start];
    }

    for(idx = 0; idx < n1; ++idx)
    {
        right[idx] = arrdata[idx + mid + 1];
    }
    k = start;
    idx = jdx = 0;

    while ((idx < n1) &&(jdx < n2) )
    {
        if (left[idx]<= right[jdx])
        {
            arrdata[k++] = left[idx++];
        }
        else
        {
            arrdata[k++] = right[jdx++];
        }
        while(idx < n1)
        {
           arrdata[k++] = left[idx++];
        }
        while(jdx < n2)
        {
            arrdata[k++] = right[jdx++];
        }
    }
   
}

void merge_sort(int start, int end)
{
    int mid = start + (end - start)/2;

    if (start < end)
    {
        merge_sort(start, mid);
        merge_sort(mid +1, end);

        merge(start, mid, end);
    }
}

void *merge_s(void *arg)
{
    int thread_part = part++;
    int low = thread_part * (SIZE / 4);
    int high = (thread_part + 1) * (SIZE / 4) - 1;
    int mid = low + (high - low) / 2;

    if (low < high)
    {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
    return arg;
}


void Init_threads_merge_sort()
{
    pthread_t merged_th[4] = {0};
    size_t idx = 0;
   
    
    for(; idx < 4; ++idx)
    {
        while(SUCCESS != pthread_create(&merged_th[idx],NULL, &merge_s, NULL));
    }
    for(idx = 0; idx < 4; ++idx)
    {
        pthread_join(merged_th[idx], NULL);
   
    }


    merge(0, (SIZE / 2 - 1) / 2, SIZE / 2 - 1);
    merge(SIZE / 2, SIZE/2 + (SIZE-1-SIZE/2)/2, SIZE - 1);
    merge(0, (SIZE - 1)/2, SIZE - 1);
    
    
    VerifySortTest(arrdata, SIZE);
    PrintSome(arrdata,SIZE);
}

void RadixTanya(void)
{
	int max = FindMax(SIZE);
    int position = 1;

    for (position = 1; (max/position) > 0; position *= 10)
    {
        count_sort(position);
    }
}

static int FindMax(size_t len)
{
	int *left = arrtest_g;
	int *right = arrtest_g + len - 1;
	int max = *arrtest_g;

	while(left < right)
	{
		if(*left > max)
		{
			max = *left;
		}
		++left;
	}
    printf("max val is %d\n", max);
	return max;
}

void count_sort(int radix)
{
	int idx = 0;
    int *arrC = (int *)calloc(10, sizeof(int));
    int *temp = (int *)calloc(SIZE, sizeof(int));
    assert(NULL != arrC);
     assert(NULL != temp);

	for(idx = 0; idx < SIZE; ++idx)
	{
		arrC[((arrtest_g[idx]/ radix) % 10)]++;
	}

	for(idx = 1; idx < 10 ; ++idx)
	{
		arrC[idx] += arrC[idx - 1];
	}

	for(idx = SIZE - 1; idx >= 0; --idx)
	{
	    temp[arrC[((arrtest_g[idx]/radix) % 10)] -1] = arrtest_g[idx];
		arrC[((arrtest_g[idx] / radix) % 10)]--;
	}
    for (idx = 0; idx < SIZE; ++idx)
    {
        arrtest_g[idx] = temp[idx];
    }
    free(arrC);
    free(temp);
}

static int MaxDigits(int max)
{
	int digit_counter = 0;

	assert(0 < max);

	while(max)
	{
		++digit_counter;
		max /= BASE;
	}
	return digit_counter;
}