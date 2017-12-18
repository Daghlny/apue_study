
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define THR_NUM 8
#define ARR_NUM 8000000L
#define PER_NUM 1000000L
    
pthread_barrier_t barrier;

void
local_sort(int *nums, int num)
{
    printf("num: %d\n", num);
    for (int i = num; i >= 0; --i) {
        /*
        if (i % 100000 == 0)
            printf("%ld # %d\n", pthread_self(), i);
            */
        for (int j = 1; j < i; ++j) {
            if (nums[j] < nums[j-1]) {
                int tmp = nums[j];
                nums[j] = nums[j-1];
                nums[j-1] = nums[j];
            }
        }
    }
}

void
merge_arr(int *nums, int num, int per)
{
    int *tmp_nums = (int *)malloc(sizeof(int) * num);
    int count = num/per;
    int *pos = (int *)malloc(sizeof(int) * count);
    for (int i = 0; i < count; ++i) {
        pos[i] = per*i;
    }

    int minvalue = nums[num-1], minidx = 0;
    for (int idx = 0; idx < num; ++idx) {
        for (int i = 0; i < count; ++i) {
            if (pos[i] < (i+1)*(per) && nums[pos[i]] < minvalue) {
                minvalue = nums[pos[i]];
                minidx = i;
            }
        }
        tmp_nums[idx] = minvalue;
        minidx++;
    }

    memcpy(nums, tmp_nums, num*sizeof(int));
}

bool
check_sorted(int *nums, int num) 
{
    for (int i = 1; i < num; ++i) {
        if (nums[i] < nums[i-1]) 
            return false;
    }
    return true;
}

void *
thr_func(void *arg)
{
    int *nums = (int *)arg;
    //local_sort(nums, PER_NUM);
    std::sort(nums, nums+PER_NUM);

    printf("Thread %ld has finished sorting.\n", pthread_self());
    pthread_barrier_wait(&barrier);
    
    return NULL;
}

int
main(void)
{
    pthread_barrier_init(&barrier, NULL, THR_NUM+1);

    int *nums = (int *)malloc(sizeof(int) * ARR_NUM);
    for (int i = 0; i < ARR_NUM; ++i) 
        nums[i] = random();
    printf("nums is generated.\n");

    pthread_t thds[THR_NUM];
    for (int i = 0; i < THR_NUM; ++i) {
        pthread_create(thds+i ,NULL, thr_func, nums+i*PER_NUM);
    }
    
    pthread_barrier_wait(&barrier);
    merge_arr(nums, ARR_NUM, PER_NUM);
    if (check_sorted(nums, ARR_NUM))
        printf("Sorted!\n");
    else 
        printf("It's not sorted!\n");

    pthread_barrier_destroy(&barrier);
    return 0;
}

