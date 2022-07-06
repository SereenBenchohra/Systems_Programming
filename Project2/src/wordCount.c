#include <stdio.h>
#include <ctype.h>
#include "wordCount.h"

#define IN   1  /* inside a word */

#define OUT  0  /* outside a word */

void wordCount(FILE* file, wordData *data)
{ 
   
   int c,state;

   state = OUT;
   data->nl = data->nw = data->nc = 0;

   while((c = fgetc(file)) != EOF)
   {
      ++data->nc;
      if (c == '\n')
         ++data->nl;
      if( isspace(c) != 0) 
         state = OUT;
      else if(state == OUT && isprint(c))
      {
         state = IN;
         ++data->nw;
      }
   }

}
