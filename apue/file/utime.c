/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: utime.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 10 Dec 2014 01:08:33 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct stat buf;
	struct utimbuf times;
	int i;

	for (i = 1; i < argc; i++) {
		stat(argv[i], &buf);
		open(argv[i], O_RDWR | O_TRUNC);
		times.actime = buf.st_atime;
		times.modtime = buf.st_mtime;
		utime(argv[i], &times);
	}
	exit(0);
}
