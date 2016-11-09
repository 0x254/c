/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: server1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 04 Dec 2014 01:37:20 PM CST
* Description:                                                       *
*********************************************************************/
#include "cs1.h"

int main(int argc, char **argv)
{
	int fd, index, lastnoverflow, temp;
	long offset;
	struct shmstruct *ptr;

	if (argc != 2)
		err_quit("Usage: server1 <name>");

	//create shm, set its size, map it, close descriptor
	shm_unlink(Px_ipc_name(argv[1]));
	fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
	ptr = Mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Ftruncate(fd, sizeof(struct shmstruct));
	Close(fd);

	//initialize the array of offsets
	for (index = 0; index < NMESG; index++)
		ptr->msgoff[index] = index * MESGSIZE;

	//initialize the semaphore in shared memory
	Sem_init(&ptr->mutex, 1, 1);
	Sem_init(&ptr->nempty, 1, NMESG);
	Sem_init(&ptr->nstored, 1, 0);
	Sem_init(&ptr->noverflowmutex, 1, 1);

	//this program is the consumer
	index = 0;
	lastnoverflow = 0;
	for ( ; ; ) {
		Sem_wait(&ptr->nstored);
		Sem_wait(&ptr->mutex);
		offset = ptr->msgoff[index];
		printf("index = %d: %s\n", index, &ptr->msgdata[offset]);
		if (++index >= NMESG)
			index = 0;
		Sem_post(&ptr->mutex);
		Sem_post(&ptr->nempty);

		Sem_wait(&ptr->noverflowmutex);
		temp = ptr->noverflow;
		Sem_post(&ptr->noverflowmutex);
		if (temp != lastnoverflow) {
			printf("noverflow = %d\n", temp);
			lastnoverflow = temp;
		}
	}
	exit(0);
}
