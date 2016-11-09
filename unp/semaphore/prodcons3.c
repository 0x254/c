/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: prodcons3.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 26 Nov 2014 02:07:32 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define NBUFF 10
#define MAXNTHREADS 100

int nitems, nproducers, nconsumers;

struct
{
	int buff[NBUFF];
	int nput;
	int nputval;
	int nget;
	int ngetval;
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
		*((int *)arg) += 1;
	}
}

void *consume(void *arg)
{
	int i;

	for ( ; ; )
	{
		Sem_wait(&shared.nstored);
		Sem_wait(&shared.mutex);

		if (shared.nget >= nitems)
		{
			Sem_post(&shared.nstored);
			Sem_post(&shared.mutex);
			return (NULL);
		}
		i = shared.nget % NBUFF;
		if (shared.buff[i] != shared.ngetval)
			printf("error: buff[%d] = %d\n", i, shared.buff[i]);
		shared.nget++;
		shared.ngetval++;

		Sem_post(&shared.mutex);
		Sem_post(&shared.nempty);
		*((int *)arg) += 1;
	}
}

int main(int argc, char **argv)
{
	int i, prodcount[MAXNTHREADS], conscount[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume[MAXNTHREADS];

	if (argc != 4)
		err_quit("Usage: pc3 <#items> <#producers> <#consumers>");
	nitems = atoi(argv[1]);
	nproducers = min(atoi(argv[2]), MAXNTHREADS);
	nconsumers = min(atoi(argv[3]), MAXNTHREADS);

	//init all producers and all consumers
	Pthread_setconcurrency(nproducers + nconsumers);
	for (i = 0; i < nproducers; i++)
	{
		prodcount[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &prodcount[i]);
	}
	for (i = 0; i < nconsumers; i++)
	{
		conscount[i] = 0;
		Pthread_create(&tid_consume[i], NULL, consume, &conscount[i]);
	}

	// wait for all producers and consumers
	for (i = 0; i < nproducers; i++)
	{
		Pthread_join(tid_produce[i], NULL);
		printf("producer count[%d] = %d\n", i, prodcount[i]);
	}
	for (i = 0; i < nconsumers; i++)
	{
		Pthread_join(tid_consume[i], NULL);
		printf("consumer count[%d] = %d\n", i, conscount[i]);
	}
	Sem_destroy(&shared.mutex);
	Sem_destroy(&shared.nempty);
	Sem_destroy(&shared.nstored);
	exit(0);
}
