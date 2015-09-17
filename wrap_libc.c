/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: wrap_stdio.h
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年08月31日 星期日 19时25分14秒
* Description: 
************************************************************************/

#include "all.h"

FILE *Fopen(const char *filename, const char *mode)
{
	FILE *ptr;
	if ((ptr = fopen(filename, mode)) == NULL)
		err_msg("fopen error");
	return (ptr);
}

FILE *Fdopen(int fd, const char *mode)
{
	FILE *ptr;
	if ((ptr = fdopen(fd, mode)) == NULL)
		err_msg("fdopen error");
}

FILE *Freopen(const char *path, const char *mode, FILE *stream)
{
	FILE *ptr;
	if ((ptr = freopen(path, mode, stream)) == NULL)
		err_msg("freopen error");
}

size_t Fread(void *ptr, size_t size, size_t nitems, FILE *stream)
{
	size_t n;
	if ((n = fread(ptr, size, nitems, stream)) == 0)
		err_msg("fread error");
	return (n);
}

void Fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream)
{
	if (fwrite(ptr, size, nitems, stream) != nitems)
		err_msg("fwrite error");
}

void Fclose(FILE *fp)
{
	if (fclose(fp) < EOF)
		err_msg("fclose error");
}



char *Fgets(char *ptr, int n, FILE *stream)
{
    char *rptr;
    
    if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
        err_msg("fgets error");
    
    return(rptr);  
} 

void Fputs(const char *ptr, FILE *stream)
{
    if (fputs(ptr, stream) == EOF)
        err_msg("fputs error");
}



void *Malloc(size_t size)
{
	void *ptr;

	if ((ptr = malloc(size)) == NULL)
		err_msg("malloc error");
	return (ptr);
}

void *Calloc(size_t nmem, size_t size)
{
	void *ptr;

	if ((ptr = calloc(nmem, size)) == NULL)
		err_sys("calloc error");
	return (ptr);
}

int Getopt(int argc, char *const argv[], const char *optstring)
{
	int opt;

	if ((opt = getopt(argc, argv, optstring)) == '?')
		exit(1); // getopt has already written to stderr
	return (opt);
}

long Sysconf(int name)
{
	long val;

	errno = 0; // in case sysconf does not change this
	if ((val = sysconf(name)) == -1) {
		if (errno != 0)
			err_sys("sysconf error");
		else
			err_sys("sysconf: %d not defined", name);
	}
	return (val);
}
