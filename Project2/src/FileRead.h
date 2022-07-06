#include<stdio.h>
#include "wordCount.h"

#ifndef FILEREAD_H
   #define FILEREAD_H

   FILE* fileOpen(const char *fname);

   /*void printFlags(int c, int l, int w, wordData data); */

   void printFlags(flagCheck flag, int nc, int nw, int nl);

   void checkIfFlag(flagCheck *flag, char *arg, wordData wdata);

   void checkFlags(int argc, char *argv[], wordData wdata);

   void printStdin(flagCheck flag, FILE* input, wordData data);

   void printMultiFile(flagCheck flag, char *argv, FILE* input, wordData data);

   int isItInput(int argc, char *argv[]);

   void totalFile(flagCheck flag, wordData data);
   void readFile(flagCheck *flag, int argc, char *argv[], wordData *data);

#endif
