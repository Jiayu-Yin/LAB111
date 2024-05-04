#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <math.h> 
int main(void){
    double height = 0;
	double volume = 0;
	printf("Enter height: ");
	scanf("%lf", &height);
	
	
	// Your code below here
    height = fabs(height); // Using fabs to get the absolute value of height
	double radius = 2.2; // Define radius
	volume = M_PI * pow(radius, 2) * height; // Calculate the volume
	
	// Do not edit below here
	printf("Volume: %.2f", volume);
	return 0;
}