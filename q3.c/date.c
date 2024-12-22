/*Contains a simple implementation of the date command. This
  program should print the current date in at least three different formats. The
  user can pass options/flags to specify the desired format (e.g., -u for UTC, -r
  for RFC 2822 format). If no flag is passed, it should print the default date and
  time format, similar to the linux date command.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    
    time_t cur = time(NULL);
    struct tm *local_time_info = localtime(&cur);
    char arr[100];
    if (argc==1){
        strftime(arr, 100, "%A %d %B %Y %I:%M:%S %p %Z",local_time_info);
    }
    
    else if(strcmp(argv[1], "-u") == 0) {
        struct tm *utc_time_info = gmtime(&cur);
        strftime(arr, 100, "%a %b %d %H:%M:%S UTC %Y",utc_time_info);

    } else if (strcmp(argv[1], "-r") == 0) {
        
        strftime(arr,100, "%a, %d %b %Y %H:%M:%S %z", local_time_info);
    }
    printf("%s\n", arr);
    return 0;
}