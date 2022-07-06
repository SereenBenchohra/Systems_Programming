/*
 * Provided - DO NOT MODIFY!!! 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "qsortHTEntries.h"
#include "hashTable.h"
#include "getWord.h"

/* Hey, it's an exercise/exploration of qsort for a project,
 * no need to get all fancy and flexible here!
 */
#define MAX_ENTRIES 1000
#define MAX_WORDLEN 14 
#define MAX_FREQ 10 

static void displayUsageAndExit()
{
   fprintf(stderr, "Usage: qsort numberOfWords seed\n");
   fprintf(stderr, "Where: 0 < numberOfWords <= 1000\n"); 
   exit(EXIT_FAILURE);
}

static void checkArgs(int argc, char *argv[], int *numberOfWords, int *seed)
{
   if (argc != 3)
      displayUsageAndExit();

   if (1 != sscanf(argv[1], "%d", numberOfWords))
      displayUsageAndExit();

   if (*numberOfWords < 1 || *numberOfWords > MAX_ENTRIES)
      displayUsageAndExit();

   if (1 != sscanf(argv[2], "%d", seed))
      displayUsageAndExit();
}

static void makeRandomWords(HTEntry *entries, int numberOfWords, int seed)
{
   int i, j;
   Word *word;

   srand(seed);

   for (i = 0; i < numberOfWords; i++)
   {
      if (NULL == (word = malloc((sizeof(Word)))))
      {
         fprintf(stderr, "Failed malloc in %s at %d\n", __FILE__, __LINE__);
         exit(EXIT_FAILURE);
      }

      word->length = (rand() % MAX_WORDLEN) + 1;

      if (NULL == (word->bytes = malloc(word->length)))
      {
         fprintf(stderr, "Failed malloc in %s at %d\n", __FILE__, __LINE__);
         exit(EXIT_FAILURE);
      }

      /* Restrict to only non-whitespace characters */
      for (j = 0; j < word->length; j++)
         while (isspace(word->bytes[j] = rand() % UCHAR_MAX));

      entries[i].data = word;
      entries[i].frequency = (rand() % MAX_FREQ) + 1;
   }
}

void cleanUp(HTEntry *entries, int size)
{
   int i;

   for (i = 0; i < size; i++) {
      free(((Word*)entries[i].data)->bytes);
      free(entries[i].data);
   }
}

void printWords(const char *header, HTEntry *entries, int size)
{
   int i, j;
   unsigned length;

   printf("%s\n", header);

   for (i = 0; i < size; i++)
   {
      length = ((Word*)entries[i].data)->length;
      printf("   Word[%3d]: freq %2u, %2u bytes, hex:",
         i, entries[i].frequency, length);

      for (j = 0; j < length; j++)
         printf(" %02x", ((Word*)entries[i].data)->bytes[j]);

      printf("\n");
   }

   printf("\n");
}

int main(int argc, char *argv[])
{
   /* Hey, this is what htToArray in the Hash Table project returns, cool! */
   HTEntry entries[MAX_ENTRIES];
   int numberOfWords, seed;
   
   /* Set it up... */
   checkArgs(argc, argv, &numberOfWords, &seed);
   makeRandomWords(entries, numberOfWords, seed);

   printWords("BEFORE SORT:", entries, numberOfWords);

   /* This is a function you must write in a separate source file */
   qsortHTEntries(entries, numberOfWords);

   printWords("AFTER SORT:", entries, numberOfWords);
   
   cleanUp(entries, numberOfWords);
   return EXIT_SUCCESS;
}
