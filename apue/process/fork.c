/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: fork.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 18 Dec 2014 12:30:08 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int gval;
char buf[] = "write to stdout\n";

int main(int argc,  char **argv)
{
	int lval = 0;
	printf("gval = %d, lval = %d\n", gval, lval);
	pid_t pid;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		err_sys("write error");
	printf("before fork\n");

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {
		lval++;
		gval++;
	}
	else
		sleep(3);

	printf("pid = %d, lval = %d, gval = %d\n", getpid(), lval, gval);
	exit(0);
}
