/*************************************************************************
* Copyright C 2014 CFETS Financial Data Co.,LTD
* All right reserved.
* File Name: wrap_ipc.c
* Version: 
* Writen by canux canuxcheng@gmail.com
* Created Time: 2014年10月04日 星期六 12时20分09秒
* Description: 
************************************************************************/
#include "all.h"

/*
 * for anonymous pipe
 */

/* pipe system call */
void Pipe(int *fds)
{
	if (pipe(fds) < 0)
		err_sys("pipe error");
}

/* pipe c lib */
FILE *Popen(const char *command, const char *type)
{
	FILE *fp;
	if ((fp = popen(command, type)) == NULL)
		err_msg("popen error");

	return (fp);
}

void Pclose(FILE *stream)
{
	if (pclose(stream) == -1)
		err_msg("pclose error");
}

/*
 * for named fifo 
 */

/* fifo c lib */
void Mkfifo(const char *pathname, mode_t mode)
{
	if ((mkfifo(pathname, mode) < 0) && (errno != EEXIST))
		err_sys("mkfifo error");
	else if (errno == EEXIST)
		err_msg("fifo exist");
}

/* fifo system call */
void Unlink(const char *pathname)
{
	if (unlink(pathname) < 0)
		err_sys("unlink error");
}

/* 
 * for posix message queue, c lib 
 */
mqd_t Mq_open(const char *name, int oflag, ...)
{
	mqd_t mqd;
	mode_t mode;
	struct mq_attr *attr;
	va_list ap;

	if (oflag & O_EXCL)
	{
		va_start(ap, oflag);
		mode = va_arg(ap, mode_t);
		attr = va_arg(ap, struct mq_attr *);
		if ((mqd = mq_open(name, oflag, mode, attr)) == (mqd_t)-1)
			err_sys("mq_open error");
		va_end(ap);
	}
	else
	{
		if ((mqd = mq_open(name, oflag)) == (mqd_t)-1)
			err_sys("mq_open error");
	}
	
	return (mqd);
}

void Mq_close(mqd_t mqd)
{
	if (mq_close(mqd) == -2)
		err_sys("mq_close error");
}

void Mq_unlink(const char *name)
{
	if (mq_unlink(name) == -1)
		err_sys("mq_unlink error");
}

void Mq_getattr(mqd_t mqdes, struct mq_attr *attr)
{
	if (mq_getattr(mqdes, attr) == -1)
		err_sys("mq_getattr error");
}

void Mq_send(mqd_t mqdes, const char *ptr, size_t len, unsigned int prio)
{
	if (mq_send(mqdes, ptr, len, prio) == -1)
		err_sys("mq_send error");
}

void Mq_receive(mqd_t mqdes, char *ptr, size_t len, unsigned int *priop)
{
	if (mq_receive(mqdes, ptr, len, priop) == -1)
		err_sys("mq_receive error");
}

void Mq_notify(mqd_t mqd, const struct sigevent *notification)
{
	if (mq_notify(mqd, notification) == -1)
		err_sys("mq_notify error");
}

/*
 * for system v message, system call
 */

int Msgget(key_t key, int oflag)
{
	int n;
	
	if ((n = msgget(key, oflag)) == -1)
		err_sys("msgget error");
	return (n);
}

void Msgsnd(int msqid, const void *ptr, size_t length, int flag)
{
	if (msgsnd(msqid, ptr, length, flag) == -1)
		err_sys("msgsnd error");
}

ssize_t Msgrcv(int msqid, void *ptr, size_t length, long type, int flag)
{
	ssize_t n;

	if ((n = msgrcv(msqid, ptr, length, type, flag)) == -1)
		err_sys("msgrcv error");
	return (n);
}

void Msgctl(int msqid, int cmd, struct msqid_ds *buff)
{
	if (msgctl(msqid, cmd, buff) == -1)
		err_sys("msgctl error");
}

/* c lib */
key_t Ftok(const char *pathname, int proj_id)
{
	key_t key;

	if ((key = ftok(pathname, proj_id)) == -1)
		err_sys("ftok error");
	return (key);
}

/*
 * for mutex lock
 */

void Pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr)
{
	int n;

	if ((n = pthread_mutex_init(mutex, mutexattr)) == 0)
		return ;
	errno = n;
	err_sys("pthread_mutex_init error");
}

void Pthread_mutex_lock(pthread_mutex_t *mutex)
{
    int n;
	if ((n = pthread_mutex_lock(mutex)) == 0)
		return ;
	errno = n;
	err_sys("pthread_mutex_lock error");
}

void Pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_mutex_unlock(mutex)) == 0)
		return ;
	errno = n;
	err_sys("pthread_mutex_unlock error");
}

void Pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_mutex_destroy(mutex)) == 0)
		return;
	errno = n;
	err_sys("pthread_mutex_destroy error");
}

/*
 * for cond variable
 */
void Pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr)
{
	int n;
	if ((n = pthread_cond_init(cond, cond_attr)) == 0)
		return;
	errno = n;
	err_sys("pthread_cond_init error");
}

void Pthread_cond_signal(pthread_cond_t *cond)
{
	int n;
	if ((n = pthread_cond_signal(cond)) == 0)
		return ;
	errno = n;
	err_sys("pthread_cond_signal error");
}

void Pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_cond_wait(cond, mutex)) == 0)
		return ;
	errno = n;
	err_sys("pthread_cond_wait error");
}

void Pthread_cond_destroy(pthread_cond_t *cond)
{
	int n;
	if ((n = pthread_cond_destroy(cond)) == 0)
		return;
	errno = n;
	err_sys("pthread_cond_destroy error");
}

/* 
 * for rwlock: read and write lock
 */
void Pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
{
	int n;
	if ((n = pthread_rwlock_init(rwlock, attr)) == 0)
		return;
	errno = n;
	err_sys("pthread_rwlock_init error");
}

void Pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_rdlock(rwlock)) == 0)
		return;
	errno = n;
	err_sys("pthread_rwlock_rdlock error");
}

void Pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_wrlock(rwlock)) == n)
		return;
	errno = n;
	err_sys("pthread_rwlock_wrlock error");
}

void Pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_unlock(rwlock)) == 0)
		return;
	errno = n;
	err_sys("pthread_rwlock_unlock error");
}

void Pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_destroy(rwlock)) == 0)
		return;
	errno = n;
	err_sys("pthread_rwlock_destroy error");
}

/*
 * posix semaphore
 */
sem_t *Sem_open(const char *name, int oflag, ...)
{
    sem_t *sem;
	va_list ap;
	mode_t mode;
	unsigned int value;

	if (oflag & O_CREAT)
	{
		va_start(ap, oflag); // init ap to final named argument
		mode = va_arg(ap, mode_t);
		value = va_arg(ap, unsigned int);
		if ((sem = sem_open(name, oflag, mode, value)) == SEM_FAILED)
			err_sys("sem_open error for %s", name);
		va_end(ap);
	}
	else
	{
		if ((sem = sem_open(name, oflag)) == SEM_FAILED)
			err_sys("sem_open error for %s", name);
	}
	return (sem);
}

void Sem_close(sem_t *sem)
{
	if (sem_close(sem) == -1)
		err_sys("sem_close error");
}

void Sem_unlink(const char *name)
{
	if (sem_unlink(name) == -1)
		err_sys("sem_unlink error");
}

void Sem_init(sem_t *sem, int pshared, unsigned int value)
{
	if (sem_init(sem, pshared, value) == -1)
		err_sys("sem_init error");
}

void Sem_destroy(sem_t *sem)
{
	if (sem_destroy(sem) == -1)
		err_sys("sem_destroy error");
}

void Sem_wait(sem_t *sem)
{
	if (sem_wait(sem) == -1)
		err_sys("sem_wait error");
}

int Sem_trywait(sem_t *sem)
{
	int rc;
	if ((rc = sem_trywait(sem)) == -1 && errno != EAGAIN)
		err_sys("sem_trywait error");
	return (rc);
}

void Sem_post(sem_t *sem)
{
	if (sem_post(sem) == -1)
		err_sys("sem_post error");
}

void Sem_getvalue(sem_t *sem, int *valp)
{
	if (sem_getvalue(sem, valp) == -1)
		err_sys("sem_getvalue error");
}

/* 
 * system v semaphore
 */
int Semget(key_t key, int nsems, int semflg)
{
	int rc;

	if ((rc = semget(key, nsems, semflg)) == -1)
		err_sys("semget error");

	return (rc);
}

int Semop(int semid, struct sembuf *sops, unsigned nsops)
{
	int rc;

	if ((rc = semop(semid, sops, nsops)) == -1)
		err_sys("semop error");

	return (rc);
}

int Semctl(int semid, int semnum, int cmd, ...)
{
	int rc;
	va_list ap;
	union semun arg;

	if (cmd == GETALL || cmd == SETALL || cmd == SETVAL || cmd == IPC_STAT || cmd == IPC_SET) {
		va_start(ap, cmd);
		arg = va_arg(ap, union semun);
		if ((rc = semctl(semid, semnum, cmd, arg)) == -1)
			err_sys("semctl error");
		va_end(ap);
	} else {
		if ((rc = semctl(semid, semnum, cmd)) == -1)
			err_sys("semctl error");
	}
	return (rc);
}

/*
 * posix shared memory
 */
void *Mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	void *ptr;

	if ((ptr = mmap(addr, length, prot, flags, fd, offset)) == MAP_FAILED)
		err_sys("mmap error");

	return (ptr);
}

void Munmap(void *addr, size_t length)
{
	if (munmap(addr, length) == -1)
		err_sys("munmap error");
}

int Shm_open(const char *pathname, int oflag, mode_t mode)
{
	int fd;

	if ((fd = shm_open(pathname, oflag, mode)) == -1)
		err_sys("shm_open error");
	return (fd);
}

void Shm_unlink(const char *pathname)
{
	if (shm_unlink(pathname) == -1)
		err_sys("shm_unlink error");
}

/*
 * system v shared memory
 */
int Shmget(key_t key, size_t size, int flags)
{
	int rc;

	if ((rc = shmget(key, size, flags)) == -1)
		err_sys("shmget error");

	return (rc);
}

void *Shmat(int id, const void *shmaddr, int flags)
{
	void *ptr;

	if ((ptr = shmat(id, shmaddr, flags)) == (void *) -1)
		err_sys("shmat error");

	return (ptr);
}

void Shmdt(const void *shmaddr)
{
	if (shmdt(shmaddr) == -1)
		err_sys("shmdt error");
}

void Shmctl(int id, int cmd, struct shmid_ds *buff)
{
	if (shmctl(id, cmd, buff) == -1)
		err_sys("shmctl error");
}
