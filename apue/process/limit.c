/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: limit.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 18 Dec 2014 12:55:33 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct rlimit ml;

	getrlimit(RLIMIT_AS, &ml);
	printf("%lld, %lld\n", (int)ml.rlim_cur, (int)ml.rlim_max);
	exit(0);
}
