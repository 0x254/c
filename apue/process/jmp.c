/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: jmp.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 18 Dec 2014 01:07:28 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

jmp_buf env;

void mycall()
{
	longjmp(env, 7);
}

int main(int argc, char **argv)
{
	int n;
	if ((n = setjmp(env)) != 0){
		printf("call by longjmp, return %d\n", n);
	    exit(0);
	}
	else
		printf("run itself\n");
	mycall();
	exit(0);
}
