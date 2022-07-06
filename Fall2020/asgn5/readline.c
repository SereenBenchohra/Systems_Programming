#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "readline.h"


#define CHUNK 80

/* Nico 's readLine from Lab 2 solution with small adjustment */

extern char *readline(FILE *infile) 
{
   int i;
   char *buff;
   char *ret;

   int size = 0;
   char c;

   size = CHUNK;
   if(NULL == (buff = (char *)malloc(size *sizeof(char))))
   {
      perror("unable to allocate");
      exit(-1);

   }

   for(i=0,c=getc(infile); c!=EOF ;c=getc(infile)) 
   {
      if(i> size - 1)
      {
         size += CHUNK;
         if(NULL==(buff=(char*)realloc(buff,size * sizeof(char)))) 
         {
            perror("unable to allocate" );
            exit(-1);
         
         }
      }
         buff[i++] = c;
         if( c == '\n')
            break;
   }


   if(i) 
   {
      buff[i] = '\0';
      if(NULL == (ret = (char*)malloc(i + 1)))
      {
         perror("unable to allocate");
         exit(-1);
      }

      strcpy(ret, buff);

   }
   else
      ret = NULL;

  
  free(buff);
   
  if( i > 512)
  {
     fprintf(stderr, "command too long\n");
     exit(EXIT_FAILURE);

  }
  return ret;

}

