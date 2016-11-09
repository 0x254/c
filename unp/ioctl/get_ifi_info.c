/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: get_ifi_info.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 28 Oct 2014 01:37:50 AM CST
* Description:                                                       *
*********************************************************************/
#include "ifi.h"

struct ifi_info *get_ifi_info(int family, int doaliases)
{
	struct ifi_info *ifi, *ifihead, **ifipnext;
	int sockfd, len, lastlen, flags, myflags, idx = 0, hlen = 0;
	char *ptr, *buf, lastname[IFNAMSIZ], *cptr, *haddr, *sdlname;
	struct ifconf ifc;
	struct ifreq *ifr, ifrcopy;
	struct sockaddr_in *sinptr;
	struct sockaddr_in6 *sin6ptr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	lastlen = 0;
	len = 100 * sizeof(struct ifreq); //initial buffer size guess

	for ( ; ; )
	{
		buf = (char *)Malloc(len);
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;
		/* get all interface list */
		if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
		{
			if (errno != EINVAL || lastlen != 0)
				err_sys("ioctl error");
		}
		else
		{
			if (ifc.ifc_len == lastlen)
				break; // success
			lastlen = ifc.ifc_len;
		}
		len += 10 * sizeof(struct ifreq); // increment
		free(buf);
	}
	ifihead = NULL;
	ifipnext  = &ifihead;
	lastname[0] = 0;
	sdlname = NULL;

	for (ptr = buf; ptr < buf + ifc.ifc_len; )
	{
		ifr = (struct ifreq *)ptr;
		switch (ifr->ifr_addr.sa_family)
		{
#ifdef IPV6
			case AF_INET6:
				len = sizeof(struct sockaddr_in6);
				break;
#endif
			case AF_INET:
			default:
				len = sizeof(struct sockaddr);
				break;
		}

		ptr += sizeof(ifr->ifr_name) + len; // for next one in buffer

#ifdef HAVE_SOCKADDR_DL_STRUCT
		/* assumes that AF_LINK precedes AF_INET or AF_INET6 */
		if (ifr->ifr_addr.sa_family == AF_LINK)
		{
			struct sockaddr_dl *sdl = (struct sockaddr_dl *)&ifr->ifr_addr;
			sdlname = ifr->ifr_name;
			idx = sdl->sdl_index;
			haddr = sdl->sdl_data + sdl->sdl_nlen;
			hlen = sdl->sdl_alen;
		}
#endif

		if (ifr->ifr_addr.sa_family != family)
			continue; // ignore if not desired address family

		myflags = 0;
		if ((cptr = strchr(ifr->ifr_name, ':')) != NULL)
			*cptr = 0; // replace colon with null
		if (strncmp(lastname, ifr->ifr_name, IFNAMSIZ) == 0)
		{
			if (doaliases == 0)
				continue; // already processed this interface
			myflags = IFI_ALIAS;
		}
		memcpy(lastname, ifr->ifr_name, IFNAMSIZ);

		/* get interface flags */
		ifrcopy = *ifr;
		Ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
	    flags = ifrcopy.ifr_flags;
		if ((flags & IFF_UP) == 0)
			continue; // ignore if interface not up

		ifi = (struct ifi_info *)Calloc(1, sizeof(struct ifi_info));
		*ifipnext = ifi; // prev points to this new one
		ifipnext = &ifi->ifi_next; // pointer to next one goes here

		ifi->ifi_flags = flags; // IFF_XXX values
		ifi->ifi_myflags = myflags; // IFI_XXX values

		/* get interface mtu */
//#if defined(SIOCGIFMTU) && defined(HAVE_STRUCT_IFREO_IFR_MTU)
#ifdef SIOCGIFMTU
		Ioctl(sockfd, SIOCGIFMTU, &ifrcopy);
		ifi->ifi_mtu = ifrcopy.ifr_mtu;
#else
	    ifi->ifi_mtu = 0;
#endif
		memcpy(ifi->ifi_name, ifr->ifr_name, IFI_NAME); // get the interface name
		ifi->ifi_name[IFI_NAME-1] = '\0';
		/* if the sockaddr_dl is from a different interface, ignore it */

		/* get the interface hwaddr ??? */
		if (sdlname == NULL || strcmp(sdlname, ifr->ifr_name) != 0)
			idx = hlen = 0;
		ifi->ifi_ivalue = idx;
		ifi->ifi_hlen = hlen;
		if (ifi->ifi_hlen > IFI_HADDR)
			ifi->ifi_hlen = IFI_HADDR;
		if (hlen)
			memcpy(ifi->ifi_haddr, haddr, ifi->ifi_hlen);

		switch (ifr->ifr_addr.sa_family)
		{
			case AF_INET:
				/* get the interface ip address */
				sinptr = (struct sockaddr_in *)&ifr->ifr_addr;
				ifi->ifi_addr = (struct sockaddr *)Calloc(1, sizeof(struct sockaddr_in));
				memcpy(ifi->ifi_addr, sinptr, sizeof(struct sockaddr_in));

				/* get the interface bcast address */
#ifdef SIOCGIFBRDADDR
				if (flags & IFF_BROADCAST)
				{
					Ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy);
					sinptr = (struct sockaddr_in *)&ifrcopy.ifr_broadaddr;
					ifi->ifi_brdaddr = (struct sockaddr *)Calloc(1, sizeof(struct sockaddr_in));
					memcpy(ifi->ifi_brdaddr, sinptr, sizeof(struct sockaddr_in));
				}
#endif

				/* get the interface netmask address */
#ifdef SIOCGIFNETMASK
				Ioctl(sockfd, SIOCGIFNETMASK, &ifrcopy);
				sinptr = (struct sockaddr_in *)&ifrcopy.ifr_netmask;
				ifi->ifi_netmask = (struct sockaddr *)Calloc(1, sizeof(struct sockaddr_in));
				memcpy(ifi->ifi_netmask, sinptr, sizeof(struct sockaddr_in));
#endif

					/* get the interface dstaddress */
#ifdef SIOCGIFDSTADDR
				if (flags & IFF_POINTOPOINT)
				{
					Ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
					sinptr = (struct sockaddr_in *)&ifrcopy.ifr_dstaddr;
					ifi->ifi_dstaddr = (struct sockaddr *)Calloc(1, sizeof(struct sockaddr_in));
					memcpy(ifi->ifi_dstaddr, sinptr, sizeof(struct sockaddr_in));
				}
#endif
				break;

			case AF_INET6:
				sin6ptr = (struct sockaddr_in6 *)&ifr->ifr_addr;
				ifi->ifi_addr = (struct sockaddr *)Calloc(1, sizeof(struct sockaddr_in6));
				memcpy(ifi->ifi_addr, sin6ptr, sizeof(struct sockaddr_in6));
#ifdef SIOCGIFDSTADDR
				if (flags & IFF_POINTOPOINT)
				{
					Ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
					sin6ptr = (struct sockaddr_in6 *)&ifrcopy.ifr_dstaddr;
					ifi->ifi_dstaddr = (struct sockaddr *)Calloc(1, sizeof(struct sockaddr_in6));
					memcpy(ifi->ifi_dstaddr, sin6ptr, sizeof(struct sockaddr_in6));
				}
#endif
				break;
			default:
				break;
		}
	}
	free(buf);
	return (ifihead); // pointer to first structure in linked list
}

/* to free the space for get_ifi_info */
void free_ifi_info(struct ifi_info *ifihead)
{
	struct ifi_info *ifi, *ifinext;

	for (ifi = ifihead; ifi != NULL; ifi = ifinext)
	{
		if (ifi->ifi_addr != NULL)
			free(ifi->ifi_addr);
		if (ifi->ifi_brdaddr != NULL)
			free(ifi->ifi_brdaddr);
		if (ifi->ifi_dstaddr != NULL)
			free(ifi->ifi_dstaddr);
		if (ifi->ifi_netmask != NULL)
			free(ifi->ifi_netmask);
		ifinext = ifi->ifi_next; // can not fetch ifi_next after free
		free(ifi); // the ifi_next itself
	}
}
