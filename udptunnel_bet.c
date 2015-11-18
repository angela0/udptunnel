/*
 * udptunnel_bet.c
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

	struct sockaddr_in dest;
	int nrecv;
	char buf[MAXLEN];

//	bzero(&dest, sizeof(dest));
//	dest.sin_family = AF_INET;
//	dest.sin_port = htons(PORT);


	for( ; ; )
	{
		nrecv = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
		if(nrecv < 0)
		{
			perror("recvfrom: ");
			exit(1);
		}
		fputs(buf, stdout);
	}

	return 0;
}
