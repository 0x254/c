/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: prodcons1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 25 Nov 2014 02:45:24 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define NBUFF 10

int nitems;
struct
{
	int buff[NBUFF];
	sem_t mutex, nempty, nstored;
} shared;

void *produce(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		Sem_wait(&shared.nempty);
		Sem_wait(&shared.mutex);
		shared.buff[i % NBUFF] = i;
		Sem_post(&shared.mutex);
		Sem_post(&shared.nstored);
	}
	return (NULL);
}

void *consume(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		Sem_wait(&shared.nstored);
		Sem_wait(&shared.mutex);
		if (shared.buff[i % NBUFF] == i)
			printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
		Sem_post(&shared.mutex);
		Sem_post(&shared.nempty);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t tid_produce, tid_consume;

	if (argc != 2)
		err_quit("Usage: pc1 <#items>");
	nitems = atoi(argv[1]);

	//init three semaphore
	Sem_init(&shared.mutex, 0, 1);
	Sem_init(&shared.nempty, 0, NBUFF);
	Sem_init(&shared.nstored, 0, 0);

	Pthread_setconcurrency(2);
	Pthread_create(&tid_produce, NULL, produce, NULL);
	Pthread_create(&tid_consume, NULL, consume, NULL);

	Pthread_join(tid_produce, NULL);
	Pthread_join(tid_consume, NULL);

	Sem_destroy(&shared.mutex);
	Sem_destroy(&shared.nempty);
	Sem_destroy(&shared.nstored);

	exit(0);
}
