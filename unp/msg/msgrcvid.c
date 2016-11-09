/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: msgrcv2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 09:27:00 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define MAXMSG (8192 + sizeof(long))

int main(int argc, char **argv)
{
	int mqid;
	ssize_t n;
	struct msgbuf *buff;

	if (argc != 2)
		err_quit("Usage: rcv2 <mqid>");
	mqid = atoi(argv[1]);

	buff = (struct msgbuf *)Malloc(MAXMSG);

	n = Msgrcv(mqid, buff, MAXMSG, 0, 0);
	printf("read %d bytes, type = %ld\n", n, buff->mtype);

	exit(0);
}
