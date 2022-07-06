#include <stdio.h>

#include "checkit.h"
#include "part8.h"

/* define testing functions */
void test_create_point1(void)
{
   struct point p = create_point(1.9, -2.7);

   checkit_double(p.x, 1.9);
   checkit_double(p.y, -2.7);
}

void test_create_point2(void)
{
   struct point p = create_point(0.2, 12.1);

   checkit_double(p.x, 0.2);
   checkit_double(p.y, 12.1);
}

void test_is_square1(void)
{
   Rect recta;
   recta.bottom_right = create_point(5, 1);
   recta.top_left = create_point(0,4);
   checkit_int(is_a_square(recta), FALSE);

}

void test_is_square2(void)
{
   Rect recta;
   recta.bottom_right = create_point(4, 0);
   recta.top_left = create_point(0,4);
   checkit_int(is_a_square(recta), TRUE);

}

void test_create_point(void)
{
   test_create_point1();
   test_create_point2();
}

void test_is_square(void)
{
   test_is_square1();
   test_is_square2();
}

int main(int arg, char *argv[])
{
   /* call testing function(s) here */
   test_create_point();
   test_is_square();

   return 0;
}
