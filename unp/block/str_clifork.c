/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* File Name: str_clifork.c
* Version:                                                           *
* Writen by canux canuxcheng@gmail.com                               *
* Created Time: Fri 24 Oct 2014 02:54:41 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void str_cli(FILE *fp, int sockfd)
{
	pid_t pid;
	char sendline[MAXLINE], recvline[MAXLINE];

	if ((pid = Fork()) == 0)
	{
		while (Readline(sockfd, recvline, MAXLINE) > 0)
			Fputs(recvline, stdout);

		kill(getppid(), SIGTERM); /* in case parent still running */
		exit(0);
	}

	while (Fgets(sendline, MAXLINE, fp) != NULL)
		Writen(sockfd, sendline, strlen(sendline));

	Shutdown(sockfd, SHUT_WR); /* eof on stdin, send fin */
	pause();
	return ;
}
