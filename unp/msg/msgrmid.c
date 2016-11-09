/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: msgrmid.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 08:32:20 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int mqid;

	if (argc != 2)
		err_quit("Usage: rmid <pathname>");

	mqid = Msgget(Ftok(argv[1], 0), 0);
	Msgctl(mqid, IPC_RMID, NULL);

	exit(0);
}
