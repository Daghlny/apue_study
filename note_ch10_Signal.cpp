
#include <signal.h>
/*
 * \func: SIG_IGN, SIG_DFL
 * \return previous singal handler for success or SIG_ERR for error
 */
void (*signal(int signo, void (*func)(int)))(int);

#include <signal.h>
/*
 * both return 0 for success, -1 for error 
 * raise(signo) == kill(getpid(), signo);
 */
int kill(pid_t pid, int signo);
int raise(int signo);

#include <unistd.h>
/*
 * \return 0 or remaining seconds
 */
unsigned int alarm(unsigned int seconds);
int pause(void);

#include <signal.h>
/*
 * first four funcs: 0 for success, -1 for error
 * \sigismember: 0 for FALSE, 1 for TRUE
 */
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
int sigismember(const sigset_t *set, int signo);

#include <signal.h>
/*
 * \how: SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK
 * \return 0 for success, -1 for error
 */
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);

#include <signal.h>
int sigpending(sigset_t *set);

#include <signal.h>
struct sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
    /* alternate handler */
    void (*sa_sigaction)(int, siginfo_t *, void *);
};
int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oact);

#include <setjmp.h>
int sigsetjmp(sigjmp_buf env, int savemask);
void siglongjmp(sigjmp_buf env, int val);

#include <stdlib.h>
void abort(void);











