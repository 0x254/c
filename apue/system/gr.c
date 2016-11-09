/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: gr.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 14 Dec 2014 08:52:37 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct group *buf;
	buf = getgrnam("canux");
	printf("name = %s, pwd = %s, gid = %d, mem = %s\n", (*buf).gr_name, (*buf).gr_passwd, (*buf).gr_gid, *(*buf).gr_mem);

	exit(0);
}
