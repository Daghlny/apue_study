
#include "../apue.h"
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int 
main(void) {

    int fd = open("./text.txt", O_CREAT | O_RDWR | O_TRUNC);

    pid_t pid = 0;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        /* child process */
        sleep(1);
        char writebuf[1000];
        memset(writebuf, 0, sizeof(writebuf));
        for (int i = 0; i < 30; ++i)
            writebuf[i] = 48+i;
        write(fd, writebuf, strlen(writebuf));
        exit(0);
    } else {
        /* parent prcess */
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(fd, &readset);
        int valid_fd_num = select(fd+1, &readset, NULL, NULL, NULL);
        if (FD_ISSET(fd, &readset)) {
            char buf[1000];
            memset(buf, 0, sizeof(buf));
            int n2read = read(fd, buf, sizeof(buf));
            printf("read %d bytes\n", n2read);
            printf("%s\n", buf);
        } else {
            err_sys("select return error");
        }
        valid_fd_num = select(fd+1, &readset, NULL, NULL, NULL);
        if (FD_ISSET(fd, &readset)) {
            char buf[1000];
            memset(buf, 0, sizeof(buf));
            int n2read = read(fd, buf, sizeof(buf));
            printf("read %d bytes\n", n2read);
            printf("%s\n", buf);
        } else {
            err_sys("select return error");
        }
    }
    int exitstat = 0;
    wait(&exitstat);

    return 0;
}
