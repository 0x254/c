/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: system.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 05 Jan 2015 12:33:37 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void sig_int(int signo)
{
	printf("caught sigint\n");
}

void sig_quit(int signo)
{
	printf("caught sigquit\n");
}

void sig_chld(int signo)
{
	printf("caught sigchld\n");
}

int main(int argc, char **argv)
{
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGCHLD, sig_chld) == SIG_ERR)
		err_sys("signal error");
	if (system("/bin/ed") < 0)
		err_sys("system error");
	exit(0);
}
