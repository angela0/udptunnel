/*
 * udptunnel_serv.c
 *
 *  Created on: 2015年11月18日
 *      Author: angela
 */

#include "udptunnel.h"

int main(int argc, char **argv)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int rawsockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sockfd < 0 || rawsockfd < 0)
	{
		perror("socket: ");
		exit(2);
	}

	const int on = 1;
	if(setsockopt(rawsockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
	{
		printf("setsockopt() error!\n");
		exit(0);
	}

	struct sockaddr_in dest, servaddr, cliaddr;
	char buf[MAXLEN];
	char tmp[MAXLEN];
	int nrecv, nsend;

	iphdr * ip = (iphdr *)buf;
	udphdr *udp = (udphdr *)(buf+IP_SIZE);

	datalen = MAXLEN-IP_SIZE-UDP_SIZE;

	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("10.0.0.166");
	dest.sin_port = htons(PORT);


	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind: ");
		exit(2);
	}

	for( ; ; )
	{
		socklen_t lencli = sizeof(cliaddr);
		nrecv = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &lencli);
		if(nrecv < 0)
		{
			perror("recvfrom: ");
			exit(1);
		}

		ip->saddr = inet_addr("10.0.0.16");
		udp->d_port = htons(PORT);
		udp->s_port = htons(PORT);
		udp->length = htons(UDP_SIZE+datalen);

		psdhdr psd;
		psd.s_ip = ip->saddr;
		psd.d_ip = ip->daddr;
		psd.mbz = 0;
		psd.proto = 0x11;
		psd.plen = udp->length;

		char tmp[sizeof(psd)+ntohs(udp->length)];
		memcpy(tmp, &psd, sizeof(psd));
		memcpy(tmp+sizeof(psd), udp, UDP_SIZE+datalen);
		udp->check = checksum((u16 *)tmp, sizeof(tmp));

		nsend = sendto(rawsockfd, buf, sizeof(buf), 0, (struct sockaddr *)&dest, sizeof(dest));
		if(nsend < 0)
		{
			perror("sendto: ");
			exit(1);
		}
		int lenbet;
		nrecv = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&dest, &lenbet);
		if(nrecv < 0)
		{
			perror("recvfrom: ");
			exit(1);
		}
		nsend = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		if(nsend < 0)
		{
			perror("sendto: ");
			exit(1);
		}
	}

	return 0;
}
