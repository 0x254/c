/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: udpcli02.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年09月19日 星期五 12时04分32秒
* Description: 
************************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int sockfd;
	socklen_t len;
	struct sockaddr_in cliaddr, servaddr;

	if (argc != 2)
		err_quit("Usage: udpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	len = sizeof(cliaddr);
	Getsockname(sockfd, (SA *)&cliaddr, &len);
	printf("local address %s\n", (char *)Sock_ntop((SA *)&cliaddr, len));

	exit(0);
}
