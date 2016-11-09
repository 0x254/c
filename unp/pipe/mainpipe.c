/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: mainpipe.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月04日 星期六 12时06分36秒
* Description: 
************************************************************************/
#include <all.h>

void client(int, int);
void server(int, int);

int main(int argc, char **argv)
{
	int pipe1[2], pipe2[2];
	pid_t childpid;

	Pipe(pipe1);
	Pipe(pipe2);

	if ((childpid = Fork()) == 0) //child
	{
		Close(pipe1[1]);
		Close(pipe2[0]);

		server(pipe1[0],pipe2[1]);
		exit(0);
	}

	//parent
	Close(pipe1[0]);
	Close(pipe2[1]);

	client(pipe2[0], pipe1[1]);

	Waitpid(childpid, NULL, 0);
	exit(0);
}
