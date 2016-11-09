/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: test1.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 19 Jan 2015 02:41:40 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct termios term;
	if (tcgetattr(STDIN_FILENO, &term) < 0)
		err_sys("tcgetattr error");
	switch(term.c_cflag & CSIZE) {
		case CS5:
			printf("5 bits/byte\n");
			break;
		case CS6:
			printf("6 bits/byte\n");
			break;
		case CS7:
			printf("7 bits/byte\n");
			break;
		case CS8:
			printf("8 bit/byte\n");
			break;
		default:
			printf("unkown bits/byte\n");
	}

	term.c_cflag &= ~CSIZE;
	term.c_cflag |= CS8;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		err_sys("tcsetattr error");

	exit(0);
}
