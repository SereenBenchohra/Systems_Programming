#include "ui.h"
#include "cuboid.h"

int main()
{

   double l, w, h;

   l = getLength();
   w = getWidth();
   h = getHeight();

   showResults(makeCuboid(l, w, h));

   return 0;
}
