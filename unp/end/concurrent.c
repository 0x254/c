/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: concurrent.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 04 Nov 2014 02:33:29 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		; /* do nothing */
	return;
}

int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	void sig_chld(int), sig_int(int), web_child(int);
	socklen_t clilen, addrlen;
	struct sockaddr *cliaddr;

	if (argc == 2)
	    listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else
		err_quit("Usage: con [<host>] <port#>");

	cliaddr = (struct sockaddr *)Malloc(addrlen);

	Signal(SIGCHLD, sig_chld);
	Signal(SIGINT, sig_int);

	for ( ; ; )
	{
		clilen = addrlen;
		if ((connfd = accept(listenfd, cliaddr, &clilen)) < 0)
		{
			if (errno = EINTR)
				continue; /* back to for */
			else
				err_sys("accept error");
		}

		if ((childpid = Fork()) == 0)
		{
			Close(listenfd); /* son close listen */
			web_child(connfd);
			exit(0); /* and son close connfd */
		}
		Close(connfd); /* parent close connfd */
	}
}
