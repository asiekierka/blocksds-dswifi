// SPDX-License-Identifier: MIT
//
// Copyright (C) 2005-2006 Stephen Stair - sgstair@akkit.org - http://www.akkit.org

// DSWifi Project - sgIP Internet Protocol Stack Implementation

#ifndef SGIP_ARP_H
#define SGIP_ARP_H

#include "sgIP_Config.h"
#include "sgIP_memblock.h"
#include "sgIP_Hub.h"

#define SGIP_ARP_FLAG_ACTIVE		0x0001
#define SGIP_ARP_FLAG_HAVEHWADDR	0x0002

typedef struct SGIP_ARP_RECORD {
	unsigned short flags, retrycount;
	unsigned long idletime;
	sgIP_Hub_HWInterface * linked_interface;
	sgIP_memblock * queued_packet;
	int linked_protocol;
	unsigned long protocol_address;
	char hw_address[SGIP_MAXHWADDRLEN];
} sgIP_ARP_Record;


typedef struct SGIP_HEADER_ARP {
	unsigned short hwspace;		// ethernet=1;
	unsigned short protocol;
	unsigned char hw_addr_len;
	unsigned char protocol_addr_len;
	unsigned short opcode;		// request=1, reply=2
	unsigned char addresses[8+12]; // sender HW, sender Protocol, dest HW, dest Protocol
} sgIP_Header_ARP;

#define SGIP_HEADER_ARP_BASESIZE	8

#ifdef __cplusplus
extern "C" {
#endif

	extern void	sgIP_ARP_Init();
	extern void sgIP_ARP_Timer100ms();
	extern void sgIP_ARP_FlushInterface(sgIP_Hub_HWInterface * hw);

	extern int sgIP_ARP_ProcessIPFrame(sgIP_Hub_HWInterface * hw, sgIP_memblock * mb);
	extern int sgIP_ARP_ProcessARPFrame(sgIP_Hub_HWInterface * hw, sgIP_memblock * mb);
	extern int sgIP_ARP_SendProtocolFrame(sgIP_Hub_HWInterface * hw, sgIP_memblock * mb, unsigned short protocol, unsigned long destaddr);
	
	extern int sgIP_ARP_SendARPResponse(sgIP_Hub_HWInterface * hw, sgIP_memblock * mb);
	extern int sgIP_ARP_SendGratARP(sgIP_Hub_HWInterface * hw);
	extern int sgIP_ARP_SendARPRequest(sgIP_Hub_HWInterface * hw, int protocol, unsigned long protocol_addr);
	


#ifdef __cplusplus
};
#endif


#endif
