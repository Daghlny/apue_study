
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THR_NUM 8
#define ARR_NUM 8000000L
#define PER_NUM 1000000L
    
pthread_barrier_t barrier;

void
local_sort(int *nums, int num)
{
    for (int *i = nums; i < nums+num; ++i) {
        for (int *j = i+1; j < nums+num; ++j) {
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
    int count = num/per;
    int *pos = (int *)malloc(sizeof(int) * count);
    for (int i = 0; i < count; ++i) 
}

void *
thr_func(void *arg)
{
    int *nums = (int *)arg;
    local_sort(nums, PER_NUM);

    pthread_barrier_wait(&barrier);
    
    return NULL;
}

int
main(void)
{
    pthread_barrier_init(&barrier, NULL, THR_NUM+1);

    struct sarg_t sarg;
    int *nums = (int *)malloc(sizeof(int) * ARR_NUM);
    for (int i = 0; i < ARR_NUM; ++i) 
        nums[i] = random();

    pthread_t thds[THR_NUM];
    for (int i = 0; i < THR_NUM; ++i) {
        pthread_create(thds+i ,NULL, thr_func, nums+(i*PER_NUM));
    }
    
    pthread_barrier_wait(&barrier);
    merge_arr(nums, ARR_NUM, PER_NUM);

    pthread_barrier_destroy(&barrier);
    return 0;
}
