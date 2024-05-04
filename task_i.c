#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {


    #define N 201
    #define M 3
    double data[N][M];

    #define MAXCHAR 100
    char buffer[MAXCHAR];
    int row = 0;
    int column = 0;
    char *ptr;

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
            continue;
        }
        char* value = strtok(buffer, ", ");
        while (value) {  
            data[row-2][column] = strtod(value,&ptr);
            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(fptr);
    fptr = NULL;

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
        median[j] = data[N/2][j];// Calculate median
    }

    // Print the result
    printf("%.2f,%.2f,%.2f", median[0], median[1], median[2]);




    return EXIT_SUCCESS;
}