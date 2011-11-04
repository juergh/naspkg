/* dhcpd.c
 *
 * udhcp Server
 * Copyright (C) 1999 Matthew Ramsay <matthewr@moreton.com.au>
 *			Chris Trew <ctrew@moreton.com.au>
 *
 * Rewrite by Russ Dill <Russ.Dill@asu.edu> July 2001
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>

#include "dhcpd.h"
#include "arpping.h"
#include "socket.h"
#include "options.h"
#include "files.h"
#include "serverpacket.h"
#include "common.h"
#include "signalpipe.h"
#include "static_leases.h"


/* globals */
struct dhcpOfferedAddr *leases;
struct server_config_t server_config;
static uint8_t hostname[MAX_HOSTNAME_LEN];	//+Wilson03232006
//uint8_t *hostname = NULL;	//+Wilson03232006


#ifdef COMBINED_BINARY	
int udhcpd_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	fd_set rfds;
	struct timeval tv;
	int server_socket = -1;
	int bytes, retval;
	struct dhcpMessage packet;
	uint8_t *state;
	uint8_t *server_id, *requested;
	uint32_t server_id_align, requested_align;
	unsigned long timeout_end;
	struct option_set *option;
	struct dhcpOfferedAddr *lease;
	struct dhcpOfferedAddr static_lease;
	int max_sock;
	unsigned long num_ips;
	static uint8_t *host = NULL;	//+Wilson03232006
	unsigned int len = 0; //+Wilson03232006

	uint32_t static_lease_ip;

	memset(&server_config, 0, sizeof(struct server_config_t));
	read_config(argc < 2 ? DHCPD_CONF_FILE : argv[1]);

	/* Start the log, sanitize fd's, and write a pid file */
	start_log_and_pid("udhcpd", server_config.pidfile);

	if ((option = find_option(server_config.options, DHCP_LEASE_TIME))) {
		memcpy(&server_config.lease, option->data + 2, 4);
		server_config.lease = ntohl(server_config.lease);
	}
	else server_config.lease = LEASE_TIME;

	/* Sanity check */
	num_ips = ntohl(server_config.end) - ntohl(server_config.start) + 1;
	if (server_config.max_leases > num_ips) {
		LOG(LOG_ERR, "max_leases value (%lu) not sane, "
			"setting to %lu instead",
			server_config.max_leases, num_ips);
		server_config.max_leases = num_ips;
	}
		
		
	leases = xcalloc(server_config.max_leases, sizeof(struct dhcpOfferedAddr));
	read_leases(server_config.lease_file);

	if (read_interface(server_config.interface, &server_config.ifindex,
			&server_config.server, server_config.arp) < 0)
		return 1;
	
	DBG_PRINT(printf("[dhcpd]server ip = %d\n", htonl(server_config.server));)
	

#ifndef DBG
	background(server_config.pidfile); /* hold lock during fork. */
#endif

	/* Setup the signal pipe */
	udhcp_sp_setup();

	timeout_end = time(0) + server_config.auto_time;
	
	/* loop until universe collapses */
	while(1) 
	{ 
		DBG_PRINT(printf("[dhcpd]wait DHCP message...\n");)
		if (server_socket < 0)
			if ((server_socket = listen_socket(INADDR_ANY, SERVER_PORT, server_config.interface)) < 0) {
				LOG(LOG_ERR, "FATAL: couldn't create server socket, %m");
				return 2;
			}

		max_sock = udhcp_sp_fd_set(&rfds, server_socket);
		if (server_config.auto_time) {
			tv.tv_sec = timeout_end - time(0);
			tv.tv_usec = 0;
		}
		if (!server_config.auto_time || tv.tv_sec > 0) {
			retval = select(max_sock + 1, &rfds, NULL, NULL,
					server_config.auto_time ? &tv : NULL);
		} else retval = 0; /* If we already timed out, fall through */

		if (retval == 0) {
			write_leases();
			timeout_end = time(0) + server_config.auto_time;
			continue;
		} else if (retval < 0 && errno != EINTR) {
			DEBUG(LOG_INFO, "error on select");
			continue;
		}

		switch (udhcp_sp_read(&rfds)) {
		case SIGUSR1:
			LOG(LOG_INFO, "Received a SIGUSR1");
			write_leases();
			/* why not just reset the timeout, eh */
			timeout_end = time(0) + server_config.auto_time;
			continue;
		case SIGTERM:
			LOG(LOG_INFO, "Received a SIGTERM");
			return 0;
		case 0: break;		/* no signal */
		default: continue;	/* signal or error (probably EINTR) */
		}

		if ((bytes = get_packet(&packet, server_socket)) < 0) { /* this waits for a packet - idle */
			if (bytes == -1 && errno != EINTR) {
				DEBUG(LOG_INFO, "error on read, %m, reopening socket");
				close(server_socket);
				server_socket = -1;
			}
			continue;
		}

		if ((state = get_option(&packet, DHCP_MESSAGE_TYPE)) == NULL) {
			DEBUG(LOG_ERR, "couldn't get option from packet, ignoring");
			continue;
		}

		/* Look for a static lease */
		static_lease_ip = getIpByMac(server_config.static_leases, &packet.chaddr);
		if(static_lease_ip)
		{
			printf("Found static lease: %x\n", static_lease_ip);
			memcpy(&static_lease.chaddr, &packet.chaddr, 16);
			static_lease.yiaddr = static_lease_ip;
			static_lease.expires = 0;
			lease = &static_lease;
		}
		else
			lease = find_lease_by_chaddr(packet.chaddr);

		/* Receive a DHCP message from client */
		DBG_PRINT(printf("[dhcpd] Receive a DHCP message from client\n");)
		switch (state[0]) 
		{
			case DHCPDISCOVER:
				DBG_PRINT(printf("[dhcpd] received DHCPDISCOVER\n");)
				if ((host = get_option(&packet, DHCP_HOST_NAME)) == NULL) 
				{
					DEBUG(LOG_ERR, "couldn't get option from packet, ignoring");
					strncpy(hostname, "", MAX_HOSTNAME_LEN);	//+Wilson03232006
				}
				else
				{
					strncpy(hostname, "", MAX_HOSTNAME_LEN);	//+Wilson04192007
					len = *(host);	//len of hostname
					strncpy(hostname, host+1, len);	//+Wilson03232006
					DEBUG(LOG_WARNING, "len = %d, client's hostname = %s\n", len, hostname);
				}
	
				if (sendOffer(&hostname[0], &packet) < 0) //+Wilson03232006
				{	
					LOG(LOG_ERR, "send OFFER failed");
				}
			break;
			
 			case DHCPREQUEST:
 				DBG_PRINT(printf("[dhcpd] received DHCPREQUEST\n");)
				requested = get_option(&packet, DHCP_REQUESTED_IP);
				server_id = get_option(&packet, DHCP_SERVER_ID);
	
				if (requested) memcpy(&requested_align, requested, 4);
				if (server_id) memcpy(&server_id_align, server_id, 4);
	
				if (lease) 
				{
					/* update the host name 08_29_2008_curtis */
					if ((host = get_option(&packet, DHCP_HOST_NAME)) == NULL) 
					{
						DBG_PRINT(printf("[dhcpd] host name is NULL\n");)
						strncpy(hostname, "", MAX_HOSTNAME_LEN);	
					}
					else
					{
						strncpy(hostname, "", MAX_HOSTNAME_LEN);	
						len = *(host);	//len of hostname
						strncpy(hostname, host+1, len);	
						DBG_PRINT(printf("len = %d, client's hostname = %s\n", len, hostname);)
						//DEBUG(LOG_WARNING, "len = %d, client's hostname = %s\n", len, hostname);
					}
					
					if (server_id) 
					{
						/* SELECTING State */
						DEBUG(LOG_INFO, "server_id = %08x", ntohl(server_id_align));
						if (server_id_align == server_config.server 
								&& 
								requested 
								&&
						    requested_align == lease->yiaddr) 
						{
							sendACK(&hostname[0], &packet, lease->yiaddr);	//+Wilson03222006
						}
					} 
					else 
					{
						if (requested) 
						{
							/* INIT-REBOOT State */
							if (lease->yiaddr == requested_align)
								sendACK(&hostname[0], &packet, lease->yiaddr);	//+Wilson03222006
							else sendNAK(&packet);
						} 
						else 
						{
							/* RENEWING or REBINDING State */
							if (lease->yiaddr == packet.ciaddr)
								sendACK(&hostname[0], &packet, lease->yiaddr);	//+Wilson03222006
							else 
							{
								/* don't know what to do!!!! */
								sendNAK(&packet);
							}
						}
					}
	
				/* what to do if we have no record of the client */
				} 
				else if (server_id) 
				{
					/* SELECTING State */
				} 
				else if (requested) 
				{
					/* INIT-REBOOT State */
					if ((lease = find_lease_by_yiaddr(requested_align))) 
					{
						if (lease_expired(lease)) 
						{
							/* probably best if we drop this lease */
							memset(lease->chaddr, 0, 16);
						/* make some contention for this address */
						} 
						else sendNAK(&packet);
					} 
					else if (requested_align < server_config.start 
									 ||
						   		 requested_align > server_config.end) 
					{
						sendNAK(&packet);
					} 
					/* else remain silent */
				} 
				else 
				{
					 /* RENEWING or REBINDING State */
				}
			break;
			
		case DHCPDECLINE:
			DBG_PRINT(printf("[dhcpd] DHCPDECLINE\n");)
			DEBUG(LOG_INFO,"received DECLINE");
			if (lease) 
			{
				memset(lease->chaddr, 0, 16);
				lease->expires = time(0) + server_config.decline_time;
			}
			break;
			
		case DHCPRELEASE:
			DBG_PRINT(printf("[dhcpd] DHCPRELEASE\n");)
			DEBUG(LOG_INFO,"received RELEASE");
			if (lease) lease->expires = time(0);
			break;
			
		case DHCPINFORM:
			DBG_PRINT(printf("[dhcpd] DHCPINFORM\n");)
			DEBUG(LOG_INFO,"received INFORM");
			send_inform(&packet);
			break;
			
		default:
			LOG(LOG_WARNING, "unsupported DHCP message (%02x) -- ignoring", state[0]);
		}
	}

	return 0;
}

