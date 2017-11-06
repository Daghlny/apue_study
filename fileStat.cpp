
#include <sys/stat.h>
#include <cstdio>


int main(int argc, char **argv)
{
    if (argc < 2) return -1;

    struct stat myfile_stat;
    if (stat(argv[1], &myfile_stat) == -1) {
        printf("error, return -1\n");
        return -1;
    }

    printf("inode number: %ld\n", myfile_stat.st_ino);

    return 0;
}
