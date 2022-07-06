
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "getInfo.h"
#include "readline.h"
#include <string.h> 

/* do not need to have command line arguments since making a simulation of a 
 * command line within the parseline */

 #include <string.h> 

int main() 
{
   
   int i;
   char *cmdLine, **parseBySpace; 
   char* token;
   FILE *file;
  
   Stage *stage;

   i = 0;
   file = stdin;
   printf("line: ");
 
   /* wait to scan string and enter as command line simulator */
   cmdLine = readline(file);    
    

   /* check for pipes, record number of pipes  */
      
   /* loop through the stages */

   while ((token = strtok_r(cmdLine, "|", &cmdLine)) != NULL) 
   {    
      /* prints stage header */
      printf("--------\n");
      printf("Stage %d: %c%s%c\n", i, '"', token, '"');
      printf("--------\n\n");
      
      /* gets input */
      parseBySpace = getWord(token);
      getInputOutput(parseBySpace, stage);
      printf("input: %s\n", stage->input);
      printf("output: %s\n", stage->output);

      
      i++;
   }

   return 0; 

}



