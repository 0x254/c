/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: get.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 04 Dec 2014 10:30:16 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int c, id, oflag;
	char *ptr;
	size_t length;

	oflag = SVSHM_MODE | IPC_CREAT;
	while ((c = Getopt(argc, argv, "e")) != -1) {
		switch (c) {
			case 'e':
				oflag |= IPC_EXCL;
				break;
		}
	}
	if (optind != argc - 2)
		err_quit("Usage: get [-e] <pathname> <length>");
	length = atoi(argv[optind + 1]);

	id = Shmget(Ftok(argv[optind], 0), length, oflag);
	ptr = Shmat(id, NULL, 0);
	exit(0);
}
