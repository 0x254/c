/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: dev.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 10 Dec 2014 01:48:48 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct stat buf;
	int i;

	for (i = 1; i < argc; i++) {
		stat(argv[i], &buf);
		printf("major = %d, minor = %d\n", major(buf.st_dev), minor(buf.st_dev));
		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
			printf("%s: %d/%d\n", S_ISCHR(buf.st_mode)? "chr" : "blk", major(buf.st_rdev), minor(buf.st_rdev));
	}
	exit(0);
}
