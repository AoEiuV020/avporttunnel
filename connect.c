/*****************************************************
	^> File Name: connect.c
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/09/20 - 13:54:53
****************************************************/
#include "global.h"
void tcpconnect(struct socktcp *p)
{
	if(connect(p->sockfd,(struct sockaddr*)&p->sockaddr_in,p->addrlen)==-1)
	{
		perror("bind error...");
		exit(5);
	}
}
void tcpsend(struct socktcp *p)
{
	unsigned char buf[512];
	int len;
	unsigned long total=0;
	while((fgets(buf,sizeof(buf),stdin))>0)
	{
		len=strlen(buf);
		total+=len;
		send(p->sockfd,buf,len,0);
		fprintf(info,"send %d:%s;\n",len,buf);
	}
	fprintf(info,"++++send %ld ok++++\n",total);
}
int myconnect()
{
	struct socktcp sconnect;
	fprintf(info,"----connect %s:%hu----\n",dip,dport);
	sconnect.sockfd=socket(AF_INET,SOCK_STREAM,0);
	fprintf(info,"----sockfd:%d----\n",sconnect.sockfd);
	tcpinit(&sconnect,dip,dport);
	tcpconnect(&sconnect);
	tcpsend(&sconnect);
	tcpclose(&sconnect);
	return 0;
}
