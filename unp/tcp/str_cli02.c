/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: str_cli2.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Thu 04 Sep 2014 11:24:53 PM CST
* Description: 
************************************************************************/
#include "all.h"

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp1;
	fd_set rset;
	char sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);
	for ( ; ; )
	{
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(fileno(fp), &rset))
		{
			if (Fgets(sendline, MAXLINE, fp) == NULL)   /* stdin==fp EOF */
				return;
			Writen(sockfd, sendline, strlen(sendline));
		}

		if (FD_ISSET(sockfd, &rset))
		{
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
		    Fputs(recvline, stdout);
		}
	}
}
