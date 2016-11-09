/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: popen.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月05日 星期日 16时19分29秒
* Description: 
************************************************************************/
#include "all.h"

int main(int argc, char **argv)
{
	size_t n;
	char buff[MAXLINE], command[MAXLINE];
	FILE *fp;

	Fgets(buff, MAXLINE, stdin);
	n = strlen(buff);
	if (buff[n-1] == '\n')
		n--;
	snprintf(command, sizeof(command), "cat %s", buff);
	fp = (FILE *)Popen(command, "r");

	while(Fgets(buff, MAXLINE, fp) != NULL)
		Fputs(buff, stdout);

	Pclose(fp);
	exit(0);
}
