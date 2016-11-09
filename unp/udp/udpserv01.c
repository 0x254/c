/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: udpserv01.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年09月16日 星期二 01时15分33秒
* Description: 
************************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
    int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	 bzero(&servaddr, sizeof(servaddr));
	 servaddr.sin_family = AF_INET;
	 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	 servaddr.sin_port = htons(SERV_PORT);

	 Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

	 dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}
