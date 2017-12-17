#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

struct job{
    struct job* j_next;
    struct job* j_prev;
    pthread_t   j_id;
};

struct queue {
    struct job *q_head;
    struct job *q_tail;
    pthrad_rwlock_t q_lock;
};

int queue_init(struct queue *qp)
{
    if (qp == NULL) return -1;
    qp->q_head = NULL;
    qp->q_tail = NULL;
    if (pthrad_rwlock_init(&qp->q_lock, NULL) != 0)
        return -2;
    return 0;
}

void job_insert(struct queue *qp, struct job *jp)
{

}

void job_append(struct queue *qp, struct job *jp)
{

}

void job_remove(struct queue *qp, struct job *jp)
{

}

struct job*
job_find(struct queue *qp, pthread_t id)
{
    struct job* jp;
    if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
        return NULL;

    for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
        if (pthread_equal(jp->j_id, id))
            break;

    pthread_rwlock_unlock(&qp->q_lock);
    return jp;
}
