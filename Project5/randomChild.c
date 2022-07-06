/*
 * Provided file - DO NOT MODIFY!!!
 *
 * Description:
 *
 *    A simple program that reads a file of integer values, modifies them in
 *    a psuedo-random way, and writes the modified integer values out to a
 *    file.
 *
 *       Usage: randomChild -i fd -o fd
 *       Where: 0 <= fd <= 5
 *
 *    IMPORTANT NOTE: The file descriptors may NOT exceed MAX_FD which is
 *                    defined below.
 *
 * Purpose:
 *
 *    This program is intended to be a simple child process for you to launch
 *    arbitrarily long pipelines from a parent program that you will write but,
 *    unlike a Unix pipeline and as a simplification, makes the pipe file
 *    descriptor management explicit.
 */

/*
 * The following macro,_POSIX_SOURCE, allows this program to use fdopen which is
 * NOT part of the C89 version of C. While this does reduce the portability of
 * the code, it also makes it possible for me to write a simpler program for you
 * to work with and making this a simpler introduction to constructing a
 * pipeline in Unix is the primary goal of this project! So:
 *
 *    !!! YOU WILL NOT NEED TO DO THIS IN ANY OF YOUR CODE SO DON'T !!!
 */
#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define ARGC 5
#define MIN_FD 0
#define MAX_FD 5
#define SEED -756438915 /* A different seed will be used during evaluation */

typedef struct
{
   FILE *in;
   FILE *out;
} RandomChild;

/* Reads an ASCII integer value from rc.in and returns it via the value
 * argument.
 * 
 * Returns EOF at end-of-file, otherwise 0.
 */
static int readInteger(FILE *in, int *value)
{
   int ret;

   if (0 == (ret = fscanf(in, "%d", value))) {
      fprintf(stderr, "readInteger: %s at %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }

   if (ret == EOF) {
      *value = 0; /* Not strictly necessary but not a bad idea! */
      return EOF;
   }

   return 0;
}

/* Writes an int value as an ASCII integer value to rc.out.
 */
static void writeInteger(FILE *out, int value)
{
   int ret;

   if (1 > (ret = fprintf(out, "%d\n", value + rand())))
      /* Assume broken pipe - nothing to do but end in failure */
      exit(EXIT_FAILURE);
}

static void showUsageAndExit()
{
   fprintf(stderr, "Usage: randomChild -i inFD -o outFD\n");
   fprintf(stderr, "Where: inFD and outFD are <= %d\n", MAX_FD);
   exit(EXIT_FAILURE);
}

/* Finds and returns the argument value or, if the argument is not found
 * displays the usage message and exits.
 */
static void getArg(char *argv[], const char *arg, int *value)
{
   int i;

   for (i = 1; argv[i] != NULL; i+=2) {
      if (0 == strcmp(argv[i], arg)) {
         if (1 != sscanf(argv[i + 1], "%d", value))
            showUsageAndExit(); /* not numeric */
         else
            return; /* found */
      }
   }

   /* Argument not found */
   showUsageAndExit();
}

/* Note that this function converts the provided input and output file
 * descriptors to FILE* so that the program can more easily read and write
 * integer values as text. This is done to make your testing easier and,
 * typically would not be done. DO NOT use fdopen in any of your solutions
 * for 357 assignments as it is not compliant with C89 and reduces the
 * portability of any code that uses it.
 */
static RandomChild checkArgs(int argc, char *argv[])
{
   int fdIn, fdOut;
   RandomChild rc;

   if (argc != ARGC)
      showUsageAndExit();

   getArg(argv, "-i", &fdIn);
   if (fdIn < MIN_FD || fdIn > MAX_FD)
      showUsageAndExit();

   getArg(argv, "-o", &fdOut);
   if (fdOut < MIN_FD || fdOut > MAX_FD)
      showUsageAndExit();

   /* Do NOT use fdopen - see comment at top of this function for the reason */
   if (NULL == (rc.in = fdopen(fdIn, "r"))) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   /* Do NOT use fdopen - see comment at top of this function for the reason */
   if (NULL == (rc.out = fdopen(fdOut, "w"))) {
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   return rc;
}

int main(int argc, char *argv[])
{
   int value;
   RandomChild rc = checkArgs(argc, argv);

   /* IMPORTANT: A different seed will be use during evaluation */
   srand(SEED);

   /* Cause failed write to pipe to return "Broken Pipe" error, not signal */
   signal(SIGPIPE, SIG_IGN);
   
   /* Read, randomly modify, and write all values */
   while (EOF != (readInteger(rc.in, &value)))
      writeInteger(rc.out, value + rand()); /* Note: Overflow happens! */

   /* Close the files explicitly to be clear and because we should! */
   fclose(rc.in);
   fclose(rc.out);
   
   return 0;
}
