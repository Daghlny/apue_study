
/*
 * Thread Attributes:
 * detachstate
 * guardsize
 * stackaddr
 * stacksize
 */
#include <pthread.h>
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

/*
 * \detachstate can be PTHREAD_CREATE_DETACHED or PTHREAD_CREATE_JOINABLE
 */
int pthread_attr_getdetachstate(const pthread_attr_t *restrict attr,
                                int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr, 
                                int *detachstate);

#include <pthread.h>
int pthread_key_create(pthread_key_t *keyp, void (*destructor)(void *));
int pthread_key_delete(pthread_key_t *key);
int pthread_once(pthread_once_t *initflag, void (*initfn)(void));

#include <pthread.h>
/* return Thread Specific Data or NULL when not associated */
void *pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value); // return 0 if success or error number when fail


#include <pthread.h>
// \state can be PTHREAD_CANCEL_ENABLE or PTHREAD_CANCEL_DISABLE
int pthread_setcancelstate(int state, int *oldstate);
void pthread_testcancel(void);
// \type can be PTHREAD_CANCEL_DEFERRED or PTHREAD_CANCEL_ASYNCHRONOUS
int pthread_setcanceltype(int type, int *oldtype);

#include <signal.h>
// \how can be SIG_BLOCK or SIG_SETMASK or SIG_UNBLOCK
// if \set is NULL then \pthread_sigmask can get the old signal mask
int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
// \signop is the amount of signals delivered
int sigwait(const sigset_t *restrict set, int *restrict signop);
int pthread_kill(pthread_t thread, int signo);

#include <pthread.h>
int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));


