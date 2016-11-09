/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: test.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 07 Dec 2014 05:18:12 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int fd;
	off_t pos;
	int en;
	fd = open("/tmp/testopen", O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
	printf("fd = %d\n", fd);
	pos = lseek(fd, 0, SEEK_CUR);
	en = errno;
	printf("pos = %ld\n", pos);
	printf("errno = %s\n", strerror(en));
	exit(0);
}
