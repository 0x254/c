/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* File Name: localcli.c
* Version:                                                           *
* Writen by canux canuxcheng@gmail.com                               *
* Created Time: Tue 21 Oct 2014 07:44:25 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define UNIXSTR_PATH "/tmp/unix.str"

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_un servaddr;

	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);

	exit(0);
}
