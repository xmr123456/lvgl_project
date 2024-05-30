#include "devInfo.h"

int Runcommand(const char *cmd, char *result, int length)
{
    if (cmd == NULL)
    {
        printf("cmd is NULL");
        return -1;
    }
    FILE *stream;
    stream = popen(cmd, "r");
    if (stream == NULL)
    {
        printf("error to run cmd:%s", cmd);
        return -1;
    }
    if (result != NULL && length != 0)
    {
        int i = fread(result, sizeof(char), length - 1, stream);
        if (i > (length - 1))
        {
            printf("error to read result of %s ", cmd);
            pclose(stream);
            return -1;
        }
        result[i] = '\0';
    }
    pclose(stream);
    return 0;
}

void get_mem_info(char *name, unsigned long long *total, unsigned long long *used, unsigned long long *free, unsigned long long *shared, unsigned long long *buffer, unsigned long long *avaiable, unsigned long long *mem_per)
{
    char result[1024] = {0};
    Runcommand("free  | grep Mem", result, sizeof(result));
    sscanf(result, "%s %lld %lld %lld %lld %lld %lld", name, total, used, free, shared, buffer, avaiable);
}

void get_cpu_percent()
{
    FILE *fd;
    char name[64] = {0};
    char buff[256];
    unsigned long long temp[10];
    int total, idel, percent;

    fd = fopen("/proc/stat", "r");
    if (fd == NULL)
    {
        printf("open %s err\n", "/proc/stat");
        return -1;
    }

    while (fgets(buff, sizeof(buff), fd))
    {
        sscanf(buff, "%s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", name, &temp[0], &temp[1], &temp[2], &temp[3], &temp[4], &temp[5], &temp[6], &temp[7], &temp[8], &temp[9]);
        total = idel = 0;
        for (int i = 0; i < 10; i++)
        {
            total = total + temp[i];
            if (i == 3)
                idel = temp[i];
        }

        if (strcmp(name, "cpu") == 0)
            break;
    }
    fclose(fd);

    if (total == 0)
        percent = 100 * (total - idel) / (total + 1);
    else
        percent = 100 * (total - idel) / total;
    return percent;
}

int get_cpu_freq()
{
    char *path = "/sys/bus/cpu/devices/cpu0/cpufreq/cpuinfo_cur_freq";
    FILE *fd;
    char buff[256] = {0};

    if (path == NULL || access(path, F_OK) != 0)
    {
        return -1;
    }
    fd = fopen(path, "r");
    if (fd == NULL)
    {
        printf("open %s err\n", path);
        return -1;
    }
    if (fgets(buff, sizeof(buff), fd) != NULL)
    {
        fclose(fd);
        return atoi(buff);
    }
    fclose(fd);
    return -1;
}
int get_cpu_temperature()
{
    int temp = -9999;
    int fd = -1;
    char read_buff[128];
    int ret_val;
    fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
    if (fd == -1)
    {
        printf("open %s err!\n", "/sys/class/thermal/thermal_zone0/temp");
        return temp;
    }
    ret_val = read(fd, read_buff, sizeof(read_buff));
    temp = atoi(read_buff);
    close(fd);
    return temp;
}

void get_system_version(char *system_version)
{
    char type[1024] = {0};
    char version[1024] = {0};
    FILE *fd1 = fopen("/proc/sys/kernel/ostype", "r");
    if (fd1 == NULL)
        printf("open %s err\n", "/proc/sys/kernel/ostype");
    else
    {
        fgets(type, sizeof(type), fd1);
        fclose(fd1);
    }

    FILE *fd2 = fopen("/proc/sys/kernel/osrelease", "r");
    if (fd1 == NULL)
        printf("open %s err\n", "/proc/sys/kernel/osrelease");
    else
    {
        fgets(version, sizeof(version), fd2);
        fclose(fd2);
    }

    strcat(system_version, type);
    strcat(system_version, " ");
    strcat(system_version, version);
}

int get_system_runtime()
{
    char buf[1024] = {0};
    FILE *fd = fopen("/proc/uptime", "r");
    if (fd == NULL)
    {
        printf("open %s err\n", "/proc/uptime");
        return -1;
    }
    fgets(buf, sizeof(buf), fd);
    fclose(fd);
    return atoi(buf);
}

// int set_net_info(char *net_info)
// void get_net_ip(char *ip)
// void get_net_mac(char *mac);

int get_net_status(char *net_dev)
{
    char path[1024] = {0};
    char buf[1024] = {0};
    sprintf(path, "/sys/class/net/%s/carrier", net_dev);
    FILE *fd = fopen(path, "r");
    if (fd == NULL)
    {
        printf("open %s err\n", path);
        return -1;
    }
    fgets(buf, sizeof(buf), fd);
    fclose(fd);
    return atoi(buf);
}
void set_date(int year, int month, int day, int hour, int minute, int second)
{
    char command[1024] = {0};
    sprintf(command, "date -s \" %s-%s-%s %s:%s:%s\"", year, mouth, day, hour, minute, second);
    Runcommand(command, NULL, 0);
}

void get_wifi_list(struct wifi_info *info_list)
{
    char *command = "wpa_cli -i wlan0 scan_result";
    FILE *stream;
    stream = popen(command, "r");
    if (stream == NULL)
    {
        printf("error to run cmd:%s", cmd);
        return;
    }

    
    if (result != NULL && length != 0)
    {
        int i = fread(result, sizeof(char), length - 1, stream);
        if (i > (length - 1))
        {
            printf("error to read result of %s ", cmd);
            pclose(stream);
            return -1;
        }
        result[i] = '\0';
    }
    pclose(stream);
}
void get_wifi_state()
{
    /*
    do {
        line = stream.readLine().trimmed();
                qDebug()<<line;
        if ( line.startsWith("ssid") ){
            QStringList tmp = line.split("=");
                        wifi_connect_status = tmp[1];
                }
                else if( line.startsWith("wpa_state") ){
                        QStringList tmp = line.split("=");
                        if(tmp[1] == "COMPLETED"){
                                if(wifi_status != wifi_connect_status){
                    emit wifiConnected(wifi_connect_status);
                    command = "udhcpc -i wlan0 -t 3 -n -q -b";
                    msic_process->start(command);
                }
                        }

                        else{
                                wifi_connect_status = "";
                                emit wifiConnected(wifi_connect_status);
                        }
                }
    } while (!line.isNull());
    wifi_status = wifi_connect_status;
    */
    char *command = "wpa_cli -i wlan0 status";
    FILE *stream;
    stream = popen(command, "r");
    if (stream == NULL)
    {
        printf("error to run cmd:%s", command);
        return;
    }

    if (result != NULL && length != 0)
    {
        int i = fread(result, sizeof(char), length - 1, stream);
        if (i > (length - 1))
        {
            printf("error to read result of %s ", cmd);
            pclose(stream);
            return -1;
        }
        result[i] = '\0';
    }
    pclose(stream);
}
void wifi_open()
{
    char command[1024] = {0};
    char buf[1024] = {0};
    strcat(command, "ifconfig | grep wlan0 | wc -l");
    Runcommand(command, buf, sizeof(buf));
    if (atoi(buf) == 0 && strlen(buf) > 0)
    {
        memset(command, 0, sizeof(command));
        strcat(command, "ifconfig wlan0 up");
        Runcommand(command, NULL, 0);
    }
    memset(command, 0, sizeof(command));
    strcat(command, "wpa_supplicant -Dnl80211 -iwlan0 -c/etc/wpa_supplicant.conf -B");
    Runcommand(command, NULL, 0);
}
void wifi_close()
{
    char *command = "ifconfig wlan0 down";
    Runcommand(command, NULL, 0);
}

void wifi_connect(char *ssid, char *passwd)
{
    char command[1024] = "wpa_cli -i wlan0 disconnect";
    Runcommand(command, NULL, 0);

    char shell_data[1024] = {0};
    char buf[1024] = {0};
    if (strlen(passwd))
    {
        strcat(shell_data, "#!/bin/sh\n");
        strcat(shell_data, "wpa_cli -i wlan0 remove_network 0\n");
        strcat(shell_data, "wpa_cli -i wlan0 add_network\n");

        memset(buf, 0, sizeof(buf));
        sprintf(buf, "wpa_cli -i wlan0 set_network 0 ssid \'\"%s\"\'\n", ssid);
        strcat(shell_data, buf);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "wpa_cli -i wlan0 set_network 0 psk \'\"%s\"\'\n", passwd);
        strcat(shell_data, buf);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "wpa_cli -i wlan0 select_network 0\n");
        strcat(shell_data, buf);
    }
    else
    {
        strcat(shell_data, "#!/bin/sh\n");
        strcat(shell_data, "wpa_cli -i wlan0 remove_network 0\n");
        strcat(shell_data, "wpa_cli -i wlan0 add_network\n");

        memset(buf, 0, sizeof(buf));
        sprintf(buf, "wpa_cli -i wlan0 set_network 0 ssid \'\"%s\"\'\n", ssid);
        strcat(shell_data, buf);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "wpa_cli -i wlan0 set_network 0 key_mgmt NONE\n");
        strcat(shell_data, buf);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "wpa_cli -i wlan0 select_network 0\n");
        strcat(shell_data, buf);
    }
    FILE *fd = fopen("/usr/share/connect_wifi.sh", "w");
    if (fd == NULL)
    {
        printf("open %s err\n", "/usr/share/connect_wifi.sh");
        return;
    }
    fwrite(shell_data, sizeof(shell_data), 1, fd);
    fclose(fd);
    Runcommand("chmod a+x /usr/share/connect_wifi.sh", NULL, 0);
    Runcommand("/usr/share/connect_wifi.sh", NULL, 0);
}
void wifi_disconnect()
{
    char *command = "wpa_cli -i wlan0 disconnect";
    Runcommand(command, NULL, 0);
}