/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: join.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 07 Jan 2015 02:57:37 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void  *thr1(void *s)
{
	printf("tid1 return\n");
	return (void *)1;
}

void *thr2(void *s)
{
	printf("tid2 exit\n");
	pthread_exit((void *)2);
}

int main(int argc, char **argv)
{
	int err;
	pthread_t tid1;
	pthread_t tid2;
	void *val;

	if (pthread_create(&tid1, NULL, thr1, NULL) != 0)
		err_quit("pthread_create tid1 error");
	if (pthread_create(&tid2, NULL, thr2, NULL) != 0)
		err_quit("pthread_create tid2 error");
	if (pthread_join(tid1, &val) != 0)
		err_quit("pthread_join tid1 error");
	printf("tid1 exit code %d\n", (int)val);
	if (pthread_join(tid2, &val) != 0)
		err_quit("pthread_join tid2 error");
	printf("tid2 exit code %d\n", (int)val);
	exit(0);
}
