#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the number of command-line arguments is not equal to 2
    if (argc != 2) {
        printf("Error. Expected 1 filename.\n");
        return 1;
    }

    // Attempt to open the file
    FILE *fptr = fopen(argv[1], "r");

    // Check if the file was successfully opened
    if (fptr == NULL) {
        printf("Error. Cannot open requested file.\n");
        return 1;
    }

    // Read number from file
    double num;
    fscanf(fptr, "%lf", &num);
    fclose(fptr);

    // Print JSON output
    printf("{\n");
    printf("  \"name\": \"Jiayu Yin\",\n");
    printf("  \"email\": \"jiayu.yin@student.manchester.ac.uk\",\n");
    printf("  \"number1\": %.2f,\n", num);  // Print num formatted to 2 decimal places
    printf("  \"number2\": %.3e\n", num);  // Print num in scientific notation with 3 digits after the decimal
    printf("}\n");

    return 0;
}