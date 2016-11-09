/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: tcpcli03.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Thu 04 Sep 2014 10:24:09 PM CST
* Description: 
************************************************************************/
#include "all.h"

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp1, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0;
	FD_ZERO(&rset);
	for ( ; ; )
	{
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(fileno(fp), &rset))
		{
		    if ((n = Read(fileno(fp), buf, MAXLINE)) == 0)   /* fp==stdin EOF */
			{
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			Writen(sockfd, buf, n);
		}

		if (FD_ISSET(sockfd, &rset))
		{
			if ((n = Read(sockfd, buf, MAXLINE)) == 0)
			{
                if (stdineof == 1)
					return;
				else
					err_quit("str_cli: server terminated prematurely");
			}
			Write(fileno(fp), buf, n);
		}
	}
}
