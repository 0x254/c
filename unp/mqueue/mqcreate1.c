/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqcreate1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 07 Nov 2014 12:08:08 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int c, flags;
	mqd_t mqd;

	flags = O_RDWR | O_CREAT;
	while ((c = Getopt(argc, argv, "e")) != -1) // already exist
	{
		switch (c)
		{
			case 'e':
				flags |= O_EXCL;
				break;
		}
	}
	if (optind != argc - 1)
		err_quit("Usage: create1 [ -e ] <name>");

	mqd = Mq_open(argv[optind], flags, FILE_MODE, NULL);

	Mq_close(mqd);
	exit(0);
}
