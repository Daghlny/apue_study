
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <cstdio>
#include <errno.h>
#include <cstdlib>

int
main(int argc, char **argv)
{
    pid_t pid = 0;
    printf("Main Process: %d\n", getpid());


    int nzero = 0;
#if defined(NZERO)
    nzero = NZERO;
#elif defined(_SC_NZERO)
    nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
    int adj = (argc > 1) ? atoi(argv[1]) : nzero;
    printf("NZERO: %d\n", nzero);
    char *s;

    pid = fork();
    if( pid == 0 ) printf("Child Process: %d\n", getpid());

    unsigned long long count = 0;
    struct timeval begin, end;

    gettimeofday(&begin, NULL);
    if (pid == 0) {
        errno = 0;
        int ret = nice(adj);
        if (ret == -1 && errno != 0) {
            printf("nice error\n");
            exit(0);
        }
        printf("Current nice value in Child: %d\n", nice(0)+nzero);
        s = "child";
    } else {
        printf("Current nice value in Parent: %d\n", nice(0)+nzero);
        s = "parent";
    }

    count = 0;
    while(++count) {
        gettimeofday(&end, NULL);
        if (end.tv_sec >= begin.tv_sec+10 && end.tv_usec >= end.tv_usec) {
            printf("%s count = %lld\n", s, count);
            exit(0);
        }
    }

    return 0;
}
