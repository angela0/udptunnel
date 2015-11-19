/*
 * udptunnel_cli.h
 *
 *  Created on: 2015年11月18日
 *      Author: angela
 */

#ifndef UDPTUNNEL_CLI_H_
#define UDPTUNNEL_CLI_H_



#endif /* UDPTUNNEL_CLI_H_ */

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define MAXLEN 120
#define PORT 23456

typedef struct
{
    u8 ihl:4;
    u8 version:4;
    u8 tos;
    u16 tot_len;
    u16 id;
    u16 frag_off;
    u8 ttl;
    u8 protocol;
    u16 check;
    u32 saddr;
    u32 daddr;
} iphdr;

typedef struct
{
	u16 s_port;
	u16 d_port;
	u16 length;
	u16 check;
	u8 data[0];
} udphdr;

typedef struct
{
	u8 smac[6];
	u8 dmac[6];
	u16 type;
} ethhdr;


typedef struct psd_header
{//伪头部，用于计算校验和
    u32 s_ip;//source ip
    u32 d_ip;//dest ip
    u8 mbz;//0
    u8 proto;//proto type
    u16 plen;//length
} psdhdr;

#define IP_SIZE sizeof(iphdr)
#define UDP_SIZE sizeof(udphdr)
#define ETH_SIZE sizeof(ethhdr)

int datalen;


u16 checksum(u16 *addr, int len);
char *ntop(char *, u32);

#define ADDR "192.168.199.217"
#define TUNADDR "192.168.199.217"
