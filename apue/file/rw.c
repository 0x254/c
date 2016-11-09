/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: rw.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 07 Dec 2014 08:23:00 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int fd, rn, wn;
	char buf[BUFFSIZE];
	
	fd = open("/tmp/rw", O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
	while ((rn = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if ((wn = write(STDOUT_FILENO, buf, rn)) != rn)
			printf("write error");
	}
	if (rn < 0)
		printf("read error");

	exit(0);
}
