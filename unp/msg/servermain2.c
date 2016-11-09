/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: servermain2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 12 Nov 2014 02:01:36 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

void server(int, int);

int main(int argc, char **argv)
{
	int msqid;
	msqid = Msgget(MQ_KEY1, SVMSG_MODE | IPC_CREAT);
	server(msqid, msqid);
	exit(0);
}
