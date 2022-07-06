#include <stdio.h>


int main()
{
   FILE* file;
   int c;



   while( (c = getchar()) != EOF)
      printf("The ASCII value for %c is 0x%0x\n", c, c);
      
  

   return 0;

}
