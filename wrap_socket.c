/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: wrap_socket.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年08月30日 星期六 15时42分20秒
* Description: the package function of socket c library
************************************************************************/
#include "all.h"

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
    int n;

again:
	if ((n = accept(sockfd, cliaddr, addrlen)) < 0)
	{
#ifdef EPROTO
		if (errno == EPROTO || errno == ECONNABORTED || errno == EINTR)
#else
		if (errno == ECONNABORTED || errno == EINTR)
#endif
			goto again;
		else
			err_sys("accept error");
	}
	return (n);
}

void Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
    if (bind(sockfd, myaddr, addrlen) < 0)
	    err_sys("bind error");
}

void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
    if (connect(sockfd, servaddr, addrlen) < 0)
		err_sys("connect error");
}

void Listen(int fd, int backlog)
{
    char *ptr;
    if ((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);
	if (listen(fd, backlog) < 0)
		err_sys("listen error");
}

int Socket(int family, int type, int protocol)
{
    int n;
	if ((n = socket(family, type, protocol)) < 0)
		err_sys("socket error");
	return (n);
}

void Shutdown(int sockfd, int how)
{
	if (shutdown(sockfd, how) < 0)
		err_sys("shutdown error");
}

void Sendto(int sockfd, const void *buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen)
{
	if (sendto(sockfd, buff, nbytes, flags, to, addrlen) != (ssize_t)nbytes)
		err_sys("sendto error");
}

ssize_t Recvfrom(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen)
{
    ssize_t n;
	if ((n = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0)
		err_sys("recvfrom error");
	return n;
}

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
    if (setsockopt(sockfd, level, optname, optval, optlen) < 0)
		err_sys("setsockopt error");
}

void Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
	if (getsockopt(sockfd, level, optname, optval, optlen) < 0)
		err_sys("getsockopt error");
}

void Getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	if (getsockname(sockfd, addr, addrlen) < 0)
		err_sys("getsockname error");
}

void Getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	if (getpeername(sockfd, addr, addrlen) < 0)
		err_sys("getpeername error");
}

void Socketpair(int domain, int type, int protocol, int sv[2])
{
	if (socketpair(domain, type, protocol, sv) < 0)
		err_sys("socketpair error");
}

/**********************************************
 * just two way to set timeout for connect and accept
 * signal and select
 * no socket options can be used for connect
 **********************************************/

/* to set the timeout for connect() use SIGALRM */
static void connect_alarm(int signo)
{
	err_sys("connect timeout");
}

void connect_timeout_alarm(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen, int nsec)
{
	Sigfunc *sigfunc;   /* used for to save previous signal handler */
	int n;

	sigfunc = Signal(SIGALRM, connect_alarm);

	if (alarm(nsec) != 0)
		err_sys("connect_timeout_alarm: alarm was already set");

	if ((n = connect(sockfd, servaddr, addrlen)) < 0)
	{
		Close(sockfd);   /* prevent three path handshake continue */
		if (errno == EINTR) /* if interrupt means timeout */
			errno = ETIMEDOUT;
		err_sys("connect error");
	}

	alarm(0);   /* turn off the alarm */
	Signal(SIGALRM, sigfunc);   /* restore previous signal handler */
}

/* set the timeout for connect use select */ 
/*
void connect_timeout_select(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen, int nsec)
{
	fd_set rset, wset;
	struct timeval tval;

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	wset = rset;

	tval.tv_sec = nsec;
	tval.tv_usec = 0;

	Select(sockfd+1, &rset, &wset, NULL, &tval);
	Connect(sockfd, servaddr, addrlen);
}
*/

/* set timeout for accept use select */
/*
int accept_timeout_select(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{

}
*/


/*****************************************************
 * three ways to set timeout for recvfrom and sendto
 * signal select and socket options
 * recvfrom for read and snedto for wirte
 * **************************************************/

/* set the timeout for recvfrom() use SIGALRM */
static void recvfrom_alrm(int signo)
{
	err_sys("recvfrom timeout") ;
}

int recvfrom_timeout_alrm(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen, int nsec)
{
	int n;
	Sigfunc *sigfunc;

	sigfunc = Signal(SIGALRM, recvfrom_alrm);
	if (alarm(nsec) != 0)
		err_sys("recvfrom_timeout_alarm: alarm was already set");
 
    n = Recvfrom(sockfd, buff, nbytes, flags, from, addrlen);
    return (n);

	alarm(0);
	Signal(SIGALRM, sigfunc);
}

/* set timeout for recvfrom() use select() */
int recvfrom_timeout_select(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen, int nsec)
{
	int n;
	fd_set rset;
	struct timeval tv;

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);

	tv.tv_sec = nsec;
	tv.tv_usec = 0;

	Select(sockfd+1, &rset, NULL, NULL, &tv);
	n = Recvfrom(sockfd, buff, nbytes, flags, from, addrlen);

	return (n);
}

/* set timeout for recvfrom use socket option SO_RCVTIMEO */
int recvfrom_timeout_socket(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen, int nsec)
{
	int n;
	struct timeval tv;

	tv.tv_sec = nsec;
	tv.tv_usec = 0;

	Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	if ((n = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0)
	{
		if (errno == EWOULDBLOCK) /* if timeout return EWOULDBLOCK or EAGAIN */
			err_sys("recvfrom timeout");
		else
			err_sys("recvfrom error");
	}
	return (n);
}


/************************************************************
 * use the nonblock to set the timeout for connect and accept 
 ************************************************************/

/* use nonblock for connect */
int connect_nob(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen, int nsec)
{
	int flags, n, error;
	socklen_t len;
	struct timeval tval;
	fd_set rset, wset;

	flags = Fcntl(sockfd, F_GETFL, 0);
	Fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	error = 0;

	/* when socket is nonblock connect return EINPROGRESS and three ways hand shake is still running */
	if ((n = connect(sockfd, servaddr, addrlen)) < 0)
	{
		if (errno != EINPROGRESS) /* ignore the mistake */
			return (-1);
	} /* nonbalck state the socket is connected now */

	/* this might happen some times */
	if (n == 0)
		goto done;

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
    wset = rset;

	tval.tv_sec = nsec;
	tval.tv_usec = 0;

	if ((n = select(sockfd+1, &rset, &wset, NULL, nsec ? &tval : NULL)) < 0)
		err_sys("select error");
	else if (n == 0) /* select time out */
	{
	    Close(sockfd);
		errno = ETIMEDOUT;
		err_sys("select timeout");
	}

	if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset))
	{
		len = sizeof(error);
		Getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
	}
	else
		err_quit("select error: sockfd not set");

done: /* wether n==0 or not bellow will excuted */
	Fcntl(sockfd, F_SETFL, flags); /* set back to block */

	if (error) /* connect error */
	{
		Close(sockfd);
	    errno = error;
	    return (-1);
	}

	return (0);
}

/* use nonblock for accept */

