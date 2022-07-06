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
   
   N =  strtol(argv[1], &end, 10);

   if(end == argv[1])
   {
      fprintf(stderr, "%s not an integer\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   printf("%d\n", N);

   // fork process 
   

   /* Child */
   if ( (child=fork()) == 0 )
   {
      int i; 
      printf("This is the child, pid %d\n", getpid());
      for(i = 0; i <= N; i++)
         if(i % 2 != 0) // check if its odd
            printf("%d\n", i);

   }
      
   else if (child == -1 )
   {
      perror("fork");
      exit(EXIT_FAILURE);
   }
   else /* parent */
   {
      int i;
      printf("This is the parent %d\n", getpid());
      for(i = 0; i <= N; i++)
         if(i % 2 == 0) // check if its even
            printf("%d\n", i);
      if (-1 == wait(&status))
      {
         perror("wait");
         exit(EXIT_FAILURE);
      }
      //printf("This is the parent, pid %d, signing off.\n", getpid()); 
  
   }

   return 0;
}


