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

int 
main(void)
{
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    raise(SIGUSR1);
    raise(SIGUSR2);

    sigset_t set, oset;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_SETMASK, &set, &oset);

    raise(SIGUSR1);
    raise(SIGUSR2);

    return 0;
}
