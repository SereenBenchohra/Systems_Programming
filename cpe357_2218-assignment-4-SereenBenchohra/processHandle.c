#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "fileHandle.h"
#include "processHandle.h"

int spawn(void )
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("");
        exit(EXIT_FAILURE);
    }
    return pid;
}


// if there are less downloads than max downloads, download all request
void download_all(Down_Info **download_list, int array_len )
{
    pid_t pid;
    int status;

    for(int i = 0; i < array_len; i++)
    {
        if((pid = spawn()) == 0) // child
        {
            printf("Starting download request for line : %d\n", i+1);

            if(download_list[i]->sec != NULL) // if the second parameter exists, run the exec with the sec argument
                execlp("curl", "curl","-m", download_list[i]->sec , "-o", download_list[i]->filename, "-s", download_list[i]->URL, (char *)NULL);
            else
                execlp("curl", "curl" , "-o", download_list[i]->filename, "-s", download_list[i]->URL, (char *)NULL);

            exit(0);
        }
    }

    for (int i = 0; i < array_len; i++) // wait for child process to finish
    {
        if(waitpid(pid, &status, 0) != -1) // wait for child
        {
            if(!WIFEXITED(status))
                printf("Process %d exited abnormal\n", pid);

        }
        printf("Finished download request for line: %d\n\n", i+1);
    }

}

void max_exceeded(Down_Info **download_list, int array_len, int maxDown)
{
    pid_t pid;
    int status, procToWait, procWaited, i, num;
    num = 1; // // num to keep track of multiple processes running at the same time
    i = procWaited = procToWait = 0;

    int remain = array_len; // record how many are remaining left
    while(remain > 0 ) // so long as there are downloads left to use, keep looping
    {
        // if it is a child , go into and download
        if((pid = spawn()) == 0) // child
        {
            printf("Starting download request for line : %d\n", i+1);

            if(download_list[i]->sec != NULL) // if the second parameter exists, run the exec with the sec argument
                execlp("curl", "curl","-m", download_list[i]->sec , "-o", download_list[i]->filename, "-s", download_list[i]->URL, (char *)NULL);
            else
                execlp("curl", "curl" , "-o", download_list[i]->filename, "-s", download_list[i]->URL, (char *)NULL);

            exit(0);
        }

            // if maxDownloads is reached(parent) , wait for a child to finish
            if((num) > maxDown) // record the amount waited, then subtract from total downloads
            {
                if(waitpid(pid, &status, 0) != -1) // wait for child
                {
                    if(!WIFEXITED(status))
                        printf("Process %d exited abnormal\n", pid);

                }
                printf("Finished download request for line: %d\n\n", i+1);
                num--;
                procWaited++;
            }
        i++;
            num++;
        remain--; // decrement the amount
    }

    procToWait = array_len - procWaited;
    for(int j = 0; j < procToWait; j++)
    {
        if(waitpid(pid, &status, 0) != -1) // wait for child
        {
            if(!WIFEXITED(status))
                printf("Process %d exited abnormal\n", pid);
        }
        printf("Finished download request for line: %d\n\n", j+1);
    }

}
