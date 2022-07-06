/*
 * Provoided source for the getWord exercise.
 *
 *   !!! DO NOT MODIFY !!!
 *
 * You must use this main with your exercise solution. Read the provided header
 * file (getWord.h) for the important details of the function you must write.
 */
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"

static void printWord(const Byte *word, unsigned wordLength, int hasPrintable)
{
   int i;

   printf("Printable: %5s, ", hasPrintable ? "true": "false");
   printf("Memory: %5u bytes, ", memCurrent());
   printf("Word: \"");

   /* For readability, this program limits each line to 30 characters max */
   for (i = 0; i < wordLength && i < 30; i++)
   {
      if (isprint(word[i]))
         printf("%c", word[i]);
      else
         printf("%c", '.');
   }
   
   /* Indicate the word is longer that was actually displayed */
   if (word->length > 30)
      printf("...");

   printf("\"\n");
}

static FILE* openFile(const char *fname)
{
   FILE* file = fopen(fname, "r");

   if (file == NULL)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   return file;
}

static void printUsageAndExit()
{
   fprintf(stderr, "Usage: getWord [-nomem | -quiet] fileName\n");
   exit(EXIT_FAILURE);
}

static FILE* checkArgs(int argc, char *argv[], int *quiet)
{
   if (argc == 2)
   {
      return openFile(argv[1]);
   }
   else if (argc == 3)
   {
      if (0 == strcmp("-nomem", argv[1]))
         memSetOutOfMemory(1);
      else if (0 == strcmp("-quiet", argv[1]))
         *quiet = 1;
      else
         printUsageAndExit();
   }
   else 
      printUsageAndExit();

   return openFile(argv[2]);
}

/*
 * Provided and required main for the getWord exercise. Read the documentation
 * in the provided getWord.h for details about the function you must write.
 *
 * This program reads "words" from the provided file by calling getWord (the
 * function you must write). The getWord function returns each "word" found
 * in the file in its own dynamically allocated and correctly sized memory
 * buffer along with its length and a boolean indicating whether or not it
 * contains any printable characters. The "words" are printed, memmon is used
 * to verify that the correct amount of memory was allocated, and then the
 * "word" is freed.
 *
 * BE SURE TO include "memmon.h" (and <stdlib> just before it) in the source
 * file containing your solution!
 */
int main(int argc, char *argv[])
{
   Word word;
   word->*byte = NULL;
   *word->length = 0;
   int hasPrintable, quiet = 0;
   FILE* file;

   /* Check the arguments and, if good, open the file to read from */
   file = checkArgs(argc, argv, &quiet);

   /* Call getWord and print the words, until done... */
   while(EOF != getWord(file, word->*byte, word->length, &hasPrintable))
   {
      if (!quiet)
         printWord(word, word->length, hasPrintable);
      free(*word.bytes);
   }
   
   /* Print and free the last word returned with the EOF, if any */
   if (!quiet)
      printWord(word, word->length, hasPrintable);

   free(*word.bytes);

   /* Make sure all the memory was freed */

   fclose(file);
   return EXIT_SUCCESS;
}
