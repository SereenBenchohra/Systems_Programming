#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define QUIT 'q'
#define NEW_PIPE 'n'
#define WRITE_TO_PIPE 'w'
#define READ_FROM_PIPE 'r'
#define CLOSE_PIPE_END 'c'

static void pipeError()
{
   fprintf(stderr, "Bad File Descriptor");
   exit(EXIT_FAILURE);
}
static void makeNewPipe(int fd[])
{
   if(pipe(fd) == -1)
   {   
      perror("Cannot Pipe");
      exit(EXIT_FAILURE);
   }
   printf("Pipe successfully created, read-fd is %d, write-fd is %d\n", fd[0],
      fd[1]);
}

static void writeToPipe(int fd[], char buf[])
{
   int input;
   printf("Enter the fd of the write-end to write to: ");
   if(scanf(" %d", &input) != 1)
      pipeError();
   else
      printf("Enter the integer value you wish to write: ");

   if(scanf(" %s", buf) != 1)
      pipeError();
   if(input != fd[1])
      pipeError();
   else{
      write(fd[1], &buf, strlen(buf));
      printf("The value %s was read successfully to fd \n", buf);
   }
}
static void readFromPipe(int fd[], char buf[])
{
   int input;
   printf("Enter the fd of the read-end to read to: ");
   if(scanf(" %d", &input) != 1)
      pipeError();

   if(input != fd[0])
      pipeError();
   else{
      read(fd[0], &buf, strlen(buf));
      printf("The value %s was read successfully to fd \n", buf);
   }

}

static void closePipe(int fd[], char buf[])
{
   int input;
   printf("Enter the fd of the pipe-end you wish to close: ");
   if(scanf(" %d", &input) != 1)
      pipeError();

   else{
      if(input == fd[0])
      {
         close(fd[0]);
         printf("File descriptor %d successfully closed \n", input);
      }
      else if(input == fd[1])
      {
         close(fd[1]);
         printf("File descriptor %d successfully closed  \n", input);
      }

      else{
         printf("Not valid");
      }

   }
}
static int getCommand()
{
   char command;

   printf("\nCommand Menu:\n");
   printf("   n - Create a new pipe\n");
   printf("   w - Write to a pipe end\n");
   printf("   r - Read from a pipe end\n");
   printf("   c - Close a pipe end\n");
   printf("   q - Quit\n\n");
   printf("Enter a command: ");

   /* I know, this expects the user to be perfect - hey it's an exercise! */
   scanf(" %c", &command);
   return command;
}

static int doACommand()
{
   char command = getCommand();
   int fd[2];
   char buf[128];

   switch (command)
   {
      case NEW_PIPE:
         makeNewPipe(fd);
      break;

      case WRITE_TO_PIPE:
         writeToPipe(fd, buf);
      break;

      case READ_FROM_PIPE:
         readFromPipe(fd, buf);
      break;

      case CLOSE_PIPE_END:
         closePipe(fd, buf);
      break;

      case QUIT:
         printf("Bye Bye - see you next time!\n");
      break;

      default:
         printf("Unknown command, please try again...\n");
   }

   return command;
}

/*
 * NOTE: The SIGPIPE signal is ignored in this program so that you can see the
 *       error that occurs when you try to write to a pipe whose read-end is
 *       closed - be sure to try that scenario!
 */
int main()
{
   int command = !QUIT;

   /* See comment block preceding main */
   signal(SIGPIPE, SIG_IGN);

   while (command != QUIT)
      command = doACommand();

   return 0;
}
