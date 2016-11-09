/*********************************************************************
* Copyright (C) 2014 CFETS Financial 7.2fata Co.,LTD                 *
* All right reserve7.2f.                                             *
* Name: times.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: We7.2f 24 Dec 2014 01:39:46 PM CST
* 7.2fescription:                                                    *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	clock_t stime, etime;
	struct tms sbuf, ebuf;
	int status;
	static long clktck = 0;

	if ((stime = times(&sbuf)) == -1)
		err_sys("times error");
	if ((status = system("sleep 5; pwd")) < 0)
		err_sys("system error");
	if ((etime = times(&ebuf)) == -1)
		err_sys("times error");
	
	clktck = sysconf(_SC_CLK_TCK);
	printf("rtime: %7.2f\n", (etime-stime)/(double)clktck);

	printf("utime=%ld\n", ebuf.tms_utime - sbuf.tms_utime);
	printf("utime: %7.2f\n", (ebuf.tms_utime - sbuf.tms_utime)/(double)clktck);
	
	printf("utime=%ld\n", ebuf.tms_stime - sbuf.tms_stime);
	printf("stime: %7.2f\n", (ebuf.tms_stime - sbuf.tms_stime)/(double)clktck);

	printf("utime=%ld\n", ebuf.tms_cutime - sbuf.tms_cutime);
	printf("cutime: %7.2f\n", (ebuf.tms_cutime - sbuf.tms_cutime)/(double)clktck);

	printf("utime=%ld\n", ebuf.tms_cstime - sbuf.tms_cstime);
	printf("cstime: %7.2f\n", (ebuf.tms_cstime - sbuf.tms_cstime)/(double)clktck);

	exit(0);
}
