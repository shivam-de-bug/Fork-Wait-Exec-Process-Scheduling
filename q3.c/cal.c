/*Contains a simple implementation of the cal command using Zeller's
  congruence. The program should take month and year as arguments and
  calculate the first day of the month using the formula for the Gregorian
  calendar. If the month and year are not provided, it should print an error
  message. Use Zeller’s congruence to determine the first day of the given
  month and construct the rest of the month.*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
	printf("Error: Please provide month and year as arguments.");
	return 1;}
    int m = atoi(argv[1]),y = atoi(argv[2]);
    if (m < 1 || m> 12||y<1 ) {
	printf("Error: Please enter a valid moth or year");
	return 1;}
	
    const char *mon[] = {"January", "February", "March", "April", "May", "June","July", "August", "September", "October", "November", "December"};
    
    char *days[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
    
    int day_m[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)){
        day_m[1] = 29;
    }
    
    if (m== 1 || m == 2) {
        m += 12;
        y--;
    }
    int day=1,k = y % 100,j = y / 100;
    int h = (day + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    int day1 = (h + 5) % 7;
    day1 = (day1 + 1) % 7;
   printf("     %s %d\n", mon[(m - 1) % 12], y + (m > 12 ? 1 : 0));

    printf(" Su Mo Tu We Th Fr Sa\n");

	int i = 0;
	while (i < day1) {
	    printf("   ");
	    i++;
	}

	int ori_mon = (m > 12) ? m - 12 : m;

	while (day <= day_m[ori_mon-1]) {
	    printf("%2d ", day);
	    if ((day + day1) % 7 == 0) {
		printf("\n");
	    }
	    day++;
	}			
	printf("\n");

    return 0;
}