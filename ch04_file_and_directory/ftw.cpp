
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "func.hpp"

typedef long long LL;
/*
 * nums[0]: regular
 * nums[1]: directory
 * nums[2]: character special
 * nums[3]: block special
 * nums[4]: fifo or pipe
 * nums[5]: symbolic link
 * nums[6]: socket
 */
LL nums[7];

int ftw(char *pathname);
int fmode(mode_t mode);

int main(int argc, char **argv)
{
    if (argc != 2)
        sys_exit("arguments error");

    char *root_path = static_cast<char*>(malloc(sizeof(char) * strlen(argv[1]) + 5));
    strcpy(root_path, argv[1]);
    wrapper(ftw(root_path), "ftw error");
    free(root_path);

    printf("regular file: %lld\n", nums[0]);
    printf("directory   : %lld\n", nums[1]);
    
    return 0;
}

/*
 * \brief count total file types' numbers
 * \param pathname is the absolute path of root, format: '/path/to/root/'
 */
int ftw(char *pathname)
{
    //printf("##current filepath: %s\n", pathname);
    struct stat statbuf;
    if (lstat(pathname, &statbuf) < 0) {
        printf("ftw lstat(pathname) error\nfilepath: %s\n", pathname);
        return -1;
    }
    if (S_ISDIR(statbuf.st_mode) == 0)
        return fmode(statbuf.st_mode);

    /* below is for directory */
    fmode(statbuf.st_mode);
    if (pathname[strlen(pathname)-1] != '/') {
        pathname[strlen(pathname)] = '/';
        pathname[strlen(pathname)+1] = 0;
    }

    struct dirent *drtp;
    DIR *dp = opendir(pathname);

    int dlen = strlen(pathname);

    while( (drtp = readdir(dp)) != NULL ) {
        if (strcmp(drtp->d_name, ".") == 0 || strcmp(drtp->d_name, "..") == 0)
            continue;
        if ( drtp->d_name[0] == '.' )
            continue;

        int flen = strlen(drtp->d_name); //this may have error
        flen += dlen+5;

        char *file_path = static_cast<char *>(malloc(sizeof(char) * flen));
        memset(file_path, 0, sizeof(char)*flen);
        strcpy(file_path, pathname);
        strcpy(&file_path[dlen], drtp->d_name);

        ftw(file_path);

        free(file_path);
    }

    return 0;
}

int fmode(mode_t mode) {
    switch(mode & S_IFMT){
        case S_IFREG:
            nums[0]++; break;
        case S_IFDIR:
            nums[1]++; break;
        case S_IFCHR:
            nums[2]++; break;
        case S_IFBLK:
            nums[3]++; break;
        case S_IFIFO:
            nums[4]++; break;
        case S_IFLNK:
            nums[5]++; break;
        case S_IFSOCK:
            nums[6]++; break;
        default:
            return -1;

    }

    return 0;
}

