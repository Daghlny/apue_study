
#include "../apue.h"
#include <stdio.h>
#include <unistd.h>
#include <aio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>

void
init_aio_sigev_none(struct aiocb *cb, int fd, void *buf_addr, size_t nbytes)
{
    cb->aio_fildes = fd;
    cb->aio_offset = 0;
    cb->aio_buf    = buf_addr;
    cb->aio_nbytes = nbytes;

    struct sigevent sevent;
    sevent.sigev_notify = SIGEV_NONE;

    cb->aio_sigevent = sevent;
}

int
main(int argc, char **argv)
{
    struct timeval begT, endT;
    gettimeofday(&begT, NULL);

    char buf[10][100];
    int  fds[10];
    char filename[50];
    memset(filename, 0, sizeof(filename));
    strcpy(filename, "aio_test");

    for (int i = 0; i < 10; ++i) {
        filename[strlen(filename)] = 48+i;
        fds[i] = open(filename, O_RDWR|O_CREAT);
        memset(buf[i], 97+i, sizeof(buf[i]));
    }

    struct aiocb cb[10];

    for (int i = 0; i < 10; ++i)
        init_aio_sigev_none(cb+i, fds[i], buf[i], 100);

    for (int i = 0; i < 10; ++i)
        if (aio_read(cb+i) < 0)
            err_sys("aio_read error");

    for (int i = 0; i < 10; ++i) {
        while(aio_error(cb+i) == EINPROGRESS);
        if (aio_error(cb+i) == 0)
            aio_return(cb+i);
        else
            err_sys("aio_error error");
    }

    for (int i = 0; i < 10; ++i) {
        close(fds[i]);
    }


    gettimeofday(&endT, NULL);
    long long time = 1000000*begT.tv_sec+begT.tv_usec;
    time -= 1000000*endT.tv_sec+endT.tv_usec;

    printf("Total time: %f\n", (double)(time/1000000.00));
    return 0;
}

