/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: create.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 07 Jan 2015 02:01:07 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void myprintf(char *s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid=%u tid=%u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void *thrfunc(void *s)
{
	myprintf("new thread:");
	return (void *)0;
}

int main(int argc, char **argv)
{
	pthread_t thread;
	int err;
	if (pthread_create(&thread, NULL, thrfunc, NULL) != 0)
		err_quit("pthread_create error");
	myprintf("main thread:");
	sleep(3);
	exit(0);
}
