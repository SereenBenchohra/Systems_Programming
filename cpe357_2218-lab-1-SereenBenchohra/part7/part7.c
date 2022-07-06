#include <stdio.h>
#include "part7.h"
#include <ctype.h>
#include <string.h>

void str_lower(char old[], char lower[])
{  
    int i;
    for(i = 0; old[i] != '\0'; i++)
        lower[i] =  tolower(old[i]); 

    lower[i] = '\0'; // null terminate string
}

void str_lower_mutate(char lower[])
{
    int length = strlen(lower);
    char string[length];
    int i;
    for (i = 0; i < length; i++)
    {
        string[i] = tolower(lower[i]); 
        lower[i] = string[i];
    }    
    
    lower[i] = '\0'; // null terminate string
    lower = string;

}