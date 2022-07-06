#include<stdio.h>
#ifndef WORDCOUNT_H
   #define WORDCOUNT_H
   typedef struct
   {
      int nl, nw, nc;
      int tnl, tnw, tnc;

   } wordData;

   typedef struct
   {
      int c, w, l; /*checks for the flags */
      int numFlags;
   } flagCheck;

   void wordCount(FILE* file, wordData *data);

#endif
