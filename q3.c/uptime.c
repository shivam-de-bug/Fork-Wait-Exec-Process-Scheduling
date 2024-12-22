/*Contains a simple implementation of the uptime command. This
  program should print the system's uptime using the sysinfo() function. If no
  additional options are provided, print the uptime in hours, minutes, and
  seconds. Add an error message if there are any issues retrieving the uptime.*/


#include <stdio.h>
#include <sys/sysinfo.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) {
        fprintf(stderr, "Failed to get system info: %s\n", strerror(errno)); 
        exit(1);
    }
    long uptime = sys_info.uptime;
    printf("System Uptime: %02ld hours, %02ld minutes, %02ld seconds\n",uptime / 3600 , (uptime % 3600) / 60, uptime % 60);

    return 0;
}