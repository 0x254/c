/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: ifi.h
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 28 Oct 2014 01:26:43 AM CST
* Description:                                                       *
*********************************************************************/
#ifndef __ifi_h
#define __ifi_h

#include "all.h"

#define IFI_NAME 16 /* same as IFNAMSIZ in <net/if.h> */
#define IFI_HADDR 8 /* allow for 64bit in future */

struct ifi_info
{
	short ifi_myflags; /* our own IFI_XXX flags */
	u_char ifi_haddr[IFI_HADDR]; /* hardware address */
	u_short ifi_hlen; /* bytes in hardware address: 0, 6, 8 */
	short ifi_ivalue; /* ivalue, interface index */
	
	char ifi_name[IFI_NAME]; /* interface name, null-terminated */
	int ifi_mtu; /* interface MTU */
	short ifi_flags; /* IFF_XXX constants from <net/if.h> */
	struct sockaddr *ifi_addr; /* primary address = ip */
	struct sockaddr *ifi_brdaddr; /* broadcast address = bcast */
	struct sockaddr *ifi_netmask; /* netmask address */
	struct sockaddr *ifi_dstaddr; /* destination address = mask */

	struct ifi_info *ifi_next; /* next of  these structures */
};

#define IFI_ALIAS 1 /* ifi_addr is an alias */

struct ifi_info *get_ifi_info(int, int);
void free_ifi_info(struct ifi_info *);

#endif 
