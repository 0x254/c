/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: dg_echo.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年09月16日 星期二 01时20分46秒
* Description: 
************************************************************************/
#include "all.h"

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	for ( ; ; )
	{
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}
