
#ifndef FUNC_H
#define FUNC_H

#include <cstdio>
#include <cstdlib>

void sys_exit(const char *str) {
    printf("%s\n", str);
    exit(0);
}

int wrapper(int rtvalue, const char *str = "") {
    if (rtvalue < 0)
    {
        printf("%s\n", str);
        exit(0);
    }
    else 
        return rtvalue;
}

#endif

