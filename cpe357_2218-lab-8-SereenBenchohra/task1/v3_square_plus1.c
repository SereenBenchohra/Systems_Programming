#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


#define MAX 4096
#define READ 0
#define WRITE 1

/*
        int fgetc(FILE *stream);

       char *fgets(char *s, int size, FILE *stream);

       int getc(FILE *stream);

       int getchar(void);

 *
 *
 */

int isINT(char *str)
{
    // checks if argument is integer other wise fail
    int N;
    char *end;

    N =  strtol(str, &end, 10); // converts string to integer

    if(end == str ) // raises error if not integer
    {
        fprintf(stderr, "%s not a integer\n", str);
        exit(EXIT_FAILURE);
    }


    return N;
}

int main()
{
    pid_t child1, child2, wpid;
    int status;
    char *line = NULL; // initialize to prevent leaks
    size_t size = 0;

    char buf[MAX];
    int num;

    int fd[2],fd1[2], fd2[2]; // need a second pipe

    while(getline(&line, &size, stdin) > 0) // getline returns a the line with a \n
    {
        if(pipe(fd) == -1 || pipe(fd1)  == -1 || pipe(fd2)  == -1) // use two pipes
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        if ( (child1=fork()) == 0 )
        {
            int readValue1 = 0;
            close(fd[WRITE]); // close write dont need it
            read(fd[READ], &readValue1, sizeof(readValue1));
            printf("%d\n", readValue1);
            readValue1 = (readValue1) * readValue1; // square the number
            close(fd[READ]);
            close(fd1[READ]);

            write(fd1[WRITE], &readValue1, sizeof(readValue1)); //write to second pipe
            close(fd1[WRITE]); // close when done

            exit(0);
        }

        else if (child1 == -1 )
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        else if((child2 = fork()) == 0) // 2nd child
        {
            int readValue2 = 0;
            close(fd1[WRITE]); // close write dont need it
            read(fd1[READ], &readValue2, sizeof(readValue2));
            readValue2 += 1; // increment by 1
           // printf("%d\n", readValue2);

            close(fd1[READ]); // close read when done
            close(fd2[READ]); // close read when done

            write(fd2[WRITE], &readValue2, sizeof(readValue2)); //write to second pipe
            close(fd2[WRITE]); // close when done
            exit(0);
        }

        else if (child2 == -1 )
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else
        {
            num  = isINT(line);
            close(fd[READ]); // close read end dont need it officially in the beggining for the parent
            write(fd[WRITE], &num, sizeof(num));
            close(fd[WRITE]); // close after done;




            if (-1 == wait(NULL)) // wait for childs  to finish
            {
                perror("wait");
                exit(EXIT_FAILURE);
            }
           // while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes
            int finalRead = 0;
            close(fd2[WRITE]);
            read(fd2[READ], &finalRead, sizeof(finalRead));
            close(fd2[READ]);



            printf("%d\n", finalRead);

        }



    }
    free(line);

    return 0;
}