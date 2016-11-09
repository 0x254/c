/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: umask.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 09 Dec 2014 12:38:04 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	umask(0);
	creat("/tmp/foo", 0777);
	umask(0777);
	creat("/tmp/bar", 0777);

	exit(0);
}
