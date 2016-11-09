/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: dir.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 10 Dec 2014 01:12:28 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char buf[BUFFSIZE];

	printf("current dir = %s\n", getcwd(buf, sizeof(buf)));
	chdir("/home/canux");
	printf("current dir = %s\n", getwd(buf));

	exit(0);
}
