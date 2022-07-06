 #include <stdlib.h>
 #include <stdio.h>

 #define TEN_MBYTES 1048576 // 1024 * 1024

 int main()
 {
   int *p; 
   p = NULL;
   if((p = malloc(sizeof(int) *TEN_MBYTES)) == NULL)
   {
      fprintf(stderr, "Failure to malloc p");
      exit(EXIT_FAILURE);

   }

   free(p);
   return 0;
 } 