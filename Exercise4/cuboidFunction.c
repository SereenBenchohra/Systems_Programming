#include <stdio.h>

typedef struct 
{
   double l, w, h;
} Cuboid;

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

Cuboid makeCuboid(double length, double width, double height)
{
   Cuboid cuboid;
   
   cuboid.l = length;
   cuboid.w = width;
   cuboid.h = height;

   return cuboid;

}

double volume(Cuboid cuboid)
{
   return cuboid.l * cuboid.w * cuboid.h;
}

double surfaceArea(Cuboid *cuboid)
{

   return (2 * cuboid->l * cuboid->w) + 
      (2 * cuboid->l * cuboid->h) + (2 * cuboid->w * cuboid->h); 
}

void showResults(Cuboid cuboid)
{
   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", volume(cuboid), 
      surfaceArea(&cuboid) , cuboid.l, cuboid.w, cuboid.h);  
}
int main()
{

   double l, w, h;

   l = getLength();
   w = getWidth();
   h = getHeight();

   showResults(makeCuboid(l, w, h));

   return 0;
}
