#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordCount.h"

FILE* fileOpen(const char *fname)
{
   FILE* Open = fopen(fname, "r"); 
   if(Open == NULL )  
   {
      fprintf(stderr, "swc: %s: ", fname);
      perror("");
      exit(EXIT_FAILURE);
   }
   return Open;
}

void improperFlag(char *arg)
{
   printf("swc: invalid option: '%s'\n", arg);
   fprintf(stderr, "Usage: swc [-l|-w|-c]... [file]...\n");
   exit(EXIT_FAILURE);

}

int checkIfFlag(flagCheck *flag, char *arg, wordData wdata)
{

   if(arg[0] == '-')
   {
      if(arg[1] == 'n')
         flag->n = 1;
             
      else 
         improperFlag(arg); 
         
   }
}

int checkNFlags(int argc, char *arg[])
{
   int i
   for(i = 1; i < argc;i++)
      checkIfFlag(flag, arg[i]);      
}

int isItInput(int argc, char *argv[])
{
   int numInputs = 0;
   int i;
   for(i = 1; i < argc; i++)
      if(strcmp(argv[i],"-n") != 0 )
        numInputs++;
   return numInputs;

}

void printStdin(FILE* input, Word word, int *hasPrintable) // A pointer?
{
   getWord(input, word, hasPrintable);
}

void printMultiFile(flagCheck flag, char *argv, FILE* input, wordData *data)
{
   input = fileOpen(argv);
   getWord(input, data); // Put getWord Assign Data to HTAdd
   printf(" %s\n", argv);
   fclose(input);
}

void isFile(flagCheck *flag, int argc, char *argv, wordData *data) 
{

   FILE* input = stdin;

   if(strcmp(argv,"-n") != 0 )
      printMultiFile(*flag, argv, input, data);

}
void readMultiFile(flagCheck *flag, int argc, char *argv[], Word word)
{
   int i, inputLength;

   inputLength = isItInput(argc, argv);

   /* check where there is actual File */
   for(i = 1; i < argc; i++)  
      isFile(flag, argc, argv[i], data); /* check where there is actual input */
   
   if(inputLength > 1 ) /* check for multiple files */
      totalFile(*flag, *data);
}

void readFile(flagCheck *flag, int argc, char *argv[], wordData *data)
{
   /*Check to see reading from File input*/
   FILE* input = stdin;
   int inputLength;

   checkFlags(flag, argc, argv, *data);
   
   inputLength = isItInput(argc, argv);
   if(inputLength == 0)
      printStdin(*flag, input, *data); 
   else
      readMultiFile(flag, argc, argv, data);

}
