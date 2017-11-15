
#include <cstdio>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>

int 
main(void)
{
    const char *file_name = "lyn_tmp_24.txt";
    
    FILE *fp = tmpfile();
    int fd = fileno(fp);

    struct stat statbuf;
    char str[256], name[256];

    snprintf(str, 255, "/proc/%d/fd/%d", getpid(), fd);
    memset(name, 0, sizeof(name));
    readlink(str, name, 255);

    printf("FILE Name: %s\n", name);

    return 0;
}
