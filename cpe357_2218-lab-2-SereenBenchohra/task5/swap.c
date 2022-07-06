#include <stdio.h>

void swap(int *a, int *b)
{
   int temp; 
   temp = *a; // saves the value of a into a temp
   *a = *b; // puts the b value into a 
   *b = temp; //saves the a value into b 
}

int main(void)
{

   int a, b;
   a = 3; 
   b = 2;
   printf("a: %d b : %d\n", a, b);
   swap(&a, &b);
   printf("a: %d b : %d\n", a, b);

   return 0;
}