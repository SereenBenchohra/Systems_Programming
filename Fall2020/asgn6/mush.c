#define _GNU_SOURCE
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include "getInfo.h"
#include <string.h> 
#include "execCommands.h"
#include <mush.h>



/* dont need the command line since making our own shell and cmdLine */
int main()
{
   
 int nPipes;
 char *cmdLine, **parsedLine; 
  
/* change this to EOF */ 
 while(1) {

   printf("\n8-P ");

   cmdLine = read_line();
   parsedLine = getWord(cmdLine);

   /* execute the commands */ 
   
   nPipes = checkforPipes(parsedLine);
   if(nPipes == 0)
      exec_system(parsedLine);
   else
      exec_piped(parsedLine, nPipes);


   /* free before next prompt */
   free(cmdLine);
   free(parsedLine);

 
 }


   return 0;

}
