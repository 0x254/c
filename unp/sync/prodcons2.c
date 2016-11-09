/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: prodcons2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 14 Nov 2014 02:51:33 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define MAXNITEMS 1000000
#define MAXNTHREADS 100

int nitems;
struct
{
	pthread_mutex_t mutex;
	int buff[MAXNITEMS];
	int nput;
	int nval;
} shared = {
	PTHREAD_MUTEX_INITIALIZER
};

void *produce(void *arg)
{
	for ( ; ; )
	{
		Pthread_mutex_lock(&shared.mutex);
		if (shared.nput >= nitems)
		{
			Pthread_mutex_unlock(&shared.mutex);
			return (NULL);
		}
		shared.buff[shared.nput] = shared.nval;
		shared.nput++;
		shared.nval++;
		Pthread_mutex_unlock(&shared.mutex);
		*((int *)arg) += 1;
	}
}

void consume_wait(int i)
{
	for ( ; ; )
	{
		Pthread_mutex_lock(&shared.mutex);
		if (i < shared.nput)
		{
			Pthread_mutex_unlock(&shared.mutex);
			return;
		}
		Pthread_mutex_unlock(&shared.mutex);
	}
}

void *consume(void *arg)
{
	int i;
	for (i = 0; i < nitems; i++)
	{
		consume_wait(i);
		if (shared.buff[i] != i)
			printf("buff[%d] = %d\n", i, shared.buff[i]);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("Usage: pc2 <#items> <#threads>");

	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

	//create all producers and one  consumer
	Pthread_setconcurrency(nthreads + 1);
	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	Pthread_create(&tid_produce[i], NULL, consume, NULL);

	//wait for all producers and the consumer
	for (i = 0; i < nthreads; i++)
	{
		Pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);
	}
	Pthread_join(tid_consume, NULL);

	exit(0);
}
