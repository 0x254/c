/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: getvalue.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 23 Nov 2014 07:49:30 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	sem_t *sem;
	int val;

	if (argc != 2)
		err_quit("Usage: getvalue <name>");
	
	sem = Sem_open(argv[1], 0);
	Sem_getvalue(sem, &val);
	printf("value = %d\n", val);

	exit(0);
}
