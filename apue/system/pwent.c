/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: pwent.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 14 Dec 2014 08:20:34 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct passwd *buf;
	setpwent();
	buf = getpwent();
	printf("name = %s, passwd = %s, uid = %d, git = %d, gecos = %s, dir = %s, shell = %s", (*buf).pw_name, (*buf).pw_passwd, (*buf).pw_uid, (*buf).pw_gid, (*buf).pw_gecos, (*buf).pw_dir, (*buf).pw_shell);
	endpwent();

	exit(0);

}
