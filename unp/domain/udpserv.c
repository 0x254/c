/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* File Name: udpserv.c
* Version:                                                           *
* Writen by canux canuxcheng@gmail.com                               *
* Created Time: Tue 21 Oct 2014 09:35:54 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define UNIXDG_PATH "/tmp/unix.dg"

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_un servaddr, cliaddr;

	sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

	unlink(UNIXDG_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXDG_PATH);

	Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

	dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}
