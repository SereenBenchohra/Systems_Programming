/*
 * Provided file - DO NOT MODIFY !!!
 */
#include <stdio.h>

#define PI 3.141592 /* Close enough for this problem */

/* Prototype of the function you must write in a SEPARATE file.
 */
double sphereVolume(double radius, double pi);

int main()
{
   double radius, volume;

   printf("*\n* This program computes the volume a sphere!\n*\n");
   printf("Enter the radius of the sphere: ");
   scanf("%lf", &radius);

   /* The call to the function you must write in a SEPARATE file */
   volume = sphereVolume(radius, PI);

   printf("\nThe volume of a sphere with radius %f is %f\n", radius, volume);

   return 0;
}
