
#include <fcntl.h>
/* 
 * \cmd can be F_GETLK, F_SETLK, F_SETLKW
 * struct flock {
 *     short l_type;  F_RDLCK, F_WRLCK or F_UNLCK 
 *     short l_whence;  SEEK_SET, SEEK_CUR or SEEK_END
 *     off_t l_start;   
 *     off_t l_len;
 *     pid_t l_pid;
 * };
 */
int fcntl(int fd, int cmd, .../* struct flock *flockptr */);

#include <sys/select.h>
/* return non-zero if \fd in \fdset, otherwise return 0 */
int FD_ISSET(int fd, fd_set *fdset);
void FD_CLR(int fd, fd_set *fdset);
void FD_SET(int fd, fd_set *fdset);
void FD_ZERO(fd_set *fdset);

/* return -1 if error
 * return 0 if no-fds are prepared
 * return >0 for the amount of prepared fds*/
int select(int maxfdp1, 
           fd_set *restrict readfds,
           fd_set *restrict writefds,
           fd_set *restrict exceptfds,
           struct timeval *restrict tvptr);

int pselect(int maxfdp1,
            fd_set *restrict readfds,
            fd_set *restrict writefds,
            fd_set *restrict exceptfds,
            const struct timespec *restrict tsptr,
            const sigset_t *restrict sigmask);

#include <poll.h>
/*
 *  struct pollfd {
 *      int fd;
 *      short events;
 *      short revents;
 *  };
 *  POLLIN POLLRDNORM POLLRDBAND POLLPRI
 *  POLLOUT POLLWRNORM POLLWRBAND 
 *  POLLERR POLLHUP POLLNVAL
 */
int poll(struct pollfd fdarray[], nfds_t nfds, int timeout);


#include <sys/epoll.h>

int epoll_create(int size);
int epoll_create1(int flags);

/* 
 * \op can be EPOLL_CTL_ADD EPOLL_CTL_MOD EPOLL_CTL_DEL
 *
 * typedef union epoll_data {
 *     void *ptr;
 *     int  fd;
 *     uint32_t u32;
 *     uint64_t u64;
 * } epoll_data_t;
 *
 * struct epoll_event {
 *     uint32_t events;
 *     epoll_data_t data;
 * };
 *
 * the \events in \epoll_event:
 * EPOLLIN
 * EPOLLOUT
 * EPOLLRDHUP
 * EPOLLPRI
 * EPOLLERR
 * EPOLLHUP
 * EPOLLET  // set the Edge Triggered for \fd
 * EPOLLONESHOT //
 * EPOLLWAKEUP
 *
 * when \epoll_ctl success, reutrns 0. When an error occurs, \epoll_ctl returns -1 and \errno is set
 * EBADF
 * EEXIST
 * EINVAL
 * ENOENT
 * ENOMEM
 * ENOSPC
 * EPERM
 */
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

/*  When successful, \epoll_wait returns the number of fds ready for the requested I/O, or zero if \timeout
 *  When an error occurs, \epoll_wait returns -1 and \errno is set.
 *  \maxevents is the size of \events
 */
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *sigmask);

#include <aio.h>
/*
 * struct aiocb {
 *     int aio_fildes;
 *     off_t aio_offset;
 *     volatile void *aio_buf;
 *     size_t aio_nbytes;
 *     int aio_reqprio;
 *     struct sigevent aio_sigevent;
 *     int aio_lio_opcode;
 * };
 *
 * struct sigevent {
 *     int             sigev_notify;
 *     int             sigev_signo;
 *     union           sigval sigev_value;
 *     void            (*sigev_notify_function)(union sigval);
 *     pthread_attr_t *sigev_notify_attributes;
 * };
 * \sigev_notify can be SIGEV_NONE or SIGEV_SIGNAL or SIGEV_THREAD
 */
int aio_read(struct aiocb* cb);
int aio_write(struct aiocb* cb);

// \op can be O_DSYNC or O_SYNC
int aio_fsync(int op, struct aiocb *cb);

// return 0 for success and use \aio_return to get returnvalue
// return -1 if error and use \errno
// EINPROGRESS if it's still wait
// other with error number
int aio_error(const struct aiocb *cb);

// return -1 if failure
// return returnvalue of \aio_read, \aio_write or \aio_fsync
ssize_t aio_return(const struct aiocb *cb);

//return -1 and errno = EINTR while SIGNAL occurs
//return -1 and errno = EAGAIN if \timeout is over
//return 0 if any AIO operation has finished
int aio_suspend(const struct aiocb* const list[],
                int nent,
                const struct timespec* timeout);

int aio_cancel(int fd, struct aiocb *cb);

/*
 * \mode can be LIO_WAIT or LIO_NOWAIT
 */
int lio_listio(int mode, struct aiocb *const list[], int nent, struct sigevent *sigev);

#include <sys/uio.h>
/*
 * struct iovec {
 *     void *iov_base;
 *     size_t iov_len;
 * };
 * \iovcnt is the size of \iov
 * \return the number of bytes that read or writed
 */
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#include <sys/mman.h>
/* 
 * \addr often be 0
 * \prot = PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE
 * \flag = MAP_FIXED, MAP_SHARED, MAP_PRIVATE
 * \return the buffer's address, MAP_FAILED if error occurs
 */
void *mmap(void *addr, size_t len, int prot, int flag, int fd, off_t off);

int mprotect(void *addr, size_t len, int prot);
int msync(void *addr, size_t len, int flags);
int munmap(void *addr, size_t len);



