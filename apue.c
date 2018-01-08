
#include "apue.h"
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>

/***************** ERROR Process ******************/
static void err_doit(int, int, const char *, va_list);

void 
err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1,errno, fmt, ap);
    va_end(ap);
    exit(1);
}

static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if (errnoflag)
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);
}

/****************** fcntl config ***************/
void set_fl(int, int);

void
clr_fl(int fd, int flags)
{
    set_fl(fd, flags);
}

void
set_fl(int fd, int flags) 
{
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");
    val |= flags;
    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}

/******************* record locking ****************/
int 
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd, cmd, &lock));
}

pid_t 
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if (fcntl(fd, F_GETLK, &lock) < 0)
        err_sys("fcntl error");

    if (lock.l_type == F_UNLCK)
        return 0;

    return (lock.l_pid);
}

