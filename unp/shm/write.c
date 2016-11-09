/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: write.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 04 Dec 2014 11:22:30 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int i, id;
	struct shmid_ds buff;
	unsigned char *ptr;

	if (argc != 2)
		err_quit("Usage: write <pathname>");

	id = Shmget(Ftok(argv[1], 0), 0, SVSHM_MODE);
	ptr = Shmat(id, NULL, 0);
	Shmctl(id, IPC_STAT, &buff);

	for (i = 0; i < buff.shm_segsz; i++)
		*ptr++ = i % 256;
	exit(0);
}
