/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: dg_cli.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年09月16日 星期二 12时30分45秒
* Description: 
************************************************************************/
#include "all.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	while (Fgets(sendline, MAXLINE, fp) != NULL)
	{
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		recvline[n] = 0;   /* means EOF to null terminate */
		Fputs(recvline, stdout);
	}

