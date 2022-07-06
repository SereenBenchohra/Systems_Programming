#include <stdio.h>
`#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"

void checkEmptyPointer(Byte * temp)
{
   if(temp == NULL)
   {   
      perror("Empty Pointer");
      exit(EXIT_FAILURE);
   }
}

/*static void reallocWhenItFills(int reallocSize, unsigned *wordLength, Byte **word)
{

   Byte* temp;
   temp = NULL;
      if(reallocSize == *wordLength )
      {
         reallocSize = reallocSize * 2;
         
         temp = realloc(*word, sizeof(Byte)* reallocSize);

         checkEmptyPointer(temp);
         *word = temp;
      }

}
*/

int getWord(FILE *file, Word word, int *hasPrintable)
{
   
   
   int c, i, reallocSize;
   Byte* temp;
   word = (Byte*)malloc(sizeof(Byte));
   word->length = 0;
   *hasPrintable =  0;
   i = 0;
   reallocSize = 1;
   c = fgetc(file);
   temp = NULL;
   while(isspace(c))  
      c = fgetc(file);
   while(EOF!=c && !isspace(c))
   { 
      if(isprint(c))
         *hasPrintable = 1;

      //reallocWhenItFills(reallocSize, wordLength, word);
      if(reallocSize == word->length )
      {
         reallocSize = reallocSize * 2;
         
         temp = realloc(word, sizeof(Byte)* reallocSize);

         checkEmptyPointer(temp);
         word = temp;
      }


      c = tolower(c);
      *((word) + i) = c;
      i++;
      word->length+= 1;
      c= fgetc(file);
   }

   word = realloc(word, sizeof(Byte) * (word->length));


   if(c == EOF)
      return EOF;

   return 0;
}

