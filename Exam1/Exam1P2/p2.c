#include <stdlib.h>
#include "p2.h"

int approxEq(double a, double b, double epsilon)
{
   int True; 
   double diff1, diff2;
   diff1 = (a - b);
   diff2 = b - a;
   if( diff1 <= epsilon || diff2 <= epsilon)
      True = 1;
   else 
      True = 0;

   return True;
}
