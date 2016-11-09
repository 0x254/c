/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: udpservselect01.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年09月19日 星期五 13时46分48秒
* Description: 
************************************************************************/
#include "all.h"

int main(int argc, char **agrv)
{
	int listenfd, connfd, udpfd, nready, maxfdp1;
	char mesg[MAXLINE];
	pid_t childpid;
	fd_set rset;
	ssize_t n;
	socklen_t len;
    struct sockaddr_in cliaddr, servaddr;
	const int on = 1;

	void sigchld_waitpid(int);

    /* create TCP socket */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

    /* create UDP socket */
	udpfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(udpfd, (SA *)&servaddr, sizeof(servaddr));

	Signal(SIGCHLD, sigchld_waitpid);

	FD_ZERO(&rset);
	maxfdp1 = max(listenfd, udpfd) + 1;
	for ( ; ; )
	{
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);
		if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) 
		{
			if (errno == EINTR)
				continue;   /* back to fork() */
		    else
				err_sys("select error");
		}
		if (FD_ISSET(listenfd, &rset))
		{
			len = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *)&cliaddr, &len);

			if ((childpid = Fork()) == 0)   /* child process */
			{
				Close(listenfd);
				str_echo(connfd);
				exit(0);
			}
			Close(connfd);   /* parent closes connected socket */
		}
		if (FD_ISSET(udpfd, &rset))
		{
			len = sizeof(cliaddr);
			n = Recvfrom(udpfd, mesg, MAXLINE, 0, (SA *)&cliaddr, &len);

			Sendto(udpfd, mesg, n, 0, (SA *)&cliaddr, len);
		}
	}
}
