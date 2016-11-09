/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: grent.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 14 Dec 2014 09:00:59 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct group *buf;
	setgrent();
	buf = getgrent();
	printf("name = %s, pwd = %s, gid = %d, mem = %s\n", (*buf).gr_name, (*buf).gr_passwd, (*buf).gr_gid, *(*buf).gr_mem);
	endgrent();
	exit(0);
}
