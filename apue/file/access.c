/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: access.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 09 Dec 2014 12:07:03 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("Usage: access <pathname>");

	if (access(argv[1], F_OK) == -1)
		err_ret("file exist error\n");
	else 
		printf("file exist\n");
	if (access(argv[1], R_OK) == -1)
		err_ret("read access error\n");
	else
		printf("read access\n");
	if (access(argv[1], W_OK) == -1)
		err_ret("write access error\n");
	else
		printf("write access\n");
	if (access(argv[1], X_OK) == -1)
		err_ret("excute access error\n");
	else
		printf("excute access\n");

	exit(0);
}
