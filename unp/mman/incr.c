/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: incr1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 01 Dec 2014 01:37:51 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define SEM_NAME "mysem"

int count = 0;

int main(int argc, char **argv)
{
	int i, nloop;
	sem_t *mutex;

	if (argc != 2)
		err_quit("Usage: incr <#loops>");
	nloop = atoi(argv[1]);

	mutex = Sem_open(Px_ipc_name(SEM_NAME), O_CREAT | O_EXCL, FILE_MODE, 1);
	Sem_unlink(Px_ipc_name(SEM_NAME));

	setbuf(stdout, NULL); // stdout is unbuffered
	if (Fork() == 0) {
		for (i = 0; i < nloop; i++) {
			Sem_wait(mutex);
			printf("child: %d\n", count++);
			Sem_post(mutex);
		}
		exit(0);
	}

	for (i = 0; i < nloop; i++) {
		Sem_wait(mutex);
		printf("parent: %d\n", count++);
		Sem_post(mutex);
	}
	exit(0);
}
