/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: string.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 11 Dec 2014 01:32:50 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char buf[BUFFSIZE];
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		if (fputs(buf, stdout) == EOF)
			err_sys("fputs error");
	}
	if (ferror(stdin))
		err_sys("stdin error");

	exit(0);
}
