/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: sigsuspend.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 05 Jan 2015 10:04:49 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void pr_mask(const char *s)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	
	if (sigprocmask(0, NULL, &sigset) < 0)
		err_sys("sigprocmask error");

	printf("%s", s);
	if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");

	printf("\n");

	errno = errno_save;
}

void sig_int(int signo)
{
	pr_mask("in sig_int: ");
}

int main(int argc, char **argv)
{
	sigset_t newset, oldset, waitset;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");
	sigemptyset(&waitset);
	sigaddset(&waitset, SIGUSR1);
	sigemptyset(&newset);
	sigaddset(&newset, SIGINT);

	pr_mask("starting main: ");

	if (sigprocmask(SIG_BLOCK, &newset, &oldset) < 0)
		err_sys("sigprocmask error");
	pr_mask("in critical region: ");

	if (sigsuspend(&waitset) != -1)
		err_sys("sigsuspend error");

	pr_mask("after return from sigsuspend: ");

	if (sigprocmask(SIG_SETMASK, &oldset, NULL) < 0)
		err_sys("sigprocmask error");
	pr_mask("program exit: ");

	exit(0);
}
