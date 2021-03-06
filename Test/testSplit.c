#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char **split(char *string, char *delim)
{
   char *substring, *local;
   local = string; // have local copy to mutate and not affect original string
   char **stringArray;
   stringArray = NULL;

   int i = 0;
    while((substring = strsep(&local, delim)) != NULL)
        i++;

    stringArray = malloc(sizeof(char*) * i); // allocate size with appropiate length; 
    i = 0;

    local = string; // reset local to original
    while((substring = strsep(&local, delim)) != NULL)
        stringArray[i++] = substring;



   return stringArray;
}

int main()
{
    char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
    char** tokens;

    tokens = split(months, ",");
    printf("%s\n", tokens[0]);


    free(tokens);

    return 0;
}