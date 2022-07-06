/*
 * Provided child program for pipe-fork-exec exercise.
 *
 *    !!! DO NOT MODIFY !!!
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_MSG 100

static int readMessage(int fd, char *msg)
{
   int i = 0, ret;

   /* Read in an entire string, including the nul-terminator */
   while(1) {
      /* This call will block until there is something to read or end-of-file */
      if (0 == (ret = read(fd, &msg[i], 1)))
         return EOF;
      else if (ret == -1) {
         fprintf(stderr, "write failure in %s at line %d\n", __FILE__, __LINE__);
         exit(EXIT_FAILURE);
      }
      else if (msg[i] == 0) /* Breaks on end-of-string */
         break;

      /* Otherwise keep reading... */
      i++;
   }

   return ret;
}

static void writeMessage(int fd, const char *msg)
{
   int len = strlen(msg) + 1;

   if (len != write(fd, msg, len)) {
      fprintf(stderr, "write failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
}

static int getFD(const char *arg)
{
   int fd;

   if (1 != sscanf(arg, "%d", &fd)) {
      fprintf(stderr, "Bad fd argument\n");
      exit(EXIT_FAILURE);
   }

   return fd;
}

int main(int argc, char **argv)
{
   int readFD, writeFD, msgCount = 0;
   char inMsg[SIZE_MSG], outMsg[SIZE_MSG];

   if (argc != 3) {
      fprintf(stderr, "Usage: child readFD writeFD\n");
      exit(EXIT_FAILURE);
   }

   readFD = getFD(argv[1]); 
   writeFD = getFD(argv[2]); 
   
   /* Send a "birth-announcement" to the parent */
   sprintf(outMsg,"I'm alive! Reading from %d, writing to %d", readFD, writeFD);
   writeMessage(writeFD, outMsg); 

   /* Loop until my parent is done - EOF when they close their write-end */
   while(1) {
      /* This will block until a message is sent */
      if (EOF == readMessage(readFD, inMsg))
         break;

      /* Send an acknowledgment to the parent */
      sprintf(outMsg, "Message %d: %s", ++msgCount, inMsg);
      writeMessage(writeFD, outMsg); 
   }

   /* Done! */
   sprintf(outMsg, "Okay, I guess you don't want to talk anymore, goodnight!");
   writeMessage(writeFD, outMsg); 

   /* Just because we should */
   close(readFD);
   close(writeFD);

   return EXIT_SUCCESS;
}
