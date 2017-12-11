
#include <signal.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

void sig_usr(int signo)
{
    if (signo == SIGINT)
        printf("received SIGINT\n");
    else 
        printf("unknown SIG\n");

}

int main(void)
{
    if (signal(SIGINT, sig_usr) == SIG_ERR) {
        printf("sigint error\n");
        exit(0);
    }
    
    pause();

    return 0;
}
