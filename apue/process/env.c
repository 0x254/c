/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: env.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 18 Dec 2014 12:48:03 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	printf("home = %s\n", getenv("HOME"));
	printf("pwd = %s\n", getenv("PWD"));
	printf("lang = %s\n", getenv("LANG"));

	exit(0);
}
