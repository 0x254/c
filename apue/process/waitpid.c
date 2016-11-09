/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: waitpid.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 22 Dec 2014 12:49:00 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	pid_t pid;
	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0) {
		printf("this is the first child: %d, %d\n", getpid(), getppid());
		if ((pid = fork()) == -1)
			err_sys("fork error");
		else if (pid > 0) {
			sleep(5);
			printf("this is the father of second child: %d\n", getpid());
			exit(0);
		}
		sleep(3);
		printf("this is the second child: %d, %d\n", getpid(),  getppid());
		exit(0);
	}
	printf("this is: %d, %d\n", getpid(), getppid());
	printf("waitpid for: %d\n", pid);
	if (waitpid(pid, NULL, 0) != pid)
		err_sys("waitpid error");

	printf("this is the father of first child: %d\n", getpid());
	exit(0);
}
