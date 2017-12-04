
#include <unistd.h>
pid_t getpid(void);
pid_t getppid(void);   
uid_t getuid(void);     // real user id
uid_t geteuid(void);    // effective user id
gid_t getgid(void);     // real group id
gid_t getegid(void);    // effective group id

#include <unistd.h>
/*
 * \return 0 in child process
 * \return child process's pid in father process
 * \return -1 if error
 */
pid_t fork(void);

#include <sys/wait.h>
pid_t wait(int *statloc);
/*
 * WIFEXITED(status) --> WEXITSTATUS(status)
 * WIFSIGNALED(status) --> WTERMSIG(status) / WCOREDUMP(status)
 * WIFSTOPPED(status) --> WSTOPSIG(status)
 * WIFCONTINUED(status)
 */
pid_t waitpid(pid_t pid, int *statloc, int options);

/*
 * \idtype  = P_PID / P_PGID / P_ALL
 * \options = WCONTINUED | WEXITED | WNOHANG | WNOWAIT | WSTOPPED
 */
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);

#include <unistd.h>
int execl  (const char *pathname, const char *arg0, .../* (char*)0 */);
int execv  (const char *pathname, char *const argv[]);
int execle (const char *pathname, const char *arg0, ... /* (char*)0 *//*char *const envp[]*/ );
int execve (const char *pathname, char *const argv[], char *const envp[]);
int execlp (const char *filename, const char *arg0, .../* (char*)0 */);
int execvp (const char *filename, char *const argv[]);
int fexecve(int fd, char *const argv[], char *const envp[]);

#include <unistd.h>
int setuid(uid_t uid);
int setgid(gid_t gid);
int setreuid(uid_t ruid, uid_t euid);
int setregid(gid_t rgid, gid_t egid);
int seteuid(uid_t uid);
int setegid(gid_t gid);

#include <stdlib.h>
int system(const char *cmdstring);

#include <unistd.h>
char *getlogin(void);

#include <unistd.h>
int nice(int incremental);

#include <sys/resource.h>
int getpriority(int which, id_t who);
int setpriority(int which, id_t who, int value);













