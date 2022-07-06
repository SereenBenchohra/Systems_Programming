
#include <stdio.h>
#include "p3.h"

int main()
{

   int *min ;
   int *max;
   double *avg;
   
   int  size; 
   &min = 0;
   &max = 0;
   &avg = 0;
   size = 4;
   int array[4];
   array[4] = {4, 3, 2, 1};

   minMaxAvg(array, size, min, max, avg);
   printf("Min is %d, Max is %d, Average is %g\n", *min, *max, *avg);
   


   return 0;

}
