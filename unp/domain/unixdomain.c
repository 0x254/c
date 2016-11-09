/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* File Name: unixdomain.c
* Version:                                                           *
* Writen by canux canuxcheng@gmail.com                               *
* Created Time: Tue 21 Oct 2014 02:41:44 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int sockfd;
	socklen_t len;
	struct sockaddr_un addr1, addr2;

	if (argc != 2)
		err_quit("Usage: unixbind <pathname>");

	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	unlink(argv[1]);

	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_LOCAL;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path)-1);
	Bind(sockfd, (SA *)&addr1, SUN_LEN(&addr1));

	len = sizeof(addr2);
	Getsockname(sockfd, (SA *)&addr2, &len);
	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);

	exit(0);
}
