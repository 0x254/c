/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: job.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 06 Jan 2015 10:51:17 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void sig_tstp(int signo)
{
	sigset_t mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGTSTP);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	signal(SIGTSTP, SIG_DFL);
	kill(getpid(), SIGTSTP);
	signal(SIGTSTP, sig_tstp);
}
int main(int argc, char **argv)
{
	int n;
	char buf[BUFFSIZE];

	if (signal(SIGTSTP, SIG_IGN) == SIG_DFL)
		signal(SIGTSTP, sig_tstp);
	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");
	if (n < 0)
		err_sys("read error");
	exit(0);
}
