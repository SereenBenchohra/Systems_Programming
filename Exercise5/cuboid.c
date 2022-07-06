#include "cuboid.h" 

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

