#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[]) 
{
  pid_t child;
  int status;
  printf("Hello, world!\n");

  /* Child */
  if ( (child=fork()) == 0 )
    printf("This is the child, pid %d\n", getpid());
  else if (child == -1 )
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else /* parent */
  {
    printf("This is the parent %d\n", getpid());
    if (-1 == wait(&status))
    {
      perror("wait");
      exit(EXIT_FAILURE);
    }
    printf("This is the parent, pid %d, signing off.\n", getpid()); 
  
  }

  
   
  
  return 0;
}
