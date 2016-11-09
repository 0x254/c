/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: atexit.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 16 Dec 2014 01:11:01 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void first()
{
	printf("first\n");
}

void second()
{
	printf("sedond\n");
}

int main(int argc, char **argv)
{
	atexit(first);
	atexit(second);
	atexit(first);
	printf("main done\n");
	return;
}
