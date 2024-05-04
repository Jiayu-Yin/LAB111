#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main(void) {
    // Set email address here	
    char email[] = "jiayu.yin@student.manchester.ac.uk";

    // Open file for writing
    FILE *fptr;
    fptr = fopen("certificate.txt", "w");
    if (fptr == NULL) {// display error if can't open file
        printf("Error. Not able to open the file.");
        return EXIT_FAILURE;
    }

    // Get current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char dateStr[20];  // Ensure the buffer is large enough
    strftime(dateStr, sizeof(dateStr), "%b %-2d %Y", tm);  // Format date

    // Print the text
    fprintf(fptr, "Hello. My email address is:\n");
    fprintf(fptr, "%s\n", email);
    fprintf(fptr, "I completed the course on %s", dateStr);

    // Close and tidy up
    fclose(fptr);
    fptr = NULL;
    return EXIT_SUCCESS;
}