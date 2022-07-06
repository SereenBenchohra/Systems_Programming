#include <stdio.h>

int main()
{

   double length, width, height;
   double SA, V;

   printf("Enter the length of the cuboid: ");
   scanf("%lf", &length);

   printf("Enter the  width of the cuboid: ");
   scanf("%lf", &width);

   printf("Enter the height of the cuboid: ");
   scanf("%lf", &height);

   SA = (2 * length * width) + (2 * length * height) + (2 * width * height); 
   V = length * height * width;
   
   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", V, 
      SA, length, width, height);  

   return 0;
}
