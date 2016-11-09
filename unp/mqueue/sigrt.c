/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: sigrt.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 10 Nov 2014 09:47:24 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

static void sig_rt(int signo, siginfo_t *info, void *context)
{
	printf("received signal #%d, code = %d, ival = %d\n", signo, info->si_code, info->si_value.sival_int);
}

int main(int argc, char **argv)
{
	int i, j;
	pid_t pid;
	sigset_t newset;
	union sigval val;

	printf("SIGRTMIN = %d, SIGRTMAX = %d\n", (int) SIGRTMIN, (int) SIGRTMAX);

	if ((pid = Fork()) == 0)
	{
		Sigemptyset(&newset);
		Sigaddset(&newset, SIGRTMAX);
		Sigaddset(&newset, SIGRTMAX - 1);
		Sigaddset(&newset, SIGRTMAX - 2);
		Sigprocmask(SIG_BLOCK, &newset, NULL);

		signal_rt(SIGRTMAX, sig_rt, &newset);
		signal_rt(SIGRTMAX - 1, sig_rt, &newset);
		signal_rt(SIGRTMAX - 2, sig_rt, &newset);

		sleep(6);

		Sigprocmask(SIG_UNBLOCK, &newset, NULL);
		sleep(3);
		exit(0);
	}
	sleep(3);
	for (i = SIGRTMAX; i >= SIGRTMAX - 2; i--)
	{
		for (j = 0; j <= 2; j++)
		{
			val.sival_int = j;
			Sigqueue(pid, i, val);
			printf("sent signal %d, val = %d\n", i, j);
		}
	}
	exit(0);
}
