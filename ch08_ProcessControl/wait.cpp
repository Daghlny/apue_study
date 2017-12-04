
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void pr_exit(int status);

int main(void) {

    int status = 0;
    pid_t pid = 0;

    if ( (pid = fork()) == 0 ) {
        exit(13);
    }

    if ( pid != wait(&status) ) {
        printf("error1\n");
        return 0;
    } else {
        pr_exit(status);
    }

    if ( (pid = fork()) ==  0) {
        abort();
    }
    if ( pid != wait(&status) ) {
        printf("error1\n");
        return 0;
    } else {
        pr_exit(status);
    }

    if ( (pid = fork()) ==  0) {
        status /= 0;
    }
    if ( pid != wait(&status) ) {
        printf("error1\n");
        return 0;
    } else {
        pr_exit(status);
    }

    return 0;
}
