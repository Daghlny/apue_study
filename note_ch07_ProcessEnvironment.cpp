
#include <stdlib.h>
void exit(int status);
void _Exit(int status);
#include <unistd.h>
void _exit(int status);

#include <stdlib.h>
int atexit(void (*func)(void));

#include <stdlib.h>
int putenv(char *str);
int setenv(const char *name, const char *value, int rewrite);
int unsetenv(const char *name);

#include <setjmp.h>
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);


#include <sys/resource.h>
/*
 * struct rlimit {
 *     rlim_t rlim_cur;
 *     rlim_t rlim_max;
 * };
 */
int getrlimit(int resource, struct rlimit *rlptr);
int setrlimit(int resource, const struct rlimit *rlptr);



