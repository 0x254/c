/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: sctp_addr_to_associd.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Wed 24 Sep 2014 10:59:58 PM CST
* Description: 
************************************************************************/
#include "all.h"

sctp_assoc_t sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen)
{
	struct sctp_paddrparams sp;
	int siz;

	siz = sizeof(sp);
	bzero(&sp,siz);
	
	memcpy(&sp.spp_address, sa, salen);
	sctp_opt_info(sock_fd,0, SCTP_PEER_ADDR_PARAMS, &sp, &siz);
	
	return(sp.spp_assoc_id);
}
