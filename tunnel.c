/*****************************************************
	^> File Name: tunnel.c
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/09/20 - 14:13:31
****************************************************/
#include "global.h"
int main(int argc, char **argv)
{
	pipe(pfd);
	snprintf(sip,sizeof(sip),"127.0.0.1");
	snprintf(dip,sizeof(dip),"127.0.0.1");
	sport=22222u;
	dport=22222u;
	info=stderr;
	setuid(geteuid());/*4770*/
	fprintf(info,"---------%d <==> %d------\n",getuid(),geteuid());
	fprintf(info,"----%s:%hu -> %s:%hu----\n",sip,sport,dip,dport);
	mylisten();
	//myconnect();
	return 0;
}
