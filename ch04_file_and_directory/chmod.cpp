
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio>
#include "func.hpp"

int main(int argc, char **argv) {

    struct stat statbuf;
    const char *foofile = "foo";
    const char *barfile = "bar";
    if (stat(foofile, &statbuf) < 0)
        sys_exit("foo file error");

    if (chmod(foofile, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        sys_exit("chmod error");

    if (chmod(barfile, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        sys_exit("chmod error for bar");

    return 0;
}
