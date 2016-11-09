/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: thread.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 04 Nov 2014 02:33:40 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void *doit(void *arg)
{
	void web_child(int);

	Pthread_detach(pthread_self());
	web_child((int) arg);
	Close((int) arg);
	return (NULL);
}

int main(int argc, char **argv)
{
	int listenfd, connfd;
	void sig_int(int);
	void *doit(void *);
	pthread_t tid;
	socklen_t clilen, addrlen;
	struct sockaddr *cliaddr;

	if (argc == 2)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else
		err_quit("Usage: thread [<host>] <port#>");
	cliaddr = (struct sockaddr *)Malloc(addrlen);

	Signal(SIGINT, sig_int);

	for ( ; ; )
	{
		clilen = addrlen;
		connfd = Accept(listenfd, cliaddr, &clilen);
		Pthread_create(&tid, NULL, &doit, (void *)connfd);
	}
}
