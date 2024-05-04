#include <stdio.h>
#include <stdlib.h>
#include "task_g.h"

int main(void) {

    // Your code below here
    FILE *file = fopen("number.txt", "r");
    if (!file) {
        printf("Error!\n");
        return 1;
    }

    double numbers[20];
    int count = 0;
    
    // Read 20 numbers from the file
    while (count < 20 && fscanf(file, "%lf", &numbers[count]) == 1) {
        count++;
    }
    fclose(file);

    // Check if we read less than 20 numbers
    if (count < 20) {
        printf("Error!\n");
        return 1;
    }

    double max;
    find_max_less_than_10(numbers, count, &max);

    if (max == -1) {  // If no valid number was found
        printf("Error!\n");
    } else {
        printf("%.2f\n", max);
    }
    
	


    return 0;
}