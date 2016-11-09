/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: name.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 15 Dec 2014 12:38:50 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char name[BUFFSIZE];
	struct utsname buf;

	gethostname(name, sizeof(name));
	printf("name = %s\n", name);

	if ((uname(&buf)) >= 0)
	    printf("sysname = %s\nnodename = %s\nrelease = %s\nversion = %s\nmachine = %s\n", buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
	else
		err_sys("uname error");

	exit(0);
}
