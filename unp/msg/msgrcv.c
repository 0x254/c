/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: msgrcv.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 08:24:41 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define MAXMSG (8192 + sizeof(long))

int main(int argc, char **argv)
{
	int c, flag, mqid;
	long type;
	ssize_t n;
	struct msgbuf *buff;

	type = flag = 0;
	while ((c = Getopt(argc, argv, "nt:")) != -1)
	{
		switch (c)
		{
			case 'n':
				flag |= IPC_NOWAIT;
				break;
			case 't':
				type = atol(optarg);
				break;
		}
	}
	if (optind != argc - 1)
		err_quit("Usage: msgrcv [-n] [-t type] <pathname>");
	
	mqid = Msgget(Ftok(argv[optind], 0), MSG_R);
	
	buff = (struct msgbuf *)Malloc(MAXMSG);

	n = Msgrcv(mqid, buff, MAXMSG, type, flag);
	printf("read %d bytes, type = %ld\n", n, buff->mtype);

	exit(0);
}
