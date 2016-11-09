/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: prodcons3.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 14 Nov 2014 10:34:46 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define MAXNITEMS 1000000
#define MAXNTHREADS 100

//globals shared by threads
int nitems;
int buff[MAXNITEMS];

struct
{
	pthread_mutex_t mutex;
	int nput;
	int nval;
} put = {
	PTHREAD_MUTEX_INITIALIZER
};

struct
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nready;
} nready = {
	PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER
};

void *produce(void *arg)
{
	for ( ; ; )
	{
		Pthread_mutex_lock(&put.mutex);
		if (put.nput >= nitems)
		{
			Pthread_mutex_unlock(&put.mutex);
			return (NULL);
		}
		buff[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		Pthread_mutex_unlock(&put.mutex);

		Pthread_mutex_lock(&nready.mutex);
		if (nready.nready == 0)
			Pthread_cond_signal(&nready.cond);
		nready.nready++;
		Pthread_mutex_unlock(&nready.mutex);

		*((int *)arg) += 1;
	}
}

void *consume(void *arg)
{
	int i;
	for (i = 0; i < nitems; i++)
	{
		Pthread_mutex_lock(&nready.mutex);
		while (nready.nready == 0)
			Pthread_cond_wait(&nready.cond, &nready.mutex);
		nready.nready--;
		Pthread_mutex_unlock(&nready.mutex);

		if (buff[i] != i)
			printf("buff[%d] = %d\n", i, buff[i]);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("Usage: pc3 <#items> <#threads>");

	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

	//create all producers and one consumer
	Pthread_setconcurrency(nthreads + 1);
	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	Pthread_create(&tid_consume, NULL, consume, NULL);

	// wait for all producers and consumer
	for (i = 0; i < nthreads; i++)
	{
		Pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);
	}
	Pthread_join(tid_consume, NULL);

	exit(0);
}
