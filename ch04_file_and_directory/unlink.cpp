
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstdio>
#include "func.hpp"

int main(int argc, char **argv) {

    int fd = creat("tempfile", S_IRWXU | S_IRWXG | S_IRWXO);
    close(fd);

    fd = wrapper(open("tempfile", O_RDWR), "open fail");
    struct stat statbuf;
    wrapper(fstat(fd, &statbuf), "stat error");
    printf("size: %d\n", statbuf.st_size);

    wrapper(ftruncate(fd, 4*1024*1024), "truncate error");
    wrapper(unlink("tempfile"), "unlink error");

    printf("file unlinked\n");
    sleep(5);
    printf("done\n");

    return 0;
}
