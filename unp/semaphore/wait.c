/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: wait.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 23 Nov 2014 07:51:27 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	sem_t *sem;
	int val;

	if (argc != 2)
		err_quit("Usage: wait <name>");

	sem = Sem_open(argv[1], 0);
	Sem_wait(sem);
	Sem_getvalue(sem, &val);
	printf("pid %ld has semaphore, value = %d\n", (long)getpid(), val);

	pause();
	exit(0);
}
