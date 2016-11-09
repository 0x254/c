/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: home_page.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 26 Oct 2014 11:39:59 PM CST
* Description:                                                       *
*********************************************************************/
#include "web.h"
void home_page(const char *host, const char *fname)
{
	int fd, n;
	char line[MAXLINE];
	
	fd = tcp_connect(host, SERV); // blocking connect
	n = snprintf(line, sizeof(line), GET_CMD, fname);
	Writen(fd, line, n);
	for ( ; ; )
	{
		if ((n = Read(fd, line, MAXLINE)) == 0)
			break; //server closed connection
		printf("read %d bytes of home page\n", n);
		//process the data
	}
	printf("end-of-file on home page\n");
	Close(fd);
}
