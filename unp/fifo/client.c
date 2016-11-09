/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: clientpipe.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月04日 星期六 12时33分54秒
* Description: 
************************************************************************/
#include "all.h"

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	/* read pathname */
	Fgets(buff, MAXLINE, stdin);
	len = strlen(buff);
	if (buff[len - 1] == '\n');
	    len--;   /* delete newline from fgets() */

	/* write pathname to IPC channel */
	Write(writefd, buff, len);

	/* read from IPC, write to standard output */
	while ((n = Read(readfd, buff, MAXLINE)) > 0)
		write(STDOUT_FILENO, buff, n);
}
