/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: signal.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 30 Dec 2014 10:53:46 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void mysh(int signum)
{
	if (signum = SIGUSR1)
		printf("received sigusr1\n");
	else if (signum = SIGUSR2)
		printf("received sigusr2\n");
	else 
		err_dump("received signal %d\n", signum);
}

int main(int argc, char **argv)
{
	if (signal(SIGUSR1, mysh) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGUSR2, mysh) == SIG_ERR)
		err_sys("signal error");
	for ( ; ; )
		pause();

	exit(0);
}
