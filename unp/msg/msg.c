/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: msg.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 10:49:02 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

ssize_t mesg_send(int id, struct mymesg *mptr)
{
	return (msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0));
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
	ssize_t n;
	do
	{
	    n = msgrcv(id, &(mptr->mesg_type), MAXMESGDATA, mptr->mesg_type, 0);
	} while((n == -1) && (errno == EINTR));
    
	if (n == -1)
		err_sys("mesg_recv error");

	mptr->mesg_len = n;

	return (n);
}
