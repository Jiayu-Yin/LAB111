#include <stdio.h>

int main() {
    char my_email[] = "jiayu.yin@student.manchester.ac.uk"; // Store the email address

    int n; // Variable to store the user's input for index

    printf("Enter an integer: ");
    scanf("%d", &n);

    // Check if the input is negative
    if (n < 0) {
        printf("Error");
        return 1; // Stop the program early
    }

    // Check if the input is within the valid range
    if (n >= sizeof(my_email) / sizeof(my_email[0]) - 1) {
        printf("Error");
        return 1; // Stop the program early
    }

    switch (my_email[n]) {
        case 'a': case 'e': case 'i': case 'o': case 'u':  // Vowels
        case 'A': case 'E': case 'I': case 'O': case 'U':  // Including uppercase vowels
            printf("Vowel");
            break;
        default:
            printf("Not vowel");
    }

    return 0;
}