/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: incr2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 01 Dec 2014 09:42:12 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

struct shared {
	sem_t mutex;
	int count;
} shared;

int main(int argc, char **argv)
{
	int fd, i, nloop;
	struct shared *ptr;

	if (argc != 3)
		err_quit("Usage: incr2 <pathname> <#loops>");
	nloop = atoi(argv[2]);

	//open file, initialize to 0, map into memory
	fd = Open(argv[1], O_RDWR | O_CREAT, FILE_MODE);
	Write(fd, &shared, sizeof(struct shared));
	ptr = Mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	//initialize semaphore that is shared between process
	Sem_init(&ptr->mutex, 1, 1);

	setbuf(stdout, NULL);
	if (Fork() == 0) {
		for (i = 0; i < nloop; i++) {
			Sem_wait(&ptr->mutex);
			printf("child: %d\n", ptr->count++);
			Sem_post(&ptr->mutex);
		}
		exit(0);
	}
	for (i = 0; i < nloop; i++) {
		Sem_wait(&ptr->mutex);
		printf("parent: %d\n", ptr->count++);
		Sem_post(&ptr->mutex);
	}
	exit(0);
}
