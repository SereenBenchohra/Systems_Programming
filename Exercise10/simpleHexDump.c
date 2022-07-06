/*
 *   !!! PROVIDED FILE - DO NOT MODIFY !!!
 */
#include <stdio.h>
#include <stdlib.h>
#include "hexFuncs.h"

/* Check the program invocation, display usage and exit if wrong
 */
static void checkArgs(int argc, char *argv[])
{
   if (argc < 2) {
      fprintf(stderr, "Usage: simpleHexDump file [file...]\n");
      exit(EXIT_FAILURE);
   }
}

static void dump(FILE *file)
{
   int bytesRead; 
   unsigned int writtenSoFar = 0;
   Byte bytes[BYTES_PER_LINE]; /* See hexFuncs.h for definitions */

   /* readBytes is a function you must write - see hexFuncs.h */
   while (0 < (bytesRead = readBytes(file, bytes))) {
      /* printLine is a function you must write - see hexFuncs.h */
      printLine(bytes, bytesRead, writtenSoFar);
      writtenSoFar += bytesRead;
   }
}

/*
 * A program to dump the content of text AND binary files to stdout in
 * hexadecimal and ASCII.
 */
int main(int argc, char *argv[])
{
   int i;
   FILE *file;
   int exitCode = EXIT_SUCCESS;

   /* checkArgs is a provided function - see above */
   checkArgs(argc, argv);

   for (i = 1; i < argc; i++) {
      printf("\nFile: %s\n", argv[i]);

      /* fileOpen is a function you must write - see hexFuncs.h */
      file = fileOpen(argv[i]); 

      if (file != NULL) {
         /* dump is a provided function - see above */
         dump(file);

         /* fileClose is a function you must write - see hexFuncs.h */
         fileClose(file);
      }
      else
         exitCode = EXIT_FAILURE;
   }

   return exitCode;
}
