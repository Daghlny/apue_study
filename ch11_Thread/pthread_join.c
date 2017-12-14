
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Foo{
    int age;
    char *name;
    size_t namelen;
} Foo;

void *
chtid_func(void *arg)
{
    pthread_t self_tid = pthread_self();
    printf("Child Thread ID: %u\n", self_tid);
    char *fname = (char*)arg;
    size_t fnamelen = strlen(fname);
    Foo *f = (Foo*)malloc(sizeof(Foo));
    f->age = 12;
    f->name = (char*)malloc(sizeof(char)*fnamelen);
    strcpy(f->name, fname);
    f->namelen = fnamelen;

    pthread_exit(f);
}

int 
main(void)
{
    pthread_t tid;
    char *fname = (char*)malloc(sizeof(char)*10);
    const char *str = "yinuo";
    strcpy(fname, str);

    pthread_create(&tid, NULL, chtid_func, fname);
    void *rvalue = NULL;
    pthread_join(tid, &rvalue);
    
    Foo *f = (Foo*)rvalue;

    printf("age: %d\nname: %s\n", f->age, f->name);

    exit(0);

}
