
#include <unistd.h>
pid_t getpgrp(void);
/* getpgid(0) == getpgrp() */
pid_t getpgid(pid_t pid);
int setpgid(pid_t pid, pid_t pgid);

#include <unistd.h>
pid_t setsid(void);
pid_t getsid(pid_t pid);

#include <unistd.h>
/* return foreground process group id of terminal with \fd */
pid_t tcgetpgrp(int fd);
int tcsetpgrp(int fd, pid_t pgrpid);

#include <termios.h>
pid_t tcgetsid(int fd);


