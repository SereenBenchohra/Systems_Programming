#include <stdio.h>

int main(int argc, char *argv[])
{
   for (size_t i = 1; i < argc; i++)
      if (argv[i][0] == '-')
         printf("%s\n",argv[i]);
      
   return 0;
}