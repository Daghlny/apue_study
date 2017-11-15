
#include <stdio.h>
#include <wchar.h>

/*
 * \mode > 0, orientate to wchar
 * \mode < 0, orientate to char
 * \mode = 0, return original orientation
 */
int fwide(FILE* fp, int mode);

/*
 * \mode can be 
 *  _IOFBF  _IOLBF  _IONBF
 */
void setbuf(FILE *restrict fp, char *restrict buf);
int  setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);

/*
 * \type can be
 * r/rb == O_RDONLY
 * w/wb == O_WRONLY | O_CREAT | O_TRUNC
 * a/ab == O_WRONLY | O_CREAT | O_APPEND
 * r+/r+b/rb+ == O_RDWR
 * w+/w+b/wb+ == O_RDWR | O_CREAT | O_TRUNC
 * a+/a+b/ab+ == O_RDWR | O_CREAT | O_APPEND
 */
FILE *fopen(const char *restrict pathname, const char *restrict type);
FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
FILE *fdopen(int fd, const char *type);
int   fclose(FILE *fp);

int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);

// return 0 for false or true
int ferror(FILE *fp);
int feof(FILE *fp);

void clearerr(FILE *fp);

int ungetc(int c, FILE *fp);

int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);

// \gets remove \n and  \fgets remain \n
char *fgets(char *restrict buf, int n, FILE *restrict fp);
char *gets(char *buf);

int fputs (const char *restrict str, FILE *restrict fp);
int puts  (const char *str);

/*
 * binary I/O
 * return the number of objects read or written
 */
size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);

long  ftell  (FILE *fp);
int   fseek  (FILE *fp, long offset, int whence);
void  rewind (FILE *fp);
off_t ftello (FILE *fp);
int   fseeko (FILE *fp, off_t offset, int whence);
int   fgetpos(FILE *fp, fpos_t *restrict pos);
int   fsetpos(FILE *fp, const fpos_t *pos);

int printf(const char *restrict format, ...);
int fprintf(FILE *restrict fp, const char *restrict format, ...);
int dprintf(int fd, const char *restrict format, ...);
int sprintf(char *restrict buf, const char *restrict format, ...);
int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);

int scanf(const char *restrict format, ...);
int fscanf(FILE *restrict fp, const char *restrict format, ...);
int sscanf(const char *restrict buf, const char *restrict format, ...);


// return corresponding fd
int fileno(FILE *fp);

/* 
 * \tmpnam first create a file name, then create the file, so it's not recommanded
 */
char *tmpnam(char *ptr);
FILE *tmpfile(void);

/* 
 * these both functions are provided by XSI extend
 */
#include <stdlib.h>
char *mkdtemp(char *template);
int   mkstemp(char *template);

#include <stdio.h>
FILE *fmemopen(void *restrict buf, size_t size, const char *restrict type);










