/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: time.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 16 Dec 2014 12:53:00 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	struct timeval tv;
	struct tm *mytm;
	time_t *mt;

	printf("time = %d\n", time(NULL));
	gettimeofday(&tv, NULL);
	printf("sec = %d, usec = %d\n", tv.tv_sec, tv.tv_usec);

	time(mt);
	mytm = gmtime(mt);
	printf("sec = %d, min = %d, hour = %d\n", (*mytm).tm_sec, (*mytm).tm_min, (*mytm).tm_hour);
	mytm = localtime(mt);
	printf("sec = %d, min = %d, hour = %d\n", (*mytm).tm_sec, (*mytm).tm_min, (*mytm).tm_hour);

	printf("mktime = %d\n", mktime(mytm));
	printf("asctime = %s\n", asctime(mytm));
	printf("ctime = %s\n", ctime(mt));

	exit(0);

}
