/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqreceive.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 07 Nov 2014 11:00:10 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int c, flags;
	mqd_t mqd;
	ssize_t n;
	unsigned int prio;
	void *buff;
	struct mq_attr attr;

	flags = O_RDONLY;
	while ((c = Getopt(argc, argv, "n")) != -1)
	{
		switch (c)
		{
			case 'n':
				flags |= O_NONBLOCK;
				break;
		}
	}
	if (optind != argc - 1)
		err_quit("Usage: receive [-n] <name>");

	mqd = Mq_open(argv[optind], flags);
	Mq_getattr(mqd, &attr);

	buff = (void *)Malloc(attr.mq_msgsize);

	n = Mq_receive(mqd, buff, attr.mq_msgsize, &prio);
	printf("read %ld bytes, priority = %u\n", (long)n, prio);

	exit(0);
}
