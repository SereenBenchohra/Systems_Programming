#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ui.h"
#include "hashTable.h"
#include <ctype.h>
#include <getopt.h>


void printMostFrequent( Node **sortedList, int parseNum, int numEntries)
{
   int i, min;
   min = (numEntries < parseNum)? numEntries: parseNum;
   printf("The top %d words (out of %d) are:\n", parseNum, numEntries);
 
   for(i = 0; i < min; i++)
      printf("%9d %s\n", sortedList[i]->freq, sortedList[i]->word);

}



FILE* fileOpen(const char *fname, int *isValid)
{
   FILE* Open = fopen(fname, "r"); 
   *isValid = 1;
   
   if(Open == NULL )  
   {
     *isValid = 0;
      perror(fname);
   }
   
   return Open;
}

void isNumeric( char *optarg)
{
   int i;
   for(i = 0; i < strlen(optarg); i++) {
      if(!isdigit(optarg[i])) {
         fprintf(stderr, "usage: fw [-n num] [ file1 [ file2 [...] ] ]");
         exit(EXIT_FAILURE);
      }
   }

   
}

int parseNum(int argc, char *argv[], int *nflag) 
{
   int option;

   while((option = getopt(argc, argv, "n:")) != -1){
      switch(option){
         case 'n' : 
            *nflag = 2;
            isNumeric(optarg);
            return (int)atol(optarg);
         case '?': /*if no number is inputted after -n flag */
            fprintf(stderr, "usage: fw [-n num] [ file1 [ file2 [...] ] ]");
            exit(EXIT_FAILURE);
            

       }
   }

   return 10;
}


