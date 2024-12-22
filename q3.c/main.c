/*This program will run all the executables of the above programs as
  child processes using the fork-wait-exec sequence. First, create 3 child
  processes using fork. Then, inside the child processes, call one of the exec
  functions to execute the above programs. Each child will run one program.
  The parent process will wait for all child processes to finish before returning.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create_child(const char *path, char *const args[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        execv(path, args);
        perror("execv failed");
        exit(1);
    }
}

int main() {
    
    char *com[][4] = {
        {"./date", NULL},
        {"./cal", "1", "2024", NULL},
        {"./uptime", NULL}
    };

    
     int i = 0;
    while (i < 3) {
        create_child(com[i][0], com[i]);
        i++;
    }

    int j = 0;
    while (j < 3) {
        int status;
        if (wait(&status) == -1) {
            perror("wait failed");
            exit(1);
        }
        j++;
    }

    return 0;
}