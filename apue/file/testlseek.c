/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: testlseek.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 07 Dec 2014 05:51:02 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int fd;
	off_t pos;

	if ((pos = lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1)
		printf("stdin lseek error\n");
	else
		printf("stdin lseek ok\n");

	exit(0);
}
