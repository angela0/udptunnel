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

	struct sockaddr_in myaddr, dest;
	int nrecv;
	char recvbuf[MAXLEN];
	char sendbuf[MAXLEN];

	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_len = sizeof(myaddr);

	if(bind(sockfd, (struct sockaddr *)&myaddr, myaddr.sin_len) < 0)
	{
		perror("bind: ");
		exit(1);
	}

	const *reback[3] = {"Invalid target!!\n", "You can't move now!!!\n", "I can't understand you!!!\n"};

	for( ; ; )
	{
		socklen_t len = sizeof(dest);
		nrecv = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&dest, &len);
		if(nrecv < 0)
		{
			perror("recvfrom: ");
			exit(1);
		}
		if(strcmp(recvbuf, "attack")==0)
			strncpy(sendbuf, reback[0], strlen(reback[0]));
		else if(strcmp(recvbuf, "back")==0)
			strncpy(sendbuf, reback[1], strlen(reback[1]));
		else
			strncpy(sendbuf, reback[2], strlen(reback[2]));

		int nsend = sendto(sockfd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *)&dest, len);
		if(nsend < 0)
		{
			perror("recvfrom: ");
			exit(1);
		}
	}

	return 0;
}
