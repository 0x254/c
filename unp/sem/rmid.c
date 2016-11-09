/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: rmid.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Fri 28 Nov 2014 09:35:42 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int semid;

	if (argc != 2)
		err_quit("Usage: rmid <pathname>");
	semid = Semget(Ftok(argv[1], 0), 0, 0);
	Semctl(semid, 0, IPC_RMID);

	exit(0);
}
