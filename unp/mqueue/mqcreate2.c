/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqcreate2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 07 Nov 2014 09:15:59 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

struct mq_attr attr; // mq_maxmsg and mq_msgsize both init to 0

int main(int argc, char **argv)
{
	int c, flags;
	mqd_t mqd;
	
	flags = O_RDWR | O_CREAT;
	while ((c = Getopt(argc, argv, "em::z:")) != -1) // -m and -z need argument
	{
        switch (c)
		{
			case 'e':
				flags |= O_EXCL;
				break;
			case 'm':
				attr.mq_maxmsg = atol(optarg);
				break;
			case 'z':
				attr.mq_msgsize = atol(optarg);
		}
	}
	if (optind != argc - 1)
		err_quit("Usage: create2 [-e] [-m maxmsg -z msgsize] <name>");

	if ((attr.mq_maxmsg != 0 && attr.mq_msgsize == 0) || (attr.mq_maxmsg == 0 && attr.mq_msgsize != 0))
		err_quit("must specify both -m maxmsg and -z msgsize");

	mqd = Mq_open(argv[optind], flags, FILE_MODE, (attr.mq_maxmsg != 0) ? &attr : NULL);

	Mq_close(mqd);
	exit(0);
}
