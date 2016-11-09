/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: start_connect.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 27 Oct 2014 10:30:49 AM CST
* Description:                                                       *
*********************************************************************/
#include "web.h"

void start_connect(struct file *fptr)
{
	int fd, flags, n;
	struct addrinfo *ai;

	ai = (struct addrinfo *)host_serv(fptr->f_host, (char *)SERV, 0, SOCK_STREAM);
	fd = Socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	fptr->f_fd = fd;
	printf("start_connect for %s, fd %d\n", fptr->f_name, fd);

	//set socket nonblocking
	flags = Fcntl(fd, F_GETFL, 0);
	Fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	//initiate nonblocking connect to the server
	if ((n = connect(fd, ai->ai_addr, ai->ai_addrlen)) < 0)
	{
		if (errno != EINPROGRESS)
			err_sys("nonblocking connect error");
		fptr->f_flags = F_CONNECTING;
		FD_SET(fd, &rset);
		FD_SET(fd, &wset);
		if (fd > maxfd)
			maxfd = fd;
	}
	else if (n >= 0) // connect is already done
		write_get_cmd(fptr); // write the GET command
}
