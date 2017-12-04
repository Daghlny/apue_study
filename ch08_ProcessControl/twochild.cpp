
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {

    pid_t pid = 0;
    
    if ( (pid = fork()) == 0 ) {
        if ( (pid = fork()) == 0 ) {
            sleep(2);
            printf("My parent pid is %ld\n", getppid());
            exit(0);
        } else {
            exit(3);
        }
    } else {
        int status;
        if ( pid != wait(&status) ) {
            printf("wait error\n");
            exit(0);
        } else {
            printf("catch child 1\n");
            exit(0);
        }
    }

    return 0;
}
