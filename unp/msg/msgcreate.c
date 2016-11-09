/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: msgcreate.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 08:11:02 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int c, oflag, mqid;

	oflag = SVMSG_MODE | IPC_CREAT;
	while ((c = Getopt(argc, argv, "e")) != -1)
	{
		switch (c)
		{
			case 'e':
				oflag |= IPC_EXCL;
				break;
		}
	}
	if (optind != argc - 1)
		err_quit("Usage: msgcreate [-e] <pathname>");

	mqid = Msgget(Ftok(argv[optind], 0), oflag);
	exit(0);
}
