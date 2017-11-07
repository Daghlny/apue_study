
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstdio>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, char **argv) {

    mode_t old_mode = umask(0);
    printf("old mode: %o\n", old_mode);

    if (creat("foo", RWRWRW) < 0) {
        printf("create foo error\n");
        return -1;
    }

    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0) {
        printf("create bar error\n");
        return -1;
    }

    return 0;
}
