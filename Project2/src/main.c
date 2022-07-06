#include <stdio.h>
#include "FileRead.h"
#include "wordCount.h"

int main(int argc, char *argv[])
{
   
   flagCheck flag;
   wordData data;
   readFile(&flag,argc, argv, &data);

   return 0;
}
