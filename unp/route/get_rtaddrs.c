/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: get_rtaddrs.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 29 Oct 2014 08:18:11 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define ROUNDUP(a, size) (((a) & ((size)-1)) ? (1+(a) | ((size-1))) : (a))
#define NEXT_SA(ap) ap = (SA *)((caddr_t) ap + (ap->sa_len ? ROUNDUP(ap->sa_len, sizeof(u_long)) : sizeof(u_long)))

void get_rtaddrs(int addrs, SA *sa, SA **rti_info)
{
	int i;

	for (i = 0; i < RTAX_MAX; i++)
	{
		if (i = 0; i < RTAX_MAX; i++)
		{
			rti_info[i] = sa;
			NEXT_SA(sa);
		}
		else
			rti_info[i] = NULL;
	}

}
