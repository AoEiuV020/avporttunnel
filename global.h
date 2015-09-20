/*****************************************************
	^> File Name: global.h
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/09/20 - 14:14:58
****************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char sip[20],dip[20];
unsigned short sport,dport;
struct socktcp
{
	int sockfd;
	struct sockaddr_in sockaddr_in;
	socklen_t addrlen;
};
void tcpinit(struct socktcp *p,const char *ip,const unsigned short port);
void tcpreuseport(struct socktcp *p);
void tcpbind(struct socktcp *p);
void tcplisten(struct socktcp *p);
void tcpaccept(struct socktcp *p);
void tcprecv(struct socktcp *p);
void tcpclose(struct socktcp *p);

int mylisten(int argc, char **argv);
int myconnect(int argc, char **argv);
#endif //GLOBAL_H
