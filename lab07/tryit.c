#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define SUCCESS 0
#define FAILURE 1

/*  The exec() functions return only if an error has occurred.  The return value is -1, and errno is set to indicate the error. */ 
void usageError()
{
   fprintf(stderr, "usage: tryit command\n");
   exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[]) 
{
   pid_t child;
   int pidNum, status, childStat;

   childStat = SUCCESS;
   
   /* before the fork */

   /* check the command line args */
   if (argc != 2 )
      usageError();

   if( access( argv[1], F_OK ) != 0 )
   {
      perror(argv[1]);
      exit(EXIT_FAILURE);
   } 
   
   /* fork() */
   /* Child */
   if ( (child=fork()) == 0 ) /* after the fork */
   {
      /*find a way to get PID and status */
      /* exec the given program */ 
      pidNum = getpid();
      if(-1 == execl(argv[1], argv[1], NULL))
      {
         perror("exec");
         childStat = FAILURE;
         exit(EXIT_FAILURE);
      }
   }  
   else if (child == -1 )
   {
      perror("fork");
      exit(EXIT_FAILURE);
   }
   else /* parent */
   {
      /* wait() for child */
      if (-1 == wait(&status))
      {
         perror("wait");
         exit(EXIT_FAILURE);
      }
  
  }

   

   /* after the exit */
   /* report on child's success */
   if(childStat == SUCCESS)
      printf("Process %d succeeded\n", pidNum );
   else
      printf("Process %d exited with an error value\n", pidNum );
   /* exit with child's status */ 
   return childStat;
}

/* 
  execl("/bin/ls","ls",NULL);
  perror("/bin/ls");
  exit(EXIT_FAILURE);

*/