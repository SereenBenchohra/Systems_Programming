#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include "execCommands.h"


#define WRITE_END 1
#define READ_END 0

void usage(char *name){
   fprintf(stderr,"usage: %s <stages>\n", name);
   exit(EXIT_FAILURE);
}



/*checks for number of Pipes  */
int checkforPipes(char **parsedLine)
{
   
   int i, npipes;
   npipes = 0;


   for(i = 0; parsedLine[i] != NULL; i++)
   {
      
      if(strcmp(parsedLine[i],"|") == 0)
         npipes++;


      if((strcmp(parsedLine[i],"|") == 0) && (strcmp(parsedLine[i+1],"|") == 0))
         { 
            fprintf(stderr, "invalid null command ");
            exit(EXIT_FAILURE);
         }
   }

   return npipes;

}

/* if there are no pipes exec and fork normally */

void exec_system(char **parsedLine)
{
   pid_t pid;
   int status;

   if( (pid = fork()) == -1){
     
     fprintf(stderr, "\n Fork Failed"); 
     exit(EXIT_FAILURE);
     

    } 
    
    /* child process */
    else if (pid == 0) 
    { 
        if (execvp(parsedLine[0], parsedLine) < 0) { 
            
            fprintf(stderr, "\nCould not execute commands");
            exit(EXIT_FAILURE);
        } 
        exit(0); 
    } else 
    { 
        
        /* waiting for child to terminate */ 
        if(wait(&status))
        {
           perror("wait");
           exit(EXIT_FAILURE);
        }

    } 
   

}



void exec_piped(char ** parsedLine, int npipes)
{
   int old[2], next[2];
   pid_t child;
   
   if ( pipe(old) ) {
      perror("old pipe");
      exit(EXIT_FAILURE);
   }
   for(i=0; i<npipes; i++) {
      if ( i < npipes-1 ) { /* create new pipe */
         if ( pipe(next) ) {
            perror("next pipe");
            exit(EXIT_FAILURE);
         }
      }
   if ( !(child = fork()) ) {
    /* child */
   if( -1 == dup2(old[READ_END], STDIN_FILENO) ) {
      perror("dup2 old");
   }
   if ( i < num-1 ) {
      if ( -1 == dup2(next[WRITE_END], STDOUT_FILENO)) {
         perror("dup2 new");
      }
   }
 
 /* close any pipes that need to be closed */
   close(old[0]); 
   close(old[1]);
   close(next[0]);
   close(next[1]);
}
   /* parent */
   /* close up old pipe */
   close(old[0]);
   close(old[1]);
   old[0]= next[0];
   old[1]= next[1];
}
  
  while ( num-- ) {
      if ( -1 == wait(NULL)) {
         perror("wait");
      }
   }
   

}

