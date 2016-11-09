/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: stat.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 08 Dec 2014 02:20:56 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char *ptr;
	//struct stat *buf1;
	struct stat *buf;
	int i;

	for (i = 1; i < argc; i++) {
		if (lstat(argv[i], &buf/* buf1 */) == -1)
			err_sys("lstat error");
		//if (S_ISREG((*buf1).st_mode))
		if (S_ISREG(buf.st_mode))
			ptr = "regular file";
		if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		if (S_ISCHR(buf.st_mode))
			ptr = "character device";
		if (S_ISBLK(buf.st_mode))
			ptr = "block device";
		if (S_ISFIFO(buf.st_mode))
			ptr = "pipe or fifo";
		if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		if (S_ISSOCK(buf.st_mode))
			ptr = "socket";

		printf("%s\n", ptr);
	}
	exit(0);
}
