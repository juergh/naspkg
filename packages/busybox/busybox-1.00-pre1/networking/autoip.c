//royc create this file for auto ip function
#include <stdio.h>
#include <sys/time.h>
#include <sys/file.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define AUTO_IP_DBG

extern void bb_show_usage(void);
extern char* get_hw_info(char *ifname);
extern int my_arping_main(char* ifname, char* ifip);
extern int my_ifconfig_main(char*, char*);

int autoip_main(int argc, char *argv[])
{
	int		status, i;
	char	ifname[16];
	char 	*hw_mac;
	char 	*p;
	char	*set_ip;
	char 	set_ip_1[4], set_ip_2[4];
	unsigned int  to_int_1, to_int_2;
	struct in_addr int_addr;

	
	if( argc != 2 )
	{
		bb_show_usage();
	}
	
	//copy network interface name
	strcpy(ifname, argv[1]);
	
	//get hardware mac address
	hw_mac = get_hw_info(ifname);

#ifdef AUTO_IP_DBG
	printf("\n%s HWaddr %s  \n", ifname, hw_mac);
#endif
	
	//determine a IP for this interface
	p = strtok(hw_mac, ":");
	for(i=0 ; i<5; i++)
	{
		p = strtok(NULL, ":");
		if(i==3)
		{
			strcpy(set_ip_1, p);
		}
		else if(i == 4)
		{
			strcpy(set_ip_2, p);
		}
	}
	
#ifdef AUTO_IP_DBG
	printf("get last 2 items from MAC = %s %s \n", set_ip_1, set_ip_2);
#endif
	
	//convert from string(hex) to int(dec)
	to_int_1 = (unsigned int)strtol(set_ip_1, NULL, 16);
	to_int_2 = (unsigned int)strtol(set_ip_2, NULL, 16);
	
	if(to_int_1 == 0 && to_int_2 == 0)
	{
		to_int_2 = 1;
	}
	
	while(1)
	{
		p = (char*)&int_addr;
		*p = 169;
		*(p+1) = 254;
		*(p+2) = to_int_1;
		*(p+3) = to_int_2;
		
		set_ip = inet_ntoa(int_addr);

#ifdef AUTO_IP_DBG
		printf("IP Now = %s\n", set_ip);
#endif

		//ARP Ping function
		if( fork() == 0 )
		{
			
#ifdef AUTO_IP_DBG
			printf("\n");
#endif
			
			//start send arp ping
			my_arping_main(ifname, set_ip);
		}
		else
		{
			wait(&status);
			
			i = WEXITSTATUS(status);
			
#ifdef AUTO_IP_DBG			
			printf("ARPING return value = %d\n", i);
#endif

			//if i == 0 means that ARP Probe not get any reply
			if(i == 0)
			{
				break;
			}
			else if(i == -1)
			{
				printf("Ohhh! System someting wrong!\n");
				return -1;
			}
			else
			{
				//increase IP
				if(to_int_1 == 255 && to_int_2 == 255)
				{
					to_int_1 = 0;
					to_int_2 = 1;
				}
				else if(to_int_2 == 255)
				{
					to_int_1 ++;
					to_int_2 = 1;		//royc 20040826
				}
				else
				{
					to_int_2 ++;
				}
				continue;
			}
		}
	}
	
	strcat(ifname, ":0");

#ifdef AUTO_IP_DBG
	printf("\nifconfig: set interface %s to %s\n\n", ifname, set_ip);
#endif
	
	my_ifconfig_main(ifname, set_ip);
	
	return 0;
}

