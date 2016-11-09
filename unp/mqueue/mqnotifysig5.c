/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqnotifysig5.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 10 Nov 2014 12:44:50 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int pipefd[2];

static void sig_usr1(int signo)
{
	Write(pipefd[1], "", 1); // one byte of 0
	return;
}

int main(int argc, char **argv)
{
	int nfds;
	char c;
	fd_set rset;
	mqd_t mqd;
	void *buff;
	ssize_t n;
	struct mq_attr attr;
	struct sigevent sigev;

	if (argc != 2)
		err_quit("Usage: nfs5 <name>");

	mqd = Mq_open(argv[1], O_RDONLY | O_NONBLOCK);
	Mq_getattr(mqd, &attr);
	buff = (void *)Malloc(attr.mq_msgsize);

	Pipe(pipefd);

	Signal(SIGUSR1, sig_usr1);
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	Mq_notify(mqd, &sigev);

	FD_ZERO(&rset);
	for ( ; ; )
	{
		FD_SET(pipefd[0], &rset);
		nfds = Select(max(pipefd[0], pipefd[1]) + 1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(pipefd[0], &rset))
		{
			Read(pipefd[0], &c, 1);
			Mq_notify(mqd, &sigev);
			while ((n = mq_receive(mqd, buff, attr.mq_msgsize, NULL)) >= 0)
				printf("read %ld bytes\n", (long)n);
		    if (errno != EAGAIN)
			    err_sys("mq_receive error");
		}
	}
	exit(0);
}
