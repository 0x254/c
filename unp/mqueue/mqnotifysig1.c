/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqnotifysig1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 09 Nov 2014 10:08:32 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

mqd_t mqd;
void *buff;
struct mq_attr attr;
struct sigevent sigev;

static void sig_usr1(int signo)
{
	ssize_t n;
	Mq_notify(mqd, &sigev);
	n = Mq_receive(mqd, buff, attr.mq_msgsize, NULL);
	printf("SIGUSR1 received, read %ld bytes\n", (long)n);
	return;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("Usage: nts1 <name>");

	mqd = Mq_open(argv[1], O_RDONLY);
	Mq_getattr(mqd, &attr);
	buff = (void *)Malloc(attr.mq_msgsize);

	Signal(SIGUSR1, sig_usr1);
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	Mq_notify(mqd, &sigev);

	for ( ; ; )
		pause();
	exit(0);
}
