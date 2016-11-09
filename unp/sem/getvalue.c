/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: getvalue.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 28 Nov 2014 10:33:28 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int semid, nsems, i;
	struct semid_ds seminfo;
	unsigned short *ptr;
	union semun arg;

	if (argc != 2)
		err_quit("Usage: getvalue <pathname>");

	//first get the number of semaphore in the set
	semid = Semget(Ftok(argv[1], 0), 0, 0);
	arg.buf = &seminfo;
	Semctl(semid, 0, IPC_STAT, arg);
	nsems = arg.buf->sem_nsems;

	//allocate memory to hold all the value in the set
	ptr = Calloc(nsems, sizeof(unsigned short));
	arg.array = ptr;

	//fetch the values and print
	Semctl(semid, 0, GETALL, arg);
	for (i = 0; i < nsems; i++)
		printf("semval[%d] = %d\n", i, ptr[i]);

	exit(0);
}
