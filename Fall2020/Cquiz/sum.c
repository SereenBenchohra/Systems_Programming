#include <stdio.h>

int sum(int x, int y)
{
   int sum;

   do {
      printf("x : %d \n", x);
      sum += x;
      x+= 1;

   }while(x <= y);

   return sum;

}

int main()
{
   int x, y, sum1;
   x= 2;
   y = 5;

   sum1 = sum(x, y);
   
   printf("sum1 : %d \n", sum1);

   return 0;

}

