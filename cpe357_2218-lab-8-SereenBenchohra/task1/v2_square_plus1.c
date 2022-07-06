#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ  0
#define WRITE 1
#define MAX 4096


int isINT(char *str)
{
      // checks if argument is integer other wise fail
   int N;
   char *end;
   
   N =  strtol(str, &end, 10); // converts string to integer 

   if(end == str) // raises error if not integer
   {
      fprintf(stderr, "%s not an integer\n", str);
      exit(EXIT_FAILURE);
   }

   return N;
}

//  pid_t waitpid(pid_t pid, int *status, int options);
// need three pipes ( or use it three times )
// one between parent and child 1 -- sending integer from parent to child 
// child 1 -- reading from pipe and squaring the integer and sending it to child 2
// child 2 -- reading from pipe from child 1 and increment by 1 and send it back to parent
// parent -- print the value, and read another value
int main(int argc, char *argv[])
{
   pid_t child1, child2;
   int status;
   int fd[2],fd1[2], fd2[2]; // need a second pipe

   // fork process 
   if(pipe(fd) == -1 || pipe(fd1) == -1 || pipe(fd2) == -1)
   {
      perror("pipe");
      exit(EXIT_FAILURE);
   }

   /* 1st Child */
   if ( (child1=fork()) == 0 )
   {
      int readValue1 = 0;
      read(fd[READ], &readValue1, sizeof(readValue1));
      readValue1 = (readValue1) * readValue1; // square the number
      write(fd1[WRITE], &readValue1, sizeof(readValue1)); //write to second pipe

   }
      
   else if (child1 == -1 )
   {
      perror("fork");
      exit(EXIT_FAILURE);
   }

   else if((child2 = fork()) == 0) // 2nd child
   {
      int readValue2 = 0;
      read(fd1[READ], &readValue2, sizeof(readValue2));
      readValue2 += 1; // increment by 1
      write(fd2[WRITE], &readValue2, sizeof(readValue2)); //write to second pipe
   }

   else if (child2 == -1 )
   {
      perror("fork");
      exit(EXIT_FAILURE);
   }

   else /* parent */
   {
      
      // char *fgets(char *s, int size, FILE *stream);
      // reads integer from keyboard and
      char buf[MAX];
      int num;
      int finalRead = 0;


      while(fgets(buf, MAX, stdin) != EOF)
      {
         num  = isINT(buf);
         write(fd[WRITE], &num, sizeof(num));
         read(fd2[READ], &finalRead, sizeof(finalRead));

         
         wait(0);
         wait(0);

      
      }
      


      close(fd[READ]);
      close(fd[WRITE]);

      close(fd1[READ]);
      close(fd1[WRITE]);

      close(fd2[READ]);
      close(fd2[WRITE]);




      printf("%d\n", finalRead);
      
     
   }
  
      //printf("This is the parent, pid %d, signing off.\n", getpid()); 
  

   return 0;
}


