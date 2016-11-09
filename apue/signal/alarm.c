/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: alarm.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 31 Dec 2014 02:40:05 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void sig_alrm(int signo)
{
	printf("alarm and return to read\n");
	return;
}

int main(int argc, char **argv)
{
	ssize_t n;
	char buf[MAXLINE];
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal error");
	alarm(10);
	if ((n = read(STDIN_FILENO, buf, MAXLINE)) < 0)
		err_sys("read error");
	alarm(0);
	write(STDOUT_FILENO, buf, n);
	exit(0);
}
