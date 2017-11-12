
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include "func.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        sys_exit("parameters is not enough");
    }

    struct stat statbuf;
    wrapper(lstat(argv[1], &statbuf), "stat error");
    int fd = wrapper(open(argv[1], O_TRUNC), "open error");
    struct timespec times[2];
    memcpy(&times[0], &statbuf.st_atime, sizeof(struct timespec));
    memcpy(&times[1], &statbuf.st_mtime, sizeof(struct timespec));
    /*
    times[0].tv_nsec = statbuf.st_atime.tv_nsec;
    times[0].tv_sec  = statbuf.st_atime.tv_sec;
    times[1].tv_sec  = 
    */
    wrapper(futimens(fd, times), "futimens error");
    close(fd);

    return 0;
}
