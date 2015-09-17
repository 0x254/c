/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: mysignal.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年09月01日 星期一 10时08分05秒
* Description: 
************************************************************************/
#include "all.h"

/*****************signal******************/
/* realise the function signal myself , but we use the systemcall */
#if 0
Sigfunc * signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;   /* sunOS */
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;   /* SVR4 BSD */
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}

/************** for real time signal *************/
typedef void Sigfunc_rt(int, siginfo_t *, void *)

Sigfunc_rt *signal_rt(int signo, Sigfunc_rt *func, sigset_t *mask)
{
	struct sigaction act, oact;
	act.sa_sigaction = func;
	act.sa_mask = *mask;
	act.sa_flags = SA_SIGINFO;
	if (signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		return ((Sigfunc_rt *) SIG_ERR);
	return (oact.sa_sigaction);
}
#endif

/**************wait**************/
void sigchld_wait(int signo)
{
	pid_t pid;
	int stat;

	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}



/*************waitpid***************/
void sigchld_waitpid(int signo)
{
	pid_t pid;
	int stat;

	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}
