/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: compete.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 22 Dec 2014 02:06:51 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void myprintf(char *str)
{
	char *ptr;
	char c;
	setbuf(stdout, NULL);
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}

int main(int argc, char **argv)
{
	pid_t pid;
	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0)
		myprintf("output from child\n");
	else 
		myprintf("output from parent\n");

	exit(0);
}
