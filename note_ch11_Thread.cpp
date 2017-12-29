
#include <pthread.h>
int pthread_equal(pthread_t tid1, pthread_t tid2);

pthread_t pthread_self(void);

int pthread_create(pthread_t *restrict tidp, 
                   const pthread_attr_t *restrict attr, 
                   void *(*start_rin)(void*), 
                   void *restrict arg);

void pthread_exit(void *rval_ptr);

int pthread_join(pthread_t thread, void **rval_ptr);

int pthread_cancel(pthread_t tid);

void pthread_cleanup_push(void (*rtn)(void*), void *arg);

void pthread_cleanup_pop(int execute);

int pthread_detach(pthread_t tid);

#include <pthread.h>
/*
 * return 0 if success, return error number if error occurs
 */
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

#include <pthread.h>
/*
 * return 0 if success, return error number if error occurs
 */
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
// if beyond the \tsptr's time, \pthread_mutex_timedlock will return ETIMEDOUT
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex,
                            const struct timespec *restrict tsptr);

#include <pthread.h>
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
                        const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_wrlock_t *rwlock);

#include <pthread.h>
#include <time.h>
int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock,
                               const struct timespec *restrict tsptr);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock,
                               const struct timespec *restrict tsptr);

/**************** Condition Variable ***************/
#include <pthread.h>
/* static init: PTHREAD_COND_INITIALIZER */
int pthread_cond_init(pthread_cond_t *restrict cond, 
                      const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *restrict cond, 
                      pthread_mutex_t *restrict mutex);
int pthread_cond_timedwait(pthread_cond_t  *restrict cond, 
                           pthread_mutex_t *restrict mutex,
                           const struct timespec *restrict tsptr);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);

/***************** Spinlock *****************/
#include <pthread.h>
int pthread_spin_init(pthread_spinlock_t *lock, int pshard);
int pthread_spin_destroy(pthread_spinlock_t *lock);

int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);

/**************** Barrier ******************/
#include <pthread.h>
int pthread_barrier_init(pthread_barrier_t *restrict barrier, 
                         const pthread_barrierattr_t *restrict attr,
                         unsigned int count);
int pthread_barrier_destroy(pthread_barrier_t *barrier);
int pthread_barrier_wait(pthread_barrier_t *barrier);

