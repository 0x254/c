/*******************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All rights reserved
* File name:

* Version:
* Writen by Canux canuxcheng@gmail.com
* Create time:
* Description:

* Modified version:
* Modified author:
* Modified time:
* Modified description:
*******************************************************************/

#include "all.h"

int daemon_proc;   /* set nonzero by daemon_init() */

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */ 
static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
    int errno_save, n;
    char buf[MAXLINE + 1];

    errno_save = errno;   /* value caller might want printed */

#ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXLINE, fmt, ap);   /* safe */
#else
    vsprintf(buf, fmt, ap);   /* not safe */
#endif

    n = strlen(buf);
    if (errnoflag)   /* related to system call */
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    strcat(buf, "\n");

    if (daemon_proc)   /* set nonzero by daemon_init() */
    {
        syslog(level, "%s", buf);   /* write to system log */
    }
    else
    {
        fflush(stdout);    /* in case stdout and stderr are the same */
        fputs(buf, stderr);
        fflush(stderr);
    }
    return;
}

/* Nonfatal error related to system call 
 * Print message and return */
void err_ret(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);
    return;   /* continue to process the program */
}

/* Fatal error related to system call
 * Print message and terminate */
void err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);   /* exit the whole program */
}

/* Fatal error related to system call
 * Print message, dump core, and terminate */
void err_dump(const char *fmt, ...)
{
    va_list ap;
 
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    abort();   /* dump core and terminate */
    exit(1);   /* shouldn't get here */
}


/* Nonfatal error unrelated to system call 
 * Print message and return */
void err_msg(const char *fmt, ...)
{
    va_list ap;
   
    va_start(ap, fmt);
    err_doit(0, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}

/* fatal error unrelated to system call
 * error code passed as explict parameter
 * print message and terminate
 */
void err_exit(int error, const char *fmt,...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, error, fmt, ap);
	va_end(ap);
	exit(1);
}

/* Fatal error unrelated to system call
 * Print message and terminate */
void err_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);   /* exit the whole program */
}
 
