
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

int mysystem(const char *cmdstring)
{
    pid_t pid;
    int status;

    if (cmdstring == NULL) return -1;

    printf("##Main Process: %d ", getpid());

    if ((pid = fork()) < 0){
        printf("fork error\n");
        exit(-1);
    }
    if (pid > 0) printf("Child Process: %d\n", pid);
    if (pid == 0) {
        printf("DEBUG__ %s\n", cmdstring);
        execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
        printf("exit not right\n");
        //_exit(127);
    } else {
        while(waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
        printf("exit waitpid()\n");
    }

    return status;
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        printf("######### %d:%s\n", i, argv[i]);
        int status = mysystem(argv[i]);
        printf("Return Value: %d\n", status);
    }

    return 0;
}


