/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: pipe.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月05日 星期日 13时54分31秒
* Description: 
************************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int pipe[2], n, len;
    char buff[MAXLINE];

	Pipe(pipe);

	Fgets(buff, MAXLINE, stdin);
	len = strlen(buff);
	if (buff[len-1] == '\n')
		len--;

	Write(pipe[1], buff, len);
	n = Read(pipe[0], buff, MAXLINE);
	Write(STDOUT_FILENO, buff, n);
	exit(0);
}
