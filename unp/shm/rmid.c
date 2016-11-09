/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: rmid.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 04 Dec 2014 10:39:30 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int id;

	if (argc != 2)
		err_quit("Usage: rmid <pathname>");

	id = Shmget(Ftok(argv[1], 0), 0, SVSHM_MODE);
	Shmctl(id, IPC_RMID, NULL);
	exit(0);
}
