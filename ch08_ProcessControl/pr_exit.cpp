
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void pr_exit(int status) {
    if (WIFEXITED(status)) 
        printf("normal exit with exitstatus: %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number=%d%s\n", WTERMSIG(status), 
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated)" : "");
#else
    "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));
}
