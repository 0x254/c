/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: mainfifo.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月06日 星期一 13时29分35秒
* Description: 
************************************************************************/
#include "all.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void client(int, int);
void server(int, int);

int main(int agrc, char **agrv)
{
	int readfd, writefd;
	pid_t childpid;

	if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("can not create %s", FIFO1);
	if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST))
	{
		Unlink(FIFO1);
	    err_sys("can not create %s", FIFO2);
	}

	if ((childpid = Fork()) == 0)
	{
		readfd = Open(FIFO1, O_RDONLY, 0);
		writefd = Open(FIFO2, O_WRONLY, 0);

		server(readfd, writefd);
		exit(0);
	}

	writefd = Open(FIFO1, O_WRONLY, 0);
	readfd = Open(FIFO2, O_RDONLY, 0);

	client(readfd, writefd);

	Waitpid(childpid, NULL, 0);

	Close(readfd);
	Close(writefd);

	Unlink(FIFO1);
	Unlink(FIFO2);
	exit(0);
}
