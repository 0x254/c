/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: sigsusvar.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 05 Jan 2015 11:45:32 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int quitflag;

void sig_int(int signo)
{
	if (signo == SIGINT)
		printf("\ninterrupt\n");
	else if (signo == SIGQUIT)
		quitflag = 1;
}

int main(int argc, char **argv)
{
	sigset_t newset, oldset, zeroset;
	
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGQUIT, sig_int) == SIG_ERR)
		err_sys("signal error");

	sigemptyset(&zeroset);
	sigemptyset(&newset);
	sigaddset(&newset, SIGQUIT);

	if (sigprocmask(SIG_BLOCK, &newset, &oldset) < 0)
		err_sys("sigprocmask error");

	while (quitflag == 0)
		if (sigsuspend(&zeroset) != -1)
			err_sys("sigsuspend error");
	quitflag = 0;

	if (sigprocmask(0, &oldset, NULL) < 0)
		err_sys("sigprocmask error");
	
	exit(0);
}
