/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqsend.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 07 Nov 2014 10:32:45 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	mqd_t mqd;
	char *ptr;
	size_t len;
	unsigned int prio;

	if (argc != 4)
		err_quit("Usage: send <name> <#bytes> <priority>");

	len = atoi(argv[2]);
	prio = atoi(argv[3]);

	mqd = Mq_open(argv[1], O_WRONLY);
	ptr = (char *)Calloc(len, sizeof(char));
	Mq_send(mqd, ptr, len, prio);
	exit(0);
}
