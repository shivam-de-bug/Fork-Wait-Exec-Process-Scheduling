/*Write a program where the parent process has 7 children. Each child generates
  4 random numbers from 1 to 100, calculates their mean, prints it in a new line and
  returns. The parent should wait for the children to finish and then return.
  Output: 7 random number means calculated by each child.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    
    for (int i = 0; i < 7; i++) {
        
        int rc = fork(); 
        if (rc == 0) { 
            // Child process
            float avg = 0.0;
            for (int j = 0; j < 4; j++) {
                 srand(time(NULL)+getpid());
                avg += rand() % 100 + 1; 
            }
            avg = avg / 4; 
            
            printf("Child %d Mean = %.2f\n", i + 1, avg);
            
            exit(0); 
        } else if (rc < 0) { 
            
            printf("Fork failed\n");
            exit(1); 
        }
    }

    
    for (int i = 0; i < 7; i++) {
        wait(NULL); 
    }

    return 0; 
}