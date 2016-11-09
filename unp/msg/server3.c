/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: server3.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Wed 12 Nov 2014 07:57:28 PM CST
* Description:                                                       *
*********************************************************************/
#include "mymsg.h"

void server(int readid, int writeid)
{
	FILE *fp;
	char *ptr;
	ssize_t n;
	struct mymesg mesg;

	Signal(SIGCHLD, sigchld_waitpid);

	for ( ; ; )
    {
	    //read pathname from our well-know queue
	    mesg.mesg_type = 1;
 	    if ((n = mesg_recv(readid, &mesg)) == 0)
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
	    *ptr++ = 0;
	    writeid = atoi(mesg.mesg_data);

 	    if (Fork() == 0)
	    {
		    if ((fp = fopen(ptr, "r")) == NULL)
		    {
			    //error must tell client
			    snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n, ":can not open, %s\n", strerror(errno));
			    mesg.mesg_len = strlen(ptr);
			    memmove(mesg.mesg_data, ptr, mesg.mesg_len);
			    mesg_send(writeid, &mesg);
		    }
		    else
		    {
			    //foen succeeded: cope file to client queue
			    while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL)
			    {
				    mesg.mesg_len = strlen(mesg.mesg_data);
				    mesg_send(writeid, &mesg);
			    }
			    Fclose(fp);
		    }

		    //send a 0 length message to signify the end
		    mesg.mesg_len = 0;
		    mesg_send(writeid, &mesg);
		    exit(0);
	    }
	    //parent just loops around
	}
}
