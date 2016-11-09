/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: iterate.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 04 Nov 2014 12:18:06 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr *cliaddr;
	socklen_t addrlen, clilen;

	if (argc == 2)
	    listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else 
		err_quit("Usage: ite [<host>] <port#>");

	cliaddr = (struct sockaddr *)Malloc(addrlen);

	for ( ; ; )
	{
		clilen = addrlen;
		connfd = Accept(listenfd, cliaddr, &clilen);

		web_child(connfd);

		Close(connfd);
	}
}
