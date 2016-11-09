/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: create.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 28 Nov 2014 09:04:36 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int c, oflag, semid, nsems;

	oflag = SVSEM_MODE | IPC_CREAT;
	while ((c = Getopt(argc, argv, "e")) != -1) {
		switch (c) {
			case 'e':
				oflag |= IPC_EXCL;
				break;
		}
	}
	if (optind != argc - 2)
		err_quit("Usage: create [-e] <pathname> <nsems>");
	nsems = atoi(argv[optind + 1]);

	semid = Semget(Ftok(argv[optind], 0), nsems, oflag);
	exit(0);
}
