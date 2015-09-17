/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: wrap_sctp.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Wed 24 Sep 2014 08:36:21 PM CST
* Description: 
************************************************************************/
#include "all.h"

int Sctp_recvmsg(int s, void *msg, size_t len, struct sockaddr *from, socklen_t *fromlen, struct sctp_sndrcvinfo *sinfo, int *msg_flags)
{
	int ret;
	if ((ret = sctp_recvmsg(s, msg, len, from, fromlen, sinfo, msg_flags)) < 0)
		err_sys("sctp_recvmsg error");

	return (ret);
}



int Sctp_sendmsg(int s, const void *data, size_t len, struct sockaddr *to, socklen_t tolen, uint32_t ppid, uint32_t flags, uint16_t stream_no, uint32_t timetolive, uint32_t context)
{
	int ret;
	if ((ret = sctp_sendmsg(s, data, len, to, tolen, ppid, flags, stream_no, timetolive, context)) < 0)
	    err_sys("sctp_sendmsg error");

	return (ret);
}



int Sctp_bindx(int sock_fd, struct sockaddr *at, int num, int op)
{
	int ret;
	if ((ret = sctp_bindx(sock_fd, at, num, op)) < 0)
		err_sys("sctp_bindx error");

	return (ret);
}
