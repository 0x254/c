/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: sigset.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 04 Jan 2015 12:20:03 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void  sig_quit(int signo)
{
	printf("caught sigquit\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		err_sys("reset sigquit error\n");
}

int main(int argc, char **arv)
{
	sigset_t newset, oldset, pendset;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("signal error");

	sigemptyset(&newset);
	sigaddset(&newset, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newset, &oldset) < 0)
		err_sys("sigprocmask error");
	sleep(5);

	if (sigpending(&oldset) < 0)
		err_sys("sigpending error");
	if (sigismember(&oldset, SIGQUIT))
		printf("sigquit is in oldset\n");

	if (sigprocmask(SIG_SETMASK, &oldset, NULL) < 0)
		err_sys("sigprocmask error");
	printf("sigquit unblock set\n");
	sleep(5);

	exit(0);
}
