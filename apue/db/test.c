/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: test.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 22 Jan 2015 01:44:13 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
    DBM *db;
	datum key, content, first, fetchkey, fetch;

	if ((db = dbm_open("testdb", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) == NULL)
		err_sys("dbm_open error");

	key.dptr = "alpha";
	key.dsize = strlen(key.dptr);
	content.dptr = "data for alpha";
	content.dsize = strlen(content.dptr);
	if (dbm_store(db, key, content, DBM_INSERT) != 0)
		err_quit("dbm_store error for alpha");

	first = dbm_firstkey(db);
    printf("dbm_firstkey = %s\n", first.dptr);

	fetchkey.dptr = "alpha";
	fetchkey.dsize = strlen(fetch.dptr);
	fetch = dbm_fetch(db, fetchkey);
	printf("dbm_fetch = %s\n", fetch.dptr);

	dbm_close(db);
	exit(0);
}
