
#include <cstdio>
#include <unistd.h>

int main(void)
{
    char *login_name = getlogin();
    printf("%s\n", login_name);

    return 0;
}
