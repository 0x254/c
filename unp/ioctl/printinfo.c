/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: printinfo.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 28 Oct 2014 01:38:38 AM CST
* Description:                                                       *
*********************************************************************/
#include "ifi.h"

int main(int argc, char **argv)
{
	struct ifi_info *ifi, *ifihead;
	struct sockaddr *sa;
	u_char *ptr;
	int i, family, doaliases;

	if (argc != 3)
		err_quit("Usage: printinfo <inet4|inet6> <doaliases>");

	if (strcmp(argv[1], "inet4") == 0)
		family = AF_INET;
	else if (strcmp(argv[1], "inet6") == 0)
		family = AF_INET6;
	else
		err_quit("invalid <address-family>");
	doaliases = atoi(argv[2]);

	for (ifihead = ifi = get_ifi_info(family, doaliases); ifi != NULL; ifi = ifi->ifi_next)
	{
		printf("%s: ", ifi->ifi_name);
	
	    if (ifi->ifi_ivalue != 0)
		    printf("(%d\n) ", ifi->ifi_ivalue);

   	    printf("flags: <");
 	    if (ifi->ifi_flags & IFF_UP) printf("UP ");
	    if (ifi->ifi_flags & IFF_BROADCAST) printf("BCAST ");
	    if (ifi->ifi_flags & IFF_MULTICAST) printf("MCAST ");
	    if (ifi->ifi_flags & IFF_LOOPBACK) printf("LOOP ");
	    if (ifi->ifi_flags & IFF_POINTOPOINT) printf("P2P ");
	    if (ifi->ifi_flags & IFF_RUNNING) printf("RUNNING ");
        printf(">\n");

		if ((i = ifi->ifi_hlen) > 0)
		{
			ptr = ifi->ifi_haddr;
			do
			{
				printf("%s%x", (i == ifi->ifi_hlen) ? " " : ":", *ptr++);
			} while (--i > 0);
			printf("\n");
		}

		if (ifi->ifi_mtu != 0)
			printf(" MTU: %d\n", ifi->ifi_mtu);

		if ((sa = ifi->ifi_addr) != NULL)
			printf(" IP addr: %s\n", (char *)Sock_ntop_host(sa, sizeof(*sa)));

		if ((sa = ifi->ifi_brdaddr) != NULL)
			printf(" Broadcast addr: %s\n", (char *)Sock_ntop_host(sa, sizeof(*sa)));

		if ((sa = ifi->ifi_netmask) != NULL)
			printf(" Netmask: %s\n", (char *)Sock_ntop_host(sa, sizeof(*sa)));

		if ((sa = ifi->ifi_dstaddr) != NULL)
			printf(" Destination addr: %s\n", (char *)Sock_ntop_host(sa, sizeof(*sa)));
	}
	free_ifi_info(ifihead);
	exit(0);
}
