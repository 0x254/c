/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: msg.h
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: Wed 08 Oct 2014 11:48:43 AM CST
* Description: 
************************************************************************/
#ifndef _msg_h
#define _msg_h

#include "all.h"

#define MAXMESGDATA (PIPE_BUF - 2*sizeof(long))

#define MESGHDRSIZE (sizeof(struct mymesg) - MAXMESGDATA)

struct mymesg
{
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
};

ssize_t mesg_send(int, struct mymesg *);
void Mesg_send(int, struct mymesg *);
ssize_t mesg_recv(int, struct mymesg *);
ssize_t Mesg_recv(int, struct mymesg *);

#endif
