/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: wrap_signal.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年08月31日 星期日 19时13分17秒
* Description: the package function of unix system call
************************************************************************/
#include "all.h"

/*
 * signal correlation system call
 */

Sigfunc *Signal(int signo, Sigfunc *func)
{
	Sigfunc *sigfunc;

	if ((sigfunc = signal(signo, func)) == SIG_ERR)
		err_sys("signal error");
	return (sigfunc);
}

void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
	if (sigprocmask(how, set, oldset) == -1)
		err_sys("sigprocmask error");
}

//pause
//alarm
//kill



/*
 * signal correlation c libs
 */

void Sigemptyset(sigset_t *set)
{
	if (sigemptyset(set) == -1)
		err_sys("sigemptyset error");
}

void Sigfillset(sigset_t *set)
{
	if (sigfillset(set) == -1)
		err_sys("sigfillset error");
}

void Sigaddset(sigset_t *set, int signum)
{
	if (sigaddset(set, signum) == -1)
		err_sys("sigaddset error");
}

void Sigdelset(sigset_t *set, int signum)
{
	if (sigdelset(set, signum) == -1)
		err_sys("sigdelset error");
}

int Sigismember(const sigset_t *set, int signum)
{
	int n;

	if (sigismember(set, signum) == -1)
		err_sys("sigismember error");

	return (n);
}

void Sigwait(const sigset_t *set, int *sig)
{
	int n;

	if ((n = sigwait(set, sig)) == 0)
		return;
	errno = n;
	err_sys("sigwait error");
}

void Sigqueue(pid_t pid, int signo, const union sigval value)
{
	if (sigqueue(pid, signo, value) == -1)
		err_sys("sigqueue error");
}

//sleep
