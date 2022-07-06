#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   pid_t child1, child2;
   int status;

/*    if(argc != 2)
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

   printf("%d\n", N); */

   // fork process 
   

   /* 1st Child */
   if ( (child1=fork()) == 0 )
   {
      
      printf("This is the child 1, pid %d\n", getpid());
      execl("/home/sbenchoh/KeenCPE357/lab7/task2/evens",argv[0], argv[1], (char *)NULL );

   }
      
   else if (child1 == -1 )
   {
      perror("fork");
      exit(EXIT_FAILURE);
   }

   else if((child2 = fork()) == 0) // 2nd child
   {
      printf("This is the child 2, pid %d\n", getpid());
      execl("/home/sbenchoh/KeenCPE357/lab7/task2/odds", argv[0], argv[1], (char *) NULL);
   }

   else if (child2 == -1 )
   {
      perror("fork");
      exit(EXIT_FAILURE);
   }
   else /* parent */
   {
      if (-1 == wait(NULL)) // wait for child process to finish
      {
         perror("wait");
         exit(EXIT_FAILURE);
      }

      if (-1 == wait(NULL)) // wait for child process to finish
      {
         perror("wait");
         exit(EXIT_FAILURE);
      }
      //printf("This is the parent, pid %d, signing off.\n", getpid()); 
  
   }

   return 0;
}


