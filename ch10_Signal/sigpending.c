
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void
signal_handler(int signo)
{
    if (signo == SIGUSR1)
        printf("Catch SIGUSR1\n");
    if (signo == SIGUSR2)
        printf("Catch SIGUSR2\n");
}

int main(void)
{
    sigset_t set, oset, pendset;

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);

    sigprocmask(SIG_SETMASK, &set, &oset);

    raise(SIGUSR1);
    if (sigpending(&pendset) == -1)
        exit(-1);
    if (sigismember(&pendset, SIGUSR1))
        printf("SIGUSR1 is pending\n");
    if (sigismember(&pendset, SIGUSR2))
        printf("SIGUSR2 is pending\n");

    return 0;
}
