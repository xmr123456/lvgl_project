#ifndef DEVINFO_H
#define DEVINFO_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/if.h>
#include <arpa/inet.h>

struct wifi_info
{
    char wifi_name[1024];
    char wifi_state[1024];
    int wifi_key_flag;
};

int Runcommand(const char *cmd, char *result, int length);

int get_cpu_percent();
int get_cpu_freq();
int get_cpu_temperature();
void get_mem_info(char *name, unsigned long long *total, unsigned long long *used, unsigned long long *free, unsigned long long *shared, unsigned long long *buffer, unsigned long long *avaiable, unsigned long long *mem_per);

void get_system_version(char *system_version);
int get_system_runtime();
//int set_net_info(char *net_info);
//void get_net_ip(char *ip);
//void get_net_mac(char *mac);
int get_net_status(char *net_dev);
void set_date(int year,int month,int day,int hour,int minute,int second);
void get_wifi_list(struct wifi_info *info_list);
void get_wifi_state();
void wifi_open();
void wifi_close();
void wifi_connect(char *ssid,char *passwd);
void wifi_disconnect();
#endif