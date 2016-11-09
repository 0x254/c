/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: spent.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 14 Dec 2014 08:42:07 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct spwd *buf;
	setspent();
	buf = getspent();
	printf("name = %s, pwd = %s", (*buf).sp_namp, (*buf).sp_pwdp);
	endspent();
	exit(0);
}
