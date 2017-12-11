
#include <signal.h>
/*
 * \func: SIG_IGN, SIG_DFL
 * \return previous singal handler for success or SIG_ERR for error
 */
void (*signal(int signo, void (*func)(int)))(int);


