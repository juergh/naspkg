#ifndef _SERVERPACKET_H
#define _SERVERPACKET_H

#include "packet.h"

int sendOffer(uint8_t *hostname, struct dhcpMessage *oldpacket);	//+Wilson03222006
int sendNAK(struct dhcpMessage *oldpacket);
int sendACK(uint8_t *hostname, struct dhcpMessage *oldpacket, uint32_t yiaddr);	//+Wilson03222006
int send_inform(struct dhcpMessage *oldpacket);


#endif
