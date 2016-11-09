/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: msgclient.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: Wed 08 Oct 2014 12:06:29 PM CST
* Description: 
************************************************************************/
#include "mymsg.h"

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	struct mymesg mesg;

	Fgets(mesg.mesg_data, MAXMESGDATA, stdin);
	len = strlen(mesg.mesg_data);
	if (mesg.mesg_data[len-1] == '\n')
		len--;
	mesg.mesg_len = len;
	mesg.mesg_type = 1;
	mesg_send(writefd, &mesg);
	while ((n = mesg_recv(readfd, &mesg)) > 0)
		Write(STDOUT_FILENO, mesg.mesg_data, n);
}
