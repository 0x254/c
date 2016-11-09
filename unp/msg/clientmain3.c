/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: servermain3.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 12 Nov 2014 02:53:52 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

int main(int argc, char **argv)
{
	int readid, writeid;

	//server must create its well-know queue
	writeid = Msgget(MQ_KEY1, 0);

	//we create our own private queue
	readid = Msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);

	client(readid, writeid);

	//and delete our private queue
	Msgctl(readid, IPC_RMID, NULL);

	exit(0);
}
