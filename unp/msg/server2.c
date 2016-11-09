/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: server2.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 12 Nov 2014 02:12:55 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

void server(int readfd, int writefd)
{
	FILE *fp;
	char *ptr;
	pid_t pid;
	ssize_t n;
	struct mymesg mesg;

	for ( ; ; )
	{
		//read pathname from IPC channel
		mesg.mesg_type = 1;
		if ((n = mesg_recv(readfd, &mesg)) == 0)
		{
			err_msg("pathname missing");
			continue;
		}
		mesg.mesg_data[n] = '\0';

		if ((ptr = strchr(mesg.mesg_data, ' ')) == NULL)
		{
			err_msg("bogus request: %s", mesg.mesg_data);
			continue;
		}

		*ptr++ = 0; // null terminate PID, ptr = pathname
		pid = atol(mesg.mesg_data);
		mesg.mesg_type = pid; // for message back to client

		if ((fp = fopen(ptr, "r")) == NULL)
		{
			snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n, ": can not open, %s\n", strerror(errno));
			mesg.mesg_len = strlen(ptr);
			memmove(mesg.mesg_data, ptr, mesg.mesg_len);
			mesg_send(writefd, &mesg);
		}
		else
		{
			// fopen succeeded: copy file to IPC cahnnel
			while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL)
			{
				mesg.mesg_len = strlen(mesg.mesg_data);
				mesg_send(writefd, &mesg);
			}
			Fclose(fp);
		}

		//send a 0 length message to signify the end
		mesg.mesg_len = 0;
		mesg_send(writefd, &mesg);
	}
}
