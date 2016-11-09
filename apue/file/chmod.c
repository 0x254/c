/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: chmod.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 09 Dec 2014 01:14:51 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct stat buf;
	stat("/tmp/foo", &buf);
	chmod("/tmp/foo", buf.st_mode & ~0777);
    chmod("/tmp/bar", 0666);

	exit(0);
}
