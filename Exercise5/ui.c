#include <stdio.h>
#include "cuboid.h"

double getLength()
{
   double l;

   printf("Enter the length of the cuboid: ");
   scanf("%lf", &l);
   
   return l;

}

double getWidth()
{

   double w;

   printf("Enter the  width of the cuboid: ");
   scanf("%lf", &w);

   return w;

}   

double getHeight()
{
   double h;

   printf("Enter the height of the cuboid: ");
   scanf("%lf", &h);

   return h;

}

void showResults(Cuboid cuboid)
{
   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", volume(cuboid), 
      surfaceArea(&cuboid) , cuboid.l, cuboid.w, cuboid.h);  
}
