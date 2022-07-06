#include <stdio.h>
#include "ui.h"
#include "getWord.h"

void DisplayUniqueVTotal(void *hashtable)
{
   int uniqueEntries, totalEntries;
   
   unique = htUniqueEntries(hashTable);
   totalEntries = htTotalEntries(hashTable);
   printf("%d unique found in %d total words", unique, totalEntries);

}

void DisplayWordFreq(HTEntry *entries, *argv[])
{
   int i;
   int numToDisplay = isThereNFlag(argv[]); // put the if statement in the function
   for(i = 0; i < numToDisplay; i++)
      printf("%d - %s", entries[i].freq, entries[i].data);

}


