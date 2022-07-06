#include <assert.h>

double sphereVolume(double radius, double pi)
{
  
   double volume;

   assert (radius > 0);
   
   volume = (4.0/3.0) * pi * (radius * radius* radius);

   return volume;

}
