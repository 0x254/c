/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: mainclient.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月07日 星期二 17时35分21秒
* Description: 
************************************************************************/
#include "all.h"
#define SERV_FIFO "/tmp/fifo.serv"

int main(int argc, char **argv)
{
	int readfifo, writefifo;
	size_t len;
	ssize_t n;
	char *ptr, fifoname[MAXLINE], buff[MAXLINE];
	pid_t pid;

	pid = getpid();
	snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
	if ((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST))
	{
		err_sys("cat not create %s", fifoname);
	}

	snprintf(buff, sizeof(buff), "%ld", (long)pid);
	len = strlen(buff);
	ptr = buff + len;   /* ptr = file */

	Fgets(ptr, MAXLINE - len, stdin);   /* get file name */
	len = strlen(buff);
	
	writefifo = Open(SERV_FIFO, O_WRONLY, 0);   /* open server fifo to write pid and file */
	Write(writefifo, buff, len);

	/* open client fifo to read file, after that close fd and delete fifo */
	readfifo = Open(fifoname, O_RDONLY, 0);   
	while ((n = Read(readfifo, buff, MAXLINE)) > 0)
		write(STDOUT_FILENO, buff, n);
	Close(readfifo);
	Unlink(fifoname);

	exit(0);
}
