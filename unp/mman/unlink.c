/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: unlink.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 02 Dec 2014 10:55:21 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("Usage: unlink <name>");

	Shm_unlink(argv[1]);

	exit(0);
}
