/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: clientmain2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 12 Nov 2014 02:11:21 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

void client(int, int);

int main(int argc, char **argv)
{
	int msqid;
	msqid = Msgget(MQ_KEY1, 0);
	client(msqid, msqid);
	exit(0);
}
