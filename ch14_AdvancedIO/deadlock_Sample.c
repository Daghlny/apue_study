
#include "../apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int
main(int argc, char **argv)
{
    if (argc < 2) 
        err_sys("argc has error");
    const char *pathname = argv[1];

    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        /** child process **/
        printf("Child Process: %d\n", getpid());
        int fd = open(pathname, O_RDWR | O_CREAT);
        if ((pid = write_lock(fd, 0, SEEK_SET, 1)) != 0 ) {
            err_sys("The first byte is seted by %d", pid);
        }
        sleep(1);
        if ( ! is_write_lockable(fd, 1, SEEK_SET, 1) ) {
            printf("The second byte is occupied\n");
        }        
        /*
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_start = 1;
        lock.l_whence = SEEK_SET;
        lock.l_len = 1;
        lock.l_pid = 1;

        fcntl(fd, F_GETLK, &lock);
        if (lock.l_type == F_UNLCK) {
            printf("the second byte is not used\n");
        } else {
            printf("the second byte is used by %d\n", lock.l_pid);
        }
        */
        
        exit(0);
    } else {
        printf("Parent Process: %d\n", getpid());
        int fd = open(pathname, O_RDWR | O_CREAT);
        if ((pid = write_lock(fd, 1, SEEK_SET, 1)) != 0 ) {
            err_sys("The second byte is seted by %d", pid);
        }
        int exitstat = 0;
        wait(&exitstat);
        //sleep(1);
        /*
        if ((pid = is_write_lockable(fd, 0, SEEK_SET, 1)) != 0) {
            printf("The first byte is occupied by %d\n", pid);
        }
        */
    }

    return 0;
}
