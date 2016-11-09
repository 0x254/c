/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: dgclioop1.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Thu 18 Sep 2014 10:16:04 PM CST
* Description: 
************************************************************************/
#include "all.h"

#define NDG 2000
#define DGLEN 1400

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int i;
	char sendline[DGLEN];

	for (i = 0; i < NDG; i++)
	{
		Sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
	}
}
