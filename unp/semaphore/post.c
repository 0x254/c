/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: post.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 23 Nov 2014 08:03:35 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	sem_t *sem;
	int val;

	if (argc != 2)
		err_quit("Usage: post <name>");

	sem = Sem_open(argv[1], 0);
	Sem_post(sem);
	Sem_getvalue(sem, &val);
	printf("value = %d\n", val);

	exit(0);
}
