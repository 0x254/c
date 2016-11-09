/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: temp.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 12 Dec 2014 01:06:34 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	printf("tmpnam = %s\n", tmpnam(NULL));
    printf("tempnam = %s\n", tempnam("/home/canux", "canux"));

	char buf[] = "mktempXXXXXX";
	printf("mktemp = %s\n", mktemp(buf));

	char buf1[] = "mkstempXXXXXX";
	printf("fd = %d\n", mkstemp(buf1));
	exit(0);
}
