
#include <sys/stat.h>

/*
 * \lstat is for symbolic link
 */
int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);

struct stat {
    mode_t                 st_mode;
    ino_t                  st_ino;
    dev_t                  st_dev;
    dev_t                  st_rdev;
    nlink_t                st_nlink;
    uid_t                  st_uid;
    gid_t                  st_gid;
    off_t                  st_size;
    struct timespec        st_atime;
    struct timespec        st_mtime;
    struct timespec        st_ctime;
    blksize_t              st_blksize;
    blkcnt_t               st_blocks;
};

struct timespec {
    time_t tv_sec;
    long   tv_nsec;
};


#include <unistd.h>

/* 
 * return 0 for ok, -1 for error
 *
 * \mode can be F_OK, R_OK, W_OK, X_OK
 */
int access(const char *pathname, int mode);
int faccessat(int fd, const char *pathname, int mode, int flag);


#include <sys/stat.h>
/*
 * S_IRUSR S_IWUSR S_IXUSR
 * S_IRGRP S_IWGRP S_IXGRP
 * S_IROTH S_IW_OTH S_IXOTH
 *
 * used additionly in \chmod function
 * S_ISUID S_ISGID
 * S_ISVTX
 * S_IRWXU S_IRWXG S_IRWXO
 */
mode_t umask(mode_t cmask);

/*
 * \flag can be AT_FDCWD, AT_SYMLINK_NOFOLLOW
 */
int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, const char *pathname, mode_t mode, int flag);

#include <unistd.h>

int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag);
int lchown(const char *pathname, uid_t owner, gid_t group);

int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length);

int link(const char *existingpath, const char *newpath);
int linkat(int efd, const char *existingpath, int nfd, const char *newpath, int flag);

int unlink(const char *pathname);
int unlinkat(int fd, const char *pathname, int flag);

#include <stdio.h>
int remove(const char *pathname);
int rename(const char *oldname, const char *newname);
int renameat(int oldfd, const char *oldname, int newfd, const char *newname);

















