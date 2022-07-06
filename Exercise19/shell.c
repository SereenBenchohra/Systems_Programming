#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
   char buf[4096];
   pid_t pid;
   int status;

   printf("%% "); /*print prompt (printf requires %% to print % */
   while (fgets(buf, 4096, stdin) != NULL)
   {
      if(buf[strlen(buf) - 1] == '\n')
         buf[strlen(buf) - 1] = 0; /* replace newline with null */

      if((pid = fork()) < 0)
      {
         fprintf(stderr, "fork error");
         exit(EXIT_FAILURE);
      }
      else if(pid == 0)
      {
         execlp(buf, buf, (char *)0);
         perror("NULL");
         exit(127);
      }
      if((pid = waitpid(pid, &status, 0)) < 0)
      {
         perror("wait error");
         exit(EXIT_FAILURE);
      }
   }
   
   return 0;

}
