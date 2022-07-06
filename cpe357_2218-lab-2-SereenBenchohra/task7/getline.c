// #define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* write a program that takes a file 
name as a command-line argument and prints the 
last three lines of this file (if there are 
fewer than three lines, then they will all be printed). */

FILE *open_file(char *path, char *mode)
{
   FILE *file;
   file = fopen(path, mode);
   if(file == NULL)
   {
      perror(path);
      exit(EXIT_FAILURE);
   }
   return file;

}

int main(int argc, char *argv[])
{
   /* Plan */
   // 1.  get the amount of lines in the file (done)
   // 2.  check if file has greater than 3 lines (done)
   // 3.  if not print all of them (done)
   // 4.  otherwise at line numbmer - 3 print the lines (done) 

   FILE *in, *file;
   char *first, *middle, *last;
   size_t size = 0;
   int line_num, count ;

   if(argc != 2)
   {
      fprintf(stderr, "Usuage %s [file]\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   in = fopen(argv[1], "r");
   file = fopen(argv[1], "r");
   
   first = middle = NULL;
   line_num = count =  0;
   while(getline(&first, &size, in) > 0)
      line_num++;

   while(getline(&middle, &size, file) > 0)
   {
      count++;
      if(count > (line_num - 3))
         printf("%s",middle);

   }
   
   fclose(in);
   fclose(file);
   free(first);
   free(middle);
   
   return 0;
}