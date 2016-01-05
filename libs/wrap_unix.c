/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: wrap_unix.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年08月31日 星期日 19时13分17秒
* Description: the package function of unix system call
************************************************************************/
#include "all.h"

int Open(const char *pathname, int oflag, mode_t mode)
{
	int fd;

	if ((fd = open(pathname, oflag, mode)) == -1)
		err_sys("open error for %s", pathname);
	return (fd);
}

void Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes)
		err_sys("write error");
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;
	if ((n = read(fd, ptr, nbytes)) == -1)
		err_sys("read error");
	return (n);
}

off_t Lseek(int fd, off_t offset, int whence)
{
	off_t pos;

	if ((pos = lseek(fd, offset, whence)) == (off_t)-1)
		err_sys("lseek error");
	return (pos);
}

void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}



pid_t Fork(void)
{
	pid_t pid;

	if ((pid = fork()) == -1)
		err_sys("fork error");
	return (pid);
}



int Fcntl(int fd, int cmd, int arg)
{
	int n;

	if ((n = fcntl(fd, cmd, arg)) == -1)
		err_sys("fcntl error");
	return (n);
}

int Ioctl(int fd, int request, void *arg)
{
	int n;

	if ((n = ioctl(fd, request, arg)) == -1)
		err_sys("ioctl error");

	return (n);
}



int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
	int n;

	if ((n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
		err_sys("select error");
	else if (n == 0)
		err_sys("select time out");
	return (n);
}

int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
{
	int n;

	if ((n = poll(fdarray, nfds, timeout)) < 0)
		err_sys("poll error");
	return (n);
}



pid_t Wait(int *iptr)
{
	pid_t pid;

	if ((pid = wait(iptr)) == -1)
		err_sys("wait error");
	return (pid);
}

pid_t Waitpid(pid_t pid, int *iptr, int options)
{
	pid_t retpid;

	if ((retpid = waitpid(pid, iptr, options)) == -1)
		err_sys("waitpid error");
	return (retpid);
}

void Ftruncate(int fd, off_t length)
{
    if (ftruncate(fd, length) == -1)
		err_sys("ftruncate error");
}

void Fstat(int fd, struct stat *buf)
{
	if (fstat(fd, buf) == -1)
		err_sys("fstat error");
}
