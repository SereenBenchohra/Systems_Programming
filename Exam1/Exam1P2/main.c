#include <stdio.h>
#include "p2.h"
int main()
{
   double True, False;
   True = approxEq(3.0010, 3.0010, 0.010);
   False = approxEq(5.002, 5.001, 0.10);

   printf("Trues value is %lf\n", True);
   printf("False value is %lf\n", False);


   return 0;

}
