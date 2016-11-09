/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: sctpcli01.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Tue 23 Sep 2014 08:43:33 PM CST
* Description: 
************************************************************************/
#include "all.h"

void sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen);

int main(int argc, char **argv)
{
	int sock_fd;
	struct sockaddr_in servaddr;
	struct sctp_event_subscribe evnts;
	int echo_to_all = 0;
	char *byemsg;

	if (argc < 2)
		err_quit("Missing host argument - use '%s host [echo]'\n", argv[0]);
	if (argc > 2)
	{
		printf("Echoing message to all streams\n");
	    echo_to_all = 1;
	}

	sock_fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));
	if (echo_to_all == 0)
		sctpstr_cli(stdin, sock_fd, (SA *)&servaddr, sizeof(servaddr));
	else
		sctpstr_cli_echoall(stdin, sock_fd, (SA *)&servaddr, sizeof(servaddr));

	strcpy(byemsg, "goodbye");
	Sctp_sendmsg(sock_fd, byemsg, strlen(byemsg), (SA *)&servaddr, sizeof(servaddr), 0, SCTP_ABORT, 0, 0, 0);

	Close(sock_fd);
	return (0);
}
