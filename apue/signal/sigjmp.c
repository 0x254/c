/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: sigjmp.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 04 Jan 2015 02:29:54 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

sigjmp_buf sig_env;
int canjmp;

void pr_mask(const char *str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0)
		err_sys("sigprocmask error");

	printf("%s", str);
	if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
	if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1" );
	if (sigismember(&sigset, SIGALRM)) printf("SIGALRM ");
	printf("\n");
	errno = errno_save;
}

void sig_usr1(int signo)
{
    time_t starttime;
	if (canjmp == 0)
		return;
	pr_mask("starting sig_usr1: ");
	alarm(3);
	starttime = time(NULL);
	for ( ; ; )
		if (time(NULL) > starttime + 5)
			break;
	pr_mask("finishing sig_usr1: ");
	canjmp = 0;
	siglongjmp(sig_env, 1);
}

void sig_alrm(int signo)
{
    pr_mask("in sig_alrm: ");
}

int main(int argc, char **argv)
{
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal error");

	pr_mask("starting main: ");
	
	if (sigsetjmp(sig_env, 1)) { // for siglongjmp
		pr_mask("ending main: ");
		exit(0);
	}
	canjmp = 1;

	for ( ; ; )
		pause();
}
