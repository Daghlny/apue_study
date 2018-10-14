
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int fd = open(argv[1], O_RDWR);
    void *addr = mmap(0, 10, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    char *str_addr = (char*)addr;
    if (addr == NULL) {
        printf("mmap failed\n");
        return -1;
    }
    printf("addr: %p\n", addr);
    printf("content: ");
    for (int i = 0; i < 10; ++i)
        printf("%c", str_addr[i]);
    printf("\n");

    int cmd = 0;
    char iobuff[24];

    while (true) {
        scanf("%d", &cmd);
        if (cmd == -1)
            break;
        else if (cmd == 0) {
            printf("content: ");
            for (int i = 0; i < 10; ++i)
                printf("%c", str_addr[i]);
            printf("\n");
        } else if (cmd == 1) {
            memset(iobuff, 0, sizeof(iobuff));
            scanf("%s", iobuff);
            memcpy(addr, iobuff, strlen(iobuff));
        }
    }


    return 0;
}
