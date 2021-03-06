/*****************************************************
	^> File Name: listen.c
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/09/20 - 10:59:18
****************************************************/
#include "global.h"
void tcpinit(struct socktcp *p,const char *ip,const unsigned short port)
{
	p->sockaddr_in.sin_family=AF_INET;
	p->sockaddr_in.sin_port=htons(port);
	p->sockaddr_in.sin_addr.s_addr=inet_addr(ip);
	memset(p->sockaddr_in.sin_zero,0,8);
	p->addrlen=sizeof(p->sockaddr_in);
	fprintf(info,"++++%p,%d,%hu,%u,%d++++\n",p,p->sockaddr_in.sin_family,p->sockaddr_in.sin_port,p->sockaddr_in.sin_addr.s_addr,p->addrlen);
}
void tcpreuseport(struct socktcp *p)
{
	int on=1;
	if(setsockopt(p->sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))==-1)
	{
		perror("etsockopt error");
		exit(1);
	}
	fprintf(info,"++++set reuse port ok++++\n");
}
void tcpbind(struct socktcp *p)
{
	if(bind(p->sockfd,(struct sockaddr*)&p->sockaddr_in,p->addrlen)==-1)
	{
		perror("bind error...");
		exit(2);
	}
	fprintf(info,"++++bind %u:%hu ok++++\n",p->sockaddr_in.sin_addr.s_addr,p->sockaddr_in.sin_port);
}
void tcplisten(struct socktcp *p)
{
	if(listen(p->sockfd,4)==-1)
	{
		perror("listen error...");
		exit(3);
	}
	fprintf(info,"++++listen ok++++\n");
}
void tcpaccept(struct socktcp *p)
{
	p->sockfd=accept(p->sockfd,(struct sockaddr*)&p->sockaddr_in,&p->addrlen);
	if(p->sockfd==-1)
	{
		perror("accept error...");
		exit(4);
	}
	fprintf(info,"++++accept from %s:%hu++++\n",inet_ntoa(p->sockaddr_in.sin_addr),ntohs(p->sockaddr_in.sin_port));
}
void tcprecv(struct socktcp *p)
{
	unsigned char buf[512];
	int len;
	unsigned long total=0;
	while((len=recv(p->sockfd,buf,sizeof(buf)-1,0))>0)
	{
		total+=len;
		buf[len]=0;
		fprintf(info,"recv %d:%.*s;\n",len,len,buf);
	}
	fprintf(info,"++++recv %ld ok++++\n",total);
}
void tcpclose(struct socktcp *p)
{
	close(p->sockfd);
}
int mylisten()
{
	struct socktcp slisten;
	fprintf(info,"----listen %s:%hu----\n",sip,sport);
	slisten.sockfd=socket(AF_INET,SOCK_STREAM,0);
	fprintf(info,"----sockfd:%d----\n",slisten.sockfd);
	tcpreuseport(&slisten);
	tcpinit(&slisten,sip,sport);
	tcpbind(&slisten);
	tcplisten(&slisten);
	tcpaccept(&slisten);
	tcprecv(&slisten);
	tcpclose(&slisten);
	return 0;
}
