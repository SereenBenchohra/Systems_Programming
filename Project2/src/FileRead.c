#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordCount.h"

FILE* fileOpen(const char *fname)
{
   FILE* Open = fopen(fname, "r"); 
   if(Open == NULL )  
   {
      fprintf(stderr, "swc: "); // fprintf(stderr, "swc: %s: ", fname);
      perror(fname); /* Exit Failure was there */
   }
   return Open;
}

void printThreeFlags(flagCheck flag, int nc, int nw, int nl) 
{

   if(flag.c == 0 && flag.w == 0 && flag.l == 0)
      printf("%10u %10u %10u", nl, nw, nc);   

   else if(flag.c == 1 && flag.w == 1 && flag.l == 1)
      printf("%10u %10u %10u", nl, nw, nc);    

}
void printOneFlags(flagCheck flag, int nc, int nw, int nl) 
{

   if(flag.c == 0 && flag.w == 0 && flag.l == 1)
      printf("%10u", nl);  

   else if(flag.c == 0 && flag.w == 1 && flag.l == 0)
      printf("%10u", nw); 

   else if(flag.c == 1 && flag.w == 0 && flag.l == 0)
      printf("%10u", nc);  
}

void printTwoFlags(flagCheck flag, int nc, int nw, int nl)
{
     
   if(flag.c == 0 && flag.w == 1 && flag.l == 1)
      printf("%10u %10u", nl, nw);    

   else if(flag.c == 1 && flag.w == 0 && flag.l == 1)
      printf("%10u %10u", nl, nc);    
   
   else if(flag.c == 1 && flag.w == 1 && flag.l == 0)
      printf("%10u %10u", nw, nc);
}

void printFlags(flagCheck flag, int nc, int nw, int nl) 
{
   printThreeFlags(flag, nc, nw, nl); 
   printOneFlags(flag, nc, nw, nl); 
   printTwoFlags(flag, nc, nw, nl); 
}

void improperFlag(char *arg)
{
   fprintf(stderr,"swc: invalid option: '%s'\n", arg);
   fprintf(stderr, "Usage: swc [-l|-w|-c]... [file]...\n");
   exit(EXIT_FAILURE);

}

void checkIfFlag(flagCheck *flag, char *arg, wordData wdata)
{

   if(arg[0] == '-')
   {
      if(arg[1] == 'c' && arg[2] == '\0')
         flag->c = 1;
            
      else if(arg[1] == 'w' && arg[2] == '\0')
         flag->w = 1;
            
      else if(arg[1] == 'l'&& arg[2] == '\0') 
         flag->l = 1;
            
      else 
         improperFlag(arg); 
         
   }
}

void checkFlags(flagCheck *flag, int argc, char *arg[], wordData wdata)
{
   int i; 
   flag->numFlags = argc;
  
   flag->c = flag->l = flag->w = 0;   
   for(i = 1; i < argc;i++)
      checkIfFlag(flag, arg[i], wdata);      
}

int isItInput(int argc, char *argv[])
{
   int numInputs = 0;
   int i;
   for(i = 1; i < argc; i++)
      if(strcmp(argv[i],"-c") != 0 && 
         strcmp(argv[i],"-w") != 0 && strcmp(argv[i],"-l") != 0 )        
         numInputs++;
   return numInputs;

}

void totalFile(flagCheck flag, wordData data)
{   
   printFlags(flag, data.tnc, data.tnw, data.tnl);
   printf(" total\n");
     
}

void printStdin(flagCheck flag, FILE* input, wordData data)
{
   wordCount(input, &data);
   printFlags(flag, data.nc, data.nw, data.nl);
   printf("\n");
}

void printMultiFile(flagCheck flag, char *argv, FILE* input, wordData *data)
{
   input = fileOpen(argv);
   wordCount(input, data);
   data->tnl  = data->nl + data->tnl;
   data->tnw = data->nw + data->tnw;
   data->tnc = data->nc + data->tnc; 
   printFlags(flag, data->nc, data->nw, data->nl);
   printf(" %s\n", argv);
   fclose(input);
}

void isFile(flagCheck *flag, int argc, char *argv, wordData *data) 
{

   FILE* input = stdin;

   if(strcmp(argv,"-c") != 0 && 
      strcmp(argv,"-w") != 0 && strcmp(argv,"-l") != 0 )
      printMultiFile(*flag, argv, input, data);

}
void readMultiFile(flagCheck *flag, int argc, char *argv[], wordData *data)
{
   int i;

   int inputLength;

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
   data->tnl = 0;
   data->tnw = 0;
   data->tnl = 0;
   inputLength = isItInput(argc, argv);
   if(inputLength == 0)
      printStdin(*flag, input, *data); 
   else
      readMultiFile(flag, argc, argv, data);

}
