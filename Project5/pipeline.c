#include "launcher.h"
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgen.h>

void pipeline(procData *data)
{
   pid_t pid;
   /*procData data; */
   int i;
   int status, fd1[2];

   //parseFile(argc, argv, data);

   // pipe(fd2);

   for(i = 0; i < data->numProc; i++)
   {
      if(pipe(fd1) == -1)
      {
         perror("Cannot Pipe");
         exit(EXIT_FAILURE);
      }

      close(fd1[0]); /* close the read end */

      if((pid = fork()) < 0)
      {
         fprintf(stderr, "fork error");
         exit(EXIT_FAILURE);
      }

      else if(pid == 0) /* child  */
      {
         //if(i == 0)
         write(fd1[1]);
         read(fd1[0]);
         // close(fd1[1]);
         if(execl(argv[data->procIndex], basename(argv[data->procIndex]), "-i",
            fd1[0], "-o",  fd1[1], (char*)NULL) < 0)
         {
            perror("No such file or directory");
            exit(127);
         }
      }
      else /* Parent Code */
      {
        /* if(pipe(fd1) == -1)
         {
            perror("Cannot Pipe");
            exit(EXIT_FAILURE);
         } */
         close(fd1[1]);
         // close(fd1[0]);
      }
      if((pid = wait(NULL)) < 0)
      {
         perror("wait error");
         exit(EXIT_FAILURE);
      }
   }

   for(i = 0; i < data.numProc; i++)
      wait(&status);

}

int main(int argc, char *argv[])
{
   procData *data;
   parseFile(argc, argv, data);
   printf("Process number : %d  Child : %d Process Flag %d\n", data->numProc,
          data->procIndex, data->pFlag);
   pipeline(data);
   return 0;
}