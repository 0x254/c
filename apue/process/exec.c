/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: exec.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 23 Dec 2014 01:11:58 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	pid_t pid;
	char *argp[] = {"bash", "-c", "echo $USER", NULL};
	char *envp[] = {"USER=weizi", NULL};

	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0) {
		if (execl("/bin/bash", "bash", "-c", "echo $USER", (char *)0) == -1)
			err_sys("execl error");
	}
	if (waitpid(pid, NULL, 0) == -1)
		err_sys("waitpid error");

	if (execvpe("bash", argp, envp) == -1)
		err_sys("execvpe error");

	exit(0);
}
