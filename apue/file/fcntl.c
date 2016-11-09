/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: testfcntl.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 08 Dec 2014 12:48:41 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int val;

	if (argc != 2)
		err_quit("Usage: testfcntl <#filedes>");
	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) == -1)
		err_sys("fcntl error");
	switch (val & O_ACCMODE) {
		case O_RDONLY:
			printf("read only\n");
			break;
		case O_WRONLY:
			printf("write only\n");
			break;
		case O_RDWR:
			printf("read and write\n");
			break;
		default:
			printf("unkonw access mode\n");
	}
	if (val & O_APPEND)
		printf("append\n");
	if (val & O_NONBLOCK)
		printf("nonblock\n");
	if (val & O_ASYNC)
		printf("async\n");

	exit(0);
}
