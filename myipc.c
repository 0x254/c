*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: myipc.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 06 Nov 2014 02:03:04 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

/* for posix name */
char *px_ipc_name(const char *name)
{
	char *dir, *dst, *slash;

	if ((dst = malloc(PATH_MAX)) == NULL)
		return (NULL);

	// can override default directory with environment variable
	if ((dir = getenv("PX_IPC_NAME")) == NULL)
	{
#ifdef POSIX_IPC_PREFIX
		dir = POSIX_IPC_PREFIX; 
#else
		dir = "/"; // for linux
#endif
	}
	// dir must end in a slash
	slash = (dir[strlen(dir) - 1] == '/') ? "" : "/";
	snprintf(dst, PATH_MAX, "%s%s%s", dir, slash, name);

	return (dst); // caller can free this pointer
}

char *Px_ipc_name(const char *name)
{
	char *ptr;

	if ((ptr = px_ipc_name(name)) == NULL)
		err_sys("px_ipc_name error");

	return (ptr);
}
