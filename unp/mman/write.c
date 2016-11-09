/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: write.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 02 Dec 2014 11:22:47 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char  **argv)
{
	int i, fd;
	struct stat stat;
	unsigned char *ptr;

	if (argc != 2)
		err_quit("Usage: write <name>");

	//open, get size, map
	fd = Shm_open(argv[1], O_RDWR, FILE_MODE);
	Fstat(fd, &stat);
	ptr = Mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	//set ptr[0] = 0, ptr[1] = 1, etc.
	for (i = 0; i < stat.st_size; i++)
		*ptr++ = i % 256;
	exit(0);
}
