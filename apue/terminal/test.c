/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: test.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 19 Jan 2015 01:33:15 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct termios term;
	long vdisable;
	if (isatty(STDIN_FILENO) == 0)
		err_quit("standard input is not a terminal device");
	if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) < 0)
		err_quit("fpathconf error or _posix_vdisable not in effect");
	if (tcgetattr(STDIN_FILENO, &term) < 0)
		err_sys("tcgetattr error");

	term.c_cc[VINTR] = vdisable;
	term.c_cc[VEOF] = 2;

	sleep(10);

	exit(0);
}
