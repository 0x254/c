/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* File Name: udpcli.c
* Version:                                                           *
* Writen by canux canuxcheng@gmail.com                               *
* Created Time: Tue 21 Oct 2014 09:35:29 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define UNIXDG_PATH "/tmp/unix.dg"

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_un cliaddr, servaddr;

	sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sun_family = AF_LOCAL;
	strcpy(cliaddr.sun_path, tmpnam(NULL));   // use mkstemp instead of tmpnam 

	Bind(sockfd, (SA *)&cliaddr, sizeof(cliaddr));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXDG_PATH);

	dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));
	
	exit(0);
}
