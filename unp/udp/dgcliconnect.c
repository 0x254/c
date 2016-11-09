/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: dgcliconnect.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Thu 18 Sep 2014 09:41:11 PM CST
* Description: 
************************************************************************/
#include "all.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	Connect(sockfd, (SA *)pservaddr, servlen);

	while (Fgets(sendline, MAXLINE, fp) != NULL)
	{
		Write(sockfd, sendline, strlen(sendline));

		n = Read(sockfd, recvline, MAXLINE);

		recvline[n] = 0;
		Fputs(recvline, stdout);
	}
}
