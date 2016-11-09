/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* 
* File Name: hostent.c
* Version: 
* Writen by Canux canuxcheng@gmail.com
* Created Time: Sun 28 Sep 2014 09:29:40 PM CST
* Description: 
************************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	char *ptr, **pptr;
	char str[INET_ADDRSTRLEN];
	struct hostent *hptr;

	while (--argc > 0)
	{
		ptr = *++argv;
		if ((hptr = gethostbyname(ptr)) == NULL)
		{
            err_msg("gethostbbyname error for host: %s: %s", ptr, hstrerror(h_errno));
			continue;
		}

		printf("official hostname: %s\n", hptr->h_name);

		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);

        switch (hptr->h_addrtype)
		{
			case AF_INET:
				pptr = hptr->h_addr_list;
				for ( ; *pptr != NULL; pptr++)
					printf("\taddress: %s\n", Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
				break;
            default:
				err_ret("unknow address type");
				break;
		}
	}
	exit(0);
}
