/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: server.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 03 Dec 2014 10:30:42 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

struct shmstruct { /* struct stored in shared memory */
	int count;
};
sem_t *mutex; /* pointer to named semaphore */

int main(int argc, char **argv)
{
	int fd;
	struct shmstruct *ptr;

	if (argc != 3)
		err_quit("Usage: server <shmname> <semname>");

	shm_unlink((const char *)Px_ipc_name(argv[1]));
	//create shm, set its size, map it, close descriptor
	fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
	Ftruncate(fd, sizeof(struct shmstruct));
	ptr = Mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	sem_unlink((const char *)Px_ipc_name(argv[2]));
	mutex = Sem_open(Px_ipc_name(argv[2]), O_CREAT | O_EXCL, FILE_MODE, 1);
	Sem_close(mutex);

	exit(0);
}
