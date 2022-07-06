#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "getInfo.h"


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

   int i;

   char *arg;
   char **word;
   word = (char **)malloc(sizeof(token) * 20);
   i = 0;
   while (( arg = strtok_r(token, " ", &token)))
   {
      
      word[i] = arg;
      i++;

   }
  
   return word;

}



void getInputOutput(char **listOfWords, Stage *stage)
{
   int i;
   for( i = 0; listOfWords[i] != NULL; i++)
   {
      if(strcmp(listOfWords[i], "<") == 0)
      {
          stage->input = listOfWords[++i]; 
          printf("input redirection\n");

      }
      
      if(strcmp(listOfWords[i], ">")== 0)
      {         
        stage->output = listOfWords[++i]; 
        printf("output redirection\n");

      }

     
   }

}



