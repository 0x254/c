/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: nocompete.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 22 Dec 2014 02:21:26 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int label;

void myprintf(char *str)
{
	char *ptr;
	char c;
    setbuf(stdout, NULL);
	for (ptr = str; (c = *ptr++) != 0; ) {
		putc(c, stdout);
	}
}

void waitparent()
{
	while (label == 0) 
		sleep(1);
	if (label == 1)
	    return;
}

void tellchild()
{
	label = 1;
	return;
}

int main(int argc, char **argv)
{
	pid_t pid;
	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0) {
		waitparent();
		myprintf("output from child\n");
	}
	else {
		myprintf("output from parent\n");
		tellchild();
	}
	exit(0);
}
