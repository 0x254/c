/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: mainserver.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月07日 星期二 15时26分13秒
* Description: 
************************************************************************/
#include "all.h"

#define SERV_FIFO "/tmp/fifo.serv"

int main(int argc, char **argv)
{
	int readfifo, writefifo, dummyfd, fd;
	char *ptr, buff[MAXLINE], fifoname[MAXLINE];
	pid_t pid;
	ssize_t n;

	if ((mkfifo(SERV_FIFO, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("can not create %s", SERV_FIFO);

	readfifo = Open(SERV_FIFO, O_RDONLY, 0);
	dummyfd = Open(SERV_FIFO, O_WRONLY, 0);   /* never use */

    /* open server fifo to read */
	while ((n = Readline(readfifo, buff, MAXLINE)) > 0)
	{
		if (buff[n-1] == '\n')
			n--;
		buff[n] = '\0';

        if ((ptr = strchr(buff, ' ')) == NULL)
    	{
            err_msg("bogus request: %s", buff);   /* id' 'file */
    		continue;   /* return to while */
    	}
    	*ptr++ = 0;   /* null terminate pid, ptr = file, buff = pid */
    	pid = atol(buff);
    	snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
    
    	if ((writefifo = open(fifoname, O_WRONLY, 0)) < 0)   /* open client fifo */
    	{
	    	err_msg("can not open: %s", fifoname);
    		continue;
    	}

    	if ((fd = open(ptr, O_RDONLY, 0)) < 0)   /* open file */
    	{
    		/*error must tell client */
    		snprintf(buff + n, sizeof(buff) - n, ": can not open, %s\n", strerror(errno));
    		n  = strlen(ptr);
    		Write(writefifo, ptr, n);
    		Close(writefifo);
    	}
    	else
    	{
    		/* open succeeded: copy file to client fifo */
    		while ((n = Read(fd, buff, MAXLINE)) > 0)
    			Write(writefifo, buff, n);
    		Close(fd);
    		Close(writefifo);
    	}
	}
	exit(0);
}
