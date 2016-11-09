/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: cs1.h
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Thu 04 Dec 2014 01:20:39 PM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

#define MESGSIZE 256
#define NMESG 16

struct shmstruct {
	sem_t mutex;
	sem_t nempty;
	sem_t nstored;
	int nput;
	long noverflow;
	sem_t noverflowmutex;
	long msgoff[NMESG];
	char msgdata[NMESG * MESGSIZE];
};
