/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: mesg.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: Wed 08 Oct 2014 11:52:24 AM CST
* Description: 
************************************************************************/
#include "msg.h"
#include "all.h"

ssize_t mesg_send(int fd, struct mymesg *mptr)
{
	return(write(fd, mptr, MESGHDRSIZE + mptr->mesg_len));
}

void Mesg_send(int fd, struct mymesg *mptr)
{
	if (mesg_send(fd, mptr) < 0)
		err_sys("mesg_send error");
}

ssize_t mesg_recv(int fd, struct mymesg *mptr)
{
	size_t len;
	ssize_t n;

	if ((n = Read(fd, mptr, MESGHDRSIZE)) == 0)
		return (0);
	else if (n != MESGHDRSIZE)
		err_quit("message header: expected %d, got %d", MESGHDRSIZE, n);

	if ((len = mptr->mesg_len) > 0)
		if ((n = Read(fd, mptr->mesg_data, len)) != len)
			err_quit("message data: expected %d, got %d", len, n);
	return (len);
}

ssize_t Mesg_recv(int fd, struct mymesg *mptr)
{
	if (mesg_recv(fd, mptr) < 0)
		err_sys("mesg_recv error");
}
