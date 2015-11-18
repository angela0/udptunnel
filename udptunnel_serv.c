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
	if(sockfd < 0)
	{
		perror("socket: ");
		exit(2);
	}
	struct sockaddr_in destaddr, servaddr, cliaddr;
	char buf[MAXLEN];
	char tmp[MAXLEN];
	int nrecv;
	ethhdr *eth = (ethhdr *)buf;
	iphdr * ip = (iphdr *)(buf+ETH_SIZE);
	udphdr *udp = (udphdr *)(buf+ETH_SIZE+IP_SIZE);

	datalen = MAXLEN-ETH_SIZE-IP_SIZE-UDP_SIZE;

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
		nrecv = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
		if(nrecv < 0)
		{
			perror("recvfrom: ");
			exit(1);
		}
		printf("eth info:\n");
		printf("\tsource mac: %s\n\tdest mac: %s\n\teth type: %u\n", eth->smac, eth->dmac, eth->type);

		printf("ip info:\n");
		printf("\tsource ip: %s\n\tdest ip: %s\n\tip proto: %u\n",
				ntop(tmp, ip->saddr), ntop(tmp, ip->daddr), ip->protocol);

		printf("udp info:\n");
		printf("\tsource port: %d\n\tdest port: %d\n", ntohs(udp->s_port), htons(udp->d_port));
		printf("data:\n");
		printf("\t%s\n", udp->data);
	}

	return 0;
}
