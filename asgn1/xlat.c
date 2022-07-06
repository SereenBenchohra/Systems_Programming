#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "functions.h"

#define TRUE  1
#define FALSE 0


void usage_error()
{
    fprintf(stderr, "usage: xlat [ -c ] [ -d ] set1 [ set2 ]\n");
    exit(EXIT_FAILURE);
}


void checkDefaultArgs(int argc,  char *argv[])
{
    if(argc != 3)
        usage_error();

    translate(argv[1], argv[2]);

}

void checkDflags( char argv[])
{
    /* check if argv exists otherwise usage error */
    if (argv == NULL)
        usage_error(); 
      my_delete(argv);
}


void checkCflags(char argv[])
{
    /* check if argv exists otherwise usage error */
    if (argv == NULL)
        usage_error(); 
    delete_complement(argv);
}


int parseOptArgs(int argc, char *argv[]) /* optarg for set1 */
{
    int isFlag, i;
    isFlag = FALSE;

    for (i = 1; i < argc; i++)
    {
        

        
        if (strcmp(argv[i], "-c") == 0)
        {
            if (argc < 4 || argc > 4)
                usage_error();
            else
            {
                isFlag = TRUE;
                if (strcmp(argv[i- 1], "-d" ) == 0)
                    checkCflags(argv[i + 1]);

                else if (strcmp(argv[i + 1], "-d" ) == 0)
                    checkCflags(argv[i + 2]);

                else
                    usage_error(); 
            }
        }

        else if(strcmp(argv[i], "-d") == 0)
        {
            if (argc < 3 || argc > 3)
                usage_error();
            else
            {
                isFlag = TRUE;
                /* c is not next argument */ 
                if (strcmp(argv[i+1], "-c") != 0)
                checkDflags(argv[i + 1]);
            }


        }
        
    }
    


    return isFlag;
}

int main(int argc,  char *argv[])
{
    
    int isFlag;
    
    isFlag = parseOptArgs(argc, argv);
    /* check to see if there is any optional flags */
    if( isFlag == FALSE)
        checkDefaultArgs(argc, argv);
     
    return 0;
}
