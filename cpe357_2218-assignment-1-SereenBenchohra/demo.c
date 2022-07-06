#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"

// * big question?
// how do I organize the file ?

/* Things to do :
 *  
 *  organize strings into appropiate categories ( ie . race , country, population )
 *  find a way to get rid of quotation marks from strings ( have a function that searches for the quotation marks and removes it )
 *  incorporate the operations file and make operations 
 *  organize the categories
 *
 */

 // every line get the appropiate field and add it so the first in each line is a county
FILE *open_file(const char *path, const char *mode)
{
   FILE *file;
   if((file = fopen(path, mode)) == NULL)
   {
      perror(path);
      exit(EXIT_FAILURE);
   } 
   return file;
}

void checkArguments(int argc)
{
   if(argc != 2) // change it back to 3 when incorporating operations file
   {
      fprintf(stderr, "Usage: prog [demo] [operations]\n");
      exit(EXIT_FAILURE);
   }
}


int main(int argc, char *argv[])
{
   int i, linenum, charRead;
   size_t size = 0; // size of line auto completes with getline 
   char *line, *testString, *noQuotes; // line to read from getline
   linenum = 0; // have a line counter to keep count of lines

   // check if file exists and appropiate arguments
   checkArguments(argc);
   // open file for demographics for reading and later storing 

   // testString = strdup(testString);
   
   ArrayList *list;

   list = array_list_new();
   
   FILE *file;
   line = NULL; // initialize it to NULL or else get conditional jump 
   file = open_file(argv[1], "r"); // open the file 

   // read in file with getline
   while((charRead = getline(&line, &size, file)) > 0) 
   {
      if(linenum > 0) // check if not the first line to not print header
         split(line, ",", list); //parse for commas decide on how to organize string 
      linenum++;
   }

   for(i = 0; i < list->numEntries; i++)
   {

      noQuotes = drop_quotes(list->stringList[i]);
      printf("%s\n", noQuotes);
   }
   // testString = strdup( "\"Hello\"");
   testString = "\"Hello\"";

   printf("%s\n", testString);
   //noQuotes = drop_quotes(testString);

   //printf("%s\n", noQuotes);



   // free(testString);
   free(line); // free malloced line 
   // close file when finished with behavior 
   free_ArrayList(list);
   fclose(file);
   return 0; 
}


