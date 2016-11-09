/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: setvalue.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 28 Nov 2014 09:59:19 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int semid, nsems, i;
	struct semid_ds seminfo;
	unsigned short *ptr;
	union semun arg;

	if (argc < 2)
		err_quit("Usage: setvalue <pathname> [ value ...]");

	//first get the number of semaphore in the set
	semid = Semget(Ftok(argv[1], 0), 0, 0);
	arg.buf = &seminfo;
	Semctl(semid, 0, IPC_STAT, arg);
	nsems = arg.buf->sem_nsems;

	//now get the values from the command line
	ptr = Calloc(nsems, sizeof(unsigned short));
	arg.array = ptr;
	for (i = 0; i < nsems; i++)
		ptr[i] = atoi(argv[i + 2]);
	Semctl(semid, 0, SETALL, arg);
	exit(0);
}
