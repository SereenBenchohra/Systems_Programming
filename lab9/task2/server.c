#define _GNU_SOURCE
#include "net.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>



#define PORT 2828

void handle_request(int nfd)
{
   FILE *network = fdopen(nfd, "r");
   char *line = NULL;
   size_t size;
   ssize_t num;

   if (network == NULL)
   {
      perror("fdopen");
      return;
   }

   while ((num = getline(&line, &size, network)) >= 0)
   {
      printf("%s", line);
   }

   free(line);
   fclose(network);
}

void handle_child(int sig)
{
   printf("Here\n");
   wait(NULL);
}
void setup(int sig)
{
   struct sigaction sa;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = 0;
   sa.sa_handler = handle_child;

   sigemptyset(&sa.sa_mask);

   sigaction(sig, &sa, NULL);


}

void run_service(int fd)
{
   while (1)
   {
      int nfd = accept_connection(fd);
      if (nfd != -1)
      {
         pid_t pid;
         int status;

         if((pid = fork()) == -1)
            perror("fork");
         else if(pid == 0) // child
         {
            printf("Connection established\n");
            handle_request(nfd);
            printf("Connection closed\n");
            exit(0);
         }

         else // parent
         {
            setup(SIGCHLD);

            //wait(NULL);  //setup(SIGCHLD);

         }



      }
   }
}

int main(void)
{
   int fd = create_service(PORT);

   if (fd != -1)
   {
      printf("listening on port: %d\n", PORT);

      run_service(fd);

      close(fd);
   }

   return 0;
}