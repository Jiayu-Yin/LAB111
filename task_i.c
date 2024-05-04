#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    // Define constants
    #define N 201  // Maximum number of rows in the data array
    #define M 3    // Number of columns in the data array
    #define MAXCHAR 100  // Maximum number of characters in a line of the input file

    // Declare variables
    double data[N][M];  // Array to store the data read from the file
    char buffer[MAXCHAR];  // Buffer to store each line of the input file
    int row = 0;  // Counter for the current row being read
    int column = 0;  // Counter for the current column being read
    char *ptr;  // Pointer for the strtod function

    // Open the input file
    char fn[] = "data.csv";
    FILE *fptr;
    fptr = fopen(fn, "r");
    if (fptr == NULL) {
        printf("Error! Could not open file");
        return EXIT_FAILURE; // Exit if file not found
    }
    
    while (fgets(buffer, MAXCHAR, fptr)) {
        column = 0;
        row++;
        if (row == 1) {
            continue;  // Skip the header row
        }
        char* value = strtok(buffer, ", ");
        while (value) {  
            data[row-2][column] = strtod(value,&ptr);  // Convert string to double and store in data array
            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(fptr);  // Close the input file

    // Sort the data and calculate the median for each column
    double median[M];
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            for (int k = i + 1; k < N; k++) {
                if (data[i][j] > data[k][j]) {
                    double temp = data[i][j];
                    data[i][j] = data[k][j];
                    data[k][j] = temp;
                }
            }
        }    
        median[j] = data[N/2][j];  // Calculate median
    }

    // Print the median values
    printf("%.2f,%.2f,%.2f", median[0], median[1], median[2]);

    return EXIT_SUCCESS;
}