
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#define BUFFSIZE 1000;

using namespace std;


int read_fifo(char *filepath) {
    if (filepath == nullptr)
        return -1;

    if (mkfifo(filepath, 0777) < 0)
        return -1;

    int readfd;
    if ( (readfd = open(filepath, O_RDONLY)) < 0) 
        return -1;

    cout << "Open FIFOfile Success" << endl;
    char buffer[BUFFSIZE];

    int bytes_read = read(readfd, buffer, BUFFSIZE);
    while ()


}

int main(int argc, char **argv) {
    if (argc < 2) 
        exit(-1);

    
}
