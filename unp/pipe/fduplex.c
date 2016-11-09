/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: fduplex.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月05日 星期日 14时16分37秒
* Description: 
************************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	int fd[2], n;
	char c;
	pid_t childpid;

	Pipe(fd);
	if ((childpid = Fork()) == 0)
	{
		sleep(5);
		if ((n = Read(fd[0], &c, 1)) != 1)
			err_quit("child: read returned %d", n);
		printf("child read %c\n", c);
		Write(fd[0], "c", 1);
		exit(0);
	}

	Write(fd[1], "p", 1);
	if ((n = Read(fd[1], &c, 1)) != 1)
		err_quit("parent: read returned %d", n);
	printf("parent read %c\n", n);
	exit(0);
}
