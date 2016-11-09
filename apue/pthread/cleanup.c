/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: cleanup.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 08 Jan 2015 01:45:42 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void cleanup(char *s)
{
	printf("cleanup %s\n", s);
}

void *func1(void *s)
{
	printf("start thr1\n");
	pthread_cleanup_push(cleanup, "thr1 first push");
	pthread_cleanup_push(cleanup, "thr1 second push");
	printf("thr1 push finish\n");
	if (s)
		return (void *)1;
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return (void *)1;
}

void *func2(void *s)
{
	printf("start thr2\n");
	pthread_cleanup_push(cleanup, "thr2 first push");
	pthread_cleanup_push(cleanup, "thr2 second push");
	printf("thr2 push finish\n");
	if (s)
		pthread_exit((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int main(int argc, char **argv)
{
	pthread_t thr1, thr2;
	void *val;
	if (pthread_create(&thr1, NULL, func1, (void *)1) != 0)
		err_quit("pthread_create thr1 error");
	if (pthread_create(&thr2, NULL, func2, (void *)2) != 0)
		err_quit("pthread_create thr2 error");
	sleep(1);
	if (pthread_join(thr1, &val) != 0)
		err_quit("pthread_join thr1 error");
	printf("thr1 exit code: %d\n", (int)val);
	if (pthread_join(thr2, &val) != 0)
		err_quit("pthread_join thr2 error");
	printf("thr2 exit code: %d\n", (int)val);
	exit(0);
}
