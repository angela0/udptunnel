/*
 * udptunnel.c
 *
 *  Created on: 2015年11月18日
 *      Author: angela
 */

#include "udptunnel.h"

u16 checksum(u16 *addr, int len)
{
    int nleft = len;
    u32 sum = 0;

    while(nleft>1)
    {
        sum += *addr++;
        nleft-=2;
    }

    if(nleft==1)
    {
        sum += *(u8 *)addr;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}

char *ntop(char *str, u32 addr)
{
	char *p = (char *)&addr;
	sprintf(str, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);

	return str;
}
