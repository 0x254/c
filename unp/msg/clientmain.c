/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: clientmain.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 10:16:06 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

void client(int, int);

int main(int argc, char **argv)
{
	int readid, writeid;

	writeid = Msgget(MQ_KEY1, 0);
	readid = Msgget(MQ_KEY2, 0);

	client(readid, writeid);

	Msgctl(readid, IPC_RMID, NULL);
	Msgctl(writeid, IPC_RMID, NULL);

	exit(0);
}
