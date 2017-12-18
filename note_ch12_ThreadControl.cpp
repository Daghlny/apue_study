
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
