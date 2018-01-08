
#include "../apue.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>

/*
 * This sample doesn't make sense, because regular file is always ready for read(2) or write(2)
 */

int 
main(int argc, char **argv)
{
    if (argc < 2) 
        err_sys("argc wrong");

    const char *pathname = argv[1];

    pid_t pid = 0;

    if ((pid = fork()) < 0) 
        err_sys("fork error");
    else if (pid == 0) {
        /* child process */
        printf("Child Process %d\n", getpid());

        int fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC);
        char writebuf[1000];
        memset(writebuf, 0, sizeof(writebuf));
        for (int i = 0; i < 40; ++i)
            writebuf[i] = 48+i;
        int writebytes = write(fd, writebuf, strlen(writebuf)+1);
        fsync(fd);
        printf("[%d] write %d bytes\n", getpid(), writebytes);

        close(fd);
        exit(0);
        
    } else {
        /* parent process */
        printf("Parent Process %d\n", getpid());

        int epfd = epoll_create(2);
        int fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC);
        struct epoll_event ep_event;
        ep_event.events = EPOLLIN;
        ep_event.data.fd = fd;
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ep_event) != 0) {
            err_sys("epoll_ctl error");
        }

        struct epoll_event ep_array[5];
        printf("[%d]Begin epoll wait\n", getpid());
        int ready_num = epoll_wait(epfd, ep_array, 5, 1000);
        printf("[%d]There is %d fd is ready\n", getpid(), ready_num);

        for (int i = 0; i < ready_num; ++i) {
            struct epoll_event *ep_ptr = ep_array+i;
            if (ep_ptr->events == EPOLLIN) {
                printf("[%d]the %dth fd is ready for read.\n", getpid(), i);
                char readbuf[1000];
                memset(readbuf, 0, sizeof(readbuf));
                int readbytes = read(ep_ptr->data.fd, readbuf, sizeof(readbuf));
                printf("[%d]read %d bytes from file:\n", getpid(), readbytes);
                printf("%s\n", readbuf);
            }
        }

        close(fd);
        close(epfd);
    }

    int exitstat = 0;
    wait(&exitstat);

    return 0;
}

