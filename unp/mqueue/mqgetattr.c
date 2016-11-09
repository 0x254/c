/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqgetattr.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 07 Nov 2014 03:03:45 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	mqd_t mqd;
	struct mq_attr attr;

	if  (argc != 2)
		err_quit("Usage: mqgetattr <name>");

	mqd = Mq_open(argv[1], O_RDONLY);

	Mq_getattr(mqd, &attr);
	//printf("flags = %ld", attr.mq_flags);
	printf("max #msgs = %ld, max #bytes/msg = %ld, #currently on queue = %ld\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

	Mq_close(mqd);
	exit(0);
}
