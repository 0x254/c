/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: Inet_ntop.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年08月31日 星期日 14时52分30秒
* Description: 
************************************************************************/

#include "all.h"

/**************sock_pton***********************************/
const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const char *ptr;

	if (strptr == NULL)   /* check for old code */
		err_quit("NULL 3rd argument to inet_ntop");
	if ((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		err_msg("inet_ntop error");   /* sets errno */
	return (ptr);
}



void Inet_pton(int family, const char *strptr, void *addrptr)
{
	int n;
	if ((n = inet_pton(family, strptr, addrptr)) < 0)
		err_msg("inet_pton error for %s", strptr);   /* errno set */
	else if (n == 0)
		err_quit("inet_pton error for %s", strptr);   /* errno not set */
}



/**************sock_ntop***********************************/
/* give net address sockaddr and return string include ip and port */
char *sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
    char portstr[8];
	static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) 
	{
	    case AF_INET: 
		{
			/* turn sockaddr into ip:port */
		    struct sockaddr_in	*sin = (struct sockaddr_in *) sa;
			if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			    return(NULL);
			if (ntohs(sin->sin_port) != 0) 
			{
				snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
			    strcat(str, portstr);
			}
			return(str);
        }		
		/* end sock_ntop */
									  
#ifdef	IPV6
		case AF_INET6: 
		{
		    struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;
		    str[0] = '[';
			if (inet_ntop(AF_INET6, &sin6->sin6_addr, str + 1, sizeof(str) - 1) == NULL)
		        return(NULL);
			if (ntohs(sin6->sin6_port) != 0) 
			{
		        snprintf(portstr, sizeof(portstr), "]:%d", ntohs(sin6->sin6_port));
			    strcat(str, portstr);
			    return (str);
			}
			return (str + 1);
		}
#endif
													   
#ifdef	AF_UNIX
		case AF_UNIX: 
		{
	        struct sockaddr_un	*unp = (struct sockaddr_un *) sa;
			/* OK to have no pathname bound to the socket: happens on
		     * every connect() unless client calls bind() first. */
		    if (unp->sun_path[0] == 0)
			    strcpy(str, "(no pathname bound)");
		    else
			    snprintf(str, sizeof(str), "%s", unp->sun_path);
			return(str);	
		}
#endif
																	  
#ifdef	HAVE_SOCKADDR_DL_STRUCT
        case AF_LINK: 
		{
			struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;
			if (sdl->sdl_nlen > 0)
		        snprintf(str, sizeof(str), "%*s (index %d)", sdl->sdl_nlen, &sdl->sdl_data[0], sdl->sdl_index);
			else
			    snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
			return(str);			
		}
#endif
		default:
		    snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d", sa->sa_family, salen);
		    return(str);				
	}
	return (NULL);
}

char *Sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
	char *ptr;

    if ( (ptr = sock_ntop(sa, salen)) == NULL)
	    err_msg("sock_ntop error");  	/* inet_ntop() sets errno */
	return (ptr);
}

/*****************sock_ntop_host*****************************/
/* give net address sockaddr just return host=ip without port */
char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    char portstr[8];
	static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) 
	{
	    case AF_INET: 
		{
			/* turn sockaddr into ip:port */
		    struct sockaddr_in	*sin = (struct sockaddr_in *) sa;
			if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			    return(NULL);
			return(str);
        }		
		/* end sock_ntop */
									  
#ifdef	IPV6
		case AF_INET6: 
		{
		    struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;
			if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
		        return(NULL);
			return (str);
		}
#endif
													   
#ifdef	AF_UNIX
		case AF_UNIX: 
		{
	        struct sockaddr_un	*unp = (struct sockaddr_un *) sa;
			/* OK to have no pathname bound to the socket: happens on
		     * every connect() unless client calls bind() first. */
		    if (unp->sun_path[0] == 0)
			    strcpy(str, "(no pathname bound)");
		    else
			    snprintf(str, sizeof(str), "%s", unp->sun_path);
			return(str);	
		}
#endif
																	  
#ifdef	HAVE_SOCKADDR_DL_STRUCT
        case AF_LINK: 
		{
			struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;
			if (sdl->sdl_nlen > 0)
		        snprintf(str, sizeof(str), "%*s (index %d)", sdl->sdl_nlen, &sdl->sdl_data[0], sdl->sdl_index);
			else
			    snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
			return(str);			
		}
#endif
		default:
		    snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d", sa->sa_family, salen);
		    return(str);				
	}
	return (NULL);
}

char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
	char *ptr;

    if ( (ptr = sock_ntop_host(sa, salen)) == NULL)
	    err_msg("sock_ntop_host error");  	/* inet_ntop() sets errno */
	return (ptr);
}



/*****************sock_masktop*****************************/
/* format mask address */
const char *sock_masktop(struct sockaddr *sa, uint8_t salen)
{
	static char str[INET6_ADDRSTRLEN];
	unsigned char *ptr = &sa->sa_data[2];
	
	if (salen == 0)
		return ("0.0.0.0");
	else if (salen == 5)
		snprintf(str, sizeof(str), "%d.0.0.0", *ptr);
	else if (salen == 6)
		snprintf(str, sizeof(str), "%d.%d.0.0", *ptr, *(ptr+1));
	else if (salen == 7)
		snprintf(str, sizeof(str), "%d.%d.%d.0", *ptr, *(ptr+1), *(ptr+2));
	else if (salen == 8)
		snprintf(str, sizeof(str), "%d.%d.%d.%d", *ptr, *(ptr+1), *(ptr+2), *(ptr+3));
    else
	    snprintf(str, sizeof(str), "(unknow mask, len = %d, family = %d)", salen, sa->sa_family);

	return (str);
}

