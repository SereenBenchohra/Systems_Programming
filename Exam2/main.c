#include <stdio.h>
#include "p1.h"
int main()
{
   
   char insertTo[5];
   insertTo[0] = 'H';
   insertTo[1] = 'e';
   insertTo[2] = 'l';
   insertTo[3] = 'd';
   insertTo[4] = '\0';
   int atIndex = 2;
   char *toInsert = "llo, wor";

   char *newString = strInsert(insertTo, atIndex, toInsert);
   printf("%s\n", newString);

   return 0;


}
