/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: wait.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 19 Dec 2014 02:28:07 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void mystatus(int status)
{
	if (WIFEXITED(status))
		printf("normal exit, status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("unnormal exit, signal = %d\n", WTERMSIG(status));
	else if (WCOREDUMP(status))
		printf("core dump\n");
	else if (WIFSTOPPED(status))
		printf("stop exit, signal = %d\n", WSTOPSIG(status));
}

int main(int argc, char **argv)
{
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		exit(7);
	if (wait(&status) != pid)
		err_sys("wait error");
	mystatus(status);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		abort();
	if (wait(&status) != pid)
		err_sys("wait error");
	mystatus(status);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		status /= 0;
	if (wait(&status) != pid)
		err_sys("wait error");
	mystatus(status);

	exit(0);
}
