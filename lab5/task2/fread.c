#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// test 
// 1, 2, 16, 32, 64, 128, 256, 512, 1024, 2048, and 4096
#define BUFSIZE 4096
#define PATH "/usr/lib/locale/locale-archive"

int main()
{
   int n;
   FILE *file;
   char *buffer[BUFSIZE];

   file = fopen(PATH, "r"); // might be rb


   if(file == NULL )
   {
      perror("fopen");
      return 1;
   }

   while((n =fread(buffer, BUFSIZE, sizeof(char) , file)) > 0);

   if(ferror(file))
   {
      perror("fread");
      return 1;
   }

   fclose(file);

   return 0;
}

/*
Write a small C program that opens a file (/usr/lib/locale/locale-archive on the department servers is a reasonable choice due to its size; though it is rather small by today's standards) and reads the contents of that file using the read system call. Write this code in a manner that allows you to easily change the number of bytes read (use a #define for the array size and argument to read).

Your program must not print anything (doing so will skew the timings discussed below).

Run this program with sizes 1, 2, 16, 32, 64, 128, 256, 512, 1024, 2048, and 4096 and record the running time with the time program on the command-line (e.g., at the prompt, type time ./a.out and record the "real" time). Plot the results; can you infer any characteristics about the system?

*/
