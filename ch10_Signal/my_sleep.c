
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

static void 
sig_alrm1(int signo)
{
    /* nothing to do */
}

unsigned int 
sleep1(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm1) == SIG_ERR)
        return (seconds);
    alarm(seconds);
    pause();
    return (alarm(0));
}

/************ version 2 *************/

static jmp_buf env_alrm;
static void
sig_alrm2(int signo)
{
    longjmp(env_alrm, 1);
}

unsigned int 
sleep2(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm2) == SIG_ERR)
        return seconds;
    if (setjmp(env_alrm) == 0) {
        alarm(seconds);
        pause();
    }
    return alarm(0);
}

