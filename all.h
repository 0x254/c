/*********************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD                      *
* All right reserved.                                                *
* Name: all.h
* Author: Canux canuxcheng@gmail.com                                   *
* Version: V1.0                                                      *
* Time: Tue 28 Oct 2014 08:57:25 PM CST
* Description:                                                       *
*********************************************************************/

/* include all.h */
/* Our own header. Tabs are set for 4 spaces, not 8 */

#ifndef __all_h
#define __all_h

#include <unistd.h>   /* */
#include <arpa/inet.h>   /* inet(3) functions */
#include <netinet/in.h>   /* sockaddr_in{} and other Internet defns */
#include <netinet/sctp.h> /* note if sctp does not exist we blow up :> */

#include <sys/types.h>   /* basic system data types */
#include <sys/socket.h>   /* basic socket definitions */
#include <sys/time.h>   /* timeval{} for select */
#include <sys/resource.h> /* for resource limit function */
#include <sys/stat.h>   /* for S_xxx file mode constants */
#include <sys/uio.h>   /* for iovec{} and readv/writev */
#include <sys/wait.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/utsname.h> /* for uname */
#include <sys/times.h> /* for times */

#include <strings.h>
#include <time.h>   /* timespec{} for pselect */
#include <stdarg.h>  /* ISO C variable arguments */   
#include <syslog.h>   /* */
#include <stdio.h>   /* */
#include <errno.h>   /* */
#include <string.h>   /* */
#include <netdb.h>
#include <stdlib.h>
#include <utime.h> /* for utime */
#include <dirent.h> /* for directory */
#include <pwd.h> /* for passwd */
#include <shadow.h> /* for shador */
#include <grp.h> /* for group */

#include <sys/ioctl.h> /* for ioctl */
#include <fcntl.h>   /* for fcntl */
#include <sys/select.h>   /* for select() */
#include <poll.h>   /* for poll() */
#include <sys/un.h>   /* for Unix domain sockets */
#include <net/if.h> /* for ioctl interface */
#include <net/if_arp.h> /* for ioctl arp */
#include <net/route.h> /* for ioctl route */
#include <linux/pfkeyv2.h> /* for AF_KEY */
#include <setjmp.h> /* for sig/setmmp and sig/longjmp */

#include <signal.h> /* for signal */
#include <pthread.h> /* for thread */
#include <mqueue.h> /* for posix message queue */
#include <semaphore.h> /* for posix semaphore */
#include <sys/mman.h> /* for posix shared memory */

#include <sys/ipc.h> /* for system v ipc */
#include <sys/msg.h> /* for system v message queue */
#include <sys/sem.h> /* for system v semaphore */
#include <sys/shm.h> /* for system v shared memory */

#include <termios.h> /* for terminal */

#include <gdbm-ndbm.h> /* for ndbm */

/* POSIX requires that an #include of <poll.h> DefinE INFTIM, but many
 * systems still DefinE it in <sys/stropts.h>.  We don't want to include
 * all the STREAMS stuff if it's not needed, so we just DefinE INFTIM here.
 * This is the standard value, but there's no guarantee it is -1. */
#include <sys/stropts.h>
#ifndef INFTIM
#define INFTIM (-1)   /* infinite poll timeout */
/* $$.Ic INFTIM$$ */
#ifndef INFTIM_UNPH
#define INFTIM_UNPH   /* tell unpxti.h wo defined it */
#endif
#endif

/* the limit of struct pollfd */
#include <limits.h>
#ifndef OPEN_MAX
#define OPEN_MAX 256
#endif

#ifndef INADDR_NONE
/* $$.Ic INADDR_NONE$$ */
#define INADDR_NONE 0xffffffff   /* should have been in <netinet/in.h> */
#endif

#ifndef SHUT_RD   /* these three POSIX names are new */
#define SHUT_RD 0   /* shutdown for reading */
#define SHUT_WR 1   /* shutdown for writing */
#define SHUT_RDWR 2   /* shutdown for reading and writing */
/* $$.Ic SHUT_RD$$ */
/* $$.Ic SHUT_WR$$ */
/* $$.Ic SHUT_RDWR$$ */
#endif

/* *INDENT-OFF* */
#ifndef INET_ADDRSTRLEN
/* $$Ic INET_ADDRSTRLEN$$ */
#define INET_ADDRSTRLEN 16   /* "ddd.ddd.ddd.ddd\0" 1234567890123456 */
#endif

/* Define following even if IPv6 not supported, so we can always allocate an adequately sized buffer without $ifdefs in the code */
#ifndef INET6_ADDRSTRLEN
/* $$.Ic INET6_ADDRSTRLEN$$ */
#define INET6_ADDRSTRLEN 46   /* max size of IPv6 address string:
122 "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx" or
123 "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\0"
124 1234567890123456789012345678901234567890123456 */
#endif
/* *INDENT-ON* */

/* macro */
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b)) 

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many kernels still $define it as 5, while actually supporting many more */
#define LISTENQ 1024   /* 2nd argument to listen() */

/* Miscellaneous constants */
#define MAXLINE 4096   /* max text line length */
#define BUFFSIZE 8192   /* buffer size for reads and writes */
#define MAXSOCKADDR 128   /* max socket address structure size */ 

/* Define some port number that can be used for our examples */
#define SERV_PORT 9877   /* TCP and UDP client-servers */
#define SERV_PORT_STR "9877"   /* TCP and UDP clientservers */
#define SCTP_PDAPI_INCR_SZ 65535   /* increment size for pdapi when adding buf space */ 
#define SCTP_PDAPI_NEED_MORE_THRESHOLD 1024   /* need more space threshold */
#define SERV_MAX_SCTP_STRM 10   /* normal maximum streams */
#define SERV_MOR_STRMS_SCTP 20   /* larger number of streams */
/* $$.ix [LISTENQ]~constant,~definition~of$$ */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */
/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
/* $$.ix [SERV_PORT]~constant,~definition~of$$ */
/* $$.ix [UNIXSTR_PATH]~constant,~definition~of$$ */
/* $$.ix [UNIXDG_PATH]~constant,~definition~of$$ */

/* Following shortens all the typecasts of pointer arguments: */
#define SA struct sockaddr

/* for file and dir */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

/* for linux system v message */
struct msgbuf
{
	long mtype;
	char mtext[1];
};

#define MSG_R 0400
#define MSG_W 0200
#define SVMSG_MODE (MSG_R | MSG_W | MSG_R >> 3 | MSG_R >> 6)

/* for system v semaphore */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

#define SEM_R 0400
#define SEM_A 0200
#define SVSEM_MODE (SEM_R | SEM_A | SEM_R>>3 | SEM_R>>6)

/* for system v shared memory */

#define SVSHM_MODE (SHM_R | SHM_W | SHM_R>>3 | SHM_R>>6)

/* signal handlers */
typedef void Sigfunc(int);

/****************************************************
 * prototypes for our own library wrapper functions 
*****************************************************/

/* C lib function package function */ 
ssize_t readline(int, void *, size_t);
ssize_t readn(int, void *, size_t);
ssize_t writen(int, const void *, size_t);
ssize_t Readline(int, void *, size_t);
ssize_t Readn(int, void *, size_t);
void Writen(int, void *, size_t);
char *Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);
const char *Inet_ntop(int, const void *, char *, size_t);
void Inet_pton(int, const char *, void *);

/* system call package function */
void sigchld_wait(int signo);
void sigchld_waitpid(int signo);
Sigfunc *Signal(int signo, Sigfunc *func);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int Poll(struct pollfd *, unsigned long, int);

/* socket function */
int Socket(int family, int type, int protocol);
int Accept(int, SA *, socklen_t *);
void Binid(int, const SA *, socklen_t);
void Connect(int, const SA *, socklen_t);
void Listen(int, int);
void Shutdown(int, int);
void Close(int);
void Sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
ssize_t Recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
void Setsockopt(int, int, int, const void *, socklen_t);
void Getsockopt(int, int, int, void *, socklen_t *);

/* error process function package function */
int daemon_init(const char *, int);
void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

/* my function for test */

#endif   /* __all_h */
