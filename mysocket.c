/*********************************************************************
* Copyright (C) 2014 CFETS Financial Data Co.,LTD                    *
* All right reserved.                                                *
* Name: mysocket.c
* Author: Canux canuxcheng@gmail.com                                 *
* Version: V1.0                                                      *
* Time: Mon 27 Oct 2014 11:30:41 AM CST
* Description:                                                       *
*********************************************************************/
#include "all.h"

/* use host and service to return address and port information, contrariwise */
struct addrinfo *host_serv(const char *host, const char *serv, int family, int socktype)
{
	int n;
	struct addrinfo hints, *res;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME;// always return canonical name
	hints.ai_family = family; //AF_UNSPEC(return any address family),AF_INET, AF_INET6
	hints.ai_socktype = socktype; //0, SOCK_STREAM, SOCK_DGRAM
	//hints.ai_protocol = 0; // 0(renturn any protocol socket address), IPPROTO_XXX

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		return (NULL);

	return (res);
}

/* the client use this function to create a socket and connect to server */
int tcp_connect(const char *host, const char *serv)
{
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;	

	bzero(&hints, sizeof(struct addrinfo));
	//hints.ai_flags = ?
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	//hints.ai_protocol = ?

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("tcp_connect: getaddrinfo error for %s, %s: %s", host, serv, gai_strerror(n));
	ressave = res;

	do 
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue; //ignore this one

		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break; // connect success
		Close(sockfd);// stop three way handshake
	} while ((res = res->ai_next) != NULL);

	if (res == NULL) // errno set from final connect
		err_sys("tcp_connect: connect error for %s, %s", host, serv);

	freeaddrinfo(ressave);

	return (sockfd);
}

/* server use this function to wait for a connect from client */
int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	int listenfd, n;
	const int on = 1;
	struct addrinfo hints, *res, *ressave;

	 bzero(&hints, sizeof(struct addrinfo));
	 hints.ai_flags = AI_PASSIVE;
	 hints.ai_family = AF_UNSPEC;
	 hints.ai_socktype = SOCK_STREAM;
	 //hints.ai_protocol = ?

	 if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		 err_quit("tcp_listen: getaddrinfo error for %s, %s: %s", host, serv, gai_strerror(n));

	 ressave = res;

	 do
	 {
		 listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		 if (listenfd < 0)
			 continue; //error, try next one
	
		 Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		 if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			 break; //bind success
		 Close(listenfd); //bind error
	 } while ((res = res->ai_next) != NULL);

	 if (res == NULL)
		 err_sys("tcp_listen error for %s, %s", host, serv);

	 Listen(listenfd, LISTENQ);

	 if (addrlenp)
		 *addrlenp = res->ai_addrlen; // return size of protocol address for accept

	 freeaddrinfo(ressave);
	 return(listenfd);
}

/* use this function to create an unconnected udp socket */
int udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp)
{
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_client error for %s, %s: %s", host, serv, gai_strerror(n));
	ressave = res;

	do
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd >= 0)
			break; // success
	} while ((res = res->ai_next) != NULL);

	if (res == NULL) //errno set from final socket
		err_sys("udp_client error for %s, %s", host, serv);

	*saptr = (SA *)Malloc(res->ai_addrlen);
	memcpy(*saptr, res->ai_addr, res->ai_addrlen);
	*lenp = res->ai_addrlen;

	freeaddrinfo(ressave);
	return (sockfd);
}

/* use this function to create an connected udp socket */
int udp_connect(const char *host, const char *serv)
{
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_connect error for %s, %s: %s", host, serv, gai_strerror(n));
	ressave = res;

	do
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue; //ignore this noe

		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break; //success
		Close(sockfd);//ignore this one
	} while ((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("udp_connect error for %s, %s", host, serv);
	
	freeaddrinfo(ressave);
	return (sockfd);
}

/* use this function to wait for a connect from client */
int udp_server(const char *host, const char *serv, socklen_t *addrlenp)
{
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_server error %s, %s: %s", host, serv, gai_strerror(n));
    ressave = res;

	do
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue; //error, try next one

		if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break; //success

		Close(sockfd); // bind error, close and try next one
	} while ((res = res->ai_next) != NULL);

    if (res == NULL) // error from final soeket or bind
	    err_sys("udp_server error for %s, %s", host, serv);

	if (addrlenp)
	    *addrlenp = res->ai_addrlen; // return size of protocol address

    freeaddrinfo(ressave);
	return (sockfd);
}
