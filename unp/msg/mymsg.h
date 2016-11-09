/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: msg.h
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: Wed 08 Oct 2014 11:48:43 AM CST
* Description: 
************************************************************************/
#ifndef _mymsg_h
#define _mymsg_h

#include "all.h"

#define MQ_KEY1 1234L
#define MQ_KEY2 2345L

#define MAXMESGDATA (PIPE_BUF - 2*sizeof(long))

#define MESGHDRSIZE (sizeof(struct mymesg) - MAXMESGDATA)

struct mymesg
{
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
};

#endif
