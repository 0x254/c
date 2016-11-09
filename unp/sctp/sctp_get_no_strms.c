/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: sctp_getnostrms.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Wed 24 Sep 2014 10:54:40 PM CST
* Description: 
************************************************************************/
#include "all.h"

int sctp_get_no_strms(int sock_fd, struct sockaddr *to, socklen_t tolen)
{

    socklen_t retsz;
	struct sctp_status status;

	retsz = sizeof(status);
	bzero(&status, retsz);

	status.sstat_assoc_id = sctp_address_to_associd(sock_fd, to, tolen);
	
	Getsockopt(sock_fd, IPPROTO_SCTP, SCTP_STATUS, &status, &retsz);
    
	return(status.sstat_outstrms);
}
