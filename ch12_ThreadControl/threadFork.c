
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void*
thr_fn(void *arg)
{
    printf("enter thr_fn function\n");
    int var = 42;
    pid_t pid = 0;

    printf("Process: %d | Thread: %ld\n", getpid(), pthread_self());
    fflush(stdout);

    if ((pid = fork()) < 0) {
        printf("fork in thread %ld has error\n", pthread_self());
        exit(0);
    } 
    if (pid == 0) {
        printf("Process: %d | Thread: %ld ", getpid(), pthread_self());
        printf("var: %d\n", var);
        exit(0);
    } else {
        waitpid(pid, NULL, 0);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid;
    pid_t pid;
    printf("Process: %d | Thread: %ld\n", getpid(), pthread_self());

    if (pthread_create(&tid, NULL, thr_fn, NULL) != 0) {
        printf("pthread_create error\n");
        exit(0);
    }
    pthread_join(tid, NULL);
    exit(0);
}

