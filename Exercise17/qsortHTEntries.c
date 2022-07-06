#include "hashTable.h"
#include <stdlib.h>
#include "getWord.h"

int wordLengthCmp(const void * a, const void * b)
{
   Word* wordA = (Word *)a;
   Word* wordB = (Word *)b;
   
   return (wordA->length - wordB-> length);

}

int wordByteCmp (const void * a, const void * b)
{  
   
   int i, matchCount;
   HTEntry *entryA = (HTEntry *)a;
   HTEntry *entryB = (HTEntry *)b;

   Word* wordA = (Word *)entryA->data;
   Word* wordB = (Word *)entryB->data;

   unsigned loopLength;
   loopLength = (wordA->length > wordB->length) ? wordA->length : wordB->length;

   for(i = 0; i < loopLength; i++)
   {   
      if( (int)wordA->bytes[i] > (int)wordB->bytes[i])
         return 1;

      else if((int)wordA->bytes[i] < (int)wordB->bytes[i])
         return -1;

      else if((int)wordA->bytes[i] == (int)wordB->bytes[i])
         matchCount++;
        
   }

   return wordLengthCmp(a, b);

}

int compare(const void * a, const void * b) 
{ 
   HTEntry *entryA = (HTEntry *)a;
   HTEntry *entryB = (HTEntry *)b;
   if(entryA->frequency == entryB->frequency)
      return wordByteCmp(a, b);
   
   return (entryB->frequency - entryA -> frequency);

}

void qsortHTEntries(HTEntry *entries, int numberOfEntries)
{
   qsort(entries, numberOfEntries, sizeof(HTEntry), compare);
}

