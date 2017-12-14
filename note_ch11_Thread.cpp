
#include <pthread.h>
int pthread_equal(pthread_t tid1, pthread_t tid2);

pthread_t pthread_self(void);

int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rin)(void*), void *restrict arg);

void pthread_exit(void *rval_ptr);

int pthread_join(pthread thread, void **rval_ptr);

int pthread_cancel(pthread_t tid);

void pthread_cleanup_push(void (*rtn)(void*), void *arg);

void pthread_cleanup_pop(int execute);

int pthread_detach(pthread_t tid);
