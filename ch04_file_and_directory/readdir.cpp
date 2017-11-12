
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include "func.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        sys_exit("arguments error");

    for (int i = 1; i < argc; ++i){
        DIR * dp = opendir(argv[i]);
        struct dirent *dr_ptr = NULL;
        while( (dr_ptr = readdir(dp)) != NULL ) {
            printf("%ld %s\n", dr_ptr->d_ino, dr_ptr->d_name);
        }
    }

    return 0;
}
