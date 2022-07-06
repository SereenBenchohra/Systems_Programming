#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "getInfo.h"

#define DELIM " \t\r\n\a"


char *read_line(void)
{
    
    int numBytes;
    char *line = NULL;
    ssize_t bufsize = 512; 

    if ((numBytes = getline(&line, &bufsize, stdin)) == -1){
       if (feof(stdin)) 
           exit(EXIT_SUCCESS); 
       else  {
              perror("readline");
              exit(EXIT_FAILURE);
          }
       
   }
   if( numBytes > 512)
   {
      fprintf(stderr, "Cmd line too long ");
      exit(1);

   }
   return line;
}



int pipeChecker (char *cmdLine)
{
   
   
   /* loop through string to check for 
    * parse into words that help */ 
   char *token; 
   int pipeCheck;

   while ((token = strtok_r(cmdLine, "|", &cmdLine)) != NULL) 
      pipeCheck++;

    
   return pipeCheck;

   return 0;


}

/* make two functions */
/* one is make a list of "words" */

/* the other is a list of pure arguments */

char **getWord(char *token)
{

   int i, bufSize;

   char *arg;
   char **words;
   bufSize = 64;
   words = (char **)malloc(sizeof(token) * 20);
   i = 0;
   while (( arg = strtok_r(token, DELIM, &token)))
   {
      
      words[i] = arg;
      i++;
      if(i >= bufSize){
      
         bufSize += bufSize;
         words = realloc(words, bufSize * sizeof(char*));
         if (!words) {
           fprintf(stderr, "lsh: allocation error\n");
           exit(EXIT_FAILURE);
      }
   }
   }
   
   words[i] = NULL;
   return words;

}


