
#include <fcntl.h>

STDIO_FILENO
STDOUT_FILENO
STDERR_FILENO

/* \return is between range [0, OPEN_MAX-1]
 *
 * \oflag is combined by OR :
 * O_RDONLY    O_WRONLY  O_RDWR
 * O_EXEC  O_APPEND
 * O_CREAT
 * O_DIRECTORY
 * O_SYNC O_TRUNC
 *
 * \openat is only useful in relative directory
 */
int open(const char *path, int oflag, .../*mode_t mode */);
int openat(int fd, const char *path, int oflag, .../*mode_t mode*/);


/* \creat equals to this format: open(path, O_WRONLY|O_CREAT|O_TRUNC, mode);
 * \creat only have write permission, so you can use open(path, O_RDWR|O_CREAT|O_TRUNC, mode)
 * \return -1 if have error
 */
int creat(const char *path, mode_t mode);



#include <unistd.h>

/* os will close all files opend when a process exit
 * \return 0 for success, -1 for failure
 */
int close(int fd);


/* After \open, offset is 0 defaultly
 * \whence can be SEEK_SET , SEEK_CUR, SEEK_END
 * SEEK_SET is set offset relative to file's begin position, SEEK_CUR is to current position, SEEK_END is to file's end
 * \return new offset if worked, -1 if error
 * if \fd is a pipe, FIFO or socket, \lseek will return -1, and set \errno to ESPIPE
 * offset of a file could bigger than file's length, it means there is a hole in file.
 */
off_t lseek(int fd, off_t offset, int whence);

/* \return the read bytes number;if touched the end of file, return 0;if error, return -1;
 */
ssize_t read(int fd, void *buf, size_t nbytes);

/* parameters and return values same as \read
 */
ssize_t write(int fd, const void *buf, size_t nbytes);

int dup(int fd);
int dup2(int fd, int fd2);

/* os has delayed write as default */
void sync(void);

/* \fdatasync only effect file's data part, but \fsync will also synchronize file's properties
 */
int fsync(int fd);
int fdatasync(int fd);



#include <fcntl.h>

/* 1. copy a fd already exist         F_DUPFD or F_DUPFD_CLOEXEC
 * 2. get or set a fd                 F_GETFD or F_SETFD
 * 3. get or set file's status flag   F_GETFL or F_SETFL
 * 4. get or set async IO ownership   F_GETOWN or F_SETOWN
 * 5. get or set log lock             F_GETLK , F_SETLK or F_SETLKW
 */
int fcntl(int fd, int cmd, .../* int arg */ );















































