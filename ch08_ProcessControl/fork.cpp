
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

int global_val = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var = 0;
    pid_t pid;

    if (write(STDOUT_FILENO, buf, strlen(buf)) != sizeof(buf)-1 ) {
        printf("write error\n");
        exit(0);
    }

    printf("before fork\n");

    if ( (pid = vfork()) < 0 ) {
        printf("fork error\n");
        exit(0);
    } else if (pid == 0) {
        global_val++;
        var++;
        exit(0);
    } else {
        sleep(2);
    }

    printf("pid=%ld, glob=%d, var=%d\n", (long)getpid(), global_val, var);

    return 0;
}
