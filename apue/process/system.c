/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: system.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 24 Dec 2014 10:53:15 AM CST
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
	int status;
	if ((status = system("date")) < 0)
		err_sys("system error");
	printf("%d\n", status);
	mystatus(status);

	if ((status = system("no")) < 0)
		err_sys("system error");
	printf("%d\n", status);
	mystatus(status);

	if ((status = system("who; exit 44")) < 0)
		err_sys("system error");
	printf("%d\n", status);
	mystatus(status);

	exit(0);
}
