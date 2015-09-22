/*****************************************************
	^> File Name: tunnel.c
	^> Author: AoEiuV020
	^> Mail: 490674483@qq.com
	^> Created Time: 2015/09/20 - 14:13:31
****************************************************/
#include "global.h"
int main(int argc, char **argv)
{
	snprintf(sip,sizeof(sip),"180.209.64.41");
	snprintf(dip,sizeof(dip),"127.0.0.1");
	sport=22222u;
	dport=22u;
	setuid(geteuid());/*4770*/
	printf("---------%d <==> %d------\n",getuid(),geteuid());
	printf("----%s:%hu -> %s:%hu----\n",sip,sport,dip,dport);
	//mylisten(argc,argv);
	myconnect(argc,argv);
	return 0;
}
