#include <stdio.h>

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

double volume(double l, double w, double h)
{
  
   return l * h * w;

}

double surfaceArea(double l, double w, double h)
{

   return (2 * l * w) + (2 * l * h) + (2 * w * h); 
}

void showResults(double l, double w, double h)
{
   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", volume(l, w, h), 
      surfaceArea(l, w, h), l, w, h);  
}

int main()
{

   double l, w, h;
   l = getLength();
   w = getWidth();
   h = getHeight();

   showResults(l, w, h);

   return 0;
}
