/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: clientmain.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月06日 星期一 15时00分54秒
* Description: 
************************************************************************/
#include "all.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

void client(int, int);

int main(int argc, char **argv)
{
	int readfd, writefd;

	writefd = Open(FIFO1, O_WRONLY);
	readfd = Open(FIFO2, O_RDONLY);

	client(readfd, writefd);

	Close(readfd);
	Close(writefd);

	Unlink(FIFO1);
	Unlink(FIFO2);
	exit(0);
}
