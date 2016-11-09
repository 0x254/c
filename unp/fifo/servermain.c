/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: servermain.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月06日 星期一 14时37分54秒
* Description: 
************************************************************************/
#include "all.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void server(int, int);

int main(int argc, char **argv)
{
	int readfd, writefd;

	if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("cat not create %s", FIFO1);
	if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST))
	{
		Unlink(FIFO1);
		err_sys("can not create %s", FIFO2);
	}

	readfd = Open(FIFO1, O_RDONLY, 0);
	writefd = Open(FIFO2, O_WRONLY, 0);

	server(readfd, writefd);
	exit(0);
}
