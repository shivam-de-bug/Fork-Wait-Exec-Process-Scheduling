/*Perform a binary search on a 16-element sorted array by passing half the array
  to a child process. The parent should define the array, print it and ask the user to
  input a target value. The parent will compare the target value to the mid element, call
  fork, and and the child will operate on half of the array. Similarly, the next child will
  operate on 1⁄4 of the array and so on. The child process that finds the target value
  should print its index in the terminal. If the target doesn’t exist in the array, print -1.
  Each parent should wait for their child to finish before returning.
  Input: Define a 16-element array in the code. The array must be sorted.
  Output: Output format should be as follows:
  Array: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
  Enter a target value: 6

  Target value’s index: 5*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ele = 16, tar = 0;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    // int arr[] = {1, 2, 5, 6, 7, 8, 9, 11, 13, 14, 16, 17, 19, 20, 22, 25};

    printf("Array: ");
    for (int i = 0; i < ele; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nEnter a target value: ");
    scanf("%d", &tar);

    int l = 0,r = ele - 1,m=0;
    
    while (l <=r) {
        m = (l + r) / 2;
        if (arr[m] == tar) {
            printf("Target value's index: %d\n", m);
            exit(0); 
        }
        
        int rc = fork(); 
        if (rc == 0) { 
            if (arr[m] <tar) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        } else if (rc < 0) { 
            printf("Fork failed");
            exit(1);
            
        } else {
           wait(NULL);
            exit(0); 
        }
    }

    printf("-1");
    return 0;
}
