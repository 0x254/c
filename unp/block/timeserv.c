/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* File Name: timeserv.c
* Version:                                                           *
* Writen by canux canuxcheng@gmail.com                               *
* Created Time: Fri 24 Oct 2014 11:03:17 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; )
	{
		connfd = Accept(listenfd, (SA *)NULL, NULL);

	    ticks = time(NULL);
	    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
   	    Write(connfd, buff, strlen(buff));

	    Close(connfd);
	}
}
