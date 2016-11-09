/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: client1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 04 Dec 2014 01:59:58 PM CST
* Description:                                                       *
*********************************************************************/
#include "cs1.h"

int main(int argc, char **argv)
{
	int fd, i, nloop, nusec;
	pid_t pid;
	char mesg[MESGSIZE];
	long offset;
	struct shmstruct *ptr;

	if (argc != 4)
		err_quit("Usage: client1 <name> <#loops> <#usec>");
	nloop = atoi(argv[2]);
	nusec = atoi(argv[3]);

	//open and map shared memory that server must create
	fd = Shm_open(Px_ipc_name(argv[1], O_RDWR, FILE_MODE));
	ptr = Mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	pid = getpid();
	for (i = 0; i < nloop; i++) {
		snprintf(mesg, MESGSIZE, "pid %ld: message %d", (long) pid, i);
		
		if (sem_trywait(&ptr->nempty) == -1) {
			if (errno == EAGAIN) { // no place for this msg
				Sem_wait(&ptr->noverflowmutex);
				ptr->noverflow++;
				Sem_post(&ptr->noverflowmutex);
				continue;
			} else
				err_sys("sem_trywait error");
		}
		Sem_wait(&ptr->mutex);
		offset = ptr->msgoff[ptr->nput];
		if (++(ptr->nput) >= NMESG)
			ptr->nput = 0;
		Sem_post(&ptr->mutex);
		strcpy(&ptr->msgdata[offset], mesg);
		Sem_post(&ptr->nstored);
	}
	exit(0);
}
