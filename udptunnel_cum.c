/*
 * udptunnel_cum.c
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

	struct sockaddr_in addr;
	char buf[MAXLEN];
	int nrecv;

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(12345);
	addr.sin_len = sizeof(addr);

	if(bind(sockfd, (struct sockaddr *)addr, sizeof(addr)) < 0)
	{
		perror("bind: ");
		exit(1);
	}

	for( ; ; )
	{
		nrecv = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
		if(nrecv < 0)
		{
			perror("recvfrom: ");
			exit(2);
		}
		fputs(buf, stdout);
	}

	return 0;
}
