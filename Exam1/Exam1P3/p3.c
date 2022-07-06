#include "p3.h"

void minMaxAvg(int *array, int size, int *min, int *max, double *avg)
{
   int i;
   double total;
   *min = array[0];
   *max = array[0];
   for (i = 0; i < size; i++)
   {  
      total += array[i];
      if(array[i] < *min)
         *min = array[i];
      if(array[i] > *max)
         *max = array[i];
   }
   *avg = total/ (double)size;

}
