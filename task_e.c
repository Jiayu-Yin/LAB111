#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error. Expected 1 filename.");
        return 1;
    }

   	double num;
	FILE *fptr;
	fptr = fopen(argv[1], "r");

    if (fptr == NULL) {
        printf("Error. Cannot open requested file.");
        return 1;
    }

    fscanf(fptr, "%lf", &num);
    fclose(fptr);

    printf("{\n");
    printf("  \"name\": \"Jiayu Yin\",\n");
    printf("  \"email\": \"jiayu.yin@student.manchester.ac.uk\",\n");
    printf("  \"number1\": %.2f,\n", num);  // Print num formatted to 2 decimal places
    printf("  \"number2\": %.3e\n", num);  // Print num in scientific notation with 3 digits after the decimal
    printf("}\n");

    return 0;
}