/*
 * udptunnel_cli.c
 *
 *  Created on: 2015年11月18日
 *      Author: angela
 */

#include "udptunnel.h"

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("usage: %s <IP address>\n", argv[0]);
		exit(1);
	}
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		perror("socket: ");
		exit(2);
	}
	struct sockaddr_in servaddr;
	char buf[MAXLEN] = {0};
	iphdr * ip = (iphdr *)buf;
	udphdr *udp = (udphdr *)(buf+IP_SIZE);

	datalen = MAXLEN-IP_SIZE-UDP_SIZE;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("10.0.0.16");
	servaddr.sin_port = htons(PORT);
	servaddr.sin_len = sizeof(servaddr);

	for( ; ; )
	{
		bzero(ip, MAXLEN);
		ip->ihl = 5;
		ip->version = 4;
		ip->tos = 0;
		ip->tot_len = IP_SIZE+UDP_SIZE+datalen;
		ip->id = 0;
		ip->frag_off = 0x40;
		ip->ttl = 0x40;
		ip->protocol = IPPROTO_UDP;
		ip->check = checksum((u16 *)(buf+ETH_SIZE), IP_SIZE+UDP_SIZE+datalen);
		ip->daddr = inet_addr("10.0.0.166");
		ip->saddr = inet_addr("10.0.0.166");

		udp->d_port = htons(PORT);
		udp->s_port = htons(12345);
		udp->length = htons(UDP_SIZE+datalen);
		fputs("please input data: ", stdout);
		fgets((char *)udp->data, datalen, stdin);

		psdhdr psd;
		psd.s_ip = inet_addr("10.0.0.166");
		psd.d_ip = inet_addr("10.0.0.166");
		psd.mbz = 0;
		psd.proto = 0x11;
		psd.plen = udp->length;

		char tmp[sizeof(psd)+ntohs(udp->length)];
		memcpy(tmp, &psd, sizeof(psd));
		memcpy(tmp+sizeof(psd), udp, UDP_SIZE+datalen);
		udp->check = checksum((u16 *)tmp, sizeof(tmp));

		int res = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		if(res < 0)
		{
			perror("sendto: ");
			exit(2);
		}
	}

	return 0;
}
