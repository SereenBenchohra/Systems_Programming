#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int len;
   double v1, v2, total;
   char oper;
   v1 = sscanf(" %g", argv[0]);
   v2 = sscanf(" %g", argv[2]);
   sscanf(argv[1],"%c", &oper);

   len = argc - 1;

   if(v1 != 0 && v2 != 0 && len == 3)
   {
      if(oper == '+')
         total = v1 + v2;    
      if(oper == '-')
         total = v1 - v2;
      if(oper == 'x')
         total = v1 * v2;
      if(oper == '/')
         total = v1/v2;        
      else
      {
         fprintf(stderr,"Usage: calc value [+|-|x|/] value\n");
         exit(EXIT_FAILURE);
      }
   }

   else
   {
      fprintf(stderr,"Usage: calc value [+|-|x|/] value\n");
      exit(EXIT_FAILURE);
   }

printf("%g %c %g = %g", v1, oper, v2, total);

return 0;

}
