#include <stdio.h>
#include "order.h"

int main()
{
   int a, b, c;

   printf("Enter any three int values to reorder: ");

   scanf("%d%d%d", &a, &b, &c);
   orderThree(&a, &b, &c);

   printf("The values in ascending order are: %d %d %d\n", a, b, c);

   return 0;
}
