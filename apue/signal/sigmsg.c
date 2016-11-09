/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: sigmsg.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 06 Jan 2015 11:25:57 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char *s;
	psignal(SIGSTOP, "sigstop");
	s = strsignal(SIGKILL);
	printf("sigkill: %s\n", s);
	exit(0);
}
