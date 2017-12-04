
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(0);
    } else if (pid == 0) {
        if (execle("./print.out", "hello", "world", "with", "APUE", (char*)0, environ) < 0) {
            printf("exec error\n");
            exit(0);
        }
        printf("child process exit\n");
        exit(0);
    }

    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error\n");
        exit(0);
    }

    return 0;
}
