/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: getrt.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 29 Oct 2014 07:19:08 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define BUFLEN (sizeof(struct rt_msghdr) + 512)
#define SEQ 9999

int main(int argc, char **argv)
{
	int sockfd;
	char *buf;
	pid_t pid;
	uint8_t salen;
	ssize_t n;
	struct rt_msghdr *rtm;
	struct sockaddr *sa, *rti_info[RTAX_MAX];
	struct sockaddr_in *sin, *gin;

	if (argc != 2)
		err_quit("Usage: getrt <Ipaddress>");

	sockfd = Socket(AF_ROUTE, SOCK_RAW, 0);

	buf = Calloc(1, BUFLEN);

	rtm = (struct rt_msghdr *)buf;
	rtm->rtm_msglen = sizeof(struct rt_msghdr) + sizeof(struct sockaddr_in);
	rtm->rtm_version = RTM_VERSION;
	rtm->rtm_type = RTM_GET;
	rtm->rtm_addrs = RTA_DST;
	rtm->rtm_pid = pid = getpid();
	rtm->rtm_seq = SEQ;

	sin = (struct sockaddr_in *)(rtm + 1);
	sin->sin_len = sizeof(struct sockaddr_in);
	sin->sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], &sin->sin_addr);

	Write(sockfd, rtm, rtm->rtm_msglen);

	do
	{
		n = Read(sockfd, rtm, BUFLEN);
	} while (rtm->rtm_type != RTM_GET || rtm->rtm_seq != SEQ || rtm->rtm_pid != pid);

	rtm = (struct rt_msghdr *)buf;

	sa = (struct sockaddr *)(rtm+1);
	salen = (uint8_t)strlen(sa);

	get_rtaddrs(rtm->rtm_addrs, sa, rti_info);
	if ((sa = rti_info[RTAX_DST]) != NULL)
		printf("dest: %s\n", Sock_ntop_host(sa, salen));

	if ((sa = rti_info[RTAX_GETWAY]) != NULL)
		printf("geteway: %s\n", Sock_ntop_host(sa, salen));

	if ((sa = rti_info[RTAX_NETMASK]) != NULL)
		printf("netmask: %s\n", Sock_masktop(sa, salen));

	if ((sa = rti_info[RTAX_GENMASK]) != NULL)
		printf("genmask: %s\n", Sock_masktop(sa, salen));
	
	exit(0);
}
