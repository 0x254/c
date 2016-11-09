/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: reentry.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 30 Dec 2014 01:58:48 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void mysh(int signo)
{
	struct passwd *sbuf;
	printf("in signal handler\n");
	if ((sbuf = getpwnam("root")) == NULL)
		err_sys("getpwnam root error");
	alarm(1);
}

int main(int argc, char **argv)
{
	struct passwd *pw;
	signal(SIGALRM, mysh);
	alarm(1);
	for ( ; ; ) {
		if ((pw = getpwnam("canux")) == NULL)
			err_sys("getpwnam canux error");
		if (strcmp(pw->pw_name, "canux") != 0)
			printf("return value corrupted, name = %s\n", pw->pw_name);
	}
	exit(0);
}
