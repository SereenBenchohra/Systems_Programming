#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/wait.h>


#include <string.h>


void set_timer(int sec)
{
    struct itimerval it_val;
    it_val.it_value.tv_sec = sec;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;


    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
        perror("setitimer");
        exit(-1);
    }

}
int isINT(char *str)
{
    // checks if argument is integer other wise fail
    int N;
    char *end;

    N =  strtol(str, &end, 10); // converts string to integer

    if(end == str || (N < 0 )) // raises error if not integer
    {
        fprintf(stderr, "%s not a positive integer\n", str);
        exit(EXIT_FAILURE);
    }

    return N;
}
void handle_action(int signo)
{
    printf("Killing Child..\n");
    exit(EXIT_FAILURE);
}
void setup(int signo) // pass signal alarm
{
    struct sigaction action;

    if(sigemptyset(&action.sa_mask) == -1)
    {
        perror("sigemptyset");
        exit(-1);
    }
    action.sa_handler = handle_action;
    action.sa_flags = 0;

    if(sigaction(signo, &action, NULL) == -1)
    {
        perror("sigaction");
        exit(-1);
    }

}


int main(int argc, char *argv[])
{
// check if integer
    pid_t child;
    setup(SIGALRM);

    int sec = isINT(argv[1]);
    if(argc < 3 )
    {
        fprintf(stderr, "Usage : need at least 3 arguments\n");
        exit(EXIT_FAILURE);
    }


//save the argument for exec argv[2] and rest
    char **arg = malloc(sizeof(char *) * (argc));

    int j = 0;
    for (int i = 2; argv[i] != NULL;  i++)
        arg[j++] = strdup(argv[i]);

    arg[j] = (char*)NULL;


    if((child = fork()) == -1)
    {
        perror("fork");
        exit(-1);
    }
    else if(child == 0) // child
    {

        execvp(arg[0], arg);
        exit(0);
    }
    else // parent
    {
        set_timer(sec);
        if (-1 == wait(NULL)) // wait for child  to finish
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; arg[i] != NULL; ++i)
        free(arg[i]);


    free(arg);

    return 0;
}
