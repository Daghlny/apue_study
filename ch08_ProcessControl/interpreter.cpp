
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid = -1;
    printf("Main Process: %d\n", getpid());
    //if ((pid = fork()<0))  ==  pid = false = 0
    if ((pid = fork())<0) {
        printf("fork error\n");
        exit(0);
    } else if (pid == 0) {
        printf("Child Process: %d\n", getpid());
        if (execl("/home/lyn/Codes/apue_study/ch08_ProcessControl/testinterp", /*"testinterp", "myarg1", "My Arg2",*/ (char*)0) < 0) {
            printf("exec error\n");
            exit(0);
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error\n");
        exit(0);
    }

    return 0;
}
