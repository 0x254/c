/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: msgctl.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Tue 11 Nov 2014 10:52:52 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int msqid;
	struct msqid_ds info;
	struct msgbuf buf;

	msqid = Msgget(IPC_PRIVATE, IPC_CREAT | SVMSG_MODE);

	buf.mtype = 1;
	buf.mtext[0] = 1;
	Msgsnd(msqid, &buf, 1, 0);

	Msgctl(msqid, IPC_STAT, &info);
	printf("read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n", info.msg_perm.mode & 0777, (ulong) info.msg_cbytes, (ulong) info.msg_qnum, (ulong) info.msg_qbytes);

	system("ipcs -q");

	Msgctl(msqid, IPC_RMID, NULL);
	exit(0);
}
