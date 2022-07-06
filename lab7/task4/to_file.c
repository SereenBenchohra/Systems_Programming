#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
   Your program is going to use "exec" to run the specified 
   program. Before doing so, however, your program will need 
   to open the specified file and take the appropriate steps 
   to redirect standard output to the specified file. 
   This setup is done so that the exec’d program will write 
   its output to the file.


*/
void valid_arguments(int argc, char *argv[])
{
   if(argc != 3) // check if number of arguments are valid
   {
      fprintf(stderr, "Usage error\n");
      exit(EXIT_FAILURE);
   }

   
}
/*
This program will take two command-line arguments.
 The first is the name of another program and the
  second is the name of a file (which need not yet exist).
*/
int main(int argc, char *argv[]) 
{
   
   // check if they are two command line arguments 
   // valid_arguments(argc, argv);

   // opens file, create the file if it doesnt exist
   int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600); // owner can read and write

   dup2(fd, 1); // redirects stdout to file opened in file 
   close(fd);

   execl(argv[1],argv[1], "20", (char *)NULL ); // takes first argument, an executable , its path, its argument

   return 0; 
}