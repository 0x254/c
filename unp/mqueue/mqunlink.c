/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mqunlink.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 07 Nov 2014 02:28:08 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("Usage: mqunlink <name>");

	Mq_unlink(argv[1]);

	exit(0);
}
