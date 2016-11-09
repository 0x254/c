/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: fopen.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 12 Dec 2014 01:05:42 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

void mystream(char *s, FILE *fp)
{
	printf("stream = %s, ", s);
	if (fp->_IO_file_flags & _IO_LINE_BUF)
		printf("line buffered\n");
	else if (fp->_IO_file_flags & _IO_UNBUFFERED)
		printf("unbuffered\n");
	else
		printf("full buffered\n");
}

int main(int argc, char **argv)
{
    fputs("clean stdout\n", stdout);
	getchar();
	fputs("clean stderr\n", stderr);

	mystream("stdin", stdin);
	mystream("stdout", stdout);
	mystream("stderr", stderr);

	exit(0);
}
