/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: unlink.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 23 Nov 2014 07:45:24 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("Usage: unlink <name>");

	Sem_unlink(argv[1]);
	exit(0);
}
