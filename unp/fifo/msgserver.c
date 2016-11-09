/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: msgserver.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: Wed 08 Oct 2014 12:11:45 PM CST
* Description: 
************************************************************************/
#include "msg.h"

void server(int readfd, int writefd)
{
	FILE *fp;
	ssize_t n;
	struct mymesg mesg;

	mesg.mesg_type = 1;
	if ((n = Mesg_recv(readfd, &mesg)) == 0)
		err_quit("pathname missing");
	mesg.mesg_data[n] = '\0';

	if ((fp = fopen(mesg.mesg_data, "r")) == NULL)
	{
		snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) -n, ": can not open %s\n", strerror(errno));
	    mesg.mesg_len = strlen(mesg.mesg_data);
        Mesg_send(writefd, &mesg);
	}
	else
	{
		while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL)
		{
			mesg.mesg_len = strlen(mesg.mesg_data);
			Mesg_send(writefd, &mesg);
		}
		Fclose(fp);
	}
	mesg.mesg_len = 0;
	Mesg_send(writefd, &mesg);
}
