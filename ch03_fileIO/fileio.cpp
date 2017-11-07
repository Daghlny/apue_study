
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

void sys_exit(const char *err_msg) {
    cout << err_msg << endl;
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 2) 
        return -1;
    
    char str1[] = "Harry Potter\n";
    //int ifd = open(argv[1], O_RDWR|O_CREAT);
    //int stdin_fd = open(STDOUT_FILENO, argv[1], O_WRONLY);

    if (write(STDOUT_FILENO, str1, strlen(str1)) == -1)
        sys_exit("write error");

    //cout << "input fd: " << ifd << endl;

    return 0;
}
