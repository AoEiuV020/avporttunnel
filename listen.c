/*****************************************************
	^> File Name: listen.c
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/09/20 - 10:59:18
****************************************************/
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

char sip[20]="127.0.0.1",dip[20]="127.0.0.1";
unsigned short sport=22222u,dport=22u;
//int lfd,cfd;/*listen file description and connect file description*/
struct socktcp
{
	int sockfd;
	struct sockaddr_in sockaddr_in;
	socklen_t addrlen;
};
void tcpinit(struct socktcp *p,const char *ip,const unsigned short port)
{
	p->sockaddr_in.sin_family=AF_INET;
	p->sockaddr_in.sin_port=htons(port);
	p->sockaddr_in.sin_addr.s_addr=inet_addr(ip);
	memset(p->sockaddr_in.sin_zero,0,8);
	p->addrlen=sizeof(p->sockaddr_in);
	printf("++++%p,%d,%hu,%u,%d++++\n",p,p->sockaddr_in.sin_family,p->sockaddr_in.sin_port,p->sockaddr_in.sin_addr.s_addr,p->addrlen);
}
void tcpreuseport(struct socktcp *p)
{
	int on=1;
	if(setsockopt(p->sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))==-1)
	{
		perror("etsockopt error");
		exit(1);
	}
}
void tcpbind(struct socktcp *p)
{
	if(bind(p->sockfd,(struct sockaddr*)&p->sockaddr_in,p->addrlen)==-1)
	{
		perror("bind error...");
		exit(2);
	}
	printf("++++bind %u:%hu ok++++\n",p->sockaddr_in.sin_addr.s_addr,p->sockaddr_in.sin_port);
}
void tcplisten(struct socktcp *p)
{
	if(listen(p->sockfd,4)==-1)
	{
		perror("listen error...");
		exit(3);
	}
	printf("++++listen ok++++\n");
}
void tcpaccept(struct socktcp *p)
{
	p->sockfd=accept(p->sockfd,(struct sockaddr*)&p->sockaddr_in,&p->addrlen);
	if(p->sockfd==-1)
	{
		perror("accept error...");
		exit(4);
	}
	printf("++++accept from %s:%hu++++\n",inet_ntoa(p->sockaddr_in.sin_addr),ntohs(p->sockaddr_in.sin_port));
}
void tcprecv(struct socktcp *p)
{
	unsigned char buf[512];
	int len;
	while((len=recv(p->sockfd,buf,sizeof(buf)-1,0))>0)
	{
		buf[len]=0;
		printf("recv %d:%.*s;\n",len,len,buf);
	}
}
void tcpclose(struct socktcp *p)
{
	close(p->sockfd);
}
int main(int argc, char **argv)
{
	struct socktcp slisten,sconnect;
	setuid(geteuid());/*4770*/
	printf("---------%d <==> %d------\n",getuid(),geteuid());
	printf("----%s:%hu -> %s:%hu----\n",sip,sport,dip,dport);
	slisten.sockfd=socket(AF_INET,SOCK_STREAM,0);
	sconnect.sockfd=socket(AF_INET,SOCK_STREAM,0);
	printf("----sockfd:%d,%d----\n",slisten.sockfd,sconnect.sockfd);
	tcpreuseport(&slisten);
	tcpinit(&slisten,sip,sport);
	tcpinit(&sconnect,dip,dport);
	tcpbind(&slisten);
	tcplisten(&slisten);
	tcpaccept(&slisten);
	tcprecv(&slisten);
	tcpclose(&slisten);
	return 0;
}
