
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char *beg = environ[0];
    int cnt = 0;
    while( beg != NULL )
    {
        printf("%s\n", beg);
        beg = environ[++cnt];
    }

    return 0;
}
