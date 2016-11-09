/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: write_get_cmd.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 26 Oct 2014 11:44:10 PM CST
* Description:                                                       *
*********************************************************************/
#include "web.h"

void write_get_cmd(struct file *fptr)
{
	int n;
	char line[MAXLINE];

	n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);
	Writen(fptr->f_fd, line, n);
	printf("wrote %d bytes for %s\n", n, fptr->f_name);

	fptr->f_flags = F_READING; //clears F_CONNECTING
	FD_SET(fptr->f_fd, &rset); // will read server's reply
	if (fptr->f_fd > maxfd)
	    maxfd = fptr->f_fd;
}
