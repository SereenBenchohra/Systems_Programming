#include "part8.h"

int is_a_square(Rect rectangle)
{
   double width, height;
   width = rectangle.bottom_right.x - rectangle.top_left.x;
   height = rectangle.top_left.y - rectangle.bottom_right.y;
   if(height == width)
      return TRUE;
   return FALSE;
}

struct point create_point(double x, double y)
{
   struct point p;

   p.x = x;
   p.y = y;

   return p;
}
