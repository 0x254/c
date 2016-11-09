/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: aj.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 31 Dec 2014 03:09:32 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

jmp_buf sig_env;

void sig_alrm(int signo)
{
	longjmp(sig_env, 1);
}

int main(int argc, char **argv)
{
	ssize_t n;
	char buf[MAXLINE];
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal error");
	if (setjmp(sig_env) != 0)
		err_quit("setjmp call by alarm");
	alarm(10);
	if ((n = read(STDIN_FILENO, buf, MAXLINE)) < 0)
		err_sys("read error");
	alarm(0);
	write(STDOUT_FILENO, buf, n);
	exit(0);
}
