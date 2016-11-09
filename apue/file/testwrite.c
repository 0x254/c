/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: testhole.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 07 Dec 2014 07:35:52 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char buf1[] = "abcdefghij";
	char buf2[] = "ABCDEFGHIJ";

	int fd;

	fd = open("/tmp/testhole", O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
	write(fd, buf1, 10);
	lseek(fd, 1035, SEEK_SET);
	write(fd, buf2, 10);

	exit(0);
}
