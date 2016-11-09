/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: web.h
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Sun 26 Oct 2014 11:26:22 PM CST
* Description:                                                       *
*********************************************************************/
#ifndef __web_h
#define __web_h

#include "all.h"

#define MAXFILES 20
#define SERV "80" //port number or server name

struct file
{
	char *f_name;//filename
	char *f_host;//hostname or address
	int f_fd;//descriptor
	int f_flags;//F_xx below
} file[MAXFILES];

#define F_CONNECTING 1 //connect in progress
#define F_READING 2 //connect complete; now reading
#define F_DONE 4 //all done

#define GET_CMD "GET %s HTTP/1.0\r\n\r\n"

//globals
int nconn, nfiles, nlefttoconn, nlefttoread, maxfd;
fd_set rset, wset;

//function prototypes
void home_page(const char *, const char *);
void start_connect(struct file *);
void write_get_cmd(struct file *);

#endif
