/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: prodcons.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 24 Nov 2014 02:46:19 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define NBUFF 10
#define SEM_MUTEX "mutex" // these are args to px_ipc_name
#define SEM_NEMPTY "nempty"
#define SEM_NSTORED "nstored"

int nitems;
struct 
{
	int buff[NBUFF];
	sem_t *mutex, *nempty, *nstored;
} shared;

void *produce(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		Sem_wait(shared.nempty); // wait for at least 1 empty slot
		Sem_wait(shared.mutex);
		shared.buff[i % NBUFF] = i; // store i into circular buffer
		Sem_post(shared.mutex);
		Sem_post(shared.nstored); // 1 more stored item
	}
	return (NULL);
}

void consume(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		Sem_wait(shared.nstored); // wait for at least 1 stored item
		Sem_wait(shared.mutex);
		if (shared.buff[i % NBUFF] == i)
			printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
		Sem_post(shared.mutex);
		Sem_post(shared.nempty); // 1 more empty slot
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t tid_produce, tid_consume;

	if (argc != 2)
		err_quit("Usage: pc <#items>");
	nitems = atoi(argv[1]);

	//create three semaphore
	shared.mutex = Sem_open(Px_ipc_name(SEM_MUTEX), O_CREAT | O_EXCL, FILE_MODE, 1);
	shared.nempty = Sem_open(Px_ipc_name(SEM_NEMPTY), O_CREAT | O_EXCL, FILE_MODE, NBUFF);
	shared.nstored = Sem_open(Px_ipc_name(SEM_NSTORED), O_CREAT | O_EXCL, FILE_MODE, 0);

	//create one producer thread and one consumer thread
	Pthread_setconcurrency(2);
	Pthread_create(&tid_produce, NULL, produce, NULL);
	Pthread_create(&tid_consume, NULL, consume, NULL);

	//wait for the two threads
	Pthread_join(tid_produce, NULL);
	Pthread_join(tid_consume, NULL);

	//remove the semaphores
	Sem_unlink(Px_ipc_name(SEM_MUTEX));
	Sem_unlink(Px_ipc_name(SEM_NEMPTY));
	Sem_unlink(Px_ipc_name(SEM_NSTORED));
	exit(0);
}
