/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: pw.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sat 13 Dec 2014 10:05:46 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct passwd *buf;
	char *ptr;
	ptr = argv[1];
	buf =  getpwnam(ptr);
	printf("name = %s, passwd = %s, uid = %d, gid = %d, gecos = %s, dir = %s, shell = %s\n", (*buf).pw_name, (*buf).pw_passwd, (*buf).pw_uid, (*buf).pw_gid, (*buf).pw_gecos, (*buf).pw_dir, (*buf).pw_shell);

	exit(0);
}
