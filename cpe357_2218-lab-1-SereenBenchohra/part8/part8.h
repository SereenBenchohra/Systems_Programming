#ifndef PART8_H
#define PART8_H

#define TRUE  1
#define FALSE 0

typedef struct point
{
   double x;
   double y;
}Point;

typedef struct rect
{
   Point top_left, bottom_right;
}Rect;

int is_a_square(Rect rectangle);
struct point create_point(double x, double y);

#endif
