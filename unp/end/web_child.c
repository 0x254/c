/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: web_child.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 05 Nov 2014 12:49:26 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define MAXN 16384

void web_child(int sockfd)
{
	int ntowrite;
	ssize_t nread;
	char line[MAXLINE], result[MAXN];

	for ( ; ; )
	{
		if ((nread = Readline(sockfd, line, MAXLINE)) == 0)
			return; /* connection closed by other end */

		ntowrite = atol(line);
		if ((ntowrite <= 0) || (ntowrite > MAXN))
			err_quit("client request for %d bytes", ntowrite);

		Writen(sockfd, result, ntowrite);
	}
}
