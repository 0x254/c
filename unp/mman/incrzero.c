/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: incr1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 01 Dec 2014 08:42:01 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define SEM_NAME "mysem"

int main(int argc, char **argv)
{
	int fd, i, nloop;
	int *ptr;
	sem_t *mutex;

	if (argc != 2)
		err_quit("Usage: incrzero <#loops>");
	nloop = atoi(argv[1]);

	//open file, initialize to 0, map into memory
	fd = Open("/dev/zero", O_RDWR);
	ptr = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	//create, initialize and unlink semaphore
	mutex = Sem_open(Px_ipc_name(SEM_NAME), O_CREAT | O_EXCL, FILE_MODE, 1);
	Sem_unlink(Px_ipc_name(SEM_NAME));

	setbuf(stdout, NULL);
	if (Fork() == 0) {
		for (i = 0; i < nloop; i++) {
			Sem_wait(mutex);
			printf("child: %d\n", (*ptr)++);
			Sem_post(mutex);
		}
		exit(0);
	}

	for (i = 0; i < nloop; i++) {
		Sem_wait(mutex);
		printf("parent: %d\n", (*ptr)++);
		Sem_post(mutex);
	}
	exit(0);
}
