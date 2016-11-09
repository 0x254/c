/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: prodcons2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 26 Nov 2014 10:10:42 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define NBUFF 10
#define MAXNTHREADS 100

int nitems, nproducers;

struct
{
	int buff[NBUFF];
	int nput;
	int nputval;
	sem_t mutex, nempty, nstored;
} shared;

void *produce(void *arg)
{
	for ( ; ; )
	{
		Sem_wait(&shared.nempty);
		Sem_wait(&shared.mutex);

		if (shared.nput >= nitems)
		{
			Sem_post(&shared.nempty);
			Sem_post(&shared.mutex);
			return (NULL);
		}
		shared.buff[shared.nput % NBUFF] = shared.nputval;
		shared.nput++;
		shared.nputval++;

		Sem_post(&shared.mutex);
		Sem_post(&shared.nstored);
		*((int *) arg) += 1;
	}
}

void *consume(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		Sem_wait(&shared.nstored);
		Sem_wait(&shared.mutex);

		if (shared.buff[i % NBUFF] != i)
			printf("error: buff[%d] = %d\n", i, shared.buff[i % NBUFF]);

		Sem_post(&shared.mutex);
		Sem_post(&shared.nempty);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int i, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("Usage: pc2 <#items> <#producers>");
	nitems = atoi(argv[1]);
	nproducers = min(atoi(argv[2]), MAXNTHREADS);

	//init three semaphore
	Sem_init(&shared.mutex, 0, 1);
	Sem_init(&shared.nempty, 0, NBUFF);
	Sem_init(&shared.nstored, 0, 0);

	//create all producers and one consumer
	Pthread_setconcurrency(nproducers + 1);
	for (i = 0; i < nproducers; i++)
	{
		count[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	Pthread_create(&tid_consume, NULL, consume, NULL);

	//wait for all producers and the consumer
	for (i = 0; i < nproducers; i++)
	{
		Pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);
	}
	Pthread_join(tid_consume, NULL);

	Sem_destroy(&shared.mutex);
	Sem_destroy(&shared.nempty);
	Sem_destroy(&shared.nstored);
	exit(0);
}
