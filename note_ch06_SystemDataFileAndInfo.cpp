
#include <pwd.h>
struct passwd *getpwuid(uid_t uid);
struct passwd *getpwnam(const char *name);


struct passwd *getpwent(void);
void           setpwent(void);
void           endpwent(void);


// for shadow passwords file
#include <shadow.h>
struct spwd *getspnam(const char *name);
struct spwd *getspent(void);
void         setspent(void);
void         endspent(void);

// for group file
#include <grp.h>
struct group *getgrgid(gid_t gid);
struct group *getgrnam(const char *name);
struct group *getgrent(void);
void          setgrent(void);
void          endgrent(void);

#include <unistd.h>
// return the supplimentary groups' number
// \gidsetsize is the maximum size of \grouplist
int getgroups(int gidsetsize, gid_t grouplist[]);

#include <grp.h> /* On Linux */
#include <unistd.h> /* On FreeBSD, Mac OS, Solaris */
int setgroups(int ngroups, const gid_t grouplist[]);
int initgroups(const char *username, gid_t basegid);

#include <sys/utsname.h>
// \return > 0 for success, -1 for error
int uname(struct utsname *name);


#include <time.h>
time_t time(time_t *calptr);

/* \clockid_t:
 * CLOCK_REALTIME
 * CLOCK_MONOTONIC
 * CLOCK_PROCESS_CPUTIME_ID
 * CLOCK_THREAD_CPUTIME_ID
 */
int clock_gettime(clockid_t clock_id, struct timespec *tsp);
int clock_getres(clockid_t clock_id, struct timespec *tsp); // only for percision
int clock_settime(clockid_t clock_id, const struct timespec *tsp);
int gettimeofday(struct timeval *restrict tp, void *restrict tzp);













