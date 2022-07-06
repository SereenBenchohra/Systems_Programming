#include "order.h"

void swap(int *a, int *b)
{
   int *temp = *a;

   *a = *b;
   *b = *temp;
}

void orderTwo(int *a, int *b)
{
   if (*a > *b)
      swap(a, b);
}

void orderThree(int *a, int *b, int *c)
{
   orderTwo(a, b);
   orderTwo(b, c);
   orderTwo(a, b);
}
