/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: servermain.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 10:14:39 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

void server(int, int);

int main(int argc, char **argv)
{
	int readid, writeid;

	readid = Msgget(MQ_KEY1, SVMSG_MODE | IPC_CREAT);
	writeid = Msgget(MQ_KEY2, SVMSG_MODE | IPC_CREAT);

	server(readid, writeid);

	exit(0);
}
