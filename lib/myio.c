/************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: myio.c
* Version:
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年08月30日 星期六 17时30分07秒
* Description:
************************************************************************/
#include "all.h"

/*******************readline***************/
static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

static ssize_t my_read(int fd, char *ptr)
{
	if (read_cnt <= 0)
	{
again:
		if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
		{
			if (errno == EINTR)
				goto again;
			return (-1);
		}
		else if (read_cnt == 0)
			return;
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
    return (1);
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++)
	{
		if ((rc = my_read(fd, &c)) == 1)
		{
			*ptr++ = c;
			if (c == '\n')
				break;   /* newline is stored, like fgets() */
		}
		else if (rc == 0)
		{
			*ptr = 0;
			return (n - 1);   /* EOF, n - 1 bytes were read */
		}
		else
			return (-1);   /* error, errno set by read() */
	}

	*ptr = 0;   /* null terminate like fgets() */
	return (n);
}

ssize_t readlinebuf(void **vptrptr)
{
	if (read_cnt)
		*vptrptr = read_ptr;
	return (read_cnt);
}



ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t n;
	if ((n = readline(fd, ptr, maxlen)) < 0)
		err_sys("readline error");
	return (n);
}

/********************readn******************/
ssize_t readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
	size_t nread;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
        if ((nread = read(fd, ptr, nleft)) < 0)
		{
            if (errno = EINTR)
				nread = 0;
			else
				return (-1);
		}
		else if (nread == 0)
			break;

		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft);
}

ssize_t Readn(int fd, void *ptr, size_t nbytes)
{
    ssize_t n;
	if ((n = readn(fd, ptr, nbytes)) < 0)
		err_sys("readn error");
	return (n);
}

/****************writen***************************/
ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
	size_t nwrite;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0)
    {
        if ((nwrite = write(fd, ptr, nleft)) < 0)
		{
            if (errno == EINTR)
				nwrite = 0;
			else
				return (-1);
		} else if (nwrite == 0)
			break;

		nleft -= nwrite;
		ptr += nwrite;
	}
}

void Writen(int fd, void *ptr, size_t nbytes)
{
    if (writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}

