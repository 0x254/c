/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: op.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 28 Nov 2014 11:00:17 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int c, i, flag, semid, nops;
	struct sembuf *ptr;

	flag = 0;
	while ((c = Getopt(argc, argv, "nu")) != -1) {
		switch (c) {
			case 'n':
				flag |= IPC_NOWAIT;
				break;
			case 'u':
				flag |= SEM_UNDO;
				break;
		}
	}
	if (argc - optind < 2)
		err_quit("Usage: op [-n] [-u] <pathnae> operation ...");

	semid = Semget(Ftok(argv[optind], 0), 0, 0);
	optind++;
	nops = argc - optind;

	//allocate memory to hold operations, store, and perform
	ptr = Calloc(nops, sizeof(struct sembuf));
	for (i = 0; i < nops; i++) {
		ptr[i].sem_num = i;
		ptr[i].sem_op = atoi(argv[optind + i]);
		ptr[i].sem_flg = flag;
	}
	Semop(semid, ptr, nops);
	exit(0);
}
