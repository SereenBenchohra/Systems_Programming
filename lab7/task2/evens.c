#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   pid_t child;
   int status;

   if(argc != 2)
   {
      perror("Invalid Number of Arguments");
      exit(EXIT_FAILURE);
   }


   // checks if argument is integer other wise fail
   int N;
   char *end;
   
   N =  strtol(argv[1], &end, 10); // converts string to integer 

   if(end == argv[1]) // raises error if not integer
   {
      fprintf(stderr, "%s not an integer\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   printf("Evens print\n");
   
   int i;
   for(i = 0; i <= N; i++)
      if(i % 2 == 0) // check if its even
         printf("%d\n", i);


   return 0;
}


