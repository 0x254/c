/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqnotifysig4.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 10 Nov 2014 12:33:00 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int signo;
	mqd_t mqd;
	void *buff;
	ssize_t n;
	sigset_t newmask;
	struct mq_attr attr;
	struct sigevent sigev;

	if (argc != 2)
		err_quit("Usage: mqnotifysig4 <name>");

	mqd = Mq_open(argv[1], O_RDONLY | O_NONBLOCK);
	Mq_getattr(mqd, &attr);
	buff = (void *)Malloc(attr.mq_msgsize);

	Sigemptyset(&newmask);
	Sigaddset(&newmask, SIGUSR1);
	Sigprocmask(SIG_BLOCK, &newmask, NULL);

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	Mq_notify(mqd, &sigev);

	for ( ; ; )
	{
		Sigwait(&newmask, &signo);
		if (signo == SIGUSR1)
		{
			Mq_notify(mqd, &sigev);
			while ((n = mq_receive(mqd, buff, attr.mq_msgsize, NULL)) >= 0)
				printf("read %ld bytes\n", (long)n);
			if (errno != EAGAIN)
				err_sys("mq_receive error");
		}
	}
	exit(0);
}
