/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: ttyname.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 20 Jan 2015 02:07:31 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char *name;
	if (isatty(0)) {
		if ((name = ttyname(0)) == NULL)
			name = "undefined";
	} else {
		name = "not a tty";
	}
	printf("fd 0: %s\n", name);

	if (isatty(1)) {
		if ((name = ttyname(1)) == NULL)
			name = "undefined";
	} else {
		name = "not a tty";
	}
	printf("fd 1: %s\n", name);

	if (isatty(2)) {
		if ((name = ttyname(2)) == NULL)
			name = "undefined";
	} else {
		name = "not a tty";
	}
	printf("fd 2: %s\n", name);

	exit(0);
}
